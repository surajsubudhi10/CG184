//
// Created by suraj on 12/7/17.
//

#ifndef CGENGINE_PLANE_H
#define CGENGINE_PLANE_H


#include "Mesh.h"

namespace CG184 {
    class Plane : public Mesh
    {
    public:
        Plane();
        Plane(unsigned int xSeg, unsigned  int ySeg);
        Plane(const Plane& plane);
        ~Plane();

    private:
        unsigned int m_XSegments;
        unsigned int m_YSegments;

        void InitMesh() override;
    };
}


#endif //CGENGINE_PLANE_H
