# graficos salvando onde deve
# fazer funcs para compor algumas funcoes, melhorar as cores e algumas coisas como o with
# Copiar o CMatrix e dar um jeito de printar em file.txt 
# Tentar criar algum gif com o python e os estagios de cada busca
import networkx as nx
import matplotlib.pyplot as plt
import numpy as np
import random as rd

# coisas para cores
rd.seed()
cores_nodes = ['red', 'blue', 'black', '#0D1321', '#FE5F55', '#8A1C7C', 'black']
cores_text = ['black', 'whitesmoke', 'whitesmoke', '#F7F7FF', 'black', 'whitesmoke', 'white']
ind_cor = rd.randint(0, len(cores_nodes) - 1)

# Funciona para ler um file.txt e retorna a matriz de numpy e o dict com os nomes e os "index's"
def leitura(file_name):
    Nomes_index = dict()
    with open("./{0}".format(file_name)) as file:
        vertices_td = int(file.readline())
        for i in range(vertices_td):
            node_tmp = str(file.readline()).strip()
            Nomes_index[i] = node_tmp
        Matriz = np.zeros((vertices_td, vertices_td))
        for i in range(vertices_td):
            linha = file.readline().strip().split()
            for ind, el in enumerate(linha):
                Matriz[i][ind] = int(el)
    return (Matriz, Nomes_index)    

def Draw(img_name, Matriz, nomes_grafo):
    Grafo = nx.relabel_nodes(nx.DiGraph(Matriz), nomes_grafo, 'name')
    plt.figure(1)
    pesos = nx.get_edge_attributes(Grafo, "weight")
    nomes = nx.get_node_attributes(Grafo, "name")
    nodos_size = [len(label) * 400 for label in nomes_grafo.values()]
    #print(nomes)
    #print(pesos)
    posi = nx.spring_layout(Grafo)             # modo spring, de mola
    #posi = nx.circular_layout(Grafo_adj)     # modo circular
    #posi = nx.planar_layout(Grafo_adj)     # forma planar, sem os edges se cuzarem
    #posi = nx.shell_layout(Grafo_adj)    # n sei oque é shell

    nx.draw(Grafo, pos=posi, node_size=nodos_size, node_color=cores_nodes[ind_cor])

    nx.draw_networkx_labels(Grafo, pos=posi, font_size=10, font_color=cores_text[ind_cor])

    for edge, w in pesos.items():
        nx.draw_networkx_edge_labels(Grafo, pos=posi, edge_labels={(edge[0], edge[1]) : w})
    plt.savefig("./{0}.png".format(img_name), format='png')

matrix, nomes = leitura("index.txt")
Draw("test", matrix, nomes)
