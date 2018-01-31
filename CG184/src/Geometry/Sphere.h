//
// Created by suraj on 12/7/17.
//

#ifndef CGENGINE_SPHERE_H
#define CGENGINE_SPHERE_H

#include "Mesh.h"

namespace CG184 
{
    class Sphere : public Mesh
    {
    public:
        Sphere();
        Sphere(Sphere& a_Sphere);
        Sphere(float rad, uint32_t xSeg, uint32_t ySeg);
        ~Sphere();

        void			SetRadius(float rad);
        void			SetSegments(uint32_t xSeg, uint32_t ySeg);

    private:
        float			m_Radius;
		uint32_t		m_XSegments;
		uint32_t		m_YSegments;

        void			InitMesh() override;
    };
}


#endif //CGENGINE_SPHERE_H
