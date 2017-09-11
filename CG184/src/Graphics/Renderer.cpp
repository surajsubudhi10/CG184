#include "Renderer.h"

namespace CG184 
{
	
	// TODO use VertexData Struct in Vector data for all the vertex Data.
	Renderer::Renderer(std::vector<float> vertexArray, std::vector<GLuint> indexArray)
	{

		int numOfFloat = vertexArray.size();
		m_IndexCount = indexArray.size();
		
		// Vertex Data Setup
		vertexData = new float[numOfFloat];
		for (int i = 0; i < numOfFloat; i++)
		{
			vertexData[i] = vertexArray[i];
		}


		// Index Data Setup
		indicesData = new GLuint[indexArray.size()];
		for (int i = 0; i < indexArray.size(); i++)
		{
			indicesData[i] = indexArray[i];
		}


		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData) * numOfFloat, vertexData, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);

		glVertexAttribPointer(SHADER_COLOR_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(float)));
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_TEXCORD_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(6 * sizeof(float)));
		glEnableVertexAttribArray(SHADER_TEXCORD_INDEX);
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		m_IBO = new IndexBuffer(indicesData, indexArray.size());

		glBindVertexArray(0);



		delete[] vertexData;
		vertexData = nullptr;

		delete[] indicesData;
		indicesData = nullptr;

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