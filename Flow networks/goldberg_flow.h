#ifndef __GOLBER_FLOW__
#define __GOLBER_FLOW__

#include "vertex.h"
#include "edge.h"

#include <functional>
#include <utility>
#include <algorithm>
#include <cstdio>

//#define NDEBUG

class Goldberg_flow
{
public:
    Goldberg_flow(){}
    Goldberg_flow(int vertices, int source, int target);
    ~Goldberg_flow();
    
    void add_edge(int from, int to, int capacity);
    int get_max_flow();
    int number_of_edges()const{return m_edges.size();}
    int number_of_vertices()const{return m_vertices.size() - 1;}
    bool edge_exists(int from, int to)const;
    const std::vector<Edge*>& vertex_neighbours(int vertex) {return m_vertices[vertex].m_edges;}

// Tests  
#ifndef NDEBUG
    void test_height_diff();
    void test_excess_flow();
    void test_height_limit();
    void test_flow();
    void test_edge(int from, int to, int capacity);
#else
    void test_height_diff(){}
    void test_excess_flow(){}
    void test_height_limit(){}
    void test_flow(){}
    void test_edge(int from, int to, int capacity){}
#endif

private:
// Private Variables
    Vertex *m_source, *m_target;
    std::vector<Vertex> m_vertices;
    std::unordered_map<std::pair<int, int>, Edge, int_pair_hash> m_edges;
    std::vector<std::list<Vertex*>> m_excessflow;
    int m_height_excessflow;

// Private Methods
    void init();
    Vertex* get_max_excess_flow_vertex();
    Edge* get_positive_residual_edge(Vertex* vertex);
    void push (Vertex* vertex, Edge* edge);
    void relable (Vertex* vertex);
    int count_max_flow();
// Debug
    void print_excessflow(int height);
    void print_unsaturated(Vertex* vertex);

