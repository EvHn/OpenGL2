/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Mesh.cpp
 * Author: evgeny
 * 
 * Created on 5 марта 2018 г., 22:47
 */

#include "Mesh.h"

Mesh::Mesh() {
    drawMode = GL_TRIANGLES;
    model = glm::mat4(1.0f);
}

Mesh::Mesh(std::vector<GLfloat> points, std::vector<GLint> indices) {
    drawMode = GL_TRIANGLES;
    model = glm::mat4(1.0f);
    this->points = points;
    this->indices = indices;
    setup();
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteVertexArrays(1, &VAO);
}

GLint Mesh::get_sizeOfPoints() const {
    return GLint(points.size());
}

GLint Mesh::get_sizeOfIndices() const {
    return GLint(indices.size());
}

GLint Mesh::get_sizeOfPointsInBytes() const {
    return  GLint(points.size()) * sizeof(GLfloat);
}

GLint Mesh::get_sizeOfIndeicesInBytes() const {
    return  GLint(indices.size()) * sizeof(GLint);
}

GLint Mesh::get_sizeOfPointInBytes() const {
    return GLint(6 * sizeof(GLfloat));
}

GLenum Mesh::get_drawMode() const {
    return drawMode;
}

const void *Mesh::get_points() {
    return &points[0];
}

const void *Mesh::get_indices() {
    return &indices[0];
}

void Mesh::set_drawMode(GLenum drawMode) {
    this->drawMode = drawMode;
}
void Mesh::setup() { 
    
    glGenBuffers(1, &EBO);
    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, get_sizeOfPointsInBytes(), 
                 get_points(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, get_sizeOfIndeicesInBytes(),
                 get_indices(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
                          get_sizeOfPointInBytes(), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, get_sizeOfPointInBytes(),
                         (GLvoid*)(3* sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); // Note that this is allowed, the call to glVertexAttribPointer registered VBO as the currently bound vertex buffer object so afterwards we can safely unbind

    glBindVertexArray(0);   
}

void Mesh::draw(Shader &shader) {
    GLint modelLoc = glGetUniformLocation(shader.Program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(VAO);
    glDrawElements(get_drawMode(), get_sizeOfIndices(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}