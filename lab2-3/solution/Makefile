CPP=g++
CPPFLAGS=-c -Wall -pedantic -std=c++14 -O0 -g
EXECUTABLE=solution

all: $(EXECUTABLE)
	
$(EXECUTABLE): main.o
	$(CPP) -O0 -g $^ -o $@ 

banchmark: banchmark.cpp
	$(CPP) -Wall -pedantic -std=c++14 -O0 banchmark.cpp -o $@

.cpp.o:
	$(CPP) $(CPPFLAGS) $< -o $@

# Зависимости
main.o : rbtree.hpp
banchmark.o : rbtree.hpp 

clean:
	rm -f *.o $(EXECUTABLE) banchmark
.PHONY: all clean