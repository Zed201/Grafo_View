# serve para achar o python.h, antes tava usando pkg, mas assim fica maias de boa de achar
#py_h=$(shell  find /usr/include/p* -name python3*) nao mais necessario
PY=$(shell which python3 || which python)
ver=cpython-312-x86_64-linux-gnu
p_b=lib.linux-x86_64-cpython-312

compile:
		$(PY) ./src/setup.py build_ext
		mv ./build/$(p_b)/lib.$(ver).so ./lib.so
		mv ./build/$(p_b)/graph.$(ver).so ./graph.so

clean:
	$(PY) ./src/setup.py clean --all
	rm -f ./src/*.c *.so *.png *.gif *.out *.o 
	
cpp:
	g++ index.cpp src/Grafo.cpp
		
