//
// Created by suraj on 12/8/17.
//

#include "Torus.h"


namespace CG184
{
    Torus::Torus() :
            Mesh(),
            m_TubeRadius(2.0f), m_TorusRadius(5.0f),
            m_TubeSegments(10), m_TorusSegments(10)
    {
        InitMesh();
    }

    Torus::Torus(const Torus &torus) :
            Mesh(),
            m_TubeRadius(torus.m_TubeRadius), m_TorusRadius(torus.m_TorusRadius),
            m_TubeSegments(torus.m_TubeSegments), m_TorusSegments(torus.m_TorusSegments)
    {
        InitMesh();
    }

    Torus::Torus(float tubeRad, float torusRad, uint32_t torusSeg, uint32_t tubeSeg):
            Mesh(),
            m_TubeRadius(tubeRad), m_TorusRadius(torusRad),
            m_TubeSegments(tubeSeg), m_TorusSegments(torusSeg)
    {
        InitMesh();
    }

    Torus::~Torus() 
    {}

    void Torus::InitMesh()
    {
        // Taken Form Cell Graphics engine
        std::vector<Vector3D> positions((m_TorusSegments + 1) * (m_TubeSegments + 1));
        std::vector<Vector2D> texCoord((m_TorusSegments + 1) * (m_TubeSegments + 1));
        std::vector<Vector3D> normals((m_TorusSegments + 1) * (m_TubeSegments + 1));
        std::vector<uint32_t> indicies(m_TorusSegments * m_TubeSegments * 6);

        std::vector<Vector3D> p(m_TorusSegments + 1);
        float a = 0.0f;
        auto step = (float)(2.0f * PI / m_TorusSegments);
        for (uint32_t i = 0; i <= m_TorusSegments; ++i)
        {
            float x = std::cos(a) * m_TorusRadius;
            float y = std::sin(a) * m_TorusRadius;
            p[i].x = x;
            p[i].y = y;
            p[i].z = 0.0f;
            a += step;
        }

        // generate all the vertices, UVs, Normals (and Tangents/Bitangents):
        for (uint32_t i = 0; i <= m_TorusSegments; ++i)
        {
            // the basis vectors of the ring equal the difference  vector between the minorRing
            // center and the donut's center position (which equals the origin (0, 0, 0)) and the
            // positive z-axis.
            Vector3D u			= (Vector3D(0.0f) - p[i]).norm() * m_TubeRadius; // Could be p[i] also
            Vector3D v			=  Vector3D(0.0f, 0.0f, 1.0f) * m_TubeRadius;

            // create the vertices of each minor ring segment:
            auto a = 0.0f;
            auto step = static_cast<float>(2.0f * PI / m_TubeSegments);
            for (uint32_t j = 0; j <= m_TubeSegments; ++j)
            {
                auto c = (float)cos(a);
                auto s = (float)sin(a);

                positions[i * (m_TubeSegments + 1) + j]		= p[i] + (u * c) + (v * s);
                texCoord [i * (m_TubeSegments + 1) + j].x	= ((float)i) / ((float)m_TorusSegments) * (float)TWO_PI;
                texCoord [i * (m_TubeSegments + 1) + j].y	= ((float)j) / ((float)m_TubeSegments);
                normals  [i * (m_TubeSegments + 1) + j]		= ((u * c) + (v * s)).norm();
                a += step;
            }
        }

        int index = 0;
        for (uint32_t i = 0; i < m_TorusSegments; ++i)
        {
            int i1 = i;
            int i2 = (i1 + 1);

            for (uint32_t j = 0; j < m_TubeSegments; ++j)
            {
                int j1 = j;
                int j2 = (j1 + 1);

                indicies[index++] = i1 * (m_TubeSegments + 1) + j1;
                indicies[index++] = i1 * (m_TubeSegments + 1) + j2;
                indicies[index++] = i2 * (m_TubeSegments + 1) + j1;

                indicies[index++] = i2 * (m_TubeSegments + 1) + j2;
                indicies[index++] = i2 * (m_TubeSegments + 1) + j1;
                indicies[index++] = i1 * (m_TubeSegments + 1) + j2;
            }
        }

        SetPositions(positions);
        SetNormals(normals);
        SetUVs(texCoord);
        SetIndicies(indicies);
    }
}   // End of CG184