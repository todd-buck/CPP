#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

bool helper(string target, vector<string> wordBank, map<string, bool> &memo) {
    if(memo.find(target) != memo.end()) return memo[target];
    if(target == ""){
        memo[target] = true;
        return true;
    } 

    for(string word: wordBank) {
        int index = target.find(word);
        if(index == 0) {
            string remainder = target.substr(index + word.length());
            if(helper(remainder, wordBank, memo) == true) {
                memo[target] = true;
                return true;
            }
        }
    }

    memo[target] = false;
    return false;
}

bool canConstruct(string target, vector<string> wordBank) {
    map<string, bool> memo;

    return helper(target, wordBank, memo);
}


int main() {
    string target;
    vector<string> wordBank;
    
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
