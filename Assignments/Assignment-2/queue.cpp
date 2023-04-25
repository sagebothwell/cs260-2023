#include <iostream>
#include <string>

using namespace std;

struct Node {
    string data;
    Node* next;
};

class queue{
    private:
        Node* head;
        Node* current;
        int length;
    public:
        queue();
        int get_length();
        void enqueue(string);
        string dequeue();
        string peek();
        void runtests();
};

int queue::get_length(){
    return this->length;
}
queue::queue(){
    this->length = 0;
    this->head = NULL;
    this->current = NULL;
}
void queue::enqueue(string s){
    Node* new_node_ptr;
    new_node_ptr = new Node;
    new_node_ptr->data = s;
    new_node_ptr->next = NULL;
    if(this->head == NULL){
        this->head = new_node_ptr;
        this->length++;
    }
    else{
        this->current = this->head;
        while(this->current->next != NULL){
            this->current = this->current->next;
        }
        this->current->next = new_node_ptr;
        this->length++;
    }
}
string queue::peek(){
    if(this->length == 0){
        return "Error: tried to peek at empty queue, aborting peek function";
    }
    return this->head->data;
}
string queue::dequeue(){
    if(this->length == 0){
        return "Error: tried to take items out of an empty queue, aborting dequeue function";
    }
    string new_data = this->head->data;
    Node* new_ptr; 
    new_ptr = new Node;
    new_ptr = this->head->next;
    delete this->head;
    this->head = new_ptr;
    this->length--;
    return new_data;

}
void queue::runtests(){
    cout << "\nWe will add the following elements to the list: '1', '2nd thing', and 'three'" << endl;
    cout << "List size before adding (expected 0): " << this->get_length() << endl;
    this->enqueue("1");
    this->enqueue("2nd thing");
    this->enqueue("three");
    cout << "List size after adding (expected 3): " << this->get_length() << endl;
    cout << "First element in the list (expected: 1): " << this->peek() << endl;
    cout << "We checked with peek, so no elements should have been removed." << endl;
    cout << "List size after using peek (expected: 3): " << this->get_length() << endl;
    cout << "Now, let's look at the first element and dequeue it (expected 1): " << this->dequeue() << endl;
    cout << "Number of elements in the list after dequeuing (expected: 2): " << this->get_length() << endl;
    cout << "Now, let's dequeue the next element (expected: 2nd thing): " << this->dequeue() << endl;
    cout << "Number of elements in the list after second dequeue (expected: 1): " << this->get_length() << endl;
    cout << "Next, let's peek the final element in the queue (expected: three): " << this->peek() << endl;
    cout << "Number of elements in list after peek (expected: 1): " << this->get_length() << endl;
    cout << "Now, let's remove this element with dequeue (expected: three): " << this->dequeue() << endl;
    cout << "Now there should be zero elements in the list, let's check (expected: 0): " << this->get_length() << endl;
    cout << "If we try to peek now, we should get an error message. Let's try: " << this->peek() << endl;
    cout << "What if we try to dequeue? Lets check: " << this->dequeue() << endl;
    cout << "How many elements are there after trying to peek and dequeue with zero elements in the list? (expected: 0): " << this->get_length() << endl;
    cout << "Tests completed!" << endl << endl;
}
int main(){
    string choice = "0";
    queue q;
    while(choice != "5"){
        cout << "Welcome to queue simulator 2023! \n";
        cout << "Choose one of the following: \n";
        cout << "1. Add to queue \n";
        cout << "2. Remove from queue\n";
        cout << "3. Peek into queue \n";
        cout << "4. View Length of queue\n";
        cout << "5. Quit \n";
        cout << "6. Run Preporgrammed tests (Do this first as this expects to start with nothing in the queue and I dont create a unique queue for this)\n";
        cout << "Your Choice: ";
        cin.clear();
        getline(cin, choice);
        while(choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6"){
            cout << "Invalid choice, please enter an int 1-4: ";
        }
        if(choice == "1"){
            cout << "Enter some data: ";
            string d;
            getline(cin, d);
            q.enqueue(d);
        }
        /*
        else if((choice == "2" || choice == "3") && q.get_length() == 0){
                cout << "The list is already empty!\n";
        }
        */
        else if(choice == "2"){
            cout << "\nData from front: " << q.dequeue() << endl << endl;
        }
        else if(choice == "3"){
            cout << "\nData from front: " << q.peek() << endl << endl;
        }
        else if(choice == "4"){
            cout << "\nLength of queue: " << q.get_length() << endl << endl;
        }
        else if(choice =="6"){
            q.runtests();
        }
    }
    return 0;
}