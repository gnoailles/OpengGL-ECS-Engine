#pragma once
#include <unordered_map>
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include <memory>

namespace Resources
{
	using Model_ptr = std::unique_ptr<Model>;
	using Shader_ptr = std::unique_ptr<Shader>;
	using Texture_ptr = std::unique_ptr<Texture>;

	class ResourcesManager
	{
	private:
		std::string m_meshRootDir;
		std::string m_shaderRootDir;
		std::string m_textureRootDir;

		std::unordered_map<std::string, Model_ptr> m_modelResources;
		std::unordered_map<std::string, Shader_ptr> m_shaderResources;
		std::unordered_map<std::string, Texture_ptr> m_textureResources;

	public:
		ResourcesManager();
		~ResourcesManager();

		Model& LoadModel(const std::string&& p_name, const std::string&& p_fileName, bool p_forceReload = false);
		Shader& LoadShader(const std::string&& p_name, const std::string&& p_fileName, bool p_forceReload = false);
		Texture& LoadTexture(const std::string&& p_name, const std::string&& p_fileName, bool p_forceReload = false);

		void SetMeshRootDir(const std::string&& p_directory)
		{ m_meshRootDir = p_directory; }
		void SetShaderRootDir(const std::string&& p_directory)
		{ m_shaderRootDir = p_directory; }
		void SetTextureRootDir(const std::string&& p_directory)
		{ m_textureRootDir = p_directory; }

		Model& GetModel(const std::string&& p_name) { return *m_modelResources.at(p_name); }
		Shader& GetShader(const std::string&& p_name) { return *m_shaderResources.at(p_name); }
		Texture& GetTexture(const std::string&& p_name) { return *m_textureResources.at(p_name); }
	};
}
