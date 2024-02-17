py_h=$(shell pkg-config --cflags python3)
CFLAGS += $(py_h)
all:
	@clear
	g++ Grafo.cpp -shared -fPIC $(CFLAGS) -o graph.so
