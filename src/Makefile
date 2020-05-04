CXX = g++

CXXFLAGS = -std=c++17 -g

DEPS =	random_number_generator.cpp shell_sort.cpp quick_sort.cpp bubble_sort.cpp insertion_sort.cpp selection_sort.cpp radix_sort.cpp merge_sort.cpp command_line.cpp

OBJS =	random_number_generator.o shell_sort.o quick_sort.o bubble_sort.o insertion_sort.o selection_sort.o radix_sort.o merge_sort.o command_line.o

data-sorting: main.o $(OBJS)
	$(CXX) $(CXXFLAGS) main.o $(OBJS) -o data-sorting -lstdc++fs

main.o: main.cpp
	$(CXX) -c $(CXXFLAGS) main.cpp -lstdc++fs

$(OBJS): $(DEPS)
	$(CXX) -c $(CXXFLAGS) $(DEPS) 

clean:
	rm -f *.o data-sorting
