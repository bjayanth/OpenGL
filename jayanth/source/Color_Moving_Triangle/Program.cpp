#include "pch.h"
#include "Utility.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

GLuint program, VAO, VBO;

GLFWwindow* start_window()
{
    if (!glfwInit())
    {
        return NULL;
    }

    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Essentials", nullptr, nullptr);
    if (window == nullptr)
    {
        return NULL;
    }
    glfwMakeContextCurrent(window);

    if (gl3wInit() != 0)
    {
        return NULL;
    }

    glViewport(0, 0, 800, 600);
    return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void tri_vertices()
{

    GLfloat vertices[] =
    {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*) 0);
    glEnableVertexAttribArray(0);

}

GLuint compile_shaders()
{
    GLuint vertex_shader, fragment_shader;

    std::vector<GLchar> vertex_shader_source;
    Library::Utility::LoadBinaryFile(L"tri.vert", vertex_shader_source);
    GLchar* sourcePointer = &vertex_shader_source[0];
    GLint length = vertex_shader_source.size();
    GLint success;
    GLchar infoLog[1024];
    vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &sourcePointer, &length);
    glCompileShader(vertex_shader);
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR: " << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }

    std::vector<GLchar> fragment_shader_source;
    Library::Utility::LoadBinaryFile(L"tri.frag", fragment_shader_source);
    sourcePointer = &fragment_shader_source[0];
    length = fragment_shader_source.size();

    fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &sourcePointer, &length);
    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 1024, NULL, infoLog);
        std::cout << "ERROR::SHADER_COMPILATION_ERROR: " << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cout << "ERROR::PROGRAM_LINKING_ERROR: " << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
    }

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return program;

}

void transformation()
{
    glm::mat4 transform;
    transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
    transform = glm::translate(transform, glm::vec3(0.5f, -0.5f, 0.0f));

    GLuint uniformLoc = glGetUniformLocation(program, "transform");
    glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(transform));
}

int main()
{
    const glm::vec4 CornflowerBlue = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
    
    GLFWwindow* window = start_window();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    tri_vertices();
    program = compile_shaders();
    


    while (!glfwWindowShouldClose(window))
    {
        glClearBufferfv(GL_COLOR, 0, &CornflowerBlue[0]);

        glUseProgram(program);

        transformation();

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