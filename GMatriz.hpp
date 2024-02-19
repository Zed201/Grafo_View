#pragma once
// requesitos para funcionar
#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <optional>
#include <fstream>
#include <deque>

class GrafoMatriz{
    private:
        int qtdNodo;
        std::vector<std::string> nodos;
        int **graph, **ret, tmpi;
        bool *mark;
        bool png;
        int first(int v);
        int next(int v, int w);
        std::string print(int **printable);
        void BFS(int start);
        void DFS(int nodoIndex);
        void save();
        void setMark();
        int Str_Int(std::string nodo);
        std::string Int_Str(int nodo_index);
        bool isIn(std::string nodo, std::vector<std::string> vec);
    public:
        GrafoMatriz();
        ~GrafoMatriz();

        void Add(std::string nodo1, int peso, std::string nodo2);
        void remove(std::string nodo);
        std::string print();
        std::string TranverseDFS(std::string inicio, bool png = false);
        std::string TranverseBFS(std::string inicio, bool png = false);
        // ajudar  no lib de python
        void addVertex(std::string n1);
        void Generate();
};

