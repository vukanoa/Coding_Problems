CXXFLAGS= -fsanitize=address -g3
.PHONY = all clean

all:
	g++ symmetric_tree.cpp -o program $(CXXFLAGS)

clean:
	rm -f program
