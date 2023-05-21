#include <iostream>
#include <string>

using namespace std;

struct Node{
    int value;
    Node* left;
    Node* right;
    int lweight;
    int rweight;
};

class bst{
    private:
        Node* head;
        Node* current;
    public:
        bst();
        void add_node(Node** node, int val);
        void place_node(Node* new_node, Node** old_node);
        void remove_node(int index, Node** node, int n);
        int traverse_tree(int val, Node* node);
        int get_l_weight();
        int get_r_weight();
        Node** get_head_ptr();
        Node* get_head();
};

Node** bst::get_head_ptr(){
    return &head;
}
Node* bst::get_head(){
    return this->head;
}
int bst::get_l_weight(){
    return this->head->lweight;
}

int bst::get_r_weight(){
    return this->head->rweight;
}

bst::bst(){
    this->head = NULL;
    this->current = NULL;
}

void bst::place_node(Node* new_node, Node** old_node){
    add_node(old_node, new_node->value);

    if(new_node->left != NULL){
        place_node(new_node->left, old_node);
    }
    if(new_node->right != NULL){
        place_node(new_node->right, old_node);
    }
}

void bst::remove_node(int index, Node** node, int n){
    bool removed = false;
    if(n == index){
        Node* lnode_ptr;
        Node* rnode_ptr;
        Node* leftovers;
        lnode_ptr = (*node)->left;
        rnode_ptr = (*node)->right;
        (*node) = NULL;
        leftovers = this->head;
        this->head = NULL;
        if(leftovers != NULL){
            place_node(leftovers, &(this->head));
        }
        if(lnode_ptr != NULL){
            place_node(lnode_ptr, &(this->head));
        }
        if(rnode_ptr != NULL){
            place_node(rnode_ptr, &(this->head));
        }
        return;
    }
    if((*node)->left != NULL){
        remove_node(index, &(*node)->left, ++n);
    }
    if((*node)->right != NULL){
        remove_node(index, &(*node)->left, ++n);
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

//I stole this function for the sake of checking to make sure my function(s) work, will remove later
void inOrderTraversal(Node *node) {
    // look and go left if not nullptr
    if(node->left != NULL) {
        inOrderTraversal(node->left);
    }

    // print yo self
    cout << node->value << " " << "(" << node->lweight << " " << node->rweight << "), ";

    // look and go right if not nullptr
    if(node->right != NULL) {
        inOrderTraversal(node->right);
    }
}

void top2bottom_left2right_traversal(Node* node){
    cout << node->value << " " << "(" << node->lweight << " " << node->rweight << "), ";
    if(node->left != NULL){
        top2bottom_left2right_traversal(node->left);
    }
    if(node->right != NULL){
        top2bottom_left2right_traversal(node->right);
    }
}
/*
int main(){
    int val;
    bst tree;
    while(true){
        cin >> val;
        tree.add_node(tree.get_head_ptr(), val);
        inOrderTraversal(tree.get_head());
        cout << endl;
    }
}
*/
int main(){
    int choice;
    int value;
    int search_not_found;
    int index;
    bst tree;
    while(choice != 4){
        cout << "Welcome to Binary Search Tree Simulator 2023!" << endl;
        cout << "What would you like to do?" << endl;
        cout << "1. Add to the binary tree" << endl;
        cout << "2. Remove from the binary tree" << endl;
        cout << "3. Search the binary tree" << endl;
        cout << "4. Quit" << endl;
        cout << "Choice: ";
        cin >> choice;
        if(choice == 1){
            cout << endl << endl;
            cout << "What value do you want to add (enter an integer): ";
            cin >> value;
            tree.add_node(tree.get_head_ptr(), value);
            cout << "Node Added!" << endl << endl;
        }
        else if(choice == 2){
            cout << endl << endl;
            cout << "As a reminder, below is all of the elements in the tree oprganized top to bottom and left to right:" << endl;
            top2bottom_left2right_traversal(tree.get_head());
            cout << endl << "Which element would you like to remove? (Enter integer n for the nth element from the order above): ";
            cin >> index;
            tree.remove_node(index, tree.get_head_ptr(), 1);
            cout << "Element Removed!" << endl << endl;
        }
        else if(choice == 3){
            cout << endl << endl;
            cout << "This search function will look through the tree using in order traversal." << endl;
            cout << "What value would you like to search for in the tree (Enter an int): ";
            cin >> value;
            cout << endl;
            cout << "Below are all of the nodes in the list with your chosen value:" << endl;
            search_not_found = tree.traverse_tree(value, tree.get_head());
            if(search_not_found == 0){
                cout << "Sorry, it appears there are no elements in the list with your chosen value.";
            }
            cout << endl << endl;
        }
    }
}