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
    for(int i = 0; i < nodes.size(); i++){
        delete nodes.at(i);
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
    //Declaration of vectors which will be used throughout the function
    vector<edge*> all_edges; //a vector containing all of the possible edges that the mst could have
    vector<Graph*> graphs; //a vector which will house a graph for each node in the parent graph
    vector<edge*> mst_edges; //a vector which stores all of the edges in the minimum spanning tree. This will serve as our final product and its contents will be printed in the end

    if(this->nodes.empty()){ //checks edge case of an empty list
        return ""; //the minimum spanning tree which spans nothing is nothing
    }
    //this next segment populates the all_edges vector with all of the edges in the parent graph    
    for(auto node_index: this->nodes){ //iterate through each node in the graph
        for(auto edge_index: node_index->Get_Neighbors()){ //iterate through each node's set of edges
            all_edges.push_back(edge_index); //add each edge which is itereted to to the all_edges vector (all edges will be added)
        }
    }
    //this next segment will populate the graphs vector
    for(auto node_index : this->nodes){ //iterate through each node in the parent graph
        Graph* new_graph; //make a new graph pointer
        new_graph = new Graph; //make it point to a new graph
        new_graph->add_node(node_index->get_value()); //put a node into the new graph which shares the same name as whatever node we are currently looking at
        graphs.push_back(new_graph); //house the new graph with a single node in it in the graphs vector
    }
    //sort through all_edges and populate mst_edges
   for(auto edge_index : all_edges){
        Graph* source_graph = nullptr; //make a pointer which will point to the source of edge we are looking at
        Graph* destination_graph = nullptr; //make a pointer which will point to the destination of the edge we are looking at
        for(auto graph_index : graphs){
            if(graph_index->get_size() > 0){
                for(auto node_index : graph_index->nodes){
                    if(node_index->get_value() == edge_index->source->get_value()){ //if a value in the graphs vector shares its name with the source of the edge we are looking at
                        source_graph = graph_index; //assign the previously defined source_graph to be equal to the graph we are looking at in the graphs vector
                    }
                    //the else if will leave nodes edges which connect nodes to themselves without their destination being pointed to
                    if(node_index->get_value() == edge_index->destination->get_value()){ //if a value in the graphs vector shares its name with the destination of the edge we are looking at
                        destination_graph = graph_index; //assign the previously defined destination_graph to be equal to the graph we are looking at in the graphs vector
                    }
                }
            }
        }
        //at this point, we should have the source and destination graphs both being pointed to for a given edge
        //now, we have to decide if this edge creates a cycle or if it can go into the mst_edges vector
        if(destination_graph != nullptr && source_graph != nullptr && destination_graph != source_graph){ //this is an equivalent statement to destination graph not equalling source graph
            mst_edges.push_back(edge_index); //add the edge which starts and ends in different graphs to the mst edge collection
            //combine destination_graph and source_graph
            for(auto destination_node : destination_graph->nodes){
                source_graph->add_node(destination_node->get_value());
            }
            destination_graph->nodes.clear(); //empty out the destination graph
        }
    }
    string tree;
    for (auto edge : mst_edges) {
        tree += edge->source->get_value() + " - " + edge->destination->get_value() + "\n";
    }

    for(auto subgraphs: graphs){ //delete the graphs that were created
        delete subgraphs;
    }

    return tree;
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
    g.add_node("G");
    g.add_node("H");
    g.add_edge("A", "A", 1);
    g.add_edge("A", "B", 1);
    g.add_edge("A", "C", 1);
    g.add_edge("A", "D", 1);
    g.add_edge("D", "E", 1);
    g.add_edge("D", "F", 1);
    g.add_edge("E", "F", 1);
    g.add_edge("E", "G", 1);
    g.add_edge("F", "G", 1);
    g.add_edge("G", "H", 1);
    g.add_edge("C", "E", 1);
    g.add_edge("B", "E", 1);
    g.add_edge("F", "H", 1);
    g.add_edge("G", "C", 1);
    g.add_edge("B", "D", 1);   
    cout << g.minimum_spanning_tree();
    return 0;
}