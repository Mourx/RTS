#pragma once

#include "Node.h"
#include "MacroValues.h"
#include <SFML/Graphics.hpp>

extern class GameObject;
extern class UnitObject;
extern class BuildingObject;
extern class UIElement;

class Player {
public:
	Player();
	std::vector<GameObject*> selectedUnits;
	std::vector<GameObject*> allUnits;
	std::vector<UIElement*> UIElements;
	bool bMouseHeld = false;
	sf::RectangleShape selectionRect = sf::RectangleShape(sf::Vector2f(0, 0));
};

class GameEngine {
public:
	GameEngine();
	std::vector<std::vector<Node*>> Nodes;
	std::vector<UnitObject*> selectedUnits;
	std::vector<Player*> playerList;
	void ConvertToNodes(int grid[26][25], std::vector<std::vector<Node*>> nodes);
	void AssignAdjacent(int Direction, Node* node, Node* next);
	Node* FindNode(int x, int y);
};

