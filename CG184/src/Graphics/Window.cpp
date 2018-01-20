//
// Created by Suraj Subudhi on 08-Sep-17.
//

#include <GL/glew.h>
#include "Window.h"

namespace CG184 {

	void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(m_width, m_height, m_WindowTitle, nullptr, nullptr);
		if (window == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			return;
		}
		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        // Initializing OpenGL
        glewExperimental = GL_TRUE;
        GLenum err = glewInit();
        if (GLEW_OK != err)
        {
            std::cout << "Error : " << glewGetErrorString(err) << std::endl;
            return;
        }
        glEnable(GL_DEPTH_TEST);
	}

	int Window::IfWindowClosed()
	{
		return glfwWindowShouldClose(window);
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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::Close()
	{
		// glfw: terminate, clearing all previously allocated GLFW resources.
		// ------------------------------------------------------------------
		glfwSetWindowShouldClose(window, true);
	}

	Window::~Window()
	{
		glfwTerminate();
		window = nullptr;
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