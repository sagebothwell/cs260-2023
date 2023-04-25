#include <iostream>
#include <string>

using namespace std;

int main(){

    cout << "hello world" << endl;
    cout << "Enter a message: ";
    string message;
    getline(cin, message);
    cout << message << endl;
    return 0;
}

//line comment test

/*
Big comment
test
*/