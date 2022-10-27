#include <iostream>
#include <vector>
#include <map>

using namespace std;

vector<vector<int> > input = {
    {1,0,0,1,0},
    {1,0,1,0,0},
    {0,0,1,0,1},
    {1,0,1,0,1},
    {1,0,1,1,0}
    };

vector<int> riverSizes;
map<int,map<int,int> > visited;
int length = 0;

void helper(int row, int col) {
    if(input[row][col] == 0 || visited[row][col]) return;

    length++;
    visited[row][col] = true;

    if(col + 1 < input[row].size()) helper(row, col+1);   //look right
    if(col < input[row+1].size()) helper(row+1, col);   //look down
}

void findRivers() {
    for(int i = 0; i < input.size(); i++) {
        for(int j = 0; j < input[i].size(); j++) {
            helper(i, j);
            if(length > 0) riverSizes.push_back(length);
            length = 0;
        }
    }
}

int main() {
    findRivers();

    cout << "River Sizes: ";
    for(int i = 0; i < riverSizes.size(); i++) {
        cout << riverSizes[i] << " ";
    }
    cout << "\n";

    return 0;
}