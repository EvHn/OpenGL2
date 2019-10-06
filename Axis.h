/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Axis.h
 * Author: evgeny
 *
 * Created on 8 марта 2018 г., 12:37
 */

#ifndef AXIS_H
#define AXIS_H
#include "Mesh.h"
#include "Shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Axis : public Mesh::Mesh {
public:
    Axis(GLfloat lengthX, GLfloat lengthY, GLfloat color[3]);
    Axis(const Axis& orig);
    virtual ~Axis();
    virtual void draw(Shader &shader);
private:
    Mesh *arrowX;
    Mesh *arrowY;
};

#endif /* AXIS_H */