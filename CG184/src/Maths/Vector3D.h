#pragma once

namespace CG184 
{
	class Vector3D
	{
	public:
		Vector3D();
		Vector3D(double _x, double _y, double _Z);
		Vector3D(double val);
		Vector3D(const Vector3D& _vec);

		Vector3D add(const Vector3D& vec) const;
		Vector3D sub(const Vector3D& vec) const;
		Vector3D mult(const Vector3D& vec) const;
		Vector3D divide(const Vector3D& vec) const;
		
		Vector3D mult(double multiplier) const;
		Vector3D divide(double diveder) const;

		double dot(const Vector3D& vec) const;
		Vector3D cross(const Vector3D& vec) const;

		void normalize();
		Vector3D norm() const;
		double squaredLength() const;
		double length()const ;

		void negate();

		const double at(size_t i) const;
		double at(size_t i);

		bool isEqual(const Vector3D& vec) const;


		double		operator[](size_t i) const;
		Vector3D&	operator=(const Vector3D& vec);
		Vector3D&   operator+(const Vector3D& vec);
		Vector3D&   operator-(const Vector3D& vec);
		Vector3D&   operator*(const Vector3D& vec);
		Vector3D&   operator/(const Vector3D& vec);
		Vector3D&   operator*(double val);
		Vector3D&   operator/(double val);
		Vector3D&   operator+=(const Vector3D& vec);
		Vector3D&   operator-=(const Vector3D& vec);
		Vector3D&   operator*=(const Vector3D& vec);
		Vector3D&   operator/=(const Vector3D& vec);
		Vector3D&   operator*=(double val);
		Vector3D&   operator/=(double val);
		bool		operator==(const Vector3D& vec);
		bool		operator!=(const Vector3D& vec);


		~Vector3D();

	public:
		double x, y, z;
	};

	
}
