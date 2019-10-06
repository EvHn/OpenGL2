/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Axis.cpp
 * Author: evgeny
 * 
 * Created on 8 марта 2018 г., 12:37
 */

#include "Axis.h"

Axis::Axis(GLfloat lengthX, GLfloat lengthY, GLfloat color[3]) {
    drawMode = GL_LINES;
    points.resize(18);
    points[0] = lengthX;
    points[1] = 0;
    points[2] = 0;
    points[6] = 0;
    points[7] = 0;
    points[8] = 0;
    points[12] = 0;
    points[13] = lengthY;
    points[14] = 0;
    for (int i = 3; i < 18; i += 6)
    {
        points[i] = color[0];
        points[i + 1] = color[1];
        points[i + 2] = color[2];
    }
    indices.resize(4);
    indices[0] = 0;
    indices[1] = 1;
    indices[2] = 1;
    indices[3] = 2;
    
    std::vector<GLfloat> arrowPoints;
    arrowPoints.resize(18);
    arrowPoints[0] = 0.1f;
    arrowPoints[1] = 0.0f;
    arrowPoints[2] = 0.0f;
    arrowPoints[6] = 0.0f;
    arrowPoints[7] = 0.1f;
    arrowPoints[8] = 0.0f;
    arrowPoints[12] = 0.0f;
    arrowPoints[13] = -0.1f;
    arrowPoints[14] = 0.0f;
    for (int i = 3; i < 18; i += 6)
    {
        arrowPoints[i] = color[0];
        arrowPoints[i + 1] = color[1];
        arrowPoints[i + 2] = color[2];
    }
    std::vector<GLint> arrowIndices;
    arrowIndices.push_back(0);
    arrowIndices.push_back(1);
    arrowIndices.push_back(2);
    arrowX = new Mesh(arrowPoints, arrowIndices);
    arrowX->set_drawMode(GL_TRIANGLES);
    arrowX->model = glm::translate(glm::mat4(1.0f), glm::vec3(lengthX, 0.0f, 0.0f));
    
    arrowY = new Mesh(arrowPoints, arrowIndices);
    arrowY->set_drawMode(GL_TRIANGLES);
    arrowY->model = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    arrowY->model = glm::translate(arrowY->model, glm::vec3(lengthY, 0.0f, 0.0f));
    setup();
}

Axis::Axis(const Axis& orig) {
}

Axis::~Axis() {
}

void Axis::draw(Shader &shader) {
    GLint modelLoc = glGetUniformLocation(shader.Program, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    glBindVertexArray(VAO);
    glDrawElements(get_drawMode(), get_sizeOfIndices(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    glm::mat4 modelArrow(model * arrowX->model);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelArrow));
    glBindVertexArray(arrowX->VAO);
    glDrawElements(arrowX->get_drawMode(), arrowX->get_sizeOfIndices() , GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
    modelArrow =  model * arrowY->model;
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelArrow));
    glBindVertexArray(arrowY->VAO);
    glDrawElements(arrowY->get_drawMode(), arrowY->get_sizeOfIndices() , GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}
