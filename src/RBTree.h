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
    // Node equivalent
    struct Site {
        float score = 0.f;
        std::string domain;
        std::string ip;

        bool color = BLACK;

        Site* left = nullptr;
        Site* right = nullptr;
    };
    Site* root = nullptr;

public:
    RBTree();
    ~RBTree();

};


#endif //COP3530_P3_RBTREE_H
