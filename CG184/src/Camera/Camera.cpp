#include "Camera.h"
#include <math.h>

#include "../Maths/Maths.h"

namespace CG184 
{
    
    Camera::Camera() 
    {
        m_Fov			= 45.0; 
        m_AspectRatio	= (float)(8 / 6); 
        m_Near			= 0.1f; 
        m_Far			= 100.0f;
        m_Position		= Vector3D(0.0f, 0.0f, 3.0f);
        m_Target		= Vector3D(0.0f, 0.0f, -1.0f);
        m_Up			= Vector3D(0.0f, 1.0f, 0.0f);

        UpdateViewMatrix();
        UpdateProjectionMatrix();
    }

    Camera::Camera(const Vector3D& pos, const Vector3D& _m_Target, const Vector3D& _m_Up) 
    {
        m_Fov			= 45.0; 
        m_AspectRatio	= (float)(8 / 6); 
        m_Near			= 0.1f; 
        m_Far			= 100.0f;
        m_Position		= pos;
        m_Target		= _m_Target;
        m_Up			= _m_Up;

        UpdateViewMatrix();
        UpdateProjectionMatrix();
    }


    Camera::Camera(float camm_Fov, float aspect, float camm_Near, float camm_Far)
    {
        m_Fov			= camm_Fov; 
        m_AspectRatio	= aspect; 
        m_Near			= camm_Near; 
        m_Far			= camm_Far;
        m_Position		= Vector3D(0.0f, 0.0f,  3.0f);
        m_Target		= Vector3D(0.0f, 0.0f, -1.0f);
        m_Up			= Vector3D(0.0f, 1.0f,  0.0f);

        UpdateViewMatrix();
        UpdateProjectionMatrix();
    }

    void Camera::SetFrustrum(float camm_Fov, float aspect, float camm_Near, float camm_Far) 
    {
        m_Fov			= camm_Fov; 
        m_AspectRatio	= aspect; 
        m_Near			= camm_Near; 
        m_Far			= camm_Far;
        UpdateProjectionMatrix();
    }

    void Camera::Set(const Vector3D& pos, const Vector3D& _m_Target, const Vector3D& _m_Up) 
    {
        m_Position		= pos;
        m_Target		= _m_Target;
        m_Up			= _m_Up;
        UpdateViewMatrix();
    }

    Camera::~Camera()
    {
    }

    void Camera::UpdateProjectionMatrix()
    {
        m_ProjectionMatrix = Prespective(m_Fov, m_AspectRatio, m_Near, m_Far);
    }

    void Camera::UpdateViewMatrix()
    {
        m_ViewMatrix = LookAt(m_Position, m_Target, m_Up);
    }

    Matrix4D Camera::Prespective(float m_FovInDeg, float m_AspectRatio, float m_Near, float m_Far)
    {
        auto m_FovInRad = (float)(PI * m_FovInDeg / 180.0f);
        const float tanHalfm_Fov = tan(m_FovInRad / 2.0f);

        Matrix4D result(1.0f);

        result.elements[0]  =  1 / (m_AspectRatio * tanHalfm_Fov);
        result.elements[5]  =  1 / tanHalfm_Fov;
        result.elements[10] = -1 * (m_Far + m_Near) / (m_Far - m_Near);
        result.elements[15] =  0.0f;
        result.elements[11] = -1.0f;
        result.elements[14] = (-2 * m_Far * m_Near) / (m_Far - m_Near);

        return result;
    }

    Matrix4D Camera::LookAt(Vector3D eyePos, Vector3D target, Vector3D m_Up)
    {
        Vector3D zAxis(target - eyePos);
        zAxis.normalize();

        Vector3D xAxis = (zAxis.cross(m_Up));
        xAxis.normalize();

        Vector3D yAxis = xAxis.cross(zAxis);

        float ex = -xAxis.dot(eyePos);
        float ey = -yAxis.dot(eyePos);
        float ez =  zAxis.dot(eyePos);

        Matrix4D lookMat(
                 xAxis.x,  xAxis.y,  xAxis.z, ex,
                 yAxis.x,  yAxis.y,  yAxis.z, ey,
                -zAxis.x, -zAxis.y, -zAxis.z, ez,
                       0,        0,    0,  1
        );
        return lookMat;
    }

    Camera::Camera(Camera &cam) {
        m_Position		= cam.m_Position;
        m_Target		= cam.m_Target;
        m_Up			= cam.m_Up;

        m_Fov			= cam.m_Fov;
        m_AspectRatio	= cam.m_AspectRatio;
        m_Near			= cam.m_Near;
        m_Far			= cam.m_Far;

        m_ViewMatrix	= cam.m_ViewMatrix;
        m_ProjectionMatrix = cam.m_ProjectionMatrix;
    }
}   // End of CG184