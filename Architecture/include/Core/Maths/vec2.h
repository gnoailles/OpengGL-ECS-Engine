#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif

#include <math.h>
#include <string>
#include <glm/vec2.hpp>



namespace Core
{
	namespace Maths
	{
		template<typename T>
		class vec2
		{
		public:
			T x;
			T y;

		public:


			static float ToDegree(const double &angle)
			{
				return angle * 180.0 / M_PI;
			}
			static float ToRad(const double &angle)
			{
				return angle * M_PI / 180.0f;
			}

			vec2(T a, T b, const bool byAngle = false) : x{ a }, y{ b }
			{
				if (byAngle)
				{
					this->x = a * cos(b);
					this->y = a * sin(b);
				}
			}
			vec2(const vec2 &p_other)
			{
				this->x = p_other.x;
				this->y = p_other.y;
			}

			vec2 &operator=(const vec2 &p_other)
			{
				this->x = p_other.x;
				this->y = p_other.y;
				return *this;
			}

			~vec2() = default;

			vec2 Normalize() const
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

			T MagSq() const { return (this->x * this->x) + (this->y * this->y); }

			T Length() const { return sqrt(MagSq()); }
			T DotProduct(const vec2 &p_other) const { return (this->x * p_other.x) + (this->y * p_other.y); }

			float AngleBetween(const vec2 &p_other) const
			{
				if (this->x == 0 && this->y == 0) return 0.0f;
				if (p_other.x == 0 && p_other.y == 0) return 0.0f;


				const double amt = this->DotProduct(p_other) / (this->Length() * p_other.Length());

				if (amt <= -1) {
					return M_PI;
				}
				else if (amt >= 1) {
					return 0;
				}
				return static_cast<float>(acos(amt));
			}

			T operator,(const vec2 &p_other) const { return this->DotProduct(p_other); }


			// SCALAR OPERATIONS

			vec2 operator+(const vec2 &p_other) const { return vec2(this->x + p_other.x, this->y + p_other.y); }
			vec2 &operator+=(const vec2 &p_other)
			{
				this->x += p_other.x;
				this->y += p_other.y;
				return *this;
			}

			vec2 Add(const vec2 &p_other) const { return vec2(this->x + p_other.x, this->y + p_other.y); }
			vec2 &Add(const vec2 &p_other)
			{
				this->x += p_other.x;
				this->y += p_other.y;
				return *this;
			}

			vec2 operator-(const vec2 &p_other) const { return vec2(this->x - p_other.x, this->y - p_other.y); }
			vec2 &operator-=(const vec2 &p_other)
			{
				this->x -= p_other.x;
				this->y -= p_other.y;
				return *this;
			}
			vec2 Sub(const vec2 &p_other) const { return vec2(this->x - p_other.x, this->y - p_other.y); }
			vec2 &Sub(const vec2 &p_other)
			{
				this->x -= p_other.x;
				this->y -= p_other.y;
				return *this;
			}

			vec2 operator*(const T n) const { return vec2(this->x*n, this->y*n); }
			vec2 &operator*=(const T n)
			{
				this->x *= n;
				this->y *= n;
				return *this;
			}
			vec2 Scale(const T n) const { return vec2(this->x*n, this->y*n); }
			vec2 &Scale(const T n)
			{
				this->x *= n;
				this->y *= n;
				return *this;
			}

			vec2 operator/(const T n) const { return vec2(this->x / n, this->y / n); }
			vec2 &operator/=(const T n)
			{
				this->x /= n;
				this->y /= n;
				return *this;
			}
			vec2 Div(T n) const { return vec2(this->x / n, this->y / n); }
			vec2 &Div(T n)
			{
				this->x /= n;
				this->y /= n;
				return *this;
			}

			vec2 &operator++(int)
			{
				T length = this->Length();
				T mult = (length + 1) / length;
				this->x *= mult;
				this->y *= mult;
				return *this;
			}
			vec2 &operator--(int)
			{
				T length = this->Length();
				T mult = (length - 1) / length;
				this->x *= mult;
				this->y *= mult;
				return *this;
			}

			// Tests

			bool IsParallel(const vec2 &other) const
			{
				return (this->x / other.x == this->y / other.y);
			}

			bool IsOpposed(const vec2 &other) const
			{
				return (this->IsParallel(other) && *this + other < *this);
			}

			bool IsPerpendicular(const vec2 &other) const
			{
				return (this->DotProduct(other) == 0);
			}

			bool IsNormalized() const
			{
				return this->Length() == 1;
			}

			bool IsNull() const
			{
				return (x == 0 && y == 0);
			}

			T &operator[](const int coord)
			{
				if (coord == 0)
					return this->x;
				else if (coord == 1)
					return this->y;
				return 0;
			}

			// Comparisons

			bool operator==(const vec2 &other) const
			{
				return this->Length() == other.Length();
			}

			bool operator!=(const vec2 &other) const
			{
				return this->Length() != other.Length();
			}

			bool operator<(const vec2 &other) const
			{
				return this->Length() < other.Length();
			}

			bool operator<=(const vec2 &other) const
			{
				return this->Length() <= other.Length();
			}

			bool operator>(const vec2 &other) const
			{
				return this->Length() > other.Length();
			}

			bool operator>=(const vec2 &other) const
			{
				return this->Length() >= other.Length();
			}

			glm::vec2 ToGLMVec2() const
			{
				return glm::vec2(x, y);
			}
		};

		// Strings

		template<typename T>
		std::ostream &operator<<(std::ostream &os, const vec2<T> &v)
		{
			os << v.x << "," << v.y;
			return os;
		}

		template<typename T>
		std::string &operator+(std::string &str, const vec2<T> &v)
		{
			str += "x:" + std::to_string(v.x) + " y:";
			return str;
		}

		template<typename T>
		std::string &operator+=(std::string &str, const vec2<T> &v)
		{
			str += "x:" + std::to_string(v.x) + " y:" + std::to_string(v.y);
			return str;
		}

		template<typename T>
		vec2<T> operator-(const vec2<T> &v) { return vec2<T>(-v.x, -v.y); }

		template<typename T>
		vec2<T> operator*(const T n, const vec2<T> &v) { return vec2<T>(v.x*n, v.y*n); }

		template<typename T>
		vec2<T> operator/(const T n, const vec2<T> &v) { return vec2<T>(v.x / n, v.y / n); }

		using vec2f = vec2<float>;
		using vec2d = vec2<double>;
		using vec2i = vec2<int>;
	}
}

