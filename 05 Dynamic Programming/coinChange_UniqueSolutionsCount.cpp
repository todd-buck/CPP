/*
Description:
    Given a targetSum and an array of potenital denominations, 
    return a number representing the number of unique possible
    combinations that add up to to targetSum

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
        dp[i] = 0;
    }

    dp[0] = 1;

    for(int coin: coins) {
        for(int i = coin; i <= targetSum; i++) {
            dp[i] += dp[i - coin]; 
        }   
    }
        
    return dp[targetSum];

}


int main() {

    deque<int> coins = {1,6,10};
    int targetSum = 12;

    int solution = coinChange(targetSum, coins);

    if(solution > 0) {
        cout << "C(" << targetSum << ") = " << solution << "\n";
    } else {
        cout << "No solution for C(" << targetSum << ")\n";
    }

    return 0;
}

