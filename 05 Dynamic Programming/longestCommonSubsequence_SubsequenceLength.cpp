/*
Description:
    Given two strings, return a number representing the
    length of the longest common non-contiguous subsequence

Time Complexity:
    O(m*n) for two strings of length m and n (respectively)
    
Space Complexity:
    O(n), only need to track two rows of data for logic
    Note: Comments are not space-optimized
*/

#include <iostream>
#include <deque>

using namespace std;

int longestCommonSubsequence(string a, string b) {
    deque<int> previous(b.length());
    deque<int> current(b.length());

    // deque<deque<int>> dp(a.length(), deque<int>(b.length()));

    for(int row = 1; row <= a.length(); row++) {
        for(int col = 1; col <= b.length(); col++) {
            current[col] = max(current[col - 1], previous[col]);
            if(a[row] == b[col]) current[col]++;

            // dp[row][col] = max(dp[row][col-1], dp[row-1][col]);
            // if(a[row] == b[col]) dp[row][col]++;
        }

        previous = current;
    }

    return current[b.length()];
    // return dp[a.length()][b.length()];
}

int main() {
    string a = "ZXVVYZW";
    string b = "XKYKZPW";

    int solution = longestCommonSubsequence(a, b);

    cout << "solution: " << solution << endl;

    return 0;
}