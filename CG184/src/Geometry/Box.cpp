//
// Created by suraj on 12/6/17.
//

#include "Box.h"

namespace CG184 {

    Box::Box() : Mesh(), m_Width(1.0f), m_Height(1.0f), m_Depth(1.0f)
    {
        InitMesh();
    }

    Box::Box(Box &a_Box): Mesh(), m_Width(a_Box.m_Width), m_Height(a_Box.m_Height), m_Depth(a_Box.m_Depth)
    {
        InitMesh();
    }

    Box::Box(float width, float height, float depth) : Mesh(), m_Width(width), m_Height(height), m_Depth(depth)
    {
        InitMesh();
    }

    void Box::InitMesh()
    {

        float X = m_Width  / 2.0f;
        float Y = m_Height / 2.0f;
        float Z = m_Depth  / 2.0f;

        std::vector<Vector3D> vertPos {
                Vector3D(-X, -Y, -Z), Vector3D( X, -Y, -Z), Vector3D( X,  Y, -Z),
                Vector3D( X,  Y, -Z), Vector3D(-X,  Y, -Z), Vector3D(-X, -Y, -Z),

                Vector3D(-X, -Y,  Z), Vector3D( X, -Y,  Z), Vector3D( X,  Y,  Z),
                Vector3D( X,  Y,  Z), Vector3D(-X,  Y,  Z), Vector3D(-X, -Y,  Z),

                Vector3D(-X,  Y,  Z), Vector3D(-X,  Y, -Z), Vector3D(-X, -Y, -Z),
                Vector3D(-X, -Y, -Z), Vector3D(-X, -Y,  Z), Vector3D(-X,  Y,  Z),

                Vector3D(X,  Y,  Z),  Vector3D(X,  Y, -Z),  Vector3D(X, -Y, -Z),
                Vector3D(X, -Y, -Z),  Vector3D(X, -Y,  Z),  Vector3D(X,  Y,  Z),

                Vector3D(-X, -Y, -Z), Vector3D( X, -Y, -Z), Vector3D( X, -Y,  Z),
                Vector3D( X, -Y,  Z), Vector3D(-X, -Y,  Z), Vector3D(-X, -Y, -Z),

                Vector3D(-X,  Y, -Z), Vector3D( X,  Y, -Z), Vector3D( X,  Y,  Z),
                Vector3D( X,  Y,  Z), Vector3D(-X,  Y,  Z), Vector3D(-X,  Y, -Z),
        };

        // Indices
        std::vector<GLuint> vertIndices {
                0,   1,  2,  3,   4,  5,
                6,   7,  8,  9,  10, 11,
                12, 13, 14,  15, 16, 17,
                18, 19, 20,  21, 22, 23,
                24, 25, 26,  27, 28, 29,
                30, 31, 32,  33, 34, 35
        };

        // Normal Data
        std::vector<Vector3D> vertNorm {
                Vector3D(  0.0f,  0.0f, -1.0f), Vector3D(  0.0f,  0.0f, -1.0f), Vector3D(  0.0f,  0.0f, -1.0f),
                Vector3D(  0.0f,  0.0f, -1.0f), Vector3D(  0.0f,  0.0f, -1.0f), Vector3D(  0.0f,  0.0f, -1.0f),
                Vector3D(  0.0f,  0.0f,  1.0f), Vector3D(  0.0f,  0.0f,  1.0f), Vector3D(  0.0f,  0.0f,  1.0f),
                Vector3D(  0.0f,  0.0f,  1.0f), Vector3D(  0.0f,  0.0f,  1.0f), Vector3D(  0.0f,  0.0f,  1.0f),
                Vector3D( -1.0f,  0.0f,  0.0f), Vector3D( -1.0f,  0.0f,  0.0f), Vector3D( -1.0f,  0.0f,  0.0f),
                Vector3D( -1.0f,  0.0f,  0.0f), Vector3D( -1.0f,  0.0f,  0.0f), Vector3D( -1.0f,  0.0f,  0.0f),
                Vector3D(  1.0f,  0.0f,  0.0f), Vector3D(  1.0f,  0.0f,  0.0f), Vector3D(  1.0f,  0.0f,  0.0f),
                Vector3D(  1.0f,  0.0f,  0.0f), Vector3D(  1.0f,  0.0f,  0.0f), Vector3D(  1.0f,  0.0f,  0.0f),
                Vector3D(  0.0f, -1.0f,  0.0f), Vector3D(  0.0f, -1.0f,  0.0f), Vector3D(  0.0f, -1.0f,  0.0f),
                Vector3D(  0.0f, -1.0f,  0.0f), Vector3D(  0.0f, -1.0f,  0.0f), Vector3D(  0.0f, -1.0f,  0.0f),
                Vector3D(  0.0f,  1.0f,  0.0f), Vector3D(  0.0f,  1.0f,  0.0f), Vector3D(  0.0f,  1.0f,  0.0f),
                Vector3D(  0.0f,  1.0f,  0.0f), Vector3D(  0.0f,  1.0f,  0.0f), Vector3D(  0.0f,  1.0f,  0.0f)
        };

        SetPositions(vertPos);
		SetColor(Vector3D(0.5f, 0.5f, 0.5f));
        SetNormals(vertNorm);
        SetIndicies(vertIndices);
		
    }

    Box::~Box()
    {
    }


}
