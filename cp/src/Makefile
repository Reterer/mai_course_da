CPP=g++
CPPFLAGS=-c -Wall -pedantic -std=c++14 -O2
EXECUTABLE=solution

all: $(EXECUTABLE)
	
$(EXECUTABLE): main.o solution.o
	$(CPP) -O2 $^ -o $@ 

.cpp.o:
	$(CPP) $(CPPFLAGS) $< -o $@

# Зависимости
main.o : solution.hpp
solution.o : solution.hpp

clean:
	rm -f *.o $(EXECUTABLE)
.PHONY: all clean