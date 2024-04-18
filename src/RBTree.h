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

        bool color = BLACK;

        Node* left = nullptr;
        Node* right = nullptr;

        Node(float& score, std::string& domain, std::string& ip)
        {
            this->score = score;
            this->domain = domain;
            this->ip = ip;
        }
    };
    Node* root = nullptr;

    // Helper Methods:
    bool compare(const RBTree::Node* const comparee_1, const RBTree::Node* const comparee_2);
    RBTree::Node* helperInsert(Node* helperRoot, float& score, std::string& domain, std::string& ip);

public:
    RBTree();
    ~RBTree();

    void insert(float& score, std::string& domain, std::string& ip);
};


#endif //COP3530_P3_RBTREE_H
