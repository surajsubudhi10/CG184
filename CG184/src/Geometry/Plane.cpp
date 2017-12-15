//
// Created by suraj on 12/7/17.
//

#include "Plane.h"


namespace CG184{

    Plane::Plane(): Mesh(), m_XSegments(10), m_YSegments(10)
    {
        InitMesh();
    }

    Plane::Plane(uint32_t xSeg, uint32_t ySeg): Mesh(), m_XSegments(xSeg), m_YSegments(ySeg)
    {
        InitMesh();
    }

    Plane::Plane(const Plane &plane): Mesh(), m_XSegments(plane.m_XSegments), m_YSegments(plane.m_YSegments)
    {
        InitMesh();
    }

    Plane::~Plane() {

    }

    void Plane::InitMesh()
    {
        std::vector<Vector3D> positions;
        std::vector<Vector2D> texCoord;
        std::vector<Vector3D> normals;
        std::vector<uint32_t> indicies;

		uint32_t numOfVert = (m_XSegments + 1) * (m_YSegments + 1);


        float dX = 1.0f / m_XSegments;
        float dY = 1.0f / m_YSegments;

        for (uint32_t y = 0; y <= m_YSegments; ++y)
        {
            for (uint32_t x = 0; x <= m_XSegments; ++x)
            {
                positions.emplace_back(dX * x * 2.0f - 1.0f, dY * y * 2.0f - 1.0f, 0);
                texCoord.emplace_back(dX * x, 1.0f - y * dY);
                normals.emplace_back(0.0f, 0.0f, 1.0f);
            }
        }

        int maxIndex = -1;
		uint32_t index = 0;
        while(maxIndex != numOfVert - 1)
        {
            if(index % (m_XSegments + 1) != m_XSegments) {
                indicies.push_back(index + 1);
                indicies.push_back(index);
                indicies.push_back(index + m_XSegments + 1);

                indicies.push_back(index + 1);
                indicies.push_back(index + m_XSegments + 1);
                indicies.push_back(index + m_XSegments + 2);

                maxIndex = index + m_XSegments + 2;
            }
            index++;
        }

        SetPositions(positions);
        SetUVs(texCoord);
        SetNormals(normals);
        SetIndicies(indicies);
    }
}