#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <utility>
#include <optional>
#include <stack>
#include <queue>
#include <fstream>

using namespace std;

// Grafo usando Matriz
class GrafoMatriz{
        private:
                int qtdNodo = 0;
                vector<string> nodos;
                // a logica e de i -> j, linhas para colunas
                int **graph = nullptr;
                // usado para ter os restornos em fromato de matriz das buscas
                int **ret = nullptr;
                bool *mark =  nullptr;

        public:
                // grafo iniciado com matriz completa
                GrafoMatriz(initializer_list<string> nodos){ 

                        for(string i : nodos){
                                this->nodos.push_back(i);
                                this->qtdNodo++;
                        }
                        this->graph = (int **)malloc(this->qtdNodo * sizeof(int *));
                        for(int i = 0; i < this->qtdNodo; i++){
                                this->graph[i] = (int *)malloc( this->qtdNodo * sizeof(int));
                        }
                        for(int i = 0; i < this->qtdNodo; i++){
                                for(int j = 0; j < this->qtdNodo; j++){
                                        this->graph[i][j] = 0;
                                }
                        }

                }
                ~GrafoMatriz(){
                        for(int i = 0; i < this->qtdNodo; i++){
                                free(this->graph[i]);
                        }
                        free(this->graph);
                }

                // sempre vai fazer uma correspondência com o index do vector
                int Str_Int(string nodo){
                        int i = 0;
                        vector<string>::iterator k = this->nodos.begin();
                        while(k != this->nodos.end() && nodo != (*k)){
                                ++i, ++k;
                        }
                        return i;
                }

                string Int_Str(int nodo_index){
                        int i = 0;
                        vector<string>::iterator k = this->nodos.begin();
                        while(k != this->nodos.end() && i != nodo_index){
                                ++i, ++k;
                        }
                        return (*k);
                }

                // fazer funcao para ver se o nodo ta no vetor
                bool isIn(string nodo, vector<string> vec){
                        vector<string>::iterator i = vec.begin();
                        while(i != vec.end()){
                                if(nodo == (*i)){
                                        return true;         
                                } else {
                                        ++i;
                                }
                        }
                        return false;
                }
                // a logica dos direcionamentos e de linha para coluna: i -> j
                void Add(string nodo, initializer_list<pair<string, optional<int>>> pares){
                        // nao verifica se o vertice ta ou nao no grafo
                        int i_nodo = this->Str_Int(nodo);
                        for(pair<string, optional<int>> i : pares){
                                if(i.second.has_value()){
                                        this->graph[i_nodo][this->Str_Int(i.first)] = i.second.value();
                                } else {
                                        this->graph[i_nodo][this->Str_Int(i.first)] = 0;
                                }
                        }
                }

                void remove(string nodo){ // basicamente ele troca todas as posição o nodo a ser eliminado
                                          // com o ultimo, tanto na matriz, quanto no vector
                                          // 
                        int i = this->Str_Int(nodo);
                        swap(this->graph[i], this->graph[this->qtdNodo - 1]);
                        for(int z = 0; z < this->qtdNodo - 1; z++){
                                swap(this->graph[z][i], this->graph[z][this->qtdNodo - 1]);
                        }
                        free(this->graph[this->qtdNodo - 1]);
                        this->graph = (int **)realloc(this->graph, --this->qtdNodo * sizeof(int *));
                        vector<string>::iterator ite = this->nodos.begin();
                        while(ite != this->nodos.end()){
                                if((*ite) == nodo){
                                        string tmp = this->nodos[this->qtdNodo];
                                        this->nodos[i] = tmp;
                                        this->nodos.erase(this->nodos.end());
                                        return;
                                }
                                ++ite;
                        }
                        
                }

                string print(){
                       return  this->print(this->graph, "print_normal");
                }

