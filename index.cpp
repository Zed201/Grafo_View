#include <iostream>
#include "./GMatriz.hpp"

using namespace std;

int main(int argv, char** argc){
        GrafoMatriz grafu({"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"});
        grafu.Add("0", {{"9", 1 } });
        grafu.Add("1", {{"0", 1}, {"6", 1} });
        grafu.Add("2", {{"1", 1}, {"3", 1}, {"4", 1} });
        grafu.Add("3", {{"1", 1} });
        grafu.Add("4", {{"3", 1} });
        grafu.Add("5", {{"4", 1} });
        grafu.Add("6", {{"5", 1}, {"2", 1}, {"7", 1} });
        grafu.Add("7", {{"8", 1}, {"9", 1} });
        grafu.Add("8", {{"0", 1}, {"6", 1} });
        grafu.Add("9", {{"0", 1} });
        
        cout << grafu.TranverseDFS("0", true);
        return 0;
}
