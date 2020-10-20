CXX=g++
CXXFLAGS=-std=c++11 -O2 -pedantic -Wall
OBJECTS=rb_tree_main.cpp
test: rb_test
	./$<

rb_test: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f rb_test

.PHONY: clean test