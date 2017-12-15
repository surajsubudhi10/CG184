//
// Created by Suraj on 9/12/17.
//

#ifndef CGENGINE_MESHFILTER_H
#define CGENGINE_MESHFILTER_H

#include <GL/glew.h>
#include <vector>
#include "../Graphics/IndexBuffer.h"

#include "Mesh.h"

namespace CG184 {

#define SHADER_VERTEX_INDEX  0
#define SHADER_COLOR_INDEX	 1
#define SHADER_NORMAL_INDEX	 2
#define SHADER_TEXCORD_INDEX 3
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)


    class MeshFilter
    {
    public:
        explicit MeshFilter(Mesh& a_Mesh);
        ~MeshFilter();


        inline GLuint& GetVAO() { return m_VAO;}
        inline IndexBuffer* GetIBO() { return m_IBO;}
        inline uint32_t GetIndexCount() const { return m_IndexCount;}

    private:
        GLuint m_VAO;
        GLuint m_VBO;
        IndexBuffer* m_IBO;

        GLuint* indicesData;
        VertexData* m_Buffer;
		uint32_t m_IndexCount;

        Mesh* m_Mesh;
    private:
        void InitGLBuffers(uint32_t numOfVert, uint32_t indicesNum);
    };
}

#endif //CGENGINE_MESHFILTER_H
