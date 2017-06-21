#include "pch.h"
#include <iostream>
#include "Utility.h"
#include "stb_image.h"


GLuint VBO, VAO, EBO, texture;

GLuint compile_shaders()
{
    GLuint vertex_shader, fragment_shader, program, vertex_array_object;

    std::vector<GLchar> vertex_shader_source;
    Library::Utility::LoadBinaryFile(L"tex.vert", vertex_shader_source);
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
    Library::Utility::LoadBinaryFile(L"tex.frag", fragment_shader_source);
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

    glGenVertexArrays(1, &vertex_array_object);
    glBindVertexArray(vertex_array_object);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    return program;

}

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

void cube_vertices()
{
    GLfloat vertices[] = {
        // positions          // colors           // texture coords
        0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
        0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 

    };

    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
}

void texture_load()
{
    glGenTextures(1, &texture);
    //glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    unsigned char * data = stbi_load(std::string("C:/Users/jayabapu/Desktop/Repository/jayanth/bootcamp/jayanth/content/Textures/wall.jpg").c_str(), &width, &height, &nrChannels, 0);

    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Texture not present" << std::endl;
    }


    stbi_image_free(data);
}


int main()
{
    const glm::vec4 backgorund_color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);


    GLFWwindow* window = start_window();

    GLuint program = compile_shaders();
    cube_vertices();
    texture_load();

    while (!glfwWindowShouldClose(window))
    {
        glClearBufferfv(GL_COLOR, 0, &backgorund_color[0]);
//        glActiveTexture(GL_TEXTURE0);

 //       glBindTexture(GL_TEXTURE_2D, texture);

        glUseProgram(program);
//        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteProgram(program);
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}