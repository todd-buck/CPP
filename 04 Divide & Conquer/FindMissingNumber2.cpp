#include <iostream>
#include <vector>

using namespace std;

int findSmallestMissingNumber(vector<int> nums, int low, int high) {
    int middle = (low + high) / 2;
    
    // no missing numbers on left side since indexes match, go right and look
    if(nums[middle] - 1 == middle) return findSmallestMissingNumber(nums, middle + 1, high);
        
    //if array before middle is index matched, then one more than left value will be smallest missing.     
    if(nums[middle - 1] == middle) return nums[middle - 1] + 1;

    // failed go right check, misaligned indexes, go left and look for smallest value    
    return findSmallestMissingNumber(nums, low, middle);
    
}

int main() {
    vector<int> nums = {1, 2, 4, 5, 7, 8, 9, 10, 11};
                    //  0  1  2  3  4  5  6  7   8
    int n = nums.size();
    int m = nums[nums.size()-1];


    int solution = findSmallestMissingNumber(nums, 0, nums.size() - 1);

    cout << "Smallest Missing Number: " << solution << endl;


    return 0;
}