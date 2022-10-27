#include <iostream>
#include <vector>

using namespace std;

void BinarySearch(vector<vector<int>> matrix, int row, int col, int target, vector<vector<int>> &solution) {
    if(row < 0 || col < 0) return;
    if(row > matrix.size() || col > matrix[0].size()-1) return;

    if(matrix[row][col] == target) {
        vector<int> temp;
        temp.push_back(row);
        temp.push_back(col);
        solution.push_back(temp);
    }

    if(matrix[row][col] > target) BinarySearch(matrix, row, col - 1, target, solution);
    if(matrix[row][col] < target) BinarySearch(matrix, row + 1, col, target, solution);

    return;
}


int main () {
    int i, j;
    vector<vector<int>> solution;

    vector<vector<int>> matrix = 
    {
        {0,3,8,10,15},
        {1,5,9,12,22},
        {2,7,10,13,24},
        {3,9,13,15,27},
        {4,11,15,19,30}
    };

    BinarySearch(matrix, 0, matrix[0].size()-1, 7, solution);

    for (i = 0; i < solution.size(); i++) {
        cout << "Found at (";
        for(j = 0; j < solution[i].size()-1; j++) {
            cout << solution[i][j] << ",";
        }
        cout << solution[i][j]<< ")\n";
    }

    return 0;
}