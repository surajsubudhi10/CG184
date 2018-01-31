//
// Created by suraj on 12/8/17.
//

#ifndef CGENGINE_TORUS_H
#define CGENGINE_TORUS_H

#include "Mesh.h"
#include "./../Maths/Maths.h"

namespace CG184 
{
    class Torus : public Mesh
    {
    public:
        Torus();
        Torus(const Torus& torus);
        Torus(float tubeRad, float torusRad, uint32_t torusSeg = 10, uint32_t tubeSeg = 10);
        ~Torus();

        inline void			SetTubeRadius	(float rad){m_TubeRadius = rad;}
        inline void			SetTorusRadius	(float rad){m_TorusRadius = rad;}
        inline void			SetSegments		(uint32_t torusSeg, uint32_t tubeSeg){ m_TorusSegments = torusSeg; m_TubeSegments = tubeSeg;}

        inline float		GetTubeRadius()  const { return  m_TubeRadius;}
        inline float		GetTorusRadius() const { return  m_TorusRadius;}

    private:
        void				InitMesh() override;

        float				m_TubeRadius;
        float				m_TorusRadius;
        uint32_t			m_TubeSegments;
        uint32_t			m_TorusSegments;
    };
}


#endif //CGENGINE_TORUS_H
