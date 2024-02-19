# Visualizador
Tem como principal função imprimir tando a matriz de adjascência dos grafos e plotar eles usando networkX e pyplot.
Basicamente uma implementação de grafos por matriz de adjascência em C++(´./Grafo.cpp´) que foi "compilado", utilizando a API do Cpython, 
como uma "biblioteca" para python(lib.py) que tem uma classe, a Grafo que basicamente implementa as mesmas funções da classe de C++.
Para compilar a "lib" só usar o make, ele vai gerar um .so que é a biblioteca de fato e ela é importada pelo lib.py; Para usar no python é so dar 
import no lib e usar a classe Grafo, exemplo de uso no index.py, a classe de C++ também pode ser usada, com basicamente a mesma sintaxe, 
exemplo no index.cpp e pode usar o ´make c´ para compilar esse codigo.
