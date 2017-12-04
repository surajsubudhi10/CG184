//
// Created by suraj on 12/3/17.
//

#ifndef CGENGINE_TRANSFORM_H
#define CGENGINE_TRANSFORM_H

#include "../Maths/Maths.h"

namespace CG184 {
    class Transform {

    public:
        Transform();
        ~Transform();



        Matrix4D& GetTransformMat();

        static Matrix4D Translate(Matrix4D& mat, float _x, float _y, float _z);
//        static void Translate(Transform& trans, float _x, float _y, float _z);

        static Matrix4D Rotate(Matrix4D& mat, float angleInDeg, const Vector3D& axis);
//        static void Rotate(Transform& trans, float angleInDeg, const Vector3D& axis);

        static Matrix4D Scale(Matrix4D& mat, float sx, float sy, float sz);
//        static void Scale(Transform& trans, float sx, float sy, float sz);


    public:
        Vector3D position;
        Vector3D localPosition;

        Vector3D eulerAngles;
        Vector3D localScale;



    private:
        Matrix4D transformMat;
        void UpdateTransformMatrix();

        friend class Node;
    };
}


#endif //CGENGINE_TRANSFORM_H
