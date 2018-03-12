#pragma once

#include "../Maths/Matrix4D.h"
#include <memory>

namespace CG184 
{
    class Camera
    {
    public:
        Camera();
        Camera(const Vector3F& pos, const Vector3F& _front, const Vector3F& _up);
        Camera(float camFov, float aspect, float camNear, float camFar);
        Camera(Camera& cam);
        ~Camera();

        void				SetFrustrum(float camFov, float aspect, float camNear, float camFar);
        void				Set(const Vector3F& pos, const Vector3F& _front, const Vector3F& _up);

        inline void			SetFOV(float camFov)				{ m_Fov = camFov; UpdateProjectionMatrix(); }
        inline void			SetAspectRatio(float aspect)		{ m_AspectRatio = aspect; UpdateProjectionMatrix(); }
        inline void			SetNearPlane(float _near)			{ m_Near = _near; UpdateProjectionMatrix(); }
        inline void			SetFarPlane(float _far)				{ m_Far = _far; UpdateProjectionMatrix(); }

        inline void			SetPosition(const Vector3F& pos)	{ m_Position = pos; UpdateViewMatrix(); }
        inline void			SetTarget(const Vector3F& _target)	{ m_Target = _target; UpdateViewMatrix(); }
        inline void			SetUp(const Vector3F& _up)			{ m_Up = _up; UpdateViewMatrix(); }

        inline Matrix4F&	GetViewMatrix()			{ return m_ViewMatrix; }
        inline Matrix4F&	GetProjectionMatrix()	{ return m_ProjectionMatrix; }
        inline Vector3F&	GetCamPos()				{ return m_Position; }

    private:
        Matrix4F			Prespective(float fov, float aspect_ratio, float near, float far);
        Matrix4F			LookAt(Vector3F eyePos, Vector3F target, Vector3F up);

        void				UpdateProjectionMatrix();
        void				UpdateViewMatrix();

        Vector3F			m_Position;
        Vector3F			m_Target;
        Vector3F			m_Up;

        float				m_Fov;
        float				m_AspectRatio;
        float				m_Near;
        float				m_Far;

        Matrix4F			m_ViewMatrix;
        Matrix4F			m_ProjectionMatrix;
    };

    typedef std::shared_ptr<Camera> CameraPtr;
}   // End of CG184