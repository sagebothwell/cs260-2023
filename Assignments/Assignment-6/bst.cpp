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
    Node* new_node_ptr;
    new_node_ptr = new Node;
    new_node_ptr->value = val;
    new_node_ptr->left = NULL;
    new_node_ptr->right = NULL;
    new_node_ptr->lweight = 0;
    new_node_ptr->rweight = 0;
    if((*node) == NULL){
        (*node) = new_node_ptr;
        return;
    }
    else if((*node)->value <= val){
        new_node_ptr->left = (*node);
        new_node_ptr->lweight = (*node)->lweight + (*node)->rweight + 1;
        (*node) = new_node_ptr;
        return;
    }
    else if((*node)->left == NULL){
        (*node)->left = new_node_ptr;
        (*node)->lweight++;
        return;
    }
    else if((*node)->right == NULL){
        (*node)->right = new_node_ptr;
        (*node)->rweight++;
        return;
    }
    else if((*node)->left->value <= val && (*node)->right->value <= val){
        if((*node)->lweight > (*node)->rweight){
            new_node_ptr->left = (*node)->right;
            (*node)->right = new_node_ptr;
            new_node_ptr->lweight = (*node)->rweight;
            (*node)->rweight++;
            return;
        }
        else{
            new_node_ptr->left = (*node)->left;
            (*node)->left = new_node_ptr;
            new_node_ptr->lweight = (*node)->lweight;
            (*node)->lweight++;
            return;
        }
    }
    else if((*node)->lweight > (*node)->rweight){
        (*node)->rweight++;
        add_node(&(*node)->right, val);
    }
    else{
        (*node)->lweight++;
        add_node(&(*node)->left, val);
    }
}

// print values of tree in-order, assuming initial BSTNode is not nullptr
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
