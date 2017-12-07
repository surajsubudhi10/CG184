//
// Created by suraj on 12/8/17.
//

#ifndef CGENGINE_TORUS_H
#define CGENGINE_TORUS_H

#include "Mesh.h"
#include "./../Maths/Maths.h"

namespace CG184 {
    class Torus : public Mesh
    {
    public:
        Torus();
        Torus(const Torus& torus);
        Torus(float tubeRad, float torusRad, unsigned int torusSeg = 10, unsigned int tubeSeg = 10);
        ~Torus();


        inline void SetTubeRadius(float rad){m_TubeRadius = rad;}
        inline void SetTorusRadius(float rad){m_TorusRadius = rad;}
        inline void SetSegments(unsigned int torusSeg, unsigned int tubeSeg){ m_TorusSegments = torusSeg; m_TubeSegments = tubeSeg;}

        inline float GetTubeRadius(){ return  m_TubeRadius;}
        inline float GetTorusRadius(){ return  m_TorusRadius;}

    private:
        void InitMesh() override;

        float m_TubeRadius;
        float m_TorusRadius;

        unsigned int m_TubeSegments;
        unsigned int m_TorusSegments;


    };
}


#endif //CGENGINE_TORUS_H
