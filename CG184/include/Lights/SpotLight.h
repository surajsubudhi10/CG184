//
// Created by Suraj Subudhi.
//

#ifndef CGENGINE_SPOTLIGHT_H
#define CGENGINE_SPOTLIGHT_H

#include "Light.h"

namespace CG184 
{
    class SpotLight : public Light
    {
    public:
        SpotLight();
        SpotLight(const SpotLight& spotLight);
        SpotLight(Vector3F pos, Vector3F dir);
        ~SpotLight();
    private:
        Vector3F m_Direction;
    };
}   // End of CG184


#endif //CGENGINE_SPOTLIGHT_H
