Big O complexity comparison table:

                      |Queue|Arbitrary List|Auto-Sorting List
-------------------------------------------------------------
Adding to list        |O(n) |O(n)          |O(n)
-------------------------------------------------------------
Removing From list    |O(1) |O(n)          |O(n)
-------------------------------------------------------------
Peeking/Searching List|O(1) |O(n)          |O(n)

Design Pseudocode:

add to list (lines 35-67):
Make a new node with desired data in it
if the list is empty or if the value stored in the new node is less than the value stored in head  
    then replace head with new node
else    
    go through the list until either at the end or new node stored value is greater then current node stored value
    if at the end of the list
        put new node at end of the list
    else
        make new node->next be current node->next->next and make current node->next be the new node


Search list (lines 70-83):
This function starts with an entered index n for the nth smallest element in the list
Because elements are auto sorted in order of least to greatest, we just go through the list n spots from head.
if searching for a spot out of the lists scope
    then return and error message and abort the function
else
    go through the list index times
return the value of the node which is landed on

Remove from list (lines 85-122):
do the search stuff from the search function
store the value of the landed on node in an int variable
if at head:
    set current to head
    make head= head->next
    delete nCurrent
if at end of list:
    set current to head
    cycle through elements until current->next is NULL
    delete current
else:
    set current to head
    cycle current through the list to the spot before the desired node
    set a new node pointer to current->next
    set current next to current->next->next
    delete the new node pointer


