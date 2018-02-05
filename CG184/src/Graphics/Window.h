#pragma once
//
// Created by Suraj Subudhi on 08-Sep-17.
//

#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <memory>

namespace CG184 
{

    class Window 
    {

    public:
        Window();
        Window(int width, int height, const char* name);

        //void			ProcessInput();
        int				IfWindowClosed();
        void			Update();
        void			Close();
        void			SetBGColor(float _r, float _g, float _b, float _a);
        
        ~Window();

    private:
        void init();

    public:
        int				m_width;
        int				m_height;
        const char*		m_WindowTitle;
        GLFWwindow*		m_WindowPtr;
    };

    typedef std::shared_ptr<Window> WindowPtr;
}   // End of CG184

