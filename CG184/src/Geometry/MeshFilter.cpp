//
// Created by Suraj on 9/12/17.
//

#include "MeshFilter.h"
#include <iostream>


namespace CG184{

    MeshFilter::MeshFilter(Mesh& a_Mesh) : m_Mesh(&a_Mesh)
    {
        if(m_Mesh != nullptr) {
            m_Buffer = m_Mesh->vertices;
            m_IndexCount = (unsigned int) m_Mesh->m_Indices.size();
            indicesData = new GLuint[m_IndexCount];
            for (unsigned int i = 0; i < m_IndexCount; i++) {
                indicesData[i] = m_Mesh->m_Indices[i];
            }
            InitGLBuffers(m_Mesh->m_NumOfVert, m_IndexCount);
        } else
            throw "(Null Exception) Mesh is a null Pointer.";
    }

    void MeshFilter::InitGLBuffers(unsigned int numOfVert, unsigned int indicesNum)
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
        m_Buffer = nullptr;

    }



    MeshFilter::~MeshFilter()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);

        delete m_IBO;
        m_IBO = nullptr;
    }
}