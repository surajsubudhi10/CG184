#pragma once

#include <ostream>

namespace CG184
{
    template <typename T>
    class Vector2
    {
    public:
        static_assert(
            std::is_floating_point<T>::value,
            "Vector only can be instantiated with floating point types");

        T x, y;

    public:

        //! Constructs default vector (0, 0).
        Vector2();

        //! Set all x and y components to \p _val.
        Vector2(T _val);

        //! Constructs vector with given parameters \p _x, \p _y.
        Vector2(T _x, T _y);

        //! Copy constructor.
        Vector2(const Vector2& _vec);

        //! Set all x, y to zero.
        void setZero();

        //! Normalizes this vector.
        void normalize();

        //! Computes this + (v, v).
        Vector2<T> add(T v) const;

        //! Computes this + (v.x, v.y).
        Vector2<T> add(const Vector2& vec) const;

        //! Computes this - (v, v).
        Vector2<T> sub(T v) const;

        //! Computes this - (v.x, v.y).
        Vector2<T> sub(const Vector2& vec) const;

        //! Computes this * (v, v).
        Vector2<T> mult(T v) const;

        //! Computes this * (v.x, v.y).
        Vector2<T> mult(const Vector2& vec) const;

        //! Computes this / (v, v).
        Vector2<T> divide(T v) const;

        //! Computes this / (v.x, v.y).
        Vector2<T> divide(const Vector2& vec) const;

        //! Computes dot product.
        T dot(const Vector2& v) const;

        //! Comptues cross product.
        float cross(const Vector2& v) const;

        //! Returns const reference to the \p i -th element of the vector.
        const T& at(size_t i) const;

        //! Returns reference to the \p i -th element of the vector.
        T& at(size_t i);

        //! Returns the sum of all the components (i.e. x + y).
        T sum() const;

        //! Returns the average of all the components.
        T avg() const;

        //! Returns the minimum value among x, y.
        T min() const;

        //! Returns the maximum value among x, y.
        T max() const;

        //! Returns normalized vector.
        Vector2<T> norm() const;

        //! Returns the length of the vector.
        T length() const;

        //! Returns the squared length of the vector.
        T squaredLength() const;

        //! Returns the distance to the other vector.
        T distanceTo(const Vector2& other) const;

        //! Returns the squared distance to the other vector.
        T distanceSquaredTo(const Vector2& other) const;

        //! Returns a vector with different value type.
        template <typename U>
        Vector2<U> castTo() const;

        //! Returns true if \p other is the same as this vector.
        bool isEqual(const Vector2& other) const;

        //! Set x and y with other vector \p pt.
        Vector2<T>& operator=(const Vector2& v);

        //! Computes this += (v, v)
        Vector2<T>& operator+=(T v);

        //! Computes this += (v.x, v.y)
        Vector2<T>& operator+=(const Vector2& v);

        //! Computes this -= (v, v)
        Vector2<T>& operator-=(T v);

        //! Computes this -= (v.x, v.y)
        Vector2<T>& operator-=(const Vector2& v);

        //! Computes this *= (v, v)
        Vector2<T>& operator*=(T v);

        //! Computes this *= (v.x, v.y)
        Vector2<T>& operator*=(const Vector2& v);

        //! Computes this /= (v, v)
        Vector2<T>& operator/=(T v);

        //! Computes this /= (v.x, v.y)
        Vector2<T>& operator/=(const Vector2& v);

        //! Returns true if \p other is the same as this vector.
        bool operator==(const Vector2& v) const;

        //! Returns true if \p other is the not same as this vector.
        bool operator!=(const Vector2& v) const;

    };

    typedef Vector2<float> Vector2F;

    
    //! Positive sign operator.
    template <typename T>
    Vector2<T> operator+(const Vector2<T>& a)
    {
        return a;
    }

    //! Negative sign operator.
    template <typename T>
    Vector2<T> operator-(const Vector2<T>& a)
    {
        return Vector2<T>(-a.x, -a.y);
    }

    //! Computes (a, a) + (b.x, b.y).
    template <typename T>
    Vector2<T> operator+(T a, const Vector2<T>& b)
    {
        return b.add(a);
    }

