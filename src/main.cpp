//
// Created by Donald Robinson on 4/16/2024.
//

#include <iostream>
#include <windows.h>

#include "Phish.h"

// For testing; to see where program executed from
std::string getexepath()
{
    char result[ MAX_PATH ];
    return std::string( result, GetModuleFileName( NULL, result, MAX_PATH ) );
}

int main()
{
    std::cout << getexepath() << "\n";
    auto phish = new Phish();


    delete phish;

    return 0;
}