    void fix_excessflow(Vertex* vertex);
    void insert_excessflow_vertex(Vertex* vertex);
    void fix_unsaturated(Edge* edge, Vertex* vertex);
    void insert_unsaturated_edge(Edge* edge, Vertex* vertex);
    void update_unsaturated_edges(Vertex* vertex);
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
        m_vertices(vertices + 1), m_excessflow(2 * vertices), m_height_excessflow(0)
{
    m_source = &m_vertices[source];
    m_target = &m_vertices[target];
}

Goldberg_flow::~Goldberg_flow() 
{
    Vertex::vertex_number = 0;
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

#ifndef NDEBUG
    test_edge(from, to, capacity);
#endif

    if (m_edges.find(edge) != m_edges.end())
        return;

    m_edges[edge] = Edge(&m_vertices[from], &m_vertices[to], capacity);
    
    m_vertices[from].m_edges.push_back(&m_edges[edge]);
    m_vertices[to].m_edges.push_back(&m_edges[edge]);
}

/**
 * Find the maximum flow and returns it
 * 
 * @return {int}  : The possible maximum flow
 */
int Goldberg_flow::get_max_flow() 
{
    init();
    Vertex* vertex = get_max_excess_flow_vertex();
    Edge* edge;  

    while (vertex != nullptr && vertex->m_excess_flow > 0)
    {
        edge = get_positive_residual_edge(vertex);       

        if (edge != nullptr)
            push(vertex, edge);
        else
            relable(vertex);

        vertex = get_max_excess_flow_vertex();
    }

    int max_flow = count_max_flow();

#ifndef NDEBUG
    std::printf("finish, max flow %d\n", max_flow);
#endif

    return count_max_flow();
}

bool Goldberg_flow::edge_exists(int from, int to) const
{
    auto edge = std::make_pair(from, to);
    return m_edges.find(edge) != m_edges.end();
}

/**
 * Initialization of Goldberg flow algorithm
 * 
 */
void Goldberg_flow::init() 
{
    m_source->m_height = number_of_vertices();
    test_height_limit();

#ifndef NDEBUG
    std::printf("init\n");
#endif

    int flow = 0;
    for (auto edge : m_source->m_edges){

        if (edge->is_outgoing(m_source)){
            flow = edge->m_capacity;

            edge->m_flow += flow;
            edge->m_reverse_flow -= flow;
            edge->m_end->m_excess_flow += flow; 
            edge->m_start->m_excess_flow -= flow; 
            fix_excessflow(edge->m_end);

#ifndef NDEBUG
            std::printf("push: from %d to %d flow %d ", m_source->m_ID, edge->m_end->m_ID, flow); 
            std::printf("| new flow %d, new rev flow %d\t", edge->m_flow, edge->m_reverse_flow);
            std::printf("| capacity %d\n", edge->m_capacity);
#endif  
        }
    }

#ifndef NDEBUG
    print_excessflow(0);
#endif 

    test_excess_flow();
    test_flow();
    test_height_diff();
}

/**
 * Finds vertex with the maximum excess flow.
 * If there aren't any, then returns null.
 * 
 * @return {Vertex*}  : Vertex with the maximum excess flow
 */
Vertex* Goldberg_flow::get_max_excess_flow_vertex() 
{
    if (m_excessflow[m_height_excessflow].size() == 0)
        return nullptr;

    return m_excessflow[m_height_excessflow].back();
}

/**
 * Finds edge with positive residual.
 * If there aren't any, then returns null.
 * 
 * @param  {Vertex*} vertex : Vertex where the edge comes from
 * @return {Edge*}          : Edge with positive residual
 */
Edge* Goldberg_flow::get_positive_residual_edge(Vertex* vertex) 
{
    int height_diff = 0;
    for(auto e : vertex->m_unsaturated){
        if (e.second->is_outgoing(vertex) || e.second->get_flow(vertex) != 0)
            return e.second;
    }
    return nullptr;
}

/**
 * Push flow from overflowing vertex along the edge
 * 
 * @param  {Vertex*} vertex : Overflowing vertex
 * @param  {Edge*} edge     : Edge along which will be pushed the flow
 */
void Goldberg_flow::push(Vertex* vertex, Edge* edge) 
{
    bool outgoing = edge->is_outgoing(vertex);
    int flow = std::min(vertex->m_excess_flow, edge->get_residual(vertex));
    flow = !outgoing && flow > edge->m_flow? edge->m_flow : flow;

    int actual_flow = outgoing? flow : -flow;
    Vertex* target = edge->get_another_vertex(vertex);

    edge->m_flow += actual_flow;
    edge->m_reverse_flow -= actual_flow;
    
    vertex->m_excess_flow -= flow;
    target->m_excess_flow += flow;

    fix_excessflow(target);
    fix_excessflow(vertex);
    fix_unsaturated(edge, vertex);

#ifndef NDEBUG
    std::printf("push: from %d to %d actual flow %d, flow %d ", vertex->m_ID, target->m_ID, actual_flow, flow); 
    std::printf("| new flow %d, source ex_flow %d\t", edge->m_flow, vertex->m_excess_flow);
    std::printf("| capacity %d\n", edge->m_capacity);
    print_unsaturated(vertex);
#endif

    test_excess_flow();
    test_flow();
}
/**
 *  Relabel vertex 
 * 
 * @param  {Vertex*} vertex : Given vertex
 */
void Goldberg_flow::relable(Vertex* vertex)
{
    m_excessflow[vertex->m_height].erase(vertex->m_excessflow_iterator);
    vertex->m_height += 1;
    insert_excessflow_vertex(vertex);

    if (vertex->m_height > m_height_excessflow)
        m_height_excessflow = vertex->m_height;

    update_unsaturated_edges(vertex);
#ifndef NDEBUG
    std::printf("relable: vertex %d, new height %d\n", vertex->m_ID, vertex->m_height);
    print_unsaturated(vertex);
#endif

    test_height_diff();
    test_height_limit();
}

/**
 * Count flow of all outgoing edges from the source)
 * 
 * @return {int}  : Return sum of all flows
 */
int Goldberg_flow::count_max_flow() 
{
    int flow = 0;
    for (auto edge : m_source->m_edges)
    {
        if (edge->is_outgoing(m_source))
            flow += edge->m_flow;
    }

    return flow;
}

void Goldberg_flow::print_excessflow(int height) 
{
    std::printf("Height %d: ", height);

    if (m_excessflow[height].size() != 0){
        for (auto v = m_excessflow[height].begin(); v != m_excessflow[height].end(); v++)
            std::printf ("%d, ", (*v)->m_ID);
    }
   
    std::printf("\n");
}

void Goldberg_flow::print_unsaturated(Vertex* vertex) 
{
    std::printf("Unsaturated edges from %d to vertices: ", vertex->m_ID);

    if (vertex->m_unsaturated.size() != 0){
        for (auto edge : vertex->m_unsaturated)
            std::printf ("%d->%d, ", edge.first.first, edge.first.second);
    }
   
    std::printf("\n");
}

void Goldberg_flow::fix_excessflow(Vertex* vertex) 
{
    if (vertex == m_source || vertex == m_target)
        return;

    int h = vertex->m_height;
    if (vertex->m_excess_flow == 0){
        vertex->m_excessflow_iterator = m_excessflow[h].erase(vertex->m_excessflow_iterator);
        vertex->m_excessflow_inserted = false;

        while (m_excessflow[m_height_excessflow].size() == 0 && m_height_excessflow > 0)
            m_height_excessflow--;
    }
    else {
        if (vertex->m_excessflow_inserted == false){
            insert_excessflow_vertex(vertex);
            vertex->m_excessflow_inserted = true;
        }
        else{
            m_excessflow[h].erase(vertex->m_excessflow_iterator);
            insert_excessflow_vertex(vertex);
        }
    }
}

void Goldberg_flow::insert_excessflow_vertex(Vertex* vertex) 
{
    int h = vertex->m_height;
    auto iter = m_excessflow[h].begin();
    int inc = 0;

    if (m_excessflow[h].size() == 0){
        vertex->m_excessflow_iterator = m_excessflow[h].insert(m_excessflow[h].begin(), vertex);
        return;
    }

    for (auto i = m_excessflow[h].begin(); i != m_excessflow[h].end(); i++)
    {
        if ((*i)->m_excess_flow < vertex->m_excess_flow){
            iter = i;
            inc++;
        }
        else break;
    }

    if (inc == m_excessflow[h].size())
        iter = m_excessflow[h].end();

    vertex->m_excessflow_iterator = m_excessflow[h].insert(iter, vertex);
}

void Goldberg_flow::fix_unsaturated(Edge* edge, Vertex* vertex) 
{
    auto e = std::make_pair(edge->m_start->m_ID, edge->m_end->m_ID);

    Vertex* another_vertex = edge->get_another_vertex(vertex);
    int height_diff = vertex->m_height - another_vertex->m_height,
        residual = edge->get_residual(vertex);

    // Residual is zero => erase the edge from the map
    if ((residual <= 0 || height_diff <= 0) && edge->m_unsaturated_inserted){
        vertex->m_unsaturated.erase(e);
        another_vertex->m_unsaturated.erase(e);
        edge->m_unsaturated_inserted = false;
    }
    else if (residual > 0 && height_diff > 0){
        // New edge => insert to the map
        if(!edge->m_unsaturated_inserted){
            insert_unsaturated_edge(edge, vertex);
            edge->m_unsaturated_inserted = true;
        }
        // Another vertex has the edge => erase the edge and insert to vertex map
        else if (another_vertex->m_unsaturated.find(e) != another_vertex->m_unsaturated.end()){
            another_vertex->m_unsaturated.erase(e);
            insert_unsaturated_edge(edge, vertex);
        }
    }     
}

void Goldberg_flow::insert_unsaturated_edge(Edge* edge, Vertex* vertex) 
{
    auto e = std::make_pair(edge->m_start->m_ID, edge->m_end->m_ID);
    vertex->m_unsaturated[e] = edge;
}

void Goldberg_flow::update_unsaturated_edges(Vertex* vertex) 
{
    for (auto edge : vertex->m_edges)
    {
        fix_unsaturated(edge, vertex);
    }
}

#ifndef NDEBUG
#include "goldberg_flow_test.h"
#endif

#endif // __GOLBER_FLOW__