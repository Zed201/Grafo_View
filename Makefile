# serve para achar o python.h, antes tava usando pkg, mas assim fica maias de boa de achar
py_h=$(shell  find /usr/include/p* -name python3*)
cpp_path=./src/
py_path=./src/

all:
	g++ $(cpp_path)libpyMatriz.cpp $(cpp_path)Grafo.cpp -shared -fPIC -I$(py_h) -o ./src/graph.so
	cython $(py_path)lib.py --3str --module-name lib
	gcc $(py_path)lib.c -fPIC -shared -I$(py_h) -o ./src/lib.so

c:
	g++ index.cpp $(cpp_path)Grafo.cpp
