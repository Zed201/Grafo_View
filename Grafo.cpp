#include "./GMatriz.hpp"
using namespace std;
#include <Python.h>

GrafoMatriz::GrafoMatriz() : qtdNodo(0), tmpi(0), png(false), graph(nullptr), ret(nullptr), mark(nullptr){
        // decomposto nas duas outras funcs para ajudar no porte para python
        /*for(std::string i : nodos){
          this->nodos.push_back(i);
          this->qtdNodo++;
          }
          this->graph = (int **) malloc(this->qtdNodo * sizeof(int *));
          for(int i = 0; i < this->qtdNodo; i++){
          this->graph[i] = (int *) malloc(sizeof(int) * this->qtdNodo);
          for(int j = 0; j < this->qtdNodo; j++){
          this->graph[i][j] = 0;
          }
          }*/
}

// adiciona o vertice, decompondo a função de init
void GrafoMatriz::addVertex(std::string n1){
        this->qtdNodo++;
        this->nodos.push_back(n1);
        //cout << n1 << " criado" << endl;
}

void GrafoMatriz::Generate(){
        //cout << this->qtdNodo << " nodos total" << endl;
        this->graph = (int **) malloc(this->qtdNodo * sizeof(int *));
        for(int i = 0; i < this->qtdNodo; i++){
                this->graph[i] = (int *) malloc(sizeof(int) * this->qtdNodo);
                for(int j = 0; j < this->qtdNodo; j++){
                        this->graph[i][j] = 0;
                }
        }
        //cout << "maloc finalizado" << endl;
}

GrafoMatriz::~GrafoMatriz(){
        if(this->graph != nullptr){
                for (int i = 0; i < this->qtdNodo; i++)
                {
                        free(this->graph[i]);
                }
                free(this->graph);
        }
        if (this->mark != nullptr)
        {
                free(this->mark);
        }
        if (this->ret != nullptr)
        {
                for (int i = 0; i < this->qtdNodo; i++)
                {
                        if(this->ret[i] != nullptr){
                                free(this->ret[i]);
                        }
                }
                free(this->ret);
        }

}

int GrafoMatriz::Str_Int(std::string nodo){
        int i = 0;
        std::vector<std::string>::iterator k = this->nodos.begin();
        while ((*k) != nodo && k != this->nodos.end())
        {
                ++i, ++k;
        }
        return i;
}

std::string GrafoMatriz::Int_Str(int nodo_index){
        int i = 0;
        std::vector<std::string>::iterator k = this->nodos.begin();
        while (k != this->nodos.end() && i != nodo_index)
        {
                ++i, ++k;
        }
        return (*k);
}

bool GrafoMatriz::isIn(std::string nodo, std::vector<std::string> vec){
        std::vector<std::string>::iterator i = vec.begin();
        while (i != vec.end())
        {
                if (nodo == (*i))
                {
                        return true;
                }
                ++i;
        }
        return false;
}

// nodo1--[peso]=->nodo2
void GrafoMatriz::Add(std::string nodo1, int peso, std::string nodo2){
        //printf("foi 2\n");
        int n1 = this->Str_Int(nodo1), n2 = this->Str_Int(nodo2);
        this->graph[n1][n2] = peso;

        /*for (std::pair<std::string, std::optional<int>> i : pares)
        {
                if (i.second.has_value())
                {
                        this->graph[i_nodo][this->Str_Int(i.first)] = i.second.value();
                }
                else
                {
                        this->graph[i_nodo][this->Str_Int(i.first)] = 0;
                }
        }*/
}
void GrafoMatriz::remove(std::string nodo){
        int i = this->Str_Int(nodo);
        std::swap(this->graph[i], this->graph[this->qtdNodo - 1]);
        for (int z = 0; z < this->qtdNodo - 1; z++)
        {
                std::swap(this->graph[z][i], this->graph[z][this->qtdNodo - 1]);
        }
        free(this->graph[this->qtdNodo - 1]);
        this->graph = (int **)realloc(this->graph, --this->qtdNodo * sizeof(int *));
        std::vector<std::string>::iterator ite = this->nodos.begin();
        while (ite != this->nodos.end())
        {
                if ((*ite) == nodo)
                {
                        std::string tmp = this->nodos[this->qtdNodo];
                        this->nodos[i] = tmp;
                        this->nodos.erase(this->nodos.end());
                        return;
                }
                ++ite;
        }
}
std::string GrafoMatriz::print(bool png){
        this->png = false;
        // desativao no momento ate fazer a integracao
        return this->print(this->graph);
        /*std::fstream file("./Matriz.txt", std::ios::out);
        file << tmp;
        file.close();
        //std::string comando = "python3 index.py Matriz Grafo_print";
        std::cout << comando << std::endl;
        system(comando.c_str());*/
}

