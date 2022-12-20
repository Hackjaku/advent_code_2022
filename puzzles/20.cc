#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include <vector>

using namespace std;

class Node {
public:
    bool seen;
    int value;

    Node(int);
    void execute(Node*&);
    void add_links(Node*, Node*);
    void print();

private:
    Node* prev;
    Node* next;

    void move_forward(Node*&);
    void move_backward(Node*&);

};

int main() {
    fstream data("../inputs/20.txt", ios::in);
    
    string line;

    vector<Node*> nodes;

    while(getline(data, line)) {
        std::istringstream iss(line);
        int n;

        if (!(iss >> n)) { 
            break;
        }

        Node* node = new Node(n);
        nodes.push_back(node);
    }



    for (int i = 0; i < nodes.size(); ++i) {
        Node* node = nodes[i];
        Node* prev = i == 0 ? nodes[nodes.size() - 1] : nodes[i - 1];
        Node* next = i == nodes.size() - 1 ? nodes[0] : nodes[i + 1];
        node->add_links(prev, next);
    }

    Node* root = nodes[0];

    for (auto node : nodes) {
        node->execute(root);
    }

    nodes[0]->print();

    cout << endl;

    root->print();

    return 0;
}

Node::Node(int value) {
    this->value = value;
    this->seen = false;
    this->prev = NULL;
    this->next = NULL;
}

void Node::move_backward(Node* &root) {
    this->prev->move_forward(root); // lol
}

void Node::move_forward(Node* &root) {
    Node* d = this->next->next;
    Node* a = this->prev;
    Node* c = this->next;

    if (this == root) {
        root = c;
    } else if (c == root) {
        root = this;
    }

    a->next = c;
    c->prev = a;
    c->next = this;
    this->prev = c;
    this->next = d;
    d->prev = this;
}

void Node::add_links(Node* prev, Node* next) {
    this->prev = prev;
    this->next = next;
}

void Node::execute(Node* &root) {
    if (this->seen) {
        return;
    }
    if (this->value < 0) {
        for (int i = 0; i > this->value; --i) {
            this->move_backward(root);
        }
    } else {
        for (int i = 0; i < this->value; ++i) {
            this->move_forward(root);
        }
    }
}

void Node::print() {
    Node* node = this;

    // do {
    //     cout << node->value << endl;
    //     node = node->next;
    // } while (node != this);

    // cout << endl << endl;

    for (int i = 0; i < 3001; ++i) {
        if (i == 1000 || i == 2000 || i == 3000) {
            cout << node->value << endl;
        }
        node = node->next;
    }
}