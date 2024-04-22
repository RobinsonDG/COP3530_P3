//
// Created by Donald Robinson on 4/18/2024.
//

#include <queue>
#include <iostream>
#include "RBTree.h"

RBTree::RBTree()
{

}

// Deletes nodes via Level Order traversal
RBTree::~RBTree()
{
    std::queue<Node*> q;
    q.emplace(root);
    while(!q.empty())
    {
        Node* temp = q.front();
        q.pop();

        if (temp->left != nullptr)
            q.emplace(temp->left);
        if (temp->right != nullptr)
            q.emplace(temp->right);

        delete temp;
    }
    root = nullptr;
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
    Node* grandparent = getGrandParent(helperRoot);
    if (grandparent->right == parent)
        return grandparent->left;
    else
        return grandparent->right;
}

void RBTree::balance(RBTree::Node* helperRoot)
{
    Node* parent = helperRoot->parent;
    Node* grandparent = getGrandParent(helperRoot);
    Node* uncle = nullptr;

    while(parent->color == RED)
    {
        parent = helperRoot->parent;
        grandparent = getGrandParent(helperRoot);
        uncle = getUncle(helperRoot);

        if (uncle != nullptr && uncle->color == RED)
        {
            uncle->color = parent->color = BLACK;
            grandparent->color = RED;
            helperRoot = grandparent;

            if (grandparent == root)
                break;

            // Update status (everytime helperRoot is adjusted)
            parent = helperRoot->parent;

            continue;
        }

        // Right-
        if (parent == grandparent->right)
        {
            // -Left Case
            if (helperRoot == parent->left)
            {
                helperRoot = parent;
                rightRotation(helperRoot);
                // Update status
                parent = helperRoot->parent;
                grandparent = getGrandParent(helperRoot);
            }
            // -Right Case
            parent->color = BLACK;
            grandparent->color = RED;
            leftRotation(grandparent);
        }
        // Left-
        else
        {
            // -Right Case
            if (helperRoot == parent->right)
            {
                helperRoot = parent;
                leftRotation(helperRoot);
                // Update status
                parent = helperRoot->parent;
                grandparent = getGrandParent(helperRoot);
            }
            // -Left Case
            parent->color = BLACK;
            grandparent->color = RED;
            rightRotation(grandparent);
        }

        if (helperRoot == root)
            break;
    }

    root->color = BLACK;
}

void RBTree::leftRotation(Node* curr_node)
{
    // Current parent of curr_node
    Node* curr_parent = curr_node->parent;

    // new_curr_node is curr_node's right child
    Node* new_curr_node = curr_node->right;

    // Transfer child
    curr_node->right = new_curr_node->left;

    // If transferred child is not null, replace parent
    if (curr_node->right != nullptr)
        curr_node->right->parent = curr_node;

    // Parent of new_curr is parent of curr_node
    new_curr_node->parent = curr_parent;

    if (curr_parent == nullptr)
        root = new_curr_node;
    // Transfer child ptr from parent
    else if (curr_node == curr_parent->right)
        curr_parent->right = new_curr_node;
    else
        curr_parent->left = new_curr_node;

    // Finalize rotation
    new_curr_node->left = curr_node;
    curr_node->parent = new_curr_node;
}

void RBTree::rightRotation(Node* curr_node)
{
    // Current parent of curr_node
    Node* curr_parent = curr_node->parent;

    // new_curr_node is curr_node's left child
    Node* new_curr_node = curr_node->left;

    // Transfer child
    curr_node->left = new_curr_node->right;

    // If transferred child is not null, replace parent
    if (curr_node->left != nullptr)
        curr_node->left->parent = curr_node;

    // Parent of new_curr is parent of curr_node
    new_curr_node->parent = curr_parent;

    if (curr_parent == nullptr)
        root = new_curr_node;
    // Transfer child ptr from parent
    else if (curr_node == curr_parent->left)
        curr_parent->left = new_curr_node;
    else
        curr_parent->right = new_curr_node;

    // Finalize rotation
    new_curr_node->right = curr_node;
    curr_node->parent = new_curr_node;
}

void RBTree::insert(float &score, std::string &domain, std::string &ip)
{
    Node* new_node = new Node(score, domain, ip);
    Node* iter_1 = root;
    Node* iter_2 = root;

    if (root == nullptr)
    {
        root = new_node;
        root->color = BLACK;
        ++size;
        return;
    }

    int compare_val = 0;
    // Iterative approach to navigate tree, keeping iter_2 one level above iter_1
    while (iter_1 != nullptr)
    {
        compare_val = compare(new_node, iter_1);
        switch (compare_val)
        {
            // If new_node is equal to root, do not add
            case -1:
                delete new_node;
                return;
            // If less, got to left
            case 0:
                iter_2 = iter_1;
                iter_1 = iter_1->left;
                break;
            // If greater, go to right
            case 1:
                iter_2 = iter_1;
                iter_1 = iter_1->right;
                break;
        }
    }

    new_node->parent = iter_2;
    ++size;
    compare_val ? iter_2->right = new_node : iter_2->left = new_node;

    // Balance the tree starting at the newly inserted node
    balance(new_node);
}

// Prints level order traversal of tree (left to right)
void RBTree::printLevelOrder()
{
    std::queue<Node*> q;
    q.emplace(root);
    while(!q.empty())
    {
        Node* temp = q.front();
        q.pop();

        if (temp->left != nullptr)
            q.emplace(temp->left);
        if (temp->right != nullptr)
            q.emplace(temp->right);

        temp->color ? std::cout << "RED | " : std::cout << "BLACK | ";
        std::cout << temp->score << " | " << temp->domain;

        if (temp->parent != nullptr)
        {
            if (temp == temp->parent->right)
                std::cout << ", right ";
            else
                std::cout << ", left ";

            std::cout << "son of " << temp->parent->domain << "\n";
        }
        else
            std::cout << "\n";
    }
}

unsigned long RBTree::getSize()
{
    return size;
}