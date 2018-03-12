//
// Created by suraj on 12/7/17.
//

#include <cmath>

#include <Geometry/Sphere.h>
#include <Maths/Maths.h>

namespace CG184 
{
    Sphere::Sphere() : Mesh(), m_Radius(5.0f), m_XSegments(20), m_YSegments(20)
    {
        InitMesh();
    }

    Sphere::Sphere(Sphere &a_Sphere) :
            Mesh(), m_Radius(a_Sphere.m_Radius),
            m_XSegments(a_Sphere.m_XSegments),
            m_YSegments(a_Sphere.m_YSegments)
    {
        InitMesh();
    }

    Sphere::Sphere(float rad, uint32_t xSeg, uint32_t ySeg):
            Mesh(), m_Radius(rad),
            m_XSegments(xSeg),
            m_YSegments(ySeg)
    {
        InitMesh();
    }

    void Sphere::SetRadius(float rad)
    {
        m_Radius = rad;
    }

    void Sphere::SetSegments(uint32_t xSeg, uint32_t ySeg)
    {
        m_XSegments = xSeg;
        m_YSegments = ySeg;
    }

    Sphere::~Sphere()
    {}

    void Sphere::InitMesh()
    {
        std::vector<Vector3F> positions;
        std::vector<Vector2F> texCoord;
        std::vector<Vector3F> normals;
        std::vector<uint32_t> indicies;

        for (uint32_t y = 0; y <= m_YSegments; ++y)
        {
            for (uint32_t x = 0; x <= m_XSegments; ++x)
            {
                float xSegment = (float)x / (float)m_YSegments;
                float ySegment = (float)y / (float)m_YSegments;
                auto xPos = static_cast<float >(m_Radius * std::cos(xSegment * TWO_PI) * std::sin(ySegment * PI)); // TAU is 2PI
                auto yPos = static_cast<float >(m_Radius * std::cos(ySegment * PI));
                auto zPos = static_cast<float >(m_Radius * std::sin(xSegment * TWO_PI) * std::sin(ySegment * PI));


                positions.emplace_back(xPos, yPos, zPos);
                texCoord.emplace_back(xSegment, ySegment);
                normals.emplace_back(xPos, yPos, zPos);
            }
        }

        for (uint32_t y = 0; y < m_YSegments; ++y)
        {
            for (uint32_t x = 0; x < m_XSegments; ++x)
            {
                indicies.push_back((y + 1) * (m_XSegments + 1) + x);
                indicies.push_back(y       * (m_XSegments + 1) + x);
                indicies.push_back(y       * (m_XSegments + 1) + x + 1);
                                              
                indicies.push_back((y + 1) * (m_XSegments + 1) + x);
                indicies.push_back(y       * (m_XSegments + 1) + x + 1);
                indicies.push_back((y + 1) * (m_XSegments + 1) + x + 1);
            }
        }

        SetPositions(positions);
        SetNormals(normals);
        SetUVs(texCoord);
        SetIndicies(indicies);
    }
}   // End of CG184
