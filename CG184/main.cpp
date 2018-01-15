#include <GL/glew.h>
#include <iostream>

#include "src/Graphics/Window.h"
#include "src/Graphics/Shader.h"

#include "src/EventSystem/Input.h"
#include "src/Camera/Camera.h"

#include "src/Scene/Nodes.h"
#include "src/Geometry/Geometry.h"
#include "src/Lights/Lights.h"


// settings
const uint32_t SCR_WIDTH = 800;
const uint32_t SCR_HEIGHT = 600;
using namespace CG184;

void KeyBoardEvents(const WindowPtr window, Eventsystem::Input input);
//void MouseEvents(GLFWwindow* window, double xpos, double ypos);
void mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
// stores how much we're seeing of either texture
float mixValue = 0.2f;

// camera
Vector3D cameraPos(0.0f, 0.0f, 3.0f);
Vector3D cameraFront(0.0f, 0.0f, -1.0f);
Vector3D cameraUp(0.0f, 1.0f, 0.0f);

bool firstMouse = false;
float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch = 0.0f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
float fov = 45.0f;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Vector3D lightPos(1.2f, 1.0f, 1.0f);

int main()
{

    WindowPtr window(new Window(SCR_WIDTH, SCR_HEIGHT, "CG184::In Development"));
	Eventsystem::Input input(window);
	

	glfwSetCursorPosCallback(window->window, mouse_cursor_callback);
	glfwSetMouseButtonCallback(window->window, mouse_button_callback);
	glfwSetScrollCallback(window->window, scroll_callback);
	// tell GLFW to capture our mouse
	//glfwSetInputMode(window->window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


    // ####################################### Camera ###############################################

    CameraPtr cam(new Camera());
    cam->SetAspectRatio((float)SCR_WIDTH / (float)SCR_HEIGHT);
	cam->SetFOV(fov);

    // ####################################### Lights ###############################################

    LightPtr pointLight(new PointLight());
    pointLight->SetPosition(Vector4D(lightPos.x, lightPos.y, lightPos.z, 1.0f));
    pointLight->SetAmbientColor(Vector4D(0.7f, 0.7f, 0.7f, 1.0f));

    // ##############################################################################################

	Box boxMesh;
	Shader boxShaderTemp("TestShaders/multipleLights.vs", "TestShaders/multipleLights.fs");
	Material boxMat(&boxShaderTemp);
	boxMat.SetAmbient(Vector4D(0.1f, 0.1f, 0.1f, 1.0f));
	boxMat.SetShininess(100.0f);
    Renderer boxRenderer(&boxMesh, &boxMat);

    NodePtr box(new Node("Box"));
	box->AttachComponent(&boxRenderer);
	//box->SetLocalEulerAngle(-45.0f, 0.0f, 0.0f);
	//box->SetLocalScale(0.5, 0.5, 0.5);
	box->SetPosition(0.0, 0.0, 0.0);



    Scene rootScene(cam);
	rootScene.AddToScene(box);
    rootScene.AddLight(pointLight);


	float angle = 0;
    while (!window->IfWindowClosed())
	{
        // time handle
        auto currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
		angle += deltaTime * 1.0f;
		//std::cout << "FPS : " << static_cast<int>(1.0f / deltaTime) << std::endl;

        KeyBoardEvents(window, input);
        window->SetBGColor(0.0f, 0.0f, 0.0f, 1.0f);

        cam->SetFOV(fov);
        cam->Set(cameraPos, cameraFront, cameraUp);
		//pointLight->SetPosition(Vector4D(sin(angle), lightPos.y - 1.0f, lightPos.z, 1.0));

		rootScene.Render();
		window->Update();
	}

	return 0;
}



void KeyBoardEvents(const WindowPtr window, Eventsystem::Input input)
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

	if (input.KeyPressed(GLFW_KEY_D)) {
		Vector3D tempVec = cameraFront.cross(cameraUp);
		tempVec.normalize();
		tempVec = (tempVec * cameraSpeed);
		cameraPos = cameraPos + tempVec;
	}
}



void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	{
		double xpos, ypos;
		//getting cursor position
		glfwGetCursorPos(window, &xpos, &ypos);
		firstMouse = true;
		//cout << firstMouse << endl;
		//cout << "Cursor Position at (" << xpos << " : " << ypos << ")" << endl;
	}

	if(action == GLFW_RELEASE){
		firstMouse = false;
	}
	
}


void mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (!firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		/*firstMouse = false;*/
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
	front.x = (cos(ToRadian(yaw)) * cos(ToRadian(pitch)));
	front.y = (sin(ToRadian(pitch)));
	front.z = (sin(ToRadian(yaw)) * cos(ToRadian(pitch)));
	cameraFront = front.norm();
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