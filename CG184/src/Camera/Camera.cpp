#include "Camera.h"
#include "../Maths/Maths.h"
#include <math.h>

namespace CG184 
{
	
	Camera::Camera() 
	{
		fov = 45.0; aspect_ratio = (float)(8 / 6); near = 0.1f; far = 100.0f;
		position = Vector3D(0.0f, 0.0f, 3.0f);
		front = Vector3D(0.0f, 0.0f, -1.0f);
		up = Vector3D(0.0f, 1.0f, 0.0f);

		viewMatrix = LookAt(position, position + front, up);
		projectionMatrix = prespective(fov, aspect_ratio, near, far);
	}

	Camera::Camera(const Vector3D& pos, const Vector3D& _front, const Vector3D& _up) 
	{
		fov = 45.0; aspect_ratio = (float)(8 / 6); near = 0.1f; far = 100.0f;
		position	= pos;
		front		= _front;
		up			= _up;

		viewMatrix = LookAt(position, position + front, up);
		projectionMatrix = prespective(fov, aspect_ratio, near, far);
	}


	Camera::Camera(float camFov, float aspect, float camNear, float camFar)
	{
		fov = camFov; aspect_ratio = aspect; near = camNear; far = camFar;
		position = Vector3D(0.0f, 0.0f,  3.0f);
		front	 = Vector3D(0.0f, 0.0f, -1.0f);
		up		 = Vector3D(0.0f, 1.0f,  0.0f);

		viewMatrix = LookAt(position, position + front, up);
		projectionMatrix = prespective(fov, aspect_ratio, near, far);
	}

	void Camera::SetFrustrum(float camFov, float aspect, float camNear, float camFar) 
	{
		fov = camFov; aspect_ratio = aspect; near = camNear; far = camFar;
		UpdateProjectionMatrix();
	}

	void Camera::Set(const Vector3D& pos, const Vector3D& _front, const Vector3D& _up) 
	{
		position = pos;
		front	 = _front;
		up		 = _up;
		UpdateViewMatrix();
	}

	Camera::~Camera()
	{
	}

	void Camera::UpdateProjectionMatrix() 
	{
		projectionMatrix = prespective(fov, aspect_ratio, near, far);
	}

	void Camera::UpdateViewMatrix() 
	{
		viewMatrix = LookAt(position, position + front, up);
	}

	Matrix4D Camera::prespective(float fovInDeg, float aspect_ratio, float near, float far)
	{
		auto fovInRad = (float)(PI * fovInDeg / 180.0f);
		const float tanHalfFov = tan(fovInRad / 2.0f);

		Matrix4D result(1.0f);

		result.elements[0]  =  1 / (aspect_ratio * tanHalfFov);
		result.elements[5]  =  1 / tanHalfFov;
		result.elements[10] = -1 * (far + near) / (far - near);
		result.elements[15] =  0.0f;
		result.elements[11] = -1.0f;
		result.elements[14] = (-2 * far * near) / (far - near);

		return result;
	}

	Matrix4D Camera::LookAt(Vector3D eyePos, Vector3D target, Vector3D up)
	{
		Vector3D f(target - eyePos);
		f.normalize();

		Vector3D s = (f.cross(up));
		s.normalize();

		Vector3D u = s.cross(f);

		float ex = -s.dot(eyePos);
		float ey = -u.dot(eyePos);
		float ez = f.dot(eyePos);

		Matrix4D lookMat(
			 s.x,  s.y,  s.z, -eyePos.x, //ex,
			 u.x,  u.y,  u.z, -eyePos.y, //ey,
			-f.x, -f.y, -f.z, -eyePos.z, //ez,
			   0,    0,    0,  1
		);

		//lookMat = lookMat.transpose();

		return lookMat;
	}

    Camera::Camera(Camera &cam) {
        position    = cam.position;
        front       = cam.front;
        up          = cam.up;

        fov = cam.fov;
        aspect_ratio = cam.aspect_ratio;
        near = cam.near;
        far = cam.far;

        viewMatrix = cam.viewMatrix;
        projectionMatrix = cam.projectionMatrix;
    }

}