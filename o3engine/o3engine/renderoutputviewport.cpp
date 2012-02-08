#include "./renderoutputviewport.hpp"
#include "./camera.hpp"

namespace o3engine
{
	// Constructor with parameters of viewport
	RenderOutputViewport::RenderOutputViewport(int width, int height, int left, int bottom)
		: RenderOutput(width, height)
	{
		m_bottom_offset = bottom;
		m_left_offset = left;
	}

	RenderOutputViewport::~RenderOutputViewport()
	{
	}

	void RenderOutputViewport::onWindowResize(int new_width, int new_height)
	{
		// By default make viewport full screen
		setSize(new_width, new_height);

		// Change camera's aspect ratio
		mp_input_camera->setAspectRatio(aspectRatio());
	}

	void RenderOutputViewport::onInputCameraChanged()
	{
		// Change camera's aspect ratio
		mp_input_camera->setAspectRatio(aspectRatio());
	}

	void RenderOutputViewport::onMouseMove(const MouseEvent & e)
	{
	/*	printf("NEW MOVE %3d(%3d) - %3d(%3d)\n", e.ms_mouse_state.m_pos_x, e.m_rel_x, e.ms_mouse_state.m_pos_y, e.m_rel_y);
		printf("   |");
		for(int i = 0;i < MS_BUTTON_MAX;i++)
			printf("%s", (e.ms_mouse_state.m_button_state[i] == MS_BUTTON_DOWN)?"D":"_");
		printf("|\n");
    */
	}

	void RenderOutputViewport::onMouseButtonPressed(const MouseEvent & e)
	{
    /*
		printf("NEW DOWN %3d(%3d) - %3d(%3d) - %d\n", e.ms_mouse_state.m_pos_x, e.m_rel_x, e.ms_mouse_state.m_pos_y, e.m_rel_y, e.m_trigger_button);
        printf("   |");
		for(int i = 0;i < MS_BUTTON_MAX;i++)
			printf("%s", (e.ms_mouse_state.m_button_state[i] == MS_BUTTON_DOWN)?"D":"_");
		printf("|\n");
    */
	}

	void RenderOutputViewport::onMouseButtonReleased(const MouseEvent & e)
	{
    /*
		printf("NEW UP   %3d(%3d) - %3d(%3d) - %d\n", e.ms_mouse_state.m_pos_x, e.m_rel_x, e.ms_mouse_state.m_pos_y, e.m_rel_y, e.m_trigger_button);
		printf("   |");
		for(int i = 0;i < MS_BUTTON_MAX;i++)
			printf("%s", (e.ms_mouse_state.m_button_state[i] == MS_BUTTON_DOWN)?"D":"_");
		printf("|\n");
    */
	}
}
