#pragma once

#include <iostream>
#include <vector>
#include <cmath>
#include <Core/Maths/vec3.h>
#include <Core/Maths/vec4.h>
#include <Core/Maths/mat3.h>

namespace Core
{
	namespace Maths
	{
		template<typename T>
		class mat4
		{
		public:
			T m_matrix[4][4];

		public:
			mat4()
			{
				for (int i = 0; i < 4; ++i)
					for (int j = 0; j < 4; ++j)
						this->m_matrix[i][j] = 0;
			}

			mat4(std::initializer_list<T> p_initList)
			{
				if (p_initList.size() < 16)
					std::cout << "Insufficient elements" << std::endl;
				else
				{
					auto it = p_initList.begin();
					for (int i = 0; i < 4; ++i)
						for (int j = 0; j < 4; ++j)
							this->m_matrix[i][j] = *it++;
				}
			}

			mat4(const mat4& p_other)
			{
				for (int i = 0; i < 4; ++i)
					for (int j = 0; j < 4; ++j)
						this->m_matrix[i][j] = p_other.m_matrix[i][j];
			}

			~mat4() {}

			//UTILS
			static int Sign(const unsigned int &p_i, const unsigned int &p_j)
			{
				return pow(-1, ((p_i + 1) + (p_j + 1)));
			}

			// TRANFORMATION MATRICES
			static mat4 CreateTranslationMatrix(const vec3<float>& p_translation)
			{
				return  { 1,0,0,p_translation.x,
						  0,1,0,p_translation.y,
						  0,0,1,p_translation.z,
						  0,0,0,1 };
			}

			static mat4 CreateScaleMatrix(const vec3<float>& p_scale)
			{
				return  { p_scale.x,0,0,0,
						  0,p_scale.y,0,0,
						  0,0,p_scale.z,0,
						  0,0,0,1 };
			}

			static mat4 CreateXRotationMatrix(const float p_angle)
			{
				return  { 1,	0,				0,				0,
						  0,	cos(p_angle),	-sin(p_angle),	0,
						  0,	sin(p_angle),	cos(p_angle),	0,
						  0,	0,				0,				1 };
			}
			static mat4 CreateYRotationMatrix(const float p_angle)
			{
				return  { cos(p_angle),	 0,	sin(p_angle),	0,
						  0,			 1,	0,				0,
						  -sin(p_angle), 0,	cos(p_angle),	0,
						  0,			 0,	0,				1 };
			}
			static mat4 CreateZRotationMatrix(const float p_angle)
			{
				return  { cos(p_angle),	-sin(p_angle),	0,	0,
						  sin(p_angle),	cos(p_angle),	0,	0,
						  0,			0,				1,	0,
						  0,			0,				0,	1 };
			}

			static mat4 CreateRotationMatrix(const vec3<float>& p_rotation)
			{
				return  CreateYRotationMatrix(vec3<float>::ToRad(p_rotation.y)) *
						CreateXRotationMatrix(vec3<float>::ToRad(p_rotation.x)) *
						CreateZRotationMatrix(vec3<float>::ToRad(p_rotation.z));
			}

			static mat4 CreateTransformMatrix(const vec3<float>& p_position, const vec3<float>& p_rotation, const vec3<float>& p_scale)
			{
				return  CreateTranslationMatrix(p_position) *
						CreateRotationMatrix(p_rotation) *
						CreateScaleMatrix(p_scale);
			}


			// SCALAR OPERATIONS
			mat4 Add(const float &p_scalar) const
			{
				mat4 add;
				for (int i = 0; i < 4; ++i)
					for (int j = 0; j < 4; ++j)
						add.m_matrix[i][j] = this->m_matrix[i][j] + p_scalar;
				return add;
			}

			void Add(const float &p_scalar)
			{
				for (int i = 0; i < 4; ++i)
					for (int j = 0; j < 4; ++j)
						this->m_matrix[i][j] += p_scalar;
			}

