#include "Renderer.h"

namespace CG184 
{
	
	Renderer::Renderer(std::vector<float> vertexArray, std::vector<GLuint> indexArray)
	{
		
		// Vertex Data Setup
		int numOfVert = vertexArray.size() / 6;
		m_Buffer = new VertexData[numOfVert];
		for (int i = 0; i < numOfVert; i += 1)
		{
			m_Buffer->position	= Vector3D(vertexArray[6 * i + 0], vertexArray[6 * i + 1], vertexArray[6 * i + 2]);
			m_Buffer->color		= Vector3D(1.0f, 0.5f, 0.31f);
			//m_Buffer->color		= Vector3D(vertexArray[8 * i + 3], vertexArray[8 * i + 4], vertexArray[8 * i + 5]);
			m_Buffer->normal	= Vector3D(vertexArray[6 * i + 3], vertexArray[6 * i + 4], vertexArray[6 * i + 5]);
			//m_Buffer->texCoord = Vector2D(vertexArray[8 * i + 6], vertexArray[8 * i + 7]);
			m_Buffer->texCoord	= Vector2D(0,0);
			m_Buffer++;
		}
		m_Buffer -= numOfVert;


		// Index Data Setup
		m_IndexCount = indexArray.size();
		indicesData = new GLuint[indexArray.size()];
		for (int i = 0; i < indexArray.size(); i++)
		{
			indicesData[i] = indexArray[i];
		}


		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(VertexData) * numOfVert, m_Buffer, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);

		glVertexAttribPointer(SHADER_COLOR_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::color)));
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::normal)));
		glEnableVertexAttribArray(SHADER_NORMAL_INDEX);

		glVertexAttribPointer(SHADER_TEXCORD_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, VertexData::texCoord)));
		glEnableVertexAttribArray(SHADER_TEXCORD_INDEX);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_IBO = new IndexBuffer(indicesData, indexArray.size());
		glBindVertexArray(0);

		delete[] indicesData;
		indicesData = nullptr;

		delete[] m_Buffer;
		m_Buffer = nullptr;

	}

	
	Renderer::~Renderer()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
	}

	void Renderer::Render()
	{

		glBindVertexArray(m_VAO); 
		m_IBO->Bind();
		
		//glDrawArrays(GL_TRIANGLES, 0, numOfVert);
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, NULL);

		m_IBO->Unbind();
		glBindVertexArray(0);
	}

}