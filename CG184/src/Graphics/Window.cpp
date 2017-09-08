//
// Created by Suraj Subudhi on 08-Sep-17.
//

#include "Window.h"

namespace CG184 {

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);
	void processInput(GLFWwindow *window);

	Window::Window()
		: m_width(960), m_height(540), m_WindowTitle("Hello Window!!"), window(nullptr)
	{
		init();
	}

	Window::Window(int width, int height, const char* name)
		: m_width(width), m_height(height), m_WindowTitle(name), window(nullptr)
	{
		init();
	}

	void Window::init()
	{
		// glfw: initialize and configure
		// ------------------------------
		glfwInit();
		//        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		//        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		//        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(m_width, m_height, m_WindowTitle, NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(window);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	}

	int Window::IfWindowClosed()
	{
		return glfwWindowShouldClose(window);
	}

	void Window::ProcessInput()
	{
		// input
		// -----
		processInput(window);
	}

	void Window::Update()
	{
		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void Window::SetBGColor(float _r, float _g, float _b, float _a)
	{
		glClearColor(_r, _g, _b, _a);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Window::Close()
	{
		// glfw: terminate, clearing all previously allocated GLFW resources.
		// ------------------------------------------------------------------
		glfwTerminate();
	}

	Window::~Window()
	{
		window = nullptr;
	}


	void processInput(GLFWwindow *window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);
	}

	// glfw: whenever the window size changed (by OS or user resize) this callback function executes
	// ---------------------------------------------------------------------------------------------
	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		// make sure the viewport matches the new window dimensions; note that width and
		// height will be significantly larger than specified on retina displays.
		glViewport(0, 0, width, height);
	}
}