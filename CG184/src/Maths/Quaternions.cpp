#include <Maths/Quaternions.h>
#include <Maths/Constants.h>

namespace CG184 
{

    Quaternion::Quaternion() :
        x(0.0f), y(0.0f), z(0.0f), w(1.0f)
    {}

    Quaternion::Quaternion(float _x, float _y, float _z, float _w):
        x(_x), y(_y), z(_z), w(_w)
    {}

    Quaternion::Quaternion(const Quaternion& quat) :
        x(quat.x), y(quat.y), z(quat.z), w(quat.w)
    {}

    Quaternion::Quaternion(const float angleInRadians, const Vector3D& axis)
    {
        const float halfAngle = 0.5f * angleInRadians;
        w = cosf(halfAngle);
        x = axis.x * sinf(halfAngle);
        y = axis.y * sinf(halfAngle);
        z = axis.z * sinf(halfAngle);
    }

    Quaternion Quaternion::add(const    Quaternion& quat) const 
    {
        return Quaternion(x + quat.x, y + quat.y, z + quat.z, w + quat.w);
    }

    Quaternion Quaternion::sub(const    Quaternion& quat) const 
    {
        return Quaternion(x - quat.x, y - quat.y, z - quat.z, w - quat.w);
    }

    Quaternion Quaternion::mult(const   Quaternion& quat) const 
    {
        Quaternion result;
        result.x = y * quat.z - z * quat.y + w * quat.x + x * quat.w;
        result.y = z * quat.x - x * quat.z + w * quat.y + y * quat.w;
        result.z = x * quat.y - y * quat.x + w * quat.z + z * quat.w;
        result.w = w * quat.w - x * quat.x - y * quat.y - z * quat.z;

        return result;
    }


    Quaternion Quaternion::mult(float multiplier) const 
    {
        return Quaternion(x*multiplier, y * multiplier, z * multiplier, w * multiplier);
    }

    Quaternion Quaternion::divide(float divisor)  const 
    {
        assert(divisor != 0.0 && "Dividing with zero.");
        return Quaternion(x / divisor, y / divisor, z / divisor, w / divisor);
    }

    Quaternion Quaternion::norm() const
    {
        float len = length();
        assert(len != 0 && "length must be greater than zero");
        float _x = x / len;
        float _y = y / len;
        float _z = z / len;
        float _w = w / len;

        return Quaternion(_x, _y, _z, _w);
    }
    
    void  Quaternion::normalize() 
    {
        float len = length();
        assert(len != 0 && "length must be greater than zero");
        *this = divide(len);
    }

    float Quaternion::squaredLength() const 
    {
        return (x * x + y * y + z * z + w * w);
    }

    float Quaternion::length() const
    {
        return sqrtf(squaredLength());
    }

    bool  Quaternion::isEqual(const Quaternion& quat) const 
    {
        return (quat.x == x && quat.y == y && quat.z == z && quat.w == w);
    }

    Quaternion  Quaternion::conjugate() const
    {
        return Quaternion(-x, -y, -z, w);
    }


    void Quaternion::ToAxisAngle(Vector3D& axis, float& angle)
    {
        angle = 2.0f * acosf(w);
        const float length = sqrtf(1.0f - w*w);
        axis = Vector3D();
        if(length != 0)
            axis = Vector3D(x, y, z) / length;
    }

    Vector3D Quaternion::ToEulerAngles() 
    {

        //Reference :- https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles

        float roll, pitch, yaw;
        // roll (x-axis rotation)
        auto sinr = +2.0 * (w * x + y * z);
        auto cosr = +1.0 - 2.0 * (x * x + y * y);
        roll = static_cast<float>(atan2(sinr, cosr));

        // pitch (y-axis rotation)
        auto sinp = +2.0 * (w * y - z * x);
        if (fabs(sinp) >= 1)
            pitch = static_cast<float>(copysign(PI / 2, sinp)); // use 90 degrees if out of range
        else
            pitch = static_cast<float>(asin(sinp));

        // yaw (z-axis rotation)
        auto siny = +2.0 * (w * z + x * y);
        auto cosy = +1.0 - 2.0 * (y * y + z * z);
        yaw = static_cast<float>(atan2(siny, cosy));

        return Vector3D(roll, pitch, yaw);
    }


    Matrix4D Quaternion::ToMatrix()
    {
        Matrix4D mat;

        mat.elements[0]  = 1.0f - 2.0f*y*y - 2.0f*z*z;
        mat.elements[1]  = 2.0f*x*y + 2.0f*w*z;
        mat.elements[2]  = 2.0f*x*z - 2.0f*w*y;
        mat.elements[3]  = 0.0f;

        mat.elements[4]  = 2.0f*x*y - 2.0f*w*z;
        mat.elements[5]  = 1.0f - 2.0f*x*x - 2.0f*z*z;
        mat.elements[6]  = 2.0f*y*z + 2.0f*w*x;
        mat.elements[7]  = 0.0f;

        mat.elements[8]  = 2.0f*x*z + 2.0f*w*y;
        mat.elements[9]  = 2.0f*y*z - 2.0f*w*x;
        mat.elements[10] = 1.0f - 2.0f*x*x - 2.0f*y*y;
        mat.elements[11] = 0.0f;

        mat.elements[12] = 0.0f;
        mat.elements[13] = 0.0f;
        mat.elements[14] = 0.0f;
        mat.elements[15] = 1.0f;

        return mat;
    }


    Quaternion::~Quaternion()
    {
    }

    std::ostream& operator<< (std::ostream& stream, const Quaternion& quat){
        stream << "(" << quat.x << ", " << quat.y << ", " << quat.z << ", " << quat.w << ")" << '\n';
        return stream;
    }
}   // End of CG184

