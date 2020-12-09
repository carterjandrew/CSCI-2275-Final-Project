#include "Graph.h"
#include <fstream>
#include <time.h>
using namespace std;
//This is used for handing basic input. With cin if a non-number is entered it can mess everything up so I use this to catch such exeptions.
int getInput()
{
    string in;
    int out;
    cin>>in;
    try{
        out = stoi(in);
    }
    catch(exception &ex){
        return -1;
    }
    return out;
}
//Main function that runs our code
int main(int argc, char const *argv[])
{
    //Initialise maze, random number seed, and the width and height of the maze. If the input is bad it will return. 
    srand (time(NULL));
    cout << "Welcome to Carters Final Project for CSCI2275!\nThis project allows you to create and randomly generate a maze, and then mess aourd with it as you please\nTo begin, please enter a width for the Maze:\n";
    int width;
    string input;
    cin >> input;
    try{
        width = stoi(input);
    }
    catch(exception &err){
        cout << "Bad input, try again\n";
        return 1;
    }
    cout << "\nNow please enter a height:\n";
    int height;
    cin>>input;
    try{
        height = stoi(input);
    }
    catch(exception &err){
        cout << "Bad input, try again\n";
        return 1;
    }
    Maze maze(width, height);
    //Now we loop over a main menu where you can preform actions the menu can only be exited by returning. 
    while (true)
    {
        std::string dmenu = "======Main Menu=====\n"
                    "Please enter the number of the command below you want to preform\n"
					"1. Recursively Divise the Maze\n"
					"2. Set Start Point(for pathfinding in the maze)\n"
                    "3. Set End Point\n"
                    "4. Pathfind\n"
                    "5. Print Maze\n"
                    "6. Resize\n"
                    "7. Output current maze to file\n"
					"8. Quit\n";
        int choice;
        cout << dmenu;
        //inner loop over menu, we again try to avoid errors in input with a try/catch function
        while (cin >> input)
        {
            //Set choice to -1 so if nothing happens we go through default switch choice. 
            choice = -1;
            //Try to get proper input, as long as it's a number it should work. 
            try{
                choice = stoi(input);
            }
            catch(exception &err){
                cout << "Bad input, try again\n";
            }
            //Block out cin so we dont get garbage while we work on our funcitions. 
            cin.clear();
            cin.ignore();
            string fileName;
            ofstream file;
            int x, y;
            switch (choice)
            {
                //If we divide up the maze we need to get rid of the start and end nodes as well as the path so we dont have issues with them. 
                case 1:
                    maze.resetPathfinding(true);
                    //Recursive division clears out maze before so we dont try and write one maze ontop of another. 
                    maze.recursiveDivision();
                    cout << dmenu;
                    break;
                //Create/modify the starting node for our pathfinding. This also has to try and clear out previous paths in the maze before setting a new one. 
                case 2:
                    cout << "The top left coordinate is 1,1 and the bottom left is " << maze.width << ", " << maze.height << " \nEnter the x coordinate\n";
                    //If we dont enter a number, it will return -1, that will be caught by if below. 
                    x = getInput();
                    cout << "Enter the y coordinate\n";
                    y = getInput();
                    if(x-1 < 0 || y-1 < 0 || y > maze.height|| x > maze.width)
                    {
                        cout << "There is something wrong with the coordinates you entered\n";
                    }
                    else
                    {
                        maze.resetPathfinding(false);
                        maze.setStart(x-1, y-1);
                    }
                    cout << dmenu;
                    break;
                //Same thing as case 2 but we set up an end point instead of a start. 
                case 3:
                    cout << "The top left coordinate is 1,1 and the bottom left is " << maze.width << ", " << maze.height << " \nEnter the x coordinate\n";
                    x = getInput();
                    cout << "Enter the y coordinate\n";
                    y = getInput();
                    if(x < 0 || y < 0 || y > maze.height - 1 || x > maze.width -1)
                    {
                        cout << "There is something wrong with the coordinates you entered\n";
                    }
                    else
                    {
                        maze.resetPathfinding(false);
                        maze.setEnd(x-1, y-1);
                    }
                    cout << dmenu;
                    break;
                //maze.pathFind will naturally handle if our start or end point are not set up. Because it is a void return we can sinmply exit if things are not set up right. 
                case 4:
                    maze.pathFind();
                    cout << dmenu;
                    break;
                //Just print the maze, nothing else is needed, no bad input can be given. 
                case 5:
                    maze.print();
                    cout << "\n\"WW\" = wall, \"  \" = open space, \"P\" = path, \"SS\" = start, \"EE\" = end\n\n"; 
                    cout << dmenu;
                    break;
                //Resize the maze requires at least a 3x3 maze, we handle bad input through getInput() and then check if its big enough.
                //This requires resetting pathfinding so we dont end up with bad pointers for our start and end nodes. We also reset our maze devision so we dont end up with a invalid maze. 
                case 6:
                    maze.resetPathfinding(true);
                    cout << "Enter new width\n";
                    int w;
                    int h;
                    w = getInput();
                    cout << "\nEnter new height\n";
                    h = getInput();
                    if(w > 3 && h > 3)
                    {
                        maze.resizeMaze(w,h);
                        maze.resetMaze();
                    }
                    else
                    {
                        cout << "The size you entered was bad! Pleaze make it larger than 3x3.\n";
                    }
                    
                    cout << dmenu;
                    break;
                //Outputting maze is like printing with the extra step of opening a file. Even if file allready exists it will be overwritten so be careful!
                case 7:
                    cout << "Input file name (NO NOT INCLUDE .txt)\n";
                    cin >> fileName;
                    fileName += ".txt";
                    file.open(fileName);
                    file << maze.textMaze();
                    file.close();
                    cout << dmenu;
                    break;
                //Quit out of maze, we really shouldnt need the break but its there for formality. 
                case 8:
                    return 0;
                    break;
                //For handing bad inputs(like -1) so we dont exit if we have a number outide rang.e 
                default:
                    cout << dmenu;
                    break;
            }
        }
    }
    
    return 0;
}
