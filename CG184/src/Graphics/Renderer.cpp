#include <algorithm>
#include "Renderer.h"
#include "../Scene/Node.h"

namespace CG184 
{

    Renderer::Renderer(Mesh *a_Mesh, Material* a_Material) : Component(), m_Mesh(*a_Mesh)
    {
        m_Type					= ComponentType ::RENDERER;
        m_SharedMaterialPtr		= a_Material;
        m_MeshFilterPtr			= new MeshFilter(a_Mesh);
        m_SharedMeshPtr			= std::make_shared<Mesh>(a_Mesh);
        m_Mesh					= *m_SharedMeshPtr.get();

        if(m_SharedMaterialPtr != nullptr)
            m_Material = *m_SharedMaterialPtr;
    }

	Renderer::Renderer(const Renderer& renderer) : Component(), m_Mesh(renderer.m_Mesh)
	{
		m_Type					= renderer.m_Type;
        m_SharedMaterialPtr		= renderer.m_SharedMaterialPtr;
		m_MeshFilterPtr			= renderer.m_MeshFilterPtr;
        m_SharedMeshPtr			= renderer.m_SharedMeshPtr;
        m_Mesh					= renderer.m_Mesh;

        if(m_SharedMaterialPtr != nullptr)
            m_Material = *m_SharedMaterialPtr;
	}

	Renderer::~Renderer()
	{
        delete m_MeshFilterPtr;
		
		m_MeshFilterPtr = nullptr;
        m_SharedMaterialPtr = nullptr;
	}

	void Renderer::Render()
	{
        m_Material.GetShader()->ActivateShader();

        if(m_SharedMeshPtr.get()->IsDirty()){
            m_Mesh.CopyMesh(*m_SharedMeshPtr.get());
			m_MeshFilterPtr->AttachMesh(m_SharedMeshPtr.get());
            m_SharedMeshPtr->MakeClean();
        }
		
		m_MeshFilterPtr->AttachMesh(&m_Mesh); // TODO donot attach the mesh every frame
        m_MeshFilterPtr->BindVertexObjects();
        m_MeshFilterPtr->GetIBO()->Bind();
        m_MeshFilterPtr->UpdateVertexBuffer();

		if(m_RenderMode == RenderMode::LINES)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else if ((m_RenderMode == RenderMode::POINTS))
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glDrawElements(GL_TRIANGLES, m_MeshFilterPtr->GetIndexCount(), GL_UNSIGNED_INT, nullptr);

        m_MeshFilterPtr->GetIBO()->Unbind();
        m_MeshFilterPtr->UnBindVertexObjects();
        m_Material.GetShader()->DeactivateShader();
	}

    Matrix4D Renderer::GetModelMatrix() const {
        return m_AttachedNodePtr->GetTransformComponent().GetWorldTransformMat();
    }

    void Renderer::SendViewMatrixData(Matrix4D &viewMat) {
        m_Material.GetShader()->SetUniformMat4f("view", viewMat.elements);
    }

	void Renderer::SendModelMatrixData(Matrix4D& modelMat) {
		m_Material.GetShader()->SetUniformMat4f("model", modelMat.elements);
	}

	void Renderer::SendLightData(LightPtr light, int index){
		std::string lightName = "light";
        lightName = lightName + "[" + std::to_string(index) + "]";
		m_Material.GetShader()->SetUniform4f(lightName + ".ambient"    , light->GetAmbientColor());
		m_Material.GetShader()->SetUniform4f(lightName + ".diffuse"    , light->GetDiffuseColor());
		m_Material.GetShader()->SetUniform4f(lightName + ".specular"   , light->GetSpecularColor());
		m_Material.GetShader()->SetUniform4f(lightName + ".position"   , light->GetPosition());
		m_Material.GetShader()->SetUniform3f(lightName + ".attenuation", light->GetAttenuation().x, light->GetAttenuation().y, light->GetAttenuation().z);
	}

	void Renderer::SendMaterialData() {
		m_Material.GetShader()->SetUniform4f("material.ambient"  , m_Material.m_Ambient);
		m_Material.GetShader()->SetUniform4f("material.diffuse"  , m_Material.m_Diffuse);
		m_Material.GetShader()->SetUniform4f("material.specular" , m_Material.m_Specular);
		m_Material.GetShader()->SetUniform4f("material.emission" , m_Material.m_Emission);
		m_Material.GetShader()->SetUniform1f("material.shininess", m_Material.m_Shininess);
	}

	void Renderer::SendCameraPosData(CameraPtr cam){
		m_Material.GetShader()->SetUniform3f("viewPos", cam->GetCamPos().x, cam->GetCamPos().y, cam->GetCamPos().z);
	}

    void Renderer::SendProjectionMatrixData(Matrix4D &projMat) {
        m_Material.GetShader()->SetUniformMat4f("projection", projMat.elements);
    }

}