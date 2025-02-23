#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

#include <glad/glad.h>
#include <memory>
#include<glm/vec2.hpp>

#include<string>

#include "VertexArray.h"

//loading textures to video adapter
namespace RenderEngine {
	class Texture2D;
	class ShaderProgram;

	class Sprite {
	public:		
		Sprite(std::shared_ptr<Texture2D> pTexture
			, std::string initialSubTexture
			, std::shared_ptr<ShaderProgram> pShaderProgram
			, const glm::vec2& position = glm::vec2(0.f)
			, const glm::vec2& size = glm::vec2(1.f)
			, const float rotation = 0.f);

		~Sprite ();

		Sprite(const Sprite& )=delete;
		Sprite& operator=(const Sprite&) = delete;

		//void render() const;
		virtual void render() const;

		void setPosition(const glm::vec2& position);
		void setSize(const glm::vec2& size);
		void setRotation(const float rotation);

	//private:
	protected:
		std::shared_ptr<Texture2D> m_pTexture;
		std::shared_ptr<ShaderProgram> m_pShaderProgram;
		glm::vec2 m_position;
		glm::vec2 m_size;
		float m_rotation;
		//GLuint m_VAO;

		//Buffers:
		//GLuint m_vertexCoordsVBO;//buffer for coordinates //=>_vertexCoordsBuffer
		//GLuint m_textureCoordsVBO;//buffer for textures// => m_textureCoordsBuffer
		//GLuint m_EBO;//(ELEMENT BUFFER OBJECT)//buffer for indexes => m_indexBuffer

		VertexArray m_vertexArray;
		VertexBuffer m_vertexCoordsBuffer;
		VertexBuffer m_textureCoordsBuffer;
		IndexBuffer m_indexBuffer;
	};	
}
