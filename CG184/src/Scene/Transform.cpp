//
// Created by suraj on 12/3/17.
//

#include <cmath>
#include <Scene/Transform.h>
#include <Maths/Maths.h>

namespace CG184
{

    Transform::Transform() :
        m_Position(Vector3F(0)),
        m_LocalPosition(Vector3F(0)),
        m_Rotation(QuaternionF()),
        m_EulerAngles(Vector3F(0)),
        m_LocalScale(Vector3F(1)),
        isDirty(false)
    {
        UpdateLocalTransformMatrix();
    }

    Transform::~Transform() = default;

    Matrix4F& Transform::GetLocalTransformMat() {
        return m_LocalTransformMat;
    }

    Matrix4F & Transform::GetWorldTransformMat()
    {
        return m_WorldTransformMat;
    }

    void Transform::UpdateLocalTransformMatrix()
    {
        m_LocalTransformMat = Matrix4F(1.0f);
        
        float angleInDeg;
        Vector3F axis;
        m_Rotation.ToAxisAngle(axis, angleInDeg);
        angleInDeg = ToDegrees(angleInDeg);
        if(axis.length() > 0.0f)
            Rotate(m_LocalTransformMat, angleInDeg, axis);
        
        Scale(m_LocalTransformMat, m_LocalScale.x, m_LocalScale.y, m_LocalScale.z);
        Translate(m_LocalTransformMat, m_LocalPosition.x, m_LocalPosition.y, m_LocalPosition.z);
        isDirty = false;
    }

    Matrix4F Transform::Translate(Matrix4F& mat, float _x, float _y, float _z)
    {
        Matrix4F transMat(
                1, 0, 0, _x,
                0, 1, 0, _y,
                0, 0, 1, _z,
                0, 0, 0,  1
        );

        //transMat = transMat.transpose();
        //mat = transMat.multiply(mat);
        mat = transMat.mult(mat);
        return mat;
    }

    Matrix4F Transform::Rotate(Matrix4F& mat, float angleInDeg, const Vector3F& axis)
    {
        auto angInRad = static_cast<float>(PI * angleInDeg / 180.0f);

        // Checkpoint only keeping rotation along z axis for testing.
        auto c = static_cast<float>(cos(angInRad));
        auto s = static_cast<float>(sin(angInRad));
        auto v = 1 - c;

        Vector3F normAxis =  axis.norm();
        auto kx = normAxis.x;
        auto ky = normAxis.y;
        auto kz = normAxis.z;

        Matrix4F rotMat(
                (kx * kx * v) + c       , (kx * ky * v) - (kz * s), (kx * kz * v) + (ky * s), 0,
                (ky * kx * v) + (kz * s), (ky * ky * v) +  c      , (ky * kz * v) - (kx * s), 0,
                (kz * kx * v) - (ky * s), (kz * ky * v) + (kx * s), (kz * kz * v) +  c      , 0,
                0,                        0,                        0, 1
        );
        //mat = rotMat.multiply(mat);
        mat = rotMat.mult(mat);
        return mat;
    }

    Matrix4F Transform::Scale(Matrix4F& mat, float sx, float sy, float sz)
    {
        Matrix4F scaleMat(
                sx,  0,  0, 0,
                0, sy,  0, 0,
                0,  0, sz, 0,
                0,  0,  0, 1
        );

        mat = scaleMat.mult(mat);
        //mat = scaleMat.multiply(mat);
        return mat;
    }
}   // End of CG184