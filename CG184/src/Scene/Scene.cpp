//
// Created by suraj on 12/4/17.
//

#include "Scene.h"

namespace CG184{

    Scene::Scene(CameraPtr cam) : m_Anchor(new Node("Anchor"))
    {
        m_Camera = std::move(cam);
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
    					renderer->SendCameraPosData(m_Camera);
	    				renderer->SendViewMatrixData(m_Camera->GetViewMatrix());
		    			renderer->SendProjectionMatrixData(m_Camera->GetProjectionMatrix());
			    		renderer->SendModelMatrixData(m_Node->GetTransformComponent().GetWorldTransformMat());

                        for (unsigned int i = 0; i < m_Lights.size(); i++)
                            renderer->SendLightData(m_Lights[i], i);

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
        m_Camera = nullptr;
    }

    void Scene::AddToScene(NodePtr node) {
        m_RenderQueue.push_back(node);
    }

	void Scene::CreateAnchor()
	{
		std::vector<Vector3D> pos{
			Vector3D(0, 0, 0), Vector3D(1, 0, 0),
			Vector3D(0, 0, 0), Vector3D(0, 1, 0),
			Vector3D(0, 0, 0), Vector3D(0, 0, 1)
		};

		std::vector<Vector3D> col{
			Vector3D(1, 0, 0), Vector3D(1, 0, 0),
			Vector3D(0, 1, 0), Vector3D(0, 1, 0),
			Vector3D(0, 0, 1), Vector3D(0, 0, 1)
		};

		std::vector<uint32_t> ind{ 0, 1, 0, 2, 3, 2, 4, 5, 4 };

		Mesh*     anchorMesh		= new Mesh(pos, ind);
		anchorMesh->SetColors(col); // Setting Same as position x->red, y->green, z->blue

		Shader*   anchorShader		= new Shader("TestShaders/anchor.vs", "TestShaders/anchor.fs");
		Material* anchorMat			= new Material(anchorShader);
		Renderer* anchorRenderer	= new Renderer(anchorMesh, anchorMat);

		anchorRenderer->SetRenderMode(RenderMode::LINES);
		m_Anchor->AttachComponent(anchorRenderer);
		this->AddToScene(m_Anchor);
	}

    void Scene::TraverseAllChildNodes(Node& a_Node){
        for (uint32_t i = 0; i < a_Node.GetNumOfChildNode(); i++){
            TraverseAllChildNodes(*(a_Node.GetChildNodeAt(i)));
        }

        if (a_Node.HasComponent(ComponentType::RENDERER)) {
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
