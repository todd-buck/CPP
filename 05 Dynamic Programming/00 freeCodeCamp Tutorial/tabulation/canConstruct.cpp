/*
Description:
    Given a target string and an array of word fragments, 
    return a boolean that indicates if the target string
    can be formed using the wordBank

Time Complexity:
    O(n*m^2), where n = number of words in word bank and m = length of target string
    
Space Complexity:
    O(m), where m -> length of target string
*/

#include <iostream>
#include <deque>

using namespace std;

bool canConstruct(string target, deque<string> wordBank) {
    deque<bool> dp;

    for(int i = 0; i <= target.length(); i++) {
        dp.push_back(false);
    }

    dp[0] = true;

    for(int i = 0; i <= target.length(); i++) {
        if(dp[i] == true) {
            for(string word: wordBank) {
                if(target.find(word, i) == i) {
                    dp[i + word.length()] = true;
                }
            }
        }
    }

    return dp[target.length()];
}

int main() {
    string target;
    deque<string> wordBank;
    
    // Test 1 -> true
    target = "abcdef";
    wordBank = {"ab", "abc", "cd", "def", "abcd"};

    cout << "Test 1: " << boolalpha << canConstruct(target, wordBank) << endl;

    // Test 2 -> false
    target = "skateboard";
    wordBank = {"bo", "rd", "ate", "t", "ska", "sk", "boar"};

    cout << "Test 2: " << boolalpha << canConstruct(target, wordBank) << endl;
    
    // Test 3 -> true
    target = "enterapotentpot";
    wordBank = {"a", "p", "ent", "enter", "ot", "o", "t"};

    cout << "Test 3: " << boolalpha << canConstruct(target, wordBank) << endl;
    
    // Test 4 -> false
    target = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef";
    wordBank = {"e", "ee", "eee", "eeee", "eeeee", "eeeeee", "eeeeeee"};

    cout << "Test 4: " << boolalpha << canConstruct(target, wordBank) << endl;

    return 0;
}
