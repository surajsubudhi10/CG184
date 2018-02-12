//
// Created by Suraj on 9/12/17.
//

#include <iostream>

#include <Geometry/MeshFilter.h>


namespace CG184
{

    MeshFilter::MeshFilter(Mesh* a_Mesh)
    {
        m_MeshPtr = a_Mesh;
        InitVertexArrayBuffer();
        if(m_MeshPtr != nullptr) {
            uint32_t vertexNumber = 0;
            InitMeshData(vertexNumber);
            InitGLBuffers(vertexNumber);
            InitIndexBuffer();
        } else
            throw "(Null Exception) Mesh is a null Pointer.";
    }

    MeshFilter::MeshFilter(const MeshFilter& a_MeshFilter) : m_MeshPtr(a_MeshFilter.m_MeshPtr)
    {
        InitVertexArrayBuffer();
        if (m_MeshPtr != nullptr) {
            uint32_t vertexNumber = 0;
            InitMeshData(vertexNumber);
            InitGLBuffers(vertexNumber);
            InitIndexBuffer();
        }
        else
            throw "(Null Exception) Mesh is a null Pointer.";
    }

    void MeshFilter::InitMeshData(uint32_t& numOfVert)
    {
        //numOfVert = m_MeshPtr->m_NumOfVert;
        numOfVert = m_MeshPtr->mesh.nVertices();
        std::vector<uint32_t> updatedIndices;
        m_MeshPtr->mesh.GetIndexArray(updatedIndices);
        
        m_IndexCount = (uint32_t)updatedIndices.size();
        //m_IndexCount = (uint32_t)m_MeshPtr->m_Indices.size();
        m_IndicesDataPtr = new GLuint[m_IndexCount];

        for (uint32_t i = 0; i < m_IndexCount; i++) {
            m_IndicesDataPtr[i] = updatedIndices[i];
            //m_IndicesDataPtr[i] = m_MeshPtr->m_Indices[i];
        }
    }


    void MeshFilter::InitGLBuffers(uint32_t& numOfVert)
    {
        UpdateBufferSize();
        BindVertexObjects();
        //uint32_t numOfVert = m_MeshPtr->m_NumOfVert;

        glVertexAttribPointer( SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glVertexAttribPointer(  SHADER_COLOR_INDEX, 3, GL_FLOAT, GL_FALSE, 0, (void*)(numOfVert * 3 * sizeof(float)));
        glVertexAttribPointer( SHADER_NORMAL_INDEX, 3, GL_FLOAT, GL_FALSE, 0, (void*)(numOfVert * 6 * sizeof(float)));
        glVertexAttribPointer(SHADER_TEXCORD_INDEX, 2, GL_FLOAT, GL_FALSE, 0, (void*)(numOfVert * 9 * sizeof(float)));

        glEnableVertexAttribArray( SHADER_VERTEX_INDEX);
        glEnableVertexAttribArray(  SHADER_COLOR_INDEX);
        glEnableVertexAttribArray( SHADER_NORMAL_INDEX);
        glEnableVertexAttribArray(SHADER_TEXCORD_INDEX);

        if (m_MeshPtr->IsDirty()) {
            m_MeshPtr->Update();
        }
        
        if (numOfVert > 0) {
            SetVertexBufferPositionData	(0, numOfVert, &m_MeshPtr->m_VertPosition[0]);
            SetVertexBufferColorData	(0, numOfVert, &m_MeshPtr->m_VertColor[0]);
            SetVertexBufferNormalData	(0, numOfVert, &m_MeshPtr->m_VertNormal[0]);
            SetVertexBufferUVData		(0, numOfVert, &m_MeshPtr->m_VertTexCoord[0]);
        }
    }

    void MeshFilter::InitVertexArrayBuffer()
    {
        glGenVertexArrays(1, &m_VAO);
        glGenBuffers(1, &m_VBO);
    }

    void MeshFilter::InitIndexBuffer()
    {
        BindVertexObjects();
        m_IBOPtr = new IndexBuffer(m_IndicesDataPtr, m_IndexCount);
        UnBindVertexObjects();
    }

    MeshFilter::~MeshFilter()
    {
        glDeleteVertexArrays(1, &m_VAO);
        glDeleteBuffers(1, &m_VBO);

        delete[] m_IndicesDataPtr;
        m_IndicesDataPtr = nullptr;

        delete m_IBOPtr;
        m_IBOPtr = nullptr;
    }

    void MeshFilter::SetVertexBufferPositionData(const int& offset, const size_t& size, const void* data) const{
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (0 + offset) * m_MeshPtr->m_NumOfVert, sizeof(GLfloat) * 3 * size, data);
    }

