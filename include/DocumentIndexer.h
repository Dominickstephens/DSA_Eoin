#ifndef DSA_PROJECT_DOCUMENTINDEXER_H
#define DSA_PROJECT_DOCUMENTINDEXER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <string>
#include "vectorBook.h"
#include "IndexEntry.h"
#include "documentIndex.h"

using namespace std;

class DocumentIndexer {
public:
    explicit DocumentIndexer(string  path);

    // Method to perform the indexing
    void performIndexing(documentIndex<string, vectorClass<IndexEntry>>& index, vectorClass<Pair<string, int>>& fileWordCount);

private:
    string bookPath;

    // Process file and insert into the index
    static void processFile(const filesystem::directory_entry& dirEntry,
                     documentIndex<string, vectorClass<IndexEntry>>& index, vectorClass<Pair<string, int>>& fileWordCount);


    static string removePunctuationsAndLower( string& s);
};




#endif
