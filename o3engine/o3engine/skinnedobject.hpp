#ifndef SKINNEDOBJECT_H_INCLUDED
#define SKINNEDOBJECT_H_INCLUDED

#include "./prereqs.hpp"
#include "./material.hpp"
#include "./drawableobject.hpp"

namespace o3engine
{
	class SkinnedObject : public DrawableObject
	{
	protected:

		//! Material of object
		const Material * pMaterial;

		//! A flag if object is transperant
		bool bTransperant;

		//! The function that will contain the draw code of object
		virtual void drawObject(bool bSolid) = 0;

	public:
		// Constructor
		SkinnedObject(const string & name);

		// Destructor
		virtual ~SkinnedObject();

		inline virtual void drawSolidPart()
		{   if (bTransperant)
				return;

			if (pMaterial)
			{
				pMaterial->useme_to_glPreDraw();
				drawObject(true);
				pMaterial->useme_to_glPostDraw();
			}
			else
				drawObject(true);
		}

		inline virtual void drawTransperantPart()
		{	if (!bTransperant)
				return;

			if (pMaterial)
			{
				pMaterial->useme_to_glPreDraw();
				drawObject(false);
				pMaterial->useme_to_glPostDraw();
			}
			else
				drawObject(false);
		}

		/**
		 * @brief Set the material of object
		 * @param mat_name The name of the material that we want to apply
		 */
		void setMaterial(const string & mat_name);

		/**
		 * @brief Set the material of object
		 * @param pmat The pointer to the material we want to apply
		 */
		inline void setMaterial(const Material * _pmat)
		{   pMaterial = _pmat;
			if (pMaterial)
				bTransperant = !pMaterial->getDepthWrite();
			else
				bTransperant = false;
		}

		/**
		 * @brief Unset the material of object
		 */
		inline void unsetMaterial() { pMaterial = NULL; bTransperant = false; }

		inline virtual bool hasTransperant()
		{	return bTransperant;	}
	};
}
#endif // SKINNEDOBJECT_H_INCLUDED
