//
// Created by Donald Robinson on 4/18/2024.
//

#include "RBTree.h"

RBTree::RBTree()
{

}

// Deletes nodes via post-order traversal
RBTree::~RBTree()
{

}

// Compares nodes on basis of phishing score (first) and domain name (second).
// false means 1 < 2. true means 1 > 2. -1 means 1 == 2.
int RBTree::compare(const RBTree::Node* const comparee_1, const RBTree::Node* const comparee_2)
{
    // Comparing phishing scores
    if (comparee_1->score < comparee_2->score)
        return false;
    else if (comparee_1->score > comparee_2->score)
        return true;

    // Comparing domain names
    size_t min_len = std::min(comparee_1->domain.length(), comparee_2->domain.length());
    for (auto i = 0; i < min_len; i++)
    {
        if (comparee_1->domain[i] < comparee_2->domain[i])
            return false;
        if (comparee_1->domain[i] > comparee_2->domain[i])
            return true;
        // If equal, continue iterating
    }

    // Given both equal up to min length...
    // return true if both the exact same
    if (comparee_1->domain.length() == comparee_2->domain.length())
        return -1;
    // return false if comparee_1 is shorter.
    if (min_len == comparee_1->domain.length())
        return false;
    // o.w. return true;
    return true;
}

// Assumes that root node not passed in
RBTree::Node* RBTree::getGrandParent(Node* helperRoot)
{
    return helperRoot->parent->parent;
}

// Assumes that root node not passed in
RBTree::Node* RBTree::getUncle(Node* helperRoot)
{
    Node* parent = helperRoot->parent;
    if (parent->right == helperRoot)
        return parent->left;
    else
        return parent->right;
}

RBTree::Node* RBTree::balance(RBTree::Node* helperRoot)
{
    // If leaf, return itself
//    if (helperRoot->left == nullptr && helperRoot->right == nullptr)
//        return helperRoot;

    Node* parent = helperRoot->parent;
    Node* uncle = getUncle(helperRoot);
    Node* grandparent = getGrandParent(helperRoot);

    if (parent->color == BLACK)
        return helperRoot;
    // if uncle black, if uncle red, rotate

    return nullptr;
}

RBTree::Node* RBTree::helperInsert(RBTree::Node *helperRoot, Node* new_node, float &score, std::string &domain, std::string &ip)
{
    // If tree empty, make root and change color to black
    if (size == 0)
    {
        new_node->color = BLACK;
        ++size;
        return new_node;
    }
    // If not empty, add new node
    else if (helperRoot == nullptr)
    {
        ++size;
        return new_node;
    }

    int compare_val = compare(new_node, helperRoot);
    switch (compare_val)
    {
        // If new_node is equal to root, do not add
        case -1:
            return nullptr;
        // If less, insert on left
        case 0:
            helperRoot->left = helperInsert(helperRoot->left, new_node, score, domain, ip);
            helperRoot->left->parent = helperRoot;
        // If greater, insert on right side
        case 1:
            helperRoot->right = helperInsert(helperRoot->right, new_node, score, domain, ip);
            helperRoot->right->parent = helperRoot;
    }



    return nullptr;
}

void RBTree::insert(float &score, std::string &domain, std::string &ip)
{
    Node* new_node = new Node(score, domain, ip);
    this->root = helperInsert(this->root, new_node, score, domain, ip);
}
