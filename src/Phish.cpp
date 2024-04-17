//
// Created by Donald Robinson on 4/17/2024.
//

#include <fstream>
#include <regex>
#include <vector>

#include "Phish.h"

// General constructor, might be modified depending on what this class calls for in future.
Phish::Phish() {
    read_phish_csv();
}

// Will delete any dynamically allocated memory
Phish::~Phish() {

}

// Reads phish_score.csv. May return something in future. Prints (size of vector containing) data points for now.
void Phish::read_phish_csv() {
    std::ifstream file;
    file.open("../phish_score.csv");

    std::string line;
    auto sites = new std::vector<Phish::Site*>;
    std::regex delim("[^\",]+");
    std::smatch match;
    while (std::getline(file, line))
    {
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
    std::cout << sites->size();

    file.close();
    for (auto i : *sites)
    {
        // std::cout << i->score << " " << i->domain << " " << i->ip << "\n";
        delete i;
    }
    delete sites;
}
