//
// Created by Gregory Nobleza on 4/17/2024.
//

#include "heap.h"

void Heap::heapify(int node) {
    int parent = (node - 1)/2;

    if(node > size){
        //not in the heap
        return;
    }
    if(node == 0){
        //top node
        return;
    }
    if((container[node] > container[parent]) == 1){
        std::swap(container[node], container[parent]);

        heapify(parent);
    }
}

Heap::Triplet::Triplet(float _score, const std::string _domain, const std::string _ip){
    score = _score;
    domain = _domain;
    ip = _ip;
}
void Heap::insert(float score, const std::string& domain, const std::string& ip){
    struct Triplet newTriplet(score, domain, ip);

    container.push_back(newTriplet);
    size++;

    heapify(size-1);
}

Heap::Triplet Heap::popTop(){
    Triplet saveTop = container[0];
    std::swap(container[0], container[size-1]);
    size--;
    heapifyDown(0);

    return saveTop;

}

void Heap::heapifyDown(int node) {
    if(node > size){
        return;
    }

    int swap = node;

    if(node*2+1 < size && (container[node*2+1] > container[node]) == 1){
        swap = node*2+1;
    }
    if((node*2)+2 < size && (container[node*2+2] > container[node]) == 1){
        swap = node*2 + 2;
    }

    if(swap != node){
        std::swap(container[node], container[swap]);
        heapifyDown(swap);
    }


}
