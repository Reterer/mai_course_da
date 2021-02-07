CPP=g++
CPPFLAGS=-c -Wall -pedantic -std=c++14 -O0 -g
EXECUTABLE=solution

all: $(EXECUTABLE)
	
$(EXECUTABLE): main.o common.o algorithm.o
	$(CPP) -O0 -g $^ -o $@ 

# banchmark: banchmark.cpp
# 	$(CPP) -Wall -pedantic -std=c++14 -O0 banchmark.cpp -o $@

.cpp.o:
	$(CPP) $(CPPFLAGS) $< -o $@

# Зависимости
main.o : algorithm.hpp common.hpp
common.o : common.hpp
algorithm.o : algorithm.hpp common.hpp

clean:
	rm -f *.o $(EXECUTABLE)
.PHONY: all clean