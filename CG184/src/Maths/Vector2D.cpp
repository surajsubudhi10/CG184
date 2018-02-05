#include "Vector2D.h"
#include <cassert>
#include <math.h>

namespace CG184
{
    Vector2D::Vector2D() : x(0), y(0)
    {
    }

    Vector2D::~Vector2D()
    {
    }

    Vector2D::Vector2D(float _x, float _y) : x(_x), y(_y)
    {
    }

    Vector2D::Vector2D(float val) : x(val), y(val)
    {
    }

    Vector2D::Vector2D(const Vector2D& _vec) : x(_vec.x), y(_vec.y)
    {
    }

    Vector2D Vector2D::add(const Vector2D& vec) const
    {
        float _x = x + vec.x;
        float _y = y + vec.y;

        return Vector2D(_x, _y);
    }

    Vector2D Vector2D::sub(const Vector2D& vec) const
    {
        float _x = x - vec.x;
        float _y = y - vec.y;

        return Vector2D(_x, _y);
    }

    Vector2D Vector2D::mult(const Vector2D& vec) const
    {
        float _x = x * vec.x;
        float _y = y * vec.y;

        return Vector2D(_x, _y);
    }

    Vector2D Vector2D::divide(const Vector2D& vec) const
    {
        assert((vec.x != 0.0 && vec.y != 0.0 ) && "Dividing with Zero.");

        float _x = x / vec.x;
        float _y = y / vec.y;

        return Vector2D(_x, _y);
    }

    Vector2D Vector2D::mult(float multiplier) const
    {
        float _x = x * multiplier;
        float _y = y * multiplier;

        return Vector2D(_x, _y);
    }

    Vector2D Vector2D::divide(float diveder) const
    {
        assert(diveder != 0.0 && "Dividing with zero.");

        float _x = x / diveder;
        float _y = y / diveder;

        return Vector2D(_x, _y);
    }

    float Vector2D::dot(const Vector2D& vec) const
    {
        return (x * vec.x + y * vec.y);
    }

    float Vector2D::cross(const Vector2D& vec) const
    {
        return (x * vec.y - y * vec.x);
    }

    void Vector2D::normalize()
    {
        float len = length();
        assert(len != 0 && "length must be greater than zero");
        *this = divide(len);
    }

    Vector2D Vector2D::norm() const
    {
        float len = length();
        assert(len != 0 && "length must be greater than zero");

        float _x = x / len;
        float _y = y / len;

        return Vector2D(_x, _y);
    }

    float Vector2D::squaredLength() const
    {
        return (x * x + y * y);
    }

    float Vector2D::length()const
    {
        return sqrt(squaredLength());
    }

    void Vector2D::negate()
    {
        mult(-1.0f);
    }

    const float Vector2D::at(int i) const
    {
        assert((i >= 0 && i < 2) && "i must be between 0 to 1");

        if (i == 0)
            return x;
        else if (i == 1)
            return y;
    }

    float Vector2D::at(int i)
    {
        assert((i >= 0 && i < 2) && "i must be between 0 to 1");

        if (i == 0)
            return x;
        else if (i == 1)
            return y;
    }

    bool Vector2D::isEqual(const Vector2D& vec) const
    {
        if (x == vec.x && y == vec.y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    float Vector2D::operator[](int i) const
    {
        return at(i);
    }

    Vector2D& Vector2D::operator=(const Vector2D& vec)
    {
        if (this == &vec)
            return *this;

        x = vec.x;
        y = vec.y;

        return *this;
    }

    Vector2D   Vector2D::operator+(const Vector2D& vec)
    {
        return add(vec);
    }

    Vector2D   Vector2D::operator-(const Vector2D& vec)
    {
        return sub(vec);
    }

    Vector2D   Vector2D::operator*(const Vector2D& vec)
    {
        return mult(vec);
    }

    Vector2D   Vector2D::operator/(const Vector2D& vec)
    {
        return divide(vec);
    }


    Vector2D   Vector2D::operator*(float val)
    {
        return mult(val);
    }

    Vector2D   Vector2D::operator/(float val)
    {
        return divide(val);
    }

    Vector2D&   Vector2D::operator+=(const Vector2D& vec)
    {
        Vector2D _vec = *this + vec;
        return _vec;
    }

    Vector2D&   Vector2D::operator-=(const Vector2D& vec)
    {
        Vector2D _vec = *this - vec;
        return _vec;
    }

    Vector2D&   Vector2D::operator*=(const Vector2D& vec)
    {
        Vector2D _vec = *this * vec;
        return _vec;
    }

    Vector2D&   Vector2D::operator/=(const Vector2D& vec)
    {
        Vector2D _vec = *this / vec;
        return _vec;
    }
    Vector2D&   Vector2D::operator*=(float val)
    {
        Vector2D _vec = *this * val;
        return _vec;
    }

    Vector2D&   Vector2D::operator/=(float val)
    {
        Vector2D _vec = *this / val;
        return _vec;
    }

    bool		Vector2D::operator==(const Vector2D& vec)
    {
        return isEqual(vec);
    }

    bool		Vector2D::operator!=(const Vector2D& vec)
    {
        return !(isEqual(vec));
    }


    std::ostream& operator<< (std::ostream& stream, const Vector2D& vec){
        stream << "(" << vec.x << ", " << vec.y << ")" << '\n';
        return stream;
    }

}   // End of CG184