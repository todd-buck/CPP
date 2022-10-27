/*
Description:
    Given a targetSum and an array of potenital denominations, 
    return a number representing the fewest number of denominations
    needed to add up to to targetSum

Time Complexity:
    O(m*targetSum) where m = number of denominations
    
Space Complexity:
    O(n), only need to track one array of data for logic
*/

#include <iostream>
#include <deque>

using namespace std;

int coinChange(int targetSum, deque<int> coins) {
    int dp[targetSum + 1];

    for(int i = 0; i <= targetSum; i++) {
        dp[i] = INT_MAX;
    }

    dp[0] = 0;

    for(int i = 1; i <= targetSum; i++) {
        for(int coin: coins) {
            if(coin <= i) {
                dp[i] = min(dp[i], dp[i - coin] + 1);
            }
        }
    }   
        
    return dp[targetSum] > targetSum ? -1: dp[targetSum];

}


int main() {

    deque<int> coins = {10,50,100};
    int targetSum = 50;

    int solution = coinChange(targetSum, coins);

    if(solution > 0) {
        cout << "C(" << targetSum << ") = " << solution << "\n";
    } else {
        cout << "No solution for C(" << targetSum << ")\n";
    }

    return 0;
}