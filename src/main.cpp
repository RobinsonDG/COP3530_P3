//
// Created by Donald Robinson on 4/16/2024.
//

#include <iostream>
#include <string>
#include <stdexcept>
// For CLI, not a data structure
#include <map>

#include "Phish.h"

int main()
{
    // Defines commands to be scanned for in input
    std::map<int, std::string> commands = {
            {0, "Compare .csv read/insertion times"},
            {1, "Compare the time it takes to identify all websites above a certain phishing score threshold"},
    };
    std::string input_str;
    int input_int;

    bool csv_read = false;

    auto phish = new Phish();

    // 49 total. 47 without outer
    // Perhaps less than ideal formatting :)

    std::cout << " " << std::string(49, '-') << " \n";
    std::cout << "|" << std::string(13, ' ') << "Something Smells Phishy" << std::string(13, ' ') << "|\n";
    std::cout << "|" << std::string(3, ' ') << "...and it's not just that grammatical error";
    std::cout << std::string(3, ' ') << "|\n";
    std::cout << "|" << std::string(12, ' ') << "asking for my password..." << std::string(12, ' ') << "|\n";
    std::cout << " " << std::string(49, '-') << " \n";

    std::cout << "Please ensure that the file \"phish_score.csv\" is located in this project directory, one directory outside of the src folder.\n";
    while (true) {
        std::cout << "\nPlease enter the number corresponding to the option you would like to choose (i.e. \"1\")\n";
        std::cout << "Enter \"0\" to quit...\n";

        for (auto i: commands) {
            std::cout << i.first + 1 << ". " << i.second << "\n";
        }

        while (true)
        {
            std::getline(std::cin, input_str);

            // Just-in-case error handling
            try { input_int = std::stoi(input_str); }
            catch(std::invalid_argument& e){
                std::cout << "Please enter a valid option.\n";
                continue;
            }
            catch(std::out_of_range& e){
                std::cout << "Please enter a valid option.\n";
                continue;
            }
            if (input_int < 0 || input_int > commands.size())
            {
                std::cout << "Please enter a valid option.\n";
                continue;
            }

            break;
        }
        if (input_int == 0)
            break;

        switch (input_int)
        {
            case 1:
                phish->read_phish_csv();
                csv_read = true;
                break;
            case 2:
                if (!csv_read)
                {
                    std::cout << "Please read from csv first! (choose option 1).\n";
                    break;
                }

                std::string input_score_str;
                float input_score;
                std::cout << "Please enter a minimum score to be filtered (float)... ";
                while (true)
                {
                    std::getline(std::cin, input_score_str);

                    // Just-in-case error handling
                    try { input_score = std::stof(input_score_str); }
                    catch(std::invalid_argument& e){
                        std::cout << "Please enter a valid float.\n";
                        continue;
                    }
                    catch(std::out_of_range& e){
                        std::cout << "Please enter a valid float.\n";
                        continue;
                    }
                    if (input_score < 0.f || input_score > 10.f)
                    {
                        std::cout << "Please enter a float between 0.0 and 10.0.\n";
                        continue;
                    }

                    break;
                }

                phish->phishing_threshold(input_score);

                break;
        }

    }

    delete phish;

    return 0;
}