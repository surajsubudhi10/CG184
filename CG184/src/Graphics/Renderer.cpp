#include <algorithm>
#include "Renderer.h"
#include "../Scene/Node.h"

namespace CG184 
{

    Renderer::Renderer(Mesh &a_Mesh, Material &a_Material) : Component()
    {
        m_Type = ComponentType ::RendererType;
        m_MeshFilter = new MeshFilter(a_Mesh);
        m_Material = &a_Material;
    }

	Renderer::~Renderer()
	{
        delete m_MeshFilter;
        m_MeshFilter = nullptr;
        m_Material = nullptr;
	}

	void Renderer::Render()
	{
        m_Material->GetShader()->SetUniformMat4f("model", GetModelMatrix().elements);

        m_Material->GetShader()->ActivateShader();
		glBindVertexArray(m_MeshFilter->GetVAO());
		m_MeshFilter->GetIBO()->Bind();

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, m_MeshFilter->GetIndexCount(), GL_UNSIGNED_INT, nullptr);

        m_MeshFilter->GetIBO()->Unbind();
		glBindVertexArray(0);
        m_Material->GetShader()->DeactivateShader();
	}

    Matrix4D Renderer::GetModelMatrix() {
        return m_AttachedNode->worldModelMatrix;
    }

    void Renderer::SendViewMatrixData(Matrix4D &viewMat) {
        m_Material->GetShader()->SetUniformMat4f("view", viewMat.elements);
    }

    void Renderer::SendProjectionMatrixData(Matrix4D &projMat) {
        m_Material->GetShader()->SetUniformMat4f("projection", projMat.elements);
    }

}