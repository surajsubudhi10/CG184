#include "Input.h"

namespace CG184 
{
	namespace Eventsystem 
	{
		Input::Input(WindowPtr window) : mouseX(0.0), mouseY(0.0)
		{
			m_Window = window;

		}

		bool Input::KeyPressed(std::string key)
		{
			const char c = *key.c_str();
			int keyVal = int(c);
			if (glfwGetKey(m_Window->window, keyVal) == GLFW_PRESS)
				return true;

			return false;
				
		}

		// TODO Temp Function 
		bool Input::KeyPressed(int keyVal)
		{
			if (glfwGetKey(m_Window->window, keyVal) == GLFW_PRESS)
				return true;

			return false;

		}


		bool Input::KeyReleased(std::string key)
		{
			return false;
		}

		bool Input::MouseClicked(std::string key)
		{
			return false;
		}

		void Input::processInput()
		{
			if (glfwGetKey(m_Window->window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
				glfwSetWindowShouldClose(m_Window->window, true);

			/*float cameraSpeed = 2.5 * deltaTime;
			if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
			if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
			if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
			if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;*/

		}

		Input::~Input()
		{
		}
	}
}