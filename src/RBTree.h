//
// Created by Donald Robinson on 4/18/2024.
//

#define BLACK false
#define RED true

#include <string>

#ifndef COP3530_P3_RBTREE_H
#define COP3530_P3_RBTREE_H

class RBTree {
private:
    struct Node {
        float score = 0.f;
        std::string domain;
        std::string ip;

        bool color = RED;

        Node* left = nullptr;
        Node* right = nullptr;
        Node* parent = nullptr;

        Node(float& score, std::string& domain, std::string& ip)
        {
            this->score = score;
            this->domain = domain;
            this->ip = ip;
        }
    };
    Node* root = nullptr;
    unsigned long size = 0;

    // Helper Methods:
    int compare(const RBTree::Node* const comparee_1, const RBTree::Node* const comparee_2);
    RBTree::Node* getGrandParent(Node* helperRoot);
    RBTree::Node* getUncle(Node* helperRoot);

    void balance(Node* helperRoot);
    void leftRotation(Node* node);
    void rightRotation(Node* node);

public:
    RBTree();
    ~RBTree();

    void insert(float& score, std::string& domain, std::string& ip);
    void printLevelOrder();
    unsigned long getSize();
};


#endif //COP3530_P3_RBTREE_H
