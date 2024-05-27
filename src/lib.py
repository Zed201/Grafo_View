import graph
import networkx as nx # desenhar e plotar o grafico
import matplotlib.pyplot as plt
import numpy as np # auxilio de matriz
import random as rd # para randomizar os estilos
import imageio.v2 as imageio # para criar o gif
import os # para remover .txt
import re 

class Grafo:
    # estilos que serão randomizados
    cores_nodes = ['red', 'blue', 'black', '#0D1321', '#FE5F55', '#8A1C7C', 'black']
    cores_text = ['black', 'whitesmoke', 'whitesmoke', '#F7F7FF', 'black', 'whitesmoke', 'white']

    # passa uma lista dos nomes dos nodos
    def __init__(self, nodos_name:list):
        self.__grafo__ = graph.create()
        for i in nodos_name:
            graph.addVertice(self.__grafo__, str(i))

        graph.generate(self.__grafo__)
        
        rd.seed()

    # Primeiro passa o nodo de inicio depois
    # passa a lista por tupla, indicando primeiro
    # o nodo de destino depois o peso, [("nodo1", 123)]
    def addVertex(self, nodo_inicio:str, vertex_list:list):
        for nodo, peso in vertex_list:
            if nodo != nodo_inicio:
                graph.addPeso(self.__grafo__, nodo_inicio, peso, nodo)
            else:
                # os algoritmos nao tem muita necessidade para 
                # vertices no mesmo nodo
                raise Exception("Não pode ter vertice para o próprio nodo")

    @property
    def matriz(self):
        return self.__sep__(graph.print(self.__grafo__))

    @property
    def qtdNodos(self):
        return graph.NodosQtd(self.__grafo__)
    @property
    def ordem(self):
        return graph.Ordem(self.__grafo__)

    # retorna uma string com o algoritmo de BFS(Matriz final)
    def BFS(self, nodo_inicio:str):
        return graph.BFS(self.__grafo__, nodo_inicio)
        # la no cpp ele cria esses .txt com os passo, ai nesse caso so retira eles

    # retorna uma string com o algoritmo de DFS(Matriz final)
    def DFS(self, nodo_inicio:str):
        return graph.DFS(self.__grafo__, nodo_inicio)
    
    def __str__(self) -> str:
        return graph.print(self.__grafo__)

    def __sep__(self, matrix:str):
        tmp = matrix.split(" \n")[:-1]
        m = np.zeros((self.qtdNodos, self.qtdNodos))
        for idx, eli in enumerate(tmp):
            for jdx, elj in enumerate(eli.split(" ")):
                m[idx, jdx] = int(elj)
        return m
 
    def __drw__(self, Matriz, nomes_grafo, style_dis:int, ind_cor:int):
        # o Grafo é escolhido na linha de baixo, podemos usar:
        # nx.Graph para nao direcionado ponderados
        # nx.DiGraph para ponderados e direcionados
        # nx.MultiGraph para multigrafos nao direcionados (nao funciona direito)
        # nx.MultiDigraph, para multigrafos direcionados(nao funciona direito, pois as multiplas arestas parecem nao funcionar com matrizes)
        # cria o grafo em si, e passa o dict como os labels deles

        Grafo = nx.relabel_nodes(G=nx.DiGraph(Matriz), mapping=nomes_grafo) # antes tinha o 'name' para indicar os nomes
        plt.figure(1, figsize=(8,6))
        # pega os atributos name e pesos
        pesos = nx.get_edge_attributes(Grafo, "weight")
        # adiciona tamanaho aos nodos a depender dos labels deles
        nodos_size = [len(label) * 400 for label in nomes_grafo.values()]
        # tipos de layouts que dizem respetto a distribuição dos nodos
        # refazer pois o cython esta dando erro
        posi = None
        if style_dis == 0: 
            posi = nx.circular_layout(Grafo)     # modo circular
        elif style_dis == 1: 
            posi = nx.spring_layout(Grafo)             # modo spring, de mola
        elif style_dis == 2: 
            posi = nx.planar_layout(Grafo)     # forma planar, sem os edges se cuzarem
        elif style_dis == 3: 
            posi = nx.shell_layout(Grafo)    # n sei oque é shell
        else: 
            posi = nx.circular_layout(Grafo)
            
        
        # draw ´principal no plot
        nx.draw(Grafo, pos=posi, node_size=nodos_size, node_color=self.cores_nodes[ind_cor])
        # draw dos nomes do nodos
        nx.draw_networkx_labels(Grafo, pos=posi, font_size=10, font_color=self.cores_text[ind_cor])
        # nx.draw_networkx_labels(Grafo)
        # # draw de cada peso de aresta 
        for edge, w in pesos.items():
            nx.draw_networkx_edge_labels(Grafo, pos=posi, edge_labels={(edge[0], edge[1]) : w})
        # # salvamento da imagem

    # Criar um .png do grafo com base nos argumentos, se nao passar o style ou a cor ele randomiza
    def DrwPrint(self, style_dis=None, ind_cor=None, file_name=None):
        Matriz = self.matriz 
        nomes_grafo = dict()
        tmp_n = self.ordem.split(" ")[:-1]
        for idx, el in enumerate(tmp_n):
            nomes_grafo[idx] = el
        self.__drw__(Matriz, nomes_grafo, style_dis, ind_cor)
        if file_name:
            plt.savefig("./{0}.png".format(file_name), format='png')
        else:
            plt.draw()
        # plt.clf()

    # def __gif__(self, file_name:str):
    #     padrao = re.compile(r'^Matriz_.*\.png$')
    #     caminhos = list(filter(lambda x: padrao.match(x), os.listdir(os.path.dirname(__file__))))
    #     file_name += ".gif"
    #     with imageio.get_writer(file_name, fps=0.5) as file:
    #         for g in sorted(caminhos):
    #             file.append_data(imageio.imread(g))
    #             os.remove(str(g))
    #     
    # def GifBFS(self, nodo_name:str, file_name:str, style_dis:int=None, ind_cor:int=None):
    #     # logica
    #     # os dados estao todos no Matriz_*.txt no proprio dir
    #     graph.BFS(self.__grafo__, nodo_name)        
    #     self.__imgs__(style_dis, ind_cor)
    #     self.__gif__(file_name)

    # def GifDFS(self, nodo_name:str, file_name:str, style_dis:int=None, ind_cor:int=None):
    #     # logica
    #     graph.DFS(self.__grafo__, nodo_name)
    #     self.__imgs__(style_dis, ind_cor)
    #     self.__gif__(file_name)

def main():
    pass

if __name__ == '__main__':
    main()
