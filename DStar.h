//
// Created by nao on 21/11/18.
//

#ifndef NAVIGATION_MESH_DSTAR_H
#define NAVIGATION_MESH_DSTAR_H

#include "NavMesh.h"
#include <list>


class Node{
public:
    float g, h, f;
 //   char estado; ///-1 = nó fechado, 0 = nó não explorado, 1 = nó aberto
    int id;
    Map pontos;

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

    Agente pessoa;

    std::vector<std::vector <Node>> listaAdj;
    std::vector<std::vector <Node>> cameFrom;

    std::vector<Node> mapPath[QUANTIDADE_CELULA*QUANTIDADE_CELULA];

   // Node mapPath[QUANTIDADE_CELULA*QUANTIDADE_CELULA];


    DStar(NavMesh *nav, int tamanho, Agente *agente);
    ~DStar() {};

    void ligaTodosNos();

    std::vector<Node> reconstructPath(std::vector<Node> mathPath[], Node current);
    float calculaDistancia(Map atual, Map destino);
    Node menorFScore(std::vector<Node> open);

    std::vector<Node> AStar();
    std::vector<Node> expand(Node current);
    std::vector<Node> nosVizinhos(Node n, int tipo,  int tamanho);
    void imprime();
    void imprimiPath();

};


#endif //NAVIGATION_MESH_DSTAR_H
