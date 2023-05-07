#include <iostream>
#include <string>

using namespace std;

struct Node {
    int data;
    Node* next;
};

class list{ //I copy pasted my code from assignment 3 over so a lot of the structure will look the same
    private:
        Node* head;
        Node* current;
        int length;
    public:
        list();
        int get_length();
        void add_to_list(int);
        int remove_from_list(int);
        int search(int);
        void runtests();
};

list::list(){
    this->length = 0;
    this->head = NULL;
    this->current = NULL;
}

int list::get_length(){
    return this->length;
}

void list::add_to_list(int val){
    Node* new_node_ptr;
    new_node_ptr = new Node;
    new_node_ptr->data = val;
    new_node_ptr->next = NULL;
    if(this->head == NULL || val < this->head->data){
        new_node_ptr->next = this->head;
        this->head = new_node_ptr;
        this->length++;
        return;
    }
    this->current = this->head;
    while(this->current->next != NULL && val > this->current->next->data){
        this->current = this->current->next;
    }
    if(this->current->next == NULL){
        this->current->next = new_node_ptr;
        this->length++;
        return;
    }
    else{
        new_node_ptr->next = this->current->next;
        this->current->next = new_node_ptr;
        this->length++;
        return;
    }
}

int list::search(int index){
    if(index <= 0 || index > this->length){
        cout << "Error: searched for an item which does not exist, aborting search function.";
        return 0;
    }
    this->current = this->head;
    for(int i=1; i<index; i++){
        this->current=this->current->next;
    }
    return this->current->data;
}

int list::remove_from_list(int index){
    if(index <= 0 || index > this->length){
        cout << "Error: tried to remove an item which does not exist, aborting removal function.";
        return 0;
    }
    this->current = this->head;
    for(int i=1; i<index; i++){
        this->current=this->current->next;
    }
    int val = this->current->data;
    Node* new_node_ptr;
    new_node_ptr = this->current;
    if(index == 1){
        this->head = this->head->next;
        delete new_node_ptr;
        new_node_ptr = 0;
    }
    else if(this->current->next == NULL){
        delete new_node_ptr;
        new_node_ptr = 0;
    }
    else{
        this->current = this->head;
        for(int i=1; i<index-1; i++){
            this->current = this->current->next;
        }
        this->current->next = this->current->next->next;
        delete new_node_ptr;
        new_node_ptr = 0;
    }
    this->length--;
    return val;
}

void list::runtests(){
    cout << "\nTo begin, we will create a brand new list anc check its length.\n";
    cout << "New list's length (expected 0): " << this->get_length() << endl;
    cout << "Now, I will add the following elements in the following order: 5, 2, 4, 1, 4, 3:\n";
    this->add_to_list(5);
    this->add_to_list(2);
    this->add_to_list(4);
    this->add_to_list(1);
    this->add_to_list(4);
    this->add_to_list(3);
    cout << "Now, I will use the search function to print out elements 1, 2, 3, 4, 5, and 6 in that order.\n";
    cout << "Expecting 1 2 3 4 4 5: " << this->search(1) << " " << this->search(2) << " " << this->search(3) << " " << this->search(4) << " " << this->search(5) << " " << this->search(6) << endl;
    cout << "Now I will remove the 4th element 4 times: \n";
    cout << "Expecting 4: " << this->remove_from_list(4) << endl;
    cout << "Expecting 4: " << this->remove_from_list(4) << endl;
    cout << "Expecting 5: " << this->remove_from_list(4) << endl;
    cout << "Expecting error: ";
    this->remove_from_list(4); //technically returns a zero but it won't get ever get printed
    cout << "\nNow, I will print the first 3 element out using search: \n";
    cout << "Expecting 1 2 3: " << this->search(1) << " " << this->search(2) << " " << this->search(3) << endl;
    cout << "Next, I will try and search for the 4th smallest element (there are only 3 elements in the list):\n";
    cout << "Expecting error: ";
    this->search(4);
    cout << "\nCurrent list length (expecting 3): " << this->get_length();
    cout << "\nNow, I will remove the first element of the list 4 times: \n";
    cout << "Expecting 1: " << this->remove_from_list(1) << endl;
    cout << "Expecting 2: " << this->remove_from_list(1) << endl;
    cout << "Expecting 3: " << this->remove_from_list(1) << endl;
    cout << "Expecting error: ";
    this->remove_from_list(1); //technically returns a zero but it won't get ever get printed
    cout << "\nNext, we will try to search for the smallest element (expecting error): ";
    this->search(1);
    cout << "\nLength of list (expecting 0): " << this->get_length() << endl;
    cout << "TESTS COMPLETED" << endl << endl;
}
int main(){
    string choice = "0";
    list l;
    while(choice != "5"){ //loops until your ready to quit
        cout << "Welcome to auto-sorting list simulator 2023! \n"; //display user choices
        cout << "Choose one of the following: \n";
        cout << "1. Add to list \n";
        cout << "2. Remove from list\n";
        cout << "3. Search the list \n";
        cout << "4. View Length of list\n";
        cout << "5. Quit \n";
        cout << "6. Run Preporgrammed tests\n";
        cout << "Your Choice: ";
        cin.clear();
        getline(cin, choice);
        if(choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6"){ //very basic error handling
            cout << "Invalid choice, please enter an int 1-6: ";
        }
        if(choice == "1"){ //if user wants to add to the list
            cout << "\nEnter some data: ";
            string d;
            getline(cin, d); //get the data they want to store
            int val = stoi(d);
            l.add_to_list(val); //run the function
            cout << endl << endl;
        }
        
        else if(choice == "2"){ //if the user wants to remove from the list
            int index;
            string p;
            cout << "\nEnter some integer n to remove the nth smallest element from the list starting with 1 as the smallest: ";
            getline(cin, p); //get the spot the user wants to remove data from
            index = stoi(p);
            cout << "\nElement which is " << index-1 << " from the smallest element: " << l.remove_from_list(index) << endl << endl; //run the function (it will return a string for this cout statement)
        }
        else if(choice == "3"){ //if the user wants to peek
            int index; //works just like the remove choice above
            cout << "\nEnter some integer n to search for the nth smallest element from the list starting with 1 as the smallest: ";
            string p;
            getline(cin, p);
            index = stoi(p);
            cout << "\nElement which is " << index-1 << " from the smallest element: " << l.search(index) << endl << endl;
        }
        else if(choice == "4"){ //if the user wants to see list length
            cout << "\nLength of list: " << l.get_length() << endl << endl; //function call (the function returns an int to complete the cout statement)
        }
        else if(choice =="6"){ //if the user wants to run tests
            list test; //makes a new list to test
            test.runtests(); //calls the runtests function
        }
    }
    return 0;
}

