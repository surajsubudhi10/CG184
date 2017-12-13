//
// Created by suraj on 12/4/17.
//

#include "Scene.h"

namespace CG184{

    Scene::Scene(CG184::Camera &cam) : Node()
    {
        m_Camera = &cam;
    }

    void Scene::Render()
    {
        for (auto &m_Node : m_Nodes) {
			m_Node->UpdateWorldModelMatrix();
        }

		for (auto &m_Node : m_Nodes) {
			if (m_Node->HasComponent(ComponentType::RendererType)) {
				Renderer* renderer = (m_Node->GetComponent<Renderer>());
				if (renderer != nullptr) {
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

    Scene::~Scene()
    {
        m_Camera = nullptr;
    }

    void Scene::AddToScene(Node* node) {
        //node.SetParent(this);
        m_Nodes.push_back(node);
    }

    void Scene::TraverseAllChildNodes(Node& a_Node){
        for (int i = 0; i < a_Node.GetNumOfChildNode(); i++){
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
