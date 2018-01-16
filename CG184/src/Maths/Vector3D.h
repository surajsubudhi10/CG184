#pragma once

#include <ostream>

namespace CG184
{
    // TODO Create Template classes for Vector3D
	class Vector3D
	{
	public:
		Vector3D();
		Vector3D(float _x, float _y, float _Z);

        explicit Vector3D(float val);
		Vector3D(const Vector3D& _vec);

		Vector3D add(const Vector3D& vec) const;
		Vector3D sub(const Vector3D& vec) const;
		Vector3D mult(const Vector3D& vec) const;
		Vector3D divide(const Vector3D& vec) const;
		
		Vector3D mult(float multiplier) const;
		Vector3D divide(float diveder) const;

		float dot(const Vector3D& vec) const;
		Vector3D cross(const Vector3D& vec) const;

		void normalize();
		Vector3D norm() const;
		float squaredLength() const;
		float length()const ;

		void negate();

		const float at(int i) const;
		float at(int i);

		bool isEqual(const Vector3D& vec) const;


		float		operator[](int i) const;
		Vector3D&	operator=(const Vector3D& vec);
		Vector3D    operator+(const Vector3D& vec);
		Vector3D    operator-(const Vector3D& vec);
		Vector3D    operator*(const Vector3D& vec);
		Vector3D    operator/(const Vector3D& vec);
		Vector3D    operator*(float val);
		Vector3D    operator*(float val) const;
		Vector3D    operator/(float val);
		Vector3D&   operator+=(const Vector3D& vec);
		Vector3D&   operator-=(const Vector3D& vec);
		Vector3D&   operator*=(const Vector3D& vec);
		Vector3D&   operator/=(const Vector3D& vec);
		Vector3D&   operator*=(float val);
		Vector3D&   operator/=(float val);
		bool		operator==(const Vector3D& vec);
		bool		operator!=(const Vector3D& vec);


		~Vector3D();

        const static Vector3D Up;
        const static Vector3D Right;
        const static Vector3D Forward ;

	public:
		float x, y, z;
	};

    std::ostream& operator<< (std::ostream& stream, const Vector3D& vec);

}
