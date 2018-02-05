#include "../Scene/Scene.h"
#include "Input.h"

namespace CG184 
{
    Vector2D Input::mousePosition = Vector2D();

    void mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    Input::Input(WindowPtr window, Scene* scene)
    {
        m_Window				= window;
        m_ScenePtr				= scene;
        
        m_PickerShaderPtr		= new Shader("TestShaders/picker.vs", "TestShaders/picker.fs");
        m_PickerMaterialPtr		= new Material(m_PickerShaderPtr);

        glfwSetCursorPosCallback(m_Window->m_WindowPtr, mouse_cursor_callback);
        glfwSetInputMode(window->m_WindowPtr, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

    bool Input::KeyPressed(std::string key){
        const char c = *key.c_str();
        int keyVal = int(c);
        return glfwGetKey(m_Window->m_WindowPtr, keyVal) == GLFW_PRESS;
    }

    // TODO Temp Function 
    bool Input::IsKeyPressed(int keyVal){
        return glfwGetKey(m_Window->m_WindowPtr, keyVal) == GLFW_PRESS;
    }


    bool Input::KeyReleased(std::string key){
        return false;
    }

    bool Input::IsMouseButtonDown(int button){
        return (glfwGetMouseButton(m_Window->m_WindowPtr, button) == GLFW_PRESS);
    }

    bool Input::IsMouseButtonUp(int button){
        return (glfwGetMouseButton(m_Window->m_WindowPtr, button) == GLFW_RELEASE);
    }


    void Input::ProcessInput()
    {
        if (glfwGetKey(m_Window->m_WindowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(m_Window->m_WindowPtr, true);
    }
        
    void Input::ProcessSelection()
    {
        unsigned char res[4];
        GLint viewport[4];

        RenderSelection();

        glGetIntegerv(GL_VIEWPORT, viewport);
        glReadPixels((int)mousePosition.x, viewport[3] - (int)mousePosition.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &res);
        switch (res[0]) {
            case 0: 
                //printf("Nothing Picked \n");
                break;
            default:
                printf("Picked Object ID: %d\n", res[0]);
        }
    }

    void Input::RenderSelection() 
    {
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto &m_Node : m_ScenePtr->m_RenderQueue) {
            m_Node->UpdateWorldModelMatrix();
        }

//		Renderer pickRenderer(new Mesh(), m_PickerMaterialPtr);
        for (auto &m_Node : m_ScenePtr->m_RenderQueue)
        {
            if (m_Node->HasComponent(ComponentType::RENDERER))
            {
                Renderer* renderer = (m_Node->GetComponent<Renderer>());
                if (&renderer != nullptr)
                {
                    Renderer pickRenderer(renderer->GetMesh(), m_PickerMaterialPtr);
                    m_PickerMaterialPtr->GetShader()->SetUniform1i("code", m_Node->GetInstanceID() + 1);
                    pickRenderer.SendViewMatrixData(m_ScenePtr->m_CameraPtr->GetViewMatrix());
                    pickRenderer.SendProjectionMatrixData(m_ScenePtr->m_CameraPtr->GetProjectionMatrix());

                    Matrix4D modelMatrix = m_Node->GetTransformComponent().GetWorldTransformMat();
                    pickRenderer.GetMaterial().GetShader()->SetUniformMat4f("model", modelMatrix.elements);
                    pickRenderer.Render();
                }
                else {
                    throw "(Null Exception) Renderer Null";
                }
            }
        }

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    }


    Input::~Input()
    {
        delete m_PickerMaterialPtr;
        delete m_PickerShaderPtr;
    }


    void mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos)
    {
        double xPos;
        double yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        Input::mousePosition = Vector2D((float)xPos, (float)yPos);
    }

    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
            return;
    }

}   // End of CG184