#pragma once

#include <cmath>

#include "Vector2D.h"
#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix4D.h"

namespace CG184 {

#define PI           3.14159265358979323846  /* pi */
#define TWO_PI        (2.0 * PI)

    typedef Vector3D Color;

    static Color WHITE  = Vector3D(1, 1, 1);
    static Color BLACK  = Vector3D(0, 0, 0);
    static Color GREY   = Vector3D(0.5, 0.5, 0.5);
    static Color RED    = Vector3D(1, 0, 0);
    static Color GREEN  = Vector3D(0, 1, 0);
    static Color BLUE   = Vector3D(0, 0, 1);


}