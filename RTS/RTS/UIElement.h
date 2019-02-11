#pragma once

#include "GameObject.h"

class UIElement : public GameObject {
public:
	UIElement(int UIElementID, GameEngine *Engine);
	GameEngine* engine;
	UIElement();
	void update(sf::Time time);
};

class UIProducer : public UIElement {
public:
	UIProducer(int UnitTypeID, GameEngine *Engine);
	void onLeftClick();
	void update(sf::Time time);
};