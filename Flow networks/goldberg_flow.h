#ifndef __GOLBER_FLOW__
#define __GOLBER_FLOW__

#include "vertex.h"
#include "edge.h"
#include <unordered_map>
#include <functional>
#include <utility>

//#define NDEBUG

struct int_pair_hash {
    std::size_t operator () (const std::pair<int,int> &p) const {
        auto h1 = std::hash<int>{}(p.first);
        auto h2 = std::hash<int>{}(p.second);

        return h1 ^ h2;  
    }
};

class Goldberg_flow
{
public:
    Goldberg_flow(){}
    Goldberg_flow(int vertices, int source, int target);
    ~Goldberg_flow(){}
    
    void add_edge(int from, int to, int capacity);
    int get_max_flow();
    int number_of_edges(){return m_edges.size();}
    int number_of_vertices(){return m_vertices.size() - 1;}

#ifndef NDEBUG
    void test_height_diff();
    void test_excess_flow();
    void test_height_limit();
    void test_flow();
#else
    void test_height_diff(){}
    void test_excess_flow(){}
    void test_height_limit(){}
    void test_flow(){}
#endif

private:
    Vertex *m_source, *m_target;
    std::vector<Vertex> m_vertices;
    std::unordered_map<std::pair<int, int>, Edge, int_pair_hash> m_edges;

    void init();
    Vertex* get_max_excess_flow_vertex();
    Edge* get_positive_residual_edge();
    void push (Edge& edge);
    void relable (Vertex& vertex);
};
/**
 * initialization constructor
 * 
 * @param  {int} edges    : Number of edges
 * @param  {int} vertices : Number of vertices
 * @param  {int} source   : Index of source vertex
 * @param  {int} target   : Index of target vertex
 */
Goldberg_flow::Goldberg_flow(int vertices, int source, int target) : 
        m_vertices(vertices + 1) 
{
    m_source = &m_vertices[source];
    m_target = &m_vertices[target];
}

/**
 * Add new edge from the vertex to another vertex
 * 
 * @param  {int} from     : Index of the vertex where the edge starts from
 * @param  {int} to       : Index of the vertex where the edge comes to
 * @param  {int} capacity : Capacity of the edge
 */
void Goldberg_flow::add_edge(int from, int to, int capacity) 
{
    auto edge = std::make_pair(from, to);

    if (m_edges.find(edge) != m_edges.end())
        return;

    m_edges[edge] = Edge(&m_vertices[from], &m_vertices[to], capacity);
    
    m_vertices[from].m_edges.push_back(&m_edges[edge]);
    m_vertices[to].m_edges.push_back(&m_edges[edge]);
}


int Goldberg_flow::get_max_flow() 
{
    init();
    Vertex* vertex = get_max_excess_flow_vertex();
    Edge* edge;

    while (vertex != m_source && vertex != m_target && vertex->m_excess_flow > 0)
    {
        edge = get_positive_residual_edge();

        if (edge != nullptr)
            push(*edge);
        else
            relable(*vertex);

        vertex = get_max_excess_flow_vertex();
    }
    

    return 0;
}

/**
 * Initialization of Goldberg flow algorithm
 * 
 */
void Goldberg_flow::init() 
{
    m_source->m_height = number_of_vertices();
    test_height_limit();

    int flow = 0;
    for (auto edge : m_source->m_edges){
        if (edge->is_outgoing(m_source)){
            flow = edge->m_capacity;

            edge->m_flow += flow;
            edge->m_reverse_flow -= flow;
            edge->m_end->m_excess_flow += flow; 
            edge->m_start->m_excess_flow -= flow; 
        }
    }

    test_excess_flow();
    test_flow();
    test_height_diff();
}

Vertex* Goldberg_flow::get_max_excess_flow_vertex() 
{
    Vertex* max = &m_vertices[0];
    for(auto &vertex: m_vertices){
        if (vertex.m_excess_flow > max->m_excess_flow)
            max = &vertex;
    }

    return max;
}

Edge* Goldberg_flow::get_positive_residual_edge() 
{
    int residual = 0, height_diff = 0;
    for(auto &e : m_edges){
        residual = e.second.m_capacity - e.second.m_flow;
        height_diff = e.second.m_start->m_height - e.second.m_end->m_height;
        if (residual > 0 && height_diff > 1)
            return &e.second;
    }
    return nullptr;
}

void Goldberg_flow::push(Edge& edge) 
{
    
}

void Goldberg_flow::relable(Vertex& vertex) 
{
    
}

#ifndef NDEBUG
#include "goldberg_flow_test.h"
#endif

#endif // __GOLBER_FLOW__