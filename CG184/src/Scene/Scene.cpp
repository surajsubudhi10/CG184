//
// Created by suraj on 12/4/17.
//

#include "Scene.h"

namespace CG184{
//    class Renderer;

    Scene::Scene(CG184::Camera &cam) : Node()
    {
        m_Camera = &cam;
    }

    void Scene::Render()
    {
        //TODO Check for the child as Null if not recursive(Traversing through all the nodes in the Scene Graph)
        for (auto &m_Node : m_Nodes) {
            if (m_Node.HasComponent(ComponentType::RendererType)) {
                Renderer* renderer = (m_Node.GetComponent<Renderer>());
                if(renderer != nullptr) {
                    renderer->SendViewMatrixData(m_Camera->GetViewMatrix());
                    renderer->SendProjectionMatrixData(m_Camera->GetProjectionMatrix());
                    renderer->Render();
                }
                else {
                    std::cerr << "Renderer Null" << std::endl;


//                    return;
                }

            }
        }
    }

    Scene::~Scene()
    {
        m_Camera = nullptr;
    }

    void Scene::AddToScene(Node &node) {
        node.SetParent(this);
        m_Nodes.push_back(node);
    }


}
