#ifndef __GOLBER_FLOW_TEST__
#define __GOLBER_FLOW_TEST__

#include "vertex.h"
#include "edge.h"
#include <string>
#include <iostream>

#define TEST(expression, message, func_name) assertm(func_name, __FILE__, __LINE__, expression, message);

void assertm(const char* function, const char* file, int line, bool expr, const std::string& message){
    if (!expr)
    {
        std::cerr << "Assert failed:\t" << message << "\n"
            << "Call function:\t" << function << "\n"
            << "Source:\t\t" << file << ", line " << line << "\n";
        abort();
    }
}


class Golberg_flow_tester
{
private:

public:
    static void test_height_diff(const std::vector<Edge> &edges, const char* call_func);
    static void test_excess_flow(const std::vector<Vertex> &vertices, const char* call_func);
    static void test_height_limit(const std::vector<Vertex> &vertices, const char* call_func);
    static void test_flow(const std::vector<Edge> &edges, const char* call_func);
};


void Golberg_flow_tester::test_height_diff(const std::vector<Edge> &edges, const char* call_func) 
{
    for(const Edge& edge : edges){
        if (edge.get_reserve() > 0){
            const Vertex &start = edge.get_start(),
            &end = edge.get_end();

            TEST((start.get_height() - edge.get_end().get_height()) <= 1,
                "vertex " + std::to_string(start.get_ID())  + 
                " height " + std::to_string(start.get_height()) + 
                "is higher then vertex " + std::to_string(end.get_ID()) + 
                " height " + std::to_string(end.get_height()), 
                call_func);
        }
    }
}

void Golberg_flow_tester::test_excess_flow(const std::vector<Vertex> &vertices, const char* call_func) 
{
    for(const Vertex& vertex : vertices){
        if (vertex.get_type() != Vertex_type::SOURCE){
            TEST(vertex.get_excess_flow() >= 0, 
                "vertex " + std::to_string(vertex.get_ID()) + " has negative excess flow" + 
                std::to_string(vertex.get_excess_flow()), 
                call_func);    
        }
    }
}

void Golberg_flow_tester::test_height_limit(const std::vector<Vertex> &vertices, const char* call_func) 
{
    int limit = vertices.size() - 1;

    for(const Vertex& vertex : vertices){
        if (vertex.get_type() == Vertex_type::SOURCE){
            TEST(vertex.get_height() == limit, 
                "source " + std::to_string(vertex.get_ID()) + " height should equal " + std::to_string(limit), 
                call_func);
        } else if (vertex.get_type() == Vertex_type::TARGET){
            TEST(vertex.get_height() == 0, 
                "source " + std::to_string(vertex.get_ID()) + " height should equal 0", 
                call_func);
        } else {
            TEST(vertex.get_height() <= 2*limit, 
                "vertex " + std::to_string(vertex.get_ID()) + " has height greater than " + std::to_string(2*limit), 
                call_func);   
        } 
             
    }
}

void Golberg_flow_tester::test_flow(const std::vector<Edge> &edges, const char* call_func) 
{
    int flow = 0;
    for(const Edge& edge : edges){
        flow = edge.get_flow();
        TEST (0 <= flow && flow <= edge.get_capacity(), 
            "edge " + std::to_string(edge.get_start().get_ID()) + "->" + 
            std::to_string(edge.get_end().get_ID()) + "has wrong flow " + std::to_string(flow) + 
            ", capacity is " + std::to_string(edge.get_capacity()), call_func);
    }
}

#endif // __GOLBER_FLOW_TEST__