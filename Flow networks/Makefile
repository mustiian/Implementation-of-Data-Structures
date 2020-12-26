CXX=g++
CXXFLAGS=-std=c++11 -O3 -pg -Wall -Wextra -g -Wno-sign-compare 
OBJECTS=vertex.h edge.h goldberg_flow_test.h goldberg_flow.h debug_main.cpp

#test: flow_test
#	./$<

flow_test: $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

clean:
	rm -f flow_test flow_test_debug

.PHONY: clean test