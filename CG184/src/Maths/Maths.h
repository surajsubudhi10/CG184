#pragma once

#include <cmath>

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix4D.h"

namespace CG184 {

#define PI           3.14159265358979323846  /* pi */
#define TWO_PI        (2.0 * PI)

    static float ToRadian(const float angleInDeg) {
        return angleInDeg * static_cast<float>(PI / 180.0);
    }

    static float ToDegrees(const float angleInRad) {
        return angleInRad * static_cast<float>(180.0 / PI);
    }

    typedef Vector4D Color;

    static Color WHITE  = Vector4D(1, 1, 1, 1);
    static Color BLACK  = Vector4D(0, 0, 0, 1);
    static Color GREY   = Vector4D(0.5, 0.5, 0.5, 1.0);
    static Color RED    = Vector4D(1, 0, 0, 1);
    static Color GREEN  = Vector4D(0, 1, 0, 1);
    static Color BLUE   = Vector4D(0, 0, 1, 1);


}