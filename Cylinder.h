/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cylinder.h
 * Author: evgeny
 *
 * Created on 4 марта 2018 г., 19:45
 */

#ifndef CYLINDER_H
#define CYLINDER_H
#include <GL/glew.h>
#include <math.h>
#include "Mesh.h"

class Cylinder : public Mesh::Mesh {
public:
    Cylinder(GLfloat l, GLfloat r, GLint rn, GLfloat colorBegin[3], GLfloat colorEnd[3]);
    Cylinder(const Cylinder& orig);
    virtual ~Cylinder();
private:
    GLfloat r;
    GLint rn;
    GLfloat l;
};

#endif /* CYLINDER_H */