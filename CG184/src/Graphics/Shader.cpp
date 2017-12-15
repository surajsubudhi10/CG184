#include <cassert>
#include "Shader.h"

namespace CG184 
{
    // Helper Function
    int GetUniformLocation(const string &name, vector<Uniform> uniformList);

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
		uint32_t vertex, fragment;

		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, nullptr);
		glCompileShader(vertex);
		CompileShader(vertex, "VERTEX");

		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, nullptr);
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


        int nAttributes, nUniforms;
        glGetProgramiv(shaderID, GL_ACTIVE_ATTRIBUTES, &nAttributes);
        glGetProgramiv(shaderID, GL_ACTIVE_UNIFORMS, &nUniforms);
        m_Attributes.resize(nAttributes);
        m_Uniforms.resize(nUniforms);

        char buffer[128];
        for (int i = 0; i < nAttributes; ++i)
        {
            GLenum glType;
            glGetActiveAttrib(shaderID, i, sizeof(buffer), 0, &m_Attributes[i].Size, &glType, buffer);
            m_Attributes[i].Name = std::string(buffer);
            // TODO think of clean way to manage type conversions of OpenGL and custom type
            //m_Attributes[i].Type = SHADER_TYPE_BOOL;

            m_Attributes[i].Location = glGetAttribLocation(shaderID, buffer);
        }

        for (int i = 0; i < nUniforms; ++i)
        {
            GLenum glType;
            glGetActiveUniform(shaderID, i, sizeof(buffer), 0, &m_Uniforms[i].Size, &glType, buffer);
            m_Uniforms[i].Name = std::string(buffer);
            // TODO think of clean way to manage type conversions of OpenGL and custom type
            // TODO This method will not get the name for uniform location if its a struct or array.
            //m_Uniforms[i].Type = SHADER_TYPE_BOOL;

            m_Uniforms[i].Location = glGetUniformLocation(shaderID, buffer);
        }

	}


	Shader::Shader(const Shader &a_Shader)
	{
		shaderID = a_Shader.shaderID;
		m_Uniforms = a_Shader.m_Uniforms;
		m_Attributes = a_Shader.m_Attributes;

		for(auto i = 0; i < 5; i++) {
			m_Textures[i] = a_Shader.m_Textures[i];
		}

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


	void Shader::CompileShader(uint32_t shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}


	Shader::~Shader()
	= default;

	void Shader::SetUniform1f(string name, float _v1)
    {
        glUseProgram(shaderID);
        auto location = GetUniformLocation(name, m_Uniforms);
		if (location != -1)
			glUniform1f(location, _v1);
        glUseProgram(0);
    }

    void Shader::SetUniform2f(string name, float _v1, float _v2)
    {
        glUseProgram(shaderID);
        auto location = GetUniformLocation(name, m_Uniforms);
		if (location != -1)
			glUniform2f(location, _v1, _v2);
        glUseProgram(0);
    }

    void Shader::SetUniform3f(string name, float _v1, float _v2, float _v3)
    {
        glUseProgram(shaderID);
        auto location = GetUniformLocation(name, m_Uniforms);
        if (location != -1)
			glUniform3f(location, _v1, _v2, _v3);
        glUseProgram(0);
    }

    void Shader::SetUniform4f(string name, float _v1, float _v2, float _v3, float _v4)
    {
        glUseProgram(shaderID);
        auto location = GetUniformLocation(name, m_Uniforms);
		if (location != -1)
			glUniform4f(location, _v1, _v2, _v3, _v4);
        glUseProgram(0);
    }

	void Shader::SetUniform4f(string name, Vector4D _vec)
	{
		glUseProgram(shaderID);
		auto location = GetUniformLocation(name, m_Uniforms);
		if (location != -1)
			glUniform4f(location, _vec.x, _vec.y, _vec.z, _vec.w);
		glUseProgram(0);
	}

    void Shader::SetUniformMat3f(string name, float *val)
    {
        glUseProgram(shaderID);
        auto location = GetUniformLocation(name, m_Uniforms);
		if (location != -1)
			glUniformMatrix3fv(location, 1, GL_FALSE, val);
        glUseProgram(0);
    }

    void Shader::SetUniformMat2f(string name, float *val)
    {
        glUseProgram(shaderID);
        auto location = GetUniformLocation(name, m_Uniforms);
		if (location != -1)
			glUniformMatrix2fv(location, 1, GL_FALSE, val);
        glUseProgram(0);
    }

    void Shader::SetUniformMat4f(string name, float *val)
    {
        glUseProgram(shaderID);
        auto location = GetUniformLocation(name, m_Uniforms);
		if (location != -1)
			glUniformMatrix4fv(location, 1, GL_FALSE, val);
        glUseProgram(0);
    }

    void Shader::SetUniform4fArray(string name, uint32_t numOfElement, float *arrayList) {
        glUseProgram(shaderID);
        auto location = GetUniformLocation(name, m_Uniforms);
		if (location != -1)
			glUniform4fv(location, numOfElement, arrayList);
        glUseProgram(0);
    }


    int GetUniformLocation(const string &name, vector<Uniform> uniformList)
    {
        for (auto &uniform : uniformList) {
            if(name == uniform.Name)
                return uniform.Location;
        }
        return -1;
    }
}