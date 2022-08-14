
#ifndef COSC_ASS_ONE_PATH_PLANNING
#define COSC_ASS_ONE_PATH_PLANNING

#include "Node.h"
#include "NodeList.h"
#include "Types.h"

class PathPlanner {
public:

   /*                                           */
   /* DO NOT MOFIFY ANY CODE IN THIS SECTION    */
   /*                                           */


   // Initialise with a given Env of size (rows,cols)
   PathPlanner(Env env, int rows, int cols);

   // Clean-up
   ~PathPlanner();

   // Set The initial position
   void initialPosition(int row, int col);

   // Method for Milestone 2
   // Return a DEEP COPY of the NodeList of all node's
   //    that the robot can reach with distances
   NodeList* getReachableNodes();


   // Method for Milestone 3
   // Get the path from the starting position to the given goal co-ordinate
   //    The path should be a DEEP COPY
   NodeList* getPath();
   NodeList* shallowCopy(NodeList&nodeList);

   /*                                           */
   /* YOU MAY ADD YOUR MODIFICATIONS HERE       */
   /*                                           */

   bool exist(NodeList* openList, NodePtr nodeToBeChecked);
   void setPotentialPtr(int row, int column);
   int emptySymbol(Env env, int row, int col);
   void addEligiblePoint(Env env, int row, int column, int distanceToS, NodeList* openList);

private:
   Env env;
   int rows;
   int cols;
   NodePtr initialPos = nullptr;
   NodePtr goalPos = nullptr;
   NodeList* reachableNodes;

};

#endif // COSC_ASS_ONE_PATH_PLANNING
