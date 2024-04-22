//
// Created by Gregory Nobleza on 4/17/2024.
//

#include <string>
#include <vector>
#include <iostream>

#ifndef UNTITLED1_HEAP_H
#define UNTITLED1_HEAP_H


class Heap {
private:
    struct Triplet{
        float score = 0.f;
        std::string domain;
        std::string ip;
        Triplet(float _score, const std::string _domain, const std::string _ip);
        bool operator>(const Triplet& rhs){
            if(this->score > rhs.score){
                return true;
            }else if(this->score < rhs.score){
                return false;
            }

            size_t min_len = std::min(this->domain.length(), rhs.domain.length());
            for(auto i = 0; i < min_len; i++){
                if(this->domain[i] > rhs.domain[i]){
                    return true;
                }
                if(this->domain[i] < rhs.domain[i]){
                    return false;
                }
            }

            if(this->domain.length() == rhs.domain.length()){
                return false;
            }

            if(min_len == this->domain.length()){
                return false;
            }
            return true;
        }
    };

    std::vector<Triplet> container;
    unsigned long capacity = 0;
    unsigned long size = 0;

    void heapify(int node);
    void heapifyDown(int node);

public:
    Triplet popTop();
    void insert(float score, const std::string& domain, const std::string& ip);
    std::vector<Triplet> aboveThreshold(float threshold){
        std::vector<Triplet> sitesAboveThreshold;

        while(container[0].score >= threshold){
            sitesAboveThreshold.push_back(popTop());
        }

        return sitesAboveThreshold;
    }
    unsigned long getSize() {return size;}
};


#endif //UNTITLED1_HEAP_H
