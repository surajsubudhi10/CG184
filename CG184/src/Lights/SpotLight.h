//
// Created by Suraj Subudhi.
//

#ifndef CGENGINE_SPOTLIGHT_H
#define CGENGINE_SPOTLIGHT_H

#include "Light.h"

namespace CG184 {
    class SpotLight : public Light
    {
    public:
        SpotLight();
        SpotLight(const SpotLight& spotLight);
        SpotLight(Vector3D pos, Vector3D dir);
        ~SpotLight();
    private:
        Vector3D m_Direction;
    };
}


#endif //CGENGINE_SPOTLIGHT_H
