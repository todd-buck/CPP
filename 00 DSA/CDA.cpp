#include <iostream>
#include <time.h>
using namespace std;

template <typename elmtype>
class CDA {
    private:

    elmtype *mainArray;
    int *indexArray;
    int **ptrToIndexArray;

    int size;
    int capacity;
    int indexArraySize;

    int frontIndex;
    int backIndex;

    elmtype initial;     
    bool isInitPresent = false;

    elmtype outOfBounds; 

    public: 

    CDA() {

        mainArray = new elmtype;
        indexArray = new int;               
        ptrToIndexArray = new int*;           
        size = 0;
        capacity = 1;
        indexArraySize = 0;
        frontIndex = 0;
        backIndex = 0;
        isInitPresent = false;

    }

    CDA(int s) {

        mainArray = new elmtype[s];
        indexArray = new int[s];               
        ptrToIndexArray = new int*[s];           
        size = s;
        capacity = s;
        indexArraySize = s;
        frontIndex = 0;
        backIndex = s - 1;
        isInitPresent = false;
    }

    CDA(int s, elmtype init) {

        mainArray = new elmtype[s];
        indexArray = new int[s];
        ptrToIndexArray = new int*[s];  
        size = s;
        capacity = s;
        indexArraySize = 0;
        frontIndex = 0;
        backIndex = s - 1;
        initial = init;
        isInitPresent = true;

    }

    CDA(const CDA &original) {

        if(!original.isInitPresent) {

            size = original.size;
            capacity = original.capacity;
            frontIndex = original.frontIndex;
            backIndex = original.backIndex;
            
            mainArray = new elmtype[capacity];

            for(int i = 0; i < capacity; i++) {
                mainArray[i] = original.mainArray[i];
            }

        } else {

            size = original.size;
            capacity = original.capacity;
            indexArraySize = original.indexArraySize;
            frontIndex = original.frontIndex;
            backIndex = original.backIndex;
            initial = original.initial;

            mainArray = new elmtype[original.capacity];
            indexArray = new int[original.capacity];              
            ptrToIndexArray = new int*[original.capacity]; 

            for(int i = 0; i < capacity; i++) {
                if(original.ptrToIndexArray[(i + frontIndex) % capacity] >= &original.indexArray[0] && original.ptrToIndexArray[(i + frontIndex) % capacity] <= &original.indexArray[indexArraySize - 1] && *original.ptrToIndexArray[(i + frontIndex) % capacity] == (i + frontIndex) % capacity) {     
                    mainArray[i] = original.mainArray[i];
                }
                else mainArray[i] = initial;
                indexArray[i] = original.indexArray[i];
                ptrToIndexArray[i] = original.ptrToIndexArray[i];
            }

        }
    }

    ~CDA() {

        if(capacity == 1) {

            delete mainArray;

            if(isInitPresent) {
                delete ptrToIndexArray;
                delete indexArray;
            }

        } else {
 
            delete [] mainArray;
            // Note: Calls destructor upon exit of foo(A) function in
            //       Phase1Main, outputs a segmentation fault when
            //       delete [] mainArray is called.


            if(isInitPresent) {
                delete [] ptrToIndexArray;
                delete [] indexArray;  
            }

        }

        

    }

    elmtype& operator[](int i) {

        if((i < 0 || i > capacity - 1)) {
            return outOfBounds;                
        }

        if(!isInitPresent) {
            return mainArray[(i + frontIndex) % capacity];
        } else {

            if(((void*)ptrToIndexArray[(i + frontIndex) % capacity] >= &indexArray[0] && (void*)ptrToIndexArray[(i + frontIndex) % capacity] <= &indexArray[indexArraySize - 1])) {   
                
                if(*ptrToIndexArray[(i + frontIndex) % capacity] == (i + frontIndex) % capacity) {      
                    return mainArray[(i + frontIndex) % capacity];
                }

                mainArray[(i + frontIndex) % capacity] = initial;
                indexArray[indexArraySize] = (frontIndex + i) % capacity;
                ptrToIndexArray[(i + frontIndex) % capacity] = &indexArray[indexArraySize];

                indexArraySize++;
                return mainArray[(i + frontIndex) % capacity];
            }
                mainArray[(i + frontIndex) % capacity] = initial;
                indexArray[indexArraySize] = (frontIndex + i) % capacity;
                ptrToIndexArray[(i + frontIndex) % capacity] = &indexArray[indexArraySize];

                indexArraySize++;
                return mainArray[(i + frontIndex) % capacity];
        }
    }

