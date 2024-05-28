#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <optional>
#include <fstream>
#include <deque>
#include <algorithm>

// requesitos para funcionar
class GrafoMatriz{
        private:
                // Qtd total de nodos
                int qtdNodo;
                // Os nomes de cada um e os estados salvos do ret
                std::vector<std::string> nodos;
                // Os auxiliares para guardar a matriz
                int tmpi, **graph, **ret;
                bool *mark;
                // Axuliares
                int first(int v);
                int next(int v, int w);
                std::string print(int **printable);
                // Auxiliares internos
                void BFS(int start);
                void DFS(int nodoIndex);
                // remover
                void save();
                // auxiliar para setar os auxiliares de matriz
                void setMark();
                // Serve para verificar correspondencia entre nome e index na matriz do vertice
                int Str_Int(std::string nodo);
                std::string Int_Str(int nodo_index);
                // se o vertice ta ou nao no grafo
        public:
                GrafoMatriz();
                GrafoMatriz(std::initializer_list<std::string> nodos);
                ~GrafoMatriz();
                // Add caminho
                void Add(std::string nodo1, int peso, std::string nodo2);
                void Add(std::string nodo, std::initializer_list<std::pair<std::string, std::optional<int>>> pares);
                // talvez remover
                void remove(std::string nodo);
                std::string print();
                std::vector<std::string> save_state;
                // std::vector<std::string> getState();
               
                std::string Ordem();
                // Verdadeiro tranverse
                std::string TranverseDFS(std::string inicio);
                std::string TranverseBFS(std::string inicio);
                // ajudar  no lib de python
                void addVertex(std::string n1);
                int isIn(std::string nodo, std::vector<std::string> vec);
                int isIn(std::string nodo);
                void Generate();
                int nodos_qtd();

};

