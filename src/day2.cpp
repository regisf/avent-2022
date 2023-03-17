#include <iostream>
#include <fstream>
#include <map>


const static int LostScore = 0;
const static int DrawScore = 3;
const static int WonScore = 6;


enum class Play 
{
    Unknown = 0,
    Rock = 1,
    Paper = 2,
    Scissors = 3
};

std::tuple<Play,Play> normalize_player(char play1, char play2) 
{
    static std::map<char, Play> map1 = {
        { 'A', Play::Rock },
        { 'B', Play::Paper },
        { 'C', Play::Scissors}
    };

     static std::map<char, Play> map2 = {
        { 'X', Play::Rock },
        { 'Y', Play::Paper },
        { 'Z', Play::Scissors}
    };

    return {map1[play1], map2[play2]};
}

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
    int score{0};

    std::map<Play, std::map<Play, int> > r = {
        { Play::Rock, { 
            { Play::Rock, DrawScore + static_cast<int>(Play::Rock) },
            { Play::Paper, WonScore + static_cast<int>(Play::Paper) },
            { Play::Scissors, LostScore + static_cast<int>(Play::Scissors) }
        }},
        { Play::Paper, {
            { Play::Rock, LostScore + static_cast<int>(Play::Rock) },
            { Play::Paper, DrawScore + static_cast<int>(Play::Paper) },
            { Play::Scissors, WonScore + static_cast<int>(Play::Scissors) }
        }},

        { Play::Scissors, {
            { Play::Rock, WonScore + static_cast<int>(Play::Rock) },
            { Play::Paper, LostScore + static_cast<int>(Play::Paper) },
            { Play::Scissors, DrawScore + static_cast<int>(Play::Scissors) }
        }}
    };

    while (std::getline(in_stream, line))
    {
        if (line.size() != 3) 
        {
            continue;
        }

        auto result = normalize_player(line[0], line[2]);
        auto player1 = std::get<0>(result);
        auto player2 = std::get<1>(result);

        score += r[player1][player2];
   }

    in_stream.close();
    std::cout << "Score : " << score << "\n";

}
