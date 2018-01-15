#include "Input.h"

namespace CG184 
{
	namespace Eventsystem 
	{
        Vector2D Input::mousePosition = Vector2D();

        void mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos);

		Input::Input(WindowPtr window) //: mousePosition(Vector2D())
		{
			m_Window = window;
            glfwSetCursorPosCallback(m_Window->window, mouse_cursor_callback);
            glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}

		bool Input::KeyPressed(std::string key)
		{
			const char c = *key.c_str();
			int keyVal = int(c);
            return glfwGetKey(m_Window->window, keyVal) == GLFW_PRESS;

        }

		// TODO Temp Function 
		bool Input::IsKeyPressed(int keyVal)
		{
            return glfwGetKey(m_Window->window, keyVal) == GLFW_PRESS;
        }


		bool Input::KeyReleased(std::string key)
		{
			return false;
		}

		bool Input::IsMouseClicked(int button)
		{
			return (glfwGetMouseButton(m_Window->window, button) == GLFW_PRESS);
		}

		void Input::processInput()
		{
			if (glfwGetKey(m_Window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(m_Window->window, true);
		}

		Input::~Input()
		{
		}


        void mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos)
        {
            double xPos;
            double yPos;
            glfwGetCursorPos(window, &xPos, &yPos);

            Input::mousePosition = Vector2D((float)xPos, (float)yPos);
        }

	}
}