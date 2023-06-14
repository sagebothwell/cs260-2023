NOTE: This whole README is my design, but I also put the complexity analysis and lines where I meet the requrements stuff into this README. Below is a table of 
contents which describes where everything can be found.

Table of Contents:
Design for my Graph - line 19
Description of Minimum Spanning Tree Function - line 38
Pseudocode for Minimum Spanning Tree Function - line 47
Complexity Analysis for Minimum Spanning Tree Function - line 92
Description of Shortest Path Function - line 145
Pseudocode for Shortest Path Function - line 153
Conplexity Analysis for Shortest Path Function - line 183
Add Node/Add Edge Functions - line 207
Complexity of the Adding Functions - line 212
Extraneous Functions - line 218
Possible Tests - line 224
Where Stuff Shows up in the Code - line 293
A problem that graphs can solve - line 301

Design for my graph:
My graph will be an unweighted undirected graph. My add node and add edge functions will be the same as we wrote in class, and the minimum spannning tree and
shortest path functions will be designed with Kruskal's and Djikstra's algorithms respectively. 
The Graph will be a class which will contain the 4 required functions, a constructor/destructor, and a private member vector of GraphNodes.
GraphNodes will also be a class with a constructor/destructor, a function for adding edges, and getters/setters for its private member variables.
    GraphNode private member variables:
        -a string to store the GraphNode's name
        -a vector containing all of the edges connected to the GraphNode
        -a bool to say if the node has been visited (for shortest path)
        -an int to say the distance a node is from some other node (for shortest path)
        -a string whioch says what the GraphNode's predecessor is in the shortest path algorithm (only used in shortest path)
Finally, the Edge will be a struct which contains two GraphNode pointers for the edge's source and destination and an int for weight.
***Note, while weight is present in my Edge struct and does show up in some of the functions, I ultimately descided not to use it, I could have gone back and deleted all
instances of weight, but by the time I decided not to use it I was already too deep. As it stands, it is an unused member variable which is always set to 1.

After finishing my design, here are a few things that I found will be required in my graph:
    -Each node in the graph must have a ditsinct name (breaks minimum spanniong tree and shortest path)
    -No node in the graph may be named "", which represents the empty string (breaks shortest path)

Minimum Spanning Tree:
For this function, I will follow Kruskal's algorithm. Because I will not be using edge weights, I will slightly alter Kruskal's algorithm to just find a spanning
tree with the minimal number of edges (i.e. if I have n nodes, it will find a tree with n-1 edges). Without accounting for edge weights, there are very few times that
there will be a single unique spanning tree, so my algorithm will run until it finds the first of these trees. 
Another small deviation I will take from Kruskal's algorithm is that I will not use sets, instead, I will make a vector of graphs, where each graph begins by housing a
single node. I will then go through the edges and merge these graphs as I go, just as what happens to the sets in Kruskal's algorithm. 
Finally, intead of actually making the minimum spanning tree, I will just find the edges of the minimum spanning tree and print those out, as that should be an easy way
of outputting what the tree should look like.

Pseudocode for minimum spanning tree:
if the graph is empty, return an empty string
create a vector for edges
for all nodes in the graph, iterate through each edge in their respective edge vectors and add each edge iterated to to the new vector for edges

Now we should have a vector which contains every edge in the graph. It may contain some repeats, but its not worth thinking much about because Kruskal's algorithm 
accounts for this later.

create a vector for graphs
for each node in the parent graph, make a new graph and add a node with the same name to the new graph vector
Note: we should not need to add any edges because those will be added later, this is all just part of the set update

Now, we have the graph vector which I described above created

