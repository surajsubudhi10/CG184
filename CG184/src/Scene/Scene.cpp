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
        std::vector<Vector3D> pos
        {
            Vector3D(0, 0, 0), Vector3D(1, 0, 0),
            Vector3D(0, 0, 0), Vector3D(0, 1, 0),
            Vector3D(0, 0, 0), Vector3D(0, 0, 1)
        };

        std::vector<Vector3D> col
        {
            Vector3D(1, 0, 0), Vector3D(1, 0, 0),
            Vector3D(0, 1, 0), Vector3D(0, 1, 0),
            Vector3D(0, 0, 1), Vector3D(0, 0, 1)
        };

        std::vector<uint32_t> ind{ 0, 1, 0, 2, 3, 2, 4, 5, 4 };

        Mesh*   anchorMesh		= new Mesh(pos, ind);
        anchorMesh->SetColors(col); // Setting Same as position x->red, y->green, z->blue

        auto*   anchorShader		= new Shader("TestShaders/anchor.vs", "TestShaders/anchor.fs");
        auto*   anchorMat			= new Material(anchorShader);
        auto*   anchorRenderer	    = new Renderer(anchorMesh, anchorMat);

        anchorRenderer->SetRenderMode(RenderMode::LINES);
        m_AnchorPtr->AttachComponent(anchorRenderer);
        this->AddToScene(m_AnchorPtr);
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
