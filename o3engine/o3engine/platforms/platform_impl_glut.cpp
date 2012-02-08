#include "./platform.hpp"
#include "./input_processor.hpp"

namespace o3engine
{
    // Internal implementation of platform
    class Platform::impl
    {
	public:
        string m_window_name;
        int m_window_height;
        int m_window_width;
        int m_window_handle;
        Color m_window_back_color;
        WindowEventsListener * mp_window_listener;

        impl()
            :m_window_name("O3 Engine"),
            m_window_height(240),
            m_window_width(320),
            m_window_back_color(Color::BLACK),
            mp_window_listener(NULL)
        {}

        void glutInitWindowSize()
        {   ::glutInitWindowSize(m_window_width, m_window_height);  }

        void glutCreateWindow()
        {   m_window_handle = ::glutCreateWindow(m_window_name.c_str());    }

        static void glutFuncDisplay()
        {   Platform::getSingleton().pimpl->mp_window_listener->onWindowRepaint();  }

        static void glutFuncIdle()
        {   Platform::getSingleton().pimpl->mp_window_listener->onWindowIdle();  }

        static void glutFuncReshape(int new_width, int new_height)
        {   impl * pimpl = Platform::getSingleton().pimpl;
            int old_width = pimpl->m_window_width;
            int old_height = pimpl->m_window_height;
            pimpl->m_window_width = new_width;
            pimpl->m_window_height = new_height;
            pimpl->mp_window_listener->onWindowResized(
                old_width,
                old_height,
                new_width,
                new_height);
        }
    };

    // Constructor
    Platform::Platform()
        :pimpl(NULL)
    {   pimpl = new impl(); }

    // Destructor
    Platform::~Platform()
    {   if (pimpl)
            delete pimpl;   }

    // Initialization
    bool Platform::init()
    {
        // Create window
        glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_ACCUM);
		pimpl->glutInitWindowSize();
		glutInitWindowPosition(0, 0);
		pimpl->glutCreateWindow();

        // Create timer
        mp_timer = new Timer();
        mp_timer->reset();

        // Create input system
        mp_inputproc = new InputProcessor();

        // Setup Callback functions
		glutReshapeFunc(impl::glutFuncReshape);
		glutDisplayFunc(impl::glutFuncDisplay);
		glutIdleFunc(impl::glutFuncIdle);

        // Setup back colors
		glClearColor(pimpl->m_window_back_color);
		glClearAccum(pimpl->m_window_back_color);

        return true;
    }

    void Platform::setWindowBackColor(const Color & back_color)
	{	glClearColor(pimpl->m_window_back_color = back_color);    }

    // Get the window back color
    const Color & Platform::getWindowBackColor(const Color & color) const
    {   return pimpl->m_window_back_color; }

    // Get the current window title
    const string & Platform::getWindowTitle() const
    {   return pimpl->m_window_name;    }

    // Set the current window title
    void Platform::setWindowTitle(const string & name)
    {   pimpl->m_window_name = name;
        glutSetWindowTitle(pimpl->m_window_name.c_str());
    }

    // Get window height
    int Platform::getWindowHeight() const
    {   return pimpl->m_window_height;  }

    // Get window width
    int Platform::getWindowWidth() const
    {   return pimpl->m_window_width;   }

    // Set window size
    void Platform::setWindowSize(int width, int height)
    {   pimpl->m_window_width = width;
        pimpl->m_window_height = height;
        glutReshapeWindow(pimpl->m_window_width, pimpl->m_window_height);
    }

    // Set/Unset windows events listener
    void Platform::setWindowEventsListener(WindowEventsListener * p_listener)
    {   pimpl->mp_window_listener = p_listener;    }

    // Get the current windows events listener
    WindowEventsListener * Platform::getWindowEventsListener()
    {   return pimpl->mp_window_listener;   }
}
