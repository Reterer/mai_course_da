CPP=g++
CPPFLAGS=-c -Wall -pedantic -std=c++14 -O2
EXECUTABLE=solution

.PHONY: all
all: $(EXECUTABLE) benchmark
	
$(EXECUTABLE): main.o common.o sort.o
	$(CPP) -O2 $^ -o $@

benchmark: benchmark.o common.o sort.o
	$(CPP) -O2 $^ -o $@
.cpp.o:
	$(CPP) $(CPPFLAGS) $< -o $@

# Зависимости
main.o : common.hpp vector.hpp sort.hpp
common.o : common.hpp
sort.o : sort.hpp vector.hpp
benchmark.o : sort.hpp common.hpp vector.hpp

.PHONY: clean
clean:
	rm -f *.o $(EXECUTABLE) benchmark