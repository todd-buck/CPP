#include <iostream>

using namespace std;

class Node {
    public: 
        int data;
        Node* next;
};

Node* Merge(Node *left, Node *right) {
    Node *result;

    if(!left) {
        return right;
    } else if(!right) {
        return left;
    }

    if(left->data <= right->data) {
        result = left;
        result->next = Merge(left->next, right);
    } else {
        result = right;
        result->next = Merge(left, right->next);
    }

    return result;
}

void Split(Node *source, Node **leftStart, Node **rightStart) {
    Node *leftEnd;
    Node *rightEnd;

    leftEnd = source;
    rightEnd = source->next;

    while(rightEnd) {
        rightEnd = rightEnd->next;
        if(rightEnd) {
            leftEnd = leftEnd->next;
            rightEnd = rightEnd->next;
        }
    }

    *leftStart = source;
    *rightStart = leftEnd->next;
    leftEnd->next = NULL;
}

void MergeSort(Node **input) {
    Node *head = *input;
    Node *left;
    Node *right;

    if(head == NULL || head->next == NULL) return;

    Split(head, &left, &right);

    MergeSort(&left);
    MergeSort(&right);

    *input = Merge(left, right);
}

// Printing List.
void printList(Node* tnode) { 
	while (tnode != NULL) { 
		cout << tnode->data << " "; 
		tnode = tnode->next; 
	} 
} 


void push(Node** input, int val) { 
	Node* temp = new Node(); 

	temp->data = val; 
	temp->next = *input; 

	*input = temp; 
} 

int main() { 
	Node* input = NULL; 
	Node* solution = NULL; 

  // List: 10->4->15->1->2->12->54
	push(&input, 54); 
	push(&input, 12); 
	push(&input, 2); 
	push(&input, 1); 
	push(&input, 15); 
	push(&input, 4);
    push(&input, 10); 

	cout << "Unsorted Linked List: "; 
	printList(input); 
	cout << "\n"; 

	MergeSort(&input); 

	cout << "Sorted Linked List: "; 
	printList(input); 

	return 0; 
} 