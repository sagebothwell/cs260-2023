#include <string>
#include <vector>
#include <iostream>

using namespace std;
class GraphNode;

struct edge {
    GraphNode* source;
    GraphNode* destination;
    int weight;
};

class GraphNode {
    public:
        //constructor
        GraphNode(string name);
        //add edge
        void Add_Edge(GraphNode *destination, int weight);
        //get neighbors as a list of pointers
        vector<edge*> Get_Neighbors();
        //get value of node
        string get_value();
        ~GraphNode();
    private:
        //stored valued
        string value;
        //reference to neighbors
        vector<edge*> neighbors;
};

class Graph{
    public:
        //constructor
        Graph();
        //destructor
        ~Graph();
        //add node
        void add_node(string newName);
        //add edge
        void add_edge(string sourceName, string destinationName, int weight);
        //shortest path, take source and return string representing shortest paths from source to each destination node
        string shortest_path(string sourceName);
        //minimum spanning tree
        string minimum_spanning_tree();
        //get size of graph nodes list
        int get_size();
    private:
        //some way of storing data
        vector<GraphNode *> nodes;
};

//Graph Stuff
Graph::Graph(){

}

Graph::~Graph(){
    for(auto node : nodes){
        for(auto edge : node->Get_Neighbors()){
            delete edge;
        }
        delete node;
    }
}

int Graph::get_size(){
    return this->nodes.size();
}

void Graph::add_node(string newName){
    GraphNode* new_node = new GraphNode(newName);
    nodes.push_back(new_node);
}

void Graph::add_edge(string sourceName, string destinationName, int weight){
    //find source/destination node reference
    GraphNode* source = nullptr;
    GraphNode* destination = nullptr;
    for(auto node : nodes){
        if(node->get_value() == sourceName){
            source = node;
        }
        if(node->get_value() == destinationName){
            destination = node;
        }
    }
    //make an edge between them
    if(source != nullptr && destination != nullptr){
        source->Add_Edge(destination, weight);
        destination->Add_Edge(source, weight);
    }
}

string Graph::shortest_path(string sourceName){
    return "";
}

string Graph::minimum_spanning_tree(){
    // Minimum Spanning Tree algorithm (using Kruskal's algorithm)
    if (nodes.empty()) {
        return "";
    }
    // Sort all edges
    vector<edge*> allEdges;
    for (auto& node : nodes) {
        for (auto& edge : node->Get_Neighbors()) {
            allEdges.push_back(edge);
        }
    }
    // Create a vector of individual graphs for each node
    vector<Graph*> nodeGraphs;
    for (auto& node : nodes) {
        Graph* newGraph = new Graph();
        newGraph->add_node(node->get_value());
        nodeGraphs.push_back(newGraph);
    }
    // Create a vector to store the edges of the minimum spanning tree
    vector<edge*> minimumSpanningTreeEdges;
    // Combine smaller graphs into a final minimum spanning tree graph
    for (auto& edge : allEdges) {
        // Find the graphs that contain the source and destination nodes of the edge
        Graph* sourceGraph = nullptr;
        Graph* destinationGraph = nullptr;
        for (auto& graph : nodeGraphs) {
            if (graph->get_size() > 0) {
                if (graph->nodes[0]->get_value() == edge->source->get_value()) {
                    sourceGraph = graph;
                }
                if (graph->nodes[0]->get_value() == edge->destination->get_value()) {
                    destinationGraph = graph;
                }
            }
        }
        // Combine the graphs if they are not the same
        if (sourceGraph != nullptr && destinationGraph != nullptr && sourceGraph != destinationGraph) {
            // Add the edge to the minimum spanning tree
            minimumSpanningTreeEdges.push_back(edge);            
            // Merge destinationGraph into sourceGraph
            for (auto& node : destinationGraph->nodes) {
                sourceGraph->add_node(node->get_value());
            }
            for (auto& node : destinationGraph->nodes) {
                for (auto& neighbor : node->Get_Neighbors()) {
                    sourceGraph->add_edge(node->get_value(), neighbor->destination->get_value(), neighbor->weight);
                }
            }
            // Clear the destinationGraph
            destinationGraph->nodes.clear();
        }
    }
    // Delete the smaller graphs
    for (auto& graph : nodeGraphs) {
        delete graph;
    }
    // Build the string representation of the minimum spanning tree
    string result;
    for (auto& edge : minimumSpanningTreeEdges) {
        result += edge->source->get_value() + " - " + edge->destination->get_value() + "\n";
    }
    return result;
}

//GraphNode stuff
GraphNode::GraphNode(string name){
    value = name;
}

GraphNode::~GraphNode(){
    for(auto neighbor: neighbors){
        delete neighbor;
    }
    neighbors.clear();
}

void GraphNode::Add_Edge(GraphNode *destination, int weight){
    edge* newEdge = new edge{this, destination, weight};
    neighbors.push_back(newEdge);
}

vector<edge*> GraphNode::Get_Neighbors(){
    return neighbors;
}

string GraphNode::get_value(){
    return this->value;
}

int main(){

    Graph g;
    g.add_node("A");
    g.add_node("B");
    g.add_node("C");
    g.add_node("D");
    g.add_node("E");
    g.add_node("F");
    g.add_edge("A", "B", 1);
    g.add_edge("A", "C", 1);
    g.add_edge("A", "D", 1);
    g.add_edge("B", "C", 1);
    g.add_edge("D", "C", 1);
    g.add_edge("B", "E", 1);
    g.add_edge("E", "F", 1);
    g.add_edge("F", "C", 1);
    g.add_edge("E", "C", 1);
    cout << g.minimum_spanning_tree();
    return 0;
}