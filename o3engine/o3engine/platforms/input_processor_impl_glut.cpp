#include "./input_processor.hpp"
#include "./platform.hpp"

namespace o3engine
{
    class InputProcessor::impl
    {
	public:
        static void _func_mouse(int button, int state, int x, int inv_y)
        {
            // Get variables
            InputProcessor * p_ip =(InputProcessor * )InputProcessor::getSingletonPtr();
            MouseState & mst = p_ip->m_mouse_state;
            E_MS_BUTTONS my_but;
            E_MS_BUTTON_STATES my_action;
            int y = Platform::getSingleton().getWindowHeight() - inv_y - 1;

            // Button event
            // Translate to local enumerations
            switch(button)
            {
            case GLUT_LEFT_BUTTON:
                my_but = MS_BUTTON_LEFT;
                break;
            case GLUT_MIDDLE_BUTTON:
                my_but = MS_BUTTON_MIDDLE;
                break;
            case GLUT_RIGHT_BUTTON:
                my_but = MS_BUTTON_RIGHT;
                break;

            /***************************************
             !!!! Work around for mouse wheel
             */
            case GLUT_RIGHT_BUTTON+1:
                my_but = MS_BUTTON_WHEELUP;
                break;
            case GLUT_RIGHT_BUTTON+2:
                my_but = MS_BUTTON_WHEELDOWN;
                break;
            default:
                // Default button is assing to left
                my_but = MS_BUTTON_LEFT;
                break;
            }

            switch (state)
            {
            case GLUT_UP:
                my_action = MS_BUTTON_UP;
                break;
            case GLUT_DOWN:
                my_action = MS_BUTTON_DOWN;
                break;
            default:
                // Default action is assigned to down
                my_action = MS_BUTTON_DOWN;
                break;
            }

            if (mst.m_button_state[my_but] != my_action)
            {
                mst.m_button_state[my_but] = my_action;
                if (my_action == MS_BUTTON_UP)
                    p_ip->raiseMouseButtonReleased(my_but);
                else
                    p_ip->raiseMouseButtonPressed(my_but);
            }

            // Process mouse move
            p_ip->raiseMouseMoved(x,y);

        }

        // Call-back function for mouse motion
        static void _func_motion(int x,int inv_y)
        {	InputProcessor * p_ip =(InputProcessor * )InputProcessor::getSingletonPtr();
            int y = Platform::getSingleton().getWindowHeight() - inv_y - 1;

            // Process mouse move
            p_ip->raiseMouseMoved(x,y);
        }

        // Call-back function for keyboard down actions
        static void _func_keyb_down(unsigned  char key, int x, int inv_y)
        {	InputProcessor * p_ip = (InputProcessor * )InputProcessor::getSingletonPtr();
            E_KB_VIRTUALKEYS VtKey = _ascii2vt(key);
            int y = Platform::getSingleton().getWindowHeight() - inv_y - 1;

            // Process mouse move
            p_ip->raiseMouseMoved(x,y);

            // Save in buffer key
            p_ip->mv_key_state[VtKey] = true;

            // Process character effect
            p_ip->raiseKeyboardPressed(VtKey);
        }

        // Call-back function for keyboard up actions
        static void _func_keyb_up(unsigned  char key, int x, int inv_y)
        {	InputProcessor * p_ip = (InputProcessor * )InputProcessor::getSingletonPtr();
            E_KB_VIRTUALKEYS VtKey = _ascii2vt(key);
            int y = Platform::getSingleton().getWindowHeight() - inv_y - 1;

            // Process mouse move
            p_ip->raiseMouseMoved(x,y);

            // Avoid system exposing 2 releases
            if (!p_ip->mv_key_state[VtKey])  return;

            // Save in buffer key
            p_ip->mv_key_state[VtKey] = false;

            // Process keyboard effect
            p_ip->raiseKeyboardCharInsert(key);
            p_ip->raiseKeyboardReleased(VtKey);
        }

        // Call-back function for special keys pressed
        static void _func_keyb_special_down(int gvt, int x, int inv_y)
        {	InputProcessor * p_ip = (InputProcessor * )InputProcessor::getSingletonPtr();
            E_KB_VIRTUALKEYS VtKey = _glutvt2vt(gvt);
            int y = Platform::getSingleton().getWindowHeight() - inv_y - 1;

            // Process mouse move
            p_ip->raiseMouseMoved(x,y);

            // Save in buffer key
            p_ip->mv_key_state[VtKey] = true;

            // Process character effect
            p_ip->raiseKeyboardPressed(VtKey);
        }

