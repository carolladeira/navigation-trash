//
// Created by carol on 11/17/18.
//

#ifndef UNTITLED_NAVMESH_H
#define UNTITLED_NAVMESH_H
#include <math.h>
#include <time.h>
#include <stdlib.h>     /* srand, rand */
#include <vector>
#include <bits/stdc++.h>


#define MIN_LARGURA_PAREDE 7
#define MAX_LARGURA_PAREDE 20
#define LARGURA_MESH_COVER 5
#define QUANTIDADE_CELULA 50
#define TAMANHO_CELULA 10





class Map{
public:
    float x;
    float y;
    int id;



};

class Polygon{
public:
    Map pontos[4];
    float dimx;
    float dimy;

};


class Agente {
public:
    Map start;
    Map end;
    Map atual;


    Agente();

};

class Wall: public Polygon{
public:
    Map atual;
    float height;
    float width;
    float ang;

   // void geraPosicaoInicial(float tam_cenario, int num_paredes);

};
class Mesh:public Polygon{
public:
    int tipo;
    int parede_pertence;

   // Mesh() {};
    Mesh(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, int t, int parede_pai);

    ~Mesh() {};

};
class Cell{
public:
    float g;
    float rhs;
    float cost;
};
class NavMesh {
public:
    std::vector<Mesh*> meshes;
    Wall *obstacles;
    Wall *objects;

    int nObstacles;
    int _meshes[QUANTIDADE_CELULA][QUANTIDADE_CELULA];
    Cell cells[QUANTIDADE_CELULA][QUANTIDADE_CELULA];

    int tamanho;

    void atualizaObstacles(Wall *obstacles, int size);
    void criaNavMesh(Wall *obstacles);
    void Cria_Mesh_Cobertura ();
  //  void Cria_NavMesh ();
    void criaGrid(Wall *obstacles, float tam_cenario);
    void criaObjetos(int num_paredes, int tam_cenario);
    void atualizaPosicao();

    NavMesh(int tam_cenario);
    virtual ~NavMesh(){};

};


#endif //UNTITLED_NAVMESH_H
