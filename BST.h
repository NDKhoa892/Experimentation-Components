#ifndef _BST_H_
#define _BST_H_

#include <iostream>

using namespace std;

template<class T>
class BST {
private:
    struct Node {
        T data;
        Node* left, *right;

        Node() {
            left = nullptr;
            right = nullptr;
        }

        Node(T data) : Node() {
            this -> data = data;
        }
    };

    Node* root;

public:
    BST() {
        root = nullptr;
    }

    ~BST() {
        removeBST();
    }

    void insert(Node* &node, T data) {
        if (!node)
            node = new Node(data);
        else if (data < node -> data)
            insert(node -> left, data);
        else
            insert(node -> right, data);
    }

    void insert(T data) {
        insert(root, data);
    }

    bool search(Node* node, T x) {
        if (!node)
            return false;
        else if (node -> data == x)
            return true;
        else if (x < node -> data)
            return search(node -> left, x);
        else
            return search(node -> right, x);
    }

    bool search(T x) {
        return search(root, x);
    }

    Node* rightMost(Node* node, Node* &maxNode) {
        if (!node) return nullptr;

        if (node -> right) {
            node -> right = rightMost(node -> right, maxNode);
            return node;
        } else {
            maxNode = node;
            return node -> left;
        }
    }

    Node* erase(Node* node, T x) {
        if (!node) return nullptr;

        if (node -> data == x) {
            Node* maxNode = nullptr;
            node -> left = rightMost(node -> left, maxNode);

            if (maxNode) {
                node -> data = maxNode -> data;
                delete maxNode;
                return node;
            } else {
                Node* tmp = node -> right;
                delete node;
                return tmp;
            }
        } else if (x < node -> data)
            node -> left = erase(node -> left, x);
        else
            node -> right = erase(node -> right, x);

        return node;
    }

    void erase(T x) {
        root = erase(root, x);
    }

    void removeBST(Node* &node) {
        if (node) {
            removeBST(node -> left);
            removeBST(node -> right);
            delete node;
        }
    }

    void removeBST() {
        removeBST(root);
    }
};

#endif
