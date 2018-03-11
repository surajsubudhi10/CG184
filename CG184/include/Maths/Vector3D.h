#pragma once

#include <ostream>
#include <cassert>

namespace CG184
{
    template <typename T>
    class Vector3 
    {
    public:
        static_assert(
        std::is_floating_point<T>::value,
        "Vector only can be instantiated with floating point types");

        T x, y, z;
        
    public:
        
        //! Constructs default vector (0, 0, 0).
        Vector3();

        //! Set all x, y, and z components to \p _val.
        Vector3(T _val);

        //! Constructs vector with given parameters \p _x, \p _y, and \p _z.
        Vector3(T _x, T _y, T _z);
      
        //! Copy constructor.
        Vector3(const Vector3& _vec);

        //! Set all x, y, and z to zero.
        void setZero();

        //! Normalizes this vector.
        void normalize();

        //! Computes this + (v, v, v).
        Vector3<T> add(T v) const;

        //! Computes this + (v.x, v.y, v.z).
        Vector3<T> add(const Vector3& vec) const;
        
        //! Computes this - (v, v, v).
        Vector3<T> sub(T v) const;

        //! Computes this - (v.x, v.y, v.z).
        Vector3<T> sub(const Vector3& vec) const;

        //! Computes this * (v, v, v).
        Vector3<T> mult(T v) const;

        //! Computes this * (v.x, v.y, v.z).
        Vector3<T> mult(const Vector3& vec) const;

        //! Computes this / (v, v, v).
        Vector3<T> divide(T v) const;

        //! Computes this / (v.x, v.y, v.z).
        Vector3<T> divide(const Vector3& vec) const;

        //! Computes dot product.
        T dot(const Vector3& v) const;

        //! Comptues cross product.
        Vector3<T> cross(const Vector3& v) const;

        //! Returns const reference to the \p i -th element of the vector.
        const T& at(size_t i) const;

        //! Returns reference to the \p i -th element of the vector.
        T& at(size_t i);

        //! Returns the sum of all the components (i.e. x + y + z).
        T sum() const;

        //! Returns the average of all the components.
        T avg() const;

        //! Returns the minimum value among x, y, and z.
        T min() const;

        //! Returns the maximum value among x, y, and z.
        T max() const;

        //! Returns normalized vector.
        Vector3<T> norm() const;

        //! Returns the length of the vector.
        T length() const;

        //! Returns the squared length of the vector.
        T squaredLength() const;

        //! Returns the distance to the other vector.
        T distanceTo(const Vector3& other) const;

        //! Returns the squared distance to the other vector.
        T distanceSquaredTo(const Vector3& other) const;

        //! Returns a vector with different value type.
        template <typename U>
        Vector3<U> castTo() const;

        //! Returns true if \p other is the same as this vector.
        bool isEqual(const Vector3& other) const;

        //! Set x and y with other vector \p pt.
        Vector3<T>& operator=(const Vector3& v);

        //! Computes this += (v, v)
        Vector3<T>& operator+=(T v);

        //! Computes this += (v.x, v.y)
        Vector3<T>& operator+=(const Vector3& v);

        //! Computes this -= (v, v)
        Vector3<T>& operator-=(T v);

        //! Computes this -= (v.x, v.y)
        Vector3<T>& operator-=(const Vector3& v);

        //! Computes this *= (v, v)
        Vector3<T>& operator*=(T v);

        //! Computes this *= (v.x, v.y)
        Vector3<T>& operator*=(const Vector3& v);

        //! Computes this /= (v, v)
        Vector3<T>& operator/=(T v);

        //! Computes this /= (v.x, v.y)
        Vector3<T>& operator/=(const Vector3& v);

        //! Returns true if \p other is the same as this vector.
        bool operator==(const Vector3& v) const;

        //! Returns true if \p other is the not same as this vector.
        bool operator!=(const Vector3& v) const;


        const static Vector3<T> Up;     
        const static Vector3<T> Right;  
        const static Vector3<T> Forward;
    };

    typedef Vector3<float> Vector3F;

    template <typename T>
    const Vector3<T> Vector3<T>::Up      = Vector3F(0.0, 1.0, 0.0);

    template <typename T>
    const Vector3<T> Vector3<T>::Right   = Vector3F(1.0, 0.0, 0.0);

    template <typename T>
    const Vector3<T> Vector3<T>::Forward = Vector3F(0.0, 0.0, 1.0);

    //! Positive sign operator.
    template <typename T>
    Vector3<T> operator+(const Vector3<T>& a) 
    {
        return a;
    }
    
    //! Negative sign operator.
    template <typename T>
    Vector3<T> operator-(const Vector3<T>& a) 
    {
        return Vector3<T>(-a.x, -a.y, -a.z);
    }

