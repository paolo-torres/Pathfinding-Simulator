#ifndef AStar_H
#define AStar_H

#include <list> // C++'s standard library linked list http://www.cplusplus.com/reference/list/list/
#include "node.hpp"

#define X_LENGTH  6 //DO NOT CHANGE: x length of grid
#define Y_LENGTH  5 //DO NOT CHANGE: y length of grid

// The grid is organized in the following manner:
// X axis starts at (x=0,y=0) and grows rightwards
// Y axis starts at (x=0,y=0) and grows downwards
// No negative coordinates allowed
//
// 1 x 1 0 1 1 (x is stored at coordinates (x=1,y=0)
// 1 1 1 1 1 1
// 1 0 1 1 0 1
// 1 0 0 0 0 0
// x 1 1 0 0 0 (x is stored at coordinates (x=0,y=4)
// 
// Each 1 indicates a walkable path, and each 0 indicates otherwise

class AStar {
		// Calculates and returns the fcost
		static int getFCost(Node* currentNode);
		// Computes the Euclidean distance between two nodes and scales it by 10 to avoid floats
		static int getHDistance(Node* A, Node* B);
		// Iterates through the node's parents and creates a list of the shortest path to take
		static std::list<Node*> retracePath(Node* startNode, Node* endNode);	
		// For the current node, cnode, discovers all walkable neighbours, and adds them to the neighbours list
		static std::list<Node*> getNeighbours(Node* node, Node* grid[Y_LENGTH][X_LENGTH]);

	public:
		// Outputs the discovered path as a string
		static std::string getPathString(std::list<Node*> path);
		// Outputs path distance
		static int getPathDistance(std::list<Node*> path);
		// Finds shortest path between startNode and endNode using A* algorithm		
		static std::list<Node*> findPath(Node* grid[Y_LENGTH][X_LENGTH], Node* startNode, Node* endNode);
};

#endif
