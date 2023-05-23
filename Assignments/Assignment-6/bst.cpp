#include <iostream>
#include <string>

using namespace std;

struct Node{
    int value;
    int index;
    Node* left;
    Node* right;
    int lweight; //number of nodes in left offshoot
    int rweight; //number of nodes in right offshoot
};

class bst{
    private:
        Node* head;
        Node* current;
    public:
        bst(); //constructor
        void add_node(Node** node, int val); //add nodes to tree
        void place_node(Node* new_node, Node** old_node); //adds multiple nodes in specified order, used to rebuild tree after deleting from it
        void remove_node(int index, Node** node); //deletes a node from the tree
        int traverse_tree(int val, Node* node); //this does in order traversal, I also have a non member function which does top to bottom, left to right traversal
        int get_l_weight(); //basic getter for root's lweight
        int get_r_weight(); //basic getter for root's rweight
        Node** get_head_ptr(); //getter for a pointer to the root, used by add_node
        Node* get_head(); //getter for head node, used by traversal functions. 
        void runtests();
};

Node** bst::get_head_ptr(){
    return &head; //return root address
}
Node* bst::get_head(){
    return this->head; //return root
}
int bst::get_l_weight(){
    return this->head->lweight; 
}

int bst::get_r_weight(){
    return this->head->rweight;
}

bst::bst(){
    this->head = NULL; //I don't actually know if these are initially set to something other than NULL, just a safety precaution
    this->current = NULL;
}

void bst::place_node(Node* new_node, Node** old_node){
    add_node(old_node, new_node->value); //adds a node in order of top to bottom left to right traversal

    if(new_node->left != NULL){
        place_node(new_node->left, old_node);
    }
    if(new_node->right != NULL){
        place_node(new_node->right, old_node);
    }
    //these two ifs are the traversal function's recursive logic
}

void bst::remove_node(int index, Node** node){
    if(this->head == NULL){
        cout << "Error: tried to remove from an empty list, aborting removal function" << endl;
        return;
    }
    if(index > this->head->lweight + this->head->rweight + 1 || index < 1){ //case checking
        cout << "Sorry, it looks like your trying to remove a node from a nonexistent space. Please pick a different index." << endl;
        return;
    }
    if((*node)->index == index){ //if we are at the nth node which is wished to be deleted
        if((*node)->left == NULL && (*node)->right == NULL){
            Node* leftovers;
            delete (*node);
            (*node) = NULL; //deleting the node
            leftovers = this->head;
            this->head = NULL;
            if(leftovers != NULL){
                place_node(leftovers, &(this->head)); //place the leftover nodes
            }
            return;
        }
        Node* lnode_ptr;
        Node* rnode_ptr; 
        Node* leftovers;
        //make three pointers, one for (deleted node)->left, one for (deleted node)->right, and one for whats left over after deleteing the node and disconnecting its left/right branches
        lnode_ptr = (*node)->left;
        rnode_ptr = (*node)->right;
        delete (*node);
        (*node) = NULL; //deleting the node
        leftovers = this->head;
        this->head = NULL;
        if(leftovers != NULL){
            place_node(leftovers, &(this->head)); //place the leftover nodes
        }
        if(lnode_ptr != NULL){
            place_node(lnode_ptr, &(this->head)); //place the left branch nodes
        }
        if(rnode_ptr != NULL){
            place_node(rnode_ptr, &(this->head)); //place the right branch nodes
        }
        return;
        //here I effectively rebuild the whole tree, not very efficient, but it gets the job done
        //potentially O(n) to find the node I want to delete
        //O(nlog(n)) to rebuild the whole tree
        //Overall, my remove node function is O(nlog(n)), very costly!
    }
    if((*node)->left != NULL){ //go through the list top to bottom, left to right
        remove_node(index, &(*node)->left);
    }
    if((*node)->right != NULL){
        remove_node(index, &(*node)->right);
    }
}

