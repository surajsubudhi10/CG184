#include <algorithm>
#include "Renderer.h"
#include "../Geometry/Mesh.h"

namespace CG184 
{

    Renderer::Renderer(Mesh &a_Mesh, Material &a_Material)
    {
        m_Buffer = a_Mesh.vertices;
        m_IndexCount = (unsigned int)a_Mesh.m_Indices.size();
        indicesData = new GLuint[m_IndexCount];
        for (int i = 0; i < m_IndexCount; i++){
            indicesData[i] = a_Mesh.m_Indices[i];
        }
        InitGLBuffers(a_Mesh.m_NumOfVert, m_IndexCount);
        m_Material = &a_Material;
    }

    void Renderer::InitGLBuffers(unsigned int numOfVert, unsigned int indicesNum)
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * numOfVert, m_Buffer, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*) nullptr);
        glEnableVertexAttribArray(SHADER_VERTEX_INDEX);

        glVertexAttribPointer(SHADER_COLOR_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
        glEnableVertexAttribArray(SHADER_COLOR_INDEX);

        glVertexAttribPointer(SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::normal)));
        glEnableVertexAttribArray(SHADER_NORMAL_INDEX);

        glVertexAttribPointer(SHADER_TEXCORD_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::texCoord)));
        glEnableVertexAttribArray(SHADER_TEXCORD_INDEX);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        m_IBO = new IndexBuffer(indicesData, indicesNum);
        glBindVertexArray(0);

        delete[] indicesData;
        indicesData = nullptr;

//        delete[] m_Buffer;
        m_Buffer = nullptr;

    }


	Renderer::~Renderer()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);

        m_Material = nullptr;
	}

	void Renderer::Render()
	{
        m_Material->GetShader()->ActivateShader();
		glBindVertexArray(m_VAO);
		m_IBO->Bind();

		//glDrawArrays(GL_TRIANGLES, 0, numOfVert);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, nullptr);

		m_IBO->Unbind();
		glBindVertexArray(0);
        m_Material->GetShader()->DeactivateShader();
	}

}