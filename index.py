# graficos salvando onde deve
import networkx as nx
import matplotlib.pyplot as plt
import numpy as np
import random as rd
rd.seed()
cores_nodes = ['red', 'blue', 'black', '#0D1321', '#FE5F55', '#8A1C7C', 'black']
cores_text = ['black', 'whitesmoke', 'whitesmoke', '#F7F7FF', 'black', 'whitesmoke', 'white']
ind_cor = rd.randint(0, len(cores_nodes) - 1)
G = dict()

with open("./index.txt") as file:
    qtd_vertices = int(file.readline())
    for i in range(qtd_vertices):
        node = str(file.readline()).strip()
        #print(node)
        G[i] = node
    # agora pega a matriz
    #print(G)
    Mtmp = np.zeros((qtd_vertices, qtd_vertices))
    for i in range(qtd_vertices):
        linha =  file.readline().strip().split()
        for index, el in enumerate(linha):
            Mtmp[i][index] = int(el)
    Grafo_adj = nx.DiGraph(Mtmp)
    Grafo_adj = nx.relabel_nodes(Grafo_adj, G, 'name')
    #print(Mtmp)
    plt.figure(1)
    
    pesos = nx.get_edge_attributes(Grafo_adj, "weight")
    nodos_size = [len(label) * 300 for label in G.values()]
    #print(nodos_nomes)
    # modo spring, de mola
    #pos = nx.spring_layout(Grafo_adj)

    # modo circular 
    #pos = nx.circular_layout(Grafo_adj)
    # forma planar, sem os edges se cuzarem 
    pos = nx.planar_layout(Grafo_adj) 
    # n sei oque é shell
    #pos = nx.shell_layout(Grafo_adj) 
    nx.draw(Grafo_adj, pos=pos, node_size=nodos_size, node_color=cores_nodes[ind_cor])
    
    nx.draw_networkx_labels(Grafo_adj, pos=pos, font_size=10, font_color=cores_text[ind_cor])

    for edge, w in pesos.items():
        nx.draw_networkx_edge_labels(Grafo_adj, pos=pos, edge_labels={(edge[0], edge[1]) : w})
    plt.savefig("Grafo_matriz.png", format='png')


