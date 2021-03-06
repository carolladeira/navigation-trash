//
// Created by carol on 11/17/18.
//

#ifndef UNTITLED_SCENE_H
#define UNTITLED_SCENE_H
#include "NavMesh.h"
#include "DStar.h"



class Scene {
public:
    Scene() {};

    ~Scene() {};


    void drawScene(NavMesh *navMesh, DStar *dstar, Wall* objetos, Agente * agente, int nWall);
    void drawObstacles(NavMesh *navMesh,Wall* objetos, int nWall);
    void drawAgent(Agente *agente);
    void drawMeshes(NavMesh *navMesh, int nWall);
    void drawGraph(DStar *dStar);
    void drawPath(DStar *dStar);
    void drawPathDStar(DStar *dstar);
    void drawPathAtual(Agente *agente);



};


#endif //UNTITLED_SCENE_H
