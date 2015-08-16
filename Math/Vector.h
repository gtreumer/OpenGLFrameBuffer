#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>

namespace Math
{
	//const float Pi = 4 * std::atan(1.0f);
    const float Pi = 3.14159265359f;
	const float TwoPi = 2 * Pi;

	template <typename T>
	struct Vector2
	{
		Vector2() : x(0), y(0) {}
		Vector2(T x, T y) : x(x), y(y) {}

		Vector2 operator-(const Vector2& v) const
		{
			return Vector2(x - v.x, y - v.y);
		}

        Vector2 operator+(const Vector2& v) const
        {
            return Vector2(x + v.x, y + v.y);
        }

		void operator+=(const Vector2& v)
		{
			*this = Vector2(x + v.x, y + v.y);
		}

		void operator-=(const Vector2& v)
		{
			*this = Vector2(x - v.x, y - v.y);
		}

		Vector2 operator/(float s) const
		{
			return Vector2(x / s, y / s);
		}

		Vector2 operator*(float s) const
		{
			return Vector2(x * s, y * s);
		}

		void operator/=(float s)
		{
			*this = Vector2(x / s, y / s);
		}

		void operator*=(float s)
		{
			*this = Vector2(x * s, y * s);
		}

        operator Vector2<float>() const
        {
            return Vector2<float>(x, y);
        }

        bool operator==(const Vector2& v) const
        {
            return x == v.x && y == v.y;
        }

        bool operator!=(const Vector2& v) const
        {
            return !(*this == v);
        }

        T Dot(const Vector2& v) const
        {
            return x * v.x + y * v.y;
        }

		void Normalize()
		{
			float s = 1.0f / Length();
			x *= s;
			y *= s;
		}

		Vector2 Normalized() const
		{
			Vector2 v = *this;
			v.Normalize();
			return v;
		}

		T LengthSquared() const
		{
			return x * x + y * y;
		}

		T Length() const
		{
			return sqrt(LengthSquared());
		}

		const T* Pointer() const
		{
			return &x;
		}

		Vector2 Lerp(float t, const Vector2& v) const
		{
			return Vector2(x * (1 - t) + v.x * t,
						   y * (1 - t) + v.y * t);
		}

        T x;
        T y;
	}; /*Vector2*/

    template <typename T>
    struct Vector3
    {
        Vector3() : x(0), y(0), z(0) {}   
        Vector3(T x, T y, T z) : x(x), y(y), z(z) {}

        Vector3 operator+(const Vector3& v) const
        {
            return Vector3(x + v.x, y + v.y, z + v.z);
        }

        void operator+=(const Vector3& v)
        {
            x += v.x;
            y += v.y;
            z += v.z;
        }

        void operator-=(const Vector3& v)
        {
            x -= v.x;
            y -= v.y;
            z -= v.z;
        }

        void operator/=(T s)
        {
            x /= s;
            y /= s;
            z /= s;
        }

        Vector3 operator-(const Vector3& v) const
        {
            return Vector3(x - v.x, y - v.y, z - v.z);
        }

        Vector3 operator-() const
        {
            return Vector3(-x, -y, -z);
        }

        Vector3 operator*(T s) const
        {
            return Vector3(x * s, y * s, z * s);
        }

        Vector3 operator/(T s) const
        {
            return Vector3(x / s, y / s, z / s);
        }

        void operator*=(T s)
        {
            x *= s;
            y *= s;
            z *= s;
        }

        bool operator==(const Vector3& v) const
        {
            return x == v.x && y == v.y && z == v.z;
        }

        bool operator!=(const Vector3& v) const
        {
            return !(*this == v);
        }

        Vector3 Lerp(float t, const Vector3& v) const
        {
            return Vector3(x * (1 - t) + v.x * t,
                y * (1 - t) + v.y * t,
                z * (1 - t) + v.z * t);
        }

        T LengthSquared()
        {
            return x * x + y * y + z * z;
        }

        T Length()
        {
            return std::sqrt(x * x + y * y + z * z);
        }

        void Normalize()
        {
            float s = 1.0f / Length();
            x *= s;
            y *= s;
            z *= s;
        }

        Vector3 Normalized() const
        {
            Vector3 v = *this;
            v.Normalize();
            return v;
        }

        Vector3 Cross(const Vector3& v) const
        {
            return Vector3(y * v.z - z * v.y,
                           z * v.x - x * v.z,
                           x * v.y - y * v.x);
        }

        T Dot(const Vector3& v) const
        {
            return x * v.x + y * v.y + z * v.z;
        }

        //Vector3 operator=(const Vector3& v)
        //{
        //    x = v.x;
        //    y = v.y;
        //    z = v.z;
        //    return *this;
        //}

        const T* Pointer() const
        {
            return &x;
        }

        T x;
        T y;
        T z;
    }; /*Vector3*/

    template <typename T>
    struct Vector4
    {
        Vector4() {}
        Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
        Vector4(const Vector3<T>& v, T w) : x(v.x), y(v.y), z(v.z), w(w) {}

        T Dot(const Vector4& v) const
        {
            return x * v.x + y * v.y + z * v.z + w * v.w;
        }

        Vector4 Lerp(float t, const Vector4& v) const
        {
            return Vector4(x * (1 - t) + v.x * t,
                           y * (1 - t) + v.y * t,
                           z * (1 - t) + v.z * t,
                           w * (1 - t) + v.w * t);
        }

        bool operator==(const Vector4& v) const
        {
            return x == v.x && y == v.y && z == v.z && w == v.w;
        }

        const T* Pointer() const
        {
            return &x;
        }

        T x;
        T y;
        T z;
        T w;
    };

    typedef Vector2<bool> Vec2b;
    
    typedef Vector2<int> Vec2i;
    typedef Vector3<int> Vec3i;
    typedef Vector4<int> Vec4i;

    typedef Vector2<float> Vec2f;
    typedef Vector3<float> Vec3f;
    typedef Vector4<float> Vec4f;
}; /*namespace Math*/

#endif