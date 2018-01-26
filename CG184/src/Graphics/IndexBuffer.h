#pragma once

#include <GL/glew.h>

namespace CG184 
{
	class IndexBuffer
	{
	public:
		IndexBuffer(GLushort* data, GLuint count);
		IndexBuffer(GLuint* data, GLuint count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

	private:
		GLuint m_BufferID;
		GLuint m_IndexCount;
	};
}
