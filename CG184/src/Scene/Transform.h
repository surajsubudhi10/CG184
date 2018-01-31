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

        Matrix4D& GetLocalTransformMat();
		Matrix4D& GetWorldTransformMat();

        Matrix4D Translate(Matrix4D& mat, float _x, float _y, float _z);
        Matrix4D Rotate(Matrix4D& mat, float angleInDeg, const Vector3D& axis);
        Matrix4D Scale(Matrix4D& mat, float sx, float sy, float sz);

		bool isDirty;

    private:
        Vector3D			m_Position;
		Quaternion			m_Rotation;
        Vector3D			m_LocalPosition;
        Vector3D			m_EulerAngles;
        Vector3D			m_LocalScale;
        
		Matrix4D			m_LocalTransformMat;
		Matrix4D			m_WorldTransformMat;

        void UpdateLocalTransformMatrix();
        friend class Node;
    };
}


#endif //CGENGINE_TRANSFORM_H
