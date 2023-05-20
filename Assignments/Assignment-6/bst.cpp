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
        void remove_node(int val);
        Node* traverse_tree(Node* node, int val);
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
    else if((*node)->left == NULL){ //if head->left is NULL, fill it with new node
        (*node)->left = new_node_ptr;
        (*node)->lweight++;
        return;
    }
    else if((*node)->right == NULL){ //if head->right is NULL, fill it with new node
        (*node)->right = new_node_ptr;
        (*node)->rweight++;
        return;
    }
    //NOTE: everything above this takes a constant time as its just case checking, so it has complexity O(n)

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
