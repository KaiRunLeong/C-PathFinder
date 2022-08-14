#include "PathPlanner.h"

#include <iostream>

#define UNKNOWN_DISTANCE   0

PathPlanner::PathPlanner(Env env, int rows, int cols){
   this->env = env;
   this->rows = rows;
   this->cols = cols;
}

PathPlanner::~PathPlanner(){
   
}

//Set the Start coordinate (initialPos) and Goal coordinate (goalPos)
void PathPlanner::initialPosition(int row, int col){
   for(int i = 0; i < row; i++){
      for(int j = 0; j < col; j++){
         if(env[i][j] == 'S'){
            //Initialize distanceToS as 0 since starting point has no distance
            this->initialPos = new Node(i, j, UNKNOWN_DISTANCE);
         }else if(env[i][j] == 'G'){
            //Initialize distanceToS as 0 since goal's distanceToS is still unknown
            this->goalPos = new Node(i,j, UNKNOWN_DISTANCE);
         }
      }
   }
}

// Implementation for this method follows the pseudocode given 
// in the assignment specificaions
NodeList* PathPlanner::getReachableNodes(){
   Env env = this->env;

   int potentialReachablePoints = emptySymbol(env, this->rows, this->cols);
   
   NodeList* openList = new NodeList(potentialReachablePoints);
   NodeList* closeList = new NodeList(potentialReachablePoints);

   //Set first element of openlist to be S
   initialPosition(this->rows, this->cols);
   openList->addBack(this->initialPos);
   NodePtr p = openList->get(0);

   int row, column, distanceToS = 0;

   while(p != nullptr){
      distanceToS = p->getDistanceToS()+1;
      for(int sides = 1; sides < 5; sides++){
         //look up
         if(sides == 1){
            row = p->getRow()-1;
            column = p->getCol();
            if(row >= 0){
               addEligiblePoint(env, row, column, distanceToS, openList);
            }          
         //look right 
         }else if(sides == 2){
            row = p->getRow();
            column = p->getCol()+1;
            
            if(column < this->cols){
               addEligiblePoint(env, row, column, distanceToS, openList);
            }
            
         //look down
         }else if(sides == 3){
            row = p->getRow()+1;
            column = p->getCol();

            if(row < this->rows){
               addEligiblePoint(env, row, column, distanceToS, openList);
            }
         //look left
         }else if(sides == 4){
            row = p->getRow();
            column = p->getCol()-1;
            if(column >= 0){
               addEligiblePoint(env, row, column, distanceToS, openList);
            }
            
         }
      }
      
      closeList->addBack(p);
      p = nullptr;

      for(int i = 0; i < openList->getLength() && p == nullptr; i++){
         p = openList->get(i);    
         if(closeList->containsNode(p)){
            p = nullptr;
         }
      }
   }

   this->reachableNodes = openList;

   return openList;
}

// Method's implementation follows the hint given in the assignment specification
NodeList* PathPlanner::getPath(){
   int found = emptySymbol(this->env, this->rows, this->cols);

   NodeList* solution = new NodeList(found);

   NodePtr currPtr = this->goalPos;
   NodePtr potentialPtr;
   int row;
   int column;
   solution->addBack(currPtr);

   bool run = false;
   while(run == false){
      for(int sides = 1; sides < 5; sides++){
         //look up
         if(sides == 1){
            row = currPtr->getRow()-1;
            column = currPtr->getCol();
            if(row >= 0){
               for(int i = 0; i < this->reachableNodes->getLength(); i++){
                  if(this->reachableNodes->get(i)->getRow() == row && this->reachableNodes->get(i)->getCol() == column){
                     if(this->reachableNodes->get(i)->getDistanceToS() < potentialPtr->getDistanceToS()){
                        potentialPtr = this->reachableNodes->get(i);
                     }
                  }
               }
            }
         //look right 
         }else if(sides == 2){
            row = currPtr->getRow();
            column = currPtr->getCol()+1;
            if(column < this->cols){
               for(int i = 0; i < this->reachableNodes->getLength(); i++){
                  if(this->reachableNodes->get(i)->getRow() == row && this->reachableNodes->get(i)->getCol() == column){
                     if(this->reachableNodes->get(i)->getDistanceToS() < potentialPtr->getDistanceToS()){
                        potentialPtr = this->reachableNodes->get(i);
                     }
                  }
               }
            }

         //look down
         }else if(sides == 3){
            row = currPtr->getRow()+1;
            column = currPtr->getCol();
            if(row < this->rows){
               for(int i = 0; i < this->reachableNodes->getLength(); i++){
                  if(this->reachableNodes->get(i)->getRow() == row && this->reachableNodes->get(i)->getCol() == column){
                     if(this->reachableNodes->get(i)->getDistanceToS() < potentialPtr->getDistanceToS()){
                        potentialPtr = this->reachableNodes->get(i);
                     }
                  }
               }
            }
            
         //look left
         }else if(sides == 4){
            row = currPtr->getRow();
            column = currPtr->getCol()-1;
            if(column >= 0){
               for(int i = 0; i < this->reachableNodes->getLength(); i++){
                  if(this->reachableNodes->get(i)->getRow() == row && this->reachableNodes->get(i)->getCol() == column){
                     if(this->reachableNodes->get(i)->getDistanceToS() < potentialPtr->getDistanceToS()){
                        potentialPtr = this->reachableNodes->get(i);
                     }
                  }
               }
            }
         }
         
      }
      currPtr = potentialPtr;
      solution->addBack(currPtr);

      if(currPtr->getRow() == initialPos->getRow() && currPtr->getCol() == initialPos->getCol()){
         run = true;
      }      
   }
   
   return solution;
}

// Method checks if a NodeList already contains the same node based on its coordinates
bool PathPlanner::exist(NodeList* openList, NodePtr nodeToBeChecked){
   bool result = false;
   for(int i = 0; i < openList->getLength(); i++){
      if(nodeToBeChecked->getRow() == openList->get(i)->getRow() &&  nodeToBeChecked->getCol() == openList->get(i)->getCol()){
         result = true;
      }
   }
   return result;
}

// This method counts the total number of potential reachable points
int PathPlanner::emptySymbol(Env env, int row, int col){
   int found = 0;

   for(int i = 0; i < row; i++){
      for(int j = 0; j < col; j++){
         if(env[i][j] == SYMBOL_EMPTY || env[i][j] == SYMBOL_START || env[i][j] == SYMBOL_GOAL){
            found++;
         }
      }
   }

   return found;
}

// Method adds a node to the openList if a coordinate is an empty point or a goal point
void PathPlanner::addEligiblePoint(Env env, int row, int column, int distanceToS, NodeList* openList){
   if(env[row][column] == SYMBOL_EMPTY || env[row][column] == SYMBOL_GOAL){
      NodePtr newNode = new Node(row, column, distanceToS);
      if(exist(openList, newNode) == false){
         openList->addBack(newNode);
      }
   }
   
   if(env[row][column] == SYMBOL_GOAL){
      this->goalPos->setDistanceToS(distanceToS);
   }
}