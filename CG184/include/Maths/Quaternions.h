#ifndef CGENGINE_QUATERNIONS_H
#define CGENGINE_QUATERNIONS_H

#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix4D.h"
#include <cmath>
#include <cassert>

namespace CG184
{
    template <typename T>
    class Quaternion
    {
    public:
        static_assert(
            std::is_floating_point<T>::value,
            "Vector only can be instantiated with floating point types");

        T x, y, z, w;

    public:
        //! Constructs default Quaternion (0, 0, 0, 1).
        Quaternion();

        //! Set all x, y, z and w components to \p _val.
        Quaternion(T _val);

        //! Constructs a quaternion with given elements.
        Quaternion(T _x, T _y, T _z, T _w);

        template <typename U>
        Quaternion( Vector3<T>& _vec, U wval);

        //! Copy constructor.
        template<typename U>
        Quaternion(const Quaternion<U>& _vec);

        //! Constructs a quaternion with given rotation axis and angle.
        template <typename U>
        Quaternion(const U angleInRadians, const Vector3<U>& axis);
        
        //! Set all x, y, and z to zero.
        void setZero();

        template <typename U>
        Quaternion<T> add(const    Quaternion<U>& quat) const;
        
        template <typename U>
        Quaternion<T> sub(const    Quaternion<U>& quat) const;

        template <typename U>
        Quaternion<T> mult(const   Quaternion<U>& quat) const;
        
        template <typename U>
        Quaternion<T> mult(U multiplier) const;
        
        template <typename U>
        Quaternion<T> divide(U divisor)  const;

        //! Returns normalized quaternion.
        Quaternion<T> norm() const;

        //! Normalize quaternion.
        void normalize();

        T squaredLength() const;

        T length() const;

        //! Check if both quat are equal or not
        bool isEqual(const Quaternion& quat) const;

        //! Returns the conjugate of the quat
        Quaternion<T> conjugate() const;

        //! Returns the axis and angle.
        void ToAxisAngle( Vector3<T>& axis, T& angle);

        Vector3<T> ToEulerAngles();

        Matrix4<T> ToMatrix();

    };

