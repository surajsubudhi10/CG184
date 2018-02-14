#include <Scene/Scene.h>
#include <EventSystem/Input.h>

namespace CG184 
{
    Vector2D Input::mousePosition = Vector2D();

    void mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos);
    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

    Input::Input(WindowPtr window, Scene* scene)
    {
        m_Window				= window;
        m_ScenePtr				= scene;
        
        m_PickerShaderPtr		= new Shader("../../CG184/TestShaders/picker.vs", "../../CG184/TestShaders/picker.fs");
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

    void Input::GetHoveredObject(const Vector2D &p, bool getElement, bool transformed)
    {

        /** Set the background color to the maximum possible value---this value should
         be far beyond the maximum pick index, since we have at most 2^(8+8+8) = 16,777,216 distinct IDs */
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        /** Clear any color values currently in the color buffer---we do not want to
         use these for picking, since they represent, e.g., shading colors rather than pick IDs.
         Also clear the depth buffer so that we can use it to determine the closest object under the cursor.*/
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        /// We want to draw the pick IDs as raw color values; shading functionality
        /// like lighting and blending shouldn't interfere.
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glDisable(GL_LIGHTING);
        glDisable(GL_BLEND);

        // Keep track of the number of picking IDs used so far
        int pickID = 0;

        for (const auto &node : m_ScenePtr->m_RenderQueue)
        {
            if(node->HasComponent(ComponentType::RENDERER))
            {
                Renderer& nodeRenderer = *node->GetComponent<Renderer>();
                if(&nodeRenderer != nullptr)
                {
                    Mesh& mesh = *nodeRenderer.GetMesh();
                    if (node->isPickable) {
                        // The implementation of draw_pick MUST increment the
                        // pickID for each new pickable element it draws.
                        mesh.draw_pick(pickID, transformed);
                    }
                }
            }
        }

        unsigned char color[4];
        glReadPixels(p.x, p.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);

        int ID = RGBToIndex(color[0], color[1], color[2]);

        // By default, set hovered object to "none"
        hovered.clear();

        // Determine which element generated this pick ID
        int i = 0;
        for (const auto &node : m_ScenePtr->m_RenderQueue)
        {
            if(node->HasComponent(ComponentType::RENDERER))
            {
                Renderer& nodeRenderer = *node->GetComponent<Renderer>();
                if(&nodeRenderer != nullptr)
                {
                    Mesh& mesh = *nodeRenderer.GetMesh();
                    // Call the object's method for setting the selection
                    // based on the ID.  (This allows the object to set
                    // the selection to an element within that particular
                    // object type, e.g., for a mesh it can specify that a
                    // particular vertex is selected, or for a camera it might
                    // specify that a control handle was selected, etc.)
                    mesh.setSelection(ID, hovered);
                    i++;
                }
            }

        }

        if (!getElement) {
            // Discard element information
            hovered.element = nullptr;
        }

        // Restore any draw state that we disabled above.
        glPopAttrib();

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