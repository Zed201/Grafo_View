// parte da compatibilidade com python
#include "./Grafo.h"
#include <python3.12/Python.h>
#include <Python.h>


// destructor da instancia da classe
static void des(PyObject *capsule){
        GrafoMatriz* ptr = (GrafoMatriz *)PyCapsule_GetPointer(capsule, NULL);
        if(ptr){        
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

// funcao para o print, retornando apenas uma string
static PyObject* print(PyObject* self, PyObject* args){
        PyObject* ptr;
        if(!PyArg_ParseTuple(args, "O", &ptr)){return NULL;}


        return Py_BuildValue("s", ((GrafoMatriz *)PyCapsule_GetPointer(ptr, NULL))->print().c_str());

}

// as funções do BFS e DFS elas geram os .txt para ser usado na geração de .gif's
static PyObject* DFS(PyObject* self, PyObject* args){
        PyObject* ptr;
        const char *str;
        if(!PyArg_ParseTuple(args, "Os", &ptr, &str)){return NULL;}

        // TODO: Nao ta retornando mais str mas sim usar o getState
        return Py_BuildValue("s", ((GrafoMatriz *)PyCapsule_GetPointer(ptr, NULL))->TranverseDFS(str).c_str());

}

static PyObject* BFS(PyObject* self, PyObject* args){
        PyObject* ptr;
        const char *str;
        if(!PyArg_ParseTuple(args, "Os", &ptr, &str)){return NULL;}
        // TODO: implementar a ideia do getState
        return Py_BuildValue("s", ((GrafoMatriz *)PyCapsule_GetPointer(ptr, NULL))->TranverseBFS(str).c_str());

}

static PyObject* get_state(PyObject* self, PyObject* args){
        PyObject* ptr;
        if(!PyArg_ParseTuple(args, "O", &ptr)){return NULL;}
        // criando a lista ele da bad_alloc, ate sem so printando ele tava dando bac_alloc
        GrafoMatriz* gra = (GrafoMatriz *) PyCapsule_GetPointer(ptr, NULL);
        if(gra->save_state.size() == 0){
                // Nao tem state
                printf("Sem states\n");
                return Py_BuildValue(""); // retorna None
        }
        PyObject* lista  = PyList_New(gra->save_state.size());
        PyObject* tmp = NULL;
        if (!lista) {
                printf("Erro criando a lista\n");
                return NULL;
        }
        int j = 0;
        for (std::string i : gra->save_state) {
                tmp = Py_BuildValue("s", i.c_str());
                if(!tmp){
                        Py_DecRef(lista);
                        printf("Erro na alocação de elementos\n");
                        return NULL;
                }
                PyList_SetItem(lista, j++, tmp);
        }
        return lista;
}

// remover um vertice
static PyObject* remove(PyObject* self, PyObject* args){
        PyObject* ptr;
        const char *str;
        if(!PyArg_ParseTuple(args, "Os", &ptr, &str)){return NULL;}

        ((GrafoMatriz *)PyCapsule_GetPointer(ptr, NULL))->remove(str);
        return Py_BuildValue("");
}

static PyObject* isIn(PyObject* self, PyObject* args){
        PyObject* ptr;
        const char *str;
        if(!PyArg_ParseTuple(args, "Os", &ptr, &str)){ return NULL;}
        std::string st = str;
        return Py_BuildValue("i", ((GrafoMatriz *)PyCapsule_GetPointer(ptr, NULL))->isIn(st));
}

static PyObject* getOrdem(PyObject *self, PyObject* args){
        PyObject* ptr;
        if(!PyArg_ParseTuple(args, "O", &ptr)){ 
                return NULL;
        }
        return Py_BuildValue("s", ((GrafoMatriz *)PyCapsule_GetPointer(ptr, NULL))->Ordem().c_str());
}

static PyObject* getQtd(PyObject *self, PyObject* args){
        PyObject* ptr;
        if(!PyArg_ParseTuple(args, "O", &ptr)){ 
                return NULL;
        }
        return Py_BuildValue("i", ((GrafoMatriz *)PyCapsule_GetPointer(ptr, NULL))->nodos_qtd());
}

// listagem de todos os métodos
static PyMethodDef lib_methods[] = {
        {"create", createC, METH_VARARGS, "Funcao de criaçao"},
        {"addVertice", addVextex, METH_VARARGS, "Adiciona os vertices"},
        {"addPeso", addPeso, METH_VARARGS, "Adiciona os pesos na matriz"},
        {"generate", Generate, METH_VARARGS, "Finaliza a adição dos vertices"},
        {"print", print, METH_VARARGS, "Retorna uma String da matriz do grafo"},
        {"remove", remove, METH_VARARGS, "Remove determinado vertice"},
        {"DFS", DFS, METH_VARARGS, "String da DFS"},
        {"BFS", BFS, METH_VARARGS, "String da BFS"},
        {"isIN", isIn, METH_VARARGS, "Verificar se um vertice esta no grafo"},
        {"Ordem", getOrdem, METH_VARARGS, "Retorna uma string com a ordem dos vertices"},
        {"getState", get_state, METH_VARARGS, "Retorna uma lista com os states"},
        {"NodosQtd", getQtd, METH_VARARGS, "Retornar a quantidade de nós no grafico"},
        {NULL, NULL, 0, NULL}
};

// criação da struct representando o modulo
static struct PyModuleDef lib_module = {
        PyModuleDef_HEAD_INIT,
        "graph",
        NULL,
        -1,
        lib_methods
};

// inicialização do módulo de fato
PyMODINIT_FUNC PyInit_graph(void){
        return PyModule_Create(&lib_module);
}

