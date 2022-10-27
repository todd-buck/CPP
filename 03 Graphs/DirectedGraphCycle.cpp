#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<vector<int> > edges = {{1,3},{2,3,4},{0},{},{2,5},{}};
map<int,bool> inPath;
map<int,bool> visited;
bool cycle = false;

void isCyclic(int node) {
    inPath[node] = true;
    visited[node] = true;


    for(int i = 0; i < edges[node].size(); i++) {
        if(inPath[edges[node][i]]) {
            cycle = true;
            return;
        } else if(!visited[edges[node][i]]) {
            isCyclic(edges[node][i]);
        }
    }

    inPath[node] = false;
}

int main() {
    isCyclic(0);

    if(cycle) cout << "Cycle occurs\n";
        else cout << "Cycle does not occur\n";

    return 0;
}