//
// Created by carol on 11/17/18.
//

#ifndef UNTITLED_SCENE_H
#define UNTITLED_SCENE_H
#include "NavMesh.h"


class Scene {
public:
    Scene();
    ~Scene();

    void drawScene(Agente * agente, int nWall, Wall *obstacles);
    void drawoBbstacles(int nWall, Wall *obstacles);
    void drawAgent(Agente *agente);

};


#endif //UNTITLED_SCENE_H