std::string GrafoMatriz::print(int **printable){
        std::string resultado;
        resultado += std::to_string(this->qtdNodo) + "\n";
        std::vector<std::string>::iterator l = this->nodos.begin();
        while (l != this->nodos.end())
        {
                resultado += (*l) + "\n";
                ++l;
        }

        for (int j = 0; j < this->qtdNodo; j++)
        {
                for (int k = 0; k < this->qtdNodo; k++)
                {
                        resultado += std::to_string(printable[j][k]) + " ";
                }
                resultado += "\n";
        }
        return resultado;
}

void GrafoMatriz::setMark(){
        if (this->mark != nullptr)
        {
                free(this->mark);
        }
        if (this->ret != nullptr)
        {
                for (int i = 0; i < this->qtdNodo; i++)
                {
                        free(this->ret[i]);
                }
                free(this->ret);
        }

        this->mark = (bool *)malloc(sizeof(bool) * this->qtdNodo);
        this->ret = (int **)malloc(sizeof(int *) * this->qtdNodo);

        for (int i = 0; i < this->qtdNodo; i++)
        {
                this->mark[i] = false;
                this->ret[i] = (int *)malloc(sizeof(int) * this->qtdNodo);
                for (int z = 0; z < this->qtdNodo; z++)
                {
                        this->ret[i][z] = 0;
                }
        }
}

void GrafoMatriz::save(){
        // ! Desativado por hora, ate implementar todo o resultado
        /* 
        std::string mtx = this->print(this->ret);
        std::fstream file("./Matriz.txt", std::ios::out);
        file << mtx;
        file.close();
        std::string comando = "python3 index.py Matriz Grafo_" + std::to_string(this->tmpi++);
        std::cout << comando <<std:: endl;
        system(comando.c_str());
        */
}

int GrafoMatriz::first(int v){
        for (int i = 0; i < this->qtdNodo; i++)
        {
                if (this->graph[v][i] != 0)
                {
                        return i;
                }
        }
        return this->qtdNodo;
}

int GrafoMatriz::next(int v, int w){
        for (int i = w + 1; i < this->qtdNodo; i++)
        {
                if (this->graph[v][i] != 0)
                {
                        return i;
                }
        }
        return this->qtdNodo;
}

void GrafoMatriz::DFS(int nodoIndex){
        // preVisit
        this->mark[nodoIndex] = true;
        int w = this->first(nodoIndex);
        while (w < this->qtdNodo)
        {
                if (this->mark[w] == false)
                {
                        this->ret[nodoIndex][w] = this->graph[nodoIndex][w];
                        if (this->png)
                        {
                                this->save();
                        }
                        this->DFS(w);
                }
                w = this->next(nodoIndex, w);
        }
        // posVisit
}
std::string GrafoMatriz::TranverseDFS(std::string inicio, bool png){
        this->png = png;
        this->setMark();
        this->DFS(this->Str_Int(inicio));
        for (int i = 0; i < this->qtdNodo; i++)
        {
                if (mark[i] == false)
                {
                        this->DFS(i);
                }
        }
        this->png = false;
        this->tmpi = 0;
        return this->print(this->ret);
}

void GrafoMatriz::BFS(int start){
        std::deque<int> q;
        q.push_back(start);
        this->mark[start] = true;
        while (q.size() > 0)
        {

                int v = q.front();
                q.pop_front();
                // pre visit
                int w = this->first(v);
                while (w < this->qtdNodo)
                {
                        if (!this->mark[w])
                        {
                                this->mark[w] = true;
                                this->ret[v][w] = this->graph[v][w];
                                if (this->png)
                                {
                                        this->save();
                                }
                                q.push_back(w);
                        }
                        w = this->next(v, w);
                }
                // pos visit
        }
}

std::string GrafoMatriz::TranverseBFS(std::string inicio, bool png){
        this->png = png;
        this->setMark();
        this->BFS(this->Str_Int(inicio));
        for (int i = 0; i < this->qtdNodo; i++)
        {
                if (this->mark[i] == false)
                {
                        this->BFS(i);
                }
        }
        this->png = false;
        this->tmpi = 0;
        return this->print(this->ret);
}


// parte da compatibilidade com python

