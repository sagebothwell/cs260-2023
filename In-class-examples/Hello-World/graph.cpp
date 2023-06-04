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

}

string Graph::minimum_spanning_tree(){

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
    
    //tests edge
    edge *newEdge = new edge{nullptr, nullptr, 42};
    cout << "newEdge->source: " << newEdge->source << "\nnewEdge->desitination: " << newEdge->destination << "\nnewEdge->weight: " << newEdge->weight << endl;
    
    //create node for test
    GraphNode *newNode = new GraphNode("testguy100");
    cout << "newNode->get_value(): " << newNode->get_value() << endl;
    cout << "newNode->getNeighbors().size(): " << newNode->Get_Neighbors().size() << endl;
    
    //add edge to node
    newNode->Add_Edge(newNode, 1);
    cout << "newNode->Get_Neighbors().size(): " << newNode->Get_Neighbors().size() << endl;
    cout << "newNode->Get_Neighbors().at(0)->destination-get_value(): " << newNode->Get_Neighbors().at(0)->destination->get_value() << endl;
    
    //delete node
    delete newNode;
    return 0;
}