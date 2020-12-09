# CSCI-2275-Final-Project
This project will be a solo developed maze genertation and pathfinding application the goal is to create an efficent random maze generaton and use BFS to pathfind through it. The user will be able to dynamically resize the maze to any size larger than 3x3. 
# Implimentation:
 This project will be using 2 data structures: graphs for the actual implimentation of the graph, and stacks for the implimentation of the random maze generation. The main advantage of using graphs is having easy, non-destructive resizeing of the maze. Another benifit that is not part of my plan to impliment would be mazes that are not of a square shape. Although they could be implimented in an array it would be ineffective for certaim maze designs and leave alot of empty space. The queues are used to create a psuedo-recursive style implimentation for the random maze generation. Basically a wall is cut into the maze from a starting point until it hits another wall. Then a single hole is generated in the new wall. Then each possible "branch" off of the wall is checked for validity(See code for specific parameters under isValid() method in Graph.cpp) if there are no valid branches off the wall, pop it off the stack. Otherwise, randomly choose one of those "Branches" and repeat the prossess, putting the branch into the stack. This leads to a valid maze that is still challenging and intricate. 
 # Third-party software:
There is no third party software being used in this application. With the exception of iostream, string and fstream standard librairy files I have created all the code myself. 
# Issues
For me at least every once in a while when I run the project there is a floating point error with the recursive maze generation function. Also I think there might be a random seg fault every once in while when you resize the maze and make both sizes bigger.
# Running the code:
g++ -std=c++11 -o test Stack.cpp Graph.cpp Runner.cpp

./test

There are no command line arguments to feel free to change "test" to whatever file name you want when running
