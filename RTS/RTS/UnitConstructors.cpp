#include "UnitObject.h"


void UnitObject::SoldierConstructor(int nodeX,int nodeY){
	spriteIcon.loadFromFile("spritesheet.png", sf::IntRect(32, 0, 32, 32));
	icon.setTexture(spriteIcon);
	scaleX = 1;
	scaleY = 1;
	icon.setScale(scaleX, scaleY);
	currentNode = engine->Nodes[nodeY][nodeX];
	currentNode->travelCost += 999;
	icon.setPosition(currentNode->x, currentNode->y);
	posX = icon.getPosition().x;
	posY = icon.getPosition().y;
	health = 10;
	speed = 64;
	armour = 0;
}