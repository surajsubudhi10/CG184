//
// Created by Suraj on 9/12/17.
//

#ifndef CGENGINE_MESHFILTER_H
#define CGENGINE_MESHFILTER_H

#include <GL/glew.h>
#include <vector>

#include "../Graphics/IndexBuffer.h"
#include "Mesh.h"

namespace CG184 
{

#define SHADER_VERTEX_INDEX  0
#define SHADER_COLOR_INDEX	 1
#define SHADER_NORMAL_INDEX	 2
#define SHADER_TEXCORD_INDEX 3
#define RENDERER_VERTEX_SIZE	((3 + 3 + 3 + 2) * sizeof(GLfloat))


    class MeshFilter
    {
    public:
        explicit MeshFilter(Mesh* a_Mesh);
        MeshFilter(const MeshFilter& a_MeshFilter);
        ~MeshFilter();

        inline GLuint&		GetVAO() { return m_VAO;}
        inline IndexBuffer* GetIBO() { return m_IBOPtr;}
        inline uint32_t		GetIndexCount() const { return m_IndexCount;}
		inline Mesh*		GetMesh()		const { return m_MeshPtr; }

        void				SetVertexBufferPositionData(const int& offset, const size_t& size, const void* data) const;
        void				SetVertexBufferColorData   (const int& offset, const size_t& size, const void* data) const;
        void				SetVertexBufferNormalData  (const int& offset, const size_t& size, const void* data) const;
        void				SetVertexBufferUVData      (const int& offset, const size_t& size, const void* data) const;

        void				AttachMesh(Mesh* a_Mesh);
        void				BindVertexObjects()   const;
        void				UnBindVertexObjects() const;
        void				UpdateBufferSize()    const;
        void				UpdateVertexBuffer()  const;

    private:
        GLuint				m_VAO;
        GLuint				m_VBO;
		uint32_t			m_IndexCount;
        
        Mesh*				m_MeshPtr;
        GLuint*				m_IndicesDataPtr;
		IndexBuffer*		m_IBOPtr;
    private:
        void				InitializeMeshData(uint32_t& numOfVert);
        void				InitGLBuffers(uint32_t numOfVert);
        //void				UpdateGLBufferData();
    };
}

#endif //CGENGINE_MESHFILTER_H
