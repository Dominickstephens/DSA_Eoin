#ifndef DSA_PROJECT_INDEXENTRY_H
#define DSA_PROJECT_INDEXENTRY_H

#include <sstream>
#include "vectorBook.h"

struct IndexEntry
{
    string filePath;
    string fileName;
    int frequency{};
    vectorClass<streampos> positionOffsets;
};

std::ostream &operator<<(std::ostream &os, const IndexEntry &entry);

IndexEntry parseIndexEntry(const std::string &str);

#endif
