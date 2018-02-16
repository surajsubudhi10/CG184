#include <GL/glew.h>
#include "GLFW/glfw3.h"
#include <iostream>

#include <Graphics/Window.h>
#include <Graphics/Shader.h>

#include <EventSystem/Input.h>
#include <Camera/Camera.h>

#include <Scene/Nodes.h>
#include <Geometry/Geometry.h>
#include <Lights/Lights.h>


// settings
const uint32_t SCR_WIDTH = 800;
const uint32_t SCR_HEIGHT = 600;
using namespace CG184;

void KeyBoardEvents(const WindowPtr window, Input& input);
void MouseEvents(const WindowPtr window, Input& input, float deltaTime);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void ProcessMouseButtons(Input& input);
void ProcessMouseMotion( Vector2D mousePosition);

// Camera Data
Vector3D cameraPos(3.0f, 3.0f, 3.0f);
Vector3D cameraTarget(0.0f, 0.0f, 0.0f);
Vector3D cameraUp(0.0f, 1.0f, 0.0f);

float yaw   = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
float pitch =   0.0f;
float firstClickPosX = SCR_WIDTH / 2.0f;
float firstClickPosY = SCR_HEIGHT / 2.0f;
float fov = 45.0f;

int IsMouseMouseTracking = 0;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Vector3D lightPos(1.2f, 1.0f, 1.0f);




int main()
{

    WindowPtr window(new Window(SCR_WIDTH, SCR_HEIGHT, "CG184::In Development"));
    glfwSetScrollCallback(window->m_WindowPtr, scroll_callback);

    // ####################################### Camera ###############################################

    CameraPtr cam(new Camera());
    cam->SetAspectRatio((float)SCR_WIDTH / (float)SCR_HEIGHT);
    cam->SetFOV(fov);

    // ####################################### Lights ###############################################

    LightPtr pointLight(new PointLight());
    pointLight->SetPosition(Vector4D(lightPos.x, lightPos.y, lightPos.z, 1.0f));
    pointLight->SetAmbientColor(Vector4D(0.7f, 0.7f, 0.7f, 1.0f));

    // ##############################################################################################

    std::vector<Vector3D> pos1{
            Vector3D(0, 0, 1), Vector3D(0, 1, 0), Vector3D(1, 0, 0)
    };

    std::vector<Vector3D> col1{
            Vector3D(0, 0, 1), Vector3D(0, 1, 0), Vector3D(1, 0, 0)
    };

    std::vector<Vector3D> norm1{
            Vector3D(1, 1, 1).norm(), Vector3D(1, 1, 1).norm(), Vector3D(1, 1, 1).norm()
    };

    std::vector<uint32_t> ind1{0, 1, 2};

    /*Mesh triangleMesh(pos1, ind1);
    triangleMesh.SetColors(col1);
    triangleMesh.SetNormals(norm1);
*/

    Mesh rockMesh;
    rockMesh.LoadModel("../../CG184/Resources/objects/rock/cubeEdit.obj");
    

    //Box boxMesh;
    //Shader boxShaderTemp("TestShaders/multipleLights.vs", "TestShaders/multipleLights.fs");
    Shader boxShaderTemp("../../CG184/TestShaders/solidWireframe.vs", "../../CG184/TestShaders/solidWireframe.fs", "../../CG184/TestShaders/solidWireframe.gs");
    Material boxMat(&boxShaderTemp);
    boxMat.SetAmbient(Vector4D(0.5f, 0.1f, 0.1f, 1.0f));
    Renderer boxRenderer(&rockMesh, &boxMat);

    NodePtr box(new Node("box1"));
    box->AttachComponent(&boxRenderer);
    //box->SetPosition(2.0, 0.0, 0.0);
    box->SetLocalScale(0.25f, 0.25f, 0.25f);

    Renderer boxRenderer1(&rockMesh, &boxMat);
    boxRenderer1.GetMaterial().SetAmbient(Vector4D(0.3f, 0.5f, 0.1f, 1.0f));

    NodePtr box1(new Node("box2"));
    box1->AttachComponent(&boxRenderer1);
    box1->SetLocalScale(0.25f, 0.25f, 0.25f);
    box1->SetPosition(0.0, 0.0, 0.0);


    Scene rootScene(cam);
    rootScene.AddToScene(box);
    //rootScene.AddToScene(box1);
    rootScene.AddLight(pointLight);

    Input input(window, &rootScene);

    Vector3D radialVec = (cameraPos - cameraTarget).norm();
    yaw   = ToDegrees(atan2f(radialVec.x, radialVec.z));
    pitch = ToDegrees(atan2f(radialVec.y, sqrtf(powf(radialVec.x, 2) + powf(radialVec.z, 2))));


    

    float angle = 0;
    while (!window->IfWindowClosed())
    {
        // time handle
        auto currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        angle += deltaTime * 1.0f;
//		std::cout << "FPS : " << static_cast<int>(1.0f / deltaTime) << std::endl;

        KeyBoardEvents(window, input);
        MouseEvents(window, input, deltaTime);
        window->SetBGColor(0.0f, 0.0f, 0.0f, 1.0f);

        cam->SetFOV(fov);
        cam->Set(cameraPos, cameraTarget, cameraUp);
//        box1->SetPosition(cameraTarget);
        //boxRenderer.GetMesh()->SetPosition(1, Vector3D(0.0f, (float)sin(angle), 0.0f));


        input.DrawSelection();
        rootScene.Render();
        window->Update();

    }   // End of animation loop
    
    return 0;
}