    //! Computes (a.x, a.y) + (b.x, b.y).
    template <typename T>
    Vector2<T> operator+(const Vector2<T>& a, const Vector2<T>& b)
    {
        return a.add(b);
    }

    //! Computes (a.x, a.y) - (b, b).
    template <typename T>
    Vector2<T> operator-(const Vector2<T>& a, T b)
    {
        return a.sub(b);
    }

    //! Computes (a, a) - (b.x, b.y).
    template <typename T>
    Vector2<T> operator-(T a, const Vector2<T>& b)
    {
        return -(b.sub(a));
    }

    //! Computes (a.x, a.y) - (b.x, b.y).
    template <typename T>
    Vector2<T> operator-(const Vector2<T>& a, const Vector2<T>& b)
    {
        return a.sub(b);
    }

    //! Computes (a.x, a.y) * (b, b).
    template <typename T>
    Vector2<T> operator*(const Vector2<T>& a, const T b)
    {
        return a.mult(b);
    }

    //! Computes (a, a) * (b.x, b.y).
    template <typename T>
    Vector2<T> operator*(T a, const Vector2<T>& b)
    {
        return b.mult(a);
    }

    //! Computes (a.x, a.y) * (b.x, b.y).
    template <typename T>
    Vector2<T> operator*(const Vector2<T>& a, const Vector2<T>& b)
    {
        return a.mult(b);
    }

    //! Computes (a.x, a.y) / (b, b).
    template <typename T>
    Vector2<T> operator/(const Vector2<T>& a, T b)
    {
        return a.divide(b);
    }

    ////! Computes (a, a) / (b.x, b.y).
    //template <typename T>
    //Vector2<T> operator/(T a, const Vector2<T>& b)
    //{
    //    
    //}

    //! Computes (a.x, a.y) / (b.x, b.y).
    template <typename T>
    Vector2<T> operator/(const Vector2<T>& a, const Vector2<T>& b)
    {
        a.divide(b)
    }


    template <typename T>
    Vector2<T>::Vector2()
    {
        x = 0;
        y = 0;
    }

    template <typename T>
    Vector2<T>::Vector2(T _val)
    {
        x = _val;
        y = _val;
    }

    template <typename T>
    Vector2<T>::Vector2(T _x, T _y)
    {
        x = _x;
        y = _y;
    }

    template <typename T>
    Vector2<T>::Vector2(const Vector2& _vec)
    {
        x = _vec.x;
        y = _vec.y;
    }

    template <typename T>
    void Vector2<T>::setZero()
    {
        x = y = 0;
    }

    template <typename T>
    void Vector2<T>::normalize()
    {
        T l = length();
        assert(l != 0);

        x /= l;
        y /= l;
    }

    template <typename T>
    Vector2<T> Vector2<T>::add(T v) const {
        return Vector2<T>(x + v, y + v);
    }

    template <typename T>
    Vector2<T> Vector2<T>::add(const Vector2& vec) const {
        return Vector2<T>(x + vec.x, y + vec.y);
    }

    template <typename T>
    Vector2<T> Vector2<T>::sub(T v) const {
        return Vector2<T>(x - v, y - v);
    }

    template <typename T>
    Vector2<T> Vector2<T>::sub(const Vector2& vec) const {
        return Vector2<T>(x - vec.x, y - vec.y);
    }

    template <typename T>
    Vector2<T> Vector2<T>::mult(T v) const {
        return Vector2<T>(x * (T)v, y * (T)v);
    }

    template <typename T>
    Vector2<T> Vector2<T>::mult(const Vector2& vec) const {
        return Vector2<T>(x * vec.x, y * vec.y);
    }

    template <typename T>
    Vector2<T> Vector2<T>::divide(T v) const {
        assert(((T)v != 0) && "Dividing with Zero.");
        return Vector2<T>(x / (T)v, y / (T)v);
    }

    template <typename T>
    Vector2<T> Vector2<T>::divide(const Vector2& vec) const {
        assert((vec.x != 0.0 && vec.y != 0.0) && "Dividing with Zero.");
        return Vector2<T>(x / vec.x, y / vec.y);
    }

    template <typename T>
    T Vector2<T>::dot(const Vector2& v) const
    {
        return x * v.x + y * v.y;
    }

    template <typename T>
    float Vector2<T>::cross(const Vector2& v) const
    {
        return (x * v.y - y * v.x);
    }

    template <typename T>
    const T& Vector2<T>::at(size_t i) const {
        assert(i < 2);

        if (i == 0)
            return x;
        else if (i == 1)
            return y;
        
    }

    template <typename T>
    T& Vector2<T>::at(size_t i) {
        assert(i < 2);

        if (i == 0)
            return x;
        else if (i == 1)
            return y;
    }

    template <typename T>
    T Vector2<T>::sum() const {
        return x + y;
    }

    template <typename T>
    T Vector2<T>::avg() const {
        return (x + y) / 2;
    }

    template <typename T>
    T Vector2<T>::min() const {
        return std::min(x, y);
    }

    template <typename T>
    T Vector2<T>::max() const {
        return std::max(x, y);
    }

    template <typename T>
    Vector2<T> Vector2<T>::norm() const {
        T l = length();
        assert(l != 0);
        return Vector2<T>(x / l, y / l);
    }

    template <typename T>
    T Vector2<T>::length() const {
        return std::sqrt(x * x + y * y);
    }

    template <typename T>
    T Vector2<T>::squaredLength() const {
        return x * x + y * y;
    }

    template <typename T>
    T Vector2<T>::distanceTo(const Vector2<T>& other) const {
        return sub(other).length();
    }

    template <typename T>
    T Vector2<T>::distanceSquaredTo(const Vector2<T>& other) const {
        return sub(other).lengthSquared();
    }

    template <typename T>
    template <typename U>
    Vector2<U> Vector2<T>::castTo() const
    {
        return Vector2<U>(
            static_cast<U>(x),
            static_cast<U>(y));
    }

    template <typename T>
    bool Vector2<T>::isEqual(const Vector2& other) const {
        return x == other.x && y == other.y;
    }

    template <typename T>
    Vector2<T>& Vector2<T>::operator=(const Vector2& v)
    {
        x = v.x; y = v.y;
        return (*this);
    }

    template <typename T>
    Vector2<T>& Vector2<T>::operator+=(T v)
    {
        x += v;
        y += v;

        return (*this);
    }

    template <typename T>
    Vector2<T>& Vector2<T>::operator+=(const Vector2& v)
    {
        x += v.x;
        y += v.y;

        return (*this);
    }

    template <typename T>
    Vector2<T>& Vector2<T>::operator-=(T v)
    {
        x -= v;
        y -= v;

        return (*this);
    }

    template <typename T>
    Vector2<T>& Vector2<T>::operator-=(const Vector2& v)
    {
        x -= v.x;
        y -= v.y;

        return (*this);
    }

    template <typename T>
    Vector2<T>& Vector2<T>::operator*=(T v)
    {
        x *= v;
        y *= v;

        return (*this);
    }

    template <typename T>
    Vector2<T>& Vector2<T>::operator*=(const Vector2& v)
    {
        x *= v.x;
        y *= v.y;

        return (*this);
    }

    template <typename T>
    Vector2<T>& Vector2<T>::operator/=(T v)
    {
        static_assert((v != 0.0) && "Dividing with Zero.");
        x /= v;
        y /= v;

        return (*this);
    }

    template <typename T>
    Vector2<T>& Vector2<T>::operator/=(const Vector2& v)
    {
        static_assert((v.x != 0.0 && v.y != 0.0) && "Dividing with Zero.");
        x /= v.x;
        y /= v.y;

        return (*this);
    }

    template <typename T>
    std::ostream&   operator<< (std::ostream& stream, const Vector2<T>& vec)
    {
        stream << "(" << vec.x << ", " << vec.y ")" << '\n';
        return stream;
    }

    template <typename T>
    float  Cross(const Vector2<T>& vec1, const Vector2<T>& vec2)
    {
        return (vec1.x * vec2.y) - (vec1.y * vec2.x);
    }

    template <typename T>
    float Dot(const Vector2<T>& vec1, const Vector2<T>& vec2)
    {
        return (vec1.x * vec1.x + vec1.y * vec1.y);
    }

} // End of CG184
