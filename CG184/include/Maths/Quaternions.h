#ifndef CGENGINE_QUATERNIONS_H
#define CGENGINE_QUATERNIONS_H

#include "Vector3D.h"
#include "Vector4D.h"
#include "Matrix4D.h"
#include <cmath>
#include <cassert>


namespace CG184 {
    class Quaternion
    {
    public:
        Quaternion();
        ~Quaternion();
        Quaternion(float _x, float _y, float _z, float _w);
        Quaternion(const Quaternion& quat);
        Quaternion(const float angleInRadians, const Vector3F& axis);

        Quaternion add(const    Quaternion& quat) const;
        Quaternion sub(const    Quaternion& quat) const;
        Quaternion mult(const   Quaternion& quat) const;
        
        Quaternion mult(float multiplier) const;
        Quaternion divide(float divisor)  const;

        Quaternion norm() const;
        void normalize();
        float squaredLength() const;
        float length() const;
        bool isEqual(const Quaternion& quat) const;
        Quaternion conjugate() const;

        void ToAxisAngle( Vector3F& axis, float& angle);
        Vector3F ToEulerAngles();
        Matrix4D ToMatrix();


    public:
        float x, y, z, w;
    };

    
    inline Quaternion operator+(const Quaternion& lhs, const Quaternion& rhs)
    {
        return Quaternion(lhs.w + rhs.w, lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    }

    inline Quaternion operator*(const Quaternion& lhs, const float scalar)
    {
        return Quaternion(scalar*lhs.w, scalar*lhs.x, scalar*lhs.y, scalar*lhs.z);
    }
    inline Quaternion operator*(const float scalar, const Quaternion& rhs)
    {
        return Quaternion(scalar*rhs.w, scalar*rhs.x, scalar*rhs.y, scalar*rhs.z);
    }

    inline float length(const Quaternion& quat)
    {
        return sqrt(quat.w*quat.w + quat.x*quat.x + quat.y*quat.y + quat.z*quat.z);
    }

    inline Quaternion& normalize(Quaternion& quat)
    {
        const float l = length(quat);
        quat = quat * (1.0f / l);
        return quat;
    }

    inline float dot(const Quaternion& lhs, const Quaternion& rhs)
    {
        return lhs.w*rhs.w + lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z;
    }

    inline Quaternion operator*(const Quaternion& lhs, const Quaternion& rhs)
    {
        Vector3F v1(rhs.x, rhs.y, rhs.z);
        Vector3F v2(lhs.x, lhs.y, lhs.z);

        const float w = rhs.w*lhs.w - dot(rhs, lhs);
        Vector3F  v = (v2 * rhs.w) + (v1 * lhs.w) + v2.cross(v1);

        return Quaternion(w, v.x, v.y, v.z);
    }

    inline Vector3F operator*(const Quaternion& quat, Vector3F& vec)
    {
        assert(vec.length() == 1.0f);
        const float w2 = quat.w * quat.w;
        Vector3F quatVec(quat.x, quat.y, quat.z);
        return vec * (2.0f * w2 - 1.0f) + quatVec * (2.0f * quatVec.dot(vec)) +  quatVec.cross(vec) * w2;
    }

    inline Quaternion inverse(const Quaternion& quat)
    {
        // TODO(Joey): assert that we're dealing with a unity vector
        assert(quat.length() == 1.0f);
        return Quaternion(-quat.x, -quat.y, -quat.z, quat.w);
    }

    inline Quaternion ToQuaternion(float roll, float pitch, float yaw) 
    {
        Quaternion q;
        // Abbreviations for the various angular functions
        auto cy = static_cast<float>(cos(yaw * 0.5));
        auto sy = static_cast<float>(sin(yaw * 0.5));
        auto cr = static_cast<float>(cos(roll * 0.5));
        auto sr = static_cast<float>(sin(roll * 0.5));
        auto cp = static_cast<float>(cos(pitch * 0.5));
        auto sp = static_cast<float>(sin(pitch * 0.5));

        q.w = cy * cr * cp + sy * sr * sp;
        q.x = cy * sr * cp - sy * cr * sp;
        q.y = cy * cr * sp + sy * sr * cp;
        q.z = sy * cr * cp - cy * sr * sp;
        return q;
    }

    inline Quaternion ToQuaternion(Vector3F eulerAngle) 
    {
        return ToQuaternion(eulerAngle.x, eulerAngle.y, eulerAngle.z);
    }

    std::ostream& operator<< (std::ostream& stream, const Quaternion& quat);

}   // End of CG184

#endif //CGENGINE_QUATERNIONS_H