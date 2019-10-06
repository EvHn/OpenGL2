/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Cylinder.cpp
 * Author: evgeny
 * 
 * Created on 4 марта 2018 г., 19:45
 */
#include "Cylinder.h"

Cylinder:: Cylinder(GLfloat l, GLfloat r, GLint rn, GLfloat colorBegin[3], GLfloat colorEnd[3]) {
    this->l = l;
    this->r = r;
    this->rn = rn;
    GLfloat theta = 2 * M_PI / rn;
    for (int i = 0; i < 6 * rn; i += 6)
    {

        points.push_back(l / 2); 
        points.push_back(r * cos(theta * i / 6));
        points.push_back(r * sin(theta * i / 6));
        points.push_back(colorBegin[0]);
        points.push_back(colorBegin[1]);
        points.push_back(colorBegin[2]);
    }
    for (int i = rn * 6; i < 12 * rn; i += 6)
    {
        points.push_back(-l / 2);
        points.push_back(r * cos(theta * i / 6));
        points.push_back(r * sin(theta * i / 6));
        points.push_back(colorEnd[0]);
        points.push_back(colorEnd[1]);
        points.push_back(colorEnd[2]);
    }
    
    int j = 0;
    for (int i = 0; i < rn - 2; i++)
    {
        indices.push_back(0);
        indices.push_back(i + 1);
        indices.push_back(i + 2);
    }
    for (int i = 0; i < rn - 1; i++)
    {
        indices.push_back(i);
        indices.push_back(i + rn);
        indices.push_back(i + rn + 1);
        indices.push_back(i);
        indices.push_back(i + rn + 1);
        indices.push_back(i + 1);
    }
    indices.push_back(rn - 1);
    indices.push_back(2 * rn - 1);
    indices.push_back(rn);
    indices.push_back(rn - 1);
    indices.push_back(rn);
    indices.push_back(0);
    for (int i = 0; i < rn - 2; i++)
    {
        indices.push_back(rn);
        indices.push_back(rn + i + 1);
        indices.push_back(rn + i + 2);
    }
    setup();
}

Cylinder::Cylinder(const Cylinder& orig) {
}

Cylinder::~Cylinder() {
}