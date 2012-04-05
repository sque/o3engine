#include "./materialmanager.hpp"

namespace o3engine
{
	Material::Material(const string & name)
		:ManagedObject<MaterialManager, string, Material>(name)
	{
		// Set default values
		c_basic = Color::WHITE;
		c_diffuse = Color(0.8, 0.8, 0.8, 1.0);
		c_ambient = Color(0.2, 0.2, 0.2, 0.2);
		c_specular = Color::WHITE;
		c_emission = Color::BLACK;
		m_shininess = 50;
		f_lighting = b_depthwrite = true;
		seq = 1;
		p_Texture = NULL;
	}

	// Run opengl commands to setup material
	void Material::useme_to_glPreDraw() const
	{
		return ;
		// Color
		if (f_lighting)
		{
			glEnable ( GL_COLOR_MATERIAL );

			// Diffuse
			glColorMaterial ( GL_FRONT_AND_BACK, GL_DIFFUSE ) ;
			glColor4(c_diffuse);

			// Ambient
			glColorMaterial ( GL_FRONT_AND_BACK, GL_AMBIENT ) ;
			glColor4(c_ambient);

			// Specular
			glColorMaterial ( GL_FRONT_AND_BACK, GL_SPECULAR ) ;
			glColor4(c_specular);

			// Emission
			glColorMaterial ( GL_FRONT_AND_BACK, GL_EMISSION ) ;
			glColor4(c_emission);

			// Disable color
			glDisable( GL_COLOR_MATERIAL ) ;

			// Shininess
			glMaterialf(GL_FRONT, GL_SHININESS, (GLfloat)m_shininess);
		}else
		{
			glColor4(c_basic);    // Basic color
			glDisable(GL_LIGHTING);
		}

		// Disable depth if it is transperant
		if (!b_depthwrite)
			glDepthMask(GL_FALSE);

		// Enable texturing
		if (p_Texture)
		{
			p_Texture->glBind2d();
			glEnable( GL_TEXTURE_2D );
		}
	}

	// Run opengl to post-set materials after object drawing
	void Material::useme_to_glPostDraw() const
	{
		return;
		// Enable lighting again
		if (!f_lighting)
			glEnable(GL_LIGHTING);

		// Disable depth if it is transperant
		if (!b_depthwrite)
			glDepthMask(GL_TRUE);

		// Disable texturing
		if (p_Texture)
		{   glDisable( GL_TEXTURE_2D );    }
	}
}
