#pragma once
//
// Created by Suraj Subudhi on 08-Sep-17.
//

#include <GLFW/glfw3.h>
#include <string>
#include <iostream>
#include <memory>

namespace CG184 {

	class Window {

	public:
		Window();
		Window(int width, int height, const char* name);

		//void ProcessInput();
		void Update();
		int IfWindowClosed();
		void Close();

		void SetBGColor(float _r, float _g, float _b, float _a);

		~Window();

	private:
		void init();

	public:
		int m_width;
		int m_height;
		const char* m_WindowTitle;
		GLFWwindow* window;
	};

    typedef std::shared_ptr<Window> WindowPtr;
}

