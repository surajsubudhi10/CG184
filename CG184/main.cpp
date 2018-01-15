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

Vector3D lightPos(1.2f, 1.0f, 1.0f);

int main()
{

    WindowPtr window(new Window(SCR_WIDTH, SCR_HEIGHT, "CG184::In Development"));
	Eventsystem::Input input(window);
	

	glfwSetCursorPosCallback(window->window, mouse_callback);
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
    pointLight->SetAmbientColor(Vector4D(0.2f, 0.2f, 0.2f, 1.0f));

    LightPtr pointLight1(new PointLight());
    pointLight1->SetPosition(Vector4D(lightPos.x + 100.0f, lightPos.y, lightPos.z, 1.0f));
    pointLight1->SetAmbientColor(Vector4D(0.1f, 0.1f, 0.1f, 1.0f));

    LightPtr pointLight2(new PointLight());
    pointLight2->SetPosition(Vector4D(lightPos.x, lightPos.y, lightPos.z - 1.0f, 1.0f));
    pointLight2->SetAmbientColor(Vector4D(0.1f, 0.1f, 0.1f, 1.0f));

    // ##############################################################################################

    Box lightMesh;
    Shader lightShaderTemp("TestShaders/LightCube.vs", "TestShaders/LightCube.fs");
    Material lightMat(&lightShaderTemp);
    Renderer lightBox(&lightMesh, &lightMat);

    NodePtr light(new Node("lightBox"));
    light->AttachComponent(&lightBox);
    light->SetPosition(lightPos.x, lightPos.y, lightPos.z);
    light->SetLocalScale(0.05f, 0.05f, 0.05f);

    //Sphere sphereMesh(1.0, 40, 40);
	Torus sphereMesh(0.5f, 1.0f, 40, 40);
	Shader sphereShaderTemp("TestShaders/multipleLights.vs", "TestShaders/multipleLights.fs");
	Material sphereMat(&sphereShaderTemp);
    sphereMat.SetAmbient(Vector4D(0.1f, 0.1f, 0.1f, 1.0f));
	sphereMat.SetShininess(100.0f);
    Renderer renderer1(&sphereMesh, &sphereMat);

    NodePtr torus(new Node("Torus"));
    torus->AttachComponent(&renderer1);
    torus->SetLocalEulerAngle(-45.0f, 0.0f, 0.0f);
    torus->SetLocalScale(0.5, 0.5, 0.5);
    torus->SetPosition(0.0, 0.5, 0.0);

	//torus->AddChild(light);
	//torus->AddChild(referenceBox);

    Plane groundPlaneMesh(40, 40);
    groundPlaneMesh.SetColor(Vector3D(1.0f, 0.0f, 0.0f));
    Shader groundPlaneShader("TestShaders/TextureSetup.vs", "TestShaders/TextureSetup.fs");
    groundPlaneShader.AddTexture("Resources/textures/container2.png", TextureType::Diffuse);
    groundPlaneShader.AddTexture("Resources/textures/container2_specular.png", TextureType::Specular);
    Material groundPlaneMat(&groundPlaneShader);
    groundPlaneMat.SetAmbient(Vector4D(0.1f, 0.1f, 0.1f, 1.0f));
    groundPlaneMat.SetShininess(100.0f);
    Renderer groundPlaneRenderer(&groundPlaneMesh, &groundPlaneMat);

    NodePtr groundPlane(new Node("Ground Plane"));
    groundPlane->AttachComponent(&groundPlaneRenderer);
    groundPlane->SetLocalEulerAngle(-45.0f, 0.0f, 0.0f);
    groundPlane->SetLocalScale(2.0, 2.0, 2.0);


    Scene rootScene(cam);
	rootScene.AddToScene(torus);
	rootScene.AddToScene(light);
    rootScene.AddToScene(groundPlane);
    rootScene.AddLight(pointLight);
    rootScene.AddLight(pointLight1);
    rootScene.AddLight(pointLight2);


	float angle = 0;
    while (!window->IfWindowClosed())
	{
        // time handle
        auto currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
		angle += deltaTime * 1.0f;
		std::cout << "FPS : " << static_cast<int>(1.0f / deltaTime) << std::endl;

        KeyBoardEvents(window, input);
        window->SetBGColor(0.0f, 0.0f, 0.0f, 1.0f);

        cam->SetFOV(fov);
        cam->Set(cameraPos, cameraFront, cameraUp);
		pointLight->SetPosition(Vector4D(sin(angle), lightPos.y - 1.0f, lightPos.z, 1.0));
        pointLight2->SetPosition(Vector4D(lightPos.x, lightPos.y - 1.0f, sin(angle), 1.0f));
//        pointLight1->SetPosition(Vector4D( lightPos.x, sin(angle) + 3.0f, lightPos.z, 1.0));
		light->SetPosition(sin(angle), lightPos.y, lightPos.z);

		//torus->SetPosition(sin(angle), 0, 0);
		//torus->SetLocalScale(sin(angle), sin(angle), sin(angle));
		//torus->SetRotation(angle * 2.0f, Vector3D(1.0f, 1.0f, 0.0f));
		//light->SetLocalEulerAngle(angle * 20.0f, 0.0f, 0.0f);

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