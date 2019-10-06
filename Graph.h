/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Graph.h
 * Author: evgeny
 *
 * Created on 7 марта 2018 г., 21:55
 */

#ifndef GRAPH_H
#define GRAPH_H
#include "Mesh.h"
#include <vector>

class Graph : public Mesh::Mesh {
public:
    Graph(std::vector<GLfloat> x, std::vector<GLfloat> y, GLfloat color[3]);
    Graph(const Graph& orig);
    virtual ~Graph();
private:

};

#endif /* GRAPH_H */

