#include "texturenode.hpp"
#include "../texturemanager.hpp"
#include "builder_tools.hpp"

namespace o3engine {
namespace nodmaterial {

	TextureNode::TextureNode(NodeContainer * powner, const std::string & name, const std::string & texture_name) :
		Node(powner, name, typeid(this).name()){
		addInputSocket<Socket::ValueType::Vec4>("coordinates", Vector4(0,0,0,1));
		addOutputSocket<Socket::ValueType::Vec4>("color");

		mp_texture = TextureManager::getSingleton().getObjectPtr(texture_name);
	}

	std::string TextureNode::getStaticCode(ogl::shader_type type) {

		switch(type) {
		case ogl::shader_type::FRAGMENT:
			return "uniform sampler2D myTexture;\n";// + builder::output_variable_name(this, "textureSample" );
		default:
			return "";
		}
	}

	std::string TextureNode::getExecutedCode(ogl::shader_type type) {

		switch(type){
		case ogl::shader_type::FRAGMENT:
			return "vec4 pixel = texture(myTexture, (" + builder::input_value(type, this, "coordinates") + ").xy);\n";
		default:
			return "";
		}

	}

	std::string TextureNode::getOutputSocketReference(ogl::shader_type type, const std::string & socket_name) {
		switch(type) {
		case ogl::shader_type::FRAGMENT:
			return "pixel";
		default:
			return "";
		}
	}
}
}
