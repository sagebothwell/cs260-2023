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
        //a bunch of getters/setters 
        void set_visited(bool);
        void set_distance(int);
        int get_distance();
        bool get_visited();
        void set_predecessor(string);
        string get_predecessor();
    private:
        //stored valued
        string value;
        //reference to neighbors
        vector<edge*> neighbors;
        //bool for shortest path
        bool visited;
        //int for distance to this node (shortest path)
        int distance;
        //string for predecessor name (shortest path)
        string predecessor;
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
        string shortest_path(string source_name, string destination_name);
        //minimum spanning tree
        string minimum_spanning_tree();
        //get size of graph nodes list
        int get_size();
        //getter for the nodes vector
        vector<GraphNode*> get_nodes();
    private:
        //some way of storing data
        vector<GraphNode *> nodes;
};

//Graph Stuff
Graph::Graph(){
 //never ended up needing this constructor to do anything
}

Graph::~Graph(){
    for(int i = 0; i < nodes.size(); i++){ //for all nodes 
        delete nodes.at(i); //delete the nodes
    }
}

vector<GraphNode*> Graph::get_nodes(){
    return this->nodes;
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

string Graph::shortest_path(string source_name, string destination_name){
    if(source_name == destination_name){
        return source_name;
    }
    for(auto node : this->nodes){ //go through each node in the graph
        node->set_visited(false); //set each node in the graph to unvisted
        node->set_predecessor(""); //set the name of the predecessor to an empty string
        if(node->get_value() != source_name){
            node->set_distance(this->nodes.size()+1); //unweighted graph, at largest a distance can be going through each spot once, thus this is effectively infinity
        }
        else{
            node->set_distance(0); //the source node is already at the source node
        }
    }
    int index = 0; //make an index which will increase as we visit nodes
    while(index <= this->nodes.size()){ //while we have not gone through each node
        index++; //increase index
        int small_val = this->nodes.size()+1; //new int for the smallest distance to visit
        for(auto node : this->nodes){ //go through each node
            if(node->get_distance() <= small_val && node->get_visited() == false){ //if a nonvisited node has a smaller distance than small_val
                small_val = node->get_distance(); //update small_val when we find a path with a smaller val
            }
        }
        //now we know the smallest distance held in an unvisted node
        for(auto node : this->nodes){ //go through each node
            if(node->get_distance() == small_val && node->get_visited() == false){ //if at the unvisted node with smallest distance
                node->set_visited(true); //set this node to visited
                for(auto edge : node->Get_Neighbors()){ //for each of this node's edges
                    if(edge->destination->get_distance() > node->get_distance()+1){ //if we find a new shortest path to a node
                        edge->destination->set_distance(node->get_distance()+1); //update the distance to the node to this new shortest path
                        edge->destination->set_predecessor(node->get_value()); //update the node's predecessor to the node before it in the path
                    }
                }
                break;
            }
        }
    }
    //Now, each node should have the shortest path from the source found along with predecessors, so now we just have to print the desired part
    string shortest_path;
    GraphNode* destination_node = nullptr;
    // Find the destination node
    for (auto node : this->nodes) {
        if (node->get_value() == destination_name) {
            destination_node = node;
            break;
        }
    }
    if (destination_node != nullptr && destination_node->get_distance() <= this->nodes.size()) { //I think this this is always passed but never can be too safe!
        // Traverse the predecessors from destination to source to construct the shortest path string
        GraphNode* current_node = destination_node;
        while (current_node != nullptr) {
            shortest_path = current_node->get_value() + " " + shortest_path;
            string predecessor_name = current_node->get_predecessor();
            if (predecessor_name != "") { //checks to make sure a predecessor exists (it doesnt for non source node)
                for (auto node : this->nodes) {
                    if (node->get_value() == predecessor_name){
                        current_node = node; //set current to the old predecessor
                        break;
                    }
                }
            } 
            else {
                current_node = nullptr; //if at source node, set current to nullptr to escape (still adds source node to the string though)
            }
        }
    }
    else{
        return "Either no path exists from node " + source_name + " to " + destination_name + " or the node(s) you inputted do not exist!";
    }

    return shortest_path;
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
            all_edges.push_back(edge_index); //add each edge which is iterated to to the all_edges vector (all edges will be added)
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
        tree += edge->source->get_value() + " - " + edge->destination->get_value() + "\n"; //creates a string displaying all edges in the mst
    }
    for(auto subgraphs: graphs){ //delete the graphs that were created
        delete subgraphs;
    }
    return tree;
}

