#pragma once

#include "GameObject.h"
#include "UIElement.h"
#include "GameEngine.h"

class BuildingObject : public GameObject {
public:
	BuildingObject(int UnitTypeID, GameEngine* Engine, int nodeX, int nodeY);
	int getValue(int whichValue);
	void update(sf::Time time);
	void onLeftClick();
protected:
	int health, speed, armour;
	Node* currentNode;
};