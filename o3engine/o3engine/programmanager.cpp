#include "programmanager.hpp"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/tokenizer.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <iostream>

namespace fs = boost::filesystem;

namespace o3engine {

	template<> ProgramManager * Singleton<ProgramManager>::ms_singleton = nullptr;

	ProgramManager::ProgramManager() {}

	//! Get file contents
	std::string __get_file_contents(const std::string & fpath) {
		std::ifstream shader_file;
		shader_file.open(fpath, std::ifstream::in);
		if (!shader_file.is_open())
			throw std::invalid_argument(std::string("Cannot open shader file \"") + fpath + "\"");

		// get length of file:
		shader_file.seekg (0, std::ios::end);
		size_t length = shader_file.tellg();
		shader_file.seekg (0, std::ios::beg);

		// Read all source
		std::string file_source;
		file_source.resize(length);
		shader_file.read(&file_source[0], length);
		return file_source;
	}

	std::string ProgramManager::findFilePath(const std::string &filename) {

		fs::path fpath(filename);
		if (fpath.is_absolute())
			return filename;

		// Search in all directories and return the first found
		for(auto sdir : m_search_dirs) {
			fs::path filepath(sdir + "/" + filename);
			if (!fs::exists(filepath))
				continue;
			if (!fs::is_regular_file(filepath))
				continue;

			return filepath.string();	//Found
		}

		return "";
	}

	std::string ProgramManager::includeFileSource(
			const std::string & fsource,
			std::uint16_t & max_glsl_version,
			std::set<std::string> &depending_modules,
			bool compile_object) {
		std::string processed_source;

		// By default glsl version is 100
		max_glsl_version = 100;

		// Regular expressions
		boost::regex regversion("^#version\\s+(\\d+)");
		boost::regex regdepend("^#depend\\s+\"([^\"]+)\"\\s*$");

		// Line tokenizer
		boost::char_separator<char> nlsep("\n");
		boost::tokenizer<boost::char_separator<char>> lines(fsource, nlsep);
		for(const std::string & line : lines) {
			if (line.find("#version") != std::string::npos) {
				boost::smatch version;
				if (!boost::regex_search(line, version, regversion, boost::match_default)) {
					throw shader_preprocess_error(std::string("Cannot parse #version directive: \"") + line + "\"");
				}
				uint16_t glsl_version = boost::lexical_cast<std::uint16_t>(version[1]);
				if (glsl_version > max_glsl_version)
					max_glsl_version = glsl_version;
			} else if (line.find("#depend") != std::string::npos) {
				boost::smatch filematch;
				if (!boost::regex_search(line, filematch, regdepend, boost::match_default)) {
					throw shader_preprocess_error(std::string("Cannot parse #depend directive: \"") + line + "\"");
				}
				uint16_t included_max_glsl_version;
				std::string included_fpath = findFilePath(filematch[1]);
				if (included_fpath.empty()){
					throw shader_preprocess_error("Cannot open #depend ing file \"" + filematch[1] + "\"");
				}

				std::string include_source = includeFileSource(__get_file_contents(included_fpath), included_max_glsl_version, depending_modules, false);
				if (included_max_glsl_version > max_glsl_version)
					max_glsl_version = included_max_glsl_version;

				depending_modules.insert(included_fpath);
				if (compile_object) {
					// We must wrap it because it changes state from COMPILE_OBJECT = 1 to COMPILE_OBJECT = NULL
					include_source = "#undef COMPILE_OBJECT\n" + include_source + "\n#define COMPILE_OBJECT 1\n";
				}
				processed_source += include_source;
			} else {

				processed_source += line + "\n";
			}
		}

		return processed_source;
	}

	void ProgramManager::loadShader(ogl::program * pprog, ogl::shader_type type, const std::string & source) {
		if (source.empty())
			return;

		// Preprocess file source
		std::uint16_t max_glsl_version;
		std::set<std::string> dependending_modules;
		std::string processed_source = includeFileSource(source, max_glsl_version, dependending_modules);

		// Add final header
		std::string final_source = std::string("#version ") + boost::lexical_cast<std::string>(max_glsl_version) + "\n";
		final_source +=	"#ifndef O3ENGINE\n"
				"#define O3ENGINE 1\n"
				"#define O3ENGINE_VERSION_MAJOR " STRINGIFY(O3ENGINE_VERSION_MAJOR) "\n"
				"#define O3ENGINE_VERSION_MINOR " STRINGIFY(O3ENGINE_VERSION_MINOR) "\n"
				"#define O3ENGINE_VERSION_REVISION " STRINGIFY(O3ENGINE_VERSION_REVISION) "\n"
				"#define COMPILE_MODULE 1 \n"
				"#endif\n";
		final_source += processed_source;

		//std::cout << "<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl << final_source << std::endl << "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" << std::endl;
		for(auto d : dependending_modules) {
			loadShader(pprog, type, FileName(d));
		}
		pprog->attach_shader(*new ogl::shader(type, final_source));	// TODO: Leak ogl::shader
	}

	void ProgramManager::loadShader(ogl::program * pprog, ogl::shader_type type, const FileName & src_fname) {

		// Find file
		std::string fpath = findFilePath(src_fname.string());
		if (fpath.empty()) {
			throw runtime_error("Cannot find shader file \"" + src_fname.string() + "\"");
		}

		// Actually load shader object
		loadShader(pprog, type, __get_file_contents(fpath));
	}

	bool ProgramManager::removeProgram(const std::string & name) {
		programs_container_type::iterator it = m_programs.find(name);
		if (it == m_programs.end())
			return false;	// Not found

		delete it->second;
		m_programs.erase(it);

		return true;
	}

	void ProgramManager::addSearchDirectory(const std::string & pathname) {
		fs::path sdir(pathname);

		// Checks on the validity
		if (!fs::exists(sdir))
			throw std::runtime_error(std::string("Search directory \"") + pathname + "\" does not exist.");
		if (!fs::is_directory(sdir))
			throw std::runtime_error(std::string("Search directory \"") + pathname + "\" is not directory.");

		// Canonicalize and push back
		sdir = fs::canonical(sdir);
		if(!hasSearchDirectory(sdir.string()))
			m_search_dirs.push_back(sdir.string());
	}

	void ProgramManager::removeSearchDirectory(const std::string & pathname) {
		fs::path sdir(pathname);
		if (!fs::is_directory(sdir))
			throw std::runtime_error(std::string("Cannot include search directory ") + pathname + ".");
	}


}
