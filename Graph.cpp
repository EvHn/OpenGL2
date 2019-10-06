/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Graph.cpp
 * Author: evgeny
 * 
 * Created on 7 марта 2018 г., 21:55
 */

#include "Graph.h"

Graph::Graph(std::vector<GLfloat> x, std::vector<GLfloat> y, GLfloat color[3]) {
    int size = (x.size()<y.size()) ? x.size() : y.size();
    drawMode = GL_LINES;
    for (int i = 0; i < size; i++)
    {
        points.push_back(x[i]);
        points.push_back(y[i]);
        points.push_back(0);
        points.push_back(color[0]);
        points.push_back(color[1]);
        points.push_back(color[2]);
    }
    for (int i = 0; i < size - 1; i++)
    {
        indices.push_back(i);
        indices.push_back(i + 1);
    }
    setup();
}

Graph::Graph(const Graph& orig) {
}

Graph::~Graph() {
}

