#include "BuildingObject.h"

BuildingObject::BuildingObject(int UnitTypeID, GameEngine* Engine, int nodeX, int nodeY){
	engine = Engine;
	if (UnitTypeID == 0) {
		spriteIcon.loadFromFile("spritesheet.png", sf::IntRect(0, 0, 32, 32));
		icon.setTexture(spriteIcon);
		scaleX = 2; 
		scaleY = 2;
		icon.setScale(scaleX, scaleY);
		currentNode = engine->Nodes[nodeY][nodeX];
		icon.setPosition(currentNode->x, currentNode->y);
		posX = icon.getPosition().x;
		posY = icon.getPosition().y;
		engine->Nodes[nodeY][nodeX]->travelCost = 999;
		engine->Nodes[nodeY+1][nodeX]->travelCost = 999;
		engine->Nodes[nodeY][nodeX+1]->travelCost = 999;
		engine->Nodes[nodeY+1][nodeX+1]->travelCost = 999;
		health = 10;
		speed = 0;
		armour = 0;
		UIProducer* spawnSoldier = new UIProducer(1, engine);
		abilityIcons.push_back(spawnSoldier);
	}
	for (int i = 0; i < 4; i++) {
		UIElement* bar = new UIElement(-1, engine);
		healthBars.push_back(bar);
		healthBars[i]->icon.setPosition(posX, posY - 10);
	}
	healthBars[MINI_HEALTH_RED]->spriteIcon.loadFromFile("spritesheet.png", sf::IntRect(32, 32, 32, 32));
	healthBars[MINI_HEALTH_RED]->icon.setTexture(healthBars[0]->spriteIcon);
	healthBars[MINI_HEALTH_RED]->icon.setScale(scaleX, 0.25);
	healthBars[MINI_HEALTH_RED]->icon.setPosition(posX, posY - 10);

	healthBars[MINI_HEALTH_GREEN]->spriteIcon.loadFromFile("spritesheet.png", sf::IntRect(0, 32, 32, 32));
	healthBars[MINI_HEALTH_GREEN]->icon.setTexture(healthBars[1]->spriteIcon);
	healthBars[MINI_HEALTH_GREEN]->icon.setScale(scaleX, 0.25);
	healthBars[MINI_HEALTH_GREEN]->icon.setPosition(posX, posY - 10);

	healthBars[LARGE_HEALTH_RED]->spriteIcon.loadFromFile("spritesheet.png", sf::IntRect(32, 32, 32, 32));
	healthBars[LARGE_HEALTH_RED]->icon.setTexture(healthBars[2]->spriteIcon);
	healthBars[LARGE_HEALTH_RED]->icon.setScale(8, 32 / 32);
	healthBars[LARGE_HEALTH_RED]->icon.setPosition(200, 700);

	healthBars[LARGE_HEALTH_GREEN]->spriteIcon.loadFromFile("spritesheet.png", sf::IntRect(0, 32, 32, 32));
	healthBars[LARGE_HEALTH_GREEN]->icon.setTexture(healthBars[3]->spriteIcon);
	healthBars[LARGE_HEALTH_GREEN]->icon.setScale(8, 32 / 32);
	healthBars[LARGE_HEALTH_GREEN]->icon.setPosition(200, 700);

}

int BuildingObject::getValue(int whichValue) {
	switch (whichValue) {
	case 0:
		return health;
	case 1:
		return speed;
	case 2:
		return armour;
	}
}

void BuildingObject::update(sf::Time time) {

}

void BuildingObject::onLeftClick() {
	
}