    void MeshFilter::SetVertexBufferColorData(const int &offset, const size_t &size, const void *data) const {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (3 + offset) * m_MeshPtr->m_NumOfVert, sizeof(GLfloat) * 3 * size, data);
    }

    void MeshFilter::SetVertexBufferNormalData(const int &offset, const size_t &size, const void *data) const {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (3 + 3 + offset) * m_MeshPtr->m_NumOfVert, sizeof(GLfloat) * 3 * size, data);
    }

    void MeshFilter::SetVertexBufferUVData(const int &offset, const size_t &size, const void *data) const {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat) * (3 + 3 + 3 + offset) * m_MeshPtr->m_NumOfVert, sizeof(GLfloat) * 3 * size, data);
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
        glBufferData(GL_ARRAY_BUFFER, RENDERER_VERTEX_SIZE * m_MeshPtr->m_NumOfVert, nullptr, GL_DYNAMIC_DRAW);
        UnBindVertexObjects();
    }

    void MeshFilter::UpdateVertexBuffer() const {
        if(m_MeshPtr->IsDirty()){
            uint32_t numOfVert = m_MeshPtr->m_NumOfVert;
            if (numOfVert > 0) {
                SetVertexBufferPositionData	(0, numOfVert, &m_MeshPtr->m_VertPosition[0]);
                SetVertexBufferColorData	(0, numOfVert, &m_MeshPtr->m_VertColor[0]);
                SetVertexBufferNormalData	(0, numOfVert, &m_MeshPtr->m_VertNormal[0]);
                SetVertexBufferUVData		(0, numOfVert, &m_MeshPtr->m_VertTexCoord[0]);
            }
            m_MeshPtr->m_IsDirty = false;
        }
    }

    void MeshFilter::AttachMesh(Mesh* a_Mesh)
    {
        if (m_MeshPtr != nullptr)
        {
            if(m_MeshPtr->IsDirty())
            {
                if (m_MeshPtr->m_NumOfVert != a_Mesh->m_NumOfVert)
                {
                    //m_MeshPtr->m_NumOfVert = a_Mesh->m_NumOfVert;

                    /*m_IndexCount = (uint32_t) a_Mesh->m_Indices.size();
                    delete[] m_IndicesDataPtr;
                    
                    m_IndicesDataPtr = new GLuint[m_IndexCount];
                    for (uint32_t i = 0; i < m_IndexCount; i++) {
                        m_IndicesDataPtr[i] = a_Mesh->m_Indices[i];
                    }
*/

                    uint32_t numOfVert = a_Mesh->mesh.nVertices();
                    m_MeshPtr->m_NumOfVert = numOfVert;

                    std::vector<uint32_t> updatedIndices;
                    a_Mesh->mesh.GetIndexArray(updatedIndices);

                    m_IndexCount = (uint32_t)updatedIndices.size();
                    m_IndicesDataPtr = new GLuint[m_IndexCount];

                    for (uint32_t i = 0; i < m_IndexCount; i++) {
                        m_IndicesDataPtr[i] = updatedIndices[i];
                    }

                    InitGLBuffers(numOfVert);
                    m_IBOPtr->AddIndexBufferData(m_IndicesDataPtr, m_IndexCount);
                }

            }

        }
        
        m_MeshPtr = a_Mesh;
    }
}   // End of CG184