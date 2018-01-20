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

void KeyBoardEvents(const WindowPtr window, Input input);
void MouseEvents(const WindowPtr window, Input input);
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

	glfwSetScrollCallback(window->window, scroll_callback);

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

    NodePtr box(new Node("box1"));
	box->AttachComponent(&boxRenderer);
	box->SetLocalEulerAngle(0.0f, -45.0f, 0.0f);
	box->SetPosition(0.0, 0.0, 0.0);

	Renderer boxRenderer1(&boxMesh, &boxMat);
	boxRenderer1.GetMaterial().SetAmbient(Vector4D(0.3f, 0.1f, 0.1f, 1.0f));

	NodePtr box1(new Node("box2"));
	box1->AttachComponent(&boxRenderer1);
	box1->SetLocalScale(0.5, 0.5, 0.5);
	box1->SetPosition(2.0, 0.0, 0.0);

    Scene rootScene(cam);
	rootScene.AddToScene(box);
	rootScene.AddToScene(box1);
    rootScene.AddLight(pointLight);

	Input input(window, &rootScene);

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
        MouseEvents(window, input);
        window->SetBGColor(0.0f, 0.0f, 0.0f, 1.0f);

        cam->SetFOV(fov);
        cam->Set(cameraPos, cameraFront, cameraUp);

		rootScene.Render();
		window->Update();
	}

	return 0;
}


void KeyBoardEvents(const WindowPtr window, Input input)
{
	if (input.IsKeyPressed(GLFW_KEY_ESCAPE))
		window->Close();

    if(input.IsKeyPressed(GLFW_KEY_SPACE)){
        cameraPos   = Vector3D(0.0f, 0.0f, 3.0f);
        cameraFront = Vector3D(0.0f, 0.0f, -1.0f);
        cameraUp    = Vector3D::Up;
    }

	auto cameraSpeed = (float)(2.5 * deltaTime);
	if (input.IsKeyPressed(GLFW_KEY_W)) {
        Vector3D tempVec = (Vector3D::Forward * cameraSpeed);
		cameraPos = cameraPos - tempVec;
	}
	if (input.IsKeyPressed(GLFW_KEY_S)) {
        Vector3D tempVec = (Vector3D::Forward * cameraSpeed);
		cameraPos = cameraPos + tempVec;
	}
	if (input.IsKeyPressed(GLFW_KEY_A)){
        Vector3D tempVec = (Vector3D::Right * cameraSpeed);
		cameraPos = cameraPos + tempVec;
	}

    if (input.IsKeyPressed(GLFW_KEY_E)){
        Vector3D tempVec = (Vector3D::Up * cameraSpeed);
        cameraPos = cameraPos - tempVec;
    }
    if (input.IsKeyPressed(GLFW_KEY_Q)){
        Vector3D tempVec = (Vector3D::Up * cameraSpeed);
        cameraPos = cameraPos + tempVec;
    }

	if (input.IsKeyPressed(GLFW_KEY_D)) {
        Vector3D tempVec = (Vector3D::Right * cameraSpeed);
		cameraPos = cameraPos - tempVec;
	}
}

void MouseEvents(const WindowPtr window, Input input)
{
    firstMouse = input.IsMouseClicked(GLFW_MOUSE_BUTTON_LEFT);

    if (!firstMouse)
    {
        lastX = input.mousePosition.x;
        lastY = input.mousePosition.y;
    }

    if(input.IsMouseClicked(GLFW_MOUSE_BUTTON_LEFT)) {
        auto xoffset = input.mousePosition.x - lastX;
        auto yoffset = lastY - input.mousePosition.y; // reversed since y-coordinates go from bottom to top
        lastX = (input.mousePosition.x);
        lastY = (input.mousePosition.y);

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

        Vector3D front(1.0);
        front.x = (cos(ToRadian(yaw)) * cos(ToRadian(pitch)));
        front.y = (sin(ToRadian(pitch)));
        front.z = (sin(ToRadian(yaw)) * cos(ToRadian(pitch)));
        cameraFront = front.norm();
    }
//    cout << cameraFront;

	if (input.IsMouseClicked(GLFW_MOUSE_BUTTON_RIGHT)) { input.ProcessSelection(); }
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