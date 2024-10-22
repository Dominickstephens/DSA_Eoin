#ifndef DSA_PROJECT_ASCIIART_H
#define DSA_PROJECT_ASCIIART_H


class AsciiArt {

public:
    // Print colored text
    static void printColored(const std::string &text, const std::string &color);

    // Print the ASCII art from a file with a specific color
    static void printAsciiArtColored(const std::string &filename, const std::string &color);

};


#endif