			mat4 Sub(const float &p_scalar) const
			{
				mat4 sub;
				for (int i = 0; i < 4; ++i)
					for (int j = 0; j < 4; ++j)
						sub.m_matrix[i][j] = this->m_matrix[i][j] - p_scalar;
				return sub;
			}
			void Sub(const float &p_scalar)
			{
				for (int i = 0; i < 4; ++i)
					for (int j = 0; j < 4; ++j)
						this->m_matrix[i][j] -= p_scalar;
			}

			mat4 Scale(const float &p_scalar) const
			{
				mat4 scale;
				for (int i = 0; i < 4; ++i)
					for (int j = 0; j < 4; ++j)
						scale.m_matrix[i][j] = this->m_matrix[i][j] * p_scalar;
				return scale;
			}
			void Scale(const float &p_scalar)
			{
				for (int i = 0; i < 4; ++i)
					for (int j = 0; j < 4; ++j)
						this->m_matrix[i][j] *= p_scalar;
			}

			mat4 Div(const float &p_scalar) const
			{
				mat4 div;
				for (int i = 0; i < 4; ++i)
					for (int j = 0; j < 4; ++j)
						div.m_matrix[i][j] = this->m_matrix[i][j] / p_scalar;
				return div;
			}
			void Div(const float &p_scalar)
			{
				for (int i = 0; i < 4; ++i)
					for (int j = 0; j < 4; ++j)
						this->m_matrix[i][j] /= p_scalar;
			}


			// MATRICES ARTIHMETICS OPERATIONS
			mat4 Add(const mat4 &p_other) const
			{
				mat4 add;
				for (int i = 0; i < 4; ++i)
					for (int j = 0; j < 4; ++j)
						add.m_matrix[i][j] = this->m_matrix[i][j] + p_other.m_matrix[i][j];
				return add;
			}
			void Add(const mat4 &p_other)
			{
				for (int i = 0; i < 4; ++i)
					for (int j = 0; j < 4; ++j)
						this->m_matrix[i][j] += p_other.m_matrix[i][j];
			}

			mat4 Sub(const mat4 &p_other) const
			{
				mat4 sub;
				for (int i = 0; i < 4; ++i)
					for (int j = 0; j < 4; ++j)
						sub.m_matrix[i][j] = this->m_matrix[i][j] - p_other.m_matrix[i][j];
				return sub;
			}
			void Sub(const mat4 &p_other)
			{
				for (int i = 0; i < 4; ++i)
					for (int j = 0; j < 4; ++j)
						this->m_matrix[i][j] -= p_other.m_matrix[i][j];
			}

			mat4 Multiply(const mat4 &p_other) const
			{
				mat4 multiply;
				for (unsigned int i = 0; i < 4; ++i)
					for (unsigned int j = 0; j < 4; ++j)
						multiply.m_matrix[i][j] = VectorsMul(this->GetRow(i), p_other.GetColumn(j));
				return multiply;
			}
			void Multiply(const mat4 &p_other)
			{
				for (unsigned int i = 0; i < 4; ++i)
					for (unsigned int j = 0; j < 4; ++j)
						this->m_matrix[i][j] = VectorsMul(this->GetRow(i), p_other.GetColumn(j));
			}

			vec4<float> Multiply(const vec4<float> &p_other) const
			{
				vec4<float> multiply;
				for (unsigned int i = 0; i < 4; ++i)
					multiply[i] = VectorsMul(this->GetRow(i), p_other);
				return multiply;
			}
			void Multiply(const vec4<float> &p_other)
			{
				for (unsigned int i = 0; i < 4; ++i)
					for (unsigned int j = 0; j < 4; ++j)
						this->m_matrix[i][j] = VectorsMul(this->GetRow(i), p_other);
			}

			static float VectorsMul(const vec4<float> &p_v1, const vec4<float> &p_v2)
			{
				float VectorsMul = 0;
				int i = 0;
				for (int j = 0; i < 4; ++j)
				{
					VectorsMul += p_v1[i] * p_v2[j];
					++i;
				}
				return VectorsMul;
			}

