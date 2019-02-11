#include "GameEngine.h"


Player::Player() {};

GameEngine::GameEngine() {
	for (int i = 0; i < GRID_ROWS; i++) {
		std::vector<Node*> vector;
		for (int j = 0; j < GRID_COLUMNS; j++) {
			vector.push_back(new Node());
		}
		Nodes.push_back(vector);
	}
	ConvertToNodes(grid, Nodes);
	for (int k = 0; k < 4; k++) {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				//printf("%d,%d\t", Nodes[i][j]->x, Nodes[i][j]->y);
			}
			//printf("\n");
		}
		//printf("\n \n");
	}
	playerList.push_back(new Player());
	playerList[0]->selectionRect.setOutlineColor(sf::Color::Yellow);
	playerList[0]->selectionRect.setFillColor(sf::Color::Transparent);
	playerList[0]->selectionRect.setOutlineThickness(5);
}

void GameEngine::ConvertToNodes(int grid[26][25], std::vector<std::vector<Node*>> nodes) {
	for (int i = 0; i < GRID_ROWS; i++) {
		for (int j = 0; j < GRID_COLUMNS; j++) {
			nodes[i][j]->travelCost = grid[i][j];
			nodes[i][j]->x = j * 32;
			nodes[i][j]->y = i * 32;
			if (i > 0) AssignAdjacent(DIRECTION_UP, nodes[i][j], nodes[i - 1][j]); else nodes[i][j]->Adjacent[DIRECTION_UP] = new Node(); // Up
			if (j < GRID_COLUMNS - 1) AssignAdjacent(DIRECTION_RIGHT, nodes[i][j], nodes[i][j + 1]); else nodes[i][j]->Adjacent[DIRECTION_RIGHT] = new Node(); // Right
			if (i < GRID_ROWS - 1) AssignAdjacent(DIRECTION_DOWN, nodes[i][j], nodes[i + 1][j]); else nodes[i][j]->Adjacent[DIRECTION_DOWN] = new Node(); // Down
			if (j > 0) AssignAdjacent(DIRECTION_LEFT, nodes[i][j], nodes[i][j - 1]); else nodes[i][j]->Adjacent[DIRECTION_LEFT] = new Node(); // Left
		}
	}
}

void GameEngine::AssignAdjacent(int Direction, Node* node, Node* next) {
	if (next != nullptr) {
		node->Adjacent[Direction] = next;
	}
	else {
		node->Adjacent[Direction] = nullptr;
	}
}
Node* GameEngine::FindNode(int x, int y) {
	return Nodes[y / 32][x / 32];
}