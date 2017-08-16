#include <fstream>
#include <iostream>
#include <sstream>

#include "a_star.hpp"

using namespace std;

void printWorld(Node* world[Y_LENGTH][X_LENGTH], Node* start, Node* end)
{
	for (int i = 0; i < Y_LENGTH ; i++) {
		for (int k = 0; k < X_LENGTH ; k++) {
			cout << world[i][k]->walkable << " ";
		}
		cout << endl;
	}
	cout << "Start Node: " << "(" << start -> posX << "," << start -> posY << ")" << endl;
	cout << "End Node: " << "(" << end -> posX << "," << end -> posY << ")" << endl;
}

void generateMapFromFile(string fileName, Node* grid[Y_LENGTH][X_LENGTH], Node **startNode, Node **endNode) {
	ifstream file;
	file.open(fileName.c_str());
	if(!file.is_open()) {
		cout << "ERROR ACCESSING FILE";
		exit(1);
	}
	int startPosX, startPosY, endPosX, endPosY;
	file >> startPosX >> startPosY;
	file >> endPosX >> endPosY;
	// iterate over and generate a node Map	
	for(int i = 0; i < Y_LENGTH; i++) {
		for(int j = 0; j < X_LENGTH; j++) {
			
			int numAtSpot;
			file >> numAtSpot;
			Node* block = new Node(j, i, numAtSpot != 0);
			grid[i][j] = block;
		}
	}
	//point the memory locations of start and end nodes to the right places
	*startNode = grid[startPosY][startPosX];
	*endNode = grid[endPosY][endPosX];
	file.close();
}

void deleteMap(Node* grid[Y_LENGTH][X_LENGTH]) {
	for(int i = 0; i < Y_LENGTH; i++) {
		for(int j = 0; j < X_LENGTH; j++) {
			delete grid[i][j];
		}
	}
}

int main() {
	const int NUM_TEST_CASES = 6;
	const int SOLUTION[6] = {92, 48, 66, 66, 0, 0};
	
	Node* world[Y_LENGTH][X_LENGTH];
	Node* start = 0;
	Node* end = 0;
	list<Node*> path;
	int pathDistance;
	
	stringstream os;
	int numCorrect = 0;
	
	for(int i = 0; i < NUM_TEST_CASES; i++) {
		os << "tests/test_" << i+1 << ".txt";
		string fileName = os.str();		
		cout << "Test " << i+1 <<": " << endl;
		
		//set up world
		generateMapFromFile(fileName, world, &start, &end);
		printWorld(world, start, end);
		
		//get solution
		path = AStar::findPath(world, start, end);
		cout << "Shortest path: " << endl;
		cout << AStar::getPathString(path);
		pathDistance = AStar::getPathDistance(path);
		cout << "Distance: " << pathDistance <<endl;
		
		//verify solution
		if (pathDistance == SOLUTION[i]) {
			cout <<"PASSED" << endl;
			numCorrect++;
		} else {
			cout <<"FAILED" << endl;
		}
		cout << "--------------------------------" << endl;
		os.str("");
		os.clear();
		deleteMap(world);
	}
	
	cout << "Passed " << numCorrect << "/" << NUM_TEST_CASES << " tests!";
    return 0;
}


