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
    Goldberg_flow(int edges, int vertices, int source, int target);
    ~Goldberg_flow(){}
    
    void add_edge(int from, int to, int capacity);
    int get_max_flow();
    int number_of_edges(){return m_edges.size() / 2;}
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

    Edge& get_reverse_edge(const Edge& edge) { return m_edges[std::make_pair(edge.m_end->m_ID, edge.m_start->m_ID)];}
    Edge& get_reverse_edge(int from, int to) { return m_edges[std::make_pair(to, from)];}
    void init();
    Vertex& get_max_excess_flow_vertex();
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
Goldberg_flow::Goldberg_flow(int vertices, int edges, int source, int target) : 
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
            edge->m_end->m_excess_flow += flow; 
            edge->m_start->m_excess_flow -= flow; 
        }
    }

    test_excess_flow();
    test_flow();
    test_height_diff();
}

#ifndef NDEBUG
#include "goldberg_flow_test.h"
#endif

#endif // __GOLBER_FLOW__