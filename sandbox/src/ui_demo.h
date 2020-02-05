#ifndef UI_DEMO_H
#define UI_DEMO_H

#include <window/window.h>
#include <window/key_input_watcher.h>
#include <window/mouse_input_watcher.h>

#include <UI/ui_elements/button.h>
#include <UI/ui_input_master.h>
#include <UI/ui_renderer.h>
#include <UI/font.h>


namespace undicht {


class UIDemo
{
    public:

        window::KeyInputWatcher m_key_input;
        window::MouseInputWatcher m_mouse_input;

    public:
        // ui elements

        Font m_font;

        UIInputMaster m_ui_master;
        UIRenderer m_renderer;

        Button m_button;
        Button m_button_2;


    public:

        void update();
        void draw();

        UIDemo(window::Window* window);
        virtual ~UIDemo();

};

} // undicht

#endif // UI_DEMO_H
