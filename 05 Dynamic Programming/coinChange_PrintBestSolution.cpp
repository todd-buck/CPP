/*
Description:
    Given a targetSum and an array of potenital denominations, 
    return an array representing the fewest number of coins that
    sums to the targetSum

Time Complexity:
    O(m*targetSum^2) where m = number of denominations
    
Space Complexity:
    O(m^2), array holds best combinations for targetSum range
*/

#include <iostream>
#include <deque>

using namespace std;

deque<int> coinChange(int targetSum, deque<int> coins) {
    deque<deque<int>> dp;

    for(int i = 0; i <= targetSum; i++) {
        dp.push_back({-1});
    }

    dp[0] = {};

    for(int i = 0; i <= targetSum; i++) {
        if(dp[i].empty() || dp[i][0] != -1) {
            for(int coin: coins) {
                deque<int> combination = dp[i];
                if(i + coin <= targetSum) {
                    combination.push_back(coin);
                    if(dp[i + coin].empty() || dp[i + coin][0] == -1 || combination.size() <= dp[i + coin].size()) {
                        dp[i + coin] = combination;
                    }
                }
            }
        }
    }

    return dp[targetSum];
}

int main() {
    int targetSum = 40;
    deque<int> coins = {10, 50, 100, 500, 1000, 2000};

    
    deque<int> solution = coinChange(targetSum, coins);
    
    for(int coin: solution) {
        cout << coin << " "; 
    }

    cout << endl;

    return 0;
}