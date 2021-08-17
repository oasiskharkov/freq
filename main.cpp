#include <iostream>
#include <unordered_map>
#include <vector>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <sstream>

using namespace std;

constexpr int maxArgumentsCount = 3;

int main(int argc, char** argv)
{
    if(argc != maxArgumentsCount)
    {
        std::cerr << "Incorrect arguments count" << std::endl;
        return EXIT_FAILURE;
    }

    std::ifstream in(argv[1]);
    std::unordered_map<std::string, int> dictionary;
    if(in.is_open())
    {
        std::string lexeme;
        while(!in.eof())
        {
            in >> lexeme;
            std::transform(lexeme.begin(), lexeme.end(), lexeme.begin(), ::tolower);
            const auto& pred = [](const char l) { return !(l >= 'a' and l <= 'z'); };
            std::replace_if(lexeme.begin(), lexeme.end(), pred, ' ');

            istringstream ss(lexeme);
            string word;

            while (ss >> word)
            {
                if(dictionary.find(word) != dictionary.end())
                {
                    dictionary[word]++;
                }
                else
                {
                    dictionary.emplace(std::make_pair(word, 1));
                }
            }
        }
        in.close();
    }
    else
    {
        std::cerr << "Can't open input file in.txt" << std::endl;
        return EXIT_FAILURE;
    }

    std::vector<std::pair<int, std::string>> freq;
    std::transform(dictionary.begin(), dictionary.end(), std::back_inserter(freq), [](const auto& kv){ return std::make_pair(kv.second, kv.first);});
    std::sort(freq.begin(), freq.end(), [](const auto& p1, const auto& p2) { return p1.first > p2.first || (p1.first == p2.first && p1.second < p2.second);});

    std::ofstream out(argv[2]);
    if(out.is_open())
    {
        for(const auto& p : freq)
        {
            out << p.first << ' ' << p.second << std::endl;
        }
        out.close();
    }
    else
    {
        std::cerr << "Can't open output file out.txt" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
