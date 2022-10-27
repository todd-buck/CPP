/*
Description:
    Given two strings, return an array representing
    the longest common non-contiguous subsequence

Time Complexity:
    O(m*n) for two strings of length m and n (respectively)
    
Space Complexity:
    O(n), only need to track two rows of data for logic
    Note: Comments are not space-optimized
*/

#include <iostream>
#include <deque>

using namespace std;

string longestCommonSubsequence(string a, string b) {
    deque<string> previous(b.length() + 1);
    deque<string> current(b.length() + 1);

    // deque<deque<string>> dp(a.length()+1, deque<string>(b.length()+1));

    for(int row = 1; row <= a.length(); row++) {
        for(int col = 1; col <= b.length(); col++) {
            if(a[row-1] == b[col-1]) {
                current[col] = previous[col-1];
                current[col] += a[row - 1];

                // dp[row][col] = dp[row-1][col-1];
                // dp[row][col] += a[row-1];
            } else {
                if(current[col-1].length() >= previous[col].length()) {
                    current[col] = current[col-1];
                } else {
                    current[col] = previous[col];
                }

                // if(dp[row][col-1].length() >= dp[row-1][col].length()) {
                //     dp[row][col] = dp[row][col-1];
                // } else {
                //     dp[row][col] = dp[row-1][col];
                // }
            }
        }
        previous = current;
    }
    
    return current[b.length()];
    //return dp[a.length()][b.length()];
}

int main() {
    string b = "ZXVVYZW";
    string a = "XKYKZPW";

    string solution = longestCommonSubsequence(a, b);

    cout << "Solution:\n\t[";

    for(char letter: solution) {
        cout << "\"" << letter << "\"";
        if(letter != solution[solution.size() - 1]) {
            cout << ", ";
        }
    }

    cout << "]\n";

    return 0;
}