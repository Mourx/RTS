#pragma once

#include <SFML/Graphics.hpp>
#include "MacroValues.h"
#include <vector>

extern class GameEngine;
extern class Player;
extern class UIElement;

class GameObject {
public:
	GameObject(int UnitTypeID, GameEngine* Engine, Player* PlayerID);
	GameObject();
	void setPosition(double x, double y);
	void setPosX(double x);
	void setPosY(double y);
	sf::Sprite icon;
	sf::Texture spriteIcon;
	virtual void onRightClick(int x, int y, sf::Time time);
	virtual void onLeftClick();
	virtual void update(sf::Time time);
	virtual void move(int x, int y);
	virtual void animate();
	Player* player;
	std::vector<UIElement*> healthBars; //0 red mini, 1 green mini, 2 red large, 3 green large
	std::vector<UIElement*> abilityIcons;
protected:
	GameEngine * engine;
	double posX, posY;
	int nodeX, nodeY;
	float scaleX, scaleY;
	double sizeX, sizeY;
};