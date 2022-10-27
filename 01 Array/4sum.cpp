#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

// Time Complexity: O(n^3), two for loops for 1st and 2nd items in potential pairing plus a two-pointer approach to determin 3rd and 4th pair
// Space Complexity: Use of set and vector<vector<int>> to store pairs makes for O(n^2) space complexity

vector<vector<int>> fourSum(vector<int> nums, int target) {
    //feasability check
    if(nums.size() < 4) return {};

    //use set to eliminate possibility of duplicate quadruplets
    set<vector<int>> map;

    //sort, required for two-pointer step approach
    sort(nums.begin(), nums.end());
    
    //loops through nums[i] and nums[j], takes a two-pointer analysis of the remiaining elements (sorted)
    for(int i = 0; i < nums.size(); i++) {
        for(int j = i + 1; j < nums.size(); j++) {
            int sum = target - nums[i] - nums[j];

            int leftStart = j + 1;
            int rightEnd = nums.size()-1;

            while(leftStart < rightEnd) {
                if(nums[leftStart] + nums[rightEnd] == sum) {
                    map.insert({nums[i], nums[j], nums[leftStart], nums[rightEnd]});
                    leftStart++;
                    rightEnd--;
                } else if(nums[leftStart] + nums[rightEnd] > sum) { 
                    rightEnd--;
                } else if(nums[leftStart] + nums[rightEnd] < sum) {
                    leftStart++;
                }
            }
        }
    }

    //convert set to vector<vector<int> for proper return type
    vector<vector<int>> solution(map.begin(), map.end());

    return solution;
}

int main() {
    vector<int> nums = {7,6,4,-1,1,2,8,3,9,10,-3,-4,12,-5,15,-7};
    int targetSum = 16;

    vector<vector<int>> solution = fourSum(nums, targetSum);

    if(solution.size() == 0) cout << "No solution.\n"; 

    for(int i = 0; i < solution.size(); i++) {
            cout << "[";
        for(int j = 0; j < solution[i].size()-1; j++) {
            cout << solution[i][j] << ", ";
        }

        cout << solution[i][solution[i].size()-1]<< "],\n";
    }

    return 0;
}