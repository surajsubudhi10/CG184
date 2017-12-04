#pragma once

#include <GL/glew.h>
#include <vector>
#include "IndexBuffer.h"

#include "../Maths/Maths.h"
#include "Material.h"
#include "../Scene/Componet.h"


namespace CG184 
{

#define SHADER_VERTEX_INDEX  0
#define SHADER_COLOR_INDEX	 1
#define SHADER_NORMAL_INDEX	 2
#define SHADER_TEXCORD_INDEX 3
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)


	class Mesh;
	class VertexData;

	class Renderer : public Component
	{
	public:

		Renderer(Mesh& a_Mesh, Material& a_Material);
		~Renderer();

		void Render();

        void SendProjectionMatrixData(Matrix4D& projMat);
        void SendViewMatrixData(Matrix4D & viewMat);

    private:
        Matrix4D GetModelMatrix();

	public:

		GLuint m_VAO;
		GLuint m_VBO;

		unsigned int m_IndexCount;
		
		GLuint* indicesData;
		VertexData* m_Buffer;
		IndexBuffer* m_IBO;

    private:
        Material* m_Material;
        void InitGLBuffers(unsigned int numOfVert, unsigned int indicesNum);
	};

	
}