#ifndef O3ENGINE_OVERLAY_HPP_INCLUDED
#define O3ENGINE_OVERLAY_HPP_INCLUDED

#include "./prereqs.hpp"
#include "./texture.hpp"
#include <list>

namespace o3engine {
	//! Handles an Overlay that displays above 3d-scene
	class Overlay {
	public:
		//! All the available overlay coordinate systems
		enum E_COORD_TYPE {
			COORD_TYPE_UNIFORM, COORD_TYPE_ABSOLUTE
		};

	protected:
		// Child overlays
		typedef list<Overlay *> children_type;
		children_type mv_children;

		Vector2 m_pos; 					//!< Position of overlay
		Vector2 m_size; 				//!< Size of overlay
		Vector2 m_inverted_size; 		//!< Size of overlay inverted (1/size)
		bool m_visible; 				//!< Flag if overlay is visible
		E_COORD_TYPE m_coord_system; 	//!< Our coordinates system
		GLUquadric * mp_quadric; 		//!< Pointer to quadric @todo Remove this quadric!!
		Overlay * mp_parent;			//!< Pointer to parent overlay
		children_type::iterator myIterator; //!< Our position in the list of our parent.
		bool m_handle_input_events; 	//!< Flag if this overlay handles input events for this and childs
		bool m_input_transperant; 		//!< Flag if overlay is input transparent for this and childs

		//! EVENT: Routine called to draw overlay
		virtual void onDrawOverlay() {
		}

		//! EVENT: Routine called when RenderOutput get resized
		virtual void onRenderOutputResize(int width, int height) {
		}

		//! EVENT: Routine called when mouse is moved over overlay
		virtual void onMouseMove(const Vector2 & pos) {
		}

		//! EVENT: Routine called when mouse enter overlay
		virtual void onMouseEnter() {
		}

		//! EVENT: Routine called when mouse leaves overlay
		virtual void onMouseLeave() {
		}

		//! Routine to draw a rectangle with a background color
		inline void drawRectangle(Real left, Real bottom, Real right, Real top,
				const Color & back_color) {
			glColor4(back_color);
			glBegin(GL_POLYGON);
			glVertex2f((GLfloat) left, (GLfloat) bottom);
			glVertex2f((GLfloat) left, (GLfloat) top);
			glVertex2f((GLfloat) right, (GLfloat) top);
			glVertex2f((GLfloat) right, (GLfloat) bottom);
			glEnd();
		}

		//! Routine to draw a rectangle with texture
		inline void drawTexturedRectangle(Real left, Real bottom, Real right,
				Real top, Texture * p_texture, const Color & tex_color) {
			glColor4(tex_color);
			glEnable(GL_TEXTURE_2D);
			p_texture->glBind2d();
			glBegin(GL_POLYGON);

			glTexCoord2f(0.0, 0.0);
			glVertex2f((GLfloat) left, (GLfloat) bottom);
			glTexCoord2f(0.0, 1.0);
			glVertex2f((GLfloat) left, (GLfloat) top);
			glTexCoord2f(1.0, 1.0);
			glVertex2f((GLfloat) right, (GLfloat) top);
			glTexCoord2f(1.0, 0.0);
			glVertex2f((GLfloat) right, (GLfloat) bottom);

			glEnd();
			glDisable(GL_TEXTURE_2D);
		}

		//! Routine to draw a line
		inline void drawLine(Real x1, Real y1, Real x2, Real y2,
				const Color & line_color) {
			glColor4(line_color);
			glBegin(GL_LINES);
			glVertex2f((GLfloat) x1, (GLfloat) y1);
			glVertex2f((GLfloat) x2, (GLfloat) y2);
			glEnd();
		}

		//! Routine to draw a Disc
		inline void drawDisc(Real x, Real y, Real radius, int slices,
				const Color & circle_color) {
			glColor4(circle_color);
			glTranslatef((GLfloat) x, (GLfloat) y, 0.0);
			gluDisk(mp_quadric, 0.0, radius, slices, 1);
			glTranslatef((GLfloat) -x, (GLfloat) -y, 0.0);
		}

	public:

		//! Overlay constructor
		/**
		 * Constructor of a new overlay. An overlay is attached at its parent at the creation time
		 * @param parent A pointer to the overlay that will contain this one
		 * @param pos The position of this overlay inside its parent
		 * @param size The size that will have.
		 * @param coord_type The coordination system that this overlay will follow. Position
		 *  and size are translated accordinally to this parameter.
		 */
		Overlay(Overlay * parent, const Vector2 & pos, const Vector2 & size,
				E_COORD_TYPE coord_type = COORD_TYPE_UNIFORM);

		//! Destructor
		virtual ~Overlay();

		//! Called to render overlay
		void renderOverlay(const Vector2 & abs_size);

		//! Called when render output get resized
		void renderOutputResized(int width, int height);

		//! Set new position
		void setPosition(const Vector2 & v2_pos);

		//! Get position
		inline const Vector2 & getPosition() const {
			return m_pos;
		}

		//! Translate at new position
		void translate(const Vector2 & v2_trans);

		//! Set size of overlay
		void setSize(const Vector2 & v2_size);

		//! Get size of overlay
		inline const Vector2 & getSize() const {
			return m_size;
		}

		//! Set visible
		inline void setVisible(bool visible) {
			m_visible = visible;
		}

		//! Check if is visible
		inline bool isVisible() const {
			return m_visible;
		}

		//! Show overlay (set visible true)
		inline void show() {
			setVisible(true);
		}

		//! Hide overlay (set visible false)
		inline void hide() {
			setVisible(false);
		}

		//! Get coordinate system
		inline E_COORD_TYPE getCoordSystem() {
			return m_coord_system;
		}

		//! Send overlay back to zOrder
		void zSendBack();

		//! Make overlay top-most
		void zBringFront();

		//! Check if handling input events
		inline bool isHandlingInputEvents() {
			return m_handle_input_events;
		}

		//! Set if handling for input events
		inline void setHandlingInputEvents(bool enabled) {
			m_handle_input_events = enabled;
		}
	};
}
#endif
