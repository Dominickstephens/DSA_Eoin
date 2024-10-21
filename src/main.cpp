#include <iostream>
#include "vectorBook.h"
#include "documentIndex.h"
#include "IndexEntry.h"
#include "serialization.h"
#include <regex>
#include "DocumentIndexer.h"

using namespace std;

int main() {

    documentIndex<string, vectorClass<IndexEntry>> index;
    string bookPath = "../books";

    // Create DocumentIndexer and perform indexing
    DocumentIndexer indexer(bookPath);
    indexer.performIndexing(index);

    serialize(index, "index.csv");

    documentIndex<string, vectorClass<IndexEntry>> index2;

    deserialize(index2, "index.csv");

    index2.printFirstPair();


    return 0;

}
