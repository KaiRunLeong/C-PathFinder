
#include "Node.h"


Node::Node(int row, int col, int distanceToS){
   //TODO
   this->row = row;
   this->col = col;
   this->distanceToS = distanceToS;
}
    
Node::~Node(){
   //TODO
   //Deconstructor will be used if user wishes to manually clear NodeList
}

int Node::getRow(){
   //TODO
   return row;
}

int Node::getCol(){
   //TODO
   return col;
}

int Node::getDistanceToS(){
   //TODO
   return distanceToS;
}

void Node::setDistanceToS(int distanceToS){
   //TODO
   this->distanceToS = distanceToS;
}
