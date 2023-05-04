Assignment 3 Read Me:

First, Big O complexity of the functions:

-Enqueue:
    This function takes a new entry and places it at the end of an n-element queue
    Thus, it has a complexity of O(n)

-Dequeue:
    This always just looks at head, it always has the same runtime
    Thus, it has a complexity of O(1)

-Peek
    Same as Dequeue
    Complexity of O(1)


Where important things happen in my code:

1. uses a linked-list to store values in the queue (list is made lines 6-23, the whole code uses it)

2. has an enqueue method that will appropriately add a value to the back of the queue as an appropriate element (lines 33-50)

3. has a dequeue method that will appropriately remove an element from the front of the queue and return its value (lined 57-68)

4. Optionally has a peek method that returns the value at the front of the queue without removing it (lines 51-56)

5. Tests (lines 71-93)
