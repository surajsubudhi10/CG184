#include "Renderer.h"

namespace CG184 
{
	
	// TODO use VertexData Struct in Vector data for all the vertex Data.
	Renderer::Renderer(std::vector<float> vertexArray)
	{

		int numOfVert = vertexArray.size();
		vertexData = new float[numOfVert];
		for (int i = 0; i < numOfVert; i++)
		{
			vertexData[i] = vertexArray[i];
		}

		glGenVertexArrays(1, &m_VAO);
		glGenBuffers(1, &m_VBO);

		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData) * numOfVert, vertexData, GL_DYNAMIC_DRAW);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);

		glVertexAttribPointer(SHADER_COLOR_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(float)));
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);


		glBindVertexArray(0);

	}

	
	Renderer::~Renderer()
	{
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
		
		delete[] vertexData;
		vertexData = nullptr;
	}

	void Renderer::Render()
	{
		glBindVertexArray(m_VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
		glDrawArrays(GL_TRIANGLES, 0, 3);
		
		glBindVertexArray(0);
	}

}