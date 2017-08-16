#include <iostream>
#include <math.h>
#include <algorithm> 
#include <string>
#include <sstream>

#include "a_star.hpp"

using namespace std;

// Calculates and returns the fcost
int AStar::getFCost(Node* currentNode) {
	currentNode->fCost = currentNode->gCost + currentNode->hCost;
	return currentNode->fCost;
}

// Computes the Euclidean distance between two nodes and scales it by 10 to avoid floats
int AStar::getHDistance(Node* A, Node* B) {
	return sqrt(pow(abs(A->posX - B->posX), 2) + pow(abs(A->posY - B->posY), 2)) * 10;
}

// Iterates through the node's parents and creates a list of the shortest path to take
list<Node*> AStar::retracePath (Node* startNode, Node* endNode) {
	list<Node*> path;	
	Node* currentNode = endNode;
	while (currentNode != startNode) {
		path.push_front(currentNode);
		currentNode = currentNode->parent;
	}
	return path;
}

// For the current node, cnode, discovers all walkable neighbours, and adds them to the neighbours list
list<Node*> AStar::getNeighbours(Node* cnode, Node* grid[Y_LENGTH][X_LENGTH]) {
	list<Node*> neighbours;	
	for (int i = cnode->posX - 1; i <= cnode->posX + 1; i++)
		for (int j = cnode->posY - 1; j <= cnode->posY + 1; j++)
			if (i >= 0 && i < X_LENGTH && j >= 0 && j < Y_LENGTH && grid[j][i]->walkable && grid[j][i] != cnode)
				neighbours.push_back(grid[j][i]);
	return neighbours;
}

// Outputs the discovered path as a string
string AStar::getPathString(list<Node*> path) {
	stringstream outputStream;
	for (list<Node*>::iterator it = path.begin(); it != path.end(); ++it)
		outputStream << "(" << (*it)->posX << "," << (*it)->posY << ")" << endl;
	return outputStream.str();
}

// Outputs path distance
int AStar::getPathDistance(list<Node*> path) {
	return path.size() > 0 ? path.back() -> fCost : 0;
}

// Finds shortest path between startNode and endNode using A* algorithm
list<Node*> AStar::findPath(Node* world[Y_LENGTH][X_LENGTH], Node* startNode, Node* endNode) {
	list<Node*> openSet; // list of nodes not yet evaluated
	list<Node*> closedSet; // list of nodes already evaluated
	list<Node*> results;
	Node* currentNode;
	startNode->gCost = 0;
	startNode->hCost = getHDistance(startNode, endNode);
	startNode->fCost = startNode->hCost;
	openSet.push_back(startNode); // insert the starting node at the beginning of the open set
	while(!openSet.empty()) {
		currentNode = openSet.front();
		for (list<Node*>::iterator it = openSet.begin(); it != openSet.end(); it++)
			if (AStar::getFCost(*it) < AStar::getFCost(currentNode)
				|| (AStar::getFCost(*it) == AStar::getFCost(currentNode) && (*it)->hCost < currentNode->hCost))
				currentNode = *it;
		openSet.remove(currentNode);
		closedSet.push_front(currentNode);
		// temp, to allow for compilation
		list<Node*> neighbours = getNeighbours(currentNode, world);
		for(list<Node*>::iterator it = neighbours.begin(); it != neighbours.end(); it++) {
			bool skip = false;
			for(list<Node*>::iterator closed = closedSet.begin(); closed != closedSet.end(); closed++) {
				if (*it == *closed) {
					skip = true;
					break;
				}
			}
			if (!skip) {
				// If that cost is less than previously computed gCost, update the neighbour's parent to the current node, and 	
				// update gCost, hCost, and fCost values for the neighbour to match the current node
				// Use getHDistance to get the cost from the current node to the current neighour
				int gCost = currentNode->gCost + AStar::getHDistance(currentNode, *it);
				if (gCost < (*it)->gCost || (*it)->gCost == 0) {
					(*it)->parent = currentNode;
					(*it)->gCost = gCost;
					(*it)->hCost = AStar::getHDistance(*it, endNode);
					(*it)->fCost = AStar::getFCost(*it);
					openSet.push_back(*it);
				}
				openSet.unique();
			}
 		}
 		if(currentNode == endNode)
 			return retracePath(startNode, endNode);
	}
	list<Node*> empty;
	return empty;
}
