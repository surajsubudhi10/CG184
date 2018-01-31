#include <algorithm>
#include "Renderer.h"
#include "../Scene/Node.h"

namespace CG184 
{

    Renderer::Renderer(Mesh *a_Mesh, Material* a_Material) : Component(), m_Mesh(*a_Mesh)
    {
        m_Type = ComponentType ::RENDERER;
        m_SharedMaterial = a_Material;
        m_MeshFilter = new MeshFilter(a_Mesh);
        m_SharedMesh = make_shared<Mesh>(a_Mesh);
        m_Mesh = *m_SharedMesh.get();
        //m_Mesh.CopyMesh(*m_SharedMesh);


//        if(m_SharedMeshFilter != nullptr) {
//            m_MeshFilter.AttachMesh(*m_SharedMeshFilter->GetMesh());
//        }

        if(m_SharedMaterial != nullptr)
            m_Material = *m_SharedMaterial;
    }

	Renderer::Renderer(const Renderer& renderer) : Component(), m_Mesh(renderer.m_Mesh)
	{
		m_Type = renderer.m_Type;
        m_SharedMaterial = renderer.m_SharedMaterial;
		m_MeshFilter = renderer.m_MeshFilter;
        m_SharedMesh = renderer.m_SharedMesh;
        m_Mesh = renderer.m_Mesh;
//        m_Mesh.CopyMesh(renderer.m_Mesh);

//        if(m_SharedMeshFilter != nullptr)
//            m_MeshFilter.AttachMesh(*m_SharedMeshFilter->GetMesh());
            //m_MeshFilter = new MeshFilter(*m_SharedMesh.get());

        if(m_SharedMaterial != nullptr)
            m_Material = *m_SharedMaterial;
	}

	Renderer::~Renderer()
	{
        delete m_MeshFilter;
		m_MeshFilter = nullptr;

        m_SharedMaterial = nullptr;
	}

	void Renderer::Render()
	{
        m_Material.GetShader()->ActivateShader();

        if(m_SharedMesh.get()->IsDirty()){
            m_Mesh.CopyMesh(*m_SharedMesh.get());
			m_MeshFilter->AttachMesh(m_SharedMesh.get());
            m_SharedMesh->MakeClean();
        }
		m_MeshFilter->AttachMesh(&m_Mesh);

        m_MeshFilter->BindVertexObjects();
        m_MeshFilter->GetIBO()->Bind();
        m_MeshFilter->UpdateVertexBuffer();

		if(m_RenderMode == RenderMode::LINES)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		else if ((m_RenderMode == RenderMode::POINTS))
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		else
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		glDrawElements(GL_TRIANGLES, m_MeshFilter->GetIndexCount(), GL_UNSIGNED_INT, nullptr);

        m_MeshFilter->GetIBO()->Unbind();
        m_MeshFilter->UnBindVertexObjects();
        m_Material.GetShader()->DeactivateShader();
	}

    Matrix4D Renderer::GetModelMatrix() const {
        return m_AttachedNode->GetTransformComponent().GetWorldTransformMat();
    }

    void Renderer::SendViewMatrixData(Matrix4D &viewMat) {
        m_Material.GetShader()->SetUniformMat4f("view", viewMat.elements);
    }

	void Renderer::SendModelMatrixData(Matrix4D& modelMat) {
		m_Material.GetShader()->SetUniformMat4f("model", modelMat.elements);
	}

	void Renderer::SendLightData(LightPtr light, int index){
        string lightName = "light";
        lightName = lightName + "[" + to_string(index) + "]";
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