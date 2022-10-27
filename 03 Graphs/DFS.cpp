#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Node {
    public:  
        char name;
        vector<Node> children;

        Node(char name) {this->name = name;}
};

void helper(Node root, vector<char> &output) {
    if(!root.name) return;

    output.push_back(root.name);

    for(int i = 0; i < root.children.size(); i++) {
        helper(root.children[i], output);
    }

    return;
}

vector<char> DFS(Node root) {
    vector<char> output;
    helper(root, output);

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

    vector<char> output = DFS(a);

    for(int i = 0; i < output.size(); i++) {
        cout << output[i] << " ";
    }

    cout << "\n";

    return 0;
}