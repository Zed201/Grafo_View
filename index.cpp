// so preguica de criar o .h
#include "./GMatriz.cpp"

int main(int argv, char** argc){
        GrafoMatriz grafu({"a", "b", "c", "d"});
        grafu.Add("a", {{"b", 2}, {"d", 3} });
        grafu.Add("b", {{"c", 5}, {"d", 1} });
        grafu.Add("c", {{"d", 3}});
        grafu.Add("d", {{"c", 6} });
        printf("%s\n", argc[1]);
        grafu.TranverseBFS();
        
        return 0;
}
