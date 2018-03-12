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

        Matrix4F& GetLocalTransformMat();
        Matrix4F& GetWorldTransformMat();

        Matrix4F Translate(Matrix4F& mat, float _x, float _y, float _z);
        Matrix4F Rotate(Matrix4F& mat, float angleInDeg, const Vector3F& axis);
        Matrix4F Scale(Matrix4F& mat, float sx, float sy, float sz);

        bool isDirty;

    private:
        Vector3F			m_Position;
        QuaternionF			m_Rotation;
        Vector3F			m_LocalPosition;
        Vector3F			m_EulerAngles;
        Vector3F			m_LocalScale;
        
        Matrix4F			m_LocalTransformMat;
        Matrix4F			m_WorldTransformMat;

        void UpdateLocalTransformMatrix();
        friend class Node;
    };
}   // End of CG184


#endif //CGENGINE_TRANSFORM_H
