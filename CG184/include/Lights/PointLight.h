//
// Created by Suraj Subudhi.
//

#ifndef CGENGINE_POINTLIGHT_H
#define CGENGINE_POINTLIGHT_H

#include "Light.h"

namespace CG184 
{
    class PointLight : public Light
    {
    public:
        PointLight();
        PointLight(const PointLight& pointLight);
        ~PointLight() override;

        void SetAttenuation(float constant, float linear, float quad) { m_Attenuation = Vector3F(constant, linear, quad); }

    private:
    };
}   // End of CG184


#endif //CGENGINE_POINTLIGHT_H
