#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include <vector>

#include "Texture.h"
#include "../Maths/Maths.h"

namespace CG184 
{
    using namespace std;
	class Uniform
	{
    public:
		//SHADER_TYPE Type;
		std::string Name;
		int Size;
		uint32_t Location;
	};

    class VertexAttribute
	{
    public:
		//SHADER_TYPE Type;
		std::string Name;
		int Size;
		uint32_t Location;
	};

	class Shader
	{
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		Shader(const Shader& a_Shader);
		~Shader();

		void ActivateShader();
		void DeactivateShader();

		void AddTexture(const char* texturePath, TextureType texType);

		// TODO add More Uniform Setter functions
        void SetUniform1f(string name, float _v1);
		void SetUniform1i(string name, int _v1);
        void SetUniform2f(string name, float _v1, float _v2);
        void SetUniform3f(string name, float _v1, float _v2, float _v3);
        void SetUniform4f(string name, float _v1, float _v2, float _v3, float _v4);
		void SetUniform4f(string name, Vector4D _v4);

        void SetUniformMat2f(string name, float* val);
        void SetUniformMat3f(string name, float* val);
        void SetUniformMat4f(string name, float* val);

		void SetUniform4fArray(string name, uint32_t numOfElement, float* arrayList);

		uint32_t GetShaderID() const { return shaderID; }

	private:
		uint32_t shaderID;
		std::vector<Uniform> m_Uniforms;
		std::vector<VertexAttribute> m_Attributes;

		Texture m_Textures[5] = {}; // TODO Fix -> Hard Coded Fixed No. of Texture Support.
		
		void CompileShader(uint32_t shader, std::string type);
	};

}
