#pragma once

#include "../Maths/Matrix4D.h"
#include <memory>

namespace CG184 
{
    class Camera
    {
    public:
        Camera();
        Camera(const Vector3D& pos, const Vector3D& _front, const Vector3D& _up);
        Camera(float camFov, float aspect, float camNear, float camFar);
        Camera(Camera& cam);
        ~Camera();

        void				SetFrustrum(float camFov, float aspect, float camNear, float camFar);
        void				Set(const Vector3D& pos, const Vector3D& _front, const Vector3D& _up);

        inline void			SetFOV(float camFov)				{ m_Fov = camFov; UpdateProjectionMatrix(); }
        inline void			SetAspectRatio(float aspect)		{ m_AspectRatio = aspect; UpdateProjectionMatrix(); }
        inline void			SetNearPlane(float _near)			{ m_Near = _near; UpdateProjectionMatrix(); }
        inline void			SetFarPlane(float _far)				{ m_Far = _far; UpdateProjectionMatrix(); }

        inline void			SetPosition(const Vector3D& pos)	{ m_Position = pos; UpdateViewMatrix(); }
        inline void			SetTarget(const Vector3D& _target)	{ m_Target = _target; UpdateViewMatrix(); }
        inline void			SetUp(const Vector3D& _up)			{ m_Up = _up; UpdateViewMatrix(); }

        inline Matrix4D&	GetViewMatrix()			{ return m_ViewMatrix; }
        inline Matrix4D&	GetProjectionMatrix()	{ return m_ProjectionMatrix; }
        inline Vector3D&	GetCamPos()				{ return m_Position; }

    private:
        Matrix4D			Prespective(float fov, float aspect_ratio, float near, float far);
        Matrix4D			LookAt(Vector3D eyePos, Vector3D target, Vector3D up);

        void				UpdateProjectionMatrix();
        void				UpdateViewMatrix();

        Vector3D			m_Position;
        Vector3D			m_Target;
        Vector3D			m_Up;

        float				m_Fov;
        float				m_AspectRatio;
        float				m_Near;
        float				m_Far;

        Matrix4D			m_ViewMatrix;
        Matrix4D			m_ProjectionMatrix;
    };

    typedef std::shared_ptr<Camera> CameraPtr;
}   // End of CG184