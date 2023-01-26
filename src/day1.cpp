#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <numeric>
#include <vector>

int main(int argc, char ** argv)
{
    if (argc != 2) 
    {
        std::cerr << "Il faut un et un seul argument, le fichier d'input\n";
        std::exit(EXIT_FAILURE);
    }

    std::ifstream in_stream{argv[1]};
    if (!in_stream.is_open()) 
    {
        std::cerr << "Impossible d'ouvrir le fichier\n";
        std::exit(EXIT_FAILURE);
    }

    std::string line;
    std::vector<int> calories;
    int current = 0;

    while (std::getline(in_stream, line)) 
    {
        if (line.empty()) 
        {
            calories.push_back(current);
            current = 0;
            continue;
        }
        current += std::atoi(line.c_str());
    }

    in_stream.close();

    std::sort(calories.begin(), calories.end(), std::greater<int>());
    int total_calories = std::accumulate(calories.begin(), calories.begin() + 3, 0);

    std::cout << "Biggest calories eater        : " << calories.at(0) << "\n";
    std::cout << "Total of calories for the top : " << total_calories << "\n";

    return 0;
}
