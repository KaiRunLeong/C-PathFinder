#include "NodeList.h"
#include <iostream>

//Used in milestone 2 and milestone 3 in order to initialize length of nodes
NodeList::NodeList(){
   for(int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE; i++){
       nodes[i] = nullptr;
   }
   this->length = 0;
}

NodeList::~NodeList(){
   
}

// Method performs a deepcopy of another NodeList, however it was not used in Milestone 4
NodeList::NodeList(NodeList& other){   
    // TODO
    NodePtr newNode;
    for(int i = 0; i < NODE_LIST_ARRAY_MAX_SIZE && other.get(i) != nullptr; i++){
        newNode = new Node(other.get(i)->getRow(), other.get(i)->getCol(), 
            other.get(i)->getDistanceToS());
        addBack(newNode);
    }

}

//Added a new constructor so that the length of a new generic 1D array can be initialized
NodeList::NodeList(int totalPotentialPoints){
   this->nodes = new NodePtr[totalPotentialPoints];
   this->length = 0;
   this->totalPotentialPoints = totalPotentialPoints;
}

int NodeList::getLength(){
   return length;
}

NodePtr NodeList::get(int i){
   return nodes[i];
}

void NodeList::addBack(NodePtr newNode){
   bool added = false;
   for(int i = 0; i < this->totalPotentialPoints && added == false; i++){
       if(nodes[i] == nullptr){
           nodes[i] = newNode;
           added = true;
           this->length += 1;
       }
   }
}

bool NodeList::containsNode(NodePtr node){
    bool result = false;    
    for(int i = 0; i < this->length; i++){
        if(node == nodes[i]){
            result = true;
        }
    }
    return result;
}

void NodeList::clear(){
   for(int i = 0; i < this->length; i++){
       delete nodes[i];
   }
   this->length = 0;
}