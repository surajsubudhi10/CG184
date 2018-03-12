#pragma once
#include "Vector3D.h"

namespace CG184 
{
    template <typename T>
    class Vector4
    {
    public:
        static_assert(
            std::is_floating_point<T>::value,
            "Vector only can be instantiated with floating point types");

        T x, y, z, w;

    public:

        //! Constructs default vector (0, 0, 0, 1).
        Vector4();

        //! Set all x, y, z and w components to \p _val.
        Vector4(T _val);

        //! Constructs vector with given parameters \p _x, \p _y, and \p _z.
        Vector4(T _x, T _y, T _z, T _w);

        template <typename U>
        Vector4( Vector3<T>& _vec, U wval);

        //! Copy constructor.
        Vector4(const Vector4& _vec);

        //! Set all x, y, and z to zero.
        void setZero();

        //! Computes this + (v, v, v, v).
        Vector4<T> add(T v) const;

        //! Computes this + (v.x, v.y, v.z, v.w).
        Vector4<T> add(const Vector4& vec) const;

        //! Computes this - (v, v, v, v).
        Vector4<T> sub(T v) const;

        //! Computes this - (v.x, v.y, v.z, v.w).
        Vector4<T> sub(const Vector4& vec) const;

        //! Computes this * (v, v, v, v).
        Vector4<T> mult(T v) const;

        //! Computes this * (v.x, v.y, v.z, v.w).
        Vector4<T> mult(const Vector4& vec) const;

        //! Computes this / (v, v, v, v).
        Vector4<T> divide(T v) const;

        //! Computes this / (v.x, v.y, v.z, v.w).
        Vector4<T> divide(const Vector4& vec) const;

        //! Returns the sum of all the components (i.e. x + y + z).
        T sum() const;

        //! Returns the average of all the components.
        T avg() const;

        //! Returns the minimum value among x, y, and z.
        T min() const;

        //! Returns the maximum value among x, y, and z.
        T max() const;

        //! Returns the length of the vector.
        T length() const;

        //! Returns the squared length of the vector.
        T squaredLength() const;

        //! Returns the distance to the other vector.
        T distanceTo(const Vector4& other) const;

        //! Returns the squared distance to the other vector.
        T distanceSquaredTo(const Vector4& other) const;

        //! Returns a vector with different value type.
        template <typename U>
        Vector4<U> castTo() const;

        //! Returns true if \p other is the same as this vector.
        bool isEqual(const Vector4& other) const;

        //! Set x and y with other vector \p pt.
        Vector4<T>& operator=(const Vector4& v);

        //! Computes this += (v, v)
        Vector4<T>& operator+=(T v);

        //! Computes this += (v.x, v.y)
        Vector4<T>& operator+=(const Vector4& v);

        //! Computes this -= (v, v)
        Vector4<T>& operator-=(T v);

        //! Computes this -= (v.x, v.y)
        Vector4<T>& operator-=(const Vector4& v);

        //! Computes this *= (v, v)
        Vector4<T>& operator*=(T v);

        //! Computes this *= (v.x, v.y)
        Vector4<T>& operator*=(const Vector4& v);

        //! Computes this /= (v, v)
        Vector4<T>& operator/=(T v);

        //! Computes this /= (v.x, v.y)
        Vector4<T>& operator/=(const Vector4& v);

        //! Returns true if \p other is the same as this vector.
        bool operator==(const Vector4& v) const;

        //! Returns true if \p other is the not same as this vector.
        bool operator!=(const Vector4& v) const;

    };

    typedef Vector4<float> Vector4F;

    //! Positive sign operator.
    template <typename T>
    Vector4<T> operator+(const Vector4<T>& a)
    {
        return a;
    }

    //! Negative sign operator.
    template <typename T>
    Vector4<T> operator-(const Vector4<T>& a)
    {
        return Vector4<T>(-a.x, -a.y, -a.z, -a.w);
    }

    //! Computes (a, a, a, a) + (b.x, b.y, b.z, b.w).
    template <typename T>
    Vector4<T> operator+(T a, const Vector4<T>& b)
    {
        return b.add(a);
    }

