#include "Node.h"

Node::Node() {
	travelCost = 9999999;
}


//void doConversion() {
//	std::vector<std::vector<Node*>> Nodes;
//	for (int i = 0; i < 10; i++) {
//		std::vector<Node*> vector;
//		for (int j = 0; j < 10; j++) {
//			vector.push_back(new Node());
//		}
//		Nodes.push_back(vector);
//	}
//	ConvertToNodes(grid, Nodes);
//	for (int k = 0; k < 4; k++) {
//		for (int i = 0; i < 10; i++) {
//			for (int j = 0; j < 10; j++) {
//				printf("%d,%d\t", Nodes[i][j]->x, Nodes[i][j]->y);
//			}
//			printf("\n");
//		}
//		printf("\n \n");
//	}
//}