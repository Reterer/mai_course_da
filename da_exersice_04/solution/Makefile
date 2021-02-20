CPP=g++
CPPFLAGS=-c -Wall -pedantic -std=c++14 -O2
EXECUTABLE=solution

all: $(EXECUTABLE)
	
$(EXECUTABLE): main.o common.o algorithm.o
	$(CPP) -O2 $^ -o $@ 

benchmark: benchmark.cpp algorithm.cpp common.cpp
	$(CPP) -Wall -pedantic -std=c++14 -O2 $^ -o $@

.cpp.o:
	$(CPP) $(CPPFLAGS) $< -o $@

# Зависимости
main.o : algorithm.hpp common.hpp
common.o : common.hpp
algorithm.o : algorithm.hpp common.hpp

clean:
	rm -f *.o $(EXECUTABLE) benchmark
.PHONY: all clean