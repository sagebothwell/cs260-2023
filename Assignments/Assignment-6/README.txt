Notes:
    -It turns out that I actually built a heap, not a binary tree, but they work the same so everything is okay!
    -My 'tree' is organized with largest elements on top and smaller elements as you go down--the parent is always bigger than its children
    -My search function will always output all elements of the searched value, so it always goes through all n elements

Requirement 1: Creating Tests (lines 194-242)
    For my tests, I tried to remove from an empty list, I added 9 elements in non-ascending and non-descending order,
    I output the elements using my top to bottom left to right traversal method, I searched for 3 elements which were in
    my list and 1 which was not using my in order traversal method, I removed 3 elements from my list, the head, a node
    in the middle and a node at the end of a branch and then I tried to delete an item which did not exist.

    Functions Tested:
        -add_node
        -remove_node
        -traverse_tree (this is a earch function)
        -in order traversal function
        -top to bottom left to right traversal function
        -all the helper functions for these functions
    
    Test Ideas:
        -Try to remove from an empty list
        -Try to remove from a list with element(s), take away different things like head or end of branch
        -Search list for elements which exist and which dont exist
        -Add elements, and check to make sure they were added in the correct configuration

Requirement 2: 
    1 - nodes to store values (lines 6-13)
    2 - add function (lines 136-168)
    3 - remove function (lines 63-108)
        helper functions for remove function (lines 51-61, 183-192)
    4 - traversal functions (lines 170-182, 117-134)
        Also in basically all functions which use recursion to travel through the tree
    
Requirement 3: 
Complexity Analysis happens in the line comments of each major function, but as a recap:
    -add node, O(log(n))
    -traversal, O(n)
    -remove node, O(nlog(n))
Again, more detail on these complexities and where they come from is given in the line comments

Design for major functions:

Add Node Function:
Create a new node with desired value stored in it
If head is currently NULL, make this node the new head
If new node has a value greater than head, make head the left branch of the new node and make the new node head
Recursively do the following until the node is placed:
    If head->left is heavier than head->right, then run the function again, but replace head with head->right
    Otherwise, run the function again, but replace head with head->left

Traverse Tree:
Very similar to what we did in class for in order traversal (in fact, exactly the same)
For top to bottom left to right, just do the recursive calls after doiung whatever you want to do with the nodes
    this new traversal stragety is good for indexing the nodes, which I can use for the removal function

Remove Node:
Index all of the nodes using top to bottom left to right traversal
Ask user which index they want to remove
if the index does not exist on the list, abort function with error message
Otherwise, recursively run through the tree using top to bottom left to right traversal until the desired index is reached
Once at the desired index, make new pointers to point at (current node)->left and (current node)->right
delete (current node)
make a pointer to point at the head of the tree now that the node and its left/right branches are gone
Now we have 3 pointrers which hold all of the nodes we need in the tree
Build a new tree By sending the elements of each of the three pointers into the add node function, starting with a head of NULL


