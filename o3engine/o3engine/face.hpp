#ifndef FACE_H_INCLUDED
#define FACE_H_INCLUDED

#include "./prereqs.hpp"

namespace o3engine
{
	class Face
	{
	protected:
		Vector3 points[3];      // Triangle points
		Vector3 normals[3];     // Normal vectors for lighting
		Vector2 textcords[3];   // Texture cords

	public:

		// Default constructor
		Face();

		// Constructor with points and normals
		Face(const Vector3 & _p1, const Vector3 & _p2, const Vector3 & _p3,
			const Vector3 & _n1, const Vector3 & _n2, const Vector3 & _n3);

		// Constructor with points and one normal for all vertexes
		Face(const Vector3 & _p1, const Vector3 & _p2, const Vector3 & _p3, const Vector3 & n);

		// use me to populate vertices
		inline void myglVertex()
		{
			glVertex(points[0]);
			glVertex(points[1]);
			glVertex(points[2]);
		}

	   // use me to populate vertices with normal
		inline void glVertex_with_normal()
		{
			glNormal(normals[0]);
			glVertex(points[0]);

			glNormal(normals[1]);
			glVertex(points[1]);

			glNormal(normals[2]);
			glVertex(points[2]);
		}

		// use me to populate vertices with normal and textcoords
		void glVertex_with_normal_n_textcoords()
		{
			glTexCoord(textcords[0]);
			glNormal(normals[0]);
			glVertex(points[0]);

			glTexCoord(textcords[1]);
			glNormal(normals[1]);
			glVertex(points[1]);

			glTexCoord(textcords[2]);
			glNormal(normals[2]);
			glVertex(points[2]);
		}
		// Copy operator
		Face & operator=(const Face & r);

		// Get points
		inline const Vector3 & getPoint1() const{   return points[0]; }
		inline const Vector3 & getPoint2() const{   return points[1]; }
		inline const Vector3 & getPoint3() const{   return points[2]; }

		// Get light normals
		inline const Vector3 & getNormal1() const{   return normals[0]; }
		inline const Vector3 & getNormal2() const{   return normals[1]; }
		inline const Vector3 & getNormal3() const{   return normals[2]; }

		// Get text coords
		inline const Vector2 & getTextCoord1() const{  return textcords[0];    }
		inline const Vector2 & getTextCoord2() const{  return textcords[1];    }
		inline const Vector2 & getTextCoord3() const{  return textcords[2];    }

		// Set points
		inline Vector3 setPoint1(const Vector3 & _r){   return points[0] = _r;    }
		inline Vector3 setPoint2(const Vector3 & _r){   return points[1] = _r;    }
		inline Vector3 setPoint3(const Vector3 & _r){   return points[2] = _r;    }

		// Set light normals
		inline Vector3 setNormal1(const Vector3 & _r){   return normals[0] = _r;    }
		inline Vector3 setNormal2(const Vector3 & _r){   return normals[1] = _r;    }
		inline Vector3 setNormal3(const Vector3 & _r){   return normals[2] = _r;    }

		// Set text coords
		inline Vector2 & setTextCoord1(const Vector2 & _r){  return textcords[0] = _r;    }
		inline Vector2 & setTextCoord2(const Vector2 & _r){  return textcords[1] = _r;    }
		inline Vector2 & setTextCoord3(const Vector2 & _r){  return textcords[2] = _r;    }

		inline void translate(const Vector3 & _trans)
		{   points[0].translate(_trans);    points[1].translate(_trans);    points[2].translate(_trans);}

		Real calcSphericalSize() const;
	};
}
#endif // FACE_H_INCLUDED
