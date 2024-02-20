# serve para achar o python.h, antes tava usando pkg, mas assim fica maias de boa de achar
py_h=$(shell  find /usr/include/p* -name python3*)

all:
	g++ libpyMatriz.cpp Grafo.cpp -shared -fPIC -I$(py_h) -o graph.so

c:
	g++ index.cpp Grafo.cpp
