//
// Created by carol on 11/17/18.
//
#include <GL/glut.h>
#include "Scene.h"

void Scene::drawAgent(Agente *agente) {
    glPointSize((GLfloat)10.0f);
    glColor3f(1.0,0.5,0.5);
    glBegin(GL_POINTS);
        glVertex2f(agente->atual.x, agente->atual.y);
    glEnd();


}

void Scene::drawScene(Agente * agente, int nWall, Wall *obstacles ) {
    this->drawAgent(agente);
    this->drawoBbstacles(nWall, obstacles);



}

void Scene::drawoBbstacles(int nWall, Wall *obstacles){
    glColor3f (0.0, 0.0, 0.0);
    glLineWidth((GLfloat)3.5);
    for (int i = 0; i < nWall; i++) {
        glBegin(GL_QUADS);
        glVertex2f (obstacles[i].atual.x, obstacles[i].atual.y);
        glVertex2f (obstacles[i].atual.x + obstacles[i].width, obstacles[i].atual.y);
        glVertex2f (obstacles[i].atual.x + obstacles[i].width, obstacles[i].atual.y + obstacles[i].height);
        glVertex2f (obstacles[i].atual.x , obstacles[i].atual.y + obstacles[i].height);
        glEnd();
    }
}

Scene::Scene() {

}

Scene::~Scene() {

}
