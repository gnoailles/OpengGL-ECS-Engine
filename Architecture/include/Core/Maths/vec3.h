#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <math.h>
#include <string>
//#include <glm/vec3.hpp>
#include <glm/glm.hpp>

namespace Core
{
	namespace Maths
	{
		template<typename T>
		class vec3
		{
		public:
			T x;
			T y;
			T z;

		public:


			static float ToDegree(const float &angle)
			{
				return angle * 180.f / static_cast<float>(M_PI);
			}
			static float ToRad(const float &angle)
			{
				return angle * static_cast<float>(M_PI) / 180.0f;
			}

			vec3(T a, T b, const bool byAngle = false) : x{ a }, y{ b }
			{
				if (byAngle)
				{
					this->x = a * cos(b);
					this->y = a * sin(b);
				}
			}
			vec3(T x = 0.0f, T y = 0.0f, T z = 0.0f) : x{ x }, y{ y }, z{ z } {}
		
			vec3(const vec3 &p_other)
			{
				this->x = p_other.x;
				this->y = p_other.y;
				this->z = p_other.z;
			}

			vec3 &operator=(const vec3 &p_other)
			{
				this->x = p_other.x;
				this->y = p_other.y;
				this->z = p_other.z;
				return *this;
			}

			~vec3() = default;

			vec3 Normalize() const
			{
				float mag = this->Length();
				if (mag != 0 && mag != 1)
				{
					return this->Div(mag);
				}
				return this;
			}

			void Normalize()
			{
				float mag = this->Length();
				if (mag != 0 && mag != 1)
				{
					this->Div(mag);
				}
			}

			T MagSq() const { return (this->x * this->x) + (this->y * this->y) + (this->z * this->z); }

			T Length() const { return sqrt(MagSq()); }

			static float DotProduct(const vec3 &p_vec1, const vec3 &p_vec2) { return (p_vec1.x * p_vec2.x) + (p_vec1.y * p_vec2.y) + (p_vec1.z * p_vec2.z); }
			float DotProduct(const vec3 &p_other) const { return (this->x * p_other.x) + (this->y * p_other.y) + (this->z * p_other.z); }

			static vec3 CrossProduct(const vec3 &p_vec1, const vec3 &p_vec2)
			{
				float crossX = (p_vec1.y * p_vec2.z) - (p_vec2.y * p_vec1.z);
				float crossY = (p_vec1.z * p_vec2.x) - (p_vec2.z * p_vec1.x);
				float crossZ = (p_vec1.x * p_vec2.y) - (p_vec2.x * p_vec1.y);

				return vec3(crossX, crossY, crossZ);
			}
			vec3 CrossProduct(const vec3 &p_other) const
						{
							float crossX = (this->y * p_other.z) - (p_other.y * this->z);
							float crossY = (this->z * p_other.x) - (p_other.z * this->x);
							float crossZ = (this->x * p_other.y) - (p_other.x * this->y);

							return vec3(crossX, crossY, crossZ);
						}

			static float AngleBetween(const vec3 &p_vec1, const vec3 &p_vec2)
			{
				if (p_vec1.x == 0 && p_vec1.y == 0 && p_vec1.z == 0) return 0.0f;
				if (p_vec2.x == 0 && p_vec2.y == 0 && p_vec2.z == 0) return 0.0f;


				const double amt = p_vec1.DotProduct(p_vec2) / (p_vec1.Length() * p_vec2.Length());

				if (amt <= -1) {
					return static_cast<float>(M_PI);
				}
				else if (amt >= 1) {
					return 0;
				}
				return acosf(static_cast<float>(amt));
			}

			float AngleBetween(const vec3 &p_other) const
			{
				if (this->x == 0 && this->y == 0 && this->z == 0) return 0.0f;
				if (p_other.x == 0 && p_other.y == 0 && p_other.z == 0) return 0.0f;


				const double amt = this->DotProduct(p_other) / (this->Length() * p_other.Length());

				if (amt <= -1) {
					return M_PI;
				}
				else if (amt >= 1) {
					return 0;
				}
				return static_cast<float>(acosf(amt));
			}

			T operator,(const vec3 &p_other) const { return this->DotProduct(p_other); }


			// SCALAR OPERATIONS

			vec3 operator+(const vec3 &p_other) const { return vec3(this->x + p_other.x, this->y + p_other.y, this->z + p_other.z); }
			vec3 &operator+=(const vec3 &p_other)
			{
				this->x += p_other.x;
				this->y += p_other.y;
				this->z += p_other.z;
				return *this;
			}

			vec3 Add(const vec3 &p_other) const { return vec3(this->x + p_other.x, this->y + p_other.y, this->z + p_other.z); }
			vec3 &Add(const vec3 &p_other)
			{
				this->x += p_other.x;
				this->y += p_other.y;
				this->z += p_other.z;
				return *this;
			}

			vec3 operator-(const vec3 &p_other) const { return vec3(this->x - p_other.x, this->y - p_other.y, this->z - p_other.z); }
			vec3 &operator-=(const vec3 &p_other)
			{
				this->x -= p_other.x;
				this->y -= p_other.y;
				this->z -= p_other.z;
				return *this;
			}
			vec3 Sub(const vec3 &p_other) const { return vec3(this->x - p_other.x, this->y - p_other.y, this->z - p_other.z); }
			vec3 &Sub(const vec3 &p_other)
			{
				this->x -= p_other.x;
				this->y -= p_other.y;
				this->z -= p_other.z;
				return *this;
			}

			vec3 operator*(const T n) const { return vec3(this->x*n, this->y*n, this->z*n); }
			vec3 &operator*=(const T n)
			{
				this->x *= n;
				this->y *= n;
				this->z *= n;
				return *this;
			}
			vec3 Scale(const T n) const { return vec3(this->x*n, this->y*n, this->z*n); }
			vec3 &Scale(const T n)
			{
				this->x *= n;
				this->y *= n;
				this->z *= n;
				return *this;
			}

			vec3 operator/(const T n) const { return vec3(this->x / n, this->y / n, this->z / n); }
			vec3 &operator/=(const T n)
			{
				this->x /= n;
				this->y /= n;
				this->z /= n;
				return *this;
			}
			vec3 Div(T n) const { return vec3(this->x / n, this->y / n, this->z / n); }
			vec3 &Div(T n)
			{
				this->x /= n;
				this->y /= n;
				this->z /= n;
				return *this;
			}

			vec3 &operator++(int)
			{
				T length = this->Length();
				T mult = (length + 1) / length;
				this->x *= mult;
				this->y *= mult;
				this->z *= mult;
				return *this;
			}
			vec3 &operator--(int)
			{
				T length = this->Length();
				T mult = (length - 1) / length;
				this->x *= mult;
				this->y *= mult;
				this->z *= mult;
				return *this;
			}

			// Tests

			bool IsParallel(const vec3 &p_other) const
			{
				return (this->x / p_other.x == this->y / p_other.y) && (this->x / p_other.x == this->z / p_other.z);
			}

			bool IsOpposed(const vec3 &p_other) const
			{
				return (this->IsParallel(p_other) && *this + p_other < *this);
			}

			bool IsPerpendicular(const vec3 &p_other) const
			{
				return (this->DotProduct(p_other) == 0);
			}

			bool IsNormalized() const
			{
				return this->Length() == 1;
			}

			bool IsNull() const
			{
				return (x == 0 && y == 0 && z == 0);
			}

			T &operator[](const int coord)
			{
				if (coord == 0)
					return this->x;
				else if (coord == 1)
					return this->y;
				else if (coord == 2)
					return this->y;
				return 0;
			}

			// Comparisons

			bool operator==(const vec3 &p_other) const { return (this->x == p_other.x && this->y == p_other.y && this->z == p_other.z); }

			bool operator!=(const vec3 &p_other) const { return (this->x != p_other.x || this->y != p_other.y || this->z != p_other.z); }

			bool operator<(const vec3 &p_other) const { return this->Length() < p_other.Length(); }

			bool operator<=(const vec3 &p_other) const { return this->Length() <= p_other.Length(); }

			bool operator>(const vec3 &p_other) const { return this->Length() > p_other.Length(); }

			bool operator>=(const vec3 &p_other) const { return this->Length() >= p_other.Length(); }


			//GLM COMPATIBILITY
			vec3(const glm::vec3 &p_other)
			{
				this->x = p_other.x;
				this->y = p_other.y;
				this->z = p_other.z;
			}
			vec3 &operator=(const glm::vec3 &p_other)
			{
				this->x = p_other.x;
				this->y = p_other.y;
				this->z = p_other.z;
				return *this;
			}

			glm::vec3 ToGLMVec3() const { return glm::vec3(x, y, z); }

			bool operator==(const glm::vec3 &p_other) const { return (this->x == p_other.x && this->y == p_other.y && this.z == p_other.z); }
			bool operator!=(const glm::vec3 &p_other) const { return (this->x != p_other.x || this->y != p_other.y || this.z != p_other.z); }
			bool operator<(const glm::vec3 &p_other) const { return this->Length() < glm::length(p_other); }
			bool operator<=(const glm::vec3 &p_other) const { return this->Length() <= glm::length(p_other); }
			bool operator>(const glm::vec3 &p_other) const { return this->Length() > glm::length(p_other); }
			bool operator>=(const glm::vec3 &p_other) const { return this->Length() >= glm::length(p_other); }


			vec3 operator+(const glm::vec3 &p_other) const { return vec3(this->x + p_other.x, this->y + p_other.y, this->z + p_other.z); }
			vec3 &operator+=(const glm::vec3 &p_other)
			{
				this->x += p_other.x;
				this->y += p_other.y;
				this->z += p_other.z;
				return *this;
			}

			vec3 Add(const glm::vec3 &p_other) const { return vec3(this->x + p_other.x, this->y + p_other.y, this->z + p_other.z); }
			vec3 &Add(const glm::vec3 &p_other)
			{
				this->x += p_other.x;
				this->y += p_other.y;
				this->z += p_other.z;
				return *this;
			}
			
			vec3 operator-(const glm::vec3 &p_other) const { return vec3(this->x - p_other.x, this->y - p_other.y, this->z - p_other.z); }
			vec3 &operator-=(const glm::vec3 &p_other)
			{
				this->x -= p_other.x;
				this->y -= p_other.y;
				this->z -= p_other.z;
				return *this;
			}
			vec3 Sub(const glm::vec3 &p_other) const { return vec3(this->x - p_other.x, this->y - p_other.y, this->z - p_other.z); }
			vec3 &Sub(const glm::vec3 &p_other)
			{
				this->x -= p_other.x;
				this->y -= p_other.y;
				this->z -= p_other.z;
				return *this;
			}

		};

		// Strings

		template<typename T>
		std::ostream &operator<<(std::ostream &os, const vec3<T> &v)
		{
			os << v.x << "," << v.y << "," << v.z;
			return os;
		}

		template<typename T>
		std::string &operator+(std::string &str, const vec3<T> &v)
		{
			str += "x:" + std::to_string(v.x) + " y:" + std::to_string(v.y) + " z:" + std::to_string(v.z);
			return str;
		}

		template<typename T>
		std::string &operator+=(std::string &str, const vec3<T> &v)
		{
			str += "x:" + std::to_string(v.x) + " y:" + std::to_string(v.y) + " z:" + std::to_string(v.z);
			return str;
		}

		template<typename T>
		vec3<T> operator-(const vec3<T> &v) { return vec3<T>(-v.x, -v.y, -v.z); }

		template<typename T>
		vec3<T> operator*(const T n, const vec3<T> &v) { return vec3<T>(v.x*n, v.y*n, v.z*n); }

		template<typename T>
		vec3<T> operator/(const T n, const vec3<T> &v) { return vec3<T>(v.x / n, v.y / n, v.z / n); }

		using vec3f = vec3<float>;
		using vec3d = vec3<double>;
		using vec3i = vec3<int>;
	}
}

