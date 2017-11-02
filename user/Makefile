CXX ?= g++
CPPFLAGS += -Wall -Werror -pedantic -std=c++11

mkfs.exfs: mkfs.o block.o format.o
	$(CXX) $(LDFLAGS) mkfs.o block.o format.o -o mkfs.exfs

mkfs.o: mkfs.cpp exfs.hpp block.hpp
	$(CXX) $(CPPFLAGS) -c mkfs.cpp -o mkfs.o

block.o: block.cpp exfs.hpp block.hpp
	$(CXX) $(CPPFLAGS) -c block.cpp -o block.o

format.o: format.cpp exfs.hpp block.hpp format.hpp bit_iterator.hpp
	$(CXX) $(CPPFLAGS) -c format.cpp -o format.o

clean:
	rm -rf *.o mkfs.exfs

.PHONY: clean
