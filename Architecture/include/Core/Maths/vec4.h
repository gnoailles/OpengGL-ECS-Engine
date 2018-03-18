#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <math.h>
#include <string>
#include <glm/vec4.hpp>
#include <Core/Maths/vec3.h>

namespace Core
{
	namespace Maths
	{
		template<typename T>
		class vec4
		{
		public:
			T x;
			T y;
			T z;
			T w;

		public:
			static float ToDegree(const double &angle)
			{
				return angle * 180.0 / M_PI;
			}
			static float ToRad(const double &angle)
			{
				return angle * M_PI / 180.0f;
			}

			vec4(const T& p_x = 0.0f, const T& p_y = 0.0f, const T& p_z = 0.0f, const T& p_w = 1.0f) : x{ p_x }, y{ p_y }, z{ p_z }, w{ p_w } {}
			vec4(const vec3<T>& vec3, const T& p_w = 1.0f) : x{ vec3.x }, y{ vec3.y }, z{ vec3.z }, w{ p_w } {}
			vec4(const vec4 &p_other)
			{
				this->x = p_other.x;
				this->y = p_other.y;
				this->z = p_other.z;
				this->w = p_other.w;
			}

			vec4 &operator=(const vec4 &p_other)
			{
				this->x = p_other.x;
				this->y = p_other.y;
				this->z = p_other.z;
				this->w = p_other.w;
				return *this;
			}

			~vec4() = default;

			vec4 Homogenize() const
			{
				if (this->w != 0 && this->w != 1)
				{
					vec4 homogenized = this->Div(this->w);
					homogenized.w = 1;
					return homogenized;
				}
				return *this;
			}

			void Homogenize()
			{
				if (this->w != 0 && this->w != 1)
				{
					this->Div(this->w);
					this->w /= this->w;
				}
			}

			vec4 Normalize() const
			{
				float mag = this->GetMagnitude();
				if (mag != 0 && mag != 1)
				{
					return this->Div(mag);
				}
				return this;
			}

			void Normalize()
			{
				float mag = this->GetMagnitude();
				if (mag != 0 && mag != 1)
				{
					this->Div(mag);
				}
			}

			T MagSq() const { return (this->x * this->x) + (this->y * this->y) + (this->z * this->z); }

			T GetMagnitude() const
			{
				if (this->w != 1.0f)
				{
					this->Homogenize();
				}
				return sqrt(MagSq());

			}
			T DotProduct(const vec4 &p_other) const { return (this->x * p_other.x) + (this->y * p_other.y) + (this->z * p_other.z); }
			vec4 CrossProduct(const vec4 &p_other) const
			{
				float crossX = (this->y * p_other.z) - (p_other.y * this->z);
				float crossY = (this->z * p_other.x) - (p_other.z * this->x);
				float crossZ = (this->x * p_other.y) - (p_other.x * this->y);

				return vec4(crossX, crossY, crossZ);
			}

			float AngleBetween(const vec4 &p_other) const
			{
				if (this->x == 0 && this->y == 0 && this->z == 0) return 0.0f;
				if (p_other.x == 0 && p_other.y == 0 && p_other.z == 0) return 0.0f;


				const double amt = this->DotProduct(p_other) / (this->GetMagnitude() * p_other.GetMagnitude());

				if (amt <= -1) {
					return M_PI;
				}
				else if (amt >= 1) {
					return 0;
				}
				return static_cast<float>(acos(amt));
			}

			T operator,(const vec4 &p_other) const { return this->DotProduct(p_other); }


			// SCALAR OPERATIONS

			vec4 operator+(const vec4 &p_other) const { return vec4(this->x + p_other.x, this->y + p_other.y, this->z + p_other.z); }
			vec4 &operator+=(const vec4 &p_other)
			{
				this->x += p_other.x;
				this->y += p_other.y;
				this->z += p_other.z;
				return *this;
			}

			vec4 Add(const vec4 &p_other) const { return vec4(this->x + p_other.x, this->y + p_other.y, this->z + p_other.z); }
			vec4 &Add(const vec4 &p_other)
			{
				this->x += p_other.x;
				this->y += p_other.y;
				this->z += p_other.z;
				return *this;
			}

			vec4 operator-(const vec4 &p_other) const { return vec4(this->x - p_other.x, this->y - p_other.y, this->z - p_other.z); }
			vec4 &operator-=(const vec4 &p_other)
			{
				this->x -= p_other.x;
				this->y -= p_other.y;
				this->z -= p_other.z;
				return *this;
			}
			vec4 Sub(const vec4 &p_other) const { return vec4(this->x - p_other.x, this->y - p_other.y, this->z - p_other.z); }
			vec4 &Sub(const vec4 &p_other)
			{
				this->x -= p_other.x;
				this->y -= p_other.y;
				this->z -= p_other.z;
				return *this;
			}

