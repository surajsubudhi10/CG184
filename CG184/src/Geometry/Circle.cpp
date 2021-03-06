//
// Created by suraj on 12/7/17.
//

#include <cmath>
#include <Geometry/Circle.h>
#include <Maths/Maths.h>

namespace CG184 
{
    Circle::Circle() 
        : Mesh(), m_Radius(2.0f), m_EdgeSegments(10)
    {
        InitMesh();
    }

    Circle::Circle(Circle &cir)  
        : Mesh(), m_Radius(cir.m_Radius), m_EdgeSegments(cir.m_EdgeSegments)
    {
        InitMesh();
    }

    Circle::Circle(float rad, uint32_t seg)
        : Mesh(), m_Radius(rad), m_EdgeSegments(seg)
    {
        InitMesh();
    }

    void Circle::InitMesh()
    {
        std::vector<Vector3F> positions;
        std::vector<Vector2F> texCoord;
        std::vector<Vector3F> normals;
        std::vector<uint32_t> indicies;

        // TODO Complete the circle mesh (we need only edge segments and radius)
        // Center Point
        positions.emplace_back(0, 0, 0);
        normals.emplace_back(0, 0, 1);

        for (uint32_t i = 0; i <= m_EdgeSegments; ++i)
        {
            float edgeSegment	= (float)i / (float)m_EdgeSegments;
            auto xPos			= static_cast<float>(m_Radius * std::cos(edgeSegment * TWO_PI));
            auto yPos			= static_cast<float>(m_Radius * std::sin(edgeSegment * TWO_PI));

            positions.emplace_back(xPos, yPos, 0);
            normals.emplace_back(0, 0, 1);
//                texCoord.emplace_back(xSegment, ySegment);
        }

        for(uint32_t i = 1; i <= m_EdgeSegments; i++)
        {
            if(i == m_EdgeSegments) 
            {
                indicies.push_back(0);
                indicies.push_back(i);
                indicies.push_back(1);
            }
            else
            {
                indicies.push_back(0);
                indicies.push_back(i);
                indicies.push_back(i + 1);
            }
        }

        SetPositions(positions);
        SetNormals(normals);
        SetIndicies(indicies);
    }


    Circle::~Circle() {}
}   // End of CG184
