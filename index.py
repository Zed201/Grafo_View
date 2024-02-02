# graficos salvando onde deve
import networkx as nx
import matplotlib.pyplot as plt
import numpy as np
G = nx.Graph()
# G.add_edge("1", "2", weight=3)
# G.add_edge("1", "3", weight=3)
# G.add_edge("2", "3", weight=3)
# plt.figure(1)
# nx.draw_networkx(G, pos=nx.spring_layout(G), with_labels=True)
# plt.savefig("graf.png", format="png")
with open("./index.txt") as file:
    qtd_vertices = int(file.readline())
    for i in range(qtd_vertices):
        node = str(file.readline()).replace("\n", "")
        G.add_node(node)
    # agora pega a matriz
    Mtmp = np.zeros((qtd_vertices, qtd_vertices))
    for i in range(qtd_vertices):
        linha =  file.readline().split(" ")
        for index, el in enumerate(linha):
            Mtmp[i][index] = int(el.replace("\n", ""))
    Grafo_adj = nx.DiGraph(Mtmp)
    print(Mtmp)
    plt.figure(1)
    pesos = nx.get_edge_attributes(Grafo_adj, "weight")
    pos = nx.spring_layout(Grafo_adj)
    nx.draw_networkx(Grafo_adj, pos=pos, with_labels=True)
    for edge, w in pesos.items():
        nx.draw_networkx_edge_labels(Grafo_adj, pos=pos, edge_labels={(edge[0], edge[1]) : w})
    plt.savefig("Grafo_matriz.png", format='png')


# plt.figure(1)
# nx.draw_networkx(G, pos=nx.spring_layout(G), with_labels=True)
# plt.savefig("graf.png", format="png")

# desenha o grafo do jeito que eu quero
# m = np.array([[0, 3, 0, 0, 0, 0, 0],
#               [0, 0, 1, 0, 0, 0, 0],
#               [0, 0, 0, 1, 0, 0, 0],
#               [0, 0, 0, 0, 4, 0, 0],
#               [0, 0, 0, 0, 0, 0, 3],
#               [0, 0, 0, 0, 0, 0, 0],
#               [0, 0, 0, 0, 0, 1, 0]])
# matriz = nx.DiGraph(m)
# plt.figure(1)
# pesos = nx.get_edge_attributes(matriz, "weight")
# pos = nx.spring_layout(matriz)
# nx.draw_networkx(matriz, pos=pos, with_labels=True)
# for edge, weitgth in pesos.items():
#     nx.draw_networkx_edge_labels(matriz, pos=pos, edge_labels={(edge[0], edge[1]): weitgth})
    
# plt.savefig("grafo.png", format='png')
