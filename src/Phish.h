//
// Created by Donald Robinson on 4/17/2024.
//

#include <iostream>
#include <string>

#include "RBTree.h"
#include "heap.h"

#ifndef COP3530_P3_PHISH_H
#define COP3530_P3_PHISH_H

class Phish {
private:
    // For testing. Each data structure will have its own node.
    struct Site {
        float score = 0.f;
        std::string domain;
        std::string ip;
    };

    RBTree* rb_tree = nullptr;
    // data_structure2* bin_heap = nullptr;

public:
    Phish();
    ~Phish();

    void read_phish_csv();
    void phishing_threshold(float& score);
};


#endif //COP3530_P3_PHISH_H