        // Call-back function for special keys release
        static void _func_keyb_special_up(int gvt, int x, int inv_y)
        {	InputProcessor * p_ip = (InputProcessor * )InputProcessor::getSingletonPtr();
            E_KB_VIRTUALKEYS VtKey = _glutvt2vt(gvt);
            int y = Platform::getSingleton().getWindowHeight() - inv_y - 1;

            // Process mouse move
            p_ip->raiseMouseMoved(x,y);

            // Avoid system exposing 2 releases
            if (!p_ip->mv_key_state[VtKey]) return;

            // Save in buffer key
            p_ip->mv_key_state[VtKey] = false;

            // Process keyboard effect
            p_ip->raiseKeyboardReleased(VtKey);
        }

        // Convertor from ascii to VT
        static E_KB_VIRTUALKEYS _ascii2vt(unsigned char asc)
        {
            // Fast select for small letter
            if ((asc >= 'a') && (asc <= 'z'))
                return (E_KB_VIRTUALKEYS)((int)KB_VTKEY_A + (asc - 'a'));

            // Fast select for big letter
            if ((asc >= 'A') && (asc <= 'Z'))
                return (E_KB_VIRTUALKEYS)((int)KB_VTKEY_A + (asc - 'A'));

            // Fast select for big letter
            if ((asc >= '0') && (asc <= '9'))
                return (E_KB_VIRTUALKEYS)((int)KB_VTKEY_0 + (asc - '0'));

            // Special
            switch(asc)
            {
            case 27:
                return KB_VTKEY_ESC;
            case ' ':
                return KB_VTKEY_SPACE;
            case '_':
            case '-':
                return KB_VTKEY_MINUS;
            case '=':
            case '+':
                return KB_VTKEY_PLUS;
            case '\t':
                return KB_VTKEY_TAB;
            case 13:
                return KB_VTKEY_ENTER;
            }
            // Invalid
            printf("GlutInput: Unmapped Ascii Character (0x%X - %02d)\n", asc, asc);
            return KB_VTKEY_UNKNOWN;
        }

        // Convertor from glutvt to VT
        static E_KB_VIRTUALKEYS _glutvt2vt(int gvt)
        {
            switch(gvt)
            {
            case GLUT_KEY_DOWN:
                return KB_VTKEY_DOWN;
            case GLUT_KEY_UP:
                return KB_VTKEY_UP;
            case GLUT_KEY_LEFT:
                return KB_VTKEY_LEFT;
            case GLUT_KEY_RIGHT:
                return KB_VTKEY_RIGHT;
            case GLUT_KEY_HOME:
                return KB_VTKEY_HOME;
            case GLUT_KEY_END:
                return KB_VTKEY_END;
            case GLUT_KEY_PAGE_UP:
                return KB_VTKEY_PGUP;
            case GLUT_KEY_PAGE_DOWN:
                return KB_VTKEY_PGDOWN;
            case GLUT_KEY_F1:
                return KB_VTKEY_FN1;
            case GLUT_KEY_F2:
                return KB_VTKEY_FN2;
            case GLUT_KEY_F3:
                return KB_VTKEY_FN3;
            case GLUT_KEY_F4:
                return KB_VTKEY_FN4;
            case GLUT_KEY_F5:
                return KB_VTKEY_FN5;
            case GLUT_KEY_F6:
                return KB_VTKEY_FN6;
            case GLUT_KEY_F7:
                return KB_VTKEY_FN7;
            case GLUT_KEY_F8:
                return KB_VTKEY_FN8;
            case GLUT_KEY_F9:
                return KB_VTKEY_FN9;
            case GLUT_KEY_F10:
                return KB_VTKEY_FN10;
            case GLUT_KEY_F11:
                return KB_VTKEY_FN11;
            case GLUT_KEY_F12:
                return KB_VTKEY_FN12;
            }
            // Invalid
            return KB_VTKEY_UNKNOWN;
        }
    };

    // Start capturing
    void InputProcessor::startCapture()
    {
        glutIgnoreKeyRepeat(1);      // Ignore key repeat
        glutMouseFunc(impl::_func_mouse);
        glutPassiveMotionFunc(impl::_func_motion);
        glutMotionFunc(impl::_func_motion);
        glutKeyboardFunc(impl::_func_keyb_down);
        glutKeyboardUpFunc(impl::_func_keyb_up);
        glutSpecialFunc(impl::_func_keyb_special_down);
        glutSpecialUpFunc(impl::_func_keyb_special_up);
    }
}
