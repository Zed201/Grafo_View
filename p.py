import graph
a = graph.create()
graph.addVertice(a, "a1")
graph.addVertice(a, "a2")
graph.addVertice(a, "a3")
graph.addVertice(a, "a4")
graph.generate(a)
# so pode dps do generate
graph.addPeso(a, "a1", 1, "a2")
graph.addPeso(a, "a4", 2, "a1")
graph.addPeso(a, "a3", 7, "a4")
graph.addPeso(a, "a2", 3, "a1")
#graph.print(a)
# graph.DFS(a, "a1")
# graph.BFS(a, "a1"

graph.print(a)
graph.remove(a, "a1")
graph.print(a)
