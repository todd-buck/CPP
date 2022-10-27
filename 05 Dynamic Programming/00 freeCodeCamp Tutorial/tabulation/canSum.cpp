/*
Description:
    Given a targetSum and an array of numbers, 
    return a boolean that indicates if the targetSum
    can be formed using a combination from the numbers array

Time Complexity:
    O(n*m), where n = size of numbers array and m = targetSum
    
Space Complexity:
    O(n), where n -> targetSum
*/

#include <iostream>
#include <deque>

using namespace std;

bool canSum(int targetSum, deque<int> numbers) {
    deque<bool> dp;

    for(int i = 0; i <= targetSum; i++) {
        dp.push_back(false);
    }

    //Base Case: You can always make a sum of 0 by taking no elements
    dp[0] = true;

    for(int i = 0; i <= targetSum; i++) {
        if(dp[i] == true) {
            for(int number: numbers) {
                if(i + number == targetSum) return true;   
                if(i + number < targetSum) dp[i + number] = true;
            }
        }
    }

    return dp[targetSum];
}

int main() {

    cout << "canSum(7, {2,3}) -> " << boolalpha << canSum(7, {5,3,4}) << endl;
    cout << "canSum(7, {5,3,4,7}) -> " << boolalpha << canSum(7, {5,3,4,7}) << endl;
    cout << "canSum(7, {2,4}) -> " << boolalpha << canSum(7, {2,4}) << endl;
    cout << "canSum(8, {2,3,5}) -> " << boolalpha << canSum(8, {2,3,5}) << endl;
    cout << "canSum(300, {7,14}) -> " << boolalpha << canSum(300, {7,14}) << endl;

    return 0;
}