#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
using namespace std;

template <typename keytype>
struct Node {
    keytype key;
    float priority;
    int subtreeSize = 1;
    Node<keytype> *leftChild = NULL;
    Node <keytype> *rightChild = NULL;
};

template <typename keytype>
class Treap {
    private:

    Node<keytype> *root = NULL;

    public:

    //project functions
    Treap() {
        srand(time(NULL));
    };

    Treap(keytype k[], float p[], int s) {
        for(int i = 0; i < s; i++) insert(k[i],p[i]);
    }

    Treap(const Treap &original) {
        root = recursiveCopyConstructor(original.root);
    }

    ~Treap() {
        delete root->leftChild;
        delete root->rightChild;
        delete root;
        root = NULL;
    }

    Treap<keytype>& operator=(const Treap &original) {
        root = recursiveCopyConstructor(original.root);
        return *this;   
    }

    float search(keytype k) {
        return recursiveSearch(root,k);
    }

    void insert(keytype k, float p) {   
        recursiveInsert(root, k, p);
    }

    void insert(keytype k) {
        recursiveInsert(root, k);
    }

    int remove(keytype k) {
        return search(k) == -1 ? 0 : recursiveRemove(root, k);
    }

    int rank(keytype k) {
        return search(k) == -1 ? 0 : recursiveRank(root, k);
    }

    keytype select(int pos) {
        return recursiveSelect(root, pos);
    }

    keytype successor(keytype k) {
        return rank(k) > root->subtreeSize ? select(rank(k)) : select(rank(k) + 1);
    }

    keytype predecessor(keytype k) {
        return rank(k) < 1 ? select(rank(k)) : select(rank(k) - 1);
    }

    int size() {
        return root->subtreeSize;
    }

    void preorder() {
        recursivePreorder(root);
        cout << endl;
    }

    void inorder() {
        recursiveInorder(root);
        cout << endl;
    }

    void postorder() {
        recursivePostorder(root);
        cout << endl;
    }

    //recursive functions
    Node<keytype> *recursiveCopyConstructor(const Node<keytype> *oldRoot) {
        if(!oldRoot) return NULL;

        Node<keytype> *newRoot = newNode(oldRoot->key, oldRoot->priority);
        newRoot->leftChild = recursiveCopyConstructor(oldRoot->leftChild);
        newRoot->rightChild = recursiveCopyConstructor(oldRoot->rightChild);

        return newRoot;
    }

    float recursiveSearch(Node<keytype>* root, keytype k) {
        if(!root) return -1;

        if(k < root->key) return recursiveSearch(root->leftChild, k);
        
        if(k > root->key) return recursiveSearch(root->rightChild, k);
        

        if(k == root->key) return root->priority;

        return -1;
    }

    void recursiveInsert(Node<keytype>* &root, keytype k, float p) {
        if(!root) {
            root = newNode(k,p);
            return;
        }

        if(k < root->key) {
            root->subtreeSize++;
            if(root->leftChild) {
                recursiveInsert(root->leftChild,k,p);
            } else {
                root->leftChild = newNode(k,p);
            }
        }

        if(k > root->key) {
            root->subtreeSize++;
            if(root->rightChild) {
                recursiveInsert(root->rightChild,k,p);
            } else {
                root->rightChild = newNode(k,p);
            }
        }
        
        if(root->leftChild && root->leftChild->priority <= root->priority) rotateRight(root);
        
        if(root->rightChild && root->rightChild->priority <= root->priority) rotateLeft(root);

    }

    void recursiveInsert(Node<keytype>* &root, keytype k) {
        if(!root) {
            root = newNode(k);
            return;
        }

        if(k < root->key) {
            root->subtreeSize++;
            if(root->leftChild) {
                recursiveInsert(root->leftChild,k);
            } else {
                root->leftChild = newNode(k);
            }
        }

        if(k > root->key) {
            root->subtreeSize++;
            if(root->rightChild) {
                recursiveInsert(root->rightChild,k);
            } else {
                root->rightChild = newNode(k);
            }
        }

        if(root->leftChild && root->leftChild->priority <= root->priority) rotateRight(root);

        if(root->rightChild && root->rightChild->priority <= root->priority) rotateLeft(root);
    }

