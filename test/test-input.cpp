
#include <Lunatix/Lunatix.hpp>

const int N = 8;

using namespace LX_Device;
using namespace lx::Event;

void printEvent(const LX_WEvent& event);


int main(int argc, char **argv)
{
    LX_Gamepad g[N];
    LX_GamepadID gid;

    lx::init();
    lx::Log::setDebugMode();

    LX_Win::LX_WindowInfo winfo;
    LX_Win::LX_initWindowInfo(winfo);
    LX_Win::LX_Window w(winfo);

    int pads = numberOfDevices();

    if(pads > 0)
    {
        for(int i = 0; i < pads; i++)
        {
            g[i].open(i);
        }
    }

    for(int j = 0; j < pads; j++)
    {
        if(g[j].isConnected())
        {
            LX_GamepadInfo gi;
            g[j].stat(gi);
            lx::Log::log("%s",gamepadToString(gi).utf8_str());
        }
    }

    bool d = false;
    LX_EventHandler evh;
    LX_UserEvent usr;
    usr.wid = 1;
    usr.code = 42;
    evh.pushUserEvent(usr);

    while(!d)
    {
        while(evh.pollEvent())
        {
            switch(evh.getEventType())
            {
            case LX_EventType::QUIT:
                lx::Log::log("Quit Request");
                d = true;
                break;

            /// ---------------- Keyboard ----------------

            case LX_EventType::KEYUP:
                lx::Log::log("KEYBOARD INPUT");
                lx::Log::log("physical key → %s",stringOfScanCode(evh.getScanCode()).utf8_str());
                lx::Log::log("virtual key  → %s",stringOfKeyCode(evh.getKeyCode()).utf8_str());
                break;

            /// ---------------- Mouse ------------------

            case LX_EventType::MOUSEBUTTONUP:
                lx::Log::log("MOUSE BUTTON INPUT");
                lx::Log::log("window ID → %d",evh.getMouseButton().wid);
                lx::Log::log("button    → %d",evh.getMouseButton().button);
                lx::Log::log("state     → %d",evh.getMouseButton().state);
                lx::Log::log("clicks    → %d",evh.getMouseButton().clicks);
                lx::Log::log("X         → %d",evh.getMouseButton().x);
                lx::Log::log("Y         → %d",evh.getMouseButton().y);
                break;

            /*case LX_EventType::MOUSEMOTION:
                lx::Log::log("MOUSE MOTION INPUT");
                lx::Log::log("window ID  → %d",evh.getMouseMotion().wid);
                lx::Log::log("state → %d %d %d %d %d",
                            evh.getMouseMotion().state[LX_MBIndex(LX_MouseButton::LBUTTON)],
                            evh.getMouseMotion().state[LX_MBIndex(LX_MouseButton::MBUTTON)],
                            evh.getMouseMotion().state[LX_MBIndex(LX_MouseButton::RBUTTON)],
                            evh.getMouseMotion().state[LX_MBIndex(LX_MouseButton::X1)],
                            evh.getMouseMotion().state[LX_MBIndex(LX_MouseButton::X2)]);
                lx::Log::log("X          → %d",evh.getMouseMotion().x);
                lx::Log::log("Y          → %d",evh.getMouseMotion().y);
                lx::Log::log("X relative → %d",evh.getMouseMotion().xrel);
                lx::Log::log("Y relative → %d",evh.getMouseMotion().yrel);
                break;*/

            case LX_EventType::MOUSEWHEEL:
                lx::Log::log("MOUSE WHEEL INPUT");
                lx::Log::log("window ID → %d",evh.getMouseWheel().wid);
                lx::Log::log("X         → %d",evh.getMouseWheel().x);
                lx::Log::log("Y         → %d",evh.getMouseWheel().y);
                break;

            /// ---------------- Gamepad ----------------

            case LX_EventType::CONTROLLERBUTTONUP:
                lx::Log::log("GAMEPAD BUTTON INPUT");
                lx::Log::log("button which → %u",evh.getButton().which);
                lx::Log::log("button → %s",stringOfButton(evh.getButton().value).utf8_str());
                break;

            case LX_EventType::CONTROLLERAXISMOTION:
                if(evh.getAxis().value > 8192 || evh.getAxis().value < -8192)
                {
                    lx::Log::log("GAMEPAD AXIS INPUT");
                    lx::Log::log("move which → %u",evh.getAxis().id);
                    lx::Log::log("move → %s",stringOfAxis(evh.getAxis().axis).utf8_str());
                }
                break;

            case LX_EventType::CONTROLLERDEVICEADDED:
                lx::Log::log("NEW GAMEPAD ADDED");
                gid = evh.getGamepadID();
                lx::Log::log("move which → %u",gid);
                if(!g[gid].isConnected())
                {
                    g[gid].open(gid);
                    if(g[gid].isConnected())
                    {
                        LX_GamepadInfo gi;
                        g[gid].stat(gi);
                        lx::Log::log("%s",gamepadToString(gi).utf8_str());
                    }
                }
                break;

            case LX_EventType::CONTROLLERDEVICEREMOVED:
                lx::Log::log("GAMEPAD REMOVED");
                gid = evh.getGamepadID();
                lx::Log::log("move which → %u",gid);
                g[gid].close();
                break;

            case LX_EventType::WINDOWEVENT:
                lx::Log::log("WINDOW EVENT");
                printEvent(evh.getWindowEvent());
                break;

            /// ---------------- User Event ----------------

            case LX_EventType::USEREVENT:
                lx::Log::log("USER EVENT");
                lx::Log::log("window ID → %d",evh.getUserEvent().wid);
                lx::Log::log("code      → %d",evh.getUserEvent().code);
                break;

            /// ---------------- Drag and drop ----------------

            case LX_EventType::DROPFILE:
                lx::Log::log("DRAG & DROP EVENT");
                lx::Log::log("file → %s",evh.getDropEvent().file.c_str());
                break;

            default:
                break;
            }
        }
        lx::Time::delay(33);
    }

    for(int k = 0; k < N; k++)
    {
        g[k].close();
    }

    lx::quit();
    return 0;
}


