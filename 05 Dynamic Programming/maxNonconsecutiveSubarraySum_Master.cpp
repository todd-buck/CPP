/*
Description:
    Given an array, return a number representing the
    maximum sum of non-contiguous subarrays

*/


#include <iostream>
#include <vector>

using namespace std;

/*
Recursive (Top-Down), No Memoization
True Brute Force
Time Complexity: O(2^N)

Space Complexity: O(N), recursive call stack

*/
int maxNonNonadjacentSubarraySum_1_helper(vector<int> nums, int i) {
    if(i < 0) return 0;

    return max(maxNonNonadjacentSubarraySum_1_helper(nums, i - 2) + nums[i], maxNonNonadjacentSubarraySum_1_helper(nums, i - 1));
}

int maxNonNonadjacentSubarraySum_1(vector<int> nums) {
    return maxNonNonadjacentSubarraySum_1_helper(nums, nums.size() - 1);
}


/*
Recursive (Top-Down), Has Memoization
Time Complexity: O(N)

Space Complexity: O(N), recursive call stack

*/

int maxNonNonadjacentSubarraySum_2_helper(vector<int> nums, int i, vector<int> &memo) {
    if(i < 0) return 0;
    
    //if solution in memo
    if(memo[i] != -1) return memo[i];

    //if not in memo, calculate solution
    int result = max(maxNonNonadjacentSubarraySum_2_helper(nums, i - 2, memo) + nums[i], maxNonNonadjacentSubarraySum_2_helper(nums, i - 1, memo));

    //store solution in memo
    memo[i] = result;

    return result;
}

int maxNonNonadjacentSubarraySum_2(vector<int> nums) {
    vector<int> memo(nums.size() + 1, -1);
    return maxNonNonadjacentSubarraySum_2_helper(nums, nums.size() - 1, memo);
}


/*
Iterative (Bottom-Up), Local Variables
Time Complexity: O(N)

Space Complexity: O(1), no recursion

*/

int maxNonNonadjacentSubarraySum_3(vector<int> nums) {
    if(nums.size() == 0) return 0;
    int prev1 = 0;
    int prev2 = 0;

    for(int num: nums) {
        int temp = prev1;
        prev1 = max(prev2 + num, prev1);
        prev2 = temp;
    }

    return prev1;
}


/*
Tabulation (Bottom-Up), Entire Array
Time Complexity: O(N)

Space Complexity: O(N) to hold dp array

*/

int maxNonNonadjacentSubarraySum_4(vector<int> nums) {
    if(nums.size() == 0) return 0;
    if(nums.size() == 1) return nums[0];
    vector<int> dp(nums.size()+1);

    dp[0] = nums[0];
    dp[1] = max(dp[0], nums[1]);

    for(int i = 2; i < nums.size(); i++) {
        dp[i] = max(dp[i-1], dp[i - 2] + nums[i]);
    }

    return dp[nums.size() - 1];
}


/*
Tabulation (Bottom-Up), Local Variables
Time Complexity: O(N)

Space Complexity: O(1), only holds local variables

Note: Uses Kadane's algorithms, a solution based on prefix sums

*/
int maxNonNonadjacentSubarraySum_5(vector<int> nums) {
    if(nums.size() == 0) return 0;
    if(nums.size() == 1) return nums[0];
    
    int prev1 = nums[0];
    int prev2 = max(prev1, nums[1]);
    int solution = prev2;

    for(int i = 2; i < nums.size(); i++) {
        solution = max(prev2, prev1 + nums[i]);
        prev1 = prev2;
        prev2 = solution;
    }

    return solution;
}

int main() {

    vector<int> nums = {192,30,337,105,350};

    cout << "maxNonNonadjacentSubarraySum_1: " << maxNonNonadjacentSubarraySum_1(nums) << endl;
    cout << "maxNonNonadjacentSubarraySum_2: " << maxNonNonadjacentSubarraySum_2(nums) << endl;
    cout << "maxNonNonadjacentSubarraySum_3: " << maxNonNonadjacentSubarraySum_3(nums) << endl;
    cout << "maxNonNonadjacentSubarraySum_4: " << maxNonNonadjacentSubarraySum_4(nums) << endl;
    cout << "maxNonNonadjacentSubarraySum_5: " << maxNonNonadjacentSubarraySum_5(nums) << endl;

    return 0;
}