int bst::traverse_tree(int val, Node* node){ //This function will traverse the function (in order traversal) and output the nth node with value m (n,m inputted by users)
    int n = 0;
    if(node->left != NULL) {
        n = n + traverse_tree(val, node->left); //The n value will increase from zero if any nodes with value 'val' are found
    }
    if(node->value == val){
        cout << "Node Value: " << node->value << endl;
        cout << "Node weight (lweight rweight): (" << node->lweight << " " << node->rweight << ")" << endl; //This is good extra info to have for error checking and testing
        return 1; //increments n
    }
    if(node->right != NULL) {
        n = n + traverse_tree(val, node->right); //The n value will increase from zero if any nodes with value 'val' are found
    }
    return n; //returns a 0 only when no nodes are found, letting me have a custom no nodes found message in main.
    
    //This function is complexity O(n), it goes through the whole tree each time.
    //It goes through everything because when you searcxh it prints out all nodes which match your search, this was just a design decision
}

void bst::add_node(Node** node, int val){
    Node* new_node_ptr; //create the node which will be inserted
    new_node_ptr = new Node;
    new_node_ptr->value = val;
    new_node_ptr->left = NULL;
    new_node_ptr->right = NULL;
    new_node_ptr->lweight = 0;
    new_node_ptr->rweight = 0;
    if((*node) == NULL){ //if head is empty, fill it with the new node
        (*node) = new_node_ptr;
        return;
    }
    else if((*node)->value <= val){ //if head is smaller than new node, make new node the new start of the tree with the old tree as its left branch
        new_node_ptr->left = (*node);
        new_node_ptr->lweight = (*node)->lweight + (*node)->rweight + 1;
        (*node) = new_node_ptr;
        return;
    }

    //NOTE: everything above this takes a constant time as its just case checking, so it has complexity O(1)

    else if((*node)->lweight > (*node)->rweight){ //recursive call! 
        (*node)->rweight++;
        add_node(&(*node)->right, val); //if left branch is heavier, recursively do this function, this time with the start of the right branch as head
    }
    else{
        (*node)->lweight++;
        add_node(&(*node)->left, val); //if right branch is heavier or equal in size, recursively do this function, this time with the start of the left branch as head
    }

    //The recursive call section will run at worst log(n) times (assuming the tree maintains balance, which it will do under most circumstances)
    //Overall, the function has Big O complexity of O(log(n)).
}

void top2bottom_left2right_traversal(Node* node){ //my new original traversal function
   
    //the inspiration for this was I needed a traversal method which let me do operations on nodes before doing recursive stuff with them
    //this lets me easily keep an index of nodes, which is good for my remove_node function
   
    cout << node->value << " " << "(" << node->lweight << " " << node->rweight << "), ";
    if(node->left != NULL){
        top2bottom_left2right_traversal(node->left);
    }
    if(node->right != NULL){
        top2bottom_left2right_traversal(node->right);
    }
}
int node_index_setter(Node** node, int index){ //sets node index using above traversal funnction
    (*node)->index = index;
    if((*node)->left != NULL){
        index = node_index_setter(&(*node)->left, index + 1);
    }
    if((*node)->right != NULL){
        index = node_index_setter(&(*node)->right, index + 1);
    }
    return index;
}

