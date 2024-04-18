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
// false means 1 < 2. true means 1 >= 2.
bool RBTree::compare(const RBTree::Node* const comparee_1, const RBTree::Node* const comparee_2)
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
        return true;
    // return false if comparee_1 is shorter.
    if (min_len == comparee_1->domain.length())
        return false;
    // o.w. return true;
    return true;
}

RBTree::Node *RBTree::helperInsert(RBTree::Node *helperRoot, float &score, std::string &domain, std::string &ip)
{
    // If (sub)tree empty, the root passed in is assigned to a Node
    if (helperRoot == nullptr)
    {
        return new Node(score, domain, ip);
    }

    return nullptr;
}

void RBTree::insert(float &score, std::string &domain, std::string &ip)
{
    this->root = helperInsert(this->root, score, domain, ip);
}
