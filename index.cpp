#include <iostream>
#include "./Grafo.hpp"
using namespace std;

int main(){
        GrafoMatriz gr({"a", "b", "c", "d", "e"});
        gr.Add("a", {{"b", 10}, {"c", 3}, {"d", 20} });
        gr.Add("b", {{"d", 5} });
        gr.Add("c", {{"b", 2}, {"e", 15} });
        gr.Add("d", {{"e", 11} });
        cout << gr.print() << endl;
        return 0;
}
