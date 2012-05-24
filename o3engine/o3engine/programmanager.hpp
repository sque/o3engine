#ifndef O3ENGINE_PROGRAMMANAGER_HPP_INCLUDED
#define O3ENGINE_PROGRAMMANAGER_HPP_INCLUDED

#include "prereqs.hpp"
#include <set>
#include <iostream>

namespace o3engine {

	//! String wrapper to declare a new filename type
	struct FileName {
		FileName(const std::string & name) :
			m_fname(name){
		}

		FileName(const FileName &) = default;
		FileName & operator=(const FileName &) = default;

		const std::string & string() const {
			return m_fname;
		}

	protected:
		std::string m_fname;
	};

	//! Preprocess exception
	struct preprocess_exception : public std::runtime_error {
		preprocess_exception(const std::string & what) :
			runtime_error(what){
		}
	};

	//! Manager class for all GPU Programs
	class ProgramManager :
		public Singleton<ProgramManager>{
	public:

		//! Default constructor
		ProgramManager();

		//! Type definition of include directories
		typedef std::vector<std::string> search_dirs_container_type;

		//! Get a program defined by its unique nickname
		ogl::program * getProgramPtr(const std::string & name) {
			return m_programs[name];
		}

		//! Check if there is a program with a nickname
		bool hasProgram(const std::string & name) {
			return m_programs.find(name) != m_programs.end();
		}

		//! Load a new program from source
		template<class TVertex, class TFragment, class TGeometry = nullptr_t, class TTessellation = nullptr_t>
		ogl::program * loadProgram(
				const char * name,
				const TVertex & vsh,
				const TFragment & fsh,
				const TGeometry & gsh = nullptr,
				const TTessellation & tsh = nullptr) {

			// Check if it already exists
			if (hasProgram(name))
				return getProgramPtr(name);

			// Create a new program
			ogl::program * pprog = new ogl::program();

			// load shader objects
			loadShader(pprog, ogl::shader_type::VERTEX, vsh);
			loadShader(pprog, ogl::shader_type::FRAGMENT, fsh);
			loadShader(pprog, ogl::shader_type::GEOMETRY, gsh);
			// TODO: GLEW 1.7 loadShader(pprog, ogl::shader_type::TESS, tsh);

			// compile objects and link them together
			try {
				pprog->build();
			} catch(ogl::shader_compile_error & e) {
				std::cerr << e.m_shader.source() << std::endl;
				throw e;
			}

			// register
			m_programs[name] = pprog;
			return pprog;
		}

		//! Delete and remove a program from manager
		bool removeProgram(const std::string & name);

		//! Add a new search directory
		void addSearchDirectory(const std::string & path);

		//! Remove a search directory
		void removeSearchDirectory(const std::string & path);

		//! Get all search directories
		const search_dirs_container_type & getSearchDirectories() const {
			return m_search_dirs;
		}

		//! Check if it has a search directory
		bool hasSearchDirectory(const std::string & path) const {
			return (std::find(m_search_dirs.begin(), m_search_dirs.end(), path) != m_search_dirs.end());
		}

	protected:

		//! Type definition of programs container type
		typedef std::map<std::string, ogl::program * > programs_container_type;

		//! Programs container
		programs_container_type m_programs;

		//! Shaders include search directories
		search_dirs_container_type m_search_dirs;

		//! Find file path by looking in search directories
		std::string findFilePath(const std::string & filename);

		//! Preprocess an included file source and return new source
		std::string includeFileSource(
				const std::string & fsource,
				std::uint16_t & max_glsl_version,
				std::set<std::string> &depending_modules,
				bool compile_object = true);

		//! Load shader from files
		void loadShader(ogl::program * pprog, ogl::shader_type type, const FileName & src_fname);

		//! Load shader from in-memory string
		void loadShader(ogl::program * pprog, ogl::shader_type type, const std::string & source);

		//! Don't load shader
		inline void loadShader(ogl::program * pprog, ogl::shader_type type, std::nullptr_t) {}
	};
}


#endif
