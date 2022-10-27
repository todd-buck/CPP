#include <iostream>
#include <deque>

using namespace std;

deque<int> howSum(int targetSum, deque<int> numbers) {
    deque<deque<int>> dp;

    for(int i = 0; i <= targetSum; i++) {
        dp.push_back({INT_MIN});
    }

    dp[0] = {};

    for(int i = 0; i <= targetSum; i++) {
        if(dp[i].empty() || dp[i][0] != INT_MIN) {
            for(int number: numbers) {
                dp[i+number] = dp[i];
                dp[i+number].push_front(number);
                if(i + number == targetSum) return dp[i + number];
                
            }
        }
    }

    return {};
}

int main() {
    int targetSum;
    deque<int> numbers;
    deque<int> solution;

    //Test 1
    targetSum = 7;
    numbers = {2,3};
    solution = howSum(targetSum, numbers);
    cout << "Test 1: ";
    for(int val: solution) {
        cout << val << " ";
    }
    cout << endl;

    //Test 2
    targetSum = 7;
    numbers = {5,3,4,7};
    solution = howSum(targetSum, numbers);
    cout << "Test 2: ";
    for(int val: solution) {
        cout << val << " ";
    }
    cout << endl;

    //Test 3
    targetSum = 7;
    numbers = {2,4};
    solution = howSum(targetSum, numbers);
    cout << "Test 3: ";
    for(int val: solution) {
        cout << val << " ";
    }
    cout << endl;

    //Test 4
    targetSum = 8;
    numbers = {2,3,5};
    solution = howSum(targetSum, numbers);
    cout << "Test 4: ";
    for(int val: solution) {
        cout << val << " ";
    }
    cout << endl;

    //Test 5
    targetSum = 300;
    numbers = {7,14};
    solution = howSum(targetSum, numbers);
    cout << "Test 5: ";
    for(int val: solution) {
        cout << val << " ";
    }
    cout << endl;

    return 0;
}