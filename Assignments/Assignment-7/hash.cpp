#include <iostream>
#include <string>

using namespace std;

struct Node{
    string value;
    Node* next; 
};

struct List{ //I made this a struct cause I put all the functions that normally go in a linked list in the hashtable class
    Node* head;
    Node* current;
};

class Hashtable {
    private:
        int size;
        int capacity;
        List* values; //My 'smart' hashtable will use linked lists to avoid collisions at the cost of algorithm and real time complexity
        int hash(string key);
    public:
        Hashtable(int starting_capacity); //constructor with specified capacity
        ~Hashtable();
        void add(string newKey); //add functions similar to that in queue
        string remove(string oldKey); //remove functions similar to that in arbitrary list
        string find(string key); //find function similar to that in arbitrary list
        int get_size();
        int get_capacity();
        void runtests();
};

Hashtable::Hashtable(int starting_capacity){
    this->capacity = starting_capacity; //set capacity
    this->values = new List[this->capacity]; //make the array of linked lists for data storage
    this->size = 0; //set list size to empty
    for(int i=0; i<this->capacity; i++){
        this->values[i].head = NULL; //make sure each linked list is empty

    }
}

Hashtable::~Hashtable(){ //destructor
    for(int i=0; i<this->capacity; i++){
        while(this->values[i].head != NULL){
            this->values[i].current = this->values[i].head;
            this->values[i].head = this->values[i].head->next; // Move head to the next node
            delete this->values[i].current; // Delete the current node
        }
    }
    delete[] this->values;
    this->values = NULL;
}

int Hashtable::hash(string key){ //same hash function as what we did in class, sums up the int conversions for each char in a given string
    int sum = 0;
    for(auto character : key){
        sum += character;
    }
    sum = sum % this->capacity;
    return sum;
}

void Hashtable::add(string newKey){
    int desired_spot = this->hash(newKey); //find which table spot to add to
    Node* new_node_ptr;
    new_node_ptr = new Node;
    new_node_ptr -> value = newKey; //make a new node and make it have a value of whatever the user entered
    if(this->values[desired_spot].head == NULL){
        this->size++; //only increase size if the node goes into a previously empty linked list
        new_node_ptr -> next = NULL;
        this->values[desired_spot].head = new_node_ptr;
        return;
    }
    new_node_ptr -> next = this->values[desired_spot].head; //if the list it is assigned to is not empty, just shove the newq node to the top of the list
    this->values[desired_spot].head = new_node_ptr;
}

string Hashtable::remove(string oldKey){
    int target_spot = this->hash(oldKey); //find desired table spot to check
    if(this->values[target_spot].head == NULL){ //if this spot is empty, print error message and abort function
        return "There are no strings in the hashtable which match your input!";
    }
    if(this->values[target_spot].head->value == oldKey){ //if the desired value is at the start of the list
        Node* new_node_ptr;
        new_node_ptr = this->values[target_spot].head; //set a new pointer to head
        this->values[target_spot].head = this->values[target_spot].head->next; //move head up one spot in the list
        if(this->values[target_spot].head == NULL){ //if the list only had one item, lower the size since that item is being removed and so the list is now empty
            this->size--;
        }
        return new_node_ptr->value;
    }
    this->values[target_spot].current = this->values[target_spot].head; //only gets here if thge list is not empty and the desired element is not immediately found
    while(this->values[target_spot].current!= NULL){ //while not at the end of the list
        if(this->values[target_spot].current->next->value == oldKey){ //check if an upcoming node is the desired node
            Node* new_node_ptr;
            new_node_ptr = this->values[target_spot].current->next; //if it is, make a new pointer to the desired node
            this->values[target_spot].current->next = this->values[target_spot].current->next->next; //clip it out of the list
            string return_val;
            return_val = new_node_ptr->value; //store value from the new pointer
            delete new_node_ptr; //delete the new pointer
            new_node_ptr = NULL;
            return return_val; //return the deleted pointers data
        }
        this->values[target_spot].current = this->values[target_spot].current->next; //move to the next spot in the list
    }
    //only gets down here if the node was not in the list, returns message saying the node was not in the table
    return "There are no strings in the hashtable which match your input!";
}

string Hashtable::find(string key){ //works very similarly to the remove function
    int target_spot = this->hash(key); //finds the desired spot to search
    if(this->values[target_spot].head == NULL){ //if the desired list is empty, return error message and abort function
        return "There are no strings in the hashtable which match your input!";
    }
    if(this->values[target_spot].head->value == key){ //if head is immediately the desired node, return the value
        return this->values[target_spot].head->value;
    }
    this->values[target_spot].current = this->values[target_spot].head; 
    while(this->values[target_spot].current != NULL){ //go through the list until the end
        if(this->values[target_spot].current->value == key){ //if we reach the desired node
            string return_val; 
            return_val = this->values[target_spot].current->value;
            return return_val; //store the desired valuye and return it
        }
        this->values[target_spot].current = this->values[target_spot].current->next; //go to the next spot
    }
    //If we get to the end of the list and never find the element, then return a message letting the user know the element is not in the table
    return "There are no strings in the hashtable which match your input!";
}

int Hashtable::get_size(){ //basic getter for size
    return this->size;
}