//GraphNode stuff
GraphNode::GraphNode(string name){ //basic comstructor, set node name
    value = name;
}

//a bunch of getters and setters, not much to say
void GraphNode::set_visited(bool visit){
    this->visited = visit;
}

void GraphNode::set_distance(int dist){
    this->distance = dist;
}

int GraphNode::get_distance(){
    return this->distance;
}

bool GraphNode::get_visited(){
    return this->visited;
}

void GraphNode::set_predecessor(string name){
    this->predecessor = name;
}

string GraphNode::get_predecessor(){
    return this->predecessor;
}

GraphNode::~GraphNode(){
    for(auto neighbor: neighbors){ //for all neighbors in a nodes edge vector
        delete neighbor; //delete the neighbors
    }
    neighbors.clear(); //clear the vector
}

void GraphNode::Add_Edge(GraphNode *destination, int weight){
    edge* newEdge = new edge{this, destination, weight}; //make a new edge on the heap
    neighbors.push_back(newEdge); //put it into the nodes edge vector
}

vector<edge*> GraphNode::Get_Neighbors(){
    return neighbors;
}

string GraphNode::get_value(){
    return this->value;
}

int main(){
    //first tests with g
    Graph g;
    //building a graph with 8 nodes and 17 edges
    cout << "To begin the tests, I will create the same graph 1 as detailed in the read me (8 nodes and 17 edges). \n";
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
    g.add_edge("G", "G", 1); 
    g.add_edge("H", "H", 1);
    g.add_edge("B", "H", 1); 
    //testing minimal spanning tree (expects 8 nodes but only 7 edges) 
    cout << endl << "[add_node test] Number of nodes in the graph (Expecting 8): " << g.get_size() << endl;
    cout << "[add_edge test] Number of edges connected to node E (Expecting 5): " << g.get_nodes().at(4)->Get_Neighbors().size() << endl;
    cout << "[minimum_spanning_tree test] Minimum Spanning Tree of Graph 1 (Expecting 7 edges and a fully connected graph): \n";
    cout << g.minimum_spanning_tree();
    //testing shortest path
    cout << "[shortest_path test] Shortest path from A to A (expecting just A): " << g.shortest_path("A", "A") << endl;
    cout << "[shortest_path test] Shortest path from A to B (Expecting A B): " << g.shortest_path("A", "B") << endl;
    cout << "[shortest_path test] Shortest path from A to C (Expecting A C): " << g.shortest_path("A", "C") << endl;
    cout << "[shortest_path test] Shortest path from A to D (Expecting A D): " << g.shortest_path("A", "D") << endl;
    cout << "[shortest_path test] Shortest path from A to E (Expecting A B E): " << g.shortest_path("A", "E") << endl;
    cout << "[shortest_path test] Shortest path from A to F (Expecting A D F): " << g.shortest_path("A", "F") << endl;
    cout << "[shortest_path test] Shortest path from A to G (Expecting A C G): " << g.shortest_path("A", "G") << endl;
    cout << "[shortest_path test] Shortest path from A to H (Expecting A B H): " << g.shortest_path("A", "H") << endl;
    cout << "[shortest_path test] Shortest path from C to H (Expecting C G H): " << g.shortest_path("C", "H") << endl;

    //second test with g2
    cout << endl << "Next, we will test Graph 2 as detailed in the read me (6 nodes 12 edges):\n";
    Graph g2;
    g2.add_node("A");
    g2.add_node("B");
    g2.add_node("C");
    g2.add_node("D");
    g2.add_node("E");
    g2.add_node("F");
    g2.add_edge("A","B",1);
    g2.add_edge("A","C",1);
    g2.add_edge("B","B",1);
    g2.add_edge("C","B",1);
    g2.add_edge("A","E",1);
    g2.add_edge("E","B",1);
    g2.add_edge("A","D",1);
    g2.add_edge("D","C",1);
    g2.add_edge("E","C",1);
    g2.add_edge("E","F",1);
    g2.add_edge("F","C",1);
    g2.add_edge("E","E",1);
    //second test for spanning tree
    cout << endl << "[add_node test] Number of nodes in the graph (Expecting 6): " << g2.get_size() << endl;
    cout << "[add_edge test] Number of edges connected to node A (Expecting 4): " << g2.get_nodes().at(0)->Get_Neighbors().size() << endl;
    cout << "[minimum_spanning_tree test] Minimum Spanning Tree of Graph 2 (Expecting 5 edges and a fully connected graph):\n";
    cout << g2.minimum_spanning_tree();
    //second set of tests for shortest path
    cout << "[shortest_path test] Shortest path from A to F (Expecting A C F): " << g2.shortest_path("A", "F") << endl;
    cout << "[shortest_path test] Shortest path from D to B (Expecting D A B): " << g2.shortest_path("D", "B") << endl;
    cout << "[shortest_path test] Shortest path from F to B (Expecting F C B): " << g2.shortest_path("F", "B") << endl;
    cout << "[shortest_path test] Shortest path from E to E (Expecting just E): " << g2.shortest_path("E", "E") << endl;
    cout << "[shortest_path test] Shortest path from C to A (Expecting C A): " << g2.shortest_path("C", "A") << endl;
    
    //weird graph test
    cout << endl << "Finally, we will test Graph 3 as detailed in the read me (5 nodes 2 edges):\n";
    Graph g3;
    g3.add_node("A");
    g3.add_node("B");
    g3.add_node("C");
    g3.add_node("D");
    g3.add_node("E");
    g3.add_edge("A","B",1);
    g3.add_edge("C","D",1);
    cout << endl << "[add_node test] Number of nodes in the graph (Expecting 5): " << g3.get_size() << endl;
    cout << "[add_edge test] Number of edges connected to node E (Expecting 0): " << g3.get_nodes().at(4)->Get_Neighbors().size() << endl;
    cout << "[add_edge test] Number of edges connected to node B (Expecting 1): " << g3.get_nodes().at(1)->Get_Neighbors().size() << endl;
    //third test for spanning tree
    cout << "[minimum_spanning_tree test] Minimum Spanning Tree of Graph 3 (Expecting the edges A - B and C - D):\n";
    cout << g3.minimum_spanning_tree();
    //third set of tests for shortest path
    cout << "[shortest_path test] Shortest path from A to B (Expecting A B): " << g3.shortest_path("A", "B") << endl;
    cout << "[shortest_path test] Shortest path from C to D (Expecting C D): " << g3.shortest_path("C", "D") << endl;
    cout << "[shortest_path test] Shortest path from A to C (Expecting error mssg): " << g3.shortest_path("A", "C") << endl;
    cout << "[shortest_path test] Shortest path from E to A (Expecting error mssg): " << g3.shortest_path("E", "A") << endl;
    cout << "[shortest_path test] Shortest path from B to D (Expecting error mssg): " << g3.shortest_path("B", "D") << endl;
    cout << "[shortest_path test] Shortest path from B to fake_node (Expecting error mssg): " << g3.shortest_path("B", "fake_node") << endl;
    cout << "Tests Complete!";
    return 0;
}