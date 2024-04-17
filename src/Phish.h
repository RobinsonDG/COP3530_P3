//
// Created by Donald Robinson on 4/17/2024.
//

#ifndef COP3530_P3_PHISH_H
#define COP3530_P3_PHISH_H

#include <iostream>
#include <string>

class Phish {
private:
    struct Site {
        float score = 0.f;
        std::string domain;
        std::string ip;
    };

    // data_structure1<Phish::Site>* ds1 = nullptr;
    // data_structure2<Phish::Site>* ds2 = nullptr;

    void read_phish_csv();

public:
    Phish();
    ~Phish();

};


#endif //COP3530_P3_PHISH_H
