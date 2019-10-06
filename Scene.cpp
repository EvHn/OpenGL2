/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Scene.cpp
 * Author: evgeny
 * 
 * Created on 5 марта 2018 г., 22:42
 */

#include "Scene.h"

Scene::Scene() {
    numOfMeshes = 0;
}

Scene::Scene(const Scene& orig) {
}

Scene::~Scene() {
    for (GLuint i = 0; i < numOfMeshes; i++)
    {
        meshes[i]->~Mesh();
    }
    delete meshes;
}

void Scene::add(Mesh *mesh) {
    if (numOfMeshes > 0)
    {
        Mesh **cpyMeshes = meshes;
        meshes = new Mesh *[numOfMeshes + 1]; 
        for (int i = 0; i < numOfMeshes; i++)
        {
            meshes[i] = cpyMeshes[i];
        }
        delete cpyMeshes;
    }
    else
    {
        meshes = new Mesh *[1];
    }
    meshes[numOfMeshes] = mesh;
    numOfMeshes++;
}
void Scene::draw(Shader &shader) {  
    GLint viewLoc = glGetUniformLocation(shader.Program, "view");
    GLint projLoc = glGetUniformLocation(shader.Program, "projection"); 
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection)); 
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    if (numOfMeshes)
        for (GLuint i = 0; i < numOfMeshes; i++)
        {
            meshes[i]->draw(shader);
        }
}