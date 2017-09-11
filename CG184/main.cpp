#include <GL\glew.h>

#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

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
		 0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right			//0
		 0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right		//1
		-0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left		//2
		-0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // top left			//3

		 0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right			//4
		 0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right		//5
		-0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left		//6
		-0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left			//7
	};


	std::vector<float> v(vertices, vertices + sizeof vertices / sizeof vertices[0]);

	GLuint indices[] = {
		2, 1, 0, // first triangle
		0, 3, 2, // second triangle

		4, 0, 1,
		1, 5, 4,

		6, 7, 4,
		4, 5, 6,

		3, 7, 6,
		7, 6, 2,

		0, 4, 7,
		7, 3, 0,

		1, 5, 6,
		6, 2, 1
	};
	std::vector<GLuint> ind(indices, indices + sizeof indices / sizeof indices[0]);

	Vector3D cubePositions[] = {
		Vector3D(0.0f,  0.0f,  0.0f),
		Vector3D(2.0f,  5.0f, -15.0f),
		Vector3D(-1.5f, -2.2f, -2.5f),
		Vector3D(-3.8f, -2.0f, -12.3f),
		Vector3D(2.4f, -0.4f, -3.5f),
		Vector3D(-1.7f,  3.0f, -7.5f),
		Vector3D(1.3f, -2.0f, -2.5f),
		Vector3D(1.5f,  2.0f, -2.5f),
		Vector3D(1.5f,  0.2f, -1.5f),
		Vector3D(-1.3f,  1.0f, -1.5f)
	};

	


	Shader ourShader("TestShaders/coordinate_systems.vs", "TestShaders/coordinate_systems.fs");
	//Shader ourShader("TestShaders/testShader.vs", "TestShaders/testShader.fs");
	//Renderer renderer1(v, ind);
	std::vector<Renderer>renderer_list;
	renderer_list.reserve(10);
	Renderer renderer1(v, ind);

	for (int i = 0; i < 10; i++) 
	{
		renderer_list.push_back(renderer1);
	}

	ourShader.AddTexture("Resources/textures/container.jpg", TextureType::Diffuse);
	ourShader.AddTexture("Resources/textures/awesomeface.png", TextureType::Specular);
	

	GLuint mixLocationInShader	= glGetUniformLocation(ourShader.shaderID, "mixValue");
	GLuint transformLoc			= glGetUniformLocation(ourShader.shaderID, "transform");
	GLuint modelLoc				= glGetUniformLocation(ourShader.shaderID, "model");
	GLuint viewLoc				= glGetUniformLocation(ourShader.shaderID, "view");
	GLuint projectionLoc		= glGetUniformLocation(ourShader.shaderID, "projection");

	ourShader.ActivateShader();
	Matrix4D projMat;
	projMat = Matrix4D::prespective(45.0f, (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, projMat.elements);
	ourShader.DeactivateShader();
	
	while (!window->IfWindowClosed())
	{
		window->ProcessInput();
		window->SetBGColor(0.2f, 0.8, 0.5, 1.0f);
		ourShader.ActivateShader();

		//Matrix4D model(1.0f);
		//model = Matrix4D::Rotate(model, 45.0f, Vector3D(1.0f, 0.0f, 1.0f));
		//model = Matrix4D::Scale(model, 2.0f, 2.0f, 2.0f);

		Matrix4D view(1.0f);
		view = Matrix4D::Translate(view, 0.0f, 0.0f, -3.0f);

		Matrix4D trans(1.0);
		////trans = Matrix4D::Translate(trans, 0.5f, -0.5f, 0.0f);
		////trans = Matrix4D::Rotate(trans, (float)glfwGetTime() * 100, Vector3D(0.0f, 0.0f, 1.0f));
		
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.elements);
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, view.elements);
		glUniform1f(mixLocationInShader, mixValue);

		//renderer1.Render();

		for (unsigned int i = 0; i < 10; i++)
		{
			// calculate the model matrix for each object and pass it to shader before drawing
			Matrix4D model;
			model = Matrix4D::Translate(model, cubePositions[i].x, cubePositions[i].y, cubePositions[i].z);
			float angle = 20.0f * i;
			model = Matrix4D::Rotate(model, angle, Vector3D(1.0f, 0.3f, 0.5f));
			glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model.elements);

			renderer_list[i].Render();
		}

		ourShader.DeactivateShader();
		window->Update();
	}


	window->Close();
	delete window;
	return 0;
}
