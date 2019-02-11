#include "Path.h"

Path::Path(Node* start) {
	route.push_back(start);
	totalCost = 0;
	remainingCost = 0;
	fCost = 0;
}

Path::Path() {

}