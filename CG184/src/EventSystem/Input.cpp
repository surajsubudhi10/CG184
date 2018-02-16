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


    void Input::GetHoveredObject(const Vector2D &p, bool getElement, bool transformed) 
    {
        cout << "Mouse Pos : " << p << endl;
        // Set the background color to the maximum possible value---this value should
        // be far
        // beyond the maximum pick index, since we have at most 2^(8+8+8) = 16,777,216
        // distinct IDs
        glClearColor(1., 1., 1., 1.);

        // Clear any color values currently in the color buffer---we do not want to
        // use these for
        // picking, since they represent, e.g., shading colors rather than pick IDs.
        // Also clear
        // the depth buffer so that we can use it to determine the closest object
        // under the cursor.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // We want to draw the pick IDs as raw color values; shading functionality
        // like lighting and blending shouldn't interfere.
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glDisable(GL_LIGHTING);
        glDisable(GL_BLEND);

        // Keep track of the number of picking IDs used so far
        int pickID = 0;

        for (NodePtr node : m_ScenePtr->m_RenderQueue) 
        {
            if (node->isPickable)
            {
                // The implementation of draw_pick MUST increment the
                // pickID for each new pickable element it draws.
                node->DrawPick(pickID, transformed, m_ScenePtr->m_CameraPtr);
            }
        }

        unsigned char color[4];
        glReadPixels(p.x, m_Window->m_height - p.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);

        int ID = RGBToIndex(color[0], color[1], color[2]);
        cout << "Selected ID : " << ID << endl;

        // By default, set hovered object to "none"
        hovered.clear();

        // Determine which element generated this pick ID
        int i = 0;
        for (NodePtr node : m_ScenePtr->m_RenderQueue) 
        {
            // Call the object's method for setting the selection
            // based on the ID.  (This allows the object to set
            // the selection to an element within that particular
            // object type, e.g., for a mesh it can specify that a
            // particular vertex is selected, or for a camera it might
            // specify that a control handle was selected, etc.)
            node->SetSelection(ID, hovered);
            i++;
        }

        if (!getElement) {
            // Discard element information
            hovered.element = nullptr;
        }

        // Restore any draw state that we disabled above.
        glPopAttrib();
    }

    /**
     * \Draw the selected element(vertex, edge, face) on Mesh.
     */
    void Input::DrawSelection() const
    {
        if(hovered.object != nullptr)
        {
            if (hovered.element != nullptr)
            {
                Matrix4D mat;
                glPushMatrix();
                glMatrixMode(GL_PROJECTION_MATRIX);
                glLoadIdentity();

                // Multipling the projection Matrix
                mat = m_ScenePtr->m_CameraPtr->GetProjectionMatrix();
                glMultMatrixf(&mat.elements[0]);

                // Multipling the model * view(here identity) Matrix
                glMatrixMode(GL_MODELVIEW_MATRIX);
                mat = m_ScenePtr->m_CameraPtr->GetViewMatrix();
                glMultMatrixf(&mat.elements[0]);

                glPushMatrix();
                const auto world_mat = hovered.object->GetTransformComponent().GetWorldTransformMat();
                glMultMatrixf(&world_mat.elements[0]);

                HalfEdgeElement* he = hovered.element;
                Face* f = he->getFace();
                if(f != nullptr)
                {
                    HalfEdgeIter h = f->halfedge();
                    Vector3D v0 = h->vertex()->position + h->vertex()->ComputeNormal() * h->vertex()->offset;
                    Vector3D v1 = h->next()->vertex()->position + h->next()->vertex()->ComputeNormal() * h->next()->vertex()->offset;
                    Vector3D v2 = h->next()->next()->vertex()->position + h->next()->next()->vertex()->ComputeNormal() * h->next()->next()->vertex()->offset;

                    glBegin(GL_TRIANGLES);
                        glColor3f(0.0f, 0.1f, 0.8f);
                        glVertex3f(v0.x, v0.y, v0.z);
                        glVertex3f(v1.x, v1.y, v1.z);
                        glVertex3f(v2.x, v2.y, v2.z);
                    glEnd();

                    glPopMatrix();
                    glPopMatrix();
                    return;
                }   // End of Face drawing

                Edge* e = hovered.element->getEdge();
                if (e != nullptr)
                {
                    HalfEdgeIter h = e->halfedge();
                    Vector3D v0 = h->vertex()->position + h->vertex()->ComputeNormal() * h->vertex()->offset;
                    Vector3D v1 = h->next()->vertex()->position + h->next()->vertex()->ComputeNormal() * h->next()->vertex()->offset;

                    glBegin(GL_LINE);
                        glColor3f(0.0f, 0.1f, 0.8f);
                        glLineWidth(2.0f);
                        glVertex3f(v0.x, v0.y, v0.z);
                        glVertex3f(v1.x, v1.y, v1.z);
                    glEnd();

                    glPopMatrix();
                    glPopMatrix();
                    return;
                } // End of Edge Drawing

                Vertex* v = hovered.element->getVertex();
                if (v != nullptr)
                {
                    HalfEdgeIter h = v->halfedge();
                    Vector3D v0 = h->vertex()->position + h->vertex()->ComputeNormal() * h->vertex()->offset;

                    glBegin(GL_POINT);
                        glColor3f(0.0f, 0.1f, 0.8f);
                        glPointSize(2.0f);
                        glVertex3f(v0.x, v0.y, v0.z);
                    glEnd();

                    glPopMatrix();
                    glPopMatrix();
                    return;
                }   // End of Vertex drawing

                glPopMatrix();
                glPopMatrix();
            }
        }
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