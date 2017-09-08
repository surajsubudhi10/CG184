#pragma once

#include <GL\glew.h>
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

namespace CG184 
{
	class Shader
	{
	public:
		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		void ActivateShader();
		void DeactivateShader();

		unsigned int shaderID;

	private:
		void CompileShader(unsigned int shader, std::string type);
	};

}