    //! Computes (a.x, a.y, a.z, a.w) + (b.x, b.y, b.z, b.w).
    template <typename T>
    Vector4<T> operator+(const Vector4<T>& a, const Vector4<T>& b)
    {
        return a.add(b);
    }

    //! Computes (a.x, a.y, a.z, a.w) - (b, b, b, b).
    template <typename T>
    Vector4<T> operator-(const Vector4<T>& a, T b)
    {
        return a.sub(b);
    }

    //! Computes (a, a, a, a) - (b.x, b.y, b.z, b.w).
    template <typename T>
    Vector4<T> operator-(T a, const Vector4<T>& b)
    {
        return -(b.sub(a));
    }

    //! Computes (a.x, a.y, a.z, a.w) - (b.x, b.y, b.z, b.w).
    template <typename T>
    Vector4<T> operator-(const Vector4<T>& a, const Vector4<T>& b)
    {
        return a.sub(b);
    }

    //! Computes (a.x, a.y, a.z, a.w) * (b, b, b, b).
    template <typename T>
    Vector4<T> operator*(const Vector4<T>& a, const T b)
    {
        return a.mult(b);
    }

    //! Computes (a, a, a, a) * (b.x, b.y, b.z, b.w).
    template <typename T>
    Vector4<T> operator*(T a, const Vector4<T>& b)
    {
        return b.mult(a);
    }

    //! Computes (a.x, a.y, a.z, a.w) * (b.x, b.y, b.z, b.w).
    template <typename T>
    Vector4<T> operator*(const Vector4<T>& a, const Vector4<T>& b)
    {
        return a.mult(b);
    }

    //! Computes (a.x, a.y, a.z, a.w) / (b, b, b, b).
    template <typename T>
    Vector4<T> operator/(const Vector4<T>& a, T b)
    {
        return a.divide(b);
    }

    ////! Computes (a, a, a) / (b.x, b.y, b.z).
    //template <typename T>
    //Vector3<T> operator/(T a, const Vector3<T>& b)
    //{
    //    
    //}

    //! Computes (a.x, a.y, a.z, a.w) / (b.x, b.y, b.z, b.w).
    template <typename T>
    Vector4<T> operator/(const Vector4<T>& a, const Vector4<T>& b)
    {
        a.divide(b)
    }


    template <typename T>
    Vector4<T>::Vector4()
    {
        x = 0;
        y = 0;
        z = 0;
        w = 1;
    }

    template <typename T>
    Vector4<T>::Vector4(T _val)
    {
        x = _val;
        y = _val;
        z = _val;
        w = _val;
    }

    template <typename T>
    Vector4<T>::Vector4(T _x, T _y, T _z, T _w)
    {
        x = _x;
        y = _y;
        z = _z;
        w = _w;
    }

    template <typename T>
    template <typename U>
    Vector4<T>::Vector4(Vector3<T>& _vec, U wval)
    {
        x = _vec.x;
        y = _vec.y;
        z = _vec.z;
        w = (T)wval;
    }

    template <typename T>
    Vector4<T>::Vector4(const Vector4& _vec)
    {
        x = _vec.x;
        y = _vec.y;
        z = _vec.z;
        w = _vec.w;
    }

    template <typename T>
    void Vector4<T>::setZero()
    {
        x = y = z = 0;
        w = 1;
    }

    template <typename T>
    Vector4<T> Vector4<T>::add(T v) const {
        return Vector4<T>(x + v, y + v, z + v, w + v);
    }