    typedef Quaternion<float> QuaternionF;


    
    template<typename T>
    inline Quaternion<T> operator+(const Quaternion<T>& lhs, const Quaternion<T>& rhs)
    {
        return Quaternion(lhs.w + rhs.w, lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    }

    template<typename T>
    inline Quaternion<T> operator*(const Quaternion<T>& lhs, const T scalar)
    {
        return Quaternion(scalar*lhs.w, scalar*lhs.x, scalar*lhs.y, scalar*lhs.z);
    }

    template<typename T>
    inline Quaternion<T> operator*(const T scalar, const Quaternion<T>& rhs)
    {
        return Quaternion(scalar*rhs.w, scalar*rhs.x, scalar*rhs.y, scalar*rhs.z);
    }

    template<typename T>
    inline T length(const Quaternion<T>& quat)
    {
        return sqrt(quat.w*quat.w + quat.x*quat.x + quat.y*quat.y + quat.z*quat.z);
    }

    template<typename T>
    inline Quaternion<T>& normalize(Quaternion<T>& quat)
    {
        const T l = length(quat);
        quat = quat * (1.0 / l);
        return quat;
    }

    template<typename T>
    inline T dot(const Quaternion<T>& lhs, const Quaternion<T>& rhs)
    {
        return lhs.w*rhs.w + lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
    }

    template<typename T>
    inline Quaternion<T> operator*(const Quaternion<T>& lhs, const Quaternion<T>& rhs)
    {
        Vector3<T> v1(rhs.x, rhs.y, rhs.z);
        Vector3<T> v2(lhs.x, lhs.y, lhs.z);

        const T w = rhs.w*lhs.w - dot(rhs, lhs);
        Vector3<T>  v = (v2 * rhs.w) + (v1 * lhs.w) + v2.cross(v1);

        return Quaternion<T>(w, v.x, v.y, v.z);
    }

    template<typename T>
    inline Vector3<T> operator*(const Quaternion<T>& quat, Vector3<T>& vec)
    {
        assert(vec.length() == 1.0f);
        const T w2 = quat.w * quat.w;
        Vector3<T> quatVec(quat.x, quat.y, quat.z);
        return vec * (2.0f * w2 - (T)1.0) + quatVec * (2.0 * quatVec.dot(vec)) +  quatVec.cross(vec) * w2;
    }

    template<typename T>
    inline Quaternion<T> inverse(const Quaternion<T>& quat)
    {
        assert(quat.length() == 1.0f);
        return Quaternion(-quat.x, -quat.y, -quat.z, quat.w);
    }

    template<typename T>
    Quaternion<T> ToQuaternion(T roll, T pitch, T yaw) 
    {
        Quaternion<T> q;
        // Abbreviations for the various angular functions
        auto cy = static_cast<T>(cos(yaw * 0.5));
        auto sy = static_cast<T>(sin(yaw * 0.5));
        auto cr = static_cast<T>(cos(roll * 0.5));
        auto sr = static_cast<T>(sin(roll * 0.5));
        auto cp = static_cast<T>(cos(pitch * 0.5));
        auto sp = static_cast<T>(sin(pitch * 0.5));

        q.w = cy * cr * cp + sy * sr * sp;
        q.x = cy * sr * cp - sy * cr * sp;
        q.y = cy * cr * sp + sy * sr * cp;
        q.z = sy * cr * cp - cy * sr * sp;
        return q;
    }

    template<typename T>
    inline Quaternion<T> ToQuaternion(Vector3<T> eulerAngle) 
    {
        return ToQuaternion(eulerAngle.x, eulerAngle.y, eulerAngle.z);
    }

    template<typename T>
    Quaternion<T>::Quaternion() :
        x(0.0f), y(0.0f), z(0.0f), w(1.0f)
    {}

    template<typename T>
    Quaternion<T>::Quaternion(T _x, T _y, T _z, T _w):
        x(_x), y(_y), z(_z), w(_w)
    {}

    template<typename T>
    template<typename U>
    Quaternion<T>::Quaternion(const Quaternion<U>& quat) :
        x(static_cast<U>quat.x), y(static_cast<U>quat.y), z(static_cast<U>quat.z), w(static_cast<U>quat.w)
    {}

    template<typename T>
    template<typename U>
    Quaternion<T>::Quaternion(const U angleInRadians, const Vector3<U>& axis)
    {
        const float halfAngle = 0.5f * angleInRadians;
        w = cosf(halfAngle);
        x = axis.x * sinf(halfAngle);
        y = axis.y * sinf(halfAngle);
        z = axis.z * sinf(halfAngle);
    }

    template<typename T>
    template<typename U>
    Quaternion<T> Quaternion<T>::add(const    Quaternion<U>& quat) const 
    {
        return Quaternion(x + (T)quat.x, y + (T)quat.y, z + (T)quat.z, w + (T)quat.w);
    }

    template<typename T>
    template<typename U>
    Quaternion<T> Quaternion<T>::sub(const    Quaternion<U>& quat) const 
    {
        return Quaternion(x - (T)quat.x, y - (T)quat.y, z - (T)quat.z, w - (T)quat.w);
    }

    template<typename T>
    template<typename U>
    Quaternion<T> Quaternion<T>::mult(const   Quaternion<U>& quat) const 
    {
        Quaternion result;
        result.x = y * (T)quat.z - z * (T)quat.y + w * (T)quat.x + x * (T)quat.w;
        result.y = z * (T)quat.x - x * (T)quat.z + w * (T)quat.y + y * (T)quat.w;
        result.z = x * (T)quat.y - y * (T)quat.x + w * (T)quat.z + z * (T)quat.w;
        result.w = w * (T)quat.w - x * (T)quat.x - y * (T)quat.y - z * (T)quat.z;

        return result;
    }

    template<typename T>
    template<typename U>
    Quaternion<T> Quaternion<T>::mult(U multiplier) const 
    {
        return Quaternion<T>(x * (T)multiplier, y * (T)multiplier, z * (T)multiplier, w * (T)multiplier);
    }

    template<typename T>
    template<typename U>
    Quaternion<T> Quaternion<T>::divide(U divisor)  const 
    {
        assert(divisor != 0.0 && "Dividing with zero.");
        return Quaternion<T>(x / (T)divisor, y / (T)divisor, z / (T)divisor, w / (T)divisor);
    }

    template<typename T>
    Quaternion<T> Quaternion<T>::norm() const
    {
        float len = length();
        assert(len != 0 && "length must be greater than zero");
        float _x = x / len;
        float _y = y / len;
        float _z = z / len;
        float _w = w / len;

        return Quaternion<T>(_x, _y, _z, _w);
    }

    template<typename T>
    void  Quaternion<T>::normalize() 
    {
        float len = length();
        assert(len != 0 && "length must be greater than zero");
        *this = divide(len);
    }

    template<typename T>
    T Quaternion<T>::squaredLength() const 
    {
        return (x * x + y * y + z * z + w * w);
    }

    template<typename T>
    T Quaternion<T>::length() const
    {
        return (T)sqrt(squaredLength());
    }

    template<typename T>
    bool  Quaternion<T>::isEqual(const Quaternion<T>& quat) const 
    {
        return (quat.x == x && quat.y == y && quat.z == z && quat.w == w);
    }

    template<typename T>
    Quaternion<T>  Quaternion<T>::conjugate() const
    {
        return Quaternion<T>(-x, -y, -z, w);
    }

    template<typename T>
    void Quaternion<T>::ToAxisAngle(Vector3<T>& axis, T& angle)
    {
        angle = 2.0f * (T)acos(w);
        T length = (T)sqrt(1.0f - w*w);
        axis = Vector3<T>();
        if(length != 0)
            axis = Vector3<T>(x, y, z) / (length);
    }

    template<typename T>
    Vector3<T> Quaternion<T>::ToEulerAngles() 
    {

        //Reference :- https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles

        T roll, pitch, yaw;
        // roll (x-axis rotation)
        auto sinr = +2.0 * (w * x + y * z);
        auto cosr = +1.0 - 2.0 * (x * x + y * y);
        roll = static_cast<T>(atan2(sinr, cosr));

        // pitch (y-axis rotation)
        auto sinp = +2.0 * (w * y - z * x);
        if (fabs(sinp) >= 1)
            pitch = static_cast<T>(copysign(PI / 2, sinp)); // use 90 degrees if out of range
        else
            pitch = static_cast<T>(asin(sinp));

        // yaw (z-axis rotation)
        auto siny = +2.0 * (w * z + x * y);
        auto cosy = +1.0 - 2.0 * (y * y + z * z);
        yaw = static_cast<T>(atan2(siny, cosy));

        return Vector3<T>(roll, pitch, yaw);
    }

    template<typename T>
    Matrix4<T> Quaternion<T>::ToMatrix()
    {
        Matrix4<T> mat;

        mat.elements[0]  = 1.0 - 2.0*y*y - 2.0*z*z;
        mat.elements[1]  = 2.0*x*y + 2.0*w*z;
        mat.elements[2]  = 2.0*x*z - 2.0*w*y;
        mat.elements[3]  = 0.0;

        mat.elements[4]  = 2.0*x*y - 2.0*w*z;
        mat.elements[5]  = 1.0 - 2.0*x*x - 2.0*z*z;
        mat.elements[6]  = 2.0*y*z + 2.0*w*x;
        mat.elements[7]  = 0.0;

        mat.elements[8]  = 2.0*x*z + 2.0*w*y;
        mat.elements[9]  = 2.0*y*z - 2.0*w*x;
        mat.elements[10] = 1.0 - 2.0*x*x - 2.0*y*y;
        mat.elements[11] = 0.0;

        mat.elements[12] = 0.0;
        mat.elements[13] = 0.0;
        mat.elements[14] = 0.0;
        mat.elements[15] = 1.0;

        return mat;
    }

    template<typename T>
    std::ostream& operator<< (std::ostream& stream, const Quaternion<T>& quat){
        stream << "(" << quat.x << ", " << quat.y << ", " << quat.z << ", " << quat.w << ")" << '\n';
        return stream;
    }

}

#endif //CGENGINE_QUATERNIONS_H
