//
// Created by suraj on 12/5/17.
//

#include "Light.h"


namespace CG184{

    Light::Light():
        position(Vector3D()), color(BLACK)
    {}

    Light::Light(Vector3D &lightPos, Color &lightCol):
        position(lightPos), color(lightCol)
    {}

    Light::Light(const Light &light):
        position(light.position), color(light.color)
    {}

    Light::~Light() = default;
}