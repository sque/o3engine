#ifndef O3ENGINE_MATERILIZER_HPP_INCLUDED
#define O3ENGINE_MATERILIZER_HPP_INCLUDED

#include "material.hpp"
#include "materilizer/node.hpp"
#include "materilizer/mathnode.hpp"
#include "materilizer/colornode.hpp"
#include "materilizer/lightingnode.hpp"

namespace o3engine {

	class Materilizer : public Material,
		public materilizer::Node{
	public:
		Materilizer(const std::string & name);

		//! Build a program out of this material
		void buildProgram();

		virtual std::string getStaticCode(ogl::shader_type type);

		virtual std::string getGeneratedCode(ogl::shader_type type);

		virtual std::string getGeneratedOutputValue(ogl::shader_type type, const std::string & connector_name);
	protected:

	};
}


#endif
