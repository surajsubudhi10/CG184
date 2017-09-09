#include "Shader.h"

namespace CG184 
{
	Shader::Shader(const char* vertexPath, const char* fragmentPath)// : textured(false)
	{

		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char * fShaderCode = fragmentCode.c_str();
		// 2. compile shaders
		unsigned int vertex, fragment;
		int success;
		char infoLog[512];
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		CompileShader(vertex, "VERTEX");
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		CompileShader(fragment, "FRAGMENT");
		// shader Program
		shaderID = glCreateProgram();
		glAttachShader(shaderID, vertex);
		glAttachShader(shaderID, fragment);
		glLinkProgram(shaderID);
		CompileShader(shaderID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);

	}

	void Shader::ActivateShader()
	{
		glUseProgram(shaderID);

		for (int i = 0; i < sizeof(m_Textures) / sizeof(m_Textures[0]); i++) 
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, m_Textures[i].textureID);
		}
	}

	void Shader::DeactivateShader() 
	{
		glUseProgram(0);
	}

	void Shader::AddTexture(const char* const texturePath, TextureType texType)
	{
		Texture tex;
		tex.LoadTexture(texturePath);

		glUseProgram(shaderID);
		switch (texType)
		{
			case TextureType::Diffuse:
				m_Textures[0] = tex;
				glUniform1i(glGetUniformLocation(shaderID, "DiffuseMap"), 0);

			case TextureType::Specular:
				m_Textures[1] = tex;
				glUniform1i(glGetUniformLocation(shaderID, "SpecularMap"), 1);

			case TextureType::Normal:
				m_Textures[2] = tex;
				glUniform1i(glGetUniformLocation(shaderID, "NormalMap"), 2);

			case TextureType::Bump:
				m_Textures[3] = tex;
				glUniform1i(glGetUniformLocation(shaderID, "BumpMap"), 3);

			case TextureType::Reflection:
				m_Textures[4] = tex;
				glUniform1i(glGetUniformLocation(shaderID, "ReflectionMap"), 4);

			default:
				break;
		}

		glUniform1i(glGetUniformLocation(shaderID, "textured"), true);

		glUseProgram(0);
	}


	void Shader::CompileShader(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}


	Shader::~Shader()
	{
	}
}