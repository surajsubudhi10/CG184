#include "IndexBuffer.h"


namespace CG184 
{
    
    IndexBuffer::IndexBuffer(GLushort * data, GLuint count)
        : m_IndexCount(count)
    {
        glGenBuffers(1, &m_BufferID);
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexCount * sizeof(GLshort), data, GL_DYNAMIC_DRAW);
        Unbind();

    }

    IndexBuffer::IndexBuffer(GLuint * data, GLuint count)
        : m_IndexCount(count)
    {
        glGenBuffers(1, &m_BufferID);
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexCount * sizeof(GLuint), data, GL_DYNAMIC_DRAW);
        Unbind();

    }

    void IndexBuffer::AddIndexBufferData(GLuint* data, GLuint count) 
    {
        m_IndexCount = count;
        Bind();
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_IndexCount * sizeof(GLuint), data, GL_DYNAMIC_DRAW);
        Unbind();
    }

    IndexBuffer::~IndexBuffer()
    {
        glDeleteBuffers(1, &m_BufferID);
    }

    void IndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
    }

    void IndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferID);
    }

}   // End of CG184