    CDA<elmtype>& operator=(const CDA &original) {

        if(!original.isInitPresent) {

            size = original.size;
            capacity = original.capacity;
            frontIndex = original.frontIndex;
            backIndex = original.backIndex;
            
            mainArray = new elmtype[original.capacity];

            for(int i = 0; i < original.size; i++) {
                mainArray[(frontIndex + i) % capacity] = original.mainArray[(frontIndex + i) % capacity];
            }

        } else {

            size = original.size;
            capacity = original.capacity;
            indexArraySize = original.indexArraySize;
            frontIndex = original.frontIndex;
            backIndex = original.backIndex;
            initial = original.initial;

            mainArray = new elmtype[original.capacity];
            indexArray = new int[original.capacity];              
            ptrToIndexArray = new int*[original.capacity]; 

            for(int i = 0; i < original.size; i++) {
                mainArray[(frontIndex + i) % capacity] = original.mainArray[(frontIndex + i) % capacity];
                indexArray[i] = original.indexArray[(frontIndex + i) % capacity];
                ptrToIndexArray[i] = original.ptrToIndexArray[i];
            }

        }

        return *this;
    }

    void GetBigger() {

        int newSize = capacity*2;

        elmtype *newMainArray = new elmtype[newSize];
        int *newIndexArray = new int[newSize];              
        int **newPtrToIndexArray = new int*[newSize];       

        for(int i = 0; i < size; i++) {
            newMainArray[i] = mainArray[(frontIndex + i) % capacity];
            newIndexArray[i] = indexArray[(frontIndex + i) % capacity];
            newPtrToIndexArray[i] = ptrToIndexArray[i];
        }

        this->~CDA();

        mainArray = newMainArray;
        indexArray = newIndexArray;
        ptrToIndexArray = newPtrToIndexArray;

        frontIndex = 0;
        backIndex = size - 1;

        capacity = newSize;

    }

    void GetSmaller() {

        if(capacity <= 4) {
            return;
        }

        int newSize = capacity/2;

        elmtype *newMainArray = new elmtype[newSize];
        int *newIndexArray = new int[newSize];
        int **newPtrToIndexArray = new int*[newSize];

        for(int i = 0; i < size; i++) {
            newMainArray[i] = mainArray[(frontIndex + i) % capacity];
            newIndexArray[i] = indexArray[(frontIndex + i) % capacity];
            newPtrToIndexArray[i] = ptrToIndexArray[(frontIndex + i) % capacity];

        }

        this->~CDA();

        mainArray = newMainArray;
        indexArray = newIndexArray;
        ptrToIndexArray = newPtrToIndexArray;

        frontIndex = 0;
        backIndex = size - 1;

        capacity = newSize;
 

    }

    void AddEnd(elmtype v) {
        if(size == capacity) { GetBigger(); }

        if(!isInitPresent) {
            backIndex = (backIndex + capacity + 1) % capacity;
            mainArray[backIndex] = v;
            size++;
        } else {
            backIndex = (backIndex + capacity + 1) % capacity;

            mainArray[backIndex] = v;
            indexArray[indexArraySize] = backIndex;
            ptrToIndexArray[backIndex] = &indexArray[indexArraySize];

            size++;
            indexArraySize++;
        }

    }

    void AddFront(elmtype v) {
        if(size == capacity) { GetBigger(); }

        if(!isInitPresent) {
            frontIndex = (frontIndex + capacity - 1) % capacity;
            mainArray[frontIndex] = v;
            size++;

        } else {
            
            frontIndex = (frontIndex + capacity - 1) % capacity;

            mainArray[frontIndex] = v;
            indexArray[indexArraySize] = frontIndex;
            ptrToIndexArray[frontIndex] = &indexArray[indexArraySize];

            size++;
            indexArraySize++;
        }

    }

