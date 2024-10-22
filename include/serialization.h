#ifndef DSA_PROJECT_SERIALIZATION_H
#define DSA_PROJECT_SERIALIZATION_H

#include "documentIndex.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "IndexEntry.h"

using namespace std;

template <typename KeyType, typename ValueType>
void serialize(const documentIndex<KeyType, ValueType> &index, const string &filename)
{
    ofstream outfile(filename);
    if (outfile.is_open())
    {
        outfile << "Key,File-Path,Filename,Frequency,LineNumbers" << endl;

        // Iterate through all buckets in the hash table
        for (const auto &bucket : index.table)
        {
            for (const auto &pair : bucket)
            {

                outfile << pair.first << ",";

                const auto &values = pair.second;
                for (size_t i = 0; i < values.size(); ++i)
                {
                    outfile << values[i];
                    if (i < values.size() - 1)
                    {
                        outfile << ";";
                    }
                    outfile << ",";
                }
                outfile << endl;
            }
        }
        outfile.close();
    }
    else
    {
        cerr << "Unable to open file for writing." << endl;
    }
}

template <typename KeyType, typename ValueType>
void deserialize(documentIndex<KeyType, ValueType> &index, const string &filename)
{
    ifstream infile(filename);
    string line;

    if (infile.is_open())
    {
        // Skip the header line
        getline(infile, line);

        while (getline(infile, line))
        {
            istringstream ss(line);
            string keyStr;
            string valuesStr;

            // Split the line into the key and values part by the first comma
            if (getline(ss, keyStr, ',') && getline(ss, valuesStr))
            {
                KeyType key = keyStr;

                if (!valuesStr.empty() && valuesStr.back() == ',')
                {
                    valuesStr.pop_back();
                }

                istringstream valuesStream(valuesStr);
                string entryStr;
                vectorClass<IndexEntry> entries;

                while (getline(valuesStream, entryStr, ';'))
                {
                    IndexEntry entry = parseIndexEntry(entryStr); // Deserialize each IndexEntry
                    entries.push(entry);
                }

                index.insertFullVector(key, entries);
            }
        }
        infile.close();
    }
    else
    {
        cerr << "Unable to open file for reading." << endl;
    }
}

#endif 
