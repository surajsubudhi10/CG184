//
// Created by suraj on 12/7/17.
//

#include <cmath>
#include "Sphere.h"
#include "../Maths/Maths.h"

namespace CG184 {
    Sphere::Sphere() : Mesh(), radius(5.0f), x_segments(20), y_segments(20)
    {
        InitMesh();
    }

    Sphere::Sphere(Sphere &a_Sphere) :
            Mesh(), radius(a_Sphere.radius),
            x_segments(a_Sphere.x_segments),
            y_segments(a_Sphere.y_segments)
    {
        InitMesh();
    }

    Sphere::Sphere(float rad, uint32_t xSeg, uint32_t ySeg):
            Mesh(), radius(rad),
            x_segments(xSeg),
            y_segments(ySeg)
    {
        InitMesh();
    }

    void Sphere::SetRadius(float rad)
    {
        radius = rad;
    }

    void Sphere::SetSegments(uint32_t xSeg, uint32_t ySeg)
    {
        x_segments = xSeg;
        y_segments = ySeg;
    }

    Sphere::~Sphere()
    {}

    void Sphere::InitMesh()
    {
        std::vector<Vector3D> positions;
        std::vector<Vector2D> texCoord;
        std::vector<Vector3D> normals;
        std::vector<uint32_t> indicies;

        for (uint32_t y = 0; y <= y_segments; ++y)
        {
            for (uint32_t x = 0; x <= x_segments; ++x)
            {
                float xSegment = (float)x / (float)y_segments;
                float ySegment = (float)y / (float)y_segments;
                auto xPos = static_cast<float >(radius * std::cos(xSegment * TWO_PI) * std::sin(ySegment * PI)); // TAU is 2PI
                auto yPos = static_cast<float >(radius * std::cos(ySegment * PI));
                auto zPos = static_cast<float >(radius * std::sin(xSegment * TWO_PI) * std::sin(ySegment * PI));


                positions.emplace_back(xPos, yPos, zPos);
                texCoord.emplace_back(xSegment, ySegment);
                normals.emplace_back(xPos, yPos, zPos);
            }
        }

        for (uint32_t y = 0; y < y_segments; ++y)
        {
            for (uint32_t x = 0; x < x_segments; ++x)
            {
                indicies.push_back((y + 1) * (x_segments + 1) + x);
                indicies.push_back(y       * (x_segments + 1) + x);
                indicies.push_back(y       * (x_segments + 1) + x + 1);

                indicies.push_back((y + 1) * (x_segments + 1) + x);
                indicies.push_back(y       * (x_segments + 1) + x + 1);
                indicies.push_back((y + 1) * (x_segments + 1) + x + 1);
            }
        }


        SetPositions(positions);
        SetNormals(normals);
        SetUVs(texCoord);
        SetIndicies(indicies);
    }


}
