# import src.lib as lib
import lib

a = lib.Grafo(["a", "b", "c", "d", "e"])
# a.addVertex("a", [("b", 10), ("c", 3), ("d", 20) ])
a.addVertex("b", [("c", 5) ])
a.addVertex("c", [("d", 2) ])
a.addVertex("d", [("a", 4) ])
a.addVertex("e", [("b", 6)])
print(a.DFS("e"))
a.states()
# a.DrwPrint(1, 1)
