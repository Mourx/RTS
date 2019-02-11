#pragma once
#include <iostream>
#include <vector>

class Node {
public:
	Node();
	Node* Adjacent[4]; // Up, Right, Down, Left
	int travelCost;
	int totalTravelCost;
	float x, y;
	Node* nextNode;
};
