#include <iostream>
#include <vector>

using namespace std;

void Merge(vector<int> &array, int start, int middle, int end) {
    int leftSize = middle - start + 1;
    int rightSize = end - middle;

    vector<int> leftArray;
    vector<int> rightArray;

    for(int i = 0; i < leftSize; i++) {
        leftArray.push_back(array[start + i]);
    }

    for(int i = 0; i < rightSize; i++) {
        rightArray.push_back(array[middle + 1 + i]);
    }

    int leftIndex = 0;
    int rightIndex = 0;
    int mergedIndex = start;

    while(leftIndex < leftSize && rightIndex < rightSize) {

        if(leftArray[leftIndex] <= rightArray[rightIndex]) {
            array[mergedIndex] = leftArray[leftIndex];
            leftIndex++;
        } else {
            array[mergedIndex] = rightArray[rightIndex];
            rightIndex++;
        }

        mergedIndex++;
    }

    while(leftIndex < leftSize) {
        array[mergedIndex] = leftArray[leftIndex];
        leftIndex++;
        mergedIndex++;
    }

    while(rightIndex < rightSize) {
        array[mergedIndex] = rightArray[rightIndex];
        rightIndex++;
        mergedIndex++;
    }
}

void MergeSort(vector<int> &array, int start, int end) {

    if(start >= end) return;

    int middle = (start + end) / 2;

    MergeSort(array, start, middle);
    MergeSort(array, middle + 1, end);

    Merge(array, start, middle, end);
}



void printList(vector<int> input) {
    for(int i = 0; i < input.size(); i++) {
        cout << input[i] << " ";
    }
}


int main() { 
	vector<int> input = {10,4,15,1,2,12,54}; 
	

	cout << "Unsorted Linked List: "; 
	printList(input); 
	cout << "\n"; 

	MergeSort(input, 0, input.size()-1); 

	cout << "Sorted Linked List: "; 
	printList(input); 

	return 0; 
} 