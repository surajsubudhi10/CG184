//
// Created by suraj on 12/7/17.
//

#ifndef CGENGINE_SPHERE_H
#define CGENGINE_SPHERE_H

#include "Mesh.h"

namespace CG184 {
    class Sphere : public Mesh
    {
    public:
        Sphere();
        Sphere(Sphere& a_Sphere);
        Sphere(float rad, uint32_t xSeg, uint32_t ySeg);
        ~Sphere();

        void SetRadius(float rad);
        void SetSegments(uint32_t xSeg, uint32_t ySeg);

    private:
        float radius;
		uint32_t x_segments;
		uint32_t y_segments;

        void InitMesh() override;
    };
}


#endif //CGENGINE_SPHERE_H
