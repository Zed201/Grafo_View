# serve para achar o python.h
py_h=$(shell pkg-config --cflags python3)
CFLAGS += $(py_h)

lib_py:
	g++ libpyMatriz.cpp Grafo.cpp -shared -fPIC $(CFLAGS) -o graph.so

c:
	g++ index.cpp Grafo.cpp
