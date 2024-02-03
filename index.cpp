// so preguica de criar o .h
#include "./GMatriz.cpp"
// basicamente nesse cpp descrevemos o grafo e a operacao
// eles elasa Tranverse de DFS e o de BSf, alem do print normal, e dps dijkstra

int main(int argv, char** argc){
        GrafoMatriz grafu({"6", "1", "2", "3", "4", "5", "0", "7", "8", "9"});
        grafu.Add("0", { });
        grafu.Add("1", {{"0", 1} });
        grafu.Add("2", {{"1", 1}, {"3", 1}, {"4", 1} });
        grafu.Add("3", {{"1", 1} });
        grafu.Add("4", {{"3", 1} });
        grafu.Add("5", {{"4", 1} });
        grafu.Add("6", {{"5", 1}, {"2", 1}, {"7", 1} });
        grafu.Add("7", {{"8", 1}, {"9", 1} });
        grafu.Add("8", { });
        grafu.Add("9", { });
        // so compilar e passar como argumento o nome do file final, o python vai cuidar de tudo
        printf("%s\n", argc[1]);
        grafu.TranverseDFS();
        
        return 0;
}
