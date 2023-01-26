#include <fstream>
#include <iostream>
#include <cstdlib>
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
    std::vector<int> lines;
    int current = 0;
    int biggest = 0;

    while (std::getline(in_stream, line)) 
    {
        if (line.empty()) 
        {
            if (current > biggest) 
            {
                biggest = current;
            }
            current = 0;
            continue;
        }
        current += std::atoi(line.c_str());
    }

    in_stream.close();

    std::cout << biggest << "\n";
    return 0;
}
