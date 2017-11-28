#pragma once

#include <GL/glew.h>
#include <vector>
#include "IndexBuffer.h"

#include "../Maths/Maths.h"


namespace CG184 
{

//#define RENDERER_MAX_SPRITES	60000
//#define RENDERER_VERTEX_SIZE	sizeof(float) * 8
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
//#define RENDERER_SPRITE_SIZE    (RENDERER_VERTEX_SIZE * 3)
//#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
//#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_VERTEX_INDEX  0
#define SHADER_COLOR_INDEX	 1
#define SHADER_NORMAL_INDEX	 2
#define SHADER_TEXCORD_INDEX 3

	struct VertexData 
	{
		Vector3D position;
		Vector3D color;
		Vector3D normal;
		Vector2D texCoord;
	};

	class Renderer
	{
	public:
		Renderer(std::vector<float>vertexArray, std::vector<GLuint> indexArray);
		~Renderer();

		void Render();
	public:

		GLuint m_VAO;
		GLuint m_VBO;

		int m_IndexCount;
		
		GLuint* indicesData;
		VertexData* m_Buffer;
		IndexBuffer* m_IBO;
	};

	
}