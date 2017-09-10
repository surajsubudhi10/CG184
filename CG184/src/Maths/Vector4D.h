#pragma once
#include "Vector3D.h"

namespace CG184
{
	class Vector4D
	{
	public:
		Vector4D();
		Vector4D(double _x, double _y, double _Z, double _w);
		Vector4D(double val);
		Vector4D(const Vector4D& _vec);
		Vector4D(const Vector3D& _vec, double wval);

		Vector4D add(const Vector4D& vec) const;
		Vector4D sub(const Vector4D& vec) const;
		Vector4D mult(const Vector4D& vec) const;
		Vector4D divide(const Vector4D& vec) const;

		Vector4D mult(double multiplier) const;
		Vector4D divide(double diveder)const ;

		const double at(size_t i) const;
		double at(size_t i);

		bool isEqual(const Vector4D& vec) const;

		double		operator[](size_t i) const;
		Vector4D&	operator=(const Vector4D& vec);
		Vector4D&   operator+(const Vector4D& vec);
		Vector4D&   operator-(const Vector4D& vec);
		Vector4D&   operator*(const Vector4D& vec);
		Vector4D&   operator/(const Vector4D& vec);
		Vector4D&   operator*(double val);
		Vector4D&   operator/(double val);
		Vector4D&   operator+=(const Vector4D& vec);
		Vector4D&   operator-=(const Vector4D& vec);
		Vector4D&   operator*=(const Vector4D& vec);
		Vector4D&   operator/=(const Vector4D& vec);
		Vector4D&   operator*=(double val);
		Vector4D&   operator/=(double val);
		bool		operator==(const Vector4D& vec);
		bool		operator!=(const Vector4D& vec);


		~Vector4D();

	public:
		double x, y, z, w;
	};


}
