#pragma once

#include <GL/glew.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include <vector>

#include "Texture.h"

namespace CG184 
{
	class Shader
	{
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		void ActivateShader();
		void DeactivateShader();

		void AddTexture(const char* const texturePath, TextureType texType);

		unsigned int shaderID;

	private:

		Texture m_Textures[5] = {}; // Hard Coded Fixed No. of Texture Support.
		
		void CompileShader(unsigned int shader, std::string type);
	};

}
