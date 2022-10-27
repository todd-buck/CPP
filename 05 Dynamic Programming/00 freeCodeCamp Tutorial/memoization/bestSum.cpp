#include <iostream>
#include <deque>
#include <map>

using namespace std;

deque<int> helper(int targetSum, deque<int> numbers, map<int, deque<int>> &memo) {
    deque<int> failure = {-1};

    if(memo.find(targetSum) != memo.end()) return memo[targetSum];
    
    if(targetSum == 0) return {};
    if(targetSum < 0) return failure;

    deque<int> shortest = failure;

    for(int num : numbers) {
        deque<int> temp = helper(targetSum - num, numbers, memo);

        if(temp != failure) {
            temp.push_back(num);
            if(shortest == failure || temp.size() <= shortest.size()) shortest = temp; 
        }
    }

    memo[targetSum] = shortest;
    return shortest;
}

deque<int> bestSum(int targetSum, deque<int> numbers) {
    map<int, deque<int>> memo;

    return helper(targetSum, numbers, memo);
}

int main() {
    deque<int> testA;
    deque<int> testB = {};

    for(int i : bestSum(7,{5,3,4,7})) {
        cout << i << ' ';
    }
    cout << endl;

    for(int i : bestSum(8,{2,3,5})) {
        cout << i << ' ';
    }
    cout << endl;

    for(int i : bestSum(8,{1,4,5})) {
        cout << i << ' ';
    }
    cout << endl;

    for(int i : bestSum(100, {1,2,5,25})) {
        cout << i << ' ';
    }
    cout << endl;

    return 0;

    return 0;
}