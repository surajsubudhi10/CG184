//
// Created by Suraj Subudhi.
//

#ifndef CGENGINE_DIRECTIONALLIGHT_H
#define CGENGINE_DIRECTIONALLIGHT_H

#include "Light.h"

namespace CG184 
{
    class DirectionalLight : public Light
    {
    public:
        DirectionalLight();
        DirectionalLight(const DirectionalLight& directionalLight);
        DirectionalLight(Vector3D pos, Vector3D dir);
        ~DirectionalLight() override ;

        inline Vector3D			GetDirection(){ return m_Direction;}
        inline void				SetDirection(const Vector3D& dir){m_Direction = dir;}

    private:
        Vector3D				m_Direction;
    };
}   // End of CG184


#endif //CGENGINE_DIRECTIONALLIGHT_H