create a new vector for edges, this vector will hold the edges in the minimum spanning tree
for all edges in the edge vector which contains all edges:
    Create two graph pointers, one which points to the source graph and one which points to the destination graph, set them both to null originally
    for all the graphs in the new graph vector:
        if the graph is not empty: (this will be important because of line 44 of the read me)
            for each node in a given graph:
                if a given node's name matches the name of a given edge's source, make the source graph pointer point to whatever graph we are in
                if a given node's name matches the name of a given edge's destination, make the destination graph pointer point to whatever graph we are in\
                Note: This requires that each node is named differently, so that is a requirement of my graph for it to work

    Now, both pointers should have found their respective graphs to point to

    if either pointer is still at null, or if the two pointers are pointing to the same graph:
        add whatever edge we are currentltyy looking at to the edge vector for minimum spanning tree edges
        for all nodes in the destination graph:
            add the nodes to the source graph
        empty the destination graph (this is why above we skip empty graphs, its part of my merge process)

Now, we should have a vector full of only minimum spanning tree edges.

Make a new results string

for each edge in the minimum spanning tree edges vector:
    add the edges source to the string, add " - ", and add the destination, and finally add "\n"
return the string

Example Output for a graph with 4 nodes A, B, C, and D where the edges in the minimum spanning tree are between A and B, B and D, and A and C:
A - B
A - C
B - D

Complexity of this algorithm:

In the beginning, the check for an empty graph edge case has complexity O(1)

Next, the creation and filling of a vector with all graph edges (assuming we have no repeats) has complexity  O(n^2)
This is because the maximum number of edges in an undirected graph with n edges is n + n(n-1)/2 
Proof by Inudction:
Consider the base case with 1 node, there is 1 possible edge which goes from this node to itself.
Further, 1 + 1(1-1)/2 = 1, so the base case works

Now assume that the claim holds through (n-1) nodes and consider a graph with n nodes.
To begin, we can make n edges from the first edge to every other edge including itself.
Now, we have (n-1) nodes remaining with no direct connections between eachother. Because
our cl;aim holkds for (n-1) nodes, we know there can be a maximum of (n-1)+(n-1)(n-2)/2 connections
here.

Thus, there is a max of n+(n-1)+(n-1)(n-2)/2 nodes in this graph, and further:

n+(n-1)+(n-1)(n-2)/2 = n+(n-1)+(n^2-3n+2)/2
                     = (4n-2+n^2-3n+2)/2
                     = (2n+n^2-n/)2
                     = n + n(n-1)/2

Thus, the claim holds for n and therefore by induction holds for all n.

So, we know worst case scenario (assuming no repeats) this part of the function has complexity O(n + (n^2-n)/2)
which we can simplify down to O(n^2).

Next, filling the vector of graphs with n graphs for n nodes has complexity of O(n)

Next, making the destination and source graph pointers point to the right places has complexity of O(n^3) because:
we go through each edge (max complexity of O(n^2) as seen before)
and for each edge go through each node (complexity of O(n) for n nodes)
and then  we do constant complexity stuff when we find fitting nodes (O(1))
So, this portion has complexity O(1*n*n^2) = O(n^3)

Checking if an edge should be added to the minimum spanning tree and adding it if so has complexity O(1)

