#ifndef __GOLBER_FLOW__
#define __GOLBER_FLOW__

#include "vertex.h"
#include "edge.h"

#include <functional>
#include <utility>
#include <algorithm>
#include <cstdio>

//#define NDEBUG

using edge_pair = std::pair<int, int>;

struct int_pair_hash {
    std::size_t operator () (const edge_pair &p) const {
        auto h = sizeof(size_t) * 8 / 2;
        auto a = std::hash<int>{}(p.first);
        return ((a << h) | (a >> h)) ^ std::hash<int>{}(p.second);  
    }
};

class Goldberg_flow
{
public:
    Goldberg_flow(int vertices, int source, int target);
    ~Goldberg_flow(){};
    
    void add_edge(int from, int to, int capacity);
    int get_max_flow();
    int number_of_edges()const{return m_edges.size();}
    int number_of_vertices()const{return m_vertices.size() - 1;}
    bool edge_exists(int from, int to)const;
    const std::vector<Edge*>& vertex_neighbours(int vertex) {return m_vertices[vertex].m_edges;}
    void print_graph();
    void print_flow_edges();
    int get_index(Vertex *v)const{return (v - &m_vertices[0]);}

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
    // Variables
    Vertex *m_source, *m_target;
    std::vector<Vertex> m_vertices;
    std::unordered_map<edge_pair, Edge, int_pair_hash> m_edges;
    std::vector<std::list<Vertex*>> m_excessflow;
    int m_height_excessflow;

    // Methods
    void init();
    Vertex* get_max_excess_flow_vertex();
    Edge* get_positive_residual_edge(Vertex* vertex);
    void push (Vertex* vertex, Edge* edge);
    void relable (Vertex* vertex);

    // Debug
    void print_excessflow(int height);
    void print_unsaturated(Vertex* vertex);

    // Improved
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
        m_vertices(vertices), m_excessflow(2 * vertices), m_height_excessflow(0)
{
    m_source = &m_vertices[source - 1];
    m_target = &m_vertices[target - 1];
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
    from -= 1;
    to -= 1;

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

    int max_flow = m_target->m_excess_flow;

#ifndef NDEBUG
    std::printf("finish, max flow %d\n", max_flow);
#endif

    return max_flow;
}

/**
 * Check if given edge exists
 * 
 * @param  {int} from : ID of outgoing vertex
 * @param  {int} to   : ID of incoming vertex
 * @return {bool}     : False if the edge doesn't exist
 */
bool Goldberg_flow::edge_exists(int from, int to) const
{
    auto edge = std::make_pair(from, to);
    return m_edges.find(edge) != m_edges.end();
}

/**
 * Print information (outgoing vertex, incoming vertex of edges and their capacity)
 * 
 */
void Goldberg_flow::print_graph() 
{
    for (auto& e : m_edges)
    {
        printf("%d %d %d\n", get_index(e.second.m_start), get_index(e.second.m_end), e.second.m_capacity);
    }
}

/**
 * Print all edges that have positive flow
 * 
 */
void Goldberg_flow::print_flow_edges()
{
    std::unordered_map<edge_pair, bool, int_pair_hash> used;

    for (auto & edge : m_edges)
    {
        if (used.find(edge.first) != used.end() || edge.second.m_flow == 0)
            continue;

        auto rev_edge =  m_edges.find(std::make_pair(edge.first.second, edge.first.first));
        if (rev_edge != m_edges.end()){
            printf("%d %d %d\n", edge.first.first, edge.first.second, edge.second.m_flow - rev_edge->second.m_flow);
            used[rev_edge->first] = true;
        }
        else{
            printf("%d %d %d\n", edge.first.first, edge.first.second, edge.second.m_flow);
        }
        used[edge.first] = true;
    }
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
            edge->m_end->m_excess_flow += flow; 
            edge->m_start->m_excess_flow -= flow; 
            fix_excessflow(edge->m_end);
#ifndef NDEBUG
            std::printf("push: from %d to %d flow %d ", get_index(m_source), get_index(edge->m_end), flow); 
            std::printf("| new flow %d\t", edge->m_flow);
            std::printf("| capacity %d\n", edge->m_capacity);
#endif  
        }
    }

#ifndef NDEBUG
    print_excessflow(0);

    test_excess_flow();
    test_flow();
    test_height_diff();
#endif 
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
    if (vertex->m_unsaturated.size() == 0)
        return nullptr;

    return vertex->m_unsaturated.back();
}

/**
 * Pushes flow from overflowing vertex along the edge
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

    vertex->m_excess_flow -= flow;
    target->m_excess_flow += flow;

    fix_excessflow(target);
    fix_excessflow(vertex);
    fix_unsaturated(edge, vertex);

#ifndef NDEBUG
    std::printf("push: from %d to %d actual flow %d, flow %d ", get_index(vertex), get_index(target), actual_flow, flow); 
    std::printf("| new flow %d, source ex_flow %d\t", edge->m_flow, vertex->m_excess_flow);
    std::printf("| capacity %d\n", edge->m_capacity);
    print_unsaturated(vertex);

    test_excess_flow();
    test_flow();
#endif
}

/**
 *  Relabels vertex 
 *  (updates height, excessflow vector and all edges of the vertex)
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
    std::printf("relable: vertex %d, new height %d\n", get_index(vertex), vertex->m_height);
    print_unsaturated(vertex);
    test_height_diff();
    test_height_limit();
#endif
}

/**
 * Prints all vertecies of the given height
 * 
 * @param  {int} height : Height 
 */