    void DelEnd() {

        if(!isInitPresent) {
            backIndex = (backIndex - 1) % capacity;
            size--;
        } else {
            ptrToIndexArray[backIndex] = NULL;
            backIndex = (backIndex - 1) % capacity;
            size--;
            indexArraySize--;
        }

        if(size <= capacity/4) {
            GetSmaller();
        }

        size = max(size++, 0);

    }

    void DelFront() {

        if(!isInitPresent) {
            frontIndex = (frontIndex + 1) % capacity;
            size--;
        } else {
            ptrToIndexArray[frontIndex] = NULL;
            frontIndex = (frontIndex + 1) % capacity;
            size--;
            indexArraySize--;
        }

        if(size <= capacity/4) {
            GetSmaller();
        }

        size = max(size++, 0);

    }

    int Length() {
        return size;
    }  

    int Capacity() {
        return capacity;
    }

    int partition(int low, int high) {
        srand(time(NULL));
        swap((*this)[rand() % (high - low + 1) + low], (*this)[high]);
        elmtype x = (*this)[high];
        int i = low;

            for (int j = low; j <= high - 1; j++) {
            if ((*this)[j] <= x) {
                swap((*this)[i], (*this)[j]);
                i++;
                }
            }

        swap((*this)[i], (*this)[high]);
        return i;
    }
    
    elmtype quickSelect(int low, int high, int k) {
    
        if ((k > 0) && (k <= high - low + 1)) {


            int index = partition(low, high);
    
            if (index - low == k - 1) {
                 return (*this)[index];
            }
    
            if (index - low > k - 1) {
                return quickSelect(low, index - 1, k);
            }
          
            return quickSelect(index + 1, high, (k - index + low - 1));
        }
      
        return -1;
    }

    elmtype Select(int k) {

        int low = 0;
        int high = size - 1;

        return quickSelect(low, high, k);
    }

    void merge(int const low, int const mid, int const high) {

        int const subArrayOne = mid - low + 1;
        int const subArrayTwo = high - mid;
    
        elmtype *leftArray = new elmtype[subArrayOne];
        elmtype *rightArray = new elmtype[subArrayTwo];
    
        for (int i = 0; i < subArrayOne; i++)
            leftArray[i] = (*this)[low + i];
        for (int j = 0; j < subArrayTwo; j++)
            rightArray[j] = (*this)[mid + 1 + j];
    
        int indexOfSubArrayOne = 0;
        int indexOfSubArrayTwo = 0; 
        int indexOfMergedArray = low; 
    
        while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
            if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
                (*this)[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            }
            else {
                (*this)[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }
            indexOfMergedArray++;
        }
 
        while (indexOfSubArrayOne < subArrayOne) {
            (*this)[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
            indexOfMergedArray++;
        }

        while (indexOfSubArrayTwo < subArrayTwo) {
            (*this)[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
            indexOfMergedArray++;
        }

    }

    void mergeSort(int const low, int const high) {
    
        if (low >= high) {
            return;
        }

        int mid = low + (high - low) / 2;
        mergeSort(low, mid);
        mergeSort(mid + 1, high);
        merge(low, mid, high);
        
    }

    void Sort() {
        mergeSort(0, size - 1);
    }

    int Search(elmtype e) {

        for(int i = 0; i < size; i++) {
            if((*this)[i] == e) {
                return i;
            }
        }

        return -1;
    }

    int binarySearch(int low, int high, int x) {

        if (high >= low) {
            if (high - low + 1 < 3){
                for (int i = low; i <= high; i++){
                    if ((*this)[i] == x) return i;
                    if ((*this)[i] > x) return ~i;
                }
            }
            int mid = low + (high - low) / 2;
    
            if ((*this)[mid] == x)
                return mid;
    
            if ((*this)[mid] > x)
                return binarySearch(low, mid - 1, x);
    
            return binarySearch(mid + 1, high, x);
        }
    
        return ~size;
    }

    int BinSearch(elmtype e) {
        return binarySearch(0, size - 1, e);
    }


};

