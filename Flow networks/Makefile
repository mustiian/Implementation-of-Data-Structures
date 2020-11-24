CXX=g++
CXXFLAGS=-std=c++11 -O2 -pedantic -Wall -g
OBJECTS=golberg_flow.h golberg_flow_test.h main.cpp
test: flow_test
	./$<

flow_test: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f flow_test flow_test_debug

.PHONY: clean test