//
// Created by nao on 21/11/18.
//

#include "DStar.h"
#include <iostream>
#include <algorithm>    // std::find


Node::Node() {
//    this->g = 0;
//    this->h = 0;
//    this->f = 0;
//    this->estado = 0;

}

Node::~Node() {

}

DStar::DStar(NavMesh *nav, int tamanho, Agente *agente) {
    int m = 0;

    std::vector<Node> temp;

    int j = 0;
    for (int i = 0; i < 49; i++) {
        for (int j = 0; j < tamanho; j++) {

            Node nox;
            nox.pontos.x = (i * 10) + 5;
            nox.pontos.y = (j * 10) + 5;
            nox.id = m;
            if (nox.pontos.x == agente->start.x && nox.pontos.y == agente->start.y) {
                pessoa.start.id = m;
            }
            if (nox.pontos.x == agente->end.x && nox.pontos.y == agente->end.y) {
                pessoa.end.id = m;
            }

            temp.push_back(nox);
            nox.pontos.x = ((i + 1) * 10) + 5;
            nox.pontos.y = ((i + 1) * 10) + 5;
            nox.id = m + 51;

            temp.push_back(nox);

            listaAdj.push_back(temp);
            temp.pop_back();
            temp.pop_back();
            m++;
        }
    }
    imprime();
}
void DStar::imprime(){
    for (int i=0; i<listaAdj.size(); i++){

        for(int j=0; j<listaAdj[i].size(); j++){
            std::cout << ' ' << listaAdj[i][j].id;
        }
        std::cout  << " " << std::endl;

    }
}

void DStar::ligaTodosNos() {

/*    while(!listaAdj.end()) {
        Node novo = listaAd;
        ///coluna da esquerda
        if(no[i].x == 5){
            ///baixo
            if(no[y].y == 5){

             //cima
            }else if(no.y == 45){

            }else{
                listaAdj[i].push_back(No)

            }

        }
    }*/

}

/*std::vector<Node> DStar::nosVizinhos(Node n, int tipo){

    std::vector<Node> vizinhos;
    if(tipo == 1)//Nos da esquerda
    {
        if(n.y == 5)//de baixo
        {
            Node novo;
            novo.x = n.x +10;
            novo.y = n.y;
            vizinhos.push_back(novo);

        }else if(n.y== 45)// de cima
        {

        }
    }else if (tipo == 2) //Nos de baixo
    {
        if(n.x == 5)//direita
        {

        }else if(n.x== 45)// esquerda
        {

        }

    }else if (tipo == 3) //Nos de cima
    {
        if(n.x == 5)//direita
        {

        }else if(n.x== 45)// esquerda
        {

        }

    }else if (tipo == 4) //Nos da direita
    {
        if(n.y == 5)//de baixo
        {

        }else if(n.y== 45)// de cima
        {

        }
    }


}*/

DStar::~DStar() {
}

//entrada: start, goal
std::vector<Node> DStar::AStar() {
    Node node;
    node.g = 0;
    node.pontos = pessoa.start;
    node.id = pessoa.start.id;
    node.f = calculaDistancia(pessoa.start, pessoa.end);
    open.push_back(node);

    std::vector<Node> vizinhos;

    float g;
    Node current;
    while (!open.empty()) {

        current = menorFScore(open);
        if (current.pontos.x == pessoa.end.x && current.pontos.y == pessoa.end.y) {
            ///encontrou caminho
            return reconstructPath(cameFrom, current);
        }


        open.erase(open.begin()); //remove de open
        closed.push_back(current); //adiciona em closed

        vizinhos = expand(current); //descobrir o sucessor e gerar os pais dele de bestNode

        for (int i = 0; i < vizinhos.size(); i++) ///para cada vizinho do atual
        {

            /// Ignore the neighbor which is already evaluated.
            if (std::find(closed.begin(), closed.end(), vizinhos[i]) != closed.end()) {
                continue;
            }

            g = current.g + calculaDistancia(current.pontos, vizinhos[i].pontos);


            if (std::find(closed.begin(), closed.end(), vizinhos[i]) != closed.end()) {
            } else {
                open.push_back(vizinhos[i]);
            }
            if (g >= vizinhos[i].g) {
                continue;
            }

            cameFrom.push_back(current);
            vizinhos[i].g = g;
            vizinhos[i].h = calculaDistancia(vizinhos[i].pontos, pessoa.end);
            vizinhos[i].f = vizinhos[i].g + vizinhos[i].h;


        }
    }
}

std::vector<Node> DStar::reconstructPath(std::vector<Node> cameFrom, Node current) {
    std::vector<Node> totalPath;
    totalPath.push_back(current);
    for (int i = 0; i < cameFrom.size(); i++) {
        current = cameFrom[i];
        totalPath.push_back(current);
    }
    return totalPath;
}

float DStar::calculaDistancia(Map atual, Map destino) {

    float dx, dy;
    dx = atual.x - destino.x;
    dy = atual.y - destino.y;

    float dist = sqrt(dx * dx + dy * dy);

    return dist;

}

Node DStar::menorFScore(std::vector<Node> open) {

    //  std::sort (open.begin(), open.end(), compara());
    sort(open.begin(), open.end(), [](const auto &lhs, const auto &rhs) {
        return lhs.f < rhs.f;
    });
    for (std::vector<Node>::iterator it = open.begin(); it != open.end(); ++it)
     //   std::cout << ' ' << it->id;
  //  std::cout << '\n';

    return open[0];

}

std::vector<Node> DStar::expand(Node current) {
    int id = current.id;

    std::vector<Node> temp;
    temp = listaAdj[id];
    return temp;
}

