#include "Vector4D.h"
#include <cassert>
#include <math.h>

namespace CG184
{
	Vector4D::Vector4D() : x(0), y(0), z(0)
	{
	}

	Vector4D::~Vector4D()
	{
	}

	Vector4D::Vector4D(double _x, double _y, double _z, double _w) : x(_x), y(_y), z(_z), w(_w)
	{
	}

	Vector4D::Vector4D(double val) : x(val), y(val), z(val), w(val)
	{
	}

	Vector4D::Vector4D(const Vector4D& _vec) : x(_vec.x), y(_vec.y), z(_vec.z), w(_vec.w)
	{
	}

	Vector4D::Vector4D(const Vector3D& _vec, double wval) : x(_vec.x), y(_vec.y), z(_vec.z), w(wval)
	{
	}

	Vector4D Vector4D::add(const Vector4D& vec) const
	{
		double _x = x + vec.x;
		double _y = y + vec.y;
		double _z = z + vec.z;
		double _w = w + vec.w;

		return Vector4D(_x, _y, _z, _w);
	}

	Vector4D Vector4D::sub(const Vector4D& vec) const
	{
		double _x = x - vec.x;
		double _y = y - vec.y;
		double _z = z - vec.z;
		double _w = w - vec.w;

		return Vector4D(_x, _y, _z, _w);
	}

	Vector4D Vector4D::mult(const Vector4D& vec) const
	{
		double _x = x * vec.x;
		double _y = y * vec.y;
		double _z = z * vec.z;
		double _w = w * vec.w;

		return Vector4D(_x, _y, _z, _w);
	}

	Vector4D Vector4D::divide(const Vector4D& vec) const
	{
		assert((vec.x != 0.0 && vec.y != 0.0 && vec.z != 0.0 && vec.w != 0.0) && "Dividing with Zero.");

		double _x = x / vec.x;
		double _y = y / vec.y;
		double _z = z / vec.z;
		double _w = w / vec.w;

		return Vector4D(_x, _y, _z, _w);
	}

	Vector4D Vector4D::mult(double multiplier) const
	{
		double _x = x * multiplier;
		double _y = y * multiplier;
		double _z = z * multiplier;
		double _w = w * multiplier;

		return Vector4D(_x, _y, _z, _w);
	}

	Vector4D Vector4D::divide(double diveder) const
	{
		assert(diveder != 0.0 && "Dividing with zero.");

		double _x = x / diveder;
		double _y = y / diveder;
		double _z = z / diveder;
		double _w = w / diveder;

		return Vector4D(_x, _y, _z, _w);
	}

	const double Vector4D::at(size_t i) const
	{
		assert((i >= 0 && i < 4) && "i must be between 0 to 3");

		if (i == 0)
			return x;
		else if (i == 1)
			return y;
		else if (i == 2)
			return z;
		else
			return w;
	}

	double Vector4D::at(size_t i)
	{
		assert((i >= 0 && i < 4) && "i must be between 0 to 3");

		if (i == 0)
			return x;
		else if (i == 1)
			return y;
		else if (i == 2)
			return z;
		else
			return w;
	}

	bool Vector4D::isEqual(const Vector4D& vec) const
	{
		if (x == vec.x && y == vec.y && z == vec.z && w == vec.w)
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	double		Vector4D::operator[](size_t i) const
	{
		return at(i);
	}

	Vector4D&	Vector4D::operator=(const Vector4D& vec)
	{
		if (this == &vec)
			return *this;

		x = vec.x;
		y = vec.y;
		z = vec.z;
		w = vec.w;

		return *this;
	}

	Vector4D&   Vector4D::operator+(const Vector4D& vec)
	{
		return add(vec);
	}

	Vector4D&   Vector4D::operator-(const Vector4D& vec)
	{
		return sub(vec);
	}

	Vector4D&   Vector4D::operator*(const Vector4D& vec)
	{
		return mult(vec);
	}

	Vector4D&   Vector4D::operator/(const Vector4D& vec)
	{
		return divide(vec);
	}


	Vector4D&   Vector4D::operator*(double val)
	{
		return mult(val);
	}

	Vector4D&   Vector4D::operator/(double val)
	{
		return divide(val);
	}

	Vector4D&   Vector4D::operator+=(const Vector4D& vec)
	{
		Vector4D _vec = *this + vec;
		return _vec;
	}

	Vector4D&   Vector4D::operator-=(const Vector4D& vec)
	{
		Vector4D _vec = *this - vec;
		return _vec;
	}

	Vector4D&   Vector4D::operator*=(const Vector4D& vec)
	{
		Vector4D _vec = *this * vec;
		return _vec;
	}

	Vector4D&   Vector4D::operator/=(const Vector4D& vec)
	{
		Vector4D _vec = *this / vec;
		return _vec;
	}
	Vector4D&   Vector4D::operator*=(double val)
	{
		Vector4D _vec = *this * val;
		return _vec;
	}

	Vector4D&   Vector4D::operator/=(double val)
	{
		Vector4D _vec = *this / val;
		return _vec;
	}

	bool		Vector4D::operator==(const Vector4D& vec)
	{
		return isEqual(vec);
	}

	bool		Vector4D::operator!=(const Vector4D& vec)
	{
		return !(isEqual(vec));
	}

}