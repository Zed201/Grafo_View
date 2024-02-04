 # Visualizador
Objetivo de fazer um plot automatico de grafos com base em matriz de adjascencia que é resultado da
implementação de grafos em C++ da materia de algoritmos.
Um modelo da entrada esta no arquivo index.txt, contendo a quantidade e a lista dos vertices e a matriz em si, que sera lido e depois plotado para um grafo pelo index.py

Atualização:
Ainda tem muitas das funções originais, mas no caso agora usando o comando make ele gera um gif do processo indicado no index.cpp.
Basicamente o GMatriz.cpp é uma implementação de um grafo or matriz, com BFS e DFS, a cada passo desses algoritmos ele salva o estado do grafo final em ./dados, basicamente uma lista com os nomes dos nodos e a matriz, além de um nome no incio indicando a ordem de cada "frame".
Além disso a cada iteração ele chama o index.py, pelo próprio index.cpp, para gerar o grafo correspondente àquele passo do algoritmo.
No final o proprio makefile ele chama o gif.py e ele gera um gif com todos as imagens
