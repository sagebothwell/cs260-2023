#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

void display_marb(int red, int blue, int green){ //dispays the contents of your marble bag
    cout << "Red Marbles: " << red << endl;
    cout << "Blue Marbles: " << blue << endl;
    cout << "Green Marbles: " << green << endl << endl;
}

void choices(int red, int blue, int green){ //displays choices to the user
    cout << endl << "Currently, you have the following marbles:" << endl;
    display_marb(red, blue, green);
    cout << "Which of the following would you like to do: " << endl;
    cout << "1. Add a red marble" << endl;
    cout << "2. Add a blue marble" << endl;
    cout << "3. Add a green marble" << endl;
    cout << "4. Add a random marble" << endl;
    cout << "5. Remove a red marble" << endl;
    cout << "6. Remove a blue marble" << endl;
    cout << "7. Remove a green marble" << endl;
    cout << "8. Remove a random marble" << endl;
    cout << "9. Display your total number of marbles" << endl;
    cout << "10. Quit" << endl;
    cout << "11. Run preprogrammed tests"  << endl << endl; 
}

bool error_handler(string s){ //makes sure the user enters one of the 11 available options
    if(s == "1" || s == "2" || s == "3" || s == "4" || s == "5" || s == "6" || s == "7" || s == "8" || s == "9" || s == "10" || s == "11")
        return true;
    return false;
}

void add_red(int& red){ 
    red++;
}

void add_blue(int& blue){
    blue++;
}

void add_green(int& green){
    green++;
}

void add_random(int& red, int& blue, int& green){
    int choice = rand() % 3; //picks a number 0-2
    if(choice == 1){
        add_red(red);
    }
    if(choice == 0){
        add_blue(blue);
    }
    if(choice == 2){
        add_green(green);
    }
}

void remove_red(int& red){
    if(red != 0){
        red--;
    }
    else{
        cout << "You try to get rid of a red, but you already have none, you just end up making a fool of yourself." << endl << endl; //error mssg
    }
}

void remove_blue(int& blue){
    if(blue != 0){
        blue--;
    }
    else{
        cout << "You try to get rid of a blue, but you already have none, you just end up making a fool of yourself." << endl << endl; //error mssg
    }
}

void remove_green(int& green){
    if(green != 0){
        green--;
    }
    else{
        cout << "You try to get rid of a green, but you already have none, you just end up making a fool of yourself." << endl << endl; //error mssg
    }
}

void remove_random(int& red, int& blue, int& green){
    int choice = rand() % 3; //picks a number 0-2
    if(red == 0 && blue == 0 && green == 0){ //if there are no marbles
        cout << "You try and remove a marble, but you dont have any marbles (you are not very good at marble simulator 2023, it seems)" << endl << endl; //error mssg
        return;
    }
    while(true){ //loops forever
       if(choice == 0){
            if(red > 0){
                red--;
                return; //escapes
            }
            else{
                choice++; //sets choice to 1
            }
        }
        if(choice == 1){
            if(blue > 0){
                blue--;
                return; //escapes
            }
            else{
                choice++; //sets choice to 2
            }
        }
        if(choice == 2){
            if(green > 0){
                green--;
                return; //escapes
            }
            else{
                choice = 0; 
            }
        }
    }
}

void count(int red, int blue, int green){
    cout << red + blue + green << endl;
}

void test(int red, int blue, int green){
    cout << "\n" << "Note, for this test I set all marble counts to zero at the start to make math easier" << endl;
    
    cout << "TEST 1:" << endl << "We will add 4 red marbles, 3 green marbles, and 2 blue marbles." << endl;
    cout << "BEFORE:" << endl;
    display_marb(red, blue, green);
    for(int i=0; i<4; i++)
        add_red(red);
    for(int i=0; i<3; i++)
        add_green(green);
    for(int i=0; i<2; i++)
        add_blue(blue);
    cout << "AFTER:" << endl;
    display_marb(red, blue, green);
    cout << "\n\n";
    
    cout << "TEST 2:" << endl << "We will now look at the total number of marbles (expected: 9)" << endl;
    cout << "Total number of marbles: ";
    count(red, blue, green);
    cout << "\n\n";
    
    cout << "TEST 3:" << endl << "Now we will remove 3 red marbles, 2 green marbles, and 1 blue marble (this means we should have 1 of each color)" << endl;
    cout << "BEFORE:" << endl;
    display_marb(red, blue, green);
    for(int i=0; i<3; i++)
        remove_red(red);
    for(int i=0; i<2; i++)
        remove_green(green);
    remove_blue(blue);
    cout << "AFTER:" << endl;
    display_marb(red, blue, green);
    
    cout << "TEST 4:" << endl << "We will randomly add and remove 1 marble (run this test mutiple times to see that it is random)" << endl;
    add_random(red, blue, green);
    cout << "AFTER ADDING:" << endl;
    display_marb(red, blue, green);
    remove_random(red, blue, green);
    cout << "AFTER REMOVING:" << endl;
    display_marb(red, blue, green);
    
    cout << "FINAL TEST:" << endl << "We will now empty the bag by removing three marbles randomly" << endl;
    for(int i=0; i<3; i++){
        remove_random(red, blue, green);
    }
    cout << "After removing three random marbles:" << endl;
    display_marb(red, blue, green);

}
void do_choice(int choice, int& red, int& blue, int& green){ //takes the user's choice and runs the correct function
    if(choice == 1)
        add_red(red);
    if(choice == 2)
        add_blue(blue);
    if(choice == 3)
        add_green(green);
    if(choice == 4)
        add_random(red, blue, green);
    if(choice == 5)
        remove_red(red);
    if(choice == 6)
        remove_blue(blue);
    if(choice == 7)
        remove_green(green);
    if(choice == 8)
        remove_random(red, blue, green);
    if(choice == 9)
        count(red, blue, green);
    if(choice == 11)
        test(0,0,0); //0,0,0 because we assume that we have no marbles at the start of the tests
}


int main() {
    srand(time(NULL)); //seeds the rand function
    int red = 0; //initializes the marble variables
    int blue = 0;
    int green = 0;
    string choice; //user choice
    bool choice_valid; //bool for if you made a valid input
    int final_choice; //user choice as an int
    cout << "Welcome to marble simulator 2023!" << endl;
    while(final_choice != 10){ //while you have not quit
        choices(red, blue, green);
        choice_valid = false; //assume the user made a bad input
        while(choice_valid == false){
            cout << "Enter your choice (1-11): ";
            cin.clear(); 
            getline(cin, choice);
            choice_valid = error_handler(choice);
            if(choice_valid == false)
                cout << "INVALID INPUT! Please input an integer 1-11" << endl; //error mssg
        }
        final_choice = stoi(choice); //makes the users good choice to an int
        
        do_choice(final_choice, red, blue, green);
    }
    return 0;
}