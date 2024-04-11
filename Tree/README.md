Augmented Binary Search Tree
Insertion: Need to use recursion, First insert, then check balance and rotate. A way to shorten code: have a function that returns height and deals with when a child is “nullptr”. 
Store weight: update weight after each rotation.  
Find Successor: Keep going right until finding an element that is bigger (if you cannot find, then no successor), then go left. 
