#include <iostream>
#include <string>

using namespace std;

struct Node {
    string data;
    Node* next;
};

class queue{ //I copy pasted my code from assignment 3 over so a lot of the structure will look the same
    private:
        Node* head;
        Node* current;
        int length;
    public:
        queue();
        int get_length();
        void enqueue(string, int);
        string dequeue(int);
        string peek(int);
        void runtests();
};

int queue::get_length(){ //basic getter function
    return this->length;
}
queue::queue(){ //a constructor so I always get a queue with a known default appearance
    this->length = 0;
    this->head = NULL;
    this->current = NULL;
}
void queue::enqueue(string s, int index){
    Node* new_node_ptr; //the node to be added
    new_node_ptr = new Node;
    new_node_ptr->data = s;
    new_node_ptr->next = NULL;
    if(index > this->length || index < 0){ //if index is larger than the largest index allowed or is negative
        cout << "Invalid list position, aborting insert function." << endl;
        return;
    }
    else if(index == 0){ //if the list is empty, set new_node_ptr as the new head
        new_node_ptr->next = this->head;
        this->head = new_node_ptr;
        this->length++;
        return;
    }
    //everything above here has constant runtime complexity, O(1)
    else if(index == this->length){ //if index is the very last spot in the list, go all the way to the back and put it in
        this->current = this->head;
        while(this->current->next != NULL){ //this runs n times, O(n)
            this->current=this->current->next;
        }
        this->current->next = new_node_ptr;
        this->length++;
        return;
    }
    else{ //if we are not at the back of the list, the list is not empty, and the user made a valid input
        this->current = this->head;
        for(int i=0; i<index-1; i++){ //runs less than n times, still linear though, O(n)
            this->current = this->current->next;
        }
        new_node_ptr->next = this->current->next; //this is the defining differnece between this part and the bhack of the list part
        this->current->next = new_node_ptr;
        this->length++;
        return;
    }
    //Overall O(n)
}
string queue::peek(int index){
    if(this->length == 0){ //if the list is empty, return an error message
        return "Error: tried to peek at empty list, aborting peek function";
    }
    else if(index > this->length-1 || index < 0){ //if the user tries to peek outside of the list, return an error message
        return "Error: tried to peek in a list position which does not exist, aborting peek function";
    }
    else{
        this->current = this->head;
        for(int i=0; i<index; i++){ //this for loop is used all over, its how I navigate my list
            this->current=this->current->next; //potentially runs n times, O(n)
        }
        return this->current->data; //return the data from the node that current stopped on
    }
    //Overall O(n)
}
string queue::dequeue(int index){
    if(this->length == 0){ 
        return "Error: tried to remove from an empty list, aborting removal function";
    }
    else if(index > this->length-1 || index < 0){ //these first two ifs are the same error checks as in peek
        return "Error: tried to remove from a list position which does not exist, aborting removal function";
    }
    //everything above this is constant complexity, O(1)
    else{
        this->current = this->head;
        for(int i=0; i<index; i++){ //go to the spot we are deleting from
            this->current=this->current->next; //potentially runs n times, O(n)
        }
        string info = this->current->data; //take the data from the soon to be deleted node and store it 
        Node* temp_ptr;
        temp_ptr = this->current; //make a temporary node and set it equal to the soon to be deleted node
        this->current = this->head;
        for(int i=0; i<index-1; i++){ //go to the spot right before the soon to be deleted node
            this->current=this->current->next; //potentiall runs n-1 times, still linear, O(n)
        }
        this->current->next = temp_ptr->next; //make the list skip over the soon to be deleted node
        delete temp_ptr; //delete the desired node
        temp_ptr = NULL;
        this->length--;
        return info; //return the info which we stored earlier
    }
    //Overall O(n)
}

