CXX=g++
CXXFLAGS=-std=c++11 -O3 -Wall -Wextra -g -Wno-sign-compare
OBJECTS=vertex.h edge.h golberg_flow_test.h golberg_flow.h main.cpp
test: flow_test
	./$<

flow_test: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f flow_test flow_test_debug

.PHONY: clean test