#include <GL\glew.h>
//#include <GLFW/glfw3.h>


#include <iostream>

#include "src/Graphics/Window.h"
#include "src/Graphics/Shader.h"
#include "src/Graphics/Renderer.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
using namespace CG184;


int main()
{

	Window *window = new Window(SCR_WIDTH, SCR_HEIGHT, "Basic Window");
	
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		std::cout << "Error : " << glewGetErrorString(err) << std::endl;
		return 0;
	}


	Shader ourShader("TestShaders/testShader.vs", "TestShaders/testShader.fs");
	

	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};
	std::vector<float> v(vertices, vertices + sizeof vertices / sizeof vertices[0]);

	Renderer renderer(v);


	while (!window->IfWindowClosed())
	{
		window->ProcessInput();
		window->SetBGColor(0.2f, 0.8, 0.5, 1.0f);

		ourShader.ActivateShader();
		renderer.Render();
		ourShader.DeactivateShader();

		window->Update();
	}


	window->Close();
	delete window;
	return 0;
}
