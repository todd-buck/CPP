#include <iostream>
#include <math.h>

using namespace std;

template <typename keytype>
struct CDA {

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

    CDA() {

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

    CDA(int s) {

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

    CDA(int s, keytype init) {

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

    CDA(const CDA &original) {

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

    ~CDA() {

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
 
    CDA<keytype>& operator=(const CDA &original) {

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

        keytype *newMainArray = new keytype[newSize];
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
        
        this->~CDA();
        
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
struct Node {
    keytype data;
    int degree = 0;

    Node<keytype>* child = NULL;
    Node<keytype>* leftSibling = NULL;
    Node<keytype>* rightSibling = NULL;
    Node<keytype>* parent = NULL;

    Node() {

    }

    Node(keytype k, int d) {
        data = k;
        degree = d;
    }

};

template <typename keytype>
class FibHeap {
    private:

        Node<keytype>* head = NULL;
        Node<keytype>* tail = NULL;
        Node<keytype>* minRoot = NULL;
        Node<keytype>* beforeMin = NULL;
        Node<keytype>* afterMin = NULL;

    public:

        FibHeap() {}

        FibHeap(keytype k[], int s) {
            for(int i = 0; i < s; i++) insert(k[i]);
            consolidate();
        }

        FibHeap(FibHeap &original) {
            Node<keytype>* newRoot;

            for(Node<keytype>* curr = original.head; curr; curr = curr->rightSibling) {
                newRoot = new Node<keytype>(curr->data, curr->degree);
                recursiveCopyConstructor(curr->child, newRoot->rightSibling);
                insert(newRoot);
            }
        }

        void recursiveCopyConstructor(const Node<keytype> *oldNode, Node<keytype>* &newNode) {
            if (oldNode == NULL) return;

            newNode = new Node<keytype>(oldNode->data, oldNode->degree);
            recursiveCopyConstructor(oldNode->child, newNode->child);
            recursiveCopyConstructor(oldNode->rightSibling, newNode->rightSibling);
        }

        Node<keytype> *newNode(const Node<keytype>* &oldNode) {
            Node<keytype> *newNode = new Node<keytype>;
            
            newNode->data = oldNode->data;
            newNode->degree = oldNode->degree;
            newNode->rightSibling = oldNode->rightSibling;
            newNode->leftSibling = oldNode->leftSibling;
            newNode->parent = oldNode->parent;
            newNode->child = oldNode->child;

            return newNode;
        }

        ~FibHeap() {
            head = NULL;
            tail = NULL;
            minRoot = NULL;
            beforeMin = NULL;
            afterMin = NULL;
        }

        FibHeap<keytype>& operator=(const FibHeap &original) {
            Node<keytype>* newRoot;

            for(Node<keytype>* curr = original.head; curr; curr = curr->rightSibling) {
                newRoot = new Node<keytype>(curr->data, curr->degree);
                recursiveCopyConstructor(curr->child, newRoot->rightSibling);
                insert(newRoot);
            }

            return *this;
        }

        keytype peekKey() {
            return minRoot->data;
        }

        keytype extractMin() {

            keytype val = minRoot->data;

            if(head->data == tail->data && !head->child) {
                head = NULL;
                tail = NULL;
                minRoot = NULL;
                return val;
            } else if(minRoot == head) {
                if(head->rightSibling) {
                    head = head->rightSibling;
                } else {
                    head = head->child;
                }
                head->leftSibling = NULL;
            } else if(minRoot == tail) {
                tail = tail->leftSibling;
                tail->rightSibling = NULL;
            } else {
                beforeMin->rightSibling = afterMin;
                afterMin->leftSibling = beforeMin;
            }

            if(minRoot->child) {
                tail->rightSibling = minRoot->child;
                minRoot->leftSibling = tail;
            }
            
            delete minRoot;
            consolidate();
            return val;
        }

        void insert(keytype k) {
            Node<keytype>* newNode = new Node<keytype>;
            newNode->data = k;
            
            if(head == NULL) {
                head = newNode;
                tail = newNode;
                minRoot = newNode;
            } else {
                newNode->leftSibling = tail;
                tail->rightSibling = newNode;
                
                if(newNode->data < minRoot->data) {
                    minRoot = newNode;
                    beforeMin = newNode->leftSibling;
                    afterMin = NULL;
                }

                if(minRoot->rightSibling) afterMin = minRoot->rightSibling;

                tail = newNode;
                
            }
        }

        void insert(Node<keytype>* newNode) {
            if(head == NULL) {
                head = newNode;
                tail = newNode;
                minRoot = newNode;
            } else {
                newNode->leftSibling = tail;
                tail->rightSibling = newNode;
                tail = newNode;

                if(newNode->data < minRoot->data) {
                    minRoot = newNode;
                    beforeMin = newNode->leftSibling;
                    afterMin = NULL;
                }

                if(minRoot->rightSibling) afterMin = minRoot->rightSibling;
            }
        }

        void merge(FibHeap<keytype> &H2) {
            tail->rightSibling = H2.head;
            H2.head->leftSibling = tail;
            tail = H2.tail;

            if(H2.minRoot < minRoot) {
                minRoot = H2.minRoot;
                beforeMin = H2.beforeMin;
                afterMin = H2.afterMin;
            }
            
        }

        void consolidate() {
            CDA<Node<keytype>*> ptrArray(50, NULL);

            for(Node<keytype>* x = head; x; x = x->rightSibling) {
                int d = x->degree;

                while(ptrArray[d] != NULL) {
                    
                    Node<keytype>* y = ptrArray[d];
                    
                    if(y->data < x->data) {
                        swap(x,y);
                        if(x->rightSibling) x->rightSibling = y->rightSibling;
                    }

                    y->rightSibling = x->child;
                    x->child = y;
                    y->parent = x;
                    x->degree++;
                    ptrArray[d] = NULL;
                    d++;
                    
                }
                ptrArray[d] = x;
            }

            minRoot = NULL;
            head = NULL;
            tail = NULL;                                   
            
            for(int i = 0; i < ptrArray.Length(); i++) {
                if(ptrArray[i] != NULL) {
                    insert(ptrArray[i]);
                }      
            }
            
            tail->rightSibling = NULL;
        }

        void printKey() {
            Node<keytype>* curr = head;

            while(curr){
                cout << "B" << curr->degree << endl;
                cout << curr->data;
                recursivePrint(curr->child);
                cout << endl << endl;
                curr = curr->rightSibling;
            }
        }

        void recursivePrint(Node<keytype>* root) {
            if(!root) return;

            cout << " " << root->data;
            recursivePrint(root->child);
            recursivePrint(root->rightSibling);
        }

        void foo() {
            extractMin();
            insert("X");
        }
};

