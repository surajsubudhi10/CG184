#include "Vector3D.h"
#include <cassert>
#include <math.h>

namespace CG184 
{
	Vector3D::Vector3D() : x(0), y(0), z(0)
	{
	}

	Vector3D::~Vector3D()
	{
	}

	Vector3D::Vector3D(double _x, double _y, double _z) : x(_x), y(_y), z(_z)
	{
	}

	Vector3D::Vector3D(double val) : x(val), y(val), z(val)
	{
	}

	Vector3D::Vector3D(const Vector3D& _vec) : x(_vec.x), y(_vec.y), z(_vec.z)
	{
	}

	Vector3D Vector3D::add(const Vector3D& vec) const
	{
		double _x = x + vec.x;
		double _y = y + vec.y;
		double _z = z + vec.z;

		return Vector3D(_x, _y, _z);
	}

	Vector3D Vector3D::sub(const Vector3D& vec) const
	{
		double _x = x - vec.x;
		double _y = y - vec.y;
		double _z = z - vec.z;

		return Vector3D(_x, _y, _z);
	}

	Vector3D Vector3D::mult(const Vector3D& vec) const
	{
		double _x = x * vec.x;
		double _y = y * vec.y;
		double _z = z * vec.z;

		return Vector3D(_x, _y, _z);
	}

	Vector3D Vector3D::divide(const Vector3D& vec) const
	{
		assert((vec.x != 0.0 && vec.y != 0.0 && vec.z != 0.0) && "Dividing with Zero.");

		double _x = x / vec.x;
		double _y = y / vec.y;
		double _z = z / vec.z;

		return Vector3D(_x, _y, _z);
	}

	Vector3D Vector3D::mult(double multiplier) const
	{
		double _x = x * multiplier;
		double _y = y * multiplier;
		double _z = z * multiplier;

		return Vector3D(_x, _y, _z);
	}

	Vector3D Vector3D::divide(double diveder) const
	{
		assert(diveder != 0.0 && "Dividing with zero.");

		double _x = x / diveder;
		double _y = y / diveder;
		double _z = z / diveder;

		return Vector3D(_x, _y, _z);
	}

	double Vector3D::dot(const Vector3D& vec) const 
	{
		return (x * vec.x + y * vec.y + z * vec.z);
	}

	Vector3D Vector3D::cross(const Vector3D& vec) const 
	{
		double _x = (y * vec.z) - (z * vec.y);
		double _y = (z * vec.x) - (x * vec.z);
		double _z = (x * vec.y) - (y * vec.x);

		return Vector3D(_x, _y, _z);
	}

	void Vector3D::normalize() 
	{
		double len = length();
		assert(len != 0 && "length must be greater than zero");
		divide(len);
	}

	Vector3D Vector3D::norm() const 
	{
		double len = length();
		assert(len != 0 && "length must be greater than zero");

		double _x = x / len;
		double _y = y / len;
		double _z = z / len;

		return Vector3D(_x, _y, _z);
	}

	double Vector3D::squaredLength() const 
	{
		return (x * x + y * y + z * z);
	}

	double Vector3D::length()const 
	{
		return sqrt(squaredLength());
	}

	void Vector3D::negate() 
	{
		mult(-1.0f);
	}

	const double Vector3D::at(size_t i) const 
	{
		assert((i >= 0 && i < 3) && "i must be between 0 to 2");

		if (i == 0)
			return x;
		else if (i == 1)
			return y;
		else
			return z;
	}

	double Vector3D::at(size_t i)
	{
		assert((i >= 0 && i < 3) && "i must be between 0 to 2");

		if (i == 0)
			return x;
		else if (i == 1)
			return y;
		else
			return z;
	}

	bool Vector3D::isEqual(const Vector3D& vec) const
	{
		if (x == vec.x && y == vec.y && z == vec.z) 
		{
			return true;
		}
		else
		{
			return false;
		}
	}


	double		Vector3D::operator[](size_t i) const
	{
		return at(i);
	}

	Vector3D&	Vector3D::operator=(const Vector3D& vec) 
	{
		if (this == &vec)
			return *this;

		x = vec.x;
		y = vec.y;
		z = vec.z;

		return *this;
	}

	Vector3D&   Vector3D::operator+(const Vector3D& vec) 
	{
		return add(vec);
	}

	Vector3D&   Vector3D::operator-(const Vector3D& vec) 
	{
		return sub(vec);
	}

	Vector3D&   Vector3D::operator*(const Vector3D& vec) 
	{
		return mult(vec);
	}

	Vector3D&   Vector3D::operator/(const Vector3D& vec) 
	{
		return divide(vec);
	}


	Vector3D&   Vector3D::operator*(double val) 
	{
		return mult(val);
	}

	Vector3D&   Vector3D::operator/(double val) 
	{
		return divide(val);
	}

	Vector3D&   Vector3D::operator+=(const Vector3D& vec) 
	{
		Vector3D _vec = *this + vec;
		return _vec;
	}

	Vector3D&   Vector3D::operator-=(const Vector3D& vec) 
	{
		Vector3D _vec = *this - vec;
		return _vec;
	}

	Vector3D&   Vector3D::operator*=(const Vector3D& vec) 
	{
		Vector3D _vec = *this * vec;
		return _vec;
	}

	Vector3D&   Vector3D::operator/=(const Vector3D& vec) 
	{
		Vector3D _vec = *this / vec;
		return _vec;
	}
	Vector3D&   Vector3D::operator*=(double val) 
	{
		Vector3D _vec = *this * val;
		return _vec;
	}

	Vector3D&   Vector3D::operator/=(double val) 
	{
		Vector3D _vec = *this / val;
		return _vec;
	}

	bool		Vector3D::operator==(const Vector3D& vec) 
	{
		return isEqual(vec);
	}

	bool		Vector3D::operator!=(const Vector3D& vec) 
	{
		return !(isEqual(vec));
	}

}