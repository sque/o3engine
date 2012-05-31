#include "texturenode.hpp"
#include "../texturemanager.hpp"
#include "programbuilder.hpp"
#include <boost/lexical_cast.hpp>

namespace o3engine {
namespace nodmaterial {

	TextureNode::TextureNode(NodeContainer * powner, const std::string & name, const std::string & texture_name) :
		Node(powner, name, typeid(this).name()),
		m_texunit_id(0){
		addInputSocket<Socket::ValueType::Vec4>("coordinates", Vector4(0,0,0,1));
		addOutputSocket<Socket::ValueType::Vec4>("color");

		mp_texture = TextureManager::getSingleton().getObjectPtr(texture_name);
	}

	std::string TextureNode::getStaticCode(ogl::shader_type type) {

		switch(type) {
		case ogl::shader_type::FRAGMENT:
			return "#extension GL_ARB_shading_language_420pack: enable\n"
					"layout(binding=" + boost::lexical_cast<std::string>(m_texunit_id) + ")uniform sampler2D " + this->getName() + "textureSample" + ";\n";
		default:
			return "";
		}
	}

	std::string TextureNode::getExecutedCode(ogl::shader_type type) {

		switch(type){
		case ogl::shader_type::FRAGMENT:
			return "vec4 " +builder::output_variable_name(this, "color") + " = texture(" + this->getName() + "textureSample" +
					", (" + builder::input_value(type, this, "coordinates") + ").xy);\n";
		default:
			return "";
		}

	}

	std::string TextureNode::getOutputSocketReference(ogl::shader_type type, const std::string & socket_name) {
		switch(type) {
		case ogl::shader_type::FRAGMENT:
			return builder::output_variable_name(this, "color");
		default:
			return "";
		}
	}

	const Node::predraw_function_type TextureNode::getPreDrawFunction() {
		return [this] {
			ogl::current_ctx().texture_unit(this->m_texunit_id).bind_texture(this->getTexture()->glObject());
		};
	}

	void TextureNode::preBuild(ProgramBuilder & pm){
		m_texunit_id = boost::lexical_cast<size_t>(pm.getDynamicBuildFlag("TextureNode::texture_unit", "0"));

		pm.getDynamicBuildFlags()["TextureNode::texture_unit"] = boost::lexical_cast<std::string>(m_texunit_id + 1);
	}
}
}
