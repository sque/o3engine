#ifndef O3ENGINE_MATERIAL_HPP_INCLUDED
#define O3ENGINE_MATERIAL_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./texture.hpp"
#include "./texturemanager.hpp"
#include "./singletonmanager.hpp"

namespace o3engine {


	//! Material parameter
	struct MaterialParameter {

		MaterialParameter() = default;

		MaterialParameter(Material * powner, const std::string & name);

		const std::string & getName() const {
			return m_name;
		}

		ogl::uniform & getUniform();
	protected:

		Material * mp_owner;

		std::string m_name;
	};

	/**
	 * @brief Material base
	 */
	class Material : public ManagedObject<MaterialManager, string, Material>
	{
	public:
		//! Type of parameters container
		typedef std::map<std::string, MaterialParameter> parameters_container_type;

		// Default constructor
		Material(const string & name);

		// Virtual destructor
		virtual ~Material(){};

		//! Get shader program
		ogl::program & getProgram() {
			return *mp_program;
		}

		//! Get shader program (const)
		const ogl::program & getProgram() const {
			return *mp_program;
		}

		//! Set shader program
		void setProgram(ogl::program * pprog) {
			if (pprog)
				mp_program = pprog;
		}

		void addParameter(const std::string & param_name);

		bool hasParameter(const std::string & param_name);

		parameters_container_type getParameters();

		MaterialParameter & getParameter(const std::string & param_name);

		virtual void preUse() const {}

		virtual void postUse() const {}

		void Use() const {
			preUse();
			getProgram().use();
			postUse();
		}
	protected:

		//! Container of parameters
		parameters_container_type m_params;

		//! Pointer to GPU program
		ogl::program * mp_program;
	};
}

// Include Material manager
#include "./materialmanager.hpp"

#endif
