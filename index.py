import src.graph as graph
import src.lib as lib

a = lib.Grafo(["a", "b", "c", "d", "e"])
a.addVertex("a", [("b", 10), ("c", 3), ("d", 20) ])
a.addVertex("b", [("d", 5) ])
a.addVertex("c", [("b", 2), ("e", 15) ])
a.addVertex("d", [("e", 11) ])
a.DrwPrint("test_print", 1, 2)
