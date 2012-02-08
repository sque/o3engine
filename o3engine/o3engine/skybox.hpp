#ifndef SKYBOX_H_INCLUDED
#define SKYBOX_H_INCLUDED

#include "./prereqs.hpp"
#include "./primativeshapes.hpp"

namespace o3engine
{
	class Skybox
	{
	protected:

		Real half_size;             //! Half-Size of skybox
		Texture * ptextures[6];     //! Pointer to 6 textures
		bool bHasTextures;          //! A Flag showing if skybox has textures

		//! Update cache of skybox
		void updateCache()
		{   bHasTextures = false;
			for(int i = 0;i < FACE_MAX; i++)
				if (ptextures[i])
					bHasTextures = true;
		}
	public:

		//! Constructor
		Skybox()
		{
			// Reset texture pointers
			for(int i = 0;i < FACE_MAX;i++)
				ptextures[i] = NULL;

			// Set size
			half_size = 500;
			bHasTextures = false;
		}

		//! Enumeration of faces
		enum E_FACE
		{
			FACE_TOP,
			FACE_BOTTOM,
			FACE_RIGHT,
			FACE_LEFT,
			FACE_FRONT,
			FACE_BACK,
			FACE_MAX
		};

		void drawObject(Camera * _pCamera);

		//! Attach texture to face by pointer
		inline void attachTexture(int face, Texture * p_tex)
		{   ptextures[face] = p_tex; updateCache(); }

		//! Attach texture to face by name
		inline void attachTexture(int face, const string & tex_name)
		{   ptextures[face] = TextureManager::getObjectPtr(tex_name); updateCache(); }

		//! Remove a texture
		inline void removeTexture(int face)
		{   ptextures[face] = NULL;
			updateCache();
		}

		//! Remove all textures
		inline void removeAllTextures()
		{
			for(int i = 0;i < FACE_MAX; i++)
					ptextures[i] = NULL;
			updateCache();
		}
	};
}
#endif // SKYBOX_H_INCLUDED
