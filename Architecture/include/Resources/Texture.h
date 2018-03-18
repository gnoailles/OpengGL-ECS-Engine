#pragma once
#include <string>

namespace Resources
{
	class Texture
	{
	private:
		unsigned int m_rendererID;
		std::string m_filePath;
		unsigned char* m_buffer;
		int m_width, m_height, m_BPP;
	public:
		Texture(const std::string&& p_filepath);
		~Texture();
		
		void Bind(const unsigned int p_slot = 0) const;
		void Unbind() const;
	};
}
