/*
Description:
    Given an array, return a number representing the
    maximum sum of all potential subarrays

Time Complexity:
    O(n) using Kadane's algorithm
    
Space Complexity:
    O(1), only use local variables to store constant values using Kadane's algorithm
*/


#include <iostream>
#include <vector>

using namespace std;

int maxSubsetSum(vector<int> nums) {
    if(nums.size() == 0) return 0;

    int prev = 0;
    int curr = 0;
    int temp;

    for(int num: nums) {
        temp = max(prev + num, curr);
        prev = curr;
        curr = temp;
    }

    return curr;

}

int main() {

    vector<int> nums = {192,30,337,105,350};

    cout << "Solution: " << maxSubsetSum(nums) << endl;

    return 0;
}