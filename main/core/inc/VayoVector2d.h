/*************************************************************************\
* 望友引擎1.0
* Copyright (c) 2018-2019 authored by 朱加浩
* 二维向量
\*************************************************************************/
#ifndef __VAYO_VECTOR2D_H__
#define __VAYO_VECTOR2D_H__

#include "VayoMath.h"

namespace Vayo {

	template<typename T>
	class Vector2d
	{
	public:
		Vector2d() : _x(0), _y(0) {}
		Vector2d(T x, T y) : _x(x), _y(y) {}
		Vector2d(const Vector2d<T>& other) : _x(other._x), _y(other._y) {}

		// operators

		Vector2d<T>& operator=(const Vector2d<T>& other) { _x = other._x; _y = other._y; return *this; }

		Vector2d<T> operator+(const Vector2d<T>& other) const { return Vector2d<T>(_x + other._x, _y + other._y); }
		Vector2d<T>& operator+=(const Vector2d<T>& other) { _x += other._x; _y += other._y; return *this; }

		Vector2d<T> operator-(const Vector2d<T>& other) const { return Vector2d<T>(_x - other._x, _y - other._y); }
		Vector2d<T>& operator-=(const Vector2d<T>& other) { _x -= other._x; _y -= other._y; return *this; }

		Vector2d<T> operator*(const Vector2d<T>& other) const { return Vector2d<T>(_x * other._x, _y * other._y); }
		Vector2d<T>& operator*=(const Vector2d<T>& other) { _x *= other._x; _y *= other._y; return *this; }
		Vector2d<T> operator*(const T v) const { return Vector2d<T>(_x * v, _y * v); }
		Vector2d<T>& operator*=(const T v) { _x *= v; _y *= v; return *this; }

		Vector2d<T> operator/(const Vector2d<T>& other) const { return Vector2d<T>(_x / other._x, _y / other._y); }
		Vector2d<T>& operator/=(const Vector2d<T>& other) { _x /= other._x; _y /= other._y; return *this; }
		Vector2d<T> operator/(const T v) const { return Vector2d<T>(_x / v, _y / v); }
		Vector2d<T>& operator/=(const T v) { _x /= v; _y /= v; return *this; }

		T operator^(const Vector2d<T>& other) const { return _x * other._y - other._x * _y; }

		bool operator==(const Vector2d<T>& other) const { return equals(_x, other._x) && equals(_y, other._y); }
		bool operator!=(const Vector2d<T>& other) const { return !equals(_x, other._x) || !equals(_y, other._y); }

		inline friend wstringstream& operator<<(wstringstream& ss, const Vector2d<T>& in)
		{
			ss << in._x << L" " << in._y << L" ";
			return ss;
		}

		inline friend wstringstream& operator >> (wstringstream& ss, Vector2d<T>& out)
		{
			ss >> out._x >> out._y;
			return ss;
		}

		// functions

		void set(const T& x, const T& y) { _x = x; _y = y; }
		void set(const Vector2d<T>& p) { _x = p._x; _y = p._y; }

		float getLength() const { return sqrtf(_x*_x + _y*_y); }

		T getLengthSQ() const { return _x*_x + _y*_y; }

		T dotProduct(const Vector2d<T>& other) const
		{
			return _x*other._x + _y*other._y;
		}

		float getDistanceFrom(const Vector2d<T>& other) const
		{
			float vx = _x - other._x; float vy = _y - other._y;
			return sqrtf(vx*vx + vy*vy);
		}

		void invert()
		{
			_x *= -1.0f;
			_y *= -1.0f;
		}

		void rotateBy(float degrees, const Vector2d<T>& center)
		{
			degrees = VayoDegToRad(degrees);
			T cs = (T)cosf(degrees);
			T sn = (T)sinf(degrees);

			_x -= center._x;
			_y -= center._y;

			set(_x*cs - _y*sn, _x*sn + _y*cs);

			_x += center._x;
			_y += center._y;
		}

		Vector2d<T>& normalize()
		{
			T len = (T)(1.0f / getLength());
			_x *= len;
			_y *= len;
			return *this;
		}

		// Calculates the angle of this vector in grad.
		// return Returns a value between 0 and 360.
		inline float getAngle() const
		{
			if (_y == 0.0f)
				return _x > 0.0f ? 90.0f : 180.0f;

			float tmp = _y / sqrtf(_x*_x + _y*_y);
			tmp = VayoRadToDeg(atanf(sqrtf(1 - tmp*tmp) / tmp));

			if (_x > 0.0f && _y > 0.0f)
				return tmp + 270;
			else if (_x > 0.0f && _y < 0.0f)
				return tmp + 90;
			else if (_x < 0.0f && _y < 0.0f)
				return 90 - tmp;
			else if (_x<0.0f && _y>0.0f)
				return 270 - tmp;

			return tmp;
		}

		// Calculates the angle between this vector and another one in grad.
		// return Returns a value between 0 and 90.
		inline float getAngleWith(const Vector2d<T>& b) const
		{
			float tmp = _x*b._x + _y*b._y;

			if (tmp == 0.0f)
				return 90.0f;

			tmp = tmp / sqrtf((_x*_x + _y*_y) * (b._x*b._x + b._y*b._y));
			if (tmp < 0.0f) tmp = -tmp;

			return VayoRadToDeg(atanf(sqrtf(1 - tmp*tmp) / tmp));
		}

		// member variables

		T _x, _y;

		static const Vector2d<T> XAxis;
		static const Vector2d<T> YAxis;
		static const Vector2d<T> Origin;
	};

	template<typename T>
	const Vector2d<T> Vector2d<T>::XAxis(1, 0);
	template<typename T>
	const Vector2d<T> Vector2d<T>::YAxis(0, 1);
	template<typename T>
	const Vector2d<T> Vector2d<T>::Origin(0, 0);

#define     Position2d               Vector2d
	typedef Vector2d<float>          Vector2df;
	typedef Vector2d<int>            Vector2di;
	typedef Vector2d<unsigned int>   Vector2du;
	typedef Position2d<float>        Position2df;
	typedef Position2d<int>          Position2di;
	typedef Position2d<unsigned int> Position2du;

}

#endif // __VAYO_VECTOR2D_H__
