/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Shader.h
 * Author: evgeny
 *
 * Created on 4 марта 2018 г., 15:16
 */

#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <GL/glew.h> // Подключаем glew для того, чтобы получить все необходимые заголовочные файлы OpenGL

class Shader {
public:
    Shader();
    Shader(const Shader& orig);
    Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
    ~Shader();
    void Use();

    GLuint Program;
private:

};

#endif

