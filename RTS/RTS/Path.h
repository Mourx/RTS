#pragma once

#include "Node.h"

class Path {
public:
	Path();
	Path(Node* start);
	std::vector<Node*> route;
	float totalCost;
	float remainingCost;
	float fCost;
};
