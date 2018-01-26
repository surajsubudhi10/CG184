//
// Created by Suraj on 9/12/17.
//

#include "MeshFilter.h"
#include <iostream>


namespace CG184{

    MeshFilter::MeshFilter(Mesh* a_Mesh) : m_Mesh(a_Mesh)
    {
        if(m_Mesh != nullptr) {
            uint32_t vertexNumber = 0;
            InitializeMeshData(vertexNumber);
            InitGLBuffers(vertexNumber);
        } else
            throw "(Null Exception) Mesh is a null Pointer.";
    }

	MeshFilter::MeshFilter(const MeshFilter& a_MeshFilter) : m_Mesh(a_MeshFilter.m_Mesh)
	{
		if (m_Mesh != nullptr) {
            uint32_t vertexNumber = 0;
            InitializeMeshData(vertexNumber);
			InitGLBuffers(vertexNumber);
		}
		else
			throw "(Null Exception) Mesh is a null Pointer.";
	}

    void MeshFilter::InitializeMeshData(uint32_t& numOfVert)
    {
        numOfVert = m_Mesh->m_NumOfVert;
        m_IndexCount = (uint32_t)m_Mesh->m_Indices.size();
        indicesData = new GLuint[m_IndexCount];
        for (uint32_t i = 0; i < m_IndexCount; i++) {
            indicesData[i] = m_Mesh->m_Indices[i];
        }

        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);

    }


    void MeshFilter::InitGLBuffers(uint32_t numOfVert)
    {

        UpdateBufferSize();
        BindVertexObjects();
        glVertexAttribPointer( SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glVertexAttribPointer(  SHADER_COLOR_INDEX, 3, GL_FLOAT, GL_FALSE, 0, (void*)(numOfVert * 3 * sizeof(float)));
        glVertexAttribPointer( SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, 0, (void*)(numOfVert * 6 * sizeof(float)));
        glVertexAttribPointer(SHADER_TEXCORD_INDEX, 2, GL_FLOAT, GL_FALSE, 0, (void*)(numOfVert * 9 * sizeof(float)));

        glEnableVertexAttribArray( SHADER_VERTEX_INDEX);
        glEnableVertexAttribArray(  SHADER_COLOR_INDEX);
        glEnableVertexAttribArray( SHADER_NORMAL_INDEX);
        glEnableVertexAttribArray(SHADER_TEXCORD_INDEX);

        SetVertexBufferPositionData(0, numOfVert, &m_Mesh->vertPosition[0]);
        SetVertexBufferColorData   (0, numOfVert, &m_Mesh->vertColor[0]);
        SetVertexBufferNormalData  (0, numOfVert, &m_Mesh->vertNormal[0]);
        SetVertexBufferUVData      (0, numOfVert, &m_Mesh->vertTexCoord[0]);

        m_IBO = new IndexBuffer(indicesData, m_IndexCount);
        UnBindVertexObjects();
    }

    MeshFilter::~MeshFilter()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);

        delete[] indicesData;
        indicesData = nullptr;

        delete m_IBO;
        m_IBO = nullptr;
    }

    void MeshFilter::SetVertexBufferPositionData(const int& offset, const size_t& size, const void* data) const{
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (0 + offset) * m_Mesh->m_NumOfVert, sizeof(GLfloat) * 3 * size, data);
    }

    void MeshFilter::SetVertexBufferColorData(const int &offset, const size_t &size, const void *data) const {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (3 + offset) * m_Mesh->m_NumOfVert, sizeof(GLfloat) * 3 * size, data);
    }

    void MeshFilter::SetVertexBufferNormalData(const int &offset, const size_t &size, const void *data) const {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (3 + 3 + offset) * m_Mesh->m_NumOfVert, sizeof(GLfloat) * 3 * size, data);
    }

    void MeshFilter::SetVertexBufferUVData(const int &offset, const size_t &size, const void *data) const {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (3 + 3 + 3 + offset) * m_Mesh->m_NumOfVert, sizeof(GLfloat) * 3 * size, data);
    }

    void MeshFilter::BindVertexObjects() const {
        glBindVertexArray(m_VAO);
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    }

    void MeshFilter::UnBindVertexObjects() const {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void MeshFilter::UpdateBufferSize() const {
        BindVertexObjects();
        glBufferData(GL_ARRAY_BUFFER, RENDERER_VERTEX_SIZE * m_Mesh->vertPosition.size(), nullptr, GL_DYNAMIC_DRAW);
        UnBindVertexObjects();
    }
}