#ifndef __GOLBER_FLOW_TEST__
#define __GOLBER_FLOW_TEST__

#include "goldberg_flow.h"
#include <cassert>
#include <cstdlib>

class Golberg_flow_tester
{
private:

public:

};


#ifndef NDEBUG

void Goldberg_flow::test_height_diff() 
{
    int residual = 0;
    for(const auto& e : m_edges){
        residual = e.second.get_capacity() - e.second.get_flow(e.second.m_start);
        if (residual > 0){
            assert((e.second.get_start()->get_height() - e.second.get_end()->get_height()) <= 1);
        }
    }
}

void Goldberg_flow::test_excess_flow() 
{
    for(const Vertex& vertex : m_vertices){      
        int e_flow = 0;
        for (const auto& edge : vertex.m_edges)
        {
            e_flow += edge->get_flow(edge->m_start);
        }
        
        if (vertex != *m_source){
            assert(vertex.get_excess_flow() >= 0);    
            assert(vertex.get_excess_flow() == e_flow);    
        }
    }
}

void Goldberg_flow::test_height_limit() 
{
    int limit = m_vertices.size() - 1;

    for(const Vertex& vertex : m_vertices){
        if (vertex == *m_source){
            assert(vertex.get_height() == limit);
        } else if (vertex == *m_target){
            assert(vertex.get_height() == 0);
        } else {
            assert(vertex.get_height() <= 2*limit);   
        } 
    }
}

void Goldberg_flow::test_flow() 
{
    int flow = 0;
    for(const auto& e : m_edges){
        flow = e.second.get_flow(e.second.m_start);
        assert(0 <= flow && flow <= e.second.get_capacity());
    }
}

#endif // NDEBUG

#endif // __GOLBER_FLOW_TEST__