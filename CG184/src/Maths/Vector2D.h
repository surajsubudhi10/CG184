#pragma once

namespace CG184
{
	class Vector2D
	{
	public:
		Vector2D();
		Vector2D(float _x, float _y);
		Vector2D(float val);
		Vector2D(const Vector2D& _vec);

		Vector2D add(const Vector2D& vec) const;
		Vector2D sub(const Vector2D& vec) const;
		Vector2D mult(const Vector2D& vec) const;
		Vector2D divide(const Vector2D& vec) const;

		Vector2D mult(float multiplier) const;
		Vector2D divide(float diveder) const;

		float dot(const Vector2D& vec) const;
		float cross(const Vector2D& vec) const;

		void normalize();
		Vector2D norm() const;
		float squaredLength() const;
		float length()const;

		void negate();

		const float at(int i) const;
		float at(int i);

		bool isEqual(const Vector2D& vec) const;


		float		operator[](int i) const;
		Vector2D&	operator=(const Vector2D& vec);
		Vector2D   operator+(const Vector2D& vec);
		Vector2D   operator-(const Vector2D& vec);
		Vector2D   operator*(const Vector2D& vec);
		Vector2D   operator/(const Vector2D& vec);
		Vector2D   operator*(float val);
		Vector2D   operator/(float val);
		Vector2D&   operator+=(const Vector2D& vec);
		Vector2D&   operator-=(const Vector2D& vec);
		Vector2D&   operator*=(const Vector2D& vec);
		Vector2D&   operator/=(const Vector2D& vec);
		Vector2D&   operator*=(float val);
		Vector2D&   operator/=(float val);
		bool		operator==(const Vector2D& vec);
		bool		operator!=(const Vector2D& vec);


		~Vector2D();

	public:
		float x, y;
	};


}
