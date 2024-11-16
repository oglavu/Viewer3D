#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Object.hpp"
#include "Parser.hpp"
#include "Viewer.hpp"
#include <iostream>


int main(void) {
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(640, 480, "Viewer3D", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewInit();
    glViewport(0, 0, 640, 480);

    glfwSetCursorPosCallback(window, Viewer::cursorCallback);
    glfwSetScrollCallback(window, Viewer::scrollCallback);

    ObjectPtr object = Parser::parseFile("./resources/untitled.obj");
    object->compile();
    ShaderPtr shader (new Shader("./resources/simple_vertex.shader", "./resources/simple_fragment.shader"));
    object->setShader(shader);

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        object->render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}