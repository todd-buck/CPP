#include <iostream>
#include <deque>
#include <vector>
#include <set>
#include <map>

using namespace std;

deque<int> helper(int targetSum, vector<int> numbers, map<int, deque<int>> &memo) {
    if(memo.find(targetSum) != memo.end()) return memo[targetSum];
    if(targetSum == 0) return {0};
    if(targetSum < 0) return {-1};

    for(int num : numbers) {
        deque<int> temp = helper(targetSum - num, numbers, memo);

        int buffer = temp[0];
        if(buffer == 0) temp.pop_front();
        
        if(buffer != -1) {
            temp.push_back(num);
            memo[targetSum] = temp;
            return temp;
        }
        
    }

    memo[targetSum] = {-1};
    return {-1};
}

deque<int> howSum(int targetSum, vector<int> numbers) {
    map<int, deque<int>> memo;

    return helper(targetSum, numbers, memo);
}


int main() {

    for(int i : howSum(7,{2,3})) {
        cout << i << ' ';
    }
    cout << endl;

    for(int i : howSum(7,{5,3,4,7})) {
        cout << i << ' ';
    }
    cout << endl;

    for(int i : howSum(7,{2,4})) {
        cout << i << ' ';
    }
    cout << endl;

    for(int i : howSum(8,{2,3,5})) {
        cout << i << ' ';
    }
    cout << endl;

    for(int i : howSum(300, {7,14})) {
        cout << i << ' ';
    }
    cout << endl;

    return 0;
}