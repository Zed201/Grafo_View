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
        void addVertex(std::string n1);
        void Generate();
    public:
        GrafoMatriz();
        ~GrafoMatriz();

        void Add(std::string nodo, std::initializer_list<std::pair<std::string, std::optional<int>>> pares);
        void remove(std::string nodo);
        std::string print(bool png = false);
        std::string TranverseDFS(std::string inicio, bool png = false);
        std::string TranverseBFS(std::string inicio, bool png = false);


};

