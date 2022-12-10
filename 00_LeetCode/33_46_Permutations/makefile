CXXFLAGS := -fsanitize=address -g
.PHONY = all clean

all:
	g++ $(CXXFLAGS) permutations.cpp -o program

clean:
	rm -f program
