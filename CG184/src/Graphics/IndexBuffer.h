#pragma once

#include <GL\glew.h>

namespace CG184 
{
	class IndexBuffer
	{
	public:
		IndexBuffer(GLushort* data, GLsizei count);
		IndexBuffer(GLuint* data, GLsizei count);
		~IndexBuffer();

		void Bind() const;
		void Unbind() const;

	private:
		GLuint m_BufferID;
		GLuint m_IndexCount;
	};
}
