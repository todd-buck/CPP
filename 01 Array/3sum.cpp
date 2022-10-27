#include <iostream>
#include <vector>
#include <set>

using namespace std;

// Time Complexity: Worst Case (n^2), loops through remainder of array within for loop
// Space Complexity: Stores duplicates, in worst case of every item in the array being included in a pair on space complexity is O(n) 

vector<vector<int>> threeSum(vector<int> nums, int target) {
    //feasability check
    if(nums.size() < 3) return {};

    //use set to eliminate possibility of duplicate triplets
    set<vector<int>> map;

    //sort, required for two-pointer step approach
    sort(nums.begin(), nums.end());

    //loops through nums, takes a two-pointer analysis of the remiaining elements (sorted)
    for(int i = 0; i < nums.size(); i++) {
        int leftStart = i + 1;
        int rightEnd = nums.size()-1;

        while(leftStart < rightEnd) {
            int sum = nums[i] + nums[leftStart] + nums[rightEnd];
            if(sum == target) {
                map.insert({nums[i], nums[leftStart], nums[rightEnd]});
                leftStart++;
                rightEnd--;
            } else if(sum < target) {
                leftStart++;
            } else if(sum > target) {
                rightEnd--;
            }
        }
    }

    //convert set to vector for proper return type
    vector<vector<int>> solution(map.begin(), map.end());

    return solution;
}

int main() {
    int i, j;
    vector<int> nums = {-1,0,1,2,-1,-4};
    int target = 0;

    vector<vector<int>> solution = threeSum(nums, target);
    cout << "[";
    for(i = 0; i < solution.size(); i++) {
        cout << "[";
        for(j = 0; j < solution[i].size()-1; j++) {
            cout << solution[i][j] << ",";
        }
        cout << solution[i][j] << "]";
        if(i != solution.size() - 1) cout << ",";
    }

    cout << "]\n";

    return 0;
}