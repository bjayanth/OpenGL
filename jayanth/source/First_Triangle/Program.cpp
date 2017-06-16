#include "pch.h"

GLuint compile_shaders()
{
	GLuint vertex_shader, fragment_shader, program, vertex_array_object;

	static const char * vertex_shader_source[] =
	{
		"#version 440 core                             \n"
		"                                              \n"
		"void main(void)                               \n"
		"{                                             \n"
		"   const vec4 vertices[3] = vec4[3](vec4(0.25, -0.25, 0.5, 1.0), \n"
		"                                    vec4(-0.25, -0.25, 0.5, 1.0), \n"
		"                                    vec4(0.25, 0.25, 0.5, 1.0)); \n"
		"   gl_Position = vertices[gl_VertexID];   \n"
		"}                                             \n"
	};

	static const char * fragment_shader_source[] =
	{
		"#version 440 core                             \n"
		"                                              \n"
		"out vec4 color;                               \n"
		"                                              \n"
		"void main(void)                               \n"
		"{                                             \n"
		"    color = vec4(1.0, 0.8, 1.0, 1.0);         \n"
		"}                                             \n"
	};

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);
	return program;

}


int main()
{
	const glm::vec4 CornflowerBlue = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	if (!glfwInit())
	{
		return -1;
	}

	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Essentials", nullptr, nullptr);
	if (window == nullptr)
	{
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (gl3wInit() != 0)
	{
		return -1;
	}

	glViewport(0, 0, 800, 600);


	GLuint program = compile_shaders();
	


	while (!glfwWindowShouldClose(window))
	{
		glClearBufferfv(GL_COLOR, 0, &CornflowerBlue[0]);

		glUseProgram(program);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteProgram(program);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}