#include "ShaderProgram.h"
#include <iostream>

#include<glm/gtc/type_ptr.hpp>


namespace RenderEngine {
	ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) {
		GLuint vertexShaderID;
		if (!createShader(vertexShader, GL_VERTEX_SHADER, vertexShaderID)) {
			std::cerr << "VERTEX SHADER compile time error" << std::endl;
			return;
		}

		GLuint fragmentShaderID;
		if (!createShader(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderID)) {
			std::cerr << "FRAGMENT SHADER compile time error" << std::endl;
			glDeleteShader(vertexShaderID);//memory free useg for fragment shader ???
			return;
		}			
		
		m_ID = glCreateProgram();
		glAttachShader(m_ID, vertexShaderID);
		glAttachShader(m_ID, fragmentShaderID);
		glLinkProgram(m_ID);//linking

		GLint success;
		glGetProgramiv(m_ID, GL_LINK_STATUS, &success);
		if (!success) {//in case of error
			GLchar infolog[1024];
			glGetProgramInfoLog(m_ID, 1024, nullptr, infolog);
			std::cerr << "ERROR::SHADER: link time error:\n" << infolog << std::endl;			
		}
		else {
			m_isCompiled = true;
		}

		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
	}

	bool ShaderProgram::createShader(const std::string& source, const GLenum shaderType, GLuint& shaderID) {
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();//string=>array
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);//command to compile shader
		
		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);//result of compilation staus is writen into sucsess
		if (!success) {//in case of error
			GLchar infolog[1024];			
			glGetProgramInfoLog(shaderID, 1024, nullptr, infolog);
			std::cerr << "ERROR::SHADER: Compile time error:\n" << infolog << std::endl;
			return false;//for createShader
		}
		return true;//createShader	
	}
		
	ShaderProgram::~ShaderProgram() {//D-tor
		glDeleteProgram(m_ID);
	}

	void ShaderProgram::use() const {
		glUseProgram(m_ID);
	}

	ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept {//move ctor
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID = 0;
		shaderProgram.m_isCompiled = false;	
	}

	ShaderProgram& ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept{//move operator =		
		glDeleteProgram(m_ID);
		m_ID = shaderProgram.m_ID;
		m_isCompiled = shaderProgram.m_isCompiled;

		shaderProgram.m_ID=0;
		shaderProgram.m_isCompiled=false;

		return *this;
	}

	void ShaderProgram::setInt(const std::string& name, const GLint value) {	
		glUniform1i(glGetUniformLocation(m_ID, name.c_str()), value);
	}

	void ShaderProgram::setFloat(const std::string& name, const GLfloat value) {
		glUniform1f(glGetUniformLocation(m_ID, name.c_str()), value);
	}

	void ShaderProgram::setMatrix4(const std::string& name, const glm::mat4& matrix) {		
		glUniformMatrix4fv(glGetUniformLocation(m_ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(matrix));
	}
}