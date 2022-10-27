#include <iostream>
#include <vector>
#include <deque>

using namespace std;

class Node {
    public:  
        char name;
        vector<Node> children;

        Node(char name) {this->name = name;}
};

vector<char> BFS(Node root) {
    deque<Node> traversal;
    vector<char> output;

    traversal.push_front(root);

    while(!traversal.empty()) {
        //puts first value in queue in output
        Node temp = traversal.front();
        output.push_back(temp.name);

        //puts all children in back of queue
        for(int i = 0; i < temp.children.size(); i++) {
            traversal.push_back(temp.children[i]);
        }

        //remove front element from queue
        traversal.pop_front();
    }

    return output;
}

int main() {
    Node a = Node('a');
    Node b = Node('b');
    Node c = Node('c');
    Node d = Node('d');
    Node e = Node('e');
    Node f = Node('f');
    Node g = Node('g');
    Node h = Node('h');
    Node i = Node('i');
    Node j = Node('j');
    Node k = Node('k');

    // put into example structure
    g.children.push_back(k);
    f.children.push_back(i);
    f.children.push_back(j);
    d.children.push_back(g);
    d.children.push_back(h);
    b.children.push_back(e);
    b.children.push_back(f);
    a.children.push_back(b);
    a.children.push_back(c);
    a.children.push_back(d);

    vector<char> output = BFS(a);

    for(int i = 0; i < output.size(); i++) {
        cout << output[i] << " ";
    }

    cout << "\n";

    return 0;
}