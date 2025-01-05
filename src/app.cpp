#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Object.hpp"
#include "Parser.hpp"
#include "Viewer.hpp"
#include <iostream>

#define GLM_ENABLE_EXPERIMENTAL

#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/io.hpp>

static const unsigned WIDTH = 640, HEIGHT = 480;

int main(void) {

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Viewer3D", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    if (glewInit() != GLEW_OK) {
        std::cout << "Error";
    }

    glfwSetCursorPosCallback(window, Viewer::cursorCallback);
    glfwSetScrollCallback(window, Viewer::scrollCallback);


    ShaderPtr shader(new Shader("./resources/simple_vertex.glsl", "./resources/simple_fragment.glsl"));
    ObjectPtr object = Parser::parseFile("./resources/ex1.obj");

    object->setShader(shader);
    object->compile();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glm::mat4 model = glm::mat4(1);
        glm::mat4 view = Viewer::getViewMatrix();
        glm::mat4 projection = glm::perspective(Viewer::getFov(),
            (float)WIDTH / HEIGHT, 0.1f, 100.0f);

        shader->uniform("model", model);
        shader->uniform("view", view);
        shader->uniform("projection", projection);

        glm::mat3 m = glm::transpose(glm::inverse(model));
        shader->uniform("norm", m);

        glm::vec3 eye = Viewer::getEye();
        shader->uniform("eye", eye);

        object->draw();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}