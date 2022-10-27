/*
Description:
    Given numbers m and n, return a number that represents 
    how many unique ways there are to traverse an m*n grid 

Time Complexity:
    O(n*m) to build table
    
Space Complexity:
    O(n*m) to store table
*/

#include <iostream>
#include <deque>

using namespace std;

deque<deque<long long>> intializeTable(int m, int n) {
    deque<deque<long long>> dp;

    for(int x = 0; x <= m; x++) {
        deque<long long> temp;
        for(int y = 0; y <= n; y++) {
            temp.push_back(0);
        }
        dp.push_back(temp);
    }

    return dp;
}

long long gridTraveler(int m, int n) {
    deque<deque<long long>> dp = intializeTable(m,n);

    //Base Case: 1 way to travel through 1x1 array
    dp[1][1] = 1;

    for(int x = 0; x <= m; x++) {
        for(int y = 0; y <= n; y++) {
            if(x + 1 <= m) dp[x+1][y] += dp[x][y];
            if(y + 1 <= n) dp[x][y+1] += dp[x][y];
        }
    }

    return dp[m][n];
}

int main() {

    cout << "Result (1,1): " << gridTraveler(1,1) << endl;
    cout << "Result (2,3): " << gridTraveler(2,3) << endl;
    cout << "Result (3,2): " << gridTraveler(3,2) << endl;
    cout << "Result (3,3): " << gridTraveler(3,3) << endl;
    cout << "Result (18,18): " << gridTraveler(18,18) << endl;

    return 0;
}