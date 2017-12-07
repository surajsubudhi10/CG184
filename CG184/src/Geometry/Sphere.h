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
        Sphere(float rad, unsigned int xSeg, unsigned int ySeg);
        ~Sphere();

        void SetRadius(float rad);
        void SetSegments(unsigned int xSeg, unsigned int ySeg);

    private:
        float radius;
        unsigned int x_segments;
        unsigned int y_segments;

        void InitMesh() override;
    };
}


#endif //CGENGINE_SPHERE_H
