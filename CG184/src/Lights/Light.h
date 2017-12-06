//
// Created by suraj on 12/5/17.
//

#ifndef CGENGINE_LIGHT_H
#define CGENGINE_LIGHT_H

#include "../Maths/Vector3D.h"
#include "../Maths/Maths.h"

namespace CG184 {
    class Light {

    public:
        Light();
        Light(const Light& light);
        Light(Vector3D& lightPos, Color& lightCol);
        ~Light();

        Vector3D position;
        Vector3D color;
    };
}


#endif //CGENGINE_LIGHT_H
