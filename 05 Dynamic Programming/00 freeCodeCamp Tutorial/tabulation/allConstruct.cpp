/*
Description:
    Given a target string and an array of word fragments, 
    return a 2D array representing the all possible ways
    to construct the string from the wordBank

Time Complexity:
    O(n^m), where n = number of words in word bank and m = length of target string
    
Space Complexity:
    O(n^m), where n = number of words in word bank and m = length of target string
*/

#include <iostream>
#include <deque>

using namespace std;

deque<deque<string>> allConstruct(string target, deque<string> wordBank) {
    deque<deque<deque<string>>> dp;

    for(int i = 0; i <= target.size(); i++) {
        dp.push_back({});
    }

    dp[0].push_back({});

    for(int i = 0; i <= target.size(); i++) {
        for(string word: wordBank) {
            string substr = target.substr(i, word.length());
            if(substr == word) {
                deque<deque<string>> temp = dp[i];
                for(deque<string> ways: temp) {
                    ways.push_back(substr);
                    dp[i + word.length()].push_back(ways);
                }
            }
        }
    }

    return dp[target.length()];
}

int main() {
string target;
    deque<string> wordBank;
    deque<deque<string>> solution;
    
    // Test 1
    target = "purple";
    wordBank = {"purp", "p", "ur", "le", "purpl"};
    
    solution = allConstruct(target, wordBank);
    cout << "Test 1:" << endl;
    cout << "{\n";
    for(int i = 0; i < solution.size(); i++) {
        cout << "\t{";
        for(int j = 0; j < solution[i].size(); j++) {
            cout << solution[i][j];
            if(j != solution[i].size() - 1) cout << ", ";
            
        }
        cout << "},\n";
    }
    cout << "}\n\n";

    // Test 2
    target = "abcdef";
    wordBank = {"ab", "abc", "cd", "def", "abcd", "ef", "c"};
    
    solution = allConstruct(target, wordBank);
    cout << "Test 2:" << endl;
    cout << "{\n";
    for(int i = 0; i < solution.size(); i++) {
        cout << "\t{";
        for(int j = 0; j < solution[i].size(); j++) {
            cout << solution[i][j];
            if(j != solution[i].size() - 1) cout << ", ";
            
        }
        cout << "},\n";
    }
    cout << "}\n\n";

    // Test 3 -> {}
    target = "skateboard";
    wordBank = {"bo", "rd", "ate", "t", "ska", "sk", "boar"};

    solution = allConstruct(target, wordBank);
    cout << "Test 3:" << endl;
    cout << "{\n";
    for(int i = 0; i < solution.size(); i++) {
        cout << "\t{";
        for(int j = 0; j < solution[i].size(); j++) {
            cout << solution[i][j];
            if(j != solution[i].size() - 1) cout << ", ";
            
        }
        cout << "},\n";
    }
    cout << "}\n\n";

    
    // Test 4 -> {}
    target = "aaaaaaaaaaaaaaaaaaaaaaaaaaaz";
    wordBank = {"a", "aa", "aaa", "aaaa", "aaaaaa", "aaaaaaa", "aaaaaaaa"};

    solution = allConstruct(target, wordBank);
    cout << "Test 4:" << endl;
    cout << "{\n";
    for(int i = 0; i < solution.size(); i++) {
        cout << "\t{";
        for(int j = 0; j < solution[i].size(); j++) {
            cout << solution[i][j];
            if(j != solution[i].size() - 1) cout << ", ";
            
        }
        cout << "},\n";
    }
    cout << "}\n\n";

    return 0;
}