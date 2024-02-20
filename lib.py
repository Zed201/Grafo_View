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

    # retorna uma str com a print do grafo
    def print(self):
        # o -1 simplesmente tira o \n do final
        return graph.print(self.__grafo__)[:-1]

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

    # retorna uma string com o algoritmo de BFS
    def BFS(self, nodo_inicio:str):
        a =  graph.BFS(self.__grafo__, nodo_inicio)[:-1]
        # la no cpp ele cria esses .txt com os passo, ai nesse caso so retira eles
        os.system("rm -rf ./Matriz_*.txt")
        return a

    # retorna uma string com o algoritmo de DFS
    def DFS(self, nodo_inicio:str):
        a =  graph.DFS(self.__grafo__, nodo_inicio)[:-1]
        os.system("rm -rf ./Matriz_*.txt")
        return a
    
    def __sep__(self, print_str:str):
        nomes_grafo = dict()
        printret = print_str.split("\n")
        vertices_td = int(printret[0])
        Matriz = np.zeros((vertices_td, vertices_td))
        for i in range(vertices_td):
            nomes_grafo[i] = str(printret[i + 1]).strip()
            linha = str(printret[vertices_td + i + 1]).split()
            for ind, el in enumerate(linha):
                Matriz[i][ind] = int(el)

        return (Matriz, nomes_grafo)

    def __drw__(self, Matriz, nomes_grafo, style_dis:int=None, ind_cor:int=None):
        # o Grafo é escolhido na linha de baixo, podemos usar:
        # nx.Graph para nao direcionado ponderados
        # nx.DiGraph para ponderados e direcionados
        # nx.MultiGraph para multigrafos nao direcionados (nao funciona direito)
        # nx.MultiDigraph, para multigrafos direcionados(nao funciona direito, pois as multiplas arestas parecem nao funcionar com matrizes)
        # cria o grafo em si, e passa o dict como os labels deles
        Grafo = nx.relabel_nodes(nx.DiGraph(Matriz), nomes_grafo, 'name')
        plt.figure(1, figsize=(8,6))
        # pega os atributos name e pesos
        pesos = nx.get_edge_attributes(Grafo, "weight")
        nomes = nx.get_node_attributes(Grafo, "name")
        # adiciona tamanaho aos nodos a depender dos labels deles
        nodos_size = [len(label) * 400 for label in nomes_grafo.values()]
        # tipos de layouts que dizem respetto a distribuição dos nodos
        match (style_dis):
            case 0: posi = nx.circular_layout(Grafo)     # modo circular
            case 1: posi = nx.spring_layout(Grafo)             # modo spring, de mola
            case 2: posi = nx.planar_layout(Grafo)     # forma planar, sem os edges se cuzarem
            case 3: posi = nx.shell_layout(Grafo)    # n sei oque é shell
            case _: posi = nx.circular_layout(Grafo)
        # draw ´principal no plot
        nx.draw(Grafo, pos=posi, node_size=nodos_size, node_color=self.cores_nodes[ind_cor])
        # draw dos nomes do nodos
        nx.draw_networkx_labels(Grafo, pos=posi, font_size=10, font_color=self.cores_text[ind_cor])
        # draw de cada peso de aresta 
        for edge, w in pesos.items():
            nx.draw_networkx_edge_labels(Grafo, pos=posi, edge_labels={(edge[0], edge[1]) : w})
        # salvamento da imagem

    # Criar um .png do grafo com base nos argumentos, se nao passar o style ou a cor ele randomiza
    def DrwPrint(self, file_name:str, style_dis:int=None, ind_cor:int=None):
        if ind_cor == None:
            ind_cor = rd.randint(0, len(self.cores_text) - 1)
        if style_dis == None:
            style_dis = rd.randint(0, 3)

        Matriz, nomes_grafo = self.__sep__(self.print()) 
        self.__drw__(Matriz, nomes_grafo, style_dis, ind_cor)
        plt.savefig("./{0}.png".format(file_name), format='png')
        plt.clf()

    def __gif__(self, file_name:str):
        padrao = re.compile(r'^Matriz_.*\.png$')
        caminhos = list(filter(lambda x: padrao.match(x), os.listdir(os.path.dirname(__file__))))
        file_name += ".gif"
        with imageio.get_writer(file_name, fps=0.5) as file:
            for g in sorted(caminhos):
                file.append_data(imageio.imread(g))
                os.remove(str(g))
        
    def __imgs__(self, style_dis:int=None, ind_cor:int=None):
        if ind_cor == None:
            ind_cor = rd.randint(0, len(self.cores_text) - 1)
        if style_dis == None:
            style_dis = rd.randint(0, 3)

        padrao = re.compile(r'^Matriz_.*\.txt$')
        caminhos = list(filter(lambda x:padrao.match(x), os.listdir(os.path.dirname(__file__))))
        for index, i in enumerate(sorted(caminhos)):
            with open(str(i)) as file:
                Matriz, nomes_grafo = self.__sep__(str(file.read()))
                self.__drw__(Matriz, nomes_grafo, style_dis, ind_cor)
                plt.savefig("./Matriz_{0}.png".format(str(index)))
                plt.clf()
                os.remove(str(i))

    # funcoes d para gerar gifs do respectivo algoritmo
    def GifBFS(self, nodo_name:str, file_name:str, style_dis:int=None, ind_cor:int=None):
        # logica
        # os dados estao todos no Matriz_*.txt no proprio dir
        graph.BFS(self.__grafo__, nodo_name)        
        self.__imgs__(style_dis, ind_cor)
        self.__gif__(file_name)

    def GifDFS(self, nodo_name:str, file_name:str, style_dis:int=None, ind_cor:int=None):
        # logica
        graph.DFS(self.__grafo__, nodo_name)
        self.__imgs__(style_dis, ind_cor)
        self.__gif__(file_name)
