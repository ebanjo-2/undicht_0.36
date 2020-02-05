#ifndef GLFW_WINDOW_H_INCLUDED
#define GLFW_WINDOW_H_INCLUDED

#include <GLFW/glfw3.h>
#include <window/window.h>


namespace undicht {

    namespace window {

        namespace glfw {

            class Window : public implementation::Window {

                public:
                    int m_width = 800;
                    int m_height = 600;
                    std::string m_title = "Window";

                    bool m_cursor_visible = true;

                    GLFWwindow* m_window = 0;

                public:

                    Window();
                    virtual ~Window();

                    virtual void open();
                    virtual void open(int width, int height, const std::string& title);
                    virtual void close();
                    virtual void update();
                    virtual bool shouldClose();


                    virtual void setSize(int width, int height);
                    virtual void getSize(int& width, int& height);
                    virtual void setTitle(const std::string& title);
                    virtual void setWindowMode(bool fullscreen, bool windowed);
                    virtual void setCursorVisible(bool visible);
                    virtual bool getCursorVisible();



            };

        }

    } // window

} // undicht



#endif // GLFW_WINDOW_H_INCLUDED
