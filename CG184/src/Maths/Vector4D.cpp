//#include <Maths/Vector4D.h>
//#include <cassert>
//#include <math.h>
//
//#if OLD_IMP == 0
//
//
//namespace CG184
//{
//    Vector4D::Vector4D() : x(0), y(0), z(0)
//    {
//    }
//
//    Vector4D::~Vector4D()
//    {
//    }
//
//    Vector4D::Vector4D(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z), w(_w)
//    {
//    }
//
//    Vector4D::Vector4D(float val) : x(val), y(val), z(val), w(val)
//    {
//    }
//
//    Vector4D::Vector4D(const Vector4D& _vec) : x(_vec.x), y(_vec.y), z(_vec.z), w(_vec.w)
//    {
//    }
//
//    Vector4D::Vector4D(const Vector3F& _vec, float wval) : x(_vec.x), y(_vec.y), z(_vec.z), w(wval)
//    {
//    }
//
//    Vector4D Vector4D::add(const Vector4D& vec) const
//    {
//        float _x = x + vec.x;
//        float _y = y + vec.y;
//        float _z = z + vec.z;
//        float _w = w + vec.w;
//
//        return Vector4D(_x, _y, _z, _w);
//    }
//
//    Vector4D Vector4D::sub(const Vector4D& vec) const
//    {
//        float _x = x - vec.x;
//        float _y = y - vec.y;
//        float _z = z - vec.z;
//        float _w = w - vec.w;
//
//        return Vector4D(_x, _y, _z, _w);
//    }
//
//    Vector4D Vector4D::mult(const Vector4D& vec) const
//    {
//        float _x = x * vec.x;
//        float _y = y * vec.y;
//        float _z = z * vec.z;
//        float _w = w * vec.w;
//
//        return Vector4D(_x, _y, _z, _w);
//    }
//
//    Vector4D Vector4D::divide(const Vector4D& vec) const
//    {
//        assert((vec.x != 0.0 && vec.y != 0.0 && vec.z != 0.0 && vec.w != 0.0) && "Dividing with Zero.");
//
//        float _x = x / vec.x;
//        float _y = y / vec.y;
//        float _z = z / vec.z;
//        float _w = w / vec.w;
//
//        return Vector4D(_x, _y, _z, _w);
//    }
//
//    Vector4D Vector4D::mult(float multiplier) const
//    {
//        float _x = x * multiplier;
//        float _y = y * multiplier;
//        float _z = z * multiplier;
//        float _w = w * multiplier;
//
//        return Vector4D(_x, _y, _z, _w);
//    }
//
//    Vector4D Vector4D::divide(float diveder) const
//    {
//        assert(diveder != 0.0 && "Dividing with zero.");
//
//        float _x = x / diveder;
//        float _y = y / diveder;
//        float _z = z / diveder;
//        float _w = w / diveder;
//
//        return Vector4D(_x, _y, _z, _w);
//    }
//
//    const float Vector4D::at(int i) const
//    {
//        assert((i >= 0 && i < 4) && "i must be between 0 to 3");
//
//        if (i == 0)
//            return x;
//        else if (i == 1)
//            return y;
//        else if (i == 2)
//            return z;
//        else
//            return w;
//    }
//
//    float Vector4D::at(int i)
//    {
//        assert((i >= 0 && i < 4) && "i must be between 0 to 3");
//
//        if (i == 0)
//            return x;
//        else if (i == 1)
//            return y;
//        else if (i == 2)
//            return z;
//        else
//            return w;
//    }
//
//    bool Vector4D::isEqual(const Vector4D& vec) const
//    {
//        return (x == vec.x && y == vec.y && z == vec.z && w == vec.w);
//    }
//
//
//    float		Vector4D::operator[](int i) const
//    {
//        return at(i);
//    }
//
//    Vector4D&	Vector4D::operator=(const Vector4D& vec)
//    {
//        if (this == &vec)
//            return *this;
//
//        x = vec.x;
//        y = vec.y;
//        z = vec.z;
//        w = vec.w;
//
//        return *this;
//    }
//
//    Vector4D   Vector4D::operator+(const Vector4D& vec)
//    {
//        return add(vec);
//    }
//
//    Vector4D   Vector4D::operator-(const Vector4D& vec)
//    {
//        return sub(vec);
//    }
//
//    Vector4D   Vector4D::operator*(const Vector4D& vec)
//    {
//        return mult(vec);
//    }
//
//    Vector4D   Vector4D::operator/(const Vector4D& vec)
//    {
//        return divide(vec);
//    }
//
//
//    Vector4D   Vector4D::operator*(float val)
//    {
//        return mult(val);
//    }
//
//    Vector4D   Vector4D::operator/(float val)
//    {
//        return divide(val);
//    }
//
//    Vector4D&   Vector4D::operator+=(const Vector4D& vec)
//    {
//        *this = add(vec);
//        return *this;
//    }
//
//    Vector4D&   Vector4D::operator-=(const Vector4D& vec)
//    {
//        *this = sub(vec);
//        return *this;
//    }
//
//    Vector4D&   Vector4D::operator*=(const Vector4D& vec)
//    {
//        *this = mult(vec);
//        return *this;
//    }
//
//    Vector4D&   Vector4D::operator/=(const Vector4D& vec)
//    {
//        *this = divide(vec);
//        return *this;
//    }
//
//    Vector4D&   Vector4D::operator*=(float val)
//    {
//        *this = mult(val);
//        return *this;
//    }
//
//    Vector4D&   Vector4D::operator/=(float val)
//    {
//        *this = divide(val);
//        return *this;;
//    }
//
//    bool		Vector4D::operator==(const Vector4D& vec)
//    {
//        return isEqual(vec);
//    }
//
//    bool		Vector4D::operator!=(const Vector4D& vec)
//    {
//        return !(isEqual(vec));
//    }
//
//    std::ostream& operator<< (std::ostream& stream, const Vector4D& vec){
//        stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w << ")" << '\n';
//        return stream;
//    }
//
//}   // End of CG184
//
//
//#endif