In the merging process, we have up to O(n) complexity to go through what could be n-1 nodes in destination graph and add them to source graph
clearing the destination graph of nodes has complexity of O(1) because it is a prebuilt function in vectors (I think its O(1), but it may be O(n), 
ultimately it won't matter)

These processes happen for at each edge, so the overall complexity of this segment is O(n^3).

Finally, we have O(n) complexity to fill the string with minimum spanning trees because the tree will have n-1 complexity and we will have O(n)
complexity to delete all n graphs.

Overall we have the following complexity:
O(1+n^2+n+n^2(n+n)+n+n)
Which is equivalent to

O(n^3)

Shortest Path:
For this function I will use Djikstra's algorithm. I will add 3 new member variables to the GraphNode class, a bool called visited, an int called distance, and a string
predecessor. These 3 varioables will be used only in the shortest path algorithm. The bool will be used to mark nodes as visited, the int will be used to store the current
shortest poath to a given node from a source node (path length is determined by number of edges passed through because I don't do weights), and the string will store the name
of the node that came before in the shortest path. 
Because I don't account for weights, in most scenariuos there will not likely be a single shortest path. Instead, there will liklely be many equally short shortest paths, and
the algorithm will only care about and print out the first of these paths that it finds.

Pseudocode for Shortest Path:
if finding the shortest path from a node to itself, return the node's name
for each node in the graph:
    -set visited to false
    -set predecessor to ""
    -if not the source node, set distance to the number of nodes + 1, else set distance to 0 (number of nodes + 1 is effectively infinity cause thats longer than the longest
    possible path of going through each node once)

while we have not done the follwing for each node:
    find the unvisted node with the smallest value stored in distance (for example, at the beginning this would be source)
    set this node to visited
    for each of this nodes neighbors:
        if current nodes distance + 1 is less than the neighbors current distance:
            set the neighbor's distance to the current node's distance + 1 and set the neighb or's predecessor to the name of the current node

Now, each node should have the shortest path from the source stored in it, along with its predecessor's name

create a string called shortest path to store the shortest path in
create a destination node ptr and make it point to the node in the graph with the name of the destination_name argument

if the destination node pointer finds a node (i.e. if the user's desired destination exists) then:
    create a current node ptr, set it to the destination node ptr
    while we have not yet reached the end of the shortest path:
        set shortest path to the name of current node + " " + the old contents of shortest path
        if the predecessor exists (i.e. if predecessor has a name other than ""):
            find the node in the graph woith the same name as current's predecessor
            set current to this node

return the shortest path string

Complexity Analaysis of Shortest Path Function:
The first edge case of shortest path from  a node to itself is constant complexity O(1).
Next we go through each node in the graph and do constant complexity stuff, overall O(n) to visit n nodes.
Next we do the following for each node O(n):
    Find the unvisited node with the smallest distance value, O(n) overall
        -go through each unvisted node to find what the smallest distance value is O(n)
        -go through the unvisited graph nodes again and find the node which has said shortest distance value, O(n)
    Once we have this node, visit all of its naighbors and do constant complexity stuff at them, O(n) for the n possible neighbors

Overall this segment has complexity O(n(n+n+n))=O(3n^2)=O(n^2)

Next create a shortest path string and a destination node pointer, O(1)
Next find the destination node with the same name as chosen by the user, O(n) to potentially visit all n nodes to find it
Assuming that a destination node was found:
    Until done with path, O(n) since a path potentially contains all n nodes:
        create a current node and set it to destination node, O(1)
        add current node's name to the shortest path string, O(1)
        find current node's predecessor (if it exists) and set current to it, O(n)
    Overall O(n(1+1+n)) = O(n^2)

So, overall, this function has complexity O(1+n+n^2+1+n+n^2) = O(n^2)

O(n^2)

Add Node/ Add Edge:
Both of these functions were written in class. The add node function simply creates a GraphgNode on the heap and then puyts it into the Graph's node vector. The add edge
function simply finds the desired source and destination nodes and, assuming both are found, goes into the source/destination node's edge vector and adds an edge from itself
to its source/destination counterpart. An important reult of the way we put together the add edge function is that our graph always creates undirected edges, that is, if 
you have a path from node A to node B, then you also have a path from node B to node A.

Complexity Analysis of the Add functions:
For add node, we simply create a new node and push it to the back of the node vector in our graph, this is all conatnt complexity so add node has complexity of O(1).
For add edge, we have to actually go through the whole vector of n nodes to find our source/destination nodes. After we find them we just do conatnt complexity stuff 
like in add node. Overall, this function has complexity O(n).

Extraneous Functions:
    -All getters and setters have complexity of O(1), they are all one line functions and simply set or return their given member variables.
    -Both the Graph and GraphNode constructors have constant runtime complexity, the Graph constructor is completely empty and the GraphNode constructor only sets the node's name.
    -Both the Graph and GraphNode destructors have complexity O(n). The Graph destructor must delete all n of its nodes in its node vector and the GraphNode destructor must delete
    all of the edges in GraphNode's edge vector (of which there can be n assuming no repeats). 

Possible Tests:
I have made 3 graphs which I could run tests on:

Graph 1:
Nodes (8): A, B, C, D, E, F, G, H
Edges (18): 
A - A 
A - B  
A - C
A - D
B - D
B - E 
B - H
C - E 
C - G 
D - E 
D - F 
E - F 
E - G 
F - G 
F - H 
G - G 
G - H 
H - H 

Graph 2:
Nodes (6): A, B, C, D, E
Edges (12): 
 A - B 
 A - C 
 A - D 
 A - E 
 B - B 
 C - B 
 D - C
 E - B 
 E - C 
 E - E 
 E - F 
 F - C

 Graph 3:
 Nodes (5): A, B, C, D, E 
 Edges (2):
 A - B 
 C - D 

 Ideas using these graphs
 Graph 1 is the most basic graph. Along with the other graphs it would be good for testing that the add node and add edge functions were implemented properly.
 For exampleafter making it, I could check how many nodes were in the whole graph (hopefully 8) or how many edges were connected to node D (hopefully 4).
 Further, I could use Graph 1 to test my minimal spanning tree function, which should reduce the number of edges from 18 to just 7 since each node is connected
 to each other node in some way. 
 Finally, I could test shortest path here by finding the shortest paths from node A to each other node in the graph, including itself since it has an edge to itself.
 Ultimately, this function tests node and edge adding, minimum spanning tree on a fully connected graph, and shortest path on a fully connected graph.

 Graph 2 is mostly the same as Graph 1, and can be used to test the same things.

 Graph 3 is interesting because it is not fully connected. It has 3 distince parts, the A - B part, the C - D part, and the E part. This Graph will test edge and node 
 addition the same as the previous graphs, but it will test minimumk spanning tree and shortest path on a disconnected graph which allows testing of the following questions:
    -Shortest path between two disconnected nodes?
    -Minimum spanning tree on a graph that can never be fully spanning?
    -Minimum spanning tree on a graph which already has minimal connections?

Ultimately, creating these graphs and running the functions on them should:
    -test add_node 19 times
    -test add edge 32 times
    -test minimum spanning tree 3 times
    -test shortest path at least 10 times (depends on how many shortest paths I actually look at)

Where stuff shows up in the code:

add_node() - lines 86-89 and 244-246
add_edge() - lines 91-108 and 279-282
minimum_spanning_tree() - lines 183-241
shortest_path() - lines 110-181
tests - lines 296-395

A problem that graphs can solve:
    -One problem that I could see graphs being helpful in would be a brute force method of showing that a function between two finite sets is a bijection and therefore has
    an inverse. If each element in both sets is made into a node in a graph, with nodes named in a way which makes it clear which set they are coming from, then a computer could
    use graphs to check the following criteria:
        1 - Does each node in set A map to a node in set B (this would just check the names of the nodes because they would be named in an easily differentiable way)
        2 - Does each node in set A only map to one node in set B (you could check this with a shortest path algorithm, as it can only find paths between nodes that already
            exist so if it can't find paths between twoi nodes that means no path exists)
        3 - Does each node from set B get mapped to (this can be checked by a minimum spanning tree algorithm that can add up how many elements with set B names are actually
            reached from nodes in set A)
    If each of these criteria are met, then that means we have a bijective function from set A to set B and therefore we have an invertible function.
    I'm not sure how efficient this would be in practice for massive sets, but it would hypothetically work and at times may be easier than an actual mathematical proof. 
    Also, just by properties of bijections, this method could also be used to show two sets are the same size, but it would never be the most efficient way to do that.
    Finally, if you already knew the sets were the same size, you could just check criteria 2 or criteria 3 to reach the conclusion that the function was bijective and thus
    has an inverse.

