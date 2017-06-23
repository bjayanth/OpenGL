#include "pch.h"
#include <iostream>
#include "Utility.h"
#include "stb_image.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint VBO, VAO, EBO, texture, program;

GLuint compile_shaders()
{
    GLuint vertex_shader, fragment_shader, vertex_array_object;

    std::vector<GLchar> vertex_shader_source;
    Library::Utility::LoadBinaryFile(L"cube.vert", vertex_shader_source);
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
    Library::Utility::LoadBinaryFile(L"cube.frag", fragment_shader_source);
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

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void cube_vertices()
{
/*    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.5f,    0.0f, 0.0f,    //Bottom left front
        0.5f, -0.5f, 0.5f,    1.0f, 0.0f,    //Bottom right front
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,    //Bottom left back
        0.5f, -0.5f, -0.5f,    1.0f, 1.0f,    //Bottom right back

        -0.5f, 0.5f, 0.5f,    0.0f, 0.0f,    //Top left front
        0.5f, 0.5f, 0.5f,    1.0f, 0.0f,    //Top right front
        -0.5f, 0.5f, -0.5f,    0.0f, 1.0f,    //Top left back
        0.5f, 0.5f, -0.5f,    1.0f, 1.0f    //Top right back
    };

    GLuint indices[] = {
        0, 1, 2,    //Bottom face
        1, 3, 2,
        4, 6, 5,    //Top face
        6, 7, 5,
        1, 5, 3,    //Right face
        5, 7, 3,
        4, 0, 2,    //Left face
        2, 6, 4,
        0, 4, 1,    //Front face
        4, 5, 1,
        3, 7, 2,    //Back face
        7, 6, 2
    };
*/
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
//    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

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

void transformation()
{
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 projection;
//    model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), (float)800 / (float)600, 0.1f, 100.0f);
    //projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, 0.1f, 100.0f);

    GLuint modelLoc = glGetUniformLocation(program, "model");
    GLuint viewLoc = glGetUniformLocation(program, "view");
    GLuint projectLoc = glGetUniformLocation(program, "projection");

    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    // note: currently we set the projection matrix each frame, but since the projection matrix rarely changes it's often best practice to set it outside the main loop only once.
    glUniformMatrix4fv(projectLoc, 1, GL_FALSE, &projection[0][0]);
}

int main()
{
    const glm::vec4 backgorund_color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);


    GLFWwindow* window = start_window();
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    GLuint program = compile_shaders();
    cube_vertices();
    texture_load();
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window))
    {
        glClearBufferfv(GL_COLOR, 0, &backgorund_color[0]);
        glClear(GL_DEPTH_BUFFER_BIT);


        glUseProgram(program);

        transformation();

//       glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_TRIANGLES, 0, 36);

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