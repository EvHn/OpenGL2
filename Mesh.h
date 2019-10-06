/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mesh.h
 * Author: evgeny
 *
 * Created on 5 марта 2018 г., 22:47
 */

#ifndef MESH_H
#define MESH_H
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include <vector>

class Mesh {
public:
    Mesh();
    Mesh(std::vector<GLfloat> points, std::vector<GLint> indices);
    virtual ~Mesh();
    GLint get_sizeOfPoints() const;
    GLint get_sizeOfIndices() const;
    GLint get_sizeOfPointsInBytes() const;
    GLint get_sizeOfIndeicesInBytes() const;
    GLint get_sizeOfPointInBytes() const;
    GLenum get_drawMode() const;
    const void *get_points();
    const void *get_indices();
    
    void set_drawMode(GLenum drowMode);
    void setup();
    virtual void draw(Shader &shader);
    GLuint VAO, VBO, EBO;
    glm::mat4 model;
protected:
    std::vector<GLfloat> points;
    std::vector<GLint> indices; 
    GLenum drawMode;
};

#endif /* MESH_H */

