#include "programmanager.hpp"
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

namespace fs = boost::filesystem;

namespace o3engine {

	template<> ProgramManager * Singleton<ProgramManager>::ms_singleton = nullptr;

	ProgramManager::ProgramManager() {
		addSearchDirectory("resources/shaders");
	}
	void ProgramManager::loadShader(ogl::program * pprog, ogl::shader_type type, const std::string & source) {
		if (source.empty())
			return;
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
