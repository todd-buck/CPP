#include <iostream>
#include <vector>
#include <map>

using namespace std;

bool helper(int targetSum, vector<int> numbers, map<int, bool> &memo) {
    if(memo.find(targetSum) != memo.end()) return memo[targetSum];
    if(targetSum == 0) return true;
    if(targetSum < 0) return false;
    
    for(int num : numbers) {
        if(helper(targetSum - num, numbers, memo) == true) {
            memo[targetSum] = true;
            return true;
        } else {
            memo[targetSum] = false;
        }
    }

    memo[targetSum] = false;
    return false;
}

bool canSum(int targetSum, vector<int> numbers) {
    map<int, bool> memo;

    return helper(targetSum, numbers, memo);
}

int main() {

    cout << boolalpha << canSum(7, {2,3}) << endl;          //true
    cout << boolalpha << canSum(7, {5,3,4,7}) << endl;      //true
    cout << boolalpha << canSum(7, {2,4}) << endl;          //false
    cout << boolalpha << canSum(8, {2,3,5}) << endl;        //true
    cout << boolalpha << canSum(300, {7,14}) << endl;       //false


    return 0;
}