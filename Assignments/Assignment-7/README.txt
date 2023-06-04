For this assignment, I only did the more advanced hashtable which we discussed as an option in class.

Design for Hashtable:
The big idea for my hastable is that it will be very similar to what we did in class (specifically the same hash function) but instead of sending values into
an array of strings as we did in class, I will send values into an array of linked lists. This means that when collisions occur, that is, when element go to a 
non empty list, no data will be lost. Instead, my code will just add the new value to the list. This means that my code does not lose data, but it does this at
the cost of Big O and runtime complexity, specifically my remove and find functions will have complexity O(n) instead of O(1) which the simple hashtable has.
However, my add function will have complexity O(1) just like the simple hashtable because it will just add the new data to the top of the list.

My hashtable will store data by running entered strings of data through my hash function. This hash function will return a number which is found by adding together
the int conversions for each char in the string and then mod-ing this value by the capacity of the hash table. This number will decide which linked list the new data
will be housed in. 

Add functiom pseudocode:
Run hash function to get the desired storage list
Create a new node pointer with desired value in it stored
if the desired list is empty, then add one to length and set the list's head to the new node
otherwise, se the new node's next to the current head and then set head to the new node

Remove function pseudocode:
As in the add function, run the hash function to figure out which list to look at
If the desired list is empty return an error mssg
If the head of the list is the desired value, then set a pointer equl to it and move head to head->next, if head is now empty do size--, return the value in the pointer
Otherwise set list.current equal to list.head
While list.current does not equal NULL
    if current-next has desired value, make a new pointer and have it point to current next, make current->next equal current->next->next, return value in new pointer
    else, set current to current->next
return that the value was not in the hastbale if we escape the while loop

Search function pseudocode:
Run the hash function to find desired list
If the desired list is empty return an error mssg
If the head of the list is the desired value, return the value in head
Otherwise set list.current equal to list.head
While list.current does not equal NULL
    if current-next has desired value,  return value in current->next
    else, set current to current->next
return that the value was not in the hastbale if we escape the while loop

Hashtable pseudocode:
Exactly the same as in class example
make a new int called sum, set sum to 0
go through each element of an inputted string, adding up the int value for each char entry
set sum to sum%capacity
return sum

Potential Tests:
1. Create a hashtable with size 5, run the get_size and get_capacity functions, ideally we will see a size of 0 and a capacity of 5
   this will test my constructor, as well as my getters for size and capacity
2. Try to remove an element while the list is empty, this should result in an error mssg
   this will test my remove function and how it acts on an empty table
3. Try to search for an element while the list is empty, this should result in an error mssg
   this will test my search function and how it acts on an empty table
3. As a pretty big test, try to add five or more elements to the table, some which should occupy the same list spot, this will test my add
   function, as it will see if it can add to empty lists and occupied lists, as well as test how add works with collisions
4. After test 3, I could again check size and capacity, hopefully size is not as big as the number of element I put in because sometimes it is
   going to an already occupied spot
5. Try to remove an element which is in a list on its own, this will test the fringe case stuff in my remove function. After that, try to remove that same element
   again, should result in an error mssg
6. Try to search for an element which is in a list on its own, this will test the fringe case stuff in my search function. After that, try to search for that same element
   again, should result in displaying the value again
7. check size and capacity after removal and after seraching for elements whioch exist, this will ensure they are working properly (i.e. capacity remains stagnant and 
   size only changes when I remove from a list that only has one element or add to an empty list.)
8. Search for an element after removing it, this will test to make sure my search function can't find nodes which should be deleted, should display error mssg
9. Make sure to remove elements from the start, end, and middle of a list, by testing these extremes I will be able to make sure that my removal function always 
   finds and properly deletes nodes. To make sure it is actually deleting things, I can search for those things after deleting them and also check size and capacity 
   when applicable 

Briefly describing Big O complexity of the three main functions:

Add Function:
This function first searches for table spot using the hash function (constant complexity), makes a new node (constant complexity) and finally places said 
node at the top of the desired list (constant complexity). Overall, thsi function has Big O complexity of O(1).

Remove Function: 
This function starts by running the has function (constant complexity), checking the fringe cases of empty list or desired value at head and acts accordingly 
(constant complexity) and then  runs through the whole list until it either finds the value it want s to remove or reaches the end (At worst goes through all 
n elements here). Overall, this function has O(n) complexity.

Search Function:
This function starts by running the has function (constant complexity), checking the fringe cases of empty list or desired value at head and acts accordingly 
(constant complexity) and then  runs through the whole list until it either finds the value it wants or reaches the end (At worst goes through all 
n elements here). Overall, this function has O(n) complexity.

Where stuff shows up in my code:

Add function (lines 64-77)
Remove Function (lines 79-109)
Search Function (lines 111-130)
Hash Function (lines 55-62)
Constructor (lines 33-41)
Destructor (lines 43-53)
Tests (lines 140-180)

