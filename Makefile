# Compiler
CXX = /msys64/mingw64/bin/g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -Iinclude

# Executable name
TARGET = main.exe

# Source files
SRCS = main.cpp src/AutocompleteHandler.cpp src/DocumentIndexer.cpp src/IndexEntry.cpp src/indexing.cpp src/search.cpp src/utils.cpp src/AsciiArt.cpp src/AccessBook.cpp src/newSearch.cpp


# Object files
OBJS = $(SRCS:.cpp=.o)

# Rule to build the target
$(TARGET): $(OBJS)
	$(CXX) -o $@ $^

# Rule to build object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up the build
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
