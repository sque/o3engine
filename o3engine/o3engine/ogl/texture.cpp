#include "./texture.hpp"

namespace o3engine {
namespace ogl{

	// Generate one texture
	texture::texture(const tex_type & type):
		m_tex_type(type){
		::glGenTextures(1, &m_gl_name);
	}

}
}
