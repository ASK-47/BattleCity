#include "Sprite.h"

#include "ShaderProgram.h"
#include "Texture2D.h"

#include<glm/mat4x4.hpp>
#include<glm/gtc/matrix_transform.hpp>

namespace Renderer {
	Sprite::Sprite(std::shared_ptr<Texture2D> pTexture
		, std::string initialSubTexture
		, std::shared_ptr<ShaderProgram> pShaderProgram
		, const glm::vec2& position
		, const glm::vec2& size
		, const float rotation)
		: m_pTexture(std::move(pTexture))
		, m_pShaderProgram(std::move(pShaderProgram))
		, m_position(position)
		, m_size(size)
		, m_rotation(rotation) {
		const GLfloat vertexCoords[] = {
		//	2-3	  1
		//	| /	/ |
		//	1	3-2

		//Optimization - changing number of vertexes
		//	1-2
		//	|/|
		//	0-3
		
		//	x	y
		//first triangle
		0.0f, 0.0f,//0
		0.0f, 1.0f,//1
		1.0f, 1.0f,//2
		//second triangle
		1.0f, 0.0f,//3				
		};

		//auto subTexture = pTexture->getSubTexture(std::move(initialSubTexture));
		auto subTexture = m_pTexture->getSubTexture(std::move(initialSubTexture));

		//Optimization - changing number of vertexes
		const GLfloat textureCoords[] = {		
		//	u	v				
		//0.0f, 0.0f,//0
		//0.0f, 1.0f,//1
		//0.1f, 1.0f,//2
		subTexture.leftBottomUV.x, subTexture.leftBottomUV.y,
		subTexture.leftBottomUV.x, subTexture.rightTopUV.y,
		subTexture.rightTopUV.x, subTexture.rightTopUV.y,
		//1.0f, 0.0f,//3				
		subTexture.rightTopUV.x, subTexture.leftBottomUV.y
		};

		const GLint indexes[] = {
			0,1,2,
			//	1-2
			//	|/
			//	0
			2,3,0			
			//  2
			// /|
			//0-3
		};


	//Creation of vertex arrays object (VAO)
	glGenVertexArrays(1, &m_VAO);//generation of vao	
	glBindVertexArray(m_VAO);

	//Vertex Buffer generation
	//glGenBuffers(1, &m_vertexCoordsVBO);//removed to VertexBuffer::init
	//glBindBuffer(GL_ARRAY_BUFFER, m_vertexCoordsVBO);//removed to VertexBuffer::init
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertexCoords), &vertexCoords, GL_STATIC_DRAW);//removed to VertexBuffer::init
	//Init
	m_vertexCoordsBuffer.init(vertexCoords, 2 * 4 * sizeof(GLfloat));//data == vertexCoords, 2 coordinates * 4 points
	//Layout to acces data in shader
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	//Texture Buffer generation
	//glGenBuffers(1, &m_textureCoordsVBO);
	//glBindBuffer(GL_ARRAY_BUFFER, m_textureCoordsVBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(textureCoords), &textureCoords, GL_STATIC_DRAW);
	
	//Init
	m_textureCoordsBuffer.init(textureCoords, 2 * 4 * sizeof(GLfloat));//data == textureCoords, 2 coordinates * 4 points
	//Layout to acces data in shader
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);

	//EBO Buffer generation
	//glGenBuffers(1, &m_EBO);//generation of EBO (ELEMENT BUFFER OBJECT)
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);//binding == making current
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexes), &indexes, GL_STATIC_DRAW);//data fill
	m_indexBuffer.init(indexes, 6 * sizeof(GLuint)); //data == textureCoords, 6 coordinates 

	glBindBuffer(GL_ARRAY_BUFFER, 0);//unbind array buffer
	glBindVertexArray(0);//unbind vertex array
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);//unbind array buffer
	}
		
	Sprite::~Sprite() {
		//glDeleteBuffers(1, &m_vertexCoordsVBO);//delete vertex coordinates=> removed to ~VertexByffer()
		//glDeleteBuffers(1, &m_textureCoordsVBO);//delete texture coordinates
		//glDeleteBuffers(1, &m_EBO);//delete EBO
		glDeleteVertexArrays(1, &m_VAO);//delete vertex array
	}	

	void Sprite::render() const {
		m_pShaderProgram->use();
		
		glm::mat4 model(1.f);

		//all operations following over local sytem of coordinates  => for right transformation need to put object to world system of coordinated and come back
		model = glm::translate(model, glm::vec3(m_position, 0.f));//5 move to postion
		model = glm::translate(model, glm::vec3(0.5f * m_size.x, 0.5f * m_size.y, 0.f));//4 move back
		model = glm::rotate (model, glm::radians(m_rotation), glm::vec3(0.f, 0.f, 1.f));//3 rotate around z axis
		model = glm::translate(model, glm::vec3(- 0.5f * m_size.x, -0.5f * m_size.y, 0.f));//2 move to center
		model = glm::scale(model, glm::vec3(m_size, 1.f));//1 scale

		glBindVertexArray(m_VAO);	
		m_pShaderProgram->setMatrix4("modelMat", model);

		glActiveTexture(GL_TEXTURE0);//texture activation
		m_pTexture->bind();

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);
	}
	
	void Sprite::setPosition(const glm::vec2& position) {
		m_position = position;
	}
	
	void Sprite::setSize(const glm::vec2& size) {
		m_size = size;		
	}

	void Sprite::setRotation(const float rotation) {
		m_rotation = rotation;
	}
}