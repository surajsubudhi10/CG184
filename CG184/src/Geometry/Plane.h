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
        Plane(uint32_t xSeg, uint32_t ySeg);
        Plane(const Plane& plane);
        ~Plane();

    private:
        uint32_t		m_XSegments;
        uint32_t		m_YSegments;

        void			InitMesh() override;
    };
}   // End of CG184


#endif //CGENGINE_PLANE_H
