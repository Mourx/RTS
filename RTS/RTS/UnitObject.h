#pragma once

#include "GameObject.h"
#include "GameEngine.h"
#include "Path.h"

class UnitObject : public GameObject {
public:
	UnitObject(int UnitTypeID, GameEngine* Engine, int nodeX, int nodeY);
	int getValue(int whichValue);
	void onRightClick(int x, int y, sf::Time time);
	void update(sf::Time time);
	void move(sf::Time time);
	void makePath(int x,int y,sf::Time time);
	void animate();
	int GetNodePath();
	void SoldierConstructor(int nodeX, int nodeY);
protected:
	int sprite = 1;
	int animateTime = 0;
	int health, armour;
	bool bMoving = false;
	int speed;
	Node* currentNode;
	Node* targetNode;
	Path path;
	int targetX = 0, targetY = 0;
	bool bIsAtDest = true;
	float remainingDistX = 0;
	float remainingDistY = 0;
	int dirX = 0, dirY = 0;
	int startTime = 0;
};