#ifndef PRIMATIVESHAPES_H_INCLUDED
#define PRIMATIVESHAPES_H_INCLUDED

#include "./prereqs.hpp"
#include "./skinnedobject.hpp"

namespace o3engine
{
	//! Primitive shape Sphere
	/**
	 * A sphere made having proper normals and texture coords.
	 */
	class Sphere : public SkinnedObject
	{
	protected:
		Real radius;
		int slices, stacks;
		GLUquadric* sphere_quadric;

		// Draw object
		inline virtual void drawObject(bool bSolid){   gluSphere(sphere_quadric, radius, slices, stacks);   }

	public:

		//! Default constructor
		/**
			Creates a sphere of radius 0.5 with 5 slices and 5 stacks.
		*/
		inline Sphere(const string & name)
			: SkinnedObject(name)
		{   radius = 0.5;
			slices = 5;
			stacks = 5;
			sphere_quadric = gluNewQuadric();
			gluQuadricTexture(sphere_quadric, GL_TRUE);
			gluQuadricOrientation(sphere_quadric, GLU_OUTSIDE);
		}

		//! Constructor with predefined size and quality
		/**
			Creates a sphere with custom size, slices, stacks
		*/
		inline Sphere(const string & name, Real _radius, int _slices, int _stacks)
			: SkinnedObject(name)
		{   radius = _radius;
			slices = _slices;
			stacks = _stacks;
			sphere_quadric = gluNewQuadric();
			gluQuadricTexture(sphere_quadric, GL_TRUE);
			gluQuadricOrientation(sphere_quadric, GLU_OUTSIDE);
		}

		//! Destructor
		virtual ~Sphere()
		{   gluDeleteQuadric(sphere_quadric);   }

		//! Get the radius of sphere
		Real getRadius() const { return radius; }

		//! Set the radius o sphere
		Real setRadius(Real _radius) { return radius = _radius;  }

		//! Get the slices of shpere
		int getSlices() const { return slices;  }

		//! Set the slices of sphere
		int setSlices(int _slice){ return slices = _slice;  }

		//! Get the stacks of sphere
		int getStacks() const { return stacks;  }

		//! Set the stacks of sphere
		int setStacks(int _stacks) { return stacks = _stacks;   }
	};

	//! Primitive object Cube
	/**
	 * A Cube object created with GLUT.
	 */
	class Cube : public SkinnedObject
	{
	protected:
		Real size;

		inline virtual void drawObject(bool bSolid) {  glutSolidCube(size);    }

	public:

		//! Default Constructor
		inline Cube(const string & name)
			: SkinnedObject(name)
		{   size = 1;   }

		//! Construct with predefined size
		inline Cube(const string & name, Real _size)
			: SkinnedObject(name)
		{   size = _size;   }

		//! Destructor
		inline virtual ~Cube(){}

		//! Get the size of cube
		Real getSize() const { return size; }

		//! Set the size of cube
		Real setSize(Real _size){ return size = _size;  }
	};

	//! Primitive object Line
	/**
	 * A Line with a start and end point defined by user.
	 */
	class Line : public SkinnedObject
	{
	protected:
		Vector3 point_start, point_end;

		inline virtual void drawObject(bool bSolid)
		{
			glBegin(GL_LINES);
				glVertex(point_start);
				glVertex(point_end);
			glEnd();
		}

	public:

		//! Constructor with default values
		inline Line(const string & name)
			: SkinnedObject(name)
		{   point_start = Vector3::ZERO; point_end = Vector3::UNIT_Y;    }

		//! Constructor with parameters
		inline Line(const string & name, const Vector3 & _point_start, const Vector3 & _point_end)
			: SkinnedObject(name)
		{   point_start = _point_start; point_end = _point_end; }

		//! Get the starting point of line
		inline const Vector3 & getStartPoint() const { return point_start; }

		//! Get the ending point of line
		inline const Vector3 & getEndPoint() const { return point_end; }

		//! Set the starting point of line
		inline Vector3 & setStartPoint(const Vector3 & new_point) { return point_start = new_point; }

		//! Set the ending point of line
		inline Vector3 & setEndPoint(const Vector3 & new_point) { return point_end = new_point; }
	};

	//! Primitive object Circle (also ellipsis)
	/**
	 * It will create a circle or ellipsis depending the parameters. The object
	 * will be draw on XY plane and normal vector will look at -Y axis.
	 */
	class Circle : public SkinnedObject
	{
	protected:
		Real x_radius, y_radius;
		int slices;

