//
// Created by Dominick on 22/10/2024.
//

#ifndef DSA_PROJECT_ASCIIART_H
#define DSA_PROJECT_ASCIIART_H


class AsciiArt {

public:
    // Function to print colored text
    static void printColored(const std::string &text, const std::string &color);

    // Function to print the ASCII art from a file with a specific color
    static void printAsciiArtColored(const std::string &filename, const std::string &color);

};


#endif //DSA_PROJECT_ASCIIART_H
