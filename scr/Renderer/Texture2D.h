#pragma once

#include <glad/glad.h>
#include <string>

#include <map>
#include <glm/vec2.hpp> 

namespace RenderEngine {
	struct SubTexture2D {
		glm::vec2 leftBottomUV;
		glm::vec2 rightTopUV;	
		SubTexture2D(const glm::vec2& _leftBottomUV, const glm::vec2& _rightTopUV) : leftBottomUV(_leftBottomUV), rightTopUV(_rightTopUV) {}
		SubTexture2D():leftBottomUV(0.f), rightTopUV(1.f) {}		
	};

	class Texture2D {
	public:
		Texture2D (const GLint width, GLint height,
			const unsigned char* data,
			const unsigned int channels = 4,
			const GLenum filter = GL_LINEAR,
			const GLenum wrapMode = GL_CLAMP_TO_EDGE);

		Texture2D() = delete;
		Texture2D(const Texture2D&) = delete;
		Texture2D& operator=(const Texture2D&) = delete;
		Texture2D& operator=(Texture2D&& texture2d) noexcept;
		Texture2D(Texture2D&& texture2d) noexcept;
		~Texture2D();
		
		void addSubTexture(std::string name, glm::vec2 leftBottomUV, glm::vec2 rightTopUV);
		const SubTexture2D& getSubTexture(const std::string& name) const;
		
		unsigned int width() const {
			return m_width;
		}
		unsigned int height() const {
			return m_height;
		}

		void bind() const;

	private:
		GLuint m_ID;		
		GLenum m_mode;
		unsigned int m_width;
		unsigned int m_height;

		std::map <std::string, SubTexture2D> m_subTextures;
	};
}
