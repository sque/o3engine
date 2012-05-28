#ifndef O3ENGINE_MATERILIZER_HPP_INCLUDED
#define O3ENGINE_MATERILIZER_HPP_INCLUDED

#include "material.hpp"
#include "materilizer/node.hpp"
#include "materilizer/mathnode.hpp"
#include "materilizer/fixedvaluenode.hpp"
#include "materilizer/lightingnode.hpp"

namespace o3engine {

	class Materilizer : public Material,
		public materilizer::Node{
	public:
		Materilizer(const std::string & name);

		//! Build a program out of this material
		void buildProgram();

		std::string getStaticCode(ogl::shader_type type);

		std::string getExecutedCode(ogl::shader_type type);

		std::string getOutputSocketReference(ogl::shader_type type, const std::string & socket_name);

	};
}

#endif
