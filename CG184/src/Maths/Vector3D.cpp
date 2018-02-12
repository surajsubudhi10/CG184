#include <Maths/Vector3D.h>
#include <cassert>
#include <math.h>

namespace CG184 
{

    const Vector3D Vector3D::Up      = Vector3D(0.0, 1.0, 0.0);
    const Vector3D Vector3D::Right   = Vector3D(1.0, 0.0, 0.0);
    const Vector3D Vector3D::Forward = Vector3D(0.0, 0.0, 1.0);

    Vector3D::Vector3D() : x(0), y(0), z(0)
    {
    }

    Vector3D::~Vector3D()
    {
    }

    Vector3D::Vector3D(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
    {
    }

    Vector3D::Vector3D(float val) : x(val), y(val), z(val)
    {
    }

    Vector3D::Vector3D(const Vector3D& _vec) : x(_vec.x), y(_vec.y), z(_vec.z)
    {
    }

    Vector3D Vector3D::add(const Vector3D& vec) const
    {
        float _x = x + vec.x;
        float _y = y + vec.y;
        float _z = z + vec.z;

        return Vector3D(_x, _y, _z);
    }

    Vector3D Vector3D::sub(const Vector3D& vec) const
    {
        float _x = x - vec.x;
        float _y = y - vec.y;
        float _z = z - vec.z;

        return Vector3D(_x, _y, _z);
    }

    Vector3D Vector3D::mult(const Vector3D& vec) const
    {
        float _x = x * vec.x;
        float _y = y * vec.y;
        float _z = z * vec.z;

        return Vector3D(_x, _y, _z);
    }

    Vector3D Vector3D::divide(const Vector3D& vec) const
    {
        assert((vec.x != 0.0 && vec.y != 0.0 && vec.z != 0.0) && "Dividing with Zero.");

        float _x = x / vec.x;
        float _y = y / vec.y;
        float _z = z / vec.z;

        return Vector3D(_x, _y, _z);
    }

    Vector3D Vector3D::mult(float multiplier) const
    {
        float _x = x * multiplier;
        float _y = y * multiplier;
        float _z = z * multiplier;

        return Vector3D(_x, _y, _z);
    }

    Vector3D Vector3D::divide(float diveder) const
    {
        assert(diveder != 0.0 && "Dividing with zero.");

        float _x = x / diveder;
        float _y = y / diveder;
        float _z = z / diveder;

        return Vector3D(_x, _y, _z);
    }

    float Vector3D::dot(const Vector3D& vec) const 
    {
        return (x * vec.x + y * vec.y + z * vec.z);
    }

    Vector3D Vector3D::cross(const Vector3D& vec) const 
    {
        float _x = (y * vec.z) - (z * vec.y);
        float _y = (z * vec.x) - (x * vec.z);
        float _z = (x * vec.y) - (y * vec.x);

        return Vector3D(_x, _y, _z);
    }

    void Vector3D::normalize() 
    {
        float len = length();
        assert(len != 0 && "length must be greater than zero");
        *this = divide(len);
    }

    Vector3D Vector3D::norm() const
    {
        float len = length();
        assert(len != 0 && "length must be greater than zero");

        float _x = x / len;
        float _y = y / len;
        float _z = z / len;

        return Vector3D(_x, _y, _z);
    }

    float Vector3D::squaredLength() const 
    {
        return (x * x + y * y + z * z);
    }

    float Vector3D::length()const 
    {
        return sqrt(squaredLength());
    }

    void Vector3D::negate() 
    {
        mult(-1.0f);
    }

    const float Vector3D::at(int i) const
    {
        assert((i >= 0 && i < 3) && "i must be between 0 to 2");

        if (i == 0)
            return x;
        else if (i == 1)
            return y;
        else
            return z;
    }

    float Vector3D::at(int i)
    {
        assert((i >= 0 && i < 3) && "i must be between 0 to 2");

        if (i == 0)
            return x;
        else if (i == 1)
            return y;
        else
            return z;
    }

    bool Vector3D::isEqual(const Vector3D& vec) const
    {
        if (x == vec.x && y == vec.y && z == vec.z) 
        {
            return true;
        }
        else
        {
            return false;
        }
    }


    float		Vector3D::operator[](int i) const
    {
        return at(i);
    }

    Vector3D&	Vector3D::operator=(const Vector3D& vec) 
    {
        if (this == &vec)
            return *this;

        x = vec.x;
        y = vec.y;
        z = vec.z;

        return *this;
    }

    Vector3D   Vector3D::operator+(const Vector3D& vec)
    {
        return add(vec);
    }

    Vector3D   Vector3D::operator-(const Vector3D& vec)
    {
        return sub(vec);
    }

    Vector3D   Vector3D::operator*(const Vector3D& vec)
    {
        return mult(vec);
    }

    Vector3D   Vector3D::operator/(const Vector3D& vec)
    {
        return divide(vec);
    }


    Vector3D   Vector3D::operator*(float val)
    {
        return mult(val);
    }

    Vector3D    Vector3D::operator*(float val) const{
        return mult(val);
    }

    Vector3D   Vector3D::operator/(float val)
    {
        return divide(val);
    }

    Vector3D&   Vector3D::operator+=(const Vector3D& vec) 
    {
        Vector3D _vec = *this + vec;
        return _vec;
    }

    Vector3D&   Vector3D::operator-=(const Vector3D& vec) 
    {
        Vector3D _vec = *this - vec;
        return _vec;
    }

    Vector3D&   Vector3D::operator*=(const Vector3D& vec) 
    {
        Vector3D _vec = *this * vec;
        return _vec;
    }

    Vector3D&   Vector3D::operator/=(const Vector3D& vec) 
    {
        Vector3D _vec = *this / vec;
        return _vec;
    }
    Vector3D&   Vector3D::operator*=(float val) 
    {
        Vector3D _vec = *this * val;
        return _vec;
    }

    Vector3D&   Vector3D::operator/=(float val) 
    {
        Vector3D _vec = *this / val;
        return _vec;
    }

    bool		Vector3D::operator==(const Vector3D& vec) 
    {
        return isEqual(vec);
    }

    bool		Vector3D::operator!=(const Vector3D& vec) 
    {
        return !(isEqual(vec));
    }

    std::ostream& operator<< (std::ostream& stream, const Vector3D& vec)
    {
        stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << '\n';
        return stream;
    }

    Vector3D Cross(const Vector3D& vec1, const Vector3D& vec2)
    {
        float _x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
        float _y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
        float _z = (vec1.x * vec2.y) - (vec1.y * vec2.x);

        return Vector3D(_x, _y, _z);
    }

    float Dot(const Vector3D& vec1, const Vector3D& vec2)
    {
        return (vec1.x * vec1.x + vec1.y * vec1.y + vec1.z * vec1.z);
    }

}   // End of CG184