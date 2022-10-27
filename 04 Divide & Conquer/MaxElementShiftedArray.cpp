#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int unknownK(vector<int> arr, int low, int high) {
    if(high - low <= 1) return arr[low];

    int middle = (low + high + 1) / 2;

    
    if(arr[middle] < arr[high]) {       
        return unknownK(arr, low, middle - 1);  //right half is sorted
    } else {
        return unknownK(arr, middle, high);     //left half is sorted
    }
    
}

int knownK(vector<int> arr, int k) {
    return arr[(k-1) % arr.size()];
}

int main() {
    vector<int> arr = {35,42,5,15,27,29};
    int k = 2;

    int known = knownK(arr, k);
    int unknown = unknownK(arr, 0, arr.size() - 1);

    cout << "Known Max: " << known << "\n";
    cout << "Unknown Max: " << unknown << "\n";

    return 0;
}