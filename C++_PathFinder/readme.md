# INSTRUCTIONS TO COMPILE AND PLAY

The program has already been compiled by the g++ compiler before pushing this code to github. To run the program, simply use the following command in the terminal: ./play < \<testCase under testCases directory>

EXAMPLE:
To run object (compiled program) file: ./play < tessCases/sample01.env

Should there be a need to re-compile the code please type in the following:</br> g++ -Wall -Werror -std=c++14 -O -o play main.cpp Node.cpp NodeList.cpp PathPlanner.cpp