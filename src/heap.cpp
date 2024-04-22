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
    if((container[node] > container[parent])){
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
    int left = 2*node + 1;
    int right = 2*node+2;

    if(left < size && (container[left] > container[swap])){
        swap = left;
    }
    if(right < size && (container[right] > container[swap])){
        swap = right;
    }

    if(swap != node){
        std::swap(container[node], container[swap]);
        heapifyDown(swap);
    }


}
