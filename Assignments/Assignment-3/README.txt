Design for major functions:

Input:
Make a new node and fill inm the proper values
check fring cases (tries to insert in invalid spot or negative spot)

if a fringe case is met return an error message

if the list is 0 long, just make the new node the head

if the node is supposed to go in the very back:
    set current to head
    while current->next does not equal NULL, set current equal to current->next
    set current next equal to the new node

otherwise:
    set current to head
    Let i denote the spot in the list we are inserting to
    repeat i-1 times:
        current = current->next
    set the new node ->next to current->next
    set current->next to the new node


Peek:
    If the list is empty or you peek at an invalid spot, return an error message
    Otherwise:
    current = head
    Loop until we reach the desired spot:
        current = current->next
    return current->stored data

Remove:
    Run the same fringe case check as Peek and return an error message if appropriate 
    current = head
    Loop until we reach the desired spot:
        current = current->next
    make a new string and set this string equal to the data in current
    make a temp pointer and set it equal to current
    current = head
    Loop until we reach (the desired spot - 1):
        current = current->next
    set current->next = temp_pointer->next
    delete temp_pointer
    return the string which was made earlier

Possible Tests:
Input tests:
    -check that a lists length is zero and then add an element, check the lists length again (should be 1)
Input/peek tests:
    -Input a few elements into a list, inserting them wherever you want and then peek at each element in the list to make sure they were all enetered where you wanted
Remove tests:
    -Remove elements from index n over and over until you get an error message, then peek at the full list to see if things were removed correctly
    -Add a single element and then remove it
Remove/Peek tests:
    -Try to remove/peek at an empty list, try to remove/peek an invalid spot (i.e. spot 1000 in a 3 element list)



Where stuff shows up in the code:

Input function -- lines 33-66
The input function works exactly as described in the above design, it would have a big O complexity of O(n) as at worst it will go through the whole list to
input at the very back.

Peek Function -- lines 68-81
The peek function works exactly as described in my design, it would have a big O complexity of O(n) as worst case scenario it will go through the whole list twice
to return a value from the very back

Remove Function -- lines 83-108
The remove function works exactly as described in the design, it would have a complexity of O(n) as it at worsdt will go through the whole list once to find the node
it wants to delete and then run through the whole list - 1 again in order to snip the element out of the list. This means it would have a Big O complexity of O(2n-1),
which is linear so we group it together with O(n).

Tests Function -- lines 110-147
This function runs a series of tests on my functions to make sure they all work as intended. The meat of these tests is adding 3 elements to my list in a known order and 
then peeking/removing them to see what happens.

**NOTE: My list starts at the oth spot, so to start adding things to it you must start by inputting at spot 0 and then build from there
    