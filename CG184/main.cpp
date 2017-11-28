#include <GL/glew.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "src/Graphics/Window.h"
#include "src/Graphics/Shader.h"
#include "src/Graphics/Renderer.h"

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

Vector3D lightPos(1.2f, 1.0f, 2.0f);

int main()
{

	auto *window = new Window(SCR_WIDTH, SCR_HEIGHT, "Basic Window");
	eventsystem::Input input(window);
	

	glfwSetCursorPosCallback(window->window, mouse_callback);
	glfwSetScrollCallback(window->window, scroll_callback);
	// tell GLFW to capture our mouse
	glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);



	//float vertices[] = {
	//	// positions          // colors           // texture coords
	//	 0.5f,  0.5f,  0.5f,   1.0f, 0.5f, 0.31f,   1.0f, 1.0f, // top right			//0
	//	 0.5f, -0.5f,  0.5f,   1.0f, 0.5f, 0.31f,   1.0f, 0.0f, // bottom right		//1
	//	-0.5f, -0.5f,  0.5f,   1.0f, 0.5f, 0.31f,   0.0f, 0.0f, // bottom left		//2
	//	-0.5f,  0.5f,  0.5f,   1.0f, 0.5f, 0.31f,   0.0f, 1.0f,  // top left			//3
	//						   
	//	 0.5f,  0.5f, -0.5f,   1.0f, 0.5f, 0.31f,   1.0f, 1.0f, // top right			//4
	//	 0.5f, -0.5f, -0.5f,   1.0f, 0.5f, 0.31f,   1.0f, 0.0f, // bottom right		//5
	//	-0.5f, -0.5f, -0.5f,   1.0f, 0.5f, 0.31f,   0.0f, 0.0f, // bottom left		//6
	//	-0.5f,  0.5f, -0.5f,   1.0f, 0.5f, 0.31f,   0.0f, 1.0f,  // top left			//7
	//};

	
	float vertices[] = {
		-0.5f, -0.5f, -0.5f,   1.0f, 0.0f,  0.0f,    0.0f,  0.0f, -1.0f,    1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   0.0f, 0.5f, 0.31f,    0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 0.5f, 0.31f,    0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 0.5f, 0.31f,    0.0f,  0.0f, -1.0f,    0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.31f,    0.0f,  0.0f, -1.0f,    1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   1.0f, 0.5f, 0.31f,    0.0f,  0.0f, -1.0f,    1.0f, 1.0f,

		-0.5f, -0.5f,  0.5f,   1.0f, 0.5f, 0.31f,    0.0f,  0.0f,  1.0f,    1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.5f, 0.31f,    0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.5f, 1.0f,    0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.5f, 0.31f,    0.0f,  0.0f,  1.0f,    0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.31f,    0.0f,  0.0f,  1.0f,    1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,   1.0f, 0.5f, 0.31f,    0.0f,  0.0f,  1.0f,    1.0f, 1.0f,

		-0.5f,  0.5f,  0.5f,   1.0f, 0.5f, 0.31f,   -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,   1.0f, 0.5f, 0.31f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.31f,   -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   1.0f, 0.5f, 0.31f,   -1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,   1.0f, 0.5f, 0.31f,   -1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   1.0f, 0.5f, 0.31f,   -1.0f,  0.0f,  0.0f,    1.0f, 1.0f,

		 0.5f,  0.5f,  0.5f,   1.0f, 0.5f, 0.31f,    1.0f,  0.0f,  0.0f,    1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 0.5f, 0.31f,    1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   1.0f, 0.5f, 0.31f,    1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,   1.0f, 0.5f, 0.31f,    1.0f,  0.0f,  0.0f,    0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.5f, 0.31f,    1.0f,  0.0f,  0.0f,    1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.5f, 0.31f,    1.0f,  0.0f,  0.0f,    1.0f, 1.0f,

		-0.5f, -0.5f, -0.5f,   1.0f, 0.5f, 0.31f,    0.0f, -1.0f,  0.0f,    1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,   1.0f, 0.5f, 0.31f,    0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.5f, 0.31f,    0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,   1.0f, 0.5f, 0.31f,    0.0f, -1.0f,  0.0f,    0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,   1.0f, 0.5f, 0.31f,    0.0f, -1.0f,  0.0f,    1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,   1.0f, 0.5f, 0.31f,    0.0f, -1.0f,  0.0f,    1.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,   1.0f, 0.5f, 0.31f,    0.0f,  1.0f,  0.0f,    1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,   1.0f, 0.5f, 0.31f,    0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.5f, 0.31f,    0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,   1.0f, 0.5f, 0.31f,    0.0f,  1.0f,  0.0f,    0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,   1.0f, 0.5f, 0.31f,    0.0f,  1.0f,  0.0f,    1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,   1.0f, 0.5f, 0.31f,    0.0f,  1.0f,  0.0f,    1.0f, 1.0f
	};


	std::vector<float> v(vertices, vertices + sizeof vertices / sizeof vertices[0]);

	//GLuint indices[] = {
	//	2, 1, 0, // first triangle
	//	0, 3, 2, // second triangle

	//	4, 0, 1,
	//	1, 5, 4,

	//	6, 7, 4,
	//	4, 5, 6,

	//	3, 7, 6,
	//	6, 2, 3,

	//	0, 4, 7,
	//	7, 3, 0,

	//	1, 5, 6,
	//	6, 2, 1
	//};

	GLuint indices[] = {
		0, 1, 2, // first triangle
		3, 4, 5, // second triangle

		6, 7, 8,
		9, 10, 11,

		12, 13, 14,
		15, 16, 17,

		18, 19, 20,
		21, 22, 23,

		24, 25, 26,
		27, 28, 29,

		30, 31, 32,
		33, 34, 35
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

	Shader ourShader("TestShaders/BoxSolid.vs", "TestShaders/BoxSolid.fs");
	Shader lightBoxShader("TestShaders/LightCube.vs", "TestShaders/LightCube.fs");
	
	std::vector<Renderer>renderer_list;
	renderer_list.reserve(10);

	Renderer renderer1(v, ind);
	Renderer lightBox(v, ind);

	for (int i = 0; i < 10; i++) 
	{
		renderer_list.push_back(renderer1);
	}

	ourShader.AddTexture("Resources/textures/container.jpg", TextureType::Diffuse);
	//ourShader.AddTexture("Resources/textures/awesomeface.png", TextureType::Specular);


	GLint modelLoc				= glGetUniformLocation(ourShader.shaderID, "model");
	GLint viewLoc				= glGetUniformLocation(ourShader.shaderID, "view");
	GLint projectionLoc		    = glGetUniformLocation(ourShader.shaderID, "projection");
	GLint posLightLoc			= glGetUniformLocation(ourShader.shaderID, "lightPos");
	GLint colorLightLoc		    = glGetUniformLocation(ourShader.shaderID, "lightColor");
	GLint viewerPosLoc			= glGetUniformLocation(ourShader.shaderID, "viewPos");


	ourShader.ActivateShader();
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, cam.GetProjectionMatrix().elements);
	ourShader.DeactivateShader();
	

	GLint modeLightlLoc		    = glGetUniformLocation(lightBoxShader.shaderID, "model");
	GLint viewLightLoc			= glGetUniformLocation(lightBoxShader.shaderID, "view");
	GLint projectionLightLoc	= glGetUniformLocation(lightBoxShader.shaderID, "projection");
	lightBoxShader.ActivateShader();
	glUniformMatrix4fv(projectionLightLoc, 1, GL_FALSE, cam.GetProjectionMatrix().elements);
	lightBoxShader.DeactivateShader();


	while (!window->IfWindowClosed())
	{
        // time handle
        auto currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

		KeyBoardEvents(window, input);

		window->SetBGColor(0.0f, 0.0f, 0.0f, 1.0f);
		
		cam.SetFOV(fov);
		cam.Set(cameraPos, cameraFront, cameraUp);
		Matrix4D model(1.0);
		//model = Matrix4D::Translate(model, cubePositions[1].x, cubePositions[1].y, cubePositions[1].z);
		
		ourShader.ActivateShader();
		glUniform3f(colorLightLoc, 1.0f, 1.0f, 1.0f);
		glUniform3f(viewerPosLoc, cam.GetCamPos().x, cam.GetCamPos().y, cam.GetCamPos().z);
		glUniform3f(posLightLoc, lightPos.x, lightPos.y, lightPos.z);

		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, cam.GetViewMatrix().elements);
		glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.elements);
		
		renderer1.Render();
		ourShader.DeactivateShader();
		
		model = Matrix4D(1.0);
		model = Matrix4D::Translate(model, lightPos.x, lightPos.y, lightPos.z);
		model = Matrix4D::Scale(model, 0.2f, 0.2f, 0.2f);
		lightBoxShader.ActivateShader();
		glUniformMatrix4fv(viewLightLoc, 1, GL_FALSE, cam.GetViewMatrix().elements);
		glUniformMatrix4fv(modeLightlLoc, 1, GL_FALSE, model.elements);

        lightBox.Render();
        lightBoxShader.DeactivateShader();


		window->Update();
	}

	delete window;
	return 0;
}



void KeyBoardEvents(Window* window, eventsystem::Input input) 
{
	if (input.KeyPressed(GLFW_KEY_ESCAPE))
		window->Close();

	auto cameraSpeed = (float)(2.5 * deltaTime);
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
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	auto xoffset = (float)(xpos - lastX);
	auto yoffset = (float)(lastY - ypos); // reversed since y-coordinates go from bottom to top
	lastX = (float)(xpos);
	lastY = (float)(ypos);

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
	front.x = (float)(cos(glm::radians(yaw)) * cos(glm::radians(pitch)));
	front.y = (float)(sin(glm::radians(pitch)));
	front.z = (float)(sin(glm::radians(yaw)) * cos(glm::radians(pitch)));
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