CXXFLAGS := -fsanitize=address -g
.PHONY = all clean

all:
	g++ merge_intervals.cpp -o program $(CXXFLAGS)

clean:
	rm -f program
