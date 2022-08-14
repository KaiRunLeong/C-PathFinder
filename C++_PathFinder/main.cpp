/*
Author: Kai Run Leong (S3862092)

The approach that I have taken to implement this program is to focus on the usage of pointers and 
references that I have learnt from the course thus far, in order to ensure that an appropriate amount 
of memory is allocated to accurately read and write an enviroment. The issues that I have encountered
during the implementation were mostly segmentation faults as not enough memory were allocated. However,
the faults were carefully investigated and should no longer be a problem, unless the user adds an extra 
empty line during file redirection (e.g. 20 x 20, but file has 21 rows and the last row being empty).

NOTE ON TESTS
All of the test cases will test the program's ability to handle segmentation faults and ability
to choose a path. Some may look simple, however, it is important to note that many issues managed
to surface because of these tests.
*/

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"

#define MOVE_UP     '^'
#define MOVE_RIGHT  '>'
#define MOVE_DOWN   'v'
#define MOVE_LEFT   '<'
#define ROW_COLUMN_INITIALIZATION   1


// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
Env readEnvStdin(int &rows, int &columns);//, std::string filename);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printPath(Env env, NodeList* solution, int envRow, int envCol);

// Print reachable paths, total possible reachable paths, and env dimensions
void printReachablePositions(NodeList* reachablePositions, int row, int col, int total);

// Additional methods
void setDirections(Env env, int nextRow, int nextCol, int currRow, int currCol);

int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!
    /*
    std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    testNode();
    testNodeList();
    std::cout << "DONE TESTING" << std::endl << std::endl;
    */

    // Load Environment 
    int rows = 0;
    int columns = 0;
    Env env = readEnvStdin(rows, columns);

    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathPlanner* pathplanner = new PathPlanner(env, rows, columns);
    NodeList* reachablePositions = nullptr;
    reachablePositions = pathplanner->getReachableNodes();

    //printReachablePositions(reachablePositions, rows, columns, 
    //reachablePositions->getLength()); //TESTING

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathplanner->getPath();

    //print the path
    printPath(env, solution, rows, columns);

    delete pathplanner;
    delete reachablePositions;
    delete solution;

}

Env readEnvStdin(int& rows, int& columns){
    //TODO 

    // Initialize row and column first in order to accurately determine
    // how much memory must be allocated for the environment
    int row = ROW_COLUMN_INITIALIZATION; 
    int column = ROW_COLUMN_INITIALIZATION; 

    // char variable c will be used to temporarily store each character from std::cin
    char c;

    // characterArray will be used to store all values from std::cin, however, it will
    // definitely have extra unused memory which could cause complications to the program.
    // Therefore, another character array called deepCopy will be made later.
    char characterArray[NODE_LIST_ARRAY_MAX_SIZE];

    // Get character from std::cin.get()
    int i = 0;
    while(!std::cin.eof()){ 
      std::cin.get(c);
      
      if (c == '\n'){
        characterArray[i] = 'n';
        row++;
        column = 0;
      }else{   
        column++;
        characterArray[i] = c;
      }
      i++;
    }

    column--; //Minus 1 because last row of env does not have \n character

    rows = row;
    columns = column; 

    //Perform a deep copy of characterArray in order to allocate 
    //the right amount of memory needed
    char deepCopy[i];
    for(int deepI = 0; deepI < i; deepI++){
        deepCopy[deepI] = characterArray[deepI];
    }

    //Allocate memory for environment
    Env env = nullptr;
    if (rows >= 0 && columns>= 0) {
      env = new char*[rows];
      for (int i = 0; i != rows; ++i) {
         env[i] = new char[columns];
      }
    }

    //Initialize each element in env
    int j = 0;
    for(int index = 0; index < row; index++){
        for(int index2 = 0; index2 < column; index2++){
            env[index][index2] = deepCopy[j];
            j++;
        }   
        j++;
    }

    return env;
}   

void printPath(Env env, NodeList* solution, int envRow, int envCol) {
    //TODO
    int row, column, currRow, currCol, nextRow, nextCol;

    //Initialize to start point coordinates
    row = solution->get(solution->getLength()-1)->getRow();
    column = solution->get(solution->getLength()-1)->getCol();

    //Set the directions for the optimum path in the environment 
    //from Start point to Goal point
    for(int i = solution->getLength() - 1; i > 0; i--){  
        currRow = solution->get(i)->getRow();
        currCol = solution->get(i)->getCol();
        nextRow = solution->get(i-1)->getRow();
        nextCol = solution->get(i-1)->getCol();

        if(i < solution->getLength() -1){
            if(currRow == row - 1){
                env[currRow][currCol] = MOVE_UP;
                setDirections(env, nextRow, nextCol, currRow, currCol);

            }else if(currRow == row + 1){
                env[currRow][currCol] = MOVE_DOWN;
                setDirections(env, nextRow, nextCol, currRow, currCol);

            }else if(currCol == column - 1){
                env[currRow][currCol] = MOVE_LEFT;
                setDirections(env, nextRow, nextCol, currRow, currCol);
                
            }else if(currCol == column + 1){
                env[currRow][currCol] = MOVE_RIGHT;
                setDirections(env, nextRow, nextCol, currRow, currCol);
            }
        }
        row = currRow;
        column = currCol;       
    }

    // Print path to terminal
    for(int i = 0; i < envRow; i++){
        for(int j = 0; j < envCol; j++){
            std::cout << env[i][j];
        }
        std::cout << std::endl;
    }
}

// This method is for testing purposes, since this method was originally 
// in the starter code, this method will not be deleted
void printReachablePositions(NodeList* reachablePositions, int row, int col, int total){
    //TODO
    for(int i = 0; i < reachablePositions->getLength(); i++){
        std::cout << reachablePositions->get(i)->getRow() << ", "
         << reachablePositions->get(i)->getCol() << ", " 
         << reachablePositions->get(i)->getDistanceToS() << " | ";
    }
    std::cout << std::endl;
    
}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList(2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addBack(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addBack(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->get(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceToS() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}

/*Additional methods*/

// Set the direction for optimum route in environment
void setDirections(Env env, int nextRow, int nextCol, int currRow, int currCol){
    if(nextRow == currRow + 1){
        env[currRow][currCol] = MOVE_DOWN;
    }else if(nextRow == currRow - 1){
        env[currRow][currCol] = MOVE_UP;
    }else if(nextCol == currCol - 1){
        env[currRow][currCol] = MOVE_LEFT;
    }else if(nextCol == currCol + 1){
        env[currRow][currCol] = MOVE_RIGHT;
    }
}

