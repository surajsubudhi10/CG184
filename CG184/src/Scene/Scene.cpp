//
// Created by suraj on 12/4/17.
//

#include "Scene.h"

namespace CG184
{

    Scene::Scene(CameraPtr cam) : m_AnchorPtr(new Node("Anchor"))
    {
        m_CameraPtr = std::move(cam);
        CreateAnchor();
    }

    void Scene::Render()
    {
        // Rendering the anchor every frame
        CreateAnchor();

        for (auto &m_Node : m_RenderQueue) {
            m_Node->UpdateWorldModelMatrix();
        }

        for (auto &m_Node : m_RenderQueue) {
            if (m_Node->HasComponent(ComponentType::RENDERER)) {
                Renderer* renderer = (m_Node->GetComponent<Renderer>());
                if (renderer != nullptr) {
                    if(renderer->IsEnabled()) {

                        // Sending Data to Associated Shader
                        renderer->SendCameraPosData(m_CameraPtr);
                        renderer->SendViewMatrixData(m_CameraPtr->GetViewMatrix());
                        renderer->SendProjectionMatrixData(m_CameraPtr->GetProjectionMatrix());
                        renderer->SendModelMatrixData(m_Node->GetTransformComponent().GetWorldTransformMat());

                        for (unsigned int i = 0; i < m_LightsPtr.size(); i++)
                            renderer->SendLightData(m_LightsPtr[i], i);

                        renderer->SendMaterialData();
                        renderer->Render();
                    }
                }
                else {
                    throw "(Null Exception) Renderer Null or Disabled.";
                }
            }
        }
    }

    Scene::~Scene() {
        m_CameraPtr = nullptr;
        m_AnchorPtr = nullptr;
    }

    void Scene::AddToScene(NodePtr node) {
        m_RenderQueue.push_back(node);
    }

    void Scene::CreateAnchor()
    {
        Matrix4D mat;
        glMatrixMode(GL_PROJECTION_MATRIX);
        glLoadIdentity();
        
        // Multipling the projection Matrix
        mat = m_CameraPtr->GetProjectionMatrix();
        glMultMatrixf(&mat.elements[0]);

        // Multipling the model * view(here identity) Matrix
        glMatrixMode(GL_MODELVIEW_MATRIX);
        mat = m_CameraPtr->GetViewMatrix();
        glMultMatrixf(&mat.elements[0]);
        
        glBegin(GL_LINES);
            // X-Axis
            glColor3f(1.f, 0.f, 0.f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(1.0f, 0.0f, 0.0f);

            // Y-Axis
            glColor3f(0.f, 1.f, 0.f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 1.0f, 0.0f);

            // Z-Axis
            glColor3f(0.f, 0.f, 1.f);
            glVertex3f(0.0f, 0.0f, 0.0f);
            glVertex3f(0.0f, 0.0f, 1.0f);
        glEnd();
    }

    void Scene::TraverseAllChildNodes(Node& a_Node){
        for (uint32_t i = 0; i < a_Node.GetNumOfChildNode(); i++){
            TraverseAllChildNodes(*(a_Node.GetChildNodeAt(i)));
        }

        if (a_Node.HasComponent(ComponentType::RENDERER)) {
            Renderer* renderer = (a_Node.GetComponent<Renderer>());
            if(renderer != nullptr) {
                renderer->SendViewMatrixData(m_CameraPtr->GetViewMatrix());
                renderer->SendProjectionMatrixData(m_CameraPtr->GetProjectionMatrix());
                renderer->Render();
            }
            else {
                throw "(Null Exception) Renderer Null";
            }
        }
    }

    void Scene::AddLight(LightPtr light) {
        m_LightsPtr.push_back(light);
    }

}   // End of CG184
