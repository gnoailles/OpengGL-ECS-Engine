#pragma once
#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <Core/Maths/vec3.h>
#include <Core/Maths/vec2.h>
#include <Core/Maths/vec4.h>
#include <glm/gtc/type_ptr.hpp>

struct ShaderProgramSource;

namespace Resources
{
	class Shader
	{
	private:
		GLuint m_rendererID;
		std::unordered_map<std::string, int> m_uniformLocationCache;

		static std::string vertexShaderStart;
		static std::string fragmentShaderStart;
	public:
		Shader(const std::string&& p_filepath);
		~Shader();

		void Bind() const;
		void Unbind() const;

		/* Uniforms */
		void SetUniform(const std::string&& p_name, const int p_value);
		void SetUniform(const std::string&& p_name, const float p_value);
		void SetUniform(const std::string&& p_name, const Core::Maths::vec2f& p_vec2f);
		void SetUniform(const std::string&& p_name, const Core::Maths::vec3f& p_vec3f);
		void SetUniform(const std::string&& p_name, const Core::Maths::vec4f& p_vec4f);
		void SetUniform(const std::string&& p_name, const glm::mat4& p_mat4f);

		static inline void SetVertexShaderDelimiter(const std::string&& p_shaderStart)
		{ vertexShaderStart = p_shaderStart; }
		static inline void SetFragmentShaderDelimiter(const std::string&& p_shaderStart)
		{ fragmentShaderStart = p_shaderStart; }

	private:
		ShaderProgramSource Parse(const std::string&& p_filepath);
		void Compile(const ShaderProgramSource& p_sources);

		void CatchCompilerError(const GLenum p_compilerAction, const GLuint p_compiledShader);

		int GetUniformLocation(const std::string&& p_name);
	};

	

}