		/**
		 * @todo Optimize this for fuck shake!
		 */
		virtual void drawObject(bool bSolid)
		{   Real slice_theta = math::DOUBLE_PI / slices;
			Real theta = 0, x_tex_factor = 0.5 / x_radius, y_tex_factor = 0.5 / y_radius;
			Vector3 v0, v1, v2;
			Vector2 TexCord, TexCordMiddle(0.5, 0.5);

			// Set normal vector
			glNormal(Vector3::UNIT_Z);

			// 1st is made by triangles
			// Create initial point
			v1.x = (x_radius * math::cos(0.0));
			v1.y = (y_radius * math::sin(0.0));

			glBegin(GL_TRIANGLES);
				for(int i = 1; i <= slices;i++)
				{   theta -= slice_theta;
					v2.x = (x_radius * math::cos(theta));
					v2.y = (y_radius * math::sin(theta));

					// Get tex_cords
					glTexCoord(TexCordMiddle);
					glVertex(v0);

					glTexCoord(Vector2((x_radius + v1.x) * x_tex_factor ,1-((y_radius + v1.y) * y_tex_factor)));
					glVertex(v1);

					glTexCoord(Vector2((x_radius + v2.x) * x_tex_factor ,1-((y_radius + v2.y) * y_tex_factor)));
					glVertex(v2);
					v1 = v2;
				}
			glEnd();
		}

	public:

		//! Default constructor
		inline Circle(const string & name)
			: SkinnedObject(name)
		{
			slices = 20;
			x_radius = y_radius = 1;
		}

		//! Construct a circle
		inline Circle(const string & name, Real _radius, int _slices)
			: SkinnedObject(name)
		{
			slices = _slices;
			x_radius = y_radius = _radius;
		}

		//! Construct an ellipsis
		inline Circle(const string & name, Real _x_radius, Real _y_radius, int _slices)
			: SkinnedObject(name)
		{
			slices = _slices;
			x_radius = _x_radius;
			y_radius = _y_radius;
		}

		//! Set same radius on two axis
		inline Real setRadius(Real _radius) {  return x_radius = y_radius = _radius; }

		//! Get radius of X-axis
		inline Real getRadiusOnX() const { return x_radius; }

		//! Get radius of Y-axis
		inline Real getRadiusOnY() const { return y_radius; }

		//! Get slices
		inline int getSlices() const { return slices; }

		//! Set slices
		inline int setSlices(int _slices) { return slices = _slices; }
	};

	//! Primitive object Quad
	/**
	 * A Quad (polygon with 4 sides) with defined points.
	 * Quad has texture coordinates respecting the order of points like this
	 *  +----+
	 *  |0  1|
	 *  |    |
	 *  |3  2|
	 *  +----+
	 */
	class Quad : public SkinnedObject
	{
	protected:
		Vector3 points[4];

		inline virtual void drawObject(bool bSolid)
		{
			glBegin(GL_POLYGON);
				glTexCoord2f(0,0);
				glVertex(points[0]);
				glTexCoord2f(1,0);
				glVertex(points[1]);
				glTexCoord2f(1,1);
				glVertex(points[2]);
				glTexCoord2f(0,1);
				glVertex(points[3]);
			glEnd();
		}

	public:

		//! Constructor with default values
		inline Quad(const string & name)
			: SkinnedObject(name)
		{
			points[0] = Vector3(-0.5, 0.5, 0);
			points[1] = Vector3(0.5, 0.5, 0);
			points[2] = Vector3(0.5, -0.5, 0);
			points[3] = Vector3(-0.5, -0.5, 0);
		}

		//! Constructor with parameters
		inline Quad(const string & name, const Vector3 & _p0, const Vector3 & _p1, const Vector3 & _p2, const Vector3 & _p3)
			: SkinnedObject(name)
		{   points[0] = _p0; points[1] = _p1; points[2] = _p2; points[3] =_p3;  }

		//! Get coordinates of a point
		inline const Vector3 & getPoint(int mem) const
		{   return points[mem];   }

		//! Set coordinates of a point
		inline Vector3 & getPoint(int mem, const Vector3 & np)
		{   return points[mem] = np;   }
	};

	//! Primitive object Quad
	/**
	 * OrthoQuad is like quad but it will constrain points in way
	 * that it will always results an orthogonal quad. You can
	 * parameterize OrthoQuad by setting its height and width.
	 */
	class OrthoQuad : public Quad
	{

	public:

		//! Constructor with default values
		inline OrthoQuad(const string & name)
			: Quad(name)
		{    }

		//! Constructor with parameters
		inline OrthoQuad(const string & name, Real _height, Real _width)
			: Quad(name)
		{   setWidth(_width); setHeight(_height); }

		//! Set width
		inline void setWidth(Real w)
		{   Real hw = w/2; points[0].x = -hw; points[3].x = -hw; points[1].x = -hw; points[2].x = hw;    }

		//! Set Height
		inline void setHeight(Real h)
		{   Real hh = h/2; points[0].y = hh; points[1].y = hh; points[2].y = -hh; points[3].y = -hh;    }
	};
}
#endif // PRIMATIVESHAPES_H_INCLUDED
