#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "shaderClass.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"


int main() 
{
	glfwInit();
	// Set the required OpenGL version and profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Use the core profile for modern OpenGL features
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Define the vertices for a triangle
	GLfloat vertices[] = {
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,		0.0f, 0.8f, 0.3f, 0.2f,		// Lower left vertex
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,			0.0f, 0.8f, 0.3f, 0.2f,		// Lower right vertex
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,		0.0f, 1.0f, 0.6f, 0.32f,		// Upper vertex


		- 0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,	0.0f, 0.9f, 0.45f, 0.17f,		// Lower left vertex
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,		0.0f, 0.9f, 0.45f, 0.17f,		// Lower right vertex
		0.0f,  -0.5f * float(sqrt(3)) / 3, 0.0f,		0.0f, 0.8f, 0.3f, 0.2f		// Upper vertex
	};

	GLuint indices[] = {
		0, 3, 5, // First triangle
		3, 2, 4, // Second triangle
		5, 4, 1	 // Third triangle
	};



	// Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(800, 800, "Glare", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();

	// Set the viewport to cover the new window
	glViewport(0, 0, 800, 800);

	Shader shaderProgram("default.vert", "default.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Link the VBO to the VAO with the specified layout
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
	VAO1.LinkAttrib(VBO1, 1, 4, GL_FLOAT, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// Set up vertex data and buffers and configure vertex attributes
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);


	// Main Render loop
	while (!glfwWindowShouldClose(window))
	{
		shaderProgram.Activate();

		VAO1.Bind();

		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}