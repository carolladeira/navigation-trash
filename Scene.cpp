//
// Created by carol on 11/17/18.
//
#include <GL/glut.h>
#include <iostream>
#include "Scene.h"

#include <fstream>
//#define DEBUG

using namespace std;

void Scene::drawScene(NavMesh *navMesh, DStar *dstar,Wall* objetos, Agente * agente, int nWall ) {
  //  this->drawGraph(dstar);
    this->drawAgent(agente);
    this->drawObstacles(navMesh,objetos, nWall);
    this->drawMeshes(navMesh, nWall);
    this->drawPath(dstar);
    this->drawPathDStar(dstar);
    this->drawPathAtual(agente);


}

void Scene::drawPathAtual(Agente *agente){
    glPointSize((GLfloat)5.0f);
    glColor3f(1.0,0.0,0.0); //red
    glBegin(GL_POINTS);
        glVertex2f(agente->atual.x, agente->atual.y);
    glEnd();
#ifdef DEBUG
    std::cout <<agente->atual.x << ","<<agente->atual.y<< " --- ";
#endif
}
///desenha agente
void Scene::drawAgent(Agente *agente) {
    glPointSize((GLfloat)10.0f);
    glColor3f(0.0,0.0,1.0); //blue
    glBegin(GL_POINTS);
        glVertex2f(agente->start.x, agente->start.y);
    glEnd();

    glColor3f(0.0,1.0,0.0); // green
    glBegin(GL_POINTS);
        glVertex2f(agente->end.x, agente->end.y);
    glEnd();

    glColor3f(0.0,1.0,1.0); // green
    glBegin(GL_POINTS);
    glVertex2f(agente->teste.x, agente->teste.y);
    glEnd();



}

///desenha obstaculos
void Scene::drawObstacles(NavMesh *navMesh, Wall* objetos, int nWall){
    glColor3f (0.0, 0.0, 0.0);
    glLineWidth((GLfloat)3.5);
    for(int i=0; i <nWall; i++){
        glBegin(GL_QUADS);
        glVertex2f(objetos[i].pontos[0].x, objetos[i].pontos[0].y);
        glVertex2f(objetos[i].pontos[1].x,objetos[i].pontos[1].y);
        glVertex2f(objetos[i].pontos[2].x, objetos[i].pontos[2].y);
        glVertex2f(objetos[i].pontos[3].x, objetos[i].pontos[3].y);
        glEnd();
    }

////#ifdef DEBUG
////    std::cout<<"------------------------------------" <<std::endl;
////    std::cout<<"Numero de obstacuclos: " <<nWall<< std::endl;
////#endif
//    for (int i = 0; i < nWall; i++) {
//        glBegin(GL_QUADS);
//            glBegin(GL_QUADS);
//            glVertex2f(navMesh->objects[i].pontos[0].x, navMesh->objects[i].pontos[0].y);
//            glVertex2f(navMesh->objects[i].pontos[1].x, navMesh->objects[i].pontos[1].y);
//            glVertex2f(navMesh->objects[i].pontos[2].x, navMesh->objects[i].pontos[2].y);
//            glVertex2f(navMesh->objects[i].pontos[3].x, navMesh->objects[i].pontos[3].y);
//            glEnd();
////
////#ifdef DEBUG
////        std::cout <<navMesh->objects[i].pontos[0].x << ","<<navMesh->objects[i].pontos[0].y<< " --- ";
////        std::cout <<navMesh->objects[i].pontos[1].x << ","<<navMesh->objects[i].pontos[1].y<< " --- ";
////        std::cout <<navMesh->objects[i].pontos[2].x << ","<<navMesh->objects[i].pontos[2].y<< " --- ";
////        std::cout <<navMesh->objects[i].pontos[3].x << ","<<navMesh->objects[i].pontos[3].y<<std::endl;
////#endif
//        glEnd();
//
//    }
}

void Scene::drawMeshes(NavMesh *navMesh, int nWall) {
    int x,y;
    glLineWidth((GLfloat)1.0);
    for (int i=0; i<50; i++){
        x=i*10;
        for(int j=0; j<50; j++){

            y=j*10;
            if(navMesh->_meshes[i][j]==1){
                glColor3f (1.0, 0.0, 0.0);
                glBegin(GL_LINE_LOOP);
                glVertex2f (x, y);
                glVertex2f (x +10, y);
                glVertex2f (x+10, y+10);
                glVertex2f (x,y+10 );
                glEnd();
            }//else  glColor3f (0.2, 0.5, 0.0);



        }
    }

}

void Scene::drawGraph(DStar *dStar) {
    int m=0;

    glLineWidth((GLfloat)1.0);
    glColor3f (0.0, 0.0, 1.0);
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
          //  std::cout <<  (i * 10) + 5 << ","<<  (j * 10) + 5 << std::endl;

            for(int t=0; t<dStar->listaAdj[m].size(); t++){
                glBegin(GL_LINES);
                glVertex2f ((i * 10) + 5, (j * 10) + 5);

                glVertex2f (dStar->listaAdj[m][t].pontos.x, dStar->listaAdj[m][t].pontos.y);
              //  std::cout <<  dStar->listaAdj[m][t].pontos.x << ","<<  dStar->listaAdj[m][t].pontos.y << " - ";

                glEnd();
            }
          //  std::cout<< ""<< std::endl;

            m++;
        }
    }
}

void Scene::drawPath(DStar *dStar) {

    glPointSize((GLfloat)5.0f);
    glLineWidth((GLfloat)2.0);

    glColor3f (1.0, 0.0, 0.0);
    glBegin(GL_LINE_STRIP);

    for(int j=0; j<dStar->totalPath.size(); j++){
        glVertex2f (dStar->totalPath[j].pontos.x, dStar->totalPath[j].pontos.y);
//        #ifdef DEBUG
//           std::cout <<  dStar->totalPath[j].id << std::endl;
//           std::cout <<  dStar->totalPath[j].pontos.x << ","<<  dStar->totalPath[j].pontos.y << std::endl;
//        #endif

    }
    glEnd();
    glColor3f (0.2, 0.0, 1.0);

    for(int j=0; j<dStar->totalPath.size(); j++){

        glBegin(GL_POINTS);
        glVertex2f (dStar->totalPath[j].pontos.x, dStar->totalPath[j].pontos.y);
        glEnd();
    }
}
void Scene::drawPathDStar(DStar *dstar)
{

    glLineWidth((GLfloat)2.0);
#ifdef DEBUG
    std::cout<<std::endl;
    std::cout<<"--------------Draw path D Star Lite-----------------------" <<std::endl;
#endif

    glColor3f (0.2, 1.0, 1.0);
    glBegin(GL_LINE_STRIP);

    for(int j=0; j<dstar->closed.size(); j++){
        glVertex2f (dstar->closed[j].pontos.x, dstar->closed[j].pontos.y);
        #ifdef DEBUG
            std::cout<<dstar->closed[j].id<<" " ;
        #endif
    }
#ifdef DEBUG
    std::cout<<std::endl;
#endif
    glEnd();
}
