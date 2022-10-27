/*
Description:
    Given a capacity and an 2D array of items {value, weight}, 
    return a number representing the most value of the optimized
    knapsack

Time Complexity:
    O(m*n) where m -> number of items and n -> capacity
    
Space Complexity:
    O(n), only need to track two arrays of data for logic
*/

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

int fillKnapsack(int capacity, deque<deque<int>> items) {
    deque<int> previous(capacity+1, 0);
    deque<int> current(capacity+1, 0);
    
     for(int row = 1; row <= items.size(); row++) {
        for(int col = 1; col <= capacity; col++) {
            if(col < items[row-1][1]) {
                current[col] = max(previous[col],current[col-1]);
            } else {
                current[col] = max(current[col-1], previous[col - items[row-1][1]] + items[row-1][0]);
            }
        }


        previous = current;
    }

    cout << "current[capacity]: " << current[capacity] << endl;

    return current[capacity];
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

    int solution = fillKnapsack(capacity, items);

    // deque<int> indexes = fillKnapsack(capacity, items);
    // int value = calculateValue(indexes, items);

    // cout << "indexes: ";
    // for(int index: indexes) {
    //     cout << index << " ";
    // }
    // cout << endl;
    // cout << "value: " << value;


    return 0;
}