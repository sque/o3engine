#ifndef O3ENGINE_NODMATERIAL_HPP_INCLUDED
#define O3ENGINE_NODMATERIAL_HPP_INCLUDED

#include "material.hpp"
#include "nodmaterial/nodecontainer.hpp"
#include "nodmaterial/mathnode.hpp"
#include "nodmaterial/constantvaluenode.hpp"
#include "nodmaterial/shadingnode.hpp"
#include "nodmaterial/geometrynode.hpp"
#include "nodmaterial/texturenode.hpp"

namespace o3engine {

	class NodMaterial : public Material,
		public nodmaterial::Node,
		public nodmaterial::NodeContainer{
	public:
		NodMaterial(const std::string & name);

		//! Build a program out of this material
		void buildProgram();

		std::string getStaticCode(ogl::shader_type type);

		std::string getExecutedCode(ogl::shader_type type);

		std::string getOutputSocketReference(ogl::shader_type type, const std::string & socket_name);

	};

	void import_nodmaterials(const std::string & fname);
}

#endif
