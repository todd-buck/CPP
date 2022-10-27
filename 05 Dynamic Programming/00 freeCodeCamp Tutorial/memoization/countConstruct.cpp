#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int helper(string target, vector<string> wordBank, map<string, int> &memo) {
    if(memo.find(target) != memo.end()) return memo[target];
    if(target == ""){
        // memo[target] = 1;
        return 1;
    } 

    int total = 0;

    for(string word: wordBank) {
        int index = target.find(word);
        if(index == 0) {
            string remainder = target.substr(index + word.length());
            int numWays = helper(remainder, wordBank, memo);
            total += numWays;
        }
    }

    memo[target] = total;
    return total;
}

int canConstruct(string target, vector<string> wordBank) {
    map<string, int> memo;

    return helper(target, wordBank, memo);
}


int main() {
    string target;
    vector<string> wordBank;
    
    // Test 1 -> true
    target = "purple";
    wordBank = {"purp", "p", "ur", "le", "purpl"};
    
    cout << "Test 1: " << canConstruct(target, wordBank) << endl;

    // Test 2 -> true
    target = "abcdef";
    wordBank = {"ab", "abc", "cd", "def", "abcd"};
    
    cout << "Test 2: " << canConstruct(target, wordBank) << endl;

    // Test 3 -> false
    target = "skateboard";
    wordBank = {"bo", "rd", "ate", "t", "ska", "sk", "boar"};

    cout << "Test 3: " << canConstruct(target, wordBank) << endl;
    
    // Test 4 -> true
    target = "enterapotentpot";
    wordBank = {"a", "p", "ent", "enter", "ot", "o", "t"};


    cout << "Test 4: " << canConstruct(target, wordBank) << endl;
    
    // Test 5 -> false
    target = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeef";
    wordBank = {"e", "ee", "eee", "eeee", "eeeee", "eeeeee", "eeeeeee"};

    cout << "Test 5: " << canConstruct(target, wordBank) << endl;
    return 0;
}