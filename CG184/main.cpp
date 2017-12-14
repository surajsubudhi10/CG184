#include <GL/glew.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "src/Graphics/Window.h"
#include "src/Graphics/Shader.h"

#include "src/EventSystem/Input.h"
#include "src/Camera/Camera.h"

#include "src/Scene/Nodes.h"
#include "src/Geometry/Geometry.h"


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
	//glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    // Light Data
    float LightPosition[] = {
             0.7f,  0.2f,  2.0f,
             2.3f, -3.3f, -4.0f,
            -4.0f,  2.0f, -12.0f
    };

    float LightColor[] = {
            1.0f,   0.0f,   0.0f,
            0.3f,   1.0f,   0.0f,
            0.0f,   0.0f,   1.0f
    };


    Camera cam;
    cam.SetAspectRatio((float)SCR_WIDTH / (float)SCR_HEIGHT);
	cam.SetFOV(fov);

//    Box box(1.0f, 1.0f, 1.0f);
//    Sphere box(1.0f, 20, 20);
//    Circle obj(2, 30);
//    Plane obj(5, 4);

    Box lightMesh;//(vertPos, ind);
    Shader lightShaderTemp("TestShaders/LightCube.vs", "TestShaders/LightCube.fs");
    Material lightMat(lightShaderTemp);
    Renderer lightBox(lightMesh, lightMat);

    Node* light = new Node();
    light->AttachComponent(lightBox);
    light->SetPosition(lightPos.x, lightPos.y, lightPos.z);
    light->SetLocalScale(0.25f, 0.25f, 0.25f);
    //light->SetPosition(0.0, 0.0, 1.0);

    Sphere sphereMesh(1.0, 40, 40);
	sphereMesh.SetColor(Vector3D(0.0f, 1.0f, 0.0f));
    Material sphereMat;
    Renderer renderer1(sphereMesh, sphereMat);

    Node* torus = new Node();
    torus->AttachComponent(renderer1);
    torus->SetLocalEulerAngle(-90.0f, 0.0f, 0.0f);

    Box referenceBoxMesh;
    referenceBoxMesh.SetColor(Vector3D(1.0f, 0.0f, 0.0f));
    Material referenceBoxMaterial;
    Renderer referenceBoxRenderer(referenceBoxMesh, referenceBoxMaterial);

    Node* referenceBox = new Node(); 
    referenceBox->AttachComponent(referenceBoxRenderer);
    referenceBox->SetLocalScale(1.5f, 0.02f, 0.02f);
    referenceBox->SetPosition(0, 1.5f, 0);

	//torus->AddChild(light);
	torus->AddChild(referenceBox);

    Scene rootScene(cam);
	rootScene.AddToScene(torus);
    rootScene.AddToScene(referenceBox);
	rootScene.AddToScene(light);

    //ourShader.AddTexture("Resources/textures/container.jpg", TextureType::Diffuse);
    //ourShader.AddTexture("Resources/textures/awesomeface.png", TextureType::Specular);


    Shader* ourShader = sphereMat.GetShader();
    Shader* referenceBoxShader = referenceBoxMaterial.GetShader();

	float angle = 0;
    while (!window->IfWindowClosed())
	{
        // time handle
        auto currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
		//std::cout << "FPS : " << static_cast<int>(1.0f / deltaTime) << std::endl;

        KeyBoardEvents(window, input);
        window->SetBGColor(0.0f, 0.0f, 0.0f, 1.0f);

        //cam.SetFOV(fov);
        cam.Set(cameraPos, cameraFront, cameraUp);

		angle += deltaTime * 10.0f;
        //torus->SetLocalEulerAngle(angle * 10.0f, 0.0f, 0.0f);
		//light->SetLocalEulerAngle(angle * 20.0f, 0.0f, 0.0f);

        (*ourShader).SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);
        (*ourShader).SetUniform3f("viewPos", cam.GetCamPos().x, cam.GetCamPos().y, cam.GetCamPos().z);
        (*ourShader).SetUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.z);

        (*referenceBoxShader).SetUniform3f("lightColor", 1.0f, 1.0f, 1.0f);
        (*referenceBoxShader).SetUniform3f("viewPos", cam.GetCamPos().x, cam.GetCamPos().y, cam.GetCamPos().z);
        (*referenceBoxShader).SetUniform3f("lightPos", lightPos.x, lightPos.y, lightPos.z);

//        (*ourShader).SetUniform4fArray("lightposnarray[0]", 3, LightPosition);
//        (*ourShader).SetUniform4fArray("lightcolorarray[0]", 3, LightColor);
		
		rootScene.Render();
		window->Update();
	}

	delete torus;
	delete light;
	delete referenceBox;

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

    if (input.KeyPressed(GLFW_KEY_E)){
        Vector3D tempVec = (cameraUp * cameraSpeed);
        cameraPos = cameraPos + tempVec;
    }
    if (input.KeyPressed(GLFW_KEY_Q)){
        Vector3D tempVec = (cameraUp * cameraSpeed);
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