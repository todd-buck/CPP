#include <iostream>
#include <vector>

using namespace std;

int FindMissingNumber(vector<int> array, int low, int high, int n) {
    if(low > high) return -1;
    
    int middle = (low + high) / 2;

    if(array[middle] - array[middle - 1] != 1) return array[middle] - 1;
    if(array[middle + 1] - array[middle] != 1) return (array[middle] + 1);

    if(array[middle] != middle + 1) {
        return FindMissingNumber(array, low, middle - 1, n);
    } else {
        return FindMissingNumber(array, middle + 1, high, n);
    }

    return -1;
}

int main() {
    int n = 10;

    vector<int> array = {1,2,3,4,5,6,8,9,10,11};

    int missingNumber = FindMissingNumber(array, 0, array.size()-1, n);

    if(missingNumber == -1) {
        cout << "Not Found.\n";
        return 0;
    }

    cout << "Missing Number is: " << missingNumber << "\n";
    return 0;
}