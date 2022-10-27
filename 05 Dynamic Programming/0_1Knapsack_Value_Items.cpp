/*
Description:
    Given a capacity and an 2D array of items {value, weight}, 
    return a number representing the most value of the optimized
    knapsack

Time Complexity:
    O(m^2*n) where m -> number of items and n -> capacity (building 
    table and potentiall revisiting each item during backtracking)
    
Space Complexity:
    O(m^2*n), need entire table for backtracking to find item indexes
    plus additional indexes array (could store every item given)
*/

#include <iostream>
#include <deque>

using namespace std;

deque<int> fillKnapsack(int capacity, deque<deque<int>> items) {
    deque<int> indexes;
    deque<deque<int>> dp(items.size() + 1, deque<int>(capacity+1, 0));

    for(int row = 1; row <= items.size(); row++) {
        for(int col = 1; col <= capacity; col++) {
            if(col < items[row-1][1]) {
                dp[row][col] = max(dp[row-1][col],dp[row][col-1]);
            } else {
                dp[row][col] = max(dp[row][col-1], dp[row-1][col - items[row-1][1]] + items[row-1][0]);
            }
        }
    }

    int row = items.size();
    int col = capacity;
    int value = dp[items.size()][capacity];

    while(value != 0) {
        if(dp[row][col] != dp[row-1][col]) {
            indexes.push_back(row-1);
            col -= items[row-1][1];
        }

        row -= 1;
        value = dp[row][col];
    }

    return indexes;
}

int calculateValue(deque<int> indexes, deque<deque<int>> items) {
    int value = 0;
    for(int index: indexes) value += items[index][0];
    return value;
}

int main() {
    int capacity = 10;
    deque<deque<int>> items = {
    /*   v,w    */
        {1,2},
        {4,3},
        {5,6},
        {6,7}
    };

    deque<int> indexes = fillKnapsack(capacity, items);
    int value = calculateValue(indexes, items);

    cout << "indexes: ";
    for(int index: indexes) {
        cout << index << " ";
    }
    cout << endl;
    cout << "value: " << value;


    return 0;
}