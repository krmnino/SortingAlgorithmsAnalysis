CXXFLAGS = -std=c++17 -g

DEPS =	random_number_generator.cpp shell_sort.cpp quick_sort.cpp bubble_sort.cpp insertion_sort.cpp selection_sort.cpp

OBJS =	random_number_generator.o shell_sort.o quick_sort.o bubble_sort.o insertion_sort.o selection_sort.o

data-sorting: main.o $(OBJS)
	g++ main.o $(OBJS) -o data-sorting

main.o: main.cpp
	g++ -c $(CXXFLAGS) main.cpp

$(OBJS): $(DEPS)
	g++ -c $(CXXFLAGS) $(DEPS)

clean:
	rm -f *.o data-sorting