    template <typename T>
    Vector4<T> Vector4<T>::add(const Vector4& vec) const {
        return Vector4<T>(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
    }

    template <typename T>
    Vector4<T> Vector4<T>::sub(T v) const {
        return Vector4<T>(x - v, y - v, z - v, w - v);
    }

    template <typename T>
    Vector4<T> Vector4<T>::sub(const Vector4& vec) const {
        return Vector4<T>(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
    }

    template <typename T>
    Vector4<T> Vector4<T>::mult(T v) const {
        return Vector4<T>(x * (T)v, y * (T)v, z * (T)v, w * (T)v);
    }

    template <typename T>
    Vector4<T> Vector4<T>::mult(const Vector4& vec) const {
        return Vector3<T>(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
    }

    template <typename T>
    Vector4<T> Vector4<T>::divide(T v) const {
        assert(((T)v != 0) && "Dividing with Zero.");
        return Vector4<T>(x / (T)v, y / (T)v, z / (T)v, w / (T)v);
    }

    template <typename T>
    Vector4<T> Vector4<T>::divide(const Vector4& vec) const {
        assert((vec.x != 0.0 && vec.y != 0.0 && vec.z != 0.0 && vec.w) && "Dividing with Zero.");
        return Vector3<T>(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
    }

    template <typename T>
    T Vector4<T>::sum() const {
        return x + y + z + w;
    }

    template <typename T>
    T Vector4<T>::avg() const {
        return (x + y + z + w) / 4;
    }

    template <typename T>
    T Vector4<T>::min() const {
        return std::min(std::min(std::min(x, y), z), w);
    }

    template <typename T>
    T Vector4<T>::max() const {
        return std::max(std::max(std::max(x, y), z), w);
    }

    template <typename T>
    T Vector4<T>::length() const {
        return std::sqrt(x * x + y * y + z * z + w * w);
    }

    template <typename T>
    T Vector4<T>::squaredLength() const {
        return x * x + y * y + z * z + w * w;
    }

    template <typename T>
    T Vector4<T>::distanceTo(const Vector4<T>& other) const {
        return sub(other).length();
    }

    template <typename T>
    T Vector4<T>::distanceSquaredTo(const Vector4<T>& other) const {
        return sub(other).lengthSquared();
    }

    template <typename T>
    template <typename U>
    Vector4<U> Vector4<T>::castTo() const
    {
        return Vector4<U>(
            static_cast<U>(x),
            static_cast<U>(y),
            static_cast<U>(z),
            static_cast<U>(w));
    }

    template <typename T>
    bool Vector4<T>::isEqual(const Vector4& other) const {
        return x == other.x && y == other.y && z == other.z && w == other.w;
    }

    template <typename T>
    Vector4<T>& Vector4<T>::operator=(const Vector4& v)
    {
        x = v.x; y = v.y; z = v.z; w = v.w;
        return (*this);
    }

    template <typename T>
    Vector4<T>& Vector4<T>::operator+=(T v)
    {
        x += v;
        y += v;
        z += v;
        w += v;
        return (*this);
    }

    template <typename T>
    Vector4<T>& Vector4<T>::operator+=(const Vector4& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        w += v.w;
        return (*this);
    }

    template <typename T>
    Vector4<T>& Vector4<T>::operator-=(T v)
    {
        x -= v;
        y -= v;
        z -= v;
        w -= v;
        return (*this);
    }

    template <typename T>
    Vector4<T>& Vector4<T>::operator-=(const Vector4& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        w -= v.w;
        return (*this);
    }

    template <typename T>
    Vector4<T>& Vector4<T>::operator*=(T v)
    {
        x *= v;
        y *= v;
        z *= v;
        w *= v;
        return (*this);
    }

    template <typename T>
    Vector4<T>& Vector4<T>::operator*=(const Vector4& v)
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;
        w *= v.w;
        return (*this);
    }

    template <typename T>
    Vector4<T>& Vector4<T>::operator/=(T v)
    {
        static_assert((v != 0.0) && "Dividing with Zero.");
        x /= v;
        y /= v;
        z /= v;
        w /= v;
        return (*this);
    }

    template <typename T>
    Vector4<T>& Vector4<T>::operator/=(const Vector4& v)
    {
        static_assert((v.x != 0.0 && v.y != 0.0 && v.z != 0.0 && v.w != 0.0) && "Dividing with Zero.");
        x /= v.x;
        y /= v.y;
        z /= v.z;
        w /= v.w;
        return (*this);
    }

    template <typename T>
    std::ostream&   operator<< (std::ostream& stream, const Vector4<T>& vec)
    {
        stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ", " << vec.w ")" << '\n';
        return stream;
    }
}