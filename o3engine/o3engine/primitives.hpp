#ifndef O3ENGINE_PRIMITIVESHAPES_HPP_INCLUDED
#define O3ENGINE_PRIMITIVESHAPES_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./geometry.hpp"
#include "./drawableobject.hpp"

namespace o3engine {

	//! Base class to declare primitive objects
	struct PrimitiveObject: public DrawableObject, public Geometry {

		//! Constructor
		PrimitiveObject(const string & name, Geometry::attributesflags_type attrs = VertexAttributes::position) :
			DrawableObject(name), Geometry(attrs),
			mp_renderer(nullptr){
		}

		//! Inheritable
		virtual ~PrimitiveObject() {
			delete mp_renderer;
		}

		inline virtual void draw() {
			mp_renderer->draw();
		}

	protected:

		//! Update reflection of this object data to GPU
		void updateGPUObjects() {
			if (!mp_renderer)
				mp_renderer = new GeometryRenderer(*this);
			mp_renderer->uploadToGPU();
		}

		//! Renderer that will be used to render geometry
		GeometryRenderer * mp_renderer;

	};

	//! UV Sphere object
	class UVSphere: public PrimitiveObject {
	public:

		//! Default constructor
		/**
		 * Creates a sphere of radius 0.5 with 5 slices and 5 stacks.
		 */
		UVSphere(const string & name);

		//! Constructor with predefined size and resolution
		/**
		 * Creates a sphere with custom size, slices, stacks
		 */
		UVSphere(const string & name, Real radius , size_t slices, size_t stacks);

		//! Get the radius of sphere
		Real getRadius() const {
			return m_radius;
		}

		//! Set the radius o sphere
		void setRadius(Real radius) {
			m_radius = radius;
			buildSphere();
			updateGPUObjects();
		}

		//! Get the slices of sphere
		size_t getSlices() const {
			return m_slices;
		}

		//! Set the slices of sphere
		void setSlices(size_t slices) {
			m_slices = slices;
			buildSphere();
			updateGPUObjects();
		}

		//! Get the stacks of sphere
		size_t getStacks() const {
			return m_stacks;
		}

		//! Set the stacks of sphere
		void setStacks(size_t stacks) {
			m_stacks = stacks;
			buildSphere();
			updateGPUObjects();
		}

	protected:

		//! Sphere radius
		Real m_radius;

		//! UV Slices
		size_t m_slices;

		//! UV Stacks
		size_t m_stacks;

		//! Build sphere
		void buildSphere();

	};

	//! Primitive object Cube
	/**
	 * A Cube object created with GLUT.
	 */
	class Cube: public PrimitiveObject {
	public:

		//! Default Constructor
		Cube(const string & name) :
				PrimitiveObject(name),
				m_size(1){
			buildCube();
			updateGPUObjects();
		}

		//! Construct with predefined size
		Cube(const string & name, Real size) :
				PrimitiveObject(name),
				m_size(size){
			buildCube();
			updateGPUObjects();
		}

		//! Get the size of cube
		Real getSize() const {
			return m_size;
		}

		//! Set the size of cube
		void setSize(Real size) {
			m_size = size;
			buildCube();
			updateGPUObjects();
		}

	protected:

		//! Build cube
		void buildCube();

		//! Size of this cube
		Real m_size;
	};

	//! Primitive object Line
	/**
	 * A Line with a start and end point defined by user.
	 */
	class Line: public PrimitiveObject {
	public:

		//! Constructor with default values
		inline Line(const string & name) :
		PrimitiveObject(name) {
			point_start = Vector3::ZERO;
			point_end = Vector3::UNIT_Y;
		}

		//! Constructor with parameters
		inline Line(const string & name, const Vector3 & _point_start,
				const Vector3 & _point_end) :
				PrimitiveObject(name) {
			point_start = _point_start;
			point_end = _point_end;
		}

		//! Get the starting point of line
		inline const Vector3 & getStartPoint() const {
			return point_start;
		}

		//! Get the ending point of line
		inline const Vector3 & getEndPoint() const {
			return point_end;
		}

