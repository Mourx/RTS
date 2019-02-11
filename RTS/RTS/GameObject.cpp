#include "GameObject.h"
#include "UIElement.h"

GameObject::GameObject(int UnitTypeID, GameEngine* Engine, Player* PlayerID) {
	engine = Engine;
	

}

GameObject::GameObject() {

}


void GameObject::setPosition(double x, double y) {
	posX = x;
	posY = y;
	icon.setPosition(x,y);
	if (healthBars.size() > 0) {
		healthBars[0]->setPosition(x, y - 10);
		healthBars[1]->setPosition(x, y - 10);
	}
}
void GameObject::setPosX(double x) {
	posX = x;
}
void GameObject::setPosY(double y) {
	posY = y;
}

void GameObject::onRightClick(int x, int y, sf::Time time) {

}

void GameObject::onLeftClick() {

}

void GameObject::update(sf::Time time) {

}

void GameObject::animate() {

}

void GameObject::move(int x, int y) {
	posX = posX + x;
	posY = posY + y;
	icon.setPosition(posX, posY);
}