#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Object.hpp"
#include "Parser.hpp"
#include "Viewer.hpp"
#include <iostream>

#include <parser_test.hpp>


static const unsigned WIDTH = 640, HEIGHT = 480;

int main(void) {

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Viewer3D", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cout << "Error";
    }


    //glfwSetCursorPosCallback(window, Viewer::cursorCallback);
    //glfwSetScrollCallback(window, Viewer::scrollCallback);

    ObjectPtr object = Parser::parseFile("./resources/untitled.obj");
    std::cout<<*object.get();
    object->compile();
    ShaderPtr shader (new Shader("./resources/simple_vertex.glsl", "./resources/simple_fragment.glsl"));
    object->setShader(shader);


    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        object->render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}