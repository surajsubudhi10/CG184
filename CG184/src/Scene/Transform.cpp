//
// Created by suraj on 12/3/17.
//

#include <cmath>
#include "Transform.h"


namespace CG184
{

    Transform::Transform() :
        position(Vector3D(0)),
        localPosition(Vector3D(0)),
        eulerAngles(Vector3D(0)),
        localScale(Vector3D(1))
    {
        UpdateTransformMatrix();
    }

    Transform::~Transform() = default;

    Matrix4D& Transform::GetTransformMat() {
        return transformMat;
    }

    void Transform::UpdateTransformMatrix()
    {
        transformMat = Matrix4D(1.0f);
        Rotate(transformMat, eulerAngles.x, Vector3D(1, 0, 0));
        Rotate(transformMat, eulerAngles.y, Vector3D(0, 1, 0));
        Rotate(transformMat, eulerAngles.z, Vector3D(0, 0, 1));
        Scale(transformMat, localScale.x, localScale.y, localScale.z);
        Translate(transformMat, localPosition.x, localPosition.y, localPosition.z);
    }

    Matrix4D Transform::Translate(Matrix4D& mat, float _x, float _y, float _z)
    {
        Matrix4D transMat(
                1, 0, 0, _x,
                0, 1, 0, _y,
                0, 0, 1, _z,
                0, 0, 0,  1
        );

        //transMat = transMat.transpose();
        mat = transMat.multiply(mat);
        return mat;
    }

    Matrix4D Transform::Rotate(Matrix4D& mat, float angleInDeg, const Vector3D& axis)
    {
        auto angInRad = static_cast<float>(PI * angleInDeg / 180.0f);

        // Checkpoint only keeping rotation along z axis for testing.
        auto c = static_cast<float>(cos(angInRad));
        auto s = static_cast<float>(sin(angInRad));
        auto v = 1 - c;

        Vector3D normAxis =  axis.norm();
        auto kx = normAxis.x;
        auto ky = normAxis.y;
        auto kz = normAxis.z;

        Matrix4D rotMat(
                (kx * kx * v) + c       , (kx * ky * v) - (kz * s), (kx * kz * v) + (ky * s), 0,
                (ky * kx * v) + (kz * s), (ky * ky * v) +  c      , (ky * kz * v) - (kx * s), 0,
                (kz * kx * v) - (ky * s), (kz * ky * v) + (kx * s), (kz * kz * v) +  c      , 0,
                0,                        0,                        0, 1
        );
        mat = rotMat.multiply(mat);
        return mat;
    }

    Matrix4D Transform::Scale(Matrix4D& mat, float sx, float sy, float sz)
    {
        Matrix4D scaleMat(
                sx,  0,  0, 0,
                0, sy,  0, 0,
                0,  0, sz, 0,
                0,  0,  0, 1
        );

        mat = scaleMat.multiply(mat);
        return mat;
    }



//    void Transform::Translate(Transform &trans, float _x, float _y, float _z) {
//        Translate(trans.transformMat, _x, _y, _z);
//    }
//
//    void Transform::Rotate(Transform &trans, float angleInDeg, const Vector3D &axis) {
//        Rotate(trans.transformMat, angleInDeg, axis);
//    }
//
//    void Transform::Scale(Transform &trans, float sx, float sy, float sz) {
//        Scale(trans.transformMat, sx, sy, sz);
//    }


}