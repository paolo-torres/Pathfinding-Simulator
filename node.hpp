#ifndef NODE_H
#define NODE_H

#include <iostream>

struct Node { 
		// operator to check if 2 nodes are the same with the same coordinates
		friend bool operator==(const Node& lhs, const Node& rhs) {
			return lhs.posX == rhs.posX && lhs.posY == rhs.posY;
		}

		friend bool operator!=(const Node& lhs, const Node& rhs) {
			return !(lhs.posX == rhs.posX && lhs.posY == rhs.posY);
		}

		bool walkable; // indicates if a cell is walkable
		int posX;	// cell's x coordinate
		int posY; 	// cell's y coordinate
		int gCost;
		int hCost;
		int fCost;
		Node* parent; // linking for retracing the path
		
		Node(int _posX, int _posY, bool _walkable) {
			walkable = _walkable;
			posX = _posX;
			posY = _posY;
			gCost = 0;
			hCost = 0;
			fCost = 0;
			parent = NULL;
		}
};

#endif
