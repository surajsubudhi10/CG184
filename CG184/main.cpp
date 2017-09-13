#include <GL\glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include <iostream>

#include "src/Graphics/Window.h"
#include "src/Graphics/Shader.h"
#include "src/Graphics/Renderer.h"

#include "src/Maths/Matrix4D.h"
#include "src/EventSystem/Input.h"
#include "src/Camera/Camera.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
using namespace CG184;

void KeyBoardEvents(Window* window, eventsystem::Input input);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// stores how much we're seeing of either texture
float mixValue = 0.2f;

// camera
Vector3D cameraPos(0.0f, 0.0f, 3.0f);
Vector3D cameraFront(0.0f, 0.0f, -1.0f);
Vector3D cameraUp(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
float fov = 45.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;



int main()
{

	Window *window = new Window(SCR_WIDTH, SCR_HEIGHT, "Basic Window");
	eventsystem::Input input(window);
	

	glfwSetCursorPosCallback(window->window, mouse_callback);
	glfwSetScrollCallback(window->window, scroll_callback);
	// tell GLFW to capture our mouse
	glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "Error : " << glewGetErrorString(err) << std::endl;
		return 0;
	}

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right			//0
		 0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right		//1
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left		//2
		-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top left			//3

		 0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right			//4
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right		//5
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left		//6
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left			//7
	};


	std::vector<float> v(vertices, vertices + sizeof vertices / sizeof vertices[0]);

	GLuint indices[] = {
		2, 1, 0, // first triangle
		0, 3, 2, // second triangle

		4, 0, 1,
		1, 5, 4,

		6, 7, 4,
		4, 5, 6,

		3, 7, 6,
		6, 2, 3,

		0, 4, 7,
		7, 3, 0,

		1, 5, 6,
		6, 2, 1
	};
	std::vector<GLuint> ind(indices, indices + sizeof indices / sizeof indices[0]);

	Vector3D cubePositions[] = {
		Vector3D(0.0f,  0.0f,  0.0f),
		Vector3D(2.0f,  5.0f, -15.0f),
		Vector3D(-1.5f, -2.2f, -2.5f),
		Vector3D(-3.8f, -2.0f, -12.3f),
		Vector3D(2.4f, -0.4f, -3.5f),
		Vector3D(-1.7f,  3.0f, -7.5f),
		Vector3D(1.3f, -2.0f, -2.5f),
		Vector3D(1.5f,  2.0f, -2.5f),
		Vector3D(1.5f,  0.2f, -1.5f),
		Vector3D(-1.3f,  1.0f, -1.5f)
	};

	
	Camera cam;
	cam.SetAspectRatio((float)SCR_WIDTH / (float)SCR_HEIGHT);

	Shader ourShader("TestShaders/coordinate_systems.vs", "TestShaders/coordinate_systems.fs");
	//Shader ourShader("TestShaders/testShader.vs", "TestShaders/testShader.fs");
	std::vector<Renderer>renderer_list;
	renderer_list.reserve(10);
	Renderer renderer1(v, ind);

	for (int i = 0; i < 10; i++) 
	{
		renderer_list.push_back(renderer1);
	}

	ourShader.AddTexture("Resources/textures/container.jpg", TextureType::Diffuse);
	ourShader.AddTexture("Resources/textures/awesomeface.png", TextureType::Specular);
	

	GLuint mixLocationInShader	= glGetUniformLocation(ourShader.shaderID, "mixValue");
	GLuint transformLoc			= glGetUniformLocation(ourShader.shaderID, "transform");
	GLuint modelLoc				= glGetUniformLocation(ourShader.shaderID, "model");
	GLuint viewLoc				= glGetUniformLocation(ourShader.shaderID, "view");
	GLuint projectionLoc		= glGetUniformLocation(ourShader.shaderID, "projection");

	ourShader.ActivateShader();
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, cam.GetProjectionMatrix().elements);
	ourShader.DeactivateShader();
	

	

	while (!window->IfWindowClosed())
	{
		// time handle
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		KeyBoardEvents(window, input);

		window->SetBGColor(0.2f, 0.8, 0.5, 1.0f);
		ourShader.ActivateShader();

		glUniform1f(mixLocationInShader, mixValue);

		cam.SetFOV(fov);
		cam.Set(cameraPos, cameraFront, cameraUp);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, cam.GetViewMatrix().elements);


		for (unsigned int i = 0; i < 10; i++)
		{
			Matrix4D model;
			model = Matrix4D::Translate(model, cubePositions[i].x, cubePositions[i].y, cubePositions[i].z);
			float angle = 20.0f * i;
			model = Matrix4D::Rotate(model, angle, Vector3D(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.elements);

			renderer_list[i].Render();
		}

		ourShader.DeactivateShader();
		window->Update();
	}

	delete window;
	return 0;
}



void KeyBoardEvents(Window* window, eventsystem::Input input) 
{
	if (input.KeyPressed(GLFW_KEY_ESCAPE))
		window->Close();

	float cameraSpeed = 2.5 * deltaTime;
	if (input.KeyPressed(GLFW_KEY_W)) {
		Vector3D tempVec = (cameraFront * cameraSpeed);
		cameraPos = cameraPos + tempVec;
	}
	if (input.KeyPressed(GLFW_KEY_S)) {
		Vector3D tempVec = (cameraFront * cameraSpeed);
		cameraPos = cameraPos - tempVec;
	}
	if (input.KeyPressed(GLFW_KEY_A)){
		Vector3D tempVec = cameraFront.cross(cameraUp);
		tempVec.normalize();
		tempVec = (tempVec * cameraSpeed);
		cameraPos = cameraPos - tempVec;
	}
		//cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (input.KeyPressed(GLFW_KEY_D)) {
		Vector3D tempVec = cameraFront.cross(cameraUp);
		tempVec.normalize();
		tempVec = (tempVec * cameraSpeed);
		cameraPos = cameraPos + tempVec;
	}
		//cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

}


void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	//glm::vec3 front;
	Vector3D front(1.0);
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = front.norm();
	//cameraFront = glm::normalize(front);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (fov >= 1.0f && fov <= 45.0f)
		fov -= yoffset;
	if (fov <= 1.0f)
		fov = 1.0f;
	if (fov >= 45.0f)
		fov = 45.0f;
}