			vec4 operator*(const T n) const { return vec4(this->x*n, this->y*n, this->z*n); }
			vec4 &operator*=(const T n)
			{
				this->x *= n;
				this->y *= n;
				this->z *= n;
				return *this;
			}
			vec4 Scale(const T n) const { return vec4(this->x*n, this->y*n, this->z*n); }
			vec4 &Scale(const T n)
			{
				this->x *= n;
				this->y *= n;
				this->z *= n;
				return *this;
			}

			vec4 operator/(const T n) const { return vec4(this->x / n, this->y / n, this->z / n); }
			vec4 &operator/=(const T n)
			{
				this->x /= n;
				this->y /= n;
				this->z /= n;
				return *this;
			}
			vec4 Div(T n) const { return vec4(this->x / n, this->y / n, this->z / n); }
			vec4 &Div(T n)
			{
				this->x /= n;
				this->y /= n;
				this->z /= n;
				return *this;
			}

			vec4 &operator++(int)
			{
				T length = this->GetMagnitude();
				T mult = (length + 1) / length;
				this->x *= mult;
				this->y *= mult;
				this->z *= mult;
				return *this;
			}
			vec4 &operator--(int)
			{
				T length = this->GetMagnitude();
				T mult = (length - 1) / length;
				this->x *= mult;
				this->y *= mult;
				this->z *= mult;
				return *this;
			}

			// Tests

			bool IsParallel(const vec4 &p_other) const
			{
				return (this->x / p_other.x == this->y / p_other.y) && (this->x / p_other.x == this->z / p_other.z);
			}

			bool IsOpposed(const vec4 &p_other) const
			{
				return (this->IsParallel(p_other) && *this + p_other < *this);
			}

			bool IsPerpendicular(const vec4 &p_other) const
			{
				return (this->DotProduct(p_other) == 0);
			}

			bool IsNormalized() const
			{
				return this->GetMagnitude() == 1;
			}

			bool IsNull() const
			{
				return (x == 0 && y == 0 && z == 0);
			}

			vec3<T> ToVec3() const
			{
				vec4<T> homogenized = this->Homogenize();
				return vec3<T>(homogenized.x, homogenized.y, homogenized.z);
			}

			glm::vec4 ToGLMVec3() const
			{
				return glm::vec4(x, y, z, w);
			}

			T& operator[](const int coord)
			{
				if (coord == 0)
					return this->x;
				if (coord == 1)
					return this->y;
				if (coord == 2)
					return this->z;
				if (coord == 3)
					return this->w;
				return this->x;
			}

			const T& operator[](const int coord) const
			{
				if (coord == 0)
					return this->x;
				if (coord == 1)
					return this->y;
				if (coord == 2)
					return this->z;
				if (coord == 3)
					return this->w;
				return this->x;
			}

			// Comparisons

			bool operator==(const vec4 &p_other) const
			{
				return this->GetMagnitude() == p_other.GetMagnitude();
			}

			bool operator!=(const vec4 &p_other) const
			{
				return this->GetMagnitude() != p_other.GetMagnitude();
			}

			bool operator<(const vec4 &p_other) const
			{
				return this->GetMagnitude() < p_other.GetMagnitude();
			}

			bool operator<=(const vec4 &p_other) const
			{
				return this->GetMagnitude() <= p_other.GetMagnitude();
			}

			bool operator>(const vec4 &p_other) const
			{
				return this->GetMagnitude() > p_other.GetMagnitude();
			}

			bool operator>=(const vec4 &p_other) const
			{
				return this->GetMagnitude() >= p_other.GetMagnitude();
			}


		};

		// Strings

		template<typename T>
		std::ostream &operator<<(std::ostream &os, const vec4<T> &v)
		{
			os << v.x << "," << v.y << "," << v.z;
			return os;
		}

		template<typename T>
		std::string &operator+(std::string &str, const vec4<T> &v)
		{
			str += "x:" + std::to_string(v.x) + " y:" + std::to_string(v.y) + " z:" + std::to_string(v.z);
			return str;
		}

		template<typename T>
		std::string &operator+=(std::string &str, const vec4<T> &v)
		{
			str += "x:" + std::to_string(v.x) + " y:" + std::to_string(v.y) + " z:" + std::to_string(v.z);
			return str;
		}

		template<typename T>
		vec4<T> operator-(const vec4<T> &v) { return vec4<T>(-v.x, -v.y, -v.z); }

		template<typename T>
		vec4<T> operator*(const T n, const vec4<T> &v) { return vec4<T>(v.x*n, v.y*n, v.z*n); }

		template<typename T>
		vec4<T> operator/(const T n, const vec4<T> &v) { return vec4<T>(v.x / n, v.y / n, v.z / n); }

		using vec4f = vec4<float>;
		using vec4d = vec4<double>;
		using vec4i = vec4<int>;
	}
}