void KeyBoardEvents(const WindowPtr window, Input& input)
{
    if (input.IsKeyPressed(GLFW_KEY_ESCAPE))
        window->Close();

    if(input.IsKeyPressed(GLFW_KEY_SPACE)){
        cameraPos    = Vector3D(0.0f, 0.0f, 3.0f);
        cameraTarget = Vector3D(0.0f, 0.0f, 0.0f);
        cameraUp     = Vector3D::Up;

        yaw = pitch = 0.0;
    }

    if (input.IsMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT)) {
        auto cameraSpeed = (float)(2.5 * deltaTime);
        Vector3D tempVec = cameraTarget - cameraPos;
        if (input.IsKeyPressed(GLFW_KEY_W)) {
            tempVec = (tempVec * cameraSpeed);
            cameraPos = cameraPos + tempVec;
            cameraTarget = cameraTarget + tempVec;
        }
        if (input.IsKeyPressed(GLFW_KEY_S)) {
            tempVec = (tempVec * cameraSpeed);
            cameraPos = cameraPos - tempVec;
            cameraTarget = cameraTarget - tempVec;
        }
        if (input.IsKeyPressed(GLFW_KEY_A)) {
            tempVec = ((tempVec.cross(cameraUp)).norm() * cameraSpeed);
            cameraPos = cameraPos + tempVec;
            cameraTarget = cameraTarget + tempVec;
        }

        if (input.IsKeyPressed(GLFW_KEY_E)) {
            tempVec = (Vector3D::Up * cameraSpeed);
            cameraPos = cameraPos - tempVec;
            cameraTarget = cameraTarget - tempVec;
        }
        if (input.IsKeyPressed(GLFW_KEY_Q)) {
            tempVec = (Vector3D::Up * cameraSpeed);
            cameraPos = cameraPos + tempVec;
            cameraTarget = cameraTarget + tempVec;
        }

        if (input.IsKeyPressed(GLFW_KEY_D)) {
            tempVec = ((tempVec.cross(cameraUp)).norm() * cameraSpeed);
            cameraPos = cameraPos - tempVec;
            cameraTarget = cameraTarget - tempVec;
        }
    }
}

void MouseEvents(const WindowPtr window, Input& input, float deltaTime)
{
    if (input.IsKeyPressed(GLFW_KEY_LEFT_ALT)) {
        ProcessMouseButtons(input);
        ProcessMouseMotion(input.mousePosition);
    }else if (input.IsMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT)) {
        //input.ProcessSelection();
        input.GetHoveredObject(input.mousePosition, true, true);
    }
}

void ProcessMouseButtons(Input& input)
{
    // start tracking the mouse
    if (input.IsMouseButtonDown(GLFW_MOUSE_BUTTON_LEFT) && IsMouseMouseTracking != 1)  {
        firstClickPosX = input.mousePosition.x;
        firstClickPosY = input.mousePosition.y;
        IsMouseMouseTracking = 1;
    }

        //stop tracking the mouse
    else if (input.IsMouseButtonUp(GLFW_MOUSE_BUTTON_LEFT)) {
        if (IsMouseMouseTracking == 1) {
            yaw   -= (input.mousePosition.x - firstClickPosX);
            pitch += (input.mousePosition.y - firstClickPosY);
            if (pitch > 85.0f)
                pitch = 85.0f;
            else if (pitch < -85.0f)
                pitch = -85.0f;
        }
        IsMouseMouseTracking = 0;
    }
}

void spherical2cartesian(float r, float alpha, float beta)
{
    cameraPos.x = cameraTarget.x + r * sin(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
    cameraPos.z = cameraTarget.z + r * cos(alpha * 3.14f / 180.0f) * cos(beta * 3.14f / 180.0f);
    cameraPos.y = cameraTarget.y + r *   			   		         sin(beta * 3.14f / 180.0f);
//    cout << "CameraPos : " << cameraPos << "CameraTarget" << cameraTarget << endl;
}

void ProcessMouseMotion( Vector2D mousePosition)
{
    if (!IsMouseMouseTracking)
        return;

    int deltaX, deltaY;
    float alphaAux, betaAux;
    float rAux = (cameraPos - cameraTarget).length();

    deltaX = static_cast<int>(- mousePosition.x + firstClickPosX);
    deltaY = static_cast<int>(  mousePosition.y - firstClickPosY);

    alphaAux = yaw + deltaX;
    betaAux  = pitch + deltaY;

    if (betaAux > 85.0f)
        betaAux = 85.0f;
    else if (betaAux < -85.0f)
        betaAux = -85.0f;

    spherical2cartesian(rAux, alphaAux, betaAux);

}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Vector3D forwardDir = (cameraPos - cameraTarget);
    float r = forwardDir.length();
    forwardDir.normalize();
    r -= yoffset * 0.1f;
    if (r < 0.1f)
        r = 0.1f;

    cameraPos = cameraTarget + (forwardDir * r);
}

