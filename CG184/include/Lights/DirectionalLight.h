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
        DirectionalLight(Vector3F pos, Vector3F dir);
        ~DirectionalLight() override ;

        inline Vector3F			GetDirection(){ return m_Direction;}
        inline void				SetDirection(const Vector3F& dir){m_Direction = dir;}

    private:
        Vector3F				m_Direction;
    };
}   // End of CG184


#endif //CGENGINE_DIRECTIONALLIGHT_H
