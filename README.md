# JellyCats Library

Welcome to **JellyCats Library**! A mini Windows-specific search engine for documents.

## Table of Contents

- [Getting Started](#getting-started)
    - [Prerequisites](#prerequisites)
    - [Compiling and running the Application](#compiling-and-running-the-application)
- [Indexing Documents](#indexing-documents)
- [Searching for Documents](#searching-for-documents)
  - [Boolean operators](#boolean-operators-for-more-advanced-searches)
  - [Keyword autocomplete](#keyword-autocomplete)
- [Exiting the Application](#exiting-the-application)
- [Contributers](#contributers)

## Getting Started

Follow these steps to set up and run **JellyCats Library** on a Windows system.

### Prerequisites

Before running the project, make sure you have the following installed:

- **Make**: To compile the project.
- **C++ Compiler**: Such as MSVC (Microsoft Visual C++) or MinGW.

### Compiling and Running the Application

1. Open a terminal or command prompt.
2. Navigate to the project directory.
3. Run the following command to compile the program:

   ```bash
   make
   ```
3. Run the following command to run the program:

   ```bash
   main
   ```

## Indexing Documents
- Our application allows you to index a set of documents for quick searching
- To illustrate our applications functionality, we have included a books folder containing .txt documents in the project directory

## Searching for Documents
- Upon running the project, you will be prompted to search for keywords or phrases
- Press Enter to submit a search
- If your search query is found within a document, a list of results ranked by tf-idf
- Each result will contain
  - Document name
  - Filepath
  - Relevant excerpt
- If no results are found, you will receive a message stating 'No documents found'


- example of a search result:
```bash
christmas
Search Results:
File Path: C:\Users\Dominick\CLionProjects\DSA_project\books\A Christmas Carol in Prose Being a Ghost Story of Christmas_46.txt                                           
File Name: A Christmas Carol in Prose Being a Ghost Story of Christmas_46.txt
´╗┐The Project Gutenberg eBook of A Christmas Carol in Prose; Being a Ghost Story of Christmas

   ```
### Boolean operators for more advanced searches:

- AND: Find documents that contain both keywords
- OR: Find documents that contain either of the keywords
- NOT: Exclude documents containing certain keywords


- example of searching 'Christmas AND Carol':
```bash
Document ID: 0 - A Christmas Carol in Prose Being a Ghost Story of Christmas_46.txt - books
Document ID: 4 - ChristmasCarol.txt - books
Document ID: 8 - White Nights and Other Stories_36034.txt - books
   ```
### Keyword autocomplete

- As you type your search query, autocomplete suggestions will appear
- These autocomplete suggestions are based off of all the words within the text documents
- To accept a suggestion, press Tab
- You can cycle through the suggestions
  - Press > to move forward
  - Press < to move backward


## Exiting the Application
To exit the application, type:
   ```bash
   exit
   ```

## Contributers
- Emily Roys: 22355561
- Dominick Stephens: 22343288
- Rosie Kennelly: 22340238