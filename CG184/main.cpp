#include <GL\glew.h>
//#include <GLFW/glfw3.h>

//#define STB_IMAGE_IMPLEMENTATION   

//#include <stb_image.h>
//#include <filesystem.h>

#include <iostream>

#include "src/Graphics/Window.h"
#include "src/Graphics/Shader.h"
#include "src/Graphics/Renderer.h"
//#include "src/Graphics/Texture.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
using namespace CG184;


// stores how much we're seeing of either texture
float mixValue = 0.2f;

int main()
{

	Window *window = new Window(SCR_WIDTH, SCR_HEIGHT, "Basic Window");
	
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "Error : " << glewGetErrorString(err) << std::endl;
		return 0;
	}

	float vertices[] = {
		// positions          // colors           // texture coords
		 0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
		 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
	};
	std::vector<float> v(vertices, vertices + sizeof vertices / sizeof vertices[0]);

	GLuint indices[] = {
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};
	std::vector<GLuint> ind(indices, indices + sizeof indices / sizeof indices[0]);


	Shader ourShader("TestShaders/texture.vs", "TestShaders/texture.fs");
	//Shader ourShader("TestShaders/testShader.vs", "TestShaders/testShader.fs");
	Renderer renderer(v, ind);

	ourShader.AddTexture("Resources/textures/container.jpg", TextureType::Diffuse);
	ourShader.AddTexture("Resources/textures/awesomeface.png", TextureType::Specular);
	

	GLuint mixLocationInShader = glGetUniformLocation(ourShader.shaderID, "mixValue");

	
	while (!window->IfWindowClosed())
	{
		window->ProcessInput();
		window->SetBGColor(0.2f, 0.8, 0.5, 1.0f);
		ourShader.ActivateShader();

		glUniform1f(mixLocationInShader, mixValue);

		renderer.Render();
		ourShader.DeactivateShader();

		window->Update();
	}


	window->Close();
	delete window;
	return 0;
}
