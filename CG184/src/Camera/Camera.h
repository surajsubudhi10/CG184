#pragma once

#include "../Maths/Matrix4D.h"

namespace CG184 
{
	class Camera
	{
	public:
		Camera();
		Camera(const Vector3D& pos, const Vector3D& _front, const Vector3D& _up);
		Camera(float camFov, float aspect, float camNear, float camFar);
		~Camera();

		void SetFrustrum(float camFov, float aspect, float camNear, float camFar);
		void Set(const Vector3D& pos, const Vector3D& _front, const Vector3D& _up);

		inline void SetFOV(float camFov)			{ fov = camFov; UpdateProjectionMatrix(); }
		inline void SetAspectRatio(float aspect)	{ aspect_ratio = aspect; UpdateProjectionMatrix(); }
		inline void SetNearPlane(float _near)		{ near = _near; UpdateProjectionMatrix(); }
		inline void SetFarPlane(float _far)			{ far = _far; UpdateProjectionMatrix(); }

		inline void SetPosition(const Vector3D& pos) { position = pos; UpdateViewMatrix(); }
		inline void SetFront(const Vector3D& _front) { front = _front; UpdateViewMatrix(); }
		inline void SetUp(const Vector3D& _up)		 { up = _up; UpdateViewMatrix(); }

		inline Matrix4D& GetViewMatrix()		{ return viewMatrix; }
		inline Matrix4D& GetProjectionMatrix()	{ return projectionMatrix; }

		inline Vector3D& GetCamPos()			{ return position; }

	private:
		Matrix4D prespective(float fov, float aspect_ratio, float near, float far);
		Matrix4D LookAt(Vector3D eyePos, Vector3D target, Vector3D up);

		void UpdateProjectionMatrix();
		void UpdateViewMatrix();

		Vector3D position;
		Vector3D front;
		Vector3D up;

		float fov;
		float aspect_ratio;
		float near;
		float far;

		Matrix4D viewMatrix;
		Matrix4D projectionMatrix;
	};

	
}