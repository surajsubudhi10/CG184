#pragma once
#include "Vector4D.h"

namespace CG184 
{
    // TODO Create Template classes for Matrices
	class Matrix4D
	{
	public:

		//! Basic Matrix Structure.
		//! Matrix4D arr = {
		//!     {0, 4,  8, 12},
		//!     {1, 5,  9, 13},
		//!     {2, 6, 10, 14},
		//!     {3, 7, 11, 15}
		//! };
		float elements[4 * 4];
		

		Matrix4D();
		Matrix4D(float diagonal);
		Matrix4D(Vector4D col1, Vector4D col2, Vector4D col3, Vector4D col4);
		Matrix4D(const Matrix4D& mat);

		Matrix4D(
			float m00, float m01, float m02,
			float m10, float m11, float m12,
			float m20, float m21, float m22);


		Matrix4D(
			float m00, float m01, float m02, float m03,
			float m10, float m11, float m12, float m13,
			float m20, float m21, float m22, float m23,
			float m30, float m31, float m32, float m33);

		Vector4D getColumn(int index);
		

		void SetRow(int i, const Vector4D& vec);
		void SetColumn(int i, const Vector4D& vec);

		Matrix4D multiply(float scalar);
		Matrix4D divide(float scalar);
		Matrix4D multiply(const Matrix4D& other);
		Vector3D multiply(const Vector3D& other);
		Vector4D multiply(const Vector4D& other);

		// TODO add more Set functions
		void Set(float diagonal);
		void Set(Vector4D col1, Vector4D col2, Vector4D col3, Vector4D col4);

		Matrix4D& operator=(const Matrix4D& rhs);

        // TODO Implement the inverse and matrix multiplication
		friend Matrix4D operator*(Matrix4D left, const Matrix4D& right);
		Matrix4D& operator*=(const Matrix4D& other);

		float at(int i);
		float operator[](int i);

		Matrix4D transpose() const;
		void inverse();

		~Matrix4D();


		


	private:
		
	};

	
}