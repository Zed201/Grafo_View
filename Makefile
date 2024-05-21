# serve para achar o python.h, antes tava usando pkg, mas assim fica maias de boa de achar
#py_h=$(shell  find /usr/include/p* -name python3*) nao mais necessario
PY=$(shell which python3 || which python)

compile:
		$(PY) ./src/setup.py build_ext
		mv ./build/lib.linux-x86_64-3.10/lib.cpython-310-x86_64-linux-gnu.so ./lib.so
		mv ./build/lib.linux-x86_64-3.10/graph.cpython-310-x86_64-linux-gnu.so ./graph.so

clean:
	$(PY) ./src/setup.py clean --all
	rm -f ./src/*.c *.so *.png *.gif *.out *.o 
	
cpp:
	g++ index.cpp src/Grafo.cpp
		