int Hashtable::get_capacity(){ //basic getter for capacity
    return this->capacity;
}

void Hashtable::runtests(){ //tests, the couts clarify what is going on everywhere
    cout << endl << endl << "To begin, I created a new hashtable of quantity 5." << endl;
    cout << "Checking size/capacity (Expecting 0/5): " << this->get_size() << "/" << this->get_capacity() << endl;
    cout << "Now we will try to remove an element named 'this list is empty' and will search for an element named 'not real'" << endl;
    cout << "Expecting 2 error messages:" << endl;
    cout << "After remove function: " << this->remove("this list is empty") << endl;
    cout << "After search function: " << this->find("not real") << endl;
    cout << "Next, we will add elements first, second, third, fourth, and fifth in that order. These elements should be hashed into hastable slots 2, 1, 4, 4, and 4 respectively." << endl;
    this->add("first");
    this->add("second");
    this->add("third");
    this->add("fourth");
    this->add("fifth");
    cout << "Checking size/capacity (Expecting 3/5): " << this->get_size() << "/" << this->get_capacity() << endl;
    cout << "Now, let's try to remove element 'first' 2 times." << endl;
    cout << "After first removal (Expecting first): " << this->remove("first") << endl;
    cout << "After second removal (Expecting error): " << this->remove("first") << endl;
    cout << "Checking size/capacity (Expecting 2/5): " << this->get_size() << "/" << this->get_capacity() << endl;
    cout << "Now, I will search for the elements first, second, thirtd, fourth, and fifth." << endl;
    cout << "Searching for 'first' (expecting error): " << this->find("first") << endl;
    cout << "Searching for 'second' (expecting second): " << this->find("second") << endl;
    cout << "Searching for 'third' (expecting third): " << this->find("third") << endl;
    cout << "Searching for 'fourth' (expecting fourth): " << this->find("fourth") << endl;
    cout << "Searching for 'fifth' (expecting fifth): " << this->find("fifth") << endl;
    cout << "Checking size/capacity (Expecting 2/5): " << this->get_size() << "/" << this->get_capacity() << endl;
    cout << "Now, we will remove elements 'second' and 'third' and then we will search for them." << endl;
    this->remove("second");
    this->remove("third");
    cout << "Searching for the removed element 'second' (Expecting error): " << this->find("second") << endl;
    cout << "Searching for the removed element 'third' (Expecting error): " << this->find("third") << endl;
    cout << "Checking size/capacity (Expecting 1/5): " << this->get_size() << "/" << this->get_capacity() << endl;
    cout << "Next, we will remove element 'fifth and then searxh for it." << endl;
    this->remove("fifth");
    cout << "Searching for the removed element 'fifth' (Expecting error): " << this->find("fifth") << endl;
    cout << "Checking size/capacity (Expecting 1/5): " << this->get_size() << "/" << this->get_capacity() << endl;
    cout << "Finally, we will remove element 'fourth' and then search for it." << endl;
    this->remove("fourth");
    cout << "Searching for the removed element 'fourth' (Expecting error): " << this->find("fourth") << endl;
    cout << "Checking size/capacity (Expecting 0/5): " << this->get_size() << "/" << this->get_capacity() << endl;
    cout << "Tests Completed!" << endl << endl;
}

int main(){
    cout << "Welcome to Hashtable Simulator 2023!" << endl;
    cout << "To begin, please input the number of slots available in this hastable (as an integer): ";
    int capacity;
    cin >> capacity;
    Hashtable table(capacity); //creates a hashtable of desired size
    cout << "Hashtable Created!" << endl << endl;

    int choice = 0;
    while(choice != 5){
        cout << "What would you like to do?" << endl;
        cout << "1. Add to hashtable" << endl;
        cout << "2. Remove from hashtable" << endl;
        cout << "3. Search hashtable" << endl;
        cout << "4. Print size/capacity of hashtable" << endl;
        cout << "5. Quit" << endl;
        cout << "6. Run Preprogrammed Tests" << endl;
        cout << "Your choice: ";
        cin >> choice;
        cin.clear();
        cin.ignore();
        if(choice == 1){ //if they want to add
            cout << "Enter a string to add to the hashtable: ";
            string data;
            getline(cin, data); //get the data they want to add
            table.add(data); //add it
            cout << "String Added!" << endl << endl;
        }
        if(choice == 2){ //if they want to remove
            cout << "Enter the string value corresponding to the data you would like to remove: ";
            string data;
            getline(cin, data); //get the data they want to remove
            cout << "Value Removed: " << table.remove(data) << endl << endl; //try to remove it (if it exists)
        }
        if(choice == 3){ //if they want to find data
            cout << "Enter the string value corresponding to the data you would like to search for: ";
            string data;
            getline(cin, data); //get the data they want to find
            cout << "Value Found: " << table.find(data) << endl << endl; //return this data if it exists
        }
        if(choice == 4){ //if they want size/capacity
            cout << "Size: " << table.get_size() << endl; //return size
            cout << "Capacity: " << table.get_capacity() << endl << endl; //return capacity
        }
        if(choice == 6){ //if they want to run tests
            Hashtable test(5); //create a test hashtable
            test.runtests(); //run tests on this hashtable
        }
    }
}
