//
// Created by suraj on 12/2/17.
//

#include <cassert>
#include "Mesh.h"

namespace CG184
{
    Mesh::Mesh(std::vector<Vector3D> a_Pos, std::vector<unsigned int>a_Ind)
    {
        m_NumOfVert = (unsigned int)a_Pos.size();
        m_Indices = std::move(a_Ind);

        vertices = new VertexData[m_NumOfVert];

        for(auto i = 0; i < m_NumOfVert; i++){
            vertices->position      = a_Pos[i];
            vertices->color         = Vector3D(0.5, 0.5, 0.5);
            vertices->normal        = Vector3D(0, 0, 0);
            vertices->texCoord      = Vector2D();
            vertices++;
        }
        vertices -= m_NumOfVert;
    }

    Mesh::Mesh(std::vector<VertexData> a_Vertices, std::vector<unsigned int> a_Ind)
    {
        m_NumOfVert = (unsigned int)a_Vertices.size();
        m_Indices = std::move(a_Ind);

        vertices = new VertexData[m_NumOfVert];

        for(auto i = 0; i < m_NumOfVert; i++){
            vertices->position      = a_Vertices[i].position;
            vertices->color         = a_Vertices[i].color;
            vertices->normal        = a_Vertices[i].normal;
            vertices->texCoord      = a_Vertices[i].texCoord;
            vertices++;
        }
        vertices -= m_NumOfVert;
    }

    void Mesh::SetPositions(std::vector<Vector3D> a_Positions)
    {
        assert(a_Positions.size() == m_NumOfVert);
        for(auto i = 0; i < m_NumOfVert; i++){
            vertices->position = a_Positions[i];
            vertices++;
        }
        vertices -= m_NumOfVert;
    }

    void Mesh::SetColors(std::vector<Vector3D> a_Colors)
    {
        assert(a_Colors.size() == m_NumOfVert);
        for(auto i = 0; i < m_NumOfVert; i++){
            vertices->color = a_Colors[i];
            vertices++;
        }
        vertices -= m_NumOfVert;
    }

    void Mesh::SetColor(Vector3D a_Color)
    {
        for(auto i = 0; i < m_NumOfVert; i++){
            vertices->color = a_Color;
            vertices++;
        }
        vertices -= m_NumOfVert;
    }

    void Mesh::SetNormals(std::vector<Vector3D> a_Normals)
    {
        assert(a_Normals.size() == m_NumOfVert);
        for(auto i = 0; i < m_NumOfVert; i++){
            vertices->normal = a_Normals[i];
            vertices++;
        }
        vertices -= m_NumOfVert;
    }

    void Mesh::SetUVs(std::vector<Vector2D> a_UV)
    {
        assert(a_UV.size() == m_NumOfVert);
        for(auto i = 0; i < m_NumOfVert; i++){
            vertices->texCoord = a_UV[i];
            vertices++;
        }
        vertices -= m_NumOfVert;
    }

    Mesh::~Mesh()
    {
        delete[] vertices;
        vertices = nullptr;
    }



}