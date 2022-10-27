#include <iostream>
#include <string>
#include <deque>
#include <map>

using namespace std;

deque<deque<string>> helper(string target, deque<string> wordBank, map<string, deque<deque<string>>> &memo) {
    if(memo.find(target) != memo.end()) return memo[target];
    if(target == "") return {{}};

    deque<deque<string>> solution;

    for(string word: wordBank) {
        int index = target.find(word);
        if(index == 0) {
            string remainder = target.substr(index + word.size());
            deque<deque<string>> temp = helper(remainder, wordBank, memo);
            for(deque<string> ways: temp) {
                ways.push_front(word);
                solution.push_front(ways);
            }
        }
    }

    memo[target] = solution;
    return solution;
}

deque<deque<string>> allConstruct(string target, deque<string> wordBank) {
    map<string, deque<deque<string>>> memo;

    return helper(target, wordBank, memo);
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
    target = "aaaaaaaz";
    wordBank = {"a", "aa", "aaa", "aaaa", "aaaaaa"};

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