#ifndef WINDOW_H_INCLUDED
#define WINDOW_H_INCLUDED

#include <core/shared_lib.h>
#include <window/window_lib.h>
#include <functional>


namespace undicht {

    namespace window {

        SHARED_LIB_DECL_BASE_CLASS(Window, WindowBase, createWindow, copyWindow, deleteWindow);

        SHARED_LIB_CLASS( class Window : public WindowBase {
        public:

            Window();
            virtual ~Window();

            /** opens the window */
            virtual void open();

            virtual void open(int width, int height, const std::string& title);

            virtual void close();

            virtual void update();

            /** \return whether a close was requested by the user */
            virtual bool shouldClose();

            virtual void setSize(int width, int height);

            virtual void getSize(int& width, int& height);

            virtual void setTitle(const std::string& title);

            virtual void setWindowMode(bool fullscreen, bool windowed);

            virtual void setCursorVisible(bool visible);

            virtual bool getCursorVisible();

        };)




    } // window

} // undicht



#endif // WINDOW_H_INCLUDED
