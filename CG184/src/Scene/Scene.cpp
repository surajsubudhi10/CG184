//
// Created by suraj on 12/4/17.
//

#include "Scene.h"

namespace CG184{

    Scene::Scene(Camera* cam)
    {
        m_Camera = cam;
		m_Light = new Light();
    }

	Scene::Scene(CG184::Camera* cam, Light* light)
	{
		m_Camera = cam;
		m_Light = light;
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
					renderer->SendCameraPosData(m_Camera);
					renderer->SendViewMatrixData(m_Camera->GetViewMatrix());
					renderer->SendProjectionMatrixData(m_Camera->GetProjectionMatrix());
					renderer->SendLightData(m_Light);
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
		m_Light = nullptr;
    }

    void Scene::AddToScene(Node* node) {
        m_RenderQueue.push_back(node);
    }



    void Scene::TraverseAllChildNodes(Node& a_Node){
        for (unsigned int i = 0; i < a_Node.GetNumOfChildNode(); i++){
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



}
