#pragma once

#include <GL\glew.h>
#include <iostream>



namespace CG184 
{
	enum TextureType
	{
		Diffuse = 0,
		Specular,
		Normal,
		Bump,
		Reflection
	};


	class Texture
	{
	public:



		Texture();
		~Texture();

		void LoadTexture(const char* const texturePath);

		// TODO make it private
	public:
		GLuint textureID;
	};

}