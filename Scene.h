/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Scene.h
 * Author: evgeny
 *
 * Created on 5 марта 2018 г., 22:42
 */

#ifndef SCENE_H
#define SCENE_H
#include "Mesh.h"
#include <GL/glew.h>
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Scene {
public:
    Scene();
    Scene(const Scene& orig);
    virtual ~Scene();
    void add(Mesh *mesh);
    void draw(Shader &shader);
    void get_numOfMesh();
    glm::mat4 view;
    glm::mat4 projection;
private:
    int numOfMeshes;
    Mesh **meshes;
};

#endif /* SCENE_H */