		//! Set the starting point of line
		inline Vector3 & setStartPoint(const Vector3 & new_point) {
			return point_start = new_point;
		}

		//! Set the ending point of line
		inline Vector3 & setEndPoint(const Vector3 & new_point) {
			return point_end = new_point;
		}
	protected:
		Vector3 point_start, point_end;
	};

	//! Primitive object Disk (also ellipsis)
	/**
	 * It will create a disk or elliptic disk depending the parameters. The object
	 * will be draw on XY plane and normal vector will look at Z axis.
	 */
	class Disk: public PrimitiveObject {
	public:

		//! Default constructor
		/**
		 * 20 slices and 0.5 x and y radius
		 */
		Disk(const string & name);

		//! Construct a circle
		Disk(const string & name, Real radius, size_t slices);

		//! Construct an ellipsis
		Disk(const string & name, Real xradius, Real yradius, size_t slices);

		//! Set radius on axis
		void setRadius(Real xradius, Real yradius) {
			m_xradius = xradius;
			m_yradius = yradius;
			buildDisk();
			updateGPUObjects();
		}

		//! Get radius of X-axis
		Real getXRadius() const {
			return m_xradius;
		}

		//! Get radius of Y-axis
		Real getRadiusOnY() const {
			return m_xradius;
		}

		//! Get slices
		size_t getSlices() const {
			return m_slices;
		}

		//! Set slices
		void setSlices(int slices) {
			m_slices = slices;
			buildDisk();
			updateGPUObjects();
		}

	protected:
		//! Slices
		size_t m_slices;

		//! Ellipsis radius in x-axis
		Real m_xradius;

		//! Ellipsis radius in y-axis
		Real m_yradius;

		//! Build this disk
		void buildDisk();
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
	class Quad: public PrimitiveObject {
	public:

		//! Constructor with default values
		inline Quad(const string & name) :
			PrimitiveObject(name) {

			m_points[0] = Vector3(-0.5, 0.5, 0);
			m_points[1] = Vector3(0.5, 0.5, 0);
			m_points[2] = Vector3(0.5, -0.5, 0);
			m_points[3] = Vector3(-0.5, -0.5, 0);

			buildQuad();
			updateGPUObjects();
		}

		//! Constructor with parameters
		inline Quad(const string & name, const Vector3 & p0, const Vector3 & p1,
				const Vector3 & p2, const Vector3 & p3) :
				PrimitiveObject(name){
			setPoints(p0, p1, p2, p3);
		}

		//! Get coordinates of a point
		inline const Vector3 & getPoint(size_t point) const {
			return m_points[4];
		}

		//! Set points of this quad
		void setPoints(const Vector3 & p0, const Vector3 & p1,
				const Vector3 & p2, const Vector3 & p3) {
			m_points[0] = p0;
			m_points[1] = p1;
			m_points[2] = p2;
			m_points[3] = p3;

			buildQuad();
			updateGPUObjects();
		}

	protected:

		//! Quad points
		Vector3 m_points[4];

		//! Build quad
		void buildQuad();
	};

	//! Primitive object Quad
	/**
	 * OrthoQuad is like quad but it will constrain points in way
	 * that it will always results an orthogonal quad. You can
	 * parameterize OrthoQuad by setting its height and width.
	 */
	class OrthoQuad: public Quad {
	public:

		//! Constructor with default values
		inline OrthoQuad(const string & name) :
				Quad(name),
				m_width(1),
				m_height(1){
		}

		//! Constructor with parameters
		inline OrthoQuad(const string & name, Real height, Real width) :
				Quad(name, Vector3(-width / 2, height / 2, 0),
						Vector3(width / 2, height / 2, 0),
						Vector3(width / 2, -height / 2, 0),
						Vector3(-width / 2, -height / 2, 0)
				),
				m_width(width),
				m_height(height) {
		}

		//! Get the width of this quad
		Real getWidth() const {
			return m_width;
		}

		//! Get height of this quad
		Real getHeight() const {
			return m_height;
		}
	protected:

		//! Width of quad
		Real m_width;

		//! Height of quad
		Real m_height;
	};
}
#endif
