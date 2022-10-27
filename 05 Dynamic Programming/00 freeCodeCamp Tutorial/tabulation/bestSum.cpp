/*
Description:
    Given a targetSum and an array of numbers, 
    return an array containing the way to construct
    the targetSum using the fewest possible numbers

Time Complexity:
    O(n*m), where n = size of numbers array and m = targetSum
    
Space Complexity:
    O(n^2), where n -> targetSum (array containing array of numbers)
*/

#include <iostream>
#include <deque>

using namespace std;

deque<int> bestSum(int targetSum, deque<int> numbers) {
    deque<deque<int>> dp;

    for(int i = 0; i <= targetSum; i++) {
        dp.push_back({INT_MIN});
    }

    dp[0] = {};

    for(int i = 0; i <= targetSum; i++) {
        if(dp[i].empty() || dp[i][0] != INT_MIN) {
            for(int number: numbers) {
                deque<int> combination = dp[i];
                if(i + number <= targetSum) {
                combination.push_back(number);
                    if(dp[i + number].empty() || dp[i + number][0] == INT_MIN || combination.size() <= dp[i + number].size()) {
                        dp[i + number] = combination;
                    }
                }
            }
        }
    }

    return dp[targetSum];
}

int main() {
    int targetSum;
    deque<int> numbers;
    deque<int> solution;

    //Test 1
    targetSum = 7;
    numbers = {5,3,4,7};
    solution = bestSum(targetSum, numbers);
    cout << "Test 1: ";
    for(int val: solution) {
        cout << val << " ";
    }
    cout << endl;

    //Test 2
    targetSum = 8;
    numbers = {2,3,5};
    solution = bestSum(targetSum, numbers);
    cout << "Test 2: ";
    for(int val: solution) {
        cout << val << " ";
    }
    cout << endl;

    //Test 3
    targetSum = 8;
    numbers = {1,4,5};
    solution = bestSum(targetSum, numbers);
    cout << "Test 3: ";
    for(int val: solution) {
        cout << val << " ";
    }
    cout << endl;

    //Test 4
    targetSum = 100;
    numbers = {1,2,5,25};
    solution = bestSum(targetSum, numbers);
    cout << "Test 4: ";
    for(int val: solution) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}