// destructor da instancia da classe
static void des(PyObject *capsule){
        GrafoMatriz* ptr = (GrafoMatriz *)PyCapsule_GetPointer(capsule, NULL);
        if(ptr){        
                //cout << "destruido" << endl;
                delete ptr;
        }
}

// criação de uma instancia da classe de grafo
// servir apenas para ponteiro, os vertices do argumentos de criaão passar para outra fuc
static PyObject* createC(PyObject* self, PyObject* args){
        GrafoMatriz* ptr = new GrafoMatriz();        
        //cout << "criado" << endl;
        return PyCapsule_New(ptr, NULL, des);
}

//recebe o grafo em si e a string
static PyObject* addVextex(PyObject* self, PyObject* args){
        PyObject* ptr;
        const char* str;
        if(!PyArg_ParseTuple(args, "Os", &ptr, &str)){return NULL;}

        ((GrafoMatriz *)PyCapsule_GetPointer(ptr, NULL))->addVertex(str);
        return Py_BuildValue("");
}

// recebe o grafo, o n1, o peso e o n2
static PyObject* addPeso(PyObject* self, PyObject* args){
        PyObject* ptr;
        const char *str, *str2;
        int peso;
        //printf("foi\n");
        if(!PyArg_ParseTuple(args, "Osis", &ptr, &str, &peso, &str2)){return NULL;}
        ((GrafoMatriz *)PyCapsule_GetPointer(ptr, NULL))->Add(str, peso, str2);
        return Py_BuildValue("");
}
// so para pssar no final e criar a matriz em si
static PyObject* Generate(PyObject* self, PyObject* args){
        PyObject* ptr;
        if(!PyArg_ParseTuple(args, "O", &ptr)){return NULL;}
        ((GrafoMatriz *)PyCapsule_GetPointer(ptr, NULL))->Generate();
        return Py_BuildValue("");
}

static PyObject* print(PyObject* self, PyObject* args){
        PyObject* ptr;
        if(!PyArg_ParseTuple(args, "O", &ptr)){return NULL;}

        // TODO: Implementar a parte do png, no momento so ta false
        return Py_BuildValue("s", ((GrafoMatriz *)PyCapsule_GetPointer(ptr, NULL))->print(false).c_str());
        
}

static PyObject* DFS(PyObject* self, PyObject* args){
        PyObject* ptr;
        const char *str;
        if(!PyArg_ParseTuple(args, "Os", &ptr, &str)){return NULL;}

        // TODO: Implementar a parte do png, no momento so ta false
        return Py_BuildValue("s", ((GrafoMatriz *)PyCapsule_GetPointer(ptr, NULL))->TranverseDFS(str, false).c_str());
}

static PyObject* BFS(PyObject* self, PyObject* args){
        PyObject* ptr;
        const char *str;
        if(!PyArg_ParseTuple(args, "Os", &ptr, &str)){return NULL;}

        // TODO: Implementar a parte do png, no momento so ta false
        return Py_BuildValue("s", ((GrafoMatriz *)PyCapsule_GetPointer(ptr, NULL))->TranverseBFS(str, false).c_str());
}

static PyObject* remove(PyObject* self, PyObject* args){
        PyObject* ptr;
        const char *str;
        if(!PyArg_ParseTuple(args, "Os", &ptr, &str)){return NULL;}

        ((GrafoMatriz *)PyCapsule_GetPointer(ptr, NULL))->remove(str);
        return Py_BuildValue("");
}
static PyMethodDef lib_methods[] = {

        {"create", createC, METH_VARARGS, "Funcao de criaçao"},
        {"addVertice", addVextex, METH_VARARGS, "Adiciona os vertices"},
        {"addPeso", addPeso, METH_VARARGS, "Adiciona os pesos na matriz"},
        {"generate", Generate, METH_VARARGS, "Finaliza a adição dos vertices"},
        {"print", print, METH_VARARGS, "Retorna uma String da matriz do grafo"},
        {"remove", remove, METH_VARARGS, "Remove determinado vertice"},
        {"DFS", DFS, METH_VARARGS, "String da DFS"},
        {"BFS", BFS, METH_VARARGS, "String da BFS"},
        {NULL, NULL, 0, NULL}
};

static struct PyModuleDef lib_module = {
        PyModuleDef_HEAD_INIT,
        "graph",
        NULL,
        -1,
        lib_methods
};

PyMODINIT_FUNC PyInit_graph(void){
        return PyModule_Create(&lib_module);
}