                // print difernet do original para estar no formato certo
                string  print(int **printable, string f_line){
                        /*printf("   ");
                        for(int i = 0; i < this->qtdNodo; i++){
                                printf("%d ", i);
                        }
                        printf("\n");*/
                        /*for(int i = 0; i <= this->qtdNodo; i++){
                                printf("--");
                        }*/
                        //printf("\n");
                        //int i = 0;
                        string resultado;
                        //printf("%d\n", this->qtdNodo);
                        resultado += f_line + "\n";
                        resultado += to_string(this->qtdNodo) + "\n";
                        vector<string>::iterator l = this->nodos.begin();
                        while(l != this->nodos.end()){
                                //printf("%s\n", (*l).c_str());
                                resultado += (*l) + "\n";
                                ++l;
                        }
                       
                        for(int j = 0; j < this->qtdNodo; j++){
                                //printf("%d| ", j);
                                for(int k = 0; k < this->qtdNodo; k++){
                                        //printf("%d ", printable[j][k]);
                                        resultado += to_string(printable[j][k]) + " ";
                                }
                                //printf("\n");
                                resultado += "\n";
                        }
                        //printf("Vetores:\n");
                        return resultado;
                }
                // inicializa tanto a tabela de mark e o novo grafo em matriz da arvore
                void setMark(){
                        if(this->mark != nullptr){
                                free(this->mark);
                        }
                        if(this->ret != nullptr){
                                for(int i = 0; i < this->qtdNodo; i++){
                                        free(this->ret[i]);
                                }
                                free(this->ret);
                        }

                        this->mark = (bool *)malloc(sizeof(bool) * this->qtdNodo);
                        this->ret = (int **)malloc(sizeof(int *) * this->qtdNodo);

                        for(int i = 0; i < this->qtdNodo; i++){
                                this->mark[i] = false;
                                this->ret[i] = (int *)malloc(sizeof(int) * this->qtdNodo);
                                for(int z = 0; z < this->qtdNodo; z++){
                                        this->ret[i][z] = 0;
                                }
                        }
                }
                int tmpi = 0;
                // usado para imprimri a matriz com certo nome e ja executar ele 
               void save(){
                       string tmp = "Grafo_";
                       tmp += to_string(this->tmpi++);
                       string mtx = this->print(this->ret, tmp);
                       string pafi = "./dados/" + tmp + ".txt";
                       fstream file(pafi, ios::out);
                       file << mtx;
                       file.close();
                       string comando = "python3 index.py " + tmp;
                       system(comando.c_str());
               }

                // ver o retorno, para ser aluma coisa de ponteiro, como uma matriz resultado da busca
                // TODO: ponto de partida personalizado
                string TranverseDFS(){
                    this->setMark();
                    for(int i = 0; i < this->qtdNodo; i++){
                        if(mark[i] == false){
                            this->DFS(i);
                        }
                    }
                    //printf("Resultado do DFS\n");
                    return this->print(this->ret, "DFS");
                }

                void DFS(int nodoIndex){
                    // preVisit
                    this->mark[nodoIndex] = true;
                    // TODO: DEBUG
                    //cout << this->Int_Str(nodoIndex) << endl; // para dizer os nodos passados
                    int w = this->first(nodoIndex);
                    while (w < this->qtdNodo)
                    {
                        if(this->mark[w] == false){
                            // provavelmente fazer algo por aque
                            // vai de nodoIndex para w, do pai para o filho
                            this->ret[nodoIndex][w] = this->graph[nodoIndex][w];
                            this->save();
                            this->DFS(w);
                        }
                        w = this->next(nodoIndex, w);
                    }
                    // posVisit
                }

                int first(int v){
                    for(int i = 0; i < this->qtdNodo; i++){
                        if(this->graph[v][i] != 0){
                            return i;
                        }
                    }
                    return this->qtdNodo;
                }

                int next(int v, int w){
                    for(int i = w + 1; i < this->qtdNodo; i++){
                        if(this->graph[v][i] != 0){
                            return i;
                        }
                    }
                    return this->qtdNodo;
                }

                string TranverseBFS(){
                        this->setMark();
                        for(int i = 0; i < this->qtdNodo; i++){
                                // TODO: Trocar as verificacoes por !
                                if(this->mark[i] == false){
                                        this->BFS(i);
                                }
                        }
                       // printf("Matriz de retorno de BFS\n");
                        return this->print(this->ret, "BFS");
                }
                
                void BFS(int start){
                        deque<int> q;
                        //cout << ini << endl;
                        q.push_back(start);
                        this->mark[start] = true;
                        while (q.size() > 0){
                                int v = q.front();
                                // o pop nao retorna nada
                                q.pop_front();
                                // pre visit
                                int w = this->first(v);
                                // TODO: DEBUG
                                //cout << "Analisar lig do " << this->Int_Str(v) << endl;
                                while( w < this->qtdNodo){
                                        if(this->mark[w] == false){
                                                this->mark[w] = true;
                                                //cout << this->Int_Str(w) << endl;
                                                // o caminho vai de v para w, pois v e tirado da fila e w surge a parit de v
                                                this->ret[v][w] = this->graph[v][w];
                                                this->save();
                                                q.push_back(w);
                                        }
                                        w = this->next(v, w);
                                }
                                // pos visit       
                        }
                }
};
