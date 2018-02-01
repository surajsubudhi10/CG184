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

		void			Bind()		const;
		void			Unbind()	const;
		void			AddIndexBufferData(GLuint* data, GLuint count);
	private:
		GLuint			m_BufferID;
		GLuint			m_IndexCount;
	};
}
