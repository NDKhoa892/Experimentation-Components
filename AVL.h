#ifndef _AVL_H_
#define _AVL_H_

#include <iostream>

using namespace std;

template<class T>
class AVL {
private:
    struct Node {
        T data;

        int height;
        Node* l, *r;

        Node(T data) {
            this -> data = data;

            height = 1;
            l = nullptr; r = nullptr;
        }
    };

    Node* root;

public:
    AVL() {
        root = nullptr;
    }

    ~AVL() {
        deleteAVL(root);
    }

    int height(Node* node) {
        if (node == nullptr)
            return 0;
        else
            return node -> height;
    }

    void updateHeight(Node* node) {
        node -> height = max(height(node -> l), height(node -> r)) + 1;
    }

    int getBalance(Node* node) {
        if (node == nullptr)
            return 0;
        else
            return height(node -> l) - height(node -> r);
    }

    Node* rRotate(Node* y) {
        Node* x = y -> l;
        y -> l = x -> r;
        x -> r = y;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* lRotate(Node* y) {
        Node* x = y -> r;
        y -> r = x -> l;
        x -> l = y;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* lrRotate(Node* x) {
        x -> l = lRotate(x -> l);
        return rRotate(x);
    }

    Node* rlRotate(Node* x) {
        x -> r = rRotate(x -> r);
        return lRotate(x);
    }

    Node* insert(Node* node, T data) {
        if (node == nullptr)
            return new Node(data);
        else if (data < node -> data)
            node -> l = insert(node -> l, data);
        else
            node -> r = insert(node -> r, data);

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1) {
            if (data < node -> l -> data) // Left left case
                return rRotate(node);
            else                        // Left right case
                return lrRotate(node);
        } else if (balance < -1) {
            if (data > node -> r -> data) // Right right case
                return lRotate(node);
            else                        // Right left case
                return rlRotate(node);
        }

        return node;
    }

    void insert(T data) {
        root = insert(root, data);
    }

    Node* minValueNode(Node* node) {
        Node* cur = node;
        while (cur -> l != nullptr) cur = cur -> l;
        return cur;
    }

    Node* erase(Node* node, T data) {
        if (data < node -> data)
            node -> l = erase(node -> l, data);
        else if (data > node -> data)
            node -> r = erase(node -> r, data);
        else {
            if (node -> l == nullptr || node -> r == nullptr) {
                Node* tmp = (node -> l ? node -> l : node -> r);

                if (tmp == nullptr) {
                    tmp = node;
                    node = nullptr;
                } else
                    *node = *tmp;

                delete tmp;
            } else {
                Node* tmp = minValueNode(node -> r);

                node -> data = tmp -> data;
                node -> r = erase(node -> r, tmp -> data);
            }
        }

        if (node == nullptr)
            return node;

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1) {
            if (getBalance(node -> l) >= 0)
                return rRotate(node);
            else
                return lrRotate(node);
        } else if (balance < -1) {
            if (getBalance(node -> r) <= 0)
                return lRotate(node);
            else
                return rlRotate(node);
        }

        return node;
    }

    void erase(T data) {
        root = erase(root, data);
    }

    bool search(Node* node, T data) {
        if (node == nullptr)
            return false;

        if (node -> data == data)
            return true;
        else if (data < node -> data)
            return search(node -> l, data);
        else
            return search(node -> r, data);
    }

    bool search(T data) {
        return search(root, data);
    }

    void deleteAVL(Node* node) {
        if (node) {
            deleteAVL(node -> l);
            deleteAVL(node -> r);

            delete node;
        }
    }
};

#endif
