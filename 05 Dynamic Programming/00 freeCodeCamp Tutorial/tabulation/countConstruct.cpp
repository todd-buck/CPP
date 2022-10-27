/*
Description:
    Given a target string and an array of word fragments, 
    return a number representing the how many unique ways
    to construct the string from the wordBank

Time Complexity:
    O(n*m^2), where n -> number of words in word bank and m -> length of target string
    
Space Complexity:
    O(m), where m -> length of target string
*/

#include <iostream>
#include <deque>

using namespace std;

int countConstruct(string target, deque<string> wordBank) {
    int dp[target.length() + 1];

    for(int i = 0; i <= target.length(); i++) {
        dp[i] = 0;
    }
 
    dp[0] = 1;

    for(int i = 0; i <= target.length(); i++) {
        for(string word: wordBank) {
            string substr = target.substr(i, word.length());
            if(substr == word) {
                dp[i + word.length()] += dp[i];
            }
        }
    }

    return dp[target.length()];

}

int main() {
    string target;
    deque<string> wordBank;
    
    // Test 2 -> 2
    target = "purple";
    wordBank = {"purp", "p", "ur", "le", "purpl"};
    
    cout << "Test 1: " << countConstruct(target, wordBank) << endl;

    // Test 2 -> 1
    target = "abcdef";
    wordBank = {"ab", "abc", "cd", "def", "abcd"};
    
    cout << "Test 2: " << countConstruct(target, wordBank) << endl;

    // Test 3 -> 0
    target = "skateboard";
    wordBank = {"bo", "rd", "ate", "t", "ska", "sk", "boar"};

    cout << "Test 3: " << countConstruct(target, wordBank) << endl;
    
    // Test 4 -> 4
    target = "enterapotentpot";
    wordBank = {"a", "p", "ent", "enter", "ot", "o", "t"};


    cout << "Test 4: " << countConstruct(target, wordBank) << endl;
    
    // Test 5 -> false
    target = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef";
    wordBank = {"e", "ee", "eee", "eeee", "eeeee", "eeeeee", "eeeeeee"};

    cout << "Test 5: " << countConstruct(target, wordBank) << endl;
    return 0;


    return 0;
}