#pragma once
#include "Vector3D.h"

namespace CG184
{
    // TODO Create Template classes for Vector4D
    class Vector4D
    {
    public:
        Vector4D();
        Vector4D(float _x, float _y, float _Z, float _w);
        explicit Vector4D(float val);
        Vector4D(const Vector4D& _vec);
        Vector4D(const Vector3D& _vec, float wval);

        Vector4D add(const Vector4D& vec) const;
        Vector4D sub(const Vector4D& vec) const;
        Vector4D mult(const Vector4D& vec) const;
        Vector4D divide(const Vector4D& vec) const;

        Vector4D mult(float multiplier) const;
        Vector4D divide(float divisor)const ;

        const float at(int i) const;
        float at(int i);

        bool isEqual(const Vector4D& vec) const;

        float		operator[](int i) const;
        Vector4D&	operator=(const Vector4D& vec);
        Vector4D   operator+(const Vector4D& vec);
        Vector4D   operator-(const Vector4D& vec);
        Vector4D   operator*(const Vector4D& vec);
        Vector4D   operator/(const Vector4D& vec);
        Vector4D   operator*(float val);
        Vector4D   operator/(float val);
        Vector4D&   operator+=(const Vector4D& vec);
        Vector4D&   operator-=(const Vector4D& vec);
        Vector4D&   operator*=(const Vector4D& vec);
        Vector4D&   operator/=(const Vector4D& vec);
        Vector4D&   operator*=(float val);
        Vector4D&   operator/=(float val);
        bool		operator==(const Vector4D& vec);
        bool		operator!=(const Vector4D& vec);


        ~Vector4D();

    public:
        float x, y, z, w;
    };

    std::ostream& operator<< (std::ostream& stream, const Vector4D& vec);

}   // End of CG184