			// MATRICES TRANSFORMATIONS
			mat4 Transpose() const
			{
				mat4 transpose;
				for (unsigned int i = 0; i < 4; ++i)
					for (unsigned int j = 0; j < 4; ++j)
						transpose.m_matrix[i][j] = m_matrix[j][i];
				return transpose;
			}

			float Determinant() const
			{
				return m_matrix[0][0] * (m_matrix[1][1] * (m_matrix[2][2] * m_matrix[3][3] - m_matrix[2][3] * m_matrix[3][2]) -
					m_matrix[1][2] * (m_matrix[2][1] * m_matrix[3][3] - m_matrix[2][3] * m_matrix[3][1]) +
					m_matrix[1][3] * (m_matrix[2][1] * m_matrix[3][2] - m_matrix[2][2] * m_matrix[3][1])) -
					m_matrix[0][1] * (m_matrix[1][0] * (m_matrix[2][2] * m_matrix[3][3] - m_matrix[2][3] * m_matrix[3][2]) -
						m_matrix[1][2] * (m_matrix[2][0] * m_matrix[3][3] - m_matrix[2][3] * m_matrix[3][0]) +
						m_matrix[1][3] * (m_matrix[2][0] * m_matrix[3][2] - m_matrix[2][2] * m_matrix[3][0])) +
					m_matrix[0][2] * (m_matrix[1][0] * (m_matrix[2][1] * m_matrix[3][3] - m_matrix[2][3] * m_matrix[3][1]) -
						m_matrix[1][1] * (m_matrix[2][0] * m_matrix[3][3] - m_matrix[2][3] * m_matrix[3][0]) +
						m_matrix[1][3] * (m_matrix[2][0] * m_matrix[3][1] - m_matrix[2][1] * m_matrix[3][0])) -
					m_matrix[0][3] * (m_matrix[1][0] * (m_matrix[2][1] * m_matrix[3][2] - m_matrix[2][2] * m_matrix[3][1]) -
						m_matrix[1][1] * (m_matrix[2][0] * m_matrix[3][2] - m_matrix[2][2] * m_matrix[3][0]) +
						m_matrix[1][2] * (m_matrix[2][0] * m_matrix[3][1] - m_matrix[2][1] * m_matrix[3][0]));
			}

			mat4 Adjoint() const
			{
				mat4 adjoint;
				for (unsigned int i = 0; i < 4; ++i)
					for (unsigned int j = 0; j < 4; ++j)
						adjoint.m_matrix[i][j] = Sign(i, j) * Minor(i, j).Determinant();

				return adjoint;
			}
			mat3<T> Minor(const int x, const int y) const
			{
				mat3<T> minor;
				unsigned int i = 0, j = 0;
				for (unsigned int row = 0; row < 4; ++row)
					for (unsigned int col = 0; col < 4; ++col)
					{
						if (row != x && col != y)
						{
							minor.m_matrix[i][j++] = m_matrix[row][col];
							if (j == 3)
							{
								j = 0;
								++i;
							}
						}
					}
				return minor;
			}
			mat4 Inverse() const
			{
				return Adjoint().Transpose() / Determinant();
			}


			// GETTERS
			T** GetData()
			{
				return reinterpret_cast<T**>(this->m_matrix);
			}
			vec4<T> GetRow(const unsigned int p_row) const
			{
				if (p_row < 4)
				{
					return vec4<T>(this->m_matrix[p_row][0],
						this->m_matrix[p_row][1],
						this->m_matrix[p_row][2],
						this->m_matrix[p_row][3]);
				}
				std::cout << "Out of Matrix" << std::endl;
				return vec4<T>();
			}
			vec4<T> GetColumn(const unsigned int p_col) const
			{
				if (p_col < 4)
				{
					return vec4<T>(this->m_matrix[0][p_col],
						this->m_matrix[1][p_col],
						this->m_matrix[2][p_col],
						this->m_matrix[3][p_col]);
				}
				std::cout << "Out of Matrix" << std::endl;
				return vec4<T>();
			}

