//
// Created by suraj on 12/4/17.
//

#include "Scene.h"

namespace CG184{

    Scene::Scene(CameraPtr cam)
    {
        m_Camera = std::move(cam);
    }

    void Scene::Render()
    {
        for (auto &m_Node : m_RenderQueue) {
			m_Node->UpdateWorldModelMatrix();
        }

		for (auto &m_Node : m_RenderQueue) {
			if (m_Node->HasComponent(ComponentType::RendererType)) {
				Renderer* renderer = (m_Node->GetComponent<Renderer>());
				if (renderer != nullptr) {

					// Sending Data to Associated Shader
					renderer->SendCameraPosData(m_Camera);
					renderer->SendViewMatrixData(m_Camera->GetViewMatrix());
					renderer->SendProjectionMatrixData(m_Camera->GetProjectionMatrix());
					renderer->SendModelMatrixData(m_Node->GetTransformComponent().GetWorldTransformMat());

                    for(auto i = 0; i < m_Lights.size(); i++)
                        renderer->SendLightData(m_Lights[i], i);

                    renderer->SendMaterialData();
					renderer->Render();
				}
				else {
					throw "(Null Exception) Renderer Null";
				}
			}
		}
    }

    Scene::~Scene() {
        m_Camera = nullptr;
    }

    void Scene::AddToScene(NodePtr node) {
        m_RenderQueue.push_back(node);
    }

    void Scene::TraverseAllChildNodes(Node& a_Node){
        for (uint32_t i = 0; i < a_Node.GetNumOfChildNode(); i++){
            TraverseAllChildNodes(*(a_Node.GetChildNodeAt(i)));
        }

        if (a_Node.HasComponent(ComponentType::RendererType)) {
            Renderer* renderer = (a_Node.GetComponent<Renderer>());
            if(renderer != nullptr) {
                renderer->SendViewMatrixData(m_Camera->GetViewMatrix());
                renderer->SendProjectionMatrixData(m_Camera->GetProjectionMatrix());
                renderer->Render();
            }
            else {
                throw "(Null Exception) Renderer Null";
            }
        }
    }

    void Scene::AddLight(LightPtr light) {
        m_Lights.push_back(light);
    }

}
