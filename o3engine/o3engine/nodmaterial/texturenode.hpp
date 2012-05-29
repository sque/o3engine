#ifndef O3ENGINE_NODMATERIAL_TEXTURE_HPP_INCLUDED
#define O3ENGINE_NODMATERIAL_TEXTURE_HPP_INCLUDED

#include "node.hpp"

namespace o3engine {
namespace nodmaterial {

	//! Node to sample from a texture
	class TextureNode : public Node{
	public:
		//! Construct a new texture node
		TextureNode(NodeContainer * powner, const std::string & name, const std::string & texture_name);

		//! Set a new texture
		void setTexture(Texture * ptexture) {
			mp_texture = ptexture;
		}

		//! Get the texture
		const Texture * getTexture() const {
			return mp_texture;
		}

		virtual std::string getStaticCode(ogl::shader_type type);

		virtual std::string getExecutedCode(ogl::shader_type type);

		virtual std::string getOutputSocketReference(ogl::shader_type type, const std::string & socket_name);

	private:

		//! Pointer to texture
		Texture * mp_texture;
	};
}
}


#endif