void printEvent(const LX_WEvent& event)
{
    switch (event.evid)
    {
    case LX_WinEventType::WIN_SHOWN:
        lx::Log::log("Window %d shown", event.wid);
        break;

    case LX_WinEventType::WIN_HIDDEN:
        lx::Log::log("Window %d hidden", event.wid);
        break;

    case LX_WinEventType::WIN_EXPOSED:
        lx::Log::log("Window %d exposed", event.wid);
        break;

    case LX_WinEventType::WIN_MOVED:
        lx::Log::log("Window %d moved to %d,%d", event.wid, event.data1, event.data2);
        break;

    case LX_WinEventType::WIN_RESIZED:
        lx::Log::log("Window %d resized to %dx%d", event.wid, event.data1, event.data2);
        break;

    case LX_WinEventType::WIN_SIZE_CHANGED:
        lx::Log::log("Window %d size changed to %dx%d", event.wid, event.data1, event.data2);
        break;

    case LX_WinEventType::WIN_MINIMIZED:
        lx::Log::log("Window %d minimized", event.wid);
        break;

    case LX_WinEventType::WIN_MAXIMIZED:
        lx::Log::log("Window %d maximized", event.wid);
        break;

    case LX_WinEventType::WIN_RESTORED:
        lx::Log::log("Window %d restored", event.wid);
        break;

    case LX_WinEventType::WIN_ENTER:
        lx::Log::log("Mouse entered window %d", event.wid);
        break;

    case LX_WinEventType::WIN_LEAVE:
        lx::Log::log("Mouse left window %d", event.wid);
        break;

    case LX_WinEventType::WIN_FOCUS_GAINED:
        lx::Log::log("Window %d gained keyboard focus", event.wid);
        break;

    case LX_WinEventType::WIN_FOCUS_LOST:
        lx::Log::log("Window %d lost keyboard focus", event.wid);
        break;

    case LX_WinEventType::WIN_CLOSE:
        lx::Log::log("Window %d closed", event.wid);
        break;

    default:
        lx::Log::log("Window %d got unknown event %d", event.wid, event.evid);
        break;
    }
}