void Goldberg_flow::print_excessflow(int height) 
{
    std::printf("Height %d: ", height);

    if (m_excessflow[height].size() != 0){
        for (auto v = m_excessflow[height].begin(); v != m_excessflow[height].end(); v++)
            std::printf ("%d, ", get_index(*v));
    }
   
    std::printf("\n");
}

/**
 * Prints all unsaturated edges for the given vertex
 * 
 * @param  {Vertex*} vertex : Vertex
 */
void Goldberg_flow::print_unsaturated(Vertex* vertex) 
{
    std::printf("Unsaturated edges from %d to vertices: ", get_index(vertex));

    if (vertex->m_unsaturated.size() != 0){
        for (auto edge : vertex->m_unsaturated)
            std::printf ("%d->%d, ", get_index(edge->m_start), get_index(edge->m_end));
    }
   
    std::printf("\n");
}

/**
 * Erases or inserts vertex to the excessflow vector based on the excess flow.
 * 
 * @param  {Vertex*} vertex : The vertex to be changed
 */
void Goldberg_flow::fix_excessflow(Vertex* vertex) 
{
    if (vertex == m_source || vertex == m_target)
        return;

    int h = vertex->m_height;
    // Excess flow is zero => remove from the vector and decrese max height
    if (vertex->m_excess_flow == 0){
        m_excessflow[h].erase(vertex->m_excessflow_iterator);
        vertex->m_excessflow_iterator = m_excessflow[h].end();
        vertex->m_excessflow_inserted = false;

        while (m_excessflow[m_height_excessflow].size() == 0 && m_height_excessflow > 0)
            m_height_excessflow--;
    }
    // Vertex wasn't inserted before => insert to the vector 
    else if (vertex->m_excessflow_inserted == false){
            insert_excessflow_vertex(vertex);
            vertex->m_excessflow_inserted = true;
    }
}

/**
 * Inserts vertex with excess flow to the vector
 * 
 * @param  {Vertex*} vertex : Vertex with excess flow
 */
void Goldberg_flow::insert_excessflow_vertex(Vertex* vertex) 
{
    int h = vertex->m_height;
    vertex->m_excessflow_iterator = m_excessflow[h].insert(m_excessflow[h].begin(), vertex);
}


/**
 * Erases or inserts edge to the list of unsaturated edges 
 * based on the residual value and height difference
 * 
 * @param  {Edge*} edge     : Unsaturated edge
 * @param  {Vertex*} vertex : Vertex
 */
void Goldberg_flow::fix_unsaturated(Edge* edge, Vertex* vertex) 
{
    Vertex* another_vertex = edge->get_another_vertex(vertex);
    int height_diff = vertex->m_height - another_vertex->m_height,
        residual = edge->get_residual(vertex);

    // Residual is zero => erase the edge from the list
    if ((residual <= 0 || height_diff <= 0) && edge->m_unsaturated_placeID != 0){
        if (get_index(vertex) == edge->m_unsaturated_placeID)
            edge->m_unsaturated_iterator = vertex->m_unsaturated.erase(edge->m_unsaturated_iterator);
        else if (get_index(another_vertex) == edge->m_unsaturated_placeID)
            edge->m_unsaturated_iterator = another_vertex->m_unsaturated.erase(edge->m_unsaturated_iterator);

        edge->m_unsaturated_placeID = 0;
    }
    else if (residual > 0 && height_diff > 0){
        // New edge => insert to the list
        if(edge->m_unsaturated_placeID == 0){
            insert_unsaturated_edge(edge, vertex);
        }
        // Another vertex has the edge => erase the edge and insert to vertex list
        else if (get_index(another_vertex) == edge->m_unsaturated_placeID){
            another_vertex->m_unsaturated.erase(edge->m_unsaturated_iterator);
            insert_unsaturated_edge(edge, vertex);
        }
    }     
}

/**
 * Inserts unsaturated edge to the vertex
 * 
 * @param  {Edge*} edge     : Unsaturated edge
 * @param  {Vertex*} vertex : Vertex
 */
void Goldberg_flow::insert_unsaturated_edge(Edge* edge, Vertex* vertex) 
{
    edge->m_unsaturated_iterator = vertex->m_unsaturated.insert(vertex->m_unsaturated.begin(), edge);
    edge->m_unsaturated_placeID = get_index(vertex);
}

/**
 * Checks all edges for the given vertex and 
 * updates them based on the residual value and height difference
 * 
 * @param  {Vertex*} vertex : Vertex
 */
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