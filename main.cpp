/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: evgeny
 *
 * Created on 4 марта 2018 г., 15:13
 */

#define GLEW_STATIC
#include <iostream>
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "Cylinder.h"
#include "Scene.h"
#include "Mesh.h"
#include "Rod.h"
#include "Graph.h"
#include "Axis.h"

const GLuint WIDTH = 1000, HEIGHT = 600;
double mouseX;
double mouseY;
GLfloat scale = 1;
GLfloat xRotation = 1, yRotation = 1, zRotation = 1;
bool press = false;
GLfloat posZ = 0.0f;
double mouseXnew;
double mouseYnew;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void cameraRotation(GLFWwindow* window);

int main()
{
    //Инициализация GLFW
    glfwInit();
    //Настройка GLFW
    //Задается минимальная требуемая версия OpenGL.
    //Мажорная
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    //Минорная
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //Установка профайла для которого создается контекст
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    //Выключение возможности изменения размера окна
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    //Создание окна
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Rod", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
	return -1;
    }
    glfwMakeContextCurrent(window);
//    Инициализация GLEW
    glewExperimental = GL_TRUE;
    int widht = 800, height = 600;
    glfwGetFramebufferSize(window, &widht, &height);
    glViewport(0, 0, WIDTH, HEIGHT);
    glfwSetKeyCallback(window, key_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    Scene *scene = new Scene();
    std::vector<GLfloat> x({-3.0f, -2.5f, -2.0f, -1.5f, -1.0f, -0.5f,
                   0.0f, 0.5f, 1.0f, 1.5f, 2.0f, 2.5f, 3.0f});
    std::vector<GLfloat> y({2.5f, 2.0f, 1.7f, 1.5f, 1.6f, 1.8f, 2.1f,
                   1.8f, 1.2f, 0.8f, 0.6f, 0.4f, 0.2f});
    GLfloat green[] = {0.0f, 1.0f, 0.0f};
    GLfloat r = 0.5f;
    //Mesh *rod = new Rod(x, y, 13, r, 30);
    Mesh *cylinder = new Cylinder(6.0f, r, 20, green, green);
    Mesh *graph = new Graph(x, y, green);
    Mesh *axis = new Axis(6, 3, green);
    graph->model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, r + 0.1f, 0.0f));
    axis->model = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f,  r + 0.1f,0.0f));
//    scene->add(rod);
    scene->add(cylinder);
    scene->add(graph);
    scene->add(axis);
    Shader shader = Shader("shaders/shader.vs", "shaders/shader.fs");
    shader.Use();   
    glClearColor(0.2, 0.2, 0.2, 1);
    glEnable(GL_DEPTH_TEST);
//    glShadeModel(GL_FLAT); // режим без сглаживания (для теней)
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);//GL_LINE

    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 eye;
//  игровой цикл. Чтобы приложени не упало сражу поле отрисовки одного изображения
    while(!glfwWindowShouldClose(window))// проверяет закрыто ли окно
    {
        glfwPollEvents(); //проверяет выжов всех событий (мышь, клавиатура)

        view = glm::translate(eye, glm::vec3(0.0f, -0.5f, -1.0f + posZ));
        view = glm::rotate(view, glm::radians(xRotation), glm::vec3(1.0f, 0.0f, 0.0f));
        view = glm::rotate(view, glm::radians(yRotation), glm::vec3(0.0f, 1.0f, 0.0f));       
        projection = glm::perspective(45.0f, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);
        scene->view = view;
        scene->projection = projection;
        
        cameraRotation(window);
        //здась происходит отрисовка вся
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        scene->draw(shader);
        
        glfwSwapBuffers(window); // меняет буфер отрисовки
    }
    scene->~Scene();
    glfwTerminate(); //очистка выделенного нам места
    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // Когда пользователь нажимает ESC, мы устанавливаем свойство WindowShouldClose в true,
    // и приложение после этого закроется
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    	glfwSetWindowShouldClose(window, GL_TRUE);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    glfwGetCursorPos(window, &mouseX, &mouseY);
    if (state == GLFW_PRESS) 
    {
        press = true;
    }
 
    if (state == GLFW_RELEASE) 
    {
        press = false;
    }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if ((posZ <= 1.0f) || ((posZ >= 1.0f) && (yoffset < 0)))
        posZ += 0.1 * yoffset;
}

void cameraRotation(GLFWwindow* window)
{
    if (press) {
    glfwGetCursorPos(window, &mouseXnew, &mouseYnew);
    xRotation -= (180 / scale) * (mouseY - mouseYnew) / HEIGHT;
    yRotation -= (180 / scale) * (mouseX - mouseXnew) / WIDTH;
    mouseX = mouseXnew;
    mouseY = mouseYnew;
    }
}
