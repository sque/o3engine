#include "./overlay.hpp"

namespace o3engine
{
	// Overlay constructor
	Overlay::Overlay(Overlay * parent, const Vector2 & pos, const Vector2 & size, E_COORD_TYPE coord_type)
		:m_pos(pos),
		m_coord_system(coord_type),
		mp_parent(parent),
		m_handle_input_events(false),
		m_input_transperant(false)
	{
		setSize(size);
		m_visible = true;

		// Create GLU quadric
		mp_quadric = gluNewQuadric();

		// Register to father
		if (mp_parent)
		{
			mp_parent->mv_childs.push_back(this);
			myIterator = mp_parent->mv_childs.end();
			myIterator--;
		}
	}

	Overlay::~Overlay()
	{	ChildIterator it;
		gluDeleteQuadric(mp_quadric);

		// Unregister
		if (mp_parent)
			mp_parent->mv_childs.erase(myIterator);

		// Delete all childs
		for(it = mv_childs.begin();it != mv_childs.end(); it++)
			delete (*it);
	}

	void Overlay::renderOverlay(const Vector2 & abs_size)
	{	ChildIterator it;
		Overlay * p_child;

		// Draw this overlay
		onDrawOverlay();

		// Calculate coordinate translation
		Vector2 uni_to_abs(1.0/abs_size.x, 1.0/(Real)abs_size.y);
		Vector2 abs_to_uni(abs_size);


		// Draw childs
		for(it = mv_childs.begin();it != mv_childs.end(); it++)
		{	p_child = *it;

			// Skip invisible overlays
			if (!p_child->m_visible)
				continue;

			// UNIFORM CHILD
			if (p_child->m_coord_system == COORD_TYPE_UNIFORM)
			{	Vector2 child_scaled_size(abs_size);
				child_scaled_size *= p_child->m_size;

				if (m_coord_system == COORD_TYPE_UNIFORM)
				{	// Uniform -> Uniform no change is needed
					glTranslate(p_child->m_pos);
					glScale(p_child->m_size);
					p_child->renderOverlay(child_scaled_size);
					glScale(p_child->m_inverted_size);
					glTranslate(p_child->m_pos.opposite());
				}
				else
				{	// Absolute -> Uniform
					glScale(abs_to_uni);

					glTranslate(p_child->m_pos);
					glScale(p_child->m_size);
					p_child->renderOverlay(child_scaled_size);
					glScale(p_child->m_inverted_size);
					glTranslate(p_child->m_pos.opposite());

					glScale(uni_to_abs);
				}
			}
			else
			// ABSOLUTE CHILD
			{
				if (m_coord_system == COORD_TYPE_ABSOLUTE)
				{	// Absolute -> Absolute no change is needed
					glTranslate(p_child->m_pos);
					p_child->renderOverlay(p_child->m_size);
					glTranslate(p_child->m_pos.opposite());
				}
				else
				{	// Uniform -> Absolute
					glScale(uni_to_abs);

					glTranslate(p_child->m_pos);
					p_child->renderOverlay(p_child->m_size);
					glTranslate(p_child->m_pos.opposite());

					glScale(abs_to_uni);

				}
			}
		}
	}

	void Overlay::setSize(const Vector2 & v2_size)
	{
		m_size = v2_size;
		m_inverted_size = Vector2(1.0 / m_size.x, 1.0 / m_size.y);
	}

	void Overlay::setPosition(const Vector2 & v2_pos)
	{	m_pos = v2_pos;	}

	// Translate at new position
	void Overlay::translate(const Vector2 & v2_trans)
	{	m_pos += v2_trans;	}

	void Overlay::zSendBack()
	{	// Skip unparented overlays
		if (!mp_parent)
			return;

		// Remove it from current position
		mp_parent->mv_childs.erase(myIterator);

		// Add it in front of the rendering pipeline
		mp_parent->mv_childs.push_front(this);
		myIterator = mp_parent->mv_childs.begin();
	}

	void Overlay::zBringFront()
	{	// Skip unparented overlays
		if (!mp_parent)
			return;

		// Remove it from current position
		mp_parent->mv_childs.erase(myIterator);

		// Add it last to the rendering pipeline
		mp_parent->mv_childs.push_back(this);
		myIterator = mp_parent->mv_childs.end();
		myIterator--;
	}

	// Called when render output get resized
	void Overlay::renderOutputResized(int width, int height)
	{	ChildIterator it;

		// Raise our event
		onRenderOutputResize(width, height);

		for(it = mv_childs.begin();it != mv_childs.end();it++)
			(*it)->renderOutputResized(width, height);
	}
}