void bst::runtests(){//the couts all explain what is happening
    cout << endl << endl;
    cout << "We will try to delete an element from the list, this should be impossible as the list is empty." << endl;
    cout << "Expecting error mssg: ";
    this->remove_node(1, this->get_head_ptr()); //1 is the root index so shopuld have error only when empty
    cout << "Now, let's add elements 10, 8, 7, 9, 6, 6, 5, 4, and 11 in that order." << endl;
    this->add_node(this->get_head_ptr(), 10);
    this->add_node(this->get_head_ptr(), 8);
    this->add_node(this->get_head_ptr(), 7);
    this->add_node(this->get_head_ptr(), 9);
    this->add_node(this->get_head_ptr(), 6);
    this->add_node(this->get_head_ptr(), 6);
    this->add_node(this->get_head_ptr(), 5);
    this->add_node(this->get_head_ptr(), 4);
    this->add_node(this->get_head_ptr(), 11);
    cout << "Now, lets output the values from the tree and their respective weights using my top to bottom left to right traversal method." << endl;
    cout << "Expecting 11 (8 0), 10(4 3), 9(2 1), 8(1 0), 4(0 0), 6(0 0), 7(1 1), 6(0 0), 5(0 0): ";
    top2bottom_left2right_traversal(this->head);
    cout << endl << "Now, let's search the list for values 11, 9, 6, and 100 in that order." << endl;
    cout << "Expecting to find 1 node of value 11, 1 node of value 9, 2 nodes of value 6 and 0 nodes of value 100:" << endl;
    this->traverse_tree(11, this->head);
    this->traverse_tree(9, this->head);
    this->traverse_tree(6, this->head);
    this->traverse_tree(100, this->head);
    cout << "Note that this method used in order traversal, which is different than what I used to show the elements above." << endl;
    cout << "Now, let's try and remove 11, 9, 5, and an element which does not exist from the list in that order." << endl;
    node_index_setter(this->get_head_ptr(), 1);
    this->remove_node(1, this->get_head_ptr()); //removes the root
    cout << "After removing 11:" << endl << "Expecting 10(4 3), 9(2 1), 5(1 0), 4(0 0), 7(0 0), 8(1 1), 6(0 0), 6(0 0): ";
    top2bottom_left2right_traversal(this->head);
    cout << endl << "After removing 9: " << endl;
    node_index_setter(this->get_head_ptr(), 1);
    this->remove_node(2, this->get_head_ptr());
    cout << "Expecting 10(3 3) 8(1 1) 6(0 0) 4(0 0) 7(2 0) 6(1 0) 5(0 0): ";
    top2bottom_left2right_traversal(this->head);
    cout << endl << "After removing 5: " << endl;
    node_index_setter(this->get_head_ptr(), 1);
    this->remove_node(7, this->get_head_ptr());
    cout << "Expecting 10(3 2) 8(1 1) 4(0 0) 6(0 0) 7(1 0) 6(0 0): ";
    top2bottom_left2right_traversal(this->head);
    cout << endl << "After trying to remove the 100th element (which does not exist):" << endl;
    node_index_setter(this->get_head_ptr(), 1);
    cout << "Expecting error message: ";
    this->remove_node(100, this->get_head_ptr());
    cout << "Current Contents of tree:" << endl;
    cout << "Expecting 10(3 2) 8(1 1) 4(0 0) 6(0 0) 7(1 0) 6(0 0): ";
    top2bottom_left2right_traversal(this->head);
    cout << endl << "Tests complete!" << endl << endl;
}

int main(){
    int choice;
    int value;
    int search_not_found;
    int index;
    bst tree; //the tree is born
    while(choice != 4){ //same sort of intro as every other assignment
        cout << "Welcome to Binary Search Tree Simulator 2023!" << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. Add to the binary tree" << endl;
        cout << "2. Remove from the binary tree" << endl;
        cout << "3. Search the binary tree" << endl;
        cout << "4. Quit" << endl;
        cout << "5. Run preprogrammed tests" << endl;
        cout << "Choice: ";
        cin >> choice;
        if(choice == 1){ //if you want to add
            cout << endl << endl;
            cout << "What value do you want to add (enter an integer): ";
            cin >> value; //take in an int value
            tree.add_node(tree.get_head_ptr(), value); //add it to the tree
            cout << "Node Added!" << endl << endl;
        }
        else if(choice == 2){ //if you want to delete an element
            cout << endl << endl;
            cout << "As a reminder, below is all of the elements in the tree oprganized top to bottom and left to right:" << endl;
            top2bottom_left2right_traversal(tree.get_head()); //display elements in order of original traversal function
            cout << endl << "Which element would you like to remove? (Enter integer n for the nth element from the order above): ";
            cin >> index; //user enters an index n
            tree.remove_node(index, tree.get_head_ptr()); //delete node at users specified index
            cout << "Element Removed!" << endl << endl;
        }
        else if(choice == 3){ //if user chooses to search tree
            cout << endl << endl;
            cout << "This search function will look through the tree using in order traversal." << endl;
            cout << "What value would you like to search for in the tree (Enter an int): ";
            cin >> value; //emter the value you want to search for
            cout << endl;
            cout << "Below are all of the nodes in the list with your chosen value:" << endl;
            search_not_found = tree.traverse_tree(value, tree.get_head()); //tree is searched for elements using in order traversal method
            if(search_not_found == 0){
                cout << "Sorry, it appears there are no elements in the list with your chosen value."; //if no elemenst are found
            }
            cout << endl << endl;
        }
        else if(choice == 5){//if user wants to do tests
            bst test;
            test.runtests();
        }
    }
}