    //! Computes (a, a, a) + (b.x, b.y, b.z).
    template <typename T>
    Vector3<T> operator+(T a, const Vector3<T>& b)
    {
        return b.add(a);
    }

    //! Computes (a.x, a.y, a.z) + (b.x, b.y, b.z).
    template <typename T>
    Vector3<T> operator+(const Vector3<T>& a, const Vector3<T>& b)
    {
        return a.add(b);
    }

    //! Computes (a.x, a.y, a.z) - (b, b, b).
    template <typename T>
    Vector3<T> operator-(const Vector3<T>& a, T b)
    {
        return a.sub(b);
    }

    //! Computes (a, a, a) - (b.x, b.y, b.z).
    template <typename T>
    Vector3<T> operator-(T a, const Vector3<T>& b)
    {
        return -(b.sub(a));
    }

    //! Computes (a.x, a.y, a.z) - (b.x, b.y, b.z).
    template <typename T>
    Vector3<T> operator-(const Vector3<T>& a, const Vector3<T>& b)
    {
        return a.sub(b);
    }

    //! Computes (a.x, a.y, a.z) * (b, b, b).
    template <typename T>
    Vector3<T> operator*(const Vector3<T>& a, const T b)
    {
        return a.mult(b);
    }

    //! Computes (a, a, a) * (b.x, b.y, b.z).
    template <typename T>
    Vector3<T> operator*(T a, const Vector3<T>& b)
    {
        return b.mult(a);
    }

    //! Computes (a.x, a.y, a.z) * (b.x, b.y, b.z).
    template <typename T>
    Vector3<T> operator*(const Vector3<T>& a, const Vector3<T>& b)
    {
        return a.mult(b);
    }

    //! Computes (a.x, a.y, a.z) / (b, b, b).
    template <typename T>
    Vector3<T> operator/(const Vector3<T>& a, T b)
    {
        return a.divide(b);
    }

    ////! Computes (a, a, a) / (b.x, b.y, b.z).
    //template <typename T>
    //Vector3<T> operator/(T a, const Vector3<T>& b)
    //{
    //    
    //}

    //! Computes (a.x, a.y, a.z) / (b.x, b.y, b.z).
    template <typename T>
    Vector3<T> operator/(const Vector3<T>& a, const Vector3<T>& b)
    {
        a.divide(b)
    }


    template <typename T>
    Vector3<T>::Vector3() 
    {
        x = 0;
        y = 0;
        z = 0;
    }

    template <typename T>
    Vector3<T>::Vector3(T _val) 
    {
        x = _val;
        y = _val;
        z = _val;
    }

    template <typename T>
    Vector3<T>::Vector3(T _x, T _y, T _z) 
    {
        x = _x;
        y = _y;
        z = _z;
    }
    
    template <typename T>
    Vector3<T>::Vector3(const Vector3& _vec) 
    {
        x = _vec.x;
        y = _vec.y;
        z = _vec.z;
    }

    template <typename T>
    void Vector3<T>::setZero()
    {
        x = y = z = 0;
    }

    template <typename T>
    void Vector3<T>::normalize()
    {
        T l = length();
        assert(l != 0);

        x /= l;
        y /= l;
        z /= l;
    }

    template <typename T>
    Vector3<T> Vector3<T>::add(T v) const{
        return Vector3<T>(x + v, y + v, z + v);
    }

    template <typename T>
    Vector3<T> Vector3<T>::add(const Vector3& vec) const{
        return Vector3<T>(x + vec.x, y + vec.y, z + vec.z);
    }

    template <typename T>
    Vector3<T> Vector3<T>::sub(T v) const{
        return Vector3<T>(x - v, y - v, z - v);
    }

    template <typename T>
    Vector3<T> Vector3<T>::sub(const Vector3& vec) const{
        return Vector3<T>(x - vec.x, y - vec.y, z - vec.z);
    }

    template <typename T>
    Vector3<T> Vector3<T>::mult(T v) const{
        return Vector3<T>(x * (T)v, y * (T)v, z * (T)v);
    }

    template <typename T>
    Vector3<T> Vector3<T>::mult(const Vector3& vec) const{
        return Vector3<T>(x * vec.x, y * vec.y, z * vec.z);
    }

    template <typename T>
    Vector3<T> Vector3<T>::divide(T v) const{
        assert(((T)v != 0) && "Dividing with Zero.");
        return Vector3<T>(x / (T)v, y / (T)v, z / (T)v);
    }

    template <typename T>
    Vector3<T> Vector3<T>::divide(const Vector3& vec) const{
        assert((vec.x != 0.0 && vec.y != 0.0 && vec.z != 0.0) && "Dividing with Zero.");
        return Vector3<T>(x / vec.x, y / vec.y, z / vec.z);
    }

    template <typename T>
    T Vector3<T>::dot(const Vector3& v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    template <typename T>
    Vector3<T> Vector3<T>::cross(const Vector3& v) const
    {
        float _x = (y * v.z) - (z * v.y);
        float _y = (z * v.x) - (x * v.z);
        float _z = (x * v.y) - (y * v.x);

        return Vector3<T>(_x, _y, _z);
    }

    template <typename T>
    const T& Vector3<T>::at(size_t i) const {
        static_assert(i < 3);
        return (&x)[i];
    }

    template <typename T>
    T& Vector3<T>::at(size_t i) {
        assert(i < 3);
        return (&x)[i];
    }

    template <typename T>
    T Vector3<T>::sum() const {
        return x + y + z;
    }

    template <typename T>
    T Vector3<T>::avg() const {
        return (x + y + z)/3;
    }

    template <typename T>
    T Vector3<T>::min() const {
        return std::min(std::min(x, y), z);
    }

    template <typename T>
    T Vector3<T>::max() const {
        return std::max(std::max(x, y), z);
    }

    
    template <typename T>
    Vector3<T> Vector3<T>::norm() const {
        T l = length();
        assert(l != 0);
        return Vector3<T>(x / l, y / l, z / l);
    }

    template <typename T>
    T Vector3<T>::length() const {
        return std::sqrt(x * x + y * y + z * z);
    }

    template <typename T>
    T Vector3<T>::squaredLength() const {
        return x * x + y * y + z * z;
    }

    template <typename T>
    T Vector3<T>::distanceTo(const Vector3<T>& other) const {
        return sub(other).length();
    }

    template <typename T>
    T Vector3<T>::distanceSquaredTo(const Vector3<T>& other) const {
        return sub(other).lengthSquared();
    }

    template <typename T>
    template <typename U>
    Vector3<U> Vector3<T>::castTo() const 
    {
        return Vector3<U>(
                    static_cast<U>(x),
                    static_cast<U>(y),
                    static_cast<U>(z));
    }

    template <typename T>
    bool Vector3<T>::isEqual(const Vector3& other) const {
        return x == other.x && y == other.y && z == other.z;
    }

    template <typename T>
    Vector3<T>& Vector3<T>::operator=(const Vector3& v) 
    {
        x = v.x; y = v.y; z = v.z;
        return (*this);
    }

    template <typename T>
    Vector3<T>& Vector3<T>::operator+=(T v) 
    {
        x += v;
        y += v;
        z += v;

        return (*this);
    }

    template <typename T>
    Vector3<T>& Vector3<T>::operator+=(const Vector3& v) 
    {
        x += v.x;
        y += v.y;
        z += v.z;

        return (*this);
    }

    template <typename T>
    Vector3<T>& Vector3<T>::operator-=(T v) 
    {
        x -= v;
        y -= v;
        z -= v;

        return (*this);
    }

    template <typename T>
    Vector3<T>& Vector3<T>::operator-=(const Vector3& v) 
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;

        return (*this);
    }

    template <typename T>
    Vector3<T>& Vector3<T>::operator*=(T v) 
    {
        x *= v;
        y *= v;
        z *= v;

        return (*this);
    }

    template <typename T>
    Vector3<T>& Vector3<T>::operator*=(const Vector3& v) 
    {
        x *= v.x;
        y *= v.y;
        z *= v.z;

        return (*this);
    }

    template <typename T>
    Vector3<T>& Vector3<T>::operator/=(T v) 
    {
        static_assert((v != 0.0) && "Dividing with Zero.");
        x /= v;
        y /= v;
        z /= v;

        return (*this);
    }

    template <typename T>
    Vector3<T>& Vector3<T>::operator/=(const Vector3& v) 
    {
        static_assert((v.x != 0.0 && v.y != 0.0 && v.z != 0.0) && "Dividing with Zero.");
        x /= v.x;
        y /= v.y;
        z /= v.z;

        return (*this);
    }

    template <typename T>
    std::ostream&   operator<< (std::ostream& stream, const Vector3<T>& vec)
    {
        stream << "(" << vec.x << ", " << vec.y << ", " << vec.z << ")" << '\n';
        return stream;
    }

    template <typename T>
    Vector3<T>  Cross(const Vector3<T>& vec1, const Vector3<T>& vec2)
    {
        float _x = (vec1.y * vec2.z) - (vec1.z * vec2.y);
        float _y = (vec1.z * vec2.x) - (vec1.x * vec2.z);
        float _z = (vec1.x * vec2.y) - (vec1.y * vec2.x);

        return Vector3<T>(_x, _y, _z);
    }

    template <typename T>
    float Dot(const Vector3<T>& vec1, const Vector3<T>& vec2)
    {
        return (vec1.x * vec1.x + vec1.y * vec1.y + vec1.z * vec1.z);
    }

}