void queue::runtests(){ //this function is full of couts which explain what is happening
cout << "\nTo begin we will create a new list" << endl;
cout << "Length of this new list upon creation (expecting 0): " << this->get_length() << endl;
cout << "Now I will attempt to add an element to position 1, this should result in an error as the only available spot is spot 0." << endl;
cout << "Expecting error message: ";
this->enqueue("bad data", 1);
cout << "Length of the list after trying to add to an invalid spot (expecting zero): " << this->get_length() << endl;
cout << "Now, I will add an element called 'first' to the 0th spot in the list, we are expecting no error message." << endl;
cout << "Expecting no text to appear: ";
this->enqueue("first", 0);
cout << endl;
cout << "Length of the list after trying to add a value to a valid spot (expecting 1): " << this->get_length() << endl;
cout << "Now, I will add an element called 'third' to position 1 and then add an element called 'second' to position 1." << endl;
cout << "Expecting no error message: ";
this->enqueue("third", 1);
this->enqueue("second", 1);
cout << endl;
cout << "Length of the list after attempting to add 2 new elements to valid spots (expecting 3): " << this->get_length() << endl;
cout << "Now, we will peek at the list in spots 0, 1, and 2:" << endl;
cout << "Value at 0 (expecting first): " << this->peek(0) << endl;
cout << "Value at 1 (expecting second): " << this->peek(1) << endl;
cout << "Value at 2 (expecting third): " << this->peek(2) << endl;
cout << "Next, we will try to peek at spot 3, which does not exist:" << endl;
cout << "Expecting an error message: " << this->peek(3) << endl;
cout << "Length of the list after peeking (expecting 3): " << this->get_length() << endl;
cout << "Next, we will remove the element in spot 1 three times:" << endl;
cout << "Removing from spot 1 (expected second): " << this->dequeue(1) << endl;
cout << "Removing from spot 1 (expected third): " << this->dequeue(1) << endl;
cout << "Removing from spot 1 (expected error message): " << this->dequeue(1) << endl;
cout << "Length of the list after removing two elements (expected 1): " << this->get_length() << endl;
cout << "Next, we will first peek at spot 0 and then remove from spot 0, and then peek at spot zero again, and then remove from the 0 spot again: " << endl;
cout << "Value at 0 (expecting first): " << this->peek(0) << endl;
cout << "Removing from spot 0 (expected first): " << this->dequeue(0) << endl;
cout << "Value at 0 (expecting error message): " << this->peek(0) << endl;
cout << "Removing from spot 0 (expecting error message): " << this->dequeue(0) << endl;
cout << "Length of the list after removing everything (expected 0): " << this->get_length() << endl;
cout << "TESTS COMPLETED" << endl << endl;
}

int main(){
    string choice = "0";
    queue q;
    while(choice != "5"){ //loops until your ready to quit
        cout << "Welcome to arbitrary list operation simulator 2023! \n"; //display user choices
        cout << "Choose one of the following: \n";
        cout << "1. Add to list \n";
        cout << "2. Remove from list\n";
        cout << "3. Peek into list \n";
        cout << "4. View Length of list\n";
        cout << "5. Quit \n";
        cout << "6. Run Preporgrammed tests\n";
        cout << "Your Choice: ";
        cin.clear();
        getline(cin, choice);
        while(choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6"){ //very basic error handling
            cout << "Invalid choice, please enter an int 1-6: ";
        }
        if(choice == "1"){ //if user wants to add to the list
            cout << "\nEnter some data: ";
            string d;
            getline(cin, d); //get the data they want to store
            cout << "Enter a list position: ";
            string p;
            getline(cin, p); //get the spot they want to store this data at
            int index = stoi(p);
            q.enqueue(d,index); //run the function
            cout << endl << endl;
        }
        
        else if(choice == "2"){ //if the user wants to remove from the list
            int index;
            string p;
            cout << "\nWhere in the list do you want to remove from: ";
            getline(cin, p); //get the spot the user wants to remove data from
            index = stoi(p);
            cout << "\nData at " << index << ": " << q.dequeue(index) << endl << endl; //run the function (it will return a string for this cout statement)
        }
        else if(choice == "3"){ //if the user wants to peek
            int index; //works just like the remove choice above
            string p;
            cout << "\nWhere in the list do you want to peek: ";
            getline(cin, p);
            index = stoi(p);
            cout << "\nData at " << index << ": " << q.peek(index) << endl << endl;
        }
        else if(choice == "4"){ //if the user wants to see list length
            cout << "\nLength of list: " << q.get_length() << endl << endl; //function call (the function returns an int to complete the cout statement)
        }
        else if(choice =="6"){ //if the user wants to run tests
            queue test; //makes a new list to test
            test.runtests(); //calls the runtests function
        }
    }
    return 0;
}