This assignment aims to model a bag of marbles where we can add and remove marbles by color or randomly and can look at the total number of marbles in the bag.

Explanation of how marbles are represented:
In this program, marbles will be represented as three different interger type variables denoted 'red', 'blue', and 'green' These variables will all start off being
set to zero, and their values will not go below zero ever. 

Explanation of different algorithms that I will incorporate:

Adding by color (lines 37-47):
The algorithm for adding any color of marble is the same, but here is an example algorithm for adding a red marble:

Simply add 1 to the 'red' variable type

Removing by color (lines 62-87):
The algorithm for removing any color of marble is the same, but here is an example algorithm for removing a red marble:

if there are zero red marbles, then do nothing/error message
otherwise, subtract 1 from the 'red' variables

Adding random (lines 49-60):
pick a random number 0-2
if the number is 0, add 1 to red
if the number is 1 add 1 to blue
if the number is 2 add 1 to Green

Removing random (lines 89-124):
if 'red'='blue'='green'=0, do nothing/error message
otherwise:
pick random number 0-2
repeat the follwing indefinitely:
    if the number is zero and 'red' > 0, remove one from red and escape the loop
    if the number is zero and 'red' = 0, add one to the random number

    if the number is one and 'blue' > 0, remove one from red and escape the loop
    if the number is one and 'blue' = 0, add one to the random number

    if the number is two and 'green' > 0, remove one from red and escape the loop
    if the number is two and 'green' = 0, add set the random number to 0

Reporting total number of marbles (lines 126-128):
Add 'red', 'green', and 'blue' together and print out the result

Possible Tests (lines 130-172):
I could write tests that do the following:
-Add a known number of known-color marbles to my marble bag and print out the contents of the bag before and after to make sure it matches (132-142)
-Remove a known number of known-color marbles to my marble bag and print out the contents of the bag before and after to make sure it matches (148-157)
-If there are n marbles in the bag, remove n random marbles, this should result in the bag being empty (165-170)
-While there is a known amount of marbles in the bag, print out the number of marbles and make sure it matches (144-146)
-Randomly add/remove 1 marble, run this test multple times to make sure it is random (158-164)



