# graficos salvando onde deve
# Tentar criar algum gif com o python e os estagios de cada busca
import networkx as nx
import matplotlib.pyplot as plt
import numpy as np
import random as rd
import sys

# coisas para cores, para selecionar cores de destaque nos nodos e nos lables
# para geracoes aleatorias funciona legal, mas para gifs nao funciona tanto
rd.seed()
cores_nodes = ['red', 'blue', 'black', '#0D1321', '#FE5F55', '#8A1C7C', 'black']
cores_text = ['black', 'whitesmoke', 'whitesmoke', '#F7F7FF', 'black', 'whitesmoke', 'white']
ind_cor = rd.randint(0, len(cores_nodes) - 1)
ind_cor = 2

# Funciona para ler um file.txt e retorna a matriz de numpy e o dict com os nomes e os "index's"
def leitura(file_name):
    # cria um dict que vai ser retornado e serve para adiiconar os labels ao grafo
    Nomes_index = dict()
    with open(file_name) as file:
        # o nome final do arquivo
        resu_fina = str(file.readline()).strip()
        vertices_td = int(file.readline())
        # leitura tanto dos nomes do nos e depois da matriz, np array no caso, respetivamente
        for i in range(vertices_td):
            node_tmp = str(file.readline()).strip()
            Nomes_index[i] = node_tmp
        Matriz = np.zeros((vertices_td, vertices_td))
        for i in range(vertices_td):
            linha = file.readline().strip().split()
            for ind, el in enumerate(linha):
                Matriz[i][ind] = int(el)
    return (Matriz, Nomes_index, resu_fina)    

# funcao que passa o nome apenas do arquivo png final, a matriz de adjascencia e o dict dos nomes dos grafos
def Draw(img_name, Matriz, nomes_grafo):

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

    # DEBUG:
    #print(nomes)
    #print(pesos)

    # tipos de layouts que dizem respetto a distribuição dos nodos
    #posi = nx.spring_layout(Grafo)             # modo spring, de mola
    posi = nx.circular_layout(Grafo)     # modo circular
    #posi = nx.planar_layout(Grafo)     # forma planar, sem os edges se cuzarem
    #posi = nx.shell_layout(Grafo)    # n sei oque é shell

    # draw ´principal no plot
    nx.draw(Grafo, pos=posi, node_size=nodos_size, node_color=cores_nodes[ind_cor])
    # draw dos nomes do nodos
    nx.draw_networkx_labels(Grafo, pos=posi, font_size=10, font_color=cores_text[ind_cor])
    # draw de cada peso de aresta 
    for edge, w in pesos.items():
        nx.draw_networkx_edge_labels(Grafo, pos=posi, edge_labels={(edge[0], edge[1]) : w})
    # salvamento da imagem
    plt.savefig("./images/{0}.png".format(img_name), format='png')

matrix, nomes_nds, final_path = leitura("./dados/{0}.txt".format(sys.argv[1]))
Draw(final_path, matrix, nomes_nds)

