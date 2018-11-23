//
// Created by carol on 11/17/18.
//
#include <GL/glut.h>
#include <iostream>
#include "Scene.h"

#include <fstream>

using namespace std;

void Scene::drawAgent(Agente *agente) {
    glPointSize((GLfloat)10.0f);
    glColor3f(1.0,0.0,1.0);
    glBegin(GL_POINTS);
        glVertex2f(agente->start.x, agente->start.y);
    glEnd();
    glColor3f(0.0,1.0,0.0);
    glBegin(GL_POINTS);
    glVertex2f(agente->end.x, agente->end.y);
    glEnd();



}

void Scene::drawScene(NavMesh *navMesh, DStar *dstar, Agente * agente, int nWall ) {
    this->drawAgent(agente);
    this->drawObstacles(navMesh, nWall);
    this->drawGraph(dstar);
    this->drawPath(dstar);





}

void Scene::drawObstacles(NavMesh *navMesh, int nWall){
    glColor3f (0.0, 0.0, 0.0);
    glLineWidth((GLfloat)3.5);
    for (int i = 0; i < nWall; i++) {
        glBegin(GL_QUADS);
            glBegin(GL_QUADS);
            glVertex2f(navMesh->objects[i].pontos[0].x, navMesh->objects[i].pontos[0].y);
            glVertex2f(navMesh->objects[i].pontos[1].x, navMesh->objects[i].pontos[1].y);
            glVertex2f(navMesh->objects[i].pontos[2].x, navMesh->objects[i].pontos[2].y);
            glVertex2f(navMesh->objects[i].pontos[3].x, navMesh->objects[i].pontos[3].y);
            glEnd();
        glEnd();


    }
}

Scene::Scene() {

}

Scene::~Scene() {

}


void Scene::drawMeshes(NavMesh *navMesh, int nWall) {
    int x,y;
    glLineWidth((GLfloat)2.0);
   // glColor3f (0.5, 0.5, 1.0);
    for (int i = 0; i < navMesh->meshes.size(); i++) {
        if (navMesh->meshes[i]->tipo == 0)
            glColor3f (0.0, 0.0, 1.0);
        else if (navMesh->meshes[i]->tipo == 1)
            glColor3f (0.0, 1.0, 0.0);
        else if (navMesh->meshes[i]->tipo == 2)
            glColor3f (1.0, 0.0, 0.0);
        else if (navMesh->meshes[i]->tipo == 4)
            glColor3f (0.8, 1.0, 0.5);
        else
            glColor3f (0.0, 1.0, 1.0);
        if (navMesh->meshes[i]->pontos[3].x != -1) {
//            glBegin(GL_LINE_LOOP);
//           // glBegin(GL_QUADS);
//            glVertex2f (navMesh->meshes[i]->pontos[0].x, navMesh->meshes[i]->pontos[0].y);
//            glVertex2f (navMesh->meshes[i]->pontos[1].x, navMesh->meshes[i]->pontos[1].y);
//            glVertex2f (navMesh->meshes[i]->pontos[2].x, navMesh->meshes[i]->pontos[2].y);
//            glVertex2f (navMesh->meshes[i]->pontos[3].x, navMesh->meshes[i]->pontos[3].y);
//            glEnd();
            glColor3f (0.0, 1.0, 1.0);
        }

    }


    glLineWidth((GLfloat)1.0);
    for (int i=0; i<50; i++){
        x=i*10;
        for(int j=0; j<50; j++){

            y=j*10;
            if(navMesh->_meshes[i][j]==1){
                glColor3f (0.0, 0.0, 1.0);
            }else  glColor3f (0.2, 0.5, 0.0);

            glBegin(GL_LINE_LOOP);
            glVertex2f (x, y);
            glVertex2f (x +10, y);
            glVertex2f (x+10, y+10);
            glVertex2f (x,y+10 );
            glEnd();

        }
    }

}

void Scene::drawGraph(DStar *dStar) {

    glLineWidth((GLfloat)1.0);
    glColor3f (0.0, 0.0, 1.0);
    for (int i=0; i<dStar->listaAdj.size(); i++){

        for(int j=0; j<dStar->listaAdj[i].size(); j++){
            glBegin(GL_LINE_LOOP);
//            glVertex2f (x, y);
//            glVertex2f (x +10, y);
//            glVertex2f (x+10, y+10);
//            glVertex2f (x,y+10 );
            glEnd();

        }
    }
//    glPointSize((GLfloat)5.0f);
//    glColor3f (0.2, 0.0, 0.0);
//        for(int j=0; j<2500; j++){
//
//            glBegin(GL_POINTS);
//            glVertex2f (dStar->no[j].x, dStar->no[j].y);
//            glEnd();
//
//        }

}

void Scene::drawPath(DStar *dStar) {

   // glPointSize((GLfloat)5.0f);
    glLineWidth((GLfloat)2.0);

    glColor3f (0.2, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);

    for(int j=0; j<dStar->cameFrom.size(); j++){

       // glBegin(GL_POINTS);

        glVertex2f (dStar->cameFrom[j].pontos.x, dStar->cameFrom[j].pontos.y);

       // std::cout <<  dStar->cameFrom[j].pontos.x << ","<<  dStar->cameFrom[j].pontos.y << std::endl;

    }
    glEnd();

    glPointSize((GLfloat)5.0f);

    glColor3f (0.2, 0.0, 1.0);

    for(int j=0; j<dStar->cameFrom.size(); j++){

        glBegin(GL_POINTS);
        glVertex2f (dStar->cameFrom[j].pontos.x, dStar->cameFrom[j].pontos.y);
        glEnd();

    }



}
