#include <iostream>
#include <vector>
#include <map>

using namespace std;


//Time Complexity: Loops through array once, O(n)
//Space Complexity: Stores at most n values in map to perform check, O(n)
vector<int> twoSum(vector<int> nums, int target) {
    //feasability check
    if(nums.size() < 3) return {};

    //holds index of value at map[value]
    map<int, int> map;
    
    for(int i = 0; i < nums.size(); i++) {
        if(map.count(target-nums[i])) {
            return {map[target-nums[i]], i}; 
        }

        map[nums[i]] = i;
    }
    
    return {};
}

int main() {
    vector<int> nums = {2,7,11,15};
    int target = 9;

    vector<int> solution = twoSum(nums, target);

    cout << "[" << solution[0] << "," << solution[1] << "]\n";

    return 0;
}