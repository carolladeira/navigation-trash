//
// Created by nao on 21/11/18.
//

#ifndef NAVIGATION_MESH_DSTAR_H
#define NAVIGATION_MESH_DSTAR_H

#include "NavMesh.h"
#include <list>

class Pair{
public:
    float first, second;
};

class Node{
public:
    int id;
    bool ocupado;
    float g, h, f, rhs;
    Pair key;
    Map pontos;
    int estado;
    //   char estado; ///-1 = nó fechado, 0 = nó não explorado, 1 = nó aberto


    Node();
    ~Node();
    bool operator==(const Node &rhs) const {
        return rhs.id == id;
    }
};

//struct myclass {
//    bool operator( ) (Node i,Node j) { return (i.f<j.f);}
//} myobject;
class DStar {
public:
    std::vector<Node> totalPath ; //path;
    std::vector <Node> open; //node is currently open
    std::vector <Node> closed; //node is no longer open
    std::vector <Node> obstacles; //node is no longer open

    Node s_start, s_end;
  //  Agente pessoa;

    Node custo[QUANTIDADE_CELULA*QUANTIDADE_CELULA];

    std::vector<std::vector <Node>> listaAdj;
    //std::vector<std::vector <Node>> cameFrom;

    std::vector<Node> mapPath[QUANTIDADE_CELULA*QUANTIDADE_CELULA];

    DStar(NavMesh *nav, int tamanho, Agente *agente);
    ~DStar() {};

    //void ligaTodosNos();
    std::vector<Node> nosVizinhos(Node n, int tipo,  int tamanho);
    void imprime();


    ///A Star
    std::vector<Node> AStar();
    std::vector<Node> expand(Node current);
    std::vector<Node> reconstructPath(std::vector<Node> mathPath[], Node current);
    float calculaDistancia(Node atual, Node destino);
    Node menorFScore(std::vector<Node> open);
    void imprimiPath();

    ///D Star Lite
    void DStarLite();
    void updateVertex(Node u, float km);
    Pair calculateKey(Node s, float km);
    int findI(Node u);
    Node min_succ(Node u);
    void computeShortestPath(float km);
    Node ordena(std::vector<Node> open);
    bool compara(Pair u, Pair s);

    float getG(Node u);
    float getRhs(Node u);

    void updateCell(int x, int y, float val);



    };


#endif //NAVIGATION_MESH_DSTAR_H
