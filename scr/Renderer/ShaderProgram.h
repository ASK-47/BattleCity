#pragma once
#include <glad/glad.h>
#include <string>

#include<glm/mat4x4.hpp>

namespace RenderEngine {
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmenttShader);
		~ShaderProgram();
		bool isCompiled() const {//methos to see colmpilation success
			return m_isCompiled;
		}
		void use() const;

		void setInt(const std::string& name, const GLint value);
		void setFloat(const std::string& name, const GLfloat value);
		void setMatrix4(const std::string& name, const glm::mat4& matrix);

		ShaderProgram() = delete;//no default ctor
		ShaderProgram(ShaderProgram&) = delete;//no-copy ctor
		ShaderProgram& operator=(const ShaderProgram&) = delete;//no copy operator =

		ShaderProgram(ShaderProgram&& shaderProgram) noexcept;//move ctor
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;//move operator =

	private:
		bool createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID );
		bool m_isCompiled = false;//flag to see colmpilation success
		GLuint m_ID =0;
	};
}
