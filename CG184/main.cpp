#include <GL\glew.h>

//#include <glm.hpp>
//#include <gtc/matrix_transform.hpp>
//#include <gtc/type_ptr.hpp>

#include <iostream>

#include "src/Graphics/Window.h"
#include "src/Graphics/Shader.h"
#include "src/Graphics/Renderer.h"

#include "src/Maths/Matrix4D.h"

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
	unsigned int transformLoc = glGetUniformLocation(ourShader.shaderID, "transform");
	
	while (!window->IfWindowClosed())
	{
		window->ProcessInput();
		window->SetBGColor(0.2f, 0.8, 0.5, 1.0f);
		ourShader.ActivateShader();

		Matrix4D trans(1.0);
		trans = Matrix4D::Translate(trans, 0.5f, -0.5f, 0.0f);
		trans = Matrix4D::Rotate(trans, (float)glfwGetTime() * 100, Vector3D(0.0f, 0.0f, 1.0f));
		
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, trans.elements);
		glUniform1f(mixLocationInShader, mixValue);

		renderer.Render();
		ourShader.DeactivateShader();

		window->Update();
	}


	window->Close();
	delete window;
	return 0;
}
