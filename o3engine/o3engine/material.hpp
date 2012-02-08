#ifndef MATERIAL_H_INCLUDED
#define MATERIAL_H_INCLUDED

#include "./prereqs.hpp"
#include "./texture.hpp"
#include "./texturemanager.hpp"
#include "./singletonmanager.hpp"

namespace o3engine
{
	/**
	 * @brief Material describer and handler
	 */
	class Material : ManagedObject<MaterialManager, string, Material>
	{
	protected:
		Color c_basic;      // Basic color
		Color c_diffuse;    // Diffuse color
		Color c_ambient;    // Ambient color
		Color c_specular;   // Specular color
		Color c_emission;   // Emission color
		Real m_shininess;  // Shininess exponement
		Texture * p_Texture;    // Pointer to texture;

		bool f_lighting;    // Flag for lighting usage
		bool b_depthwrite;  // Flag showing if depth write should be enabled

		unsigned long seq;  // Sequence number

	public:
		// Default constructor
		Material(const string & name);

		// Virtual destructor
		virtual ~Material(){};

		// Set colors
		inline Color setBasicColor(const Color & b) { seq ++; return c_basic = b; }
		inline Color setDiffuse(Color d) { seq++; return c_diffuse = d; }
		inline Color setAmbient(const Color & a) { seq ++; return c_ambient = a; }
		inline Color setSpecular(const Color & s) { seq ++; return c_specular = s; }
		inline Real setShininess(Real e) { seq ++; return m_shininess = e ; }
		inline Color setEmissive(const Color & e) { seq ++; return c_emission = e; }


		// Get parameters
		inline const Color & getBasicColor() const { return c_basic; }
		inline const Color & getDiffuse() const  { return c_diffuse;   }
		inline const Color & getAmbient() const { return c_ambient;   }
		inline const Color & getSpecular() const { return c_specular; }
		inline const Color & getEmissive() const { return c_emission;  }
		inline Real getShininess() const { return m_shininess; }

		// Texture
		inline Texture * attachTexture(Texture * p_text){ seq++; return p_Texture = p_text; }
		inline Texture * attachTexture(const string & tex_name)
		{    return attachTexture(TextureManager::getObjectPtr(tex_name));  }
		inline bool hasTexture() const { return p_Texture != NULL; }

		// Copy operator
		inline Material operator = (const Material &rmat)
		{
			// Copy colors
			c_basic = rmat.c_basic;
			c_emission = rmat.c_emission;
			c_diffuse = rmat.c_diffuse;
			c_ambient = rmat.c_ambient;
			c_specular = rmat.c_specular;

			// Parameters
			m_shininess = rmat.m_shininess;
			b_depthwrite = rmat.b_depthwrite;
			f_lighting = rmat.f_lighting;

			// Texture
			p_Texture = rmat.p_Texture;
			seq++; return *this;
		}

		// Lighting
		inline bool getLightingEffects() const {   return f_lighting;   }
		inline bool setLightingEffects(bool f){ seq ++; return f_lighting = f; }
		inline void enableLightingEffects() {  f_lighting = true; seq ++; }
		inline void disableLightingEffects() { f_lighting = false; seq ++; }

		// Depth write
		inline bool getDepthWrite() const { return b_depthwrite; }
		inline bool setDepthWrite(bool f) { seq ++; return b_depthwrite = f; }
		inline void enableDepthWrite() {   b_depthwrite = true; seq++; }
		inline void disableDepthWrite() {   b_depthwrite = false; seq++; }

		// Run opengl commands to setup material pre object drawing
		void useme_to_glPreDraw() const;

		// Run opengl to post-set materials after object drawing
		void useme_to_glPostDraw() const;

		inline unsigned long getSequenceNum() const {   return seq; }
	};
}

// Include Material manager
#include "./materialmanager.hpp"

#endif // MATERIAL_H_INCLUDED
