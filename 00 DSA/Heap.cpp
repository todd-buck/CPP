#include <iostream>

using namespace std;

template <typename keytype>
struct CDA2 {

    keytype *mainArray;
    int *indexArray;
    int **ptrToIndexArray;

    int size;
    int capacity;
    int indexArraySize;

    int frontIndex;
    int backIndex;

    keytype initial;     
    bool isInitPresent = false;

    keytype outOfBounds;  

    CDA2
() {

        mainArray = new keytype;
        indexArray = new int;               
        ptrToIndexArray = new int*;           
        size = 0;
        capacity = 1;
        indexArraySize = 0;
        frontIndex = 0;
        backIndex = 0;
        isInitPresent = false;

    }

    CDA2
(int s) {

        mainArray = new keytype[s];
        indexArray = new int[s];               
        ptrToIndexArray = new int*[s];           
        size = s;
        capacity = s;
        indexArraySize = s;
        frontIndex = 0;
        backIndex = s - 1;
        isInitPresent = false;
    }

    CDA2
(int s, keytype init) {

        mainArray = new keytype[s];
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

    CDA2
(const CDA2
 &original) {

        if(!original.isInitPresent) {

            size = original.size;
            capacity = original.capacity;
            frontIndex = original.frontIndex;
            backIndex = original.backIndex;
            
            mainArray = new keytype[capacity];

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

            mainArray = new keytype[original.capacity];
            indexArray = new int[original.capacity];              
            ptrToIndexArray = new int*[original.capacity]; 

            for(int i = 0; i < capacity; i++) {
            mainArray[i] = original.mainArray[i];
            indexArray[i] = original.indexArray[i];
            ptrToIndexArray[i] = original.ptrToIndexArray[i];
            }

        }
    }

    ~CDA2
() {

        if(capacity == 1) {

            delete mainArray;

            if(isInitPresent) {
                delete ptrToIndexArray;
                delete indexArray;
            }

        } else {

            delete [] mainArray;

            if(isInitPresent) {
                delete [] ptrToIndexArray;
                delete [] indexArray;  
            }

        }

        

    }

    keytype& operator[](int i) {

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
  
    CDA2
<keytype>& operator=(const CDA2
 &original) {

        if(!original.isInitPresent) {

            size = original.size;
            capacity = original.capacity;
            frontIndex = original.frontIndex;
            backIndex = original.backIndex;
            
            mainArray = new keytype[original.capacity];

            for(int i = 0; i < original.size; i++) {
                mainArray[i] = original.mainArray[i];
            }

        } else {

            size = original.size;
            capacity = original.capacity;
            indexArraySize = original.indexArraySize;
            frontIndex = original.frontIndex;
            backIndex = original.backIndex;
            initial = original.initial;

            mainArray = new keytype[original.capacity];
            indexArray = new int[original.capacity];              
            ptrToIndexArray = new int*[original.capacity]; 

            for(int i = 0; i < original.size; i++) {
                mainArray[i] = original.mainArray[i];
                indexArray[i] = original.indexArray[i];
                ptrToIndexArray[i] = original.ptrToIndexArray[i];
            }

        }
        return *this;
    }

    void GetBigger() {

        int newSize = capacity*2;

        keytype *newMainArray = new keytype[newSize];
        int *newIndexArray = new int[newSize];              
        int **newPtrToIndexArray = new int*[newSize];       

        for(int i = 0; i < size; i++) {
            newMainArray[i] = mainArray[(frontIndex + i) % capacity];
            newIndexArray[i] = indexArray[(frontIndex + i) % capacity];
            newPtrToIndexArray[i] = ptrToIndexArray[i];
        }

        this->~CDA2
    ();

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

        keytype *newMainArray = new keytype[newSize];
        int *newIndexArray = new int[newSize];
        int **newPtrToIndexArray = new int*[newSize];

        for(int i = 0; i < size; i++) {
            newMainArray[i] = mainArray[(frontIndex + i) % capacity];
            newIndexArray[i] = indexArray[(frontIndex + i) % capacity];
            newPtrToIndexArray[i] = ptrToIndexArray[(frontIndex + i) % capacity];

        }

        this->~CDA2
    ();

        mainArray = newMainArray;
        indexArray = newIndexArray;
        ptrToIndexArray = newPtrToIndexArray;

        frontIndex = 0;
        backIndex = size - 1;

        capacity = newSize;
 

    }

    void AddEnd(keytype v) {
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

    void AddFront(keytype v) {
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
            ptrToIndexArray[backIndex] = nullptr;
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
            ptrToIndexArray[frontIndex] = nullptr;
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
        keytype x = (*this)[high];
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
    
    keytype quickSelect(int low, int high, int k) {
    
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

    keytype Select(int k) {

        int low = 0;
        int high = size - 1;

        return quickSelect(low, high, k);
    }

    void merge(keytype *mainArray, int const low, int const mid, int const high) {

        int const subArrayOne = mid - low + 1;
        int const subArrayTwo = high - mid;
    
        keytype *leftArray = new keytype[subArrayOne];
        keytype *rightArray = new keytype[subArrayTwo];
    
        for (int i = 0; i < subArrayOne; i++)
            leftArray[i] = mainArray[low + i];
        for (int j = 0; j < subArrayTwo; j++)
            rightArray[j] = mainArray[mid + 1 + j];
    
        int indexOfSubArrayOne = 0;
        int indexOfSubArrayTwo = 0; 
        int indexOfMergedArray = low; 
    
        while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
            if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
                mainArray[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
                indexOfSubArrayOne++;
            }
            else {
                mainArray[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
                indexOfSubArrayTwo++;
            }
            indexOfMergedArray++;
        }
 
        while (indexOfSubArrayOne < subArrayOne) {
            mainArray[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
            indexOfMergedArray++;
        }

        while (indexOfSubArrayTwo < subArrayTwo) {
            mainArray[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
            indexOfMergedArray++;
        }
    }

    void mergeSort(keytype *mainArray, int const low, int const high) {
        if (low >= high) {
            return;
        }

        int mid = low + (high - low) / 2;
        mergeSort(mainArray, low, mid);
        mergeSort(mainArray, mid + 1, high);
        merge(mainArray, low, mid, high);
    }

    void align() {
       
        keytype *newMainArray = new keytype[size];
        int *newIndexArray = new int[size];              
        int **newPtrToIndexArray = new int*[size];

        for(int i = 0; i < capacity; i++) {
            newMainArray[i] = mainArray[(frontIndex + i) % capacity];
            newIndexArray[i] = indexArray[(frontIndex + i) % capacity];
            newPtrToIndexArray[i] = ptrToIndexArray[i];
        }
        
        this->~CDA2
    ();
        
        mainArray = newMainArray;
        indexArray = newIndexArray;
        ptrToIndexArray = newPtrToIndexArray;
        
        frontIndex = 0;
        backIndex = size - 1;
        
    }

    void Sort() {
        
        if(size == capacity) {
            mergeSort(mainArray, 0, size - 1);

            frontIndex = 0;
            backIndex = size - 1;
        } else {
            mergeSort(mainArray, 0, size - 1);

        }

    }

    int Search(keytype e) {
        for(int i = 0; i < size; i++) {
            if(mainArray[i] == e) {
                return i;
            }
        }

        return -1;
    }

    int BinSearch(keytype e) {

        int first = 0;
        int last = size - 1;
        int middle;

        while(first <= last) {
            middle = (first+last) / 2;
            
            if(mainArray[middle] == e) {
                return middle;
            } else if(mainArray[middle] > e) {
                last = middle - 1;
            } else if(mainArray[middle] < e) {
                first = middle +1;
            }
        }

        if(first == size) {
            return ~size;
        }

        return ~first;
    }

    void tradePlaces(int a, int b) {
        swap(mainArray[a], mainArray[b]);
    }

};


template <typename keytype>
struct Heap {

        CDA2
    <keytype> *array;

        Heap() {
            array = new CDA2
        <keytype>;
        }

        Heap(keytype k[], int s) {

            array = new CDA2
        <keytype>;

            for(int i = 0; i < s; i++) {
                array->AddEnd(k[i]);
            }

            for(int i = parent(s); i >= 0; i--) {
                minHeapify(i);
            }

            

        }

        ~Heap() {
            delete array;
        }

        keytype peekKey() {
            return array->mainArray[0];
        }

        keytype extractMin() {
            keytype root = array->mainArray[0];       
        
            array->tradePlaces(0, array->size - 1);
            array->DelEnd();

            minHeapify(0);

            return root;
        }

        void insert(keytype k) {
            array->AddEnd(k);

            int i = array->size - 1;

            while(i != 0 && array->mainArray[parent(i)] > array->mainArray[i]) {
                array->tradePlaces(parent(i), i);
                i = parent(i);
            }

        }

        void printKey() {
            for(int i = 0; i < array->size; i++) {
                cout << array->mainArray[i];

                if(i != array->size - 1) {
                    cout << " ";
                } else {
                    cout << endl;
                }
            }
        }

        void minHeapify(int location) {
        
            int left = leftChild(location);
            int right = rightChild(location);
            int smallestVal = location;

            if(left < array->size && array->mainArray[left] < array->mainArray[location]) {
                smallestVal = left;
            }

            if(right < array->size && array->mainArray[right] < array->mainArray[smallestVal]) {
                smallestVal = right;
            }

            if(smallestVal != location) {
                array->tradePlaces(location,smallestVal);
                minHeapify(smallestVal);
            }
        }

        int parent(int i) {
            return (i-1)/2;
        }

        int leftChild(int i) {
            return (2*i + 1);
        }
  
        int rightChild(int i) { 
            return (2*i + 2);
        }

};

