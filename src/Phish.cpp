//
// Created by Donald Robinson on 4/17/2024.
//

#include <fstream>
#include <regex>
#include <vector>
#include <chrono>

#include "Phish.h"

// General constructor, might be modified depending on what this class calls for in future.
Phish::Phish() {
}

// Will delete any dynamically allocated memory
Phish::~Phish() {
    delete rb_tree;
    rb_tree = nullptr;
    // delete bin_heap;
    // bin_heap = nullptr;
}

// Reads phish_score.csv and compares insertion times for RB Tree and Binary Heap
void Phish::read_phish_csv() {
    delete rb_tree;
    rb_tree = new RBTree();
    // delete bin_heap;
    bin_heap = new Heap();

    std::ifstream file;
    file.open("../phish_score.csv");

    std::string line;
    auto sites = new std::vector<Phish::Site *>;
    std::regex delim("[^\",]+");
    std::smatch match;

    while (std::getline(file, line)) {
        // Ignores header of csv
        if (line[0] == '#')
            continue;

        auto temp = new Phish::Site();

        std::regex_search(line, match, delim);
        // Discard time entered value
        line = match.suffix();

        std::regex_search(line, match, delim);
        temp->score = std::stof(match.str());
        line = match.suffix();

        std::regex_search(line, match, delim);
        temp->domain = match.str();
        line = match.suffix();

        std::regex_search(line, match, delim);
        temp->ip = match.str();

        sites->push_back(temp);
    }

    file.close();

    // Now that we have a vector to draw from, we can insert and compare times
    // -----RB Tree-----
    auto start = std::chrono::high_resolution_clock::now();
    for (Site* i: *sites)
    {
        rb_tree->insert(i->score, i->domain, i->ip);
    }
    auto finish = std::chrono::high_resolution_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);

    std::cout << "\nThe Red-Black Tree took " << microseconds.count() << "us to insert ";
    std::cout << sites->size() << " potential scam sites.\n";
    // -----*******-----

    // -----Binary Heap-----

    // -----***********-----

    start = std::chrono::high_resolution_clock::now();
    for(Site* i: *sites){
        bin_heap->insert(i->score, i->domain, i->ip);
    }
    finish = std::chrono::high_resolution_clock::now();
    microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);
    std::cout << "\nThe Max-Heap took " << microseconds.count() << "us to insert ";
    std::cout << sites->size() << " potential scam sites.\n";


    for (Site* i: *sites)
    {
        delete i;
    }
    delete sites;
}

void Phish::phishing_threshold(float& score)
{
    // -----RB Tree-----
    auto start = std::chrono::high_resolution_clock::now();
    auto results = rb_tree->findMinScore(score);
    auto finish = std::chrono::high_resolution_clock::now();
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(finish-start);

    std::cout << "\nThe Red-Black Tree took " << microseconds.count() << "us to find ";
    std::cout << results.first << " site with a phishing score greater than or equal to " << score << ".\n";

    std::string input;
    std::cout << "Would you like to see the results? [y/n]? ";
    std::cin >> input;
    if (input == "y" || input == "Y")
        std::cout << results.second;

    // -----*******-----

    // -----Binary Heap-----

    // -----***********-----
}
