#include "pch.h"
#include "Utility.h"

GLuint compile_shaders()
{
	GLuint vertex_shader, fragment_shader, program, vertex_array_object;

	std::vector<GLchar> vertex_shader_source;
	Library::Utility::LoadBinaryFile(L"tri.vert", vertex_shader_source);
	GLchar* sourcePointer = &vertex_shader_source[0];
	GLint length = vertex_shader_source.size();
	
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, &sourcePointer, &length);
	glCompileShader(vertex_shader);

	std::vector<GLchar> fragment_shader_source;
	Library::Utility::LoadBinaryFile(L"tri.frag", fragment_shader_source);
	sourcePointer = &fragment_shader_source[0];
	length = fragment_shader_source.size();
	
	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, &sourcePointer, &length);
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