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

    /**
     * \brief Get the hovered element as the mouse hover on the object
     * \param p : the mouse position
     * \param getElement : do we need the element 
     * \param transformed : is object transformed
     */
    void Input::GetHoveredObject(const Vector2D &p, bool getElement, bool transformed) 
    {
        // Set the background color to the maximum possible value---this value should
        // be far beyond the maximum pick index, since we have at most 2^(8+8+8) = 16,777,216 distinct IDs
        glClearColor(1., 1., 1., 1.);

        // Clear any color values currently in the color buffer---we do not want to use these for
        // picking, since they represent, e.g., shading colors rather than pick IDs.
        // Also clear the depth buffer so that we can use it to determine the closest object under the cursor.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // We want to draw the pick IDs as raw color values; shading functionality
        // like lighting and blending shouldn't interfere.
        glPushAttrib(GL_ALL_ATTRIB_BITS);
        glDisable(GL_LIGHTING);
        glDisable(GL_BLEND);

        // Keep track of the number of picking IDs used so far
        int pickID = 0;

        for(const auto& node : m_ScenePtr->m_RenderQueue)
        {
            if (node->isPickable)
            {
                // The implementation of draw_pick MUST increment the pickID for each new pickable element it draws.
                node->DrawPick(pickID, transformed, m_ScenePtr->m_CameraPtr);
            }
        }

        unsigned char color[4];
        glReadPixels(p.x, m_Window->m_height - p.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);

        int ID = RGBToIndex(color[0], color[1], color[2]);

        // By default, set hovered object to "none"
        hovered.clear();

        // Determine which element generated this pick ID
        int i = 0;
        for (const auto& node : m_ScenePtr->m_RenderQueue) 
        {
            // Call the object's method for setting the selection
            // based on the ID.  (This allows the object to set
            // the selection to an element within that particular
            // object type, e.g., for a mesh it can specify that a
            // particular vertex is selected etc.)
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
                        glColor3f(0.2f, 0.2f, 0.2f);
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

                    glLineWidth(2.0f);
                    glEnable(GL_LINE_SMOOTH);
                    glBegin(GL_LINES);
                        glColor3f(0.8f, 0.8f, 0.8f);
                        glVertex3f(v0.x, v0.y, v0.z);
                        glVertex3f(v1.x, v1.y, v1.z);
                    glEnd();
                    glLineWidth(1.0f);

                    glPopMatrix();
                    glPopMatrix();
                    return;
                } // End of Edge Drawing

                Vertex* v = hovered.element->getVertex();
                if (v != nullptr)
                {
                    HalfEdgeIter h = v->halfedge();
                    Vector3D v0 = h->vertex()->position + h->vertex()->ComputeNormal() * h->vertex()->offset;

                    glEnable(GL_POINT_SMOOTH);
                    glPointSize(10.0f);
                    glBegin(GL_POINTS);
                        glColor3f(0.8f, 0.8f, 0.8f);
                        glVertex3f(v0.x, v0.y, v0.z);
                    glEnd();
                    glPointSize(1.0f);

                    glPopMatrix();
                    glPopMatrix();
                    return;
                }   // End of Vertex drawing

                glPopMatrix();
                glPopMatrix();
            
            } // End of loop if hover element is valid half edge element
        }   // End of loop of hover object is valid node
    } // End of DrawSelection


    Input::~Input()
    = default;


    void mouse_cursor_callback(GLFWwindow* window, double xpos, double ypos)
    {
        double xPos;
        double yPos;
        glfwGetCursorPos(window, &xPos, &yPos);
        Input::mousePosition = Vector2D(static_cast<float>(xPos), static_cast<float>(yPos));
    }

    void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
    {
        if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
            return;
    }

}   // End of CG184