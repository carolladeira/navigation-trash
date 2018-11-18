//
// Created by carol on 11/17/18.
//

#ifndef UNTITLED_NAVMESH_H
#define UNTITLED_NAVMESH_H
#include <math.h>
#include <time.h>
#include <stdlib.h>     /* srand, rand */


#define MIN_LARGURA_PAREDE 7
#define MAX_LARGURA_PAREDE 20



class Map{
public:
    float x;
    float y;


};


class Agente {
public:
    Map start;
    Map end;
    Map atual;


    Agente() { this->atual.x =5.5; this->atual.y =222.5;}

};
//A-> x, y
//B-> x + width, y
//D-> x + width, y + height
//C-> x, y + height

class Wall{
public:
    Map atual;
    float height;
    float width;
    float ang;

    void geraPosicaoInicial(float tam_cenario, int num_paredes);

};

class NavMesh {

};


#endif //UNTITLED_NAVMESH_H
