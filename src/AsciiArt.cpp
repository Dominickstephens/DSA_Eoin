#include <string>
#include <iostream>
#include <fstream>
#include "../include/AsciiArt.h"

void AsciiArt::printColored(const std::string &text, const std::string &color)
{
    std::cout << color << text << "\033[0m";
}

void AsciiArt::printAsciiArtColored(const std::string &filename, const std::string &color)
{
    std::ifstream file(filename);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            printColored(line, color);
            std::cout << std::endl;
        }
        file.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