    int recursiveRemove(Node<keytype>* &root, keytype k) {
        if(k < root->key) {
            root->subtreeSize--;
            return recursiveRemove(root->leftChild, k);
        }

        if(k > root->key) {
            root->subtreeSize--;
            return recursiveRemove(root->rightChild, k);
        }

        if(k == root->key) {
            if(!root->leftChild && !root->rightChild) {
                delete root;
                root = NULL;
                return 1;
            } else if(!root->leftChild || !root->rightChild) {
                Node<keytype> *oldRoot = root;
                Node<keytype> *newRoot = root->leftChild;
                
                if(!root->leftChild) {
                    newRoot = root->rightChild;
                }

                root = newRoot;
                return 1;
            } else {
                if(root->leftChild->priority > root->rightChild->priority) {
                    rotateLeft(root);
                    root->subtreeSize--;
                    return recursiveRemove(root->leftChild, k);
                } else {
                    rotateRight(root);
                    root->subtreeSize--;
                    return recursiveRemove(root->rightChild, k);           
                }
            }
        }

        return 0;
    }
        
    int recursiveRank(Node<keytype> *root, keytype k) {
        if(k == root->key) {
            return checkSize(root->leftChild) + 1; 
        } else if(k < root->key) {
            return recursiveRank(root->leftChild,k);
        } else {
            int rightSize = recursiveRank(root->rightChild, k);
            return checkSize(root->leftChild) + 1 + rightSize;
        }
        
        return 0;
    }

    keytype recursiveSelect(Node<keytype> *root, int pos) {
        int nodesVisited = root->leftChild ? root->leftChild->subtreeSize + 1 : 1;
        
        if(pos == nodesVisited) return root->key;

        if(root->leftChild && pos < nodesVisited) return recursiveSelect(root->leftChild, pos);
            
        if(root->rightChild && pos > nodesVisited) return recursiveSelect(root->rightChild, pos - nodesVisited);
        
        return root->key;
    }

    void recursivePreorder(Node<keytype> *root) {
        if(root == NULL) return;
        
        cout << root->key << " ";
        recursivePreorder(root->leftChild);
        recursivePreorder(root->rightChild);
    }

    void recursiveInorder(Node<keytype> *root) {
        if(root == NULL) return;
        
        recursiveInorder(root->leftChild);
        cout << root->key << " ";
        recursiveInorder(root->rightChild);
    }

    void recursivePostorder(Node<keytype> *root) {
        if(root == NULL) return;

        recursivePostorder(root->leftChild);
        recursivePostorder(root->rightChild);
        cout << root->key << " ";
    }

    //helper functions
    Node<keytype> *newNode(keytype k) {
        Node<keytype> *node = new Node<keytype>;
        
        node->key = k;
        node->priority = (float) rand() / (float) RAND_MAX;

        return node;
    }

    Node<keytype> *newNode(keytype k, float p) {
        Node<keytype> *node = new Node<keytype>;
        
        node->key = k;
        node->priority = p;

        return node;
    }

    void rotateRight(Node<keytype>* &oldRoot) {
        Node<keytype> *newRoot = oldRoot->leftChild;
        Node<keytype> *stepChild = newRoot->rightChild;
        
        newRoot->rightChild = oldRoot;
        newRoot->subtreeSize = oldRoot->subtreeSize;

        oldRoot->leftChild = stepChild;
        oldRoot->subtreeSize = 1 + checkSize(oldRoot->leftChild) + checkSize(oldRoot->rightChild);

        oldRoot = newRoot;
    }

    void rotateLeft(Node<keytype>* &oldRoot) {
        Node<keytype> *newRoot = oldRoot->rightChild;
        Node<keytype> *stepChild = newRoot->leftChild;        

        newRoot->leftChild = oldRoot;
        newRoot->subtreeSize = oldRoot->subtreeSize;

        oldRoot->rightChild = stepChild;
        oldRoot->subtreeSize = 1 + checkSize(oldRoot->leftChild) + checkSize(oldRoot->rightChild);

        oldRoot = newRoot;
    }

    int checkSize(Node<keytype> *root) {
        return root ? root->subtreeSize : 0;
    } 
};