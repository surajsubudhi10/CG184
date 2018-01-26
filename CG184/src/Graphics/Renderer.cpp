#include <algorithm>
#include "Renderer.h"
#include "../Scene/Node.h"

namespace CG184 
{

    Renderer::Renderer(Mesh *a_Mesh, Material* a_Material) : Component()
    {
        m_Type = ComponentType ::RENDERER;
        m_MeshFilter = new MeshFilter(a_Mesh);
        m_Material = *a_Material;
    }

	Renderer::Renderer(const Renderer& renderer) : Component()
	{
		m_Type = renderer.m_Type;
		m_MeshFilter = new MeshFilter(*renderer.m_MeshFilter);
		m_Material = renderer.m_Material;
	}

	Renderer::~Renderer()
	{
        delete m_MeshFilter;
        m_MeshFilter = nullptr;
	}

	void Renderer::Render()
	{
        m_Material.GetShader()->ActivateShader();
        m_MeshFilter->BindVertexObjects();
		m_MeshFilter->GetIBO()->Bind();

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

		glDrawElements(GL_TRIANGLES, m_MeshFilter->GetIndexCount(), GL_UNSIGNED_INT, nullptr);

        m_MeshFilter->GetIBO()->Unbind();
        m_MeshFilter->UnBindVertexObjects();
        m_Material.GetShader()->DeactivateShader();
	}

    Matrix4D Renderer::GetModelMatrix() {
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