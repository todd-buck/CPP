#include <iostream>
#include <vector>

using namespace std;

int maxLength(vector<int> array, int k) {
    sort(array.begin(), array.end());
    int kCount = 1;
    int max = -1;
    int end = array.size()-1;

    for(int i = 0; i < array.size(); i++) {
        cout << "array[i]: " << array[i] << "\n";

        while(kCount < k && i < end) {
            kCount += array[end] / array[i];
            end--;
        }

        if(kCount >= k) max = array[i];

        kCount = 1;
        end = array.size()-1;
    }

    return max;
}

int main() {

    vector<int> array = {10,6,5,3};
    
    int k = 4;

    int ml = maxLength(array, k);

    cout << "Max Length: " << ml << "\n";

    return 0;
}