			const T& GetValue(const unsigned int p_row, const unsigned int p_col) const
			{
				if (p_row < 4 && p_col < 4)
				{
					return this->m_matrix[p_row][p_col];
				}
				std::cout << "Out of Matrix" << std::endl;
				return this->m_matrix[0][0];
			}
			T& GetValue(const unsigned int p_row, const unsigned int p_col)
			{
				if (p_row < 4 && p_col < 4)
				{
					return this->m_matrix[p_row][p_col];
				}
				std::cout << "Out of Matrix" << std::endl;
				return this->m_matrix[0][0];
			}

			const T& operator()(const unsigned int p_row, const unsigned int p_col) const
			{
				if (p_row < 4 && p_col < 4)
					return this->m_matrix[p_row][p_col];
				std::cout << "Out of Matrix" << std::endl;
				return this->m_matrix[0][0];
			}
			T& operator()(const unsigned int p_row, const unsigned int p_col)
			{
				if (p_row < 4 && p_col < 4)
					return this->m_matrix[p_row][p_col];
				return m_matrix[0][0];
			}


			// TESTS
			bool IsEqual(const mat4 &p_other)
			{
				for (unsigned int i = 0; i < 4; ++i)
					for (unsigned int j = 0; j < 4; ++j)
						if (m_matrix[i][j] != p_other.m_matrix[i][j])
							return false;
				return true;
			}
			bool IsOrthogonal() const
			{
				return Multiply(Transpose()).IsIdentity();
			}
			bool IsIdentity() const
			{
				for (unsigned int i = 0; i < 4; ++i)
					for (unsigned int j = 0; j < 4; ++j)
					{
						if (i == j && m_matrix[i][j] != 1)
							return false;
						if (i != j && m_matrix[i][j] != 0)
							return false;

					}
				return true;
			}

			// OPERATORS

			mat4 operator+(const mat4 &p_other) const { return Add(p_other); }
			void operator+=(const mat4 &p_other) { Add(p_other); }

			mat4 operator-(const mat4 &p_other) const { return Sub(p_other); }
			void operator-=(const mat4 &p_other) { Sub(p_other); }

			mat4 operator*(const mat4 &p_other) const { return Multiply(p_other); }
			void operator*=(const mat4 &p_other) { Multiply(p_other); }


			vec4<float> operator*(const vec4<T>& p_other) const { return Multiply(p_other); }
			void operator*=(const vec4<T> &p_other) { Multiply(p_other); }


			mat4 operator+(const float &p_scalar) const { return Add(p_scalar); }
			void operator+=(const float &p_scalar) { Add(p_scalar); }

			mat4 operator-(const float &p_scalar) const { return Sub(p_scalar); }
			void operator-=(const float &p_scalar) { Sub(p_scalar); }

			mat4 operator*(const float &p_scalar) const { return Scale(p_scalar); }
			void operator*=(const float &p_scalar) { Scale(p_scalar); }

			mat4 operator/(const float &p_scalar) const { return Div(p_scalar); }
			void operator/=(const float &p_scalar) { Div(p_scalar); }


			bool operator==(const mat4 &p_other) { return IsEqual(p_other); }
			bool operator!=(const mat4 &p_other) { return !IsEqual(p_other); }
		};

		inline std::ostream &operator<<(std::ostream &p_os, const mat4<float>&p_other)
		{
			for (int i = 0; i < 4; ++i)
			{
				for (int j = 0; j < 4; ++j)
					p_os << p_other(i, j) << " ";
				p_os << std::endl;
			}
			return p_os;
		}

		using mat4f = mat4<float>;
		using mat4d = mat4<double>;
		using mat4i = mat4<int>;
	}
}
