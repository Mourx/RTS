#include "UIElement.h"
#include "UnitObject.h"

UIProducer::UIProducer(int UnitTypeID, GameEngine *Engine) :UIElement(UnitTypeID, Engine) {
	if (UnitTypeID == 1) {

		spriteIcon.loadFromFile("spritesheet.png", sf::IntRect(32, 0, 32, 32));
		icon.setTexture(spriteIcon);
		icon.setScale(32 / 16, 32 / 16);
		icon.setPosition(ABILITY_ONE_POSX, ABILITY_ONE_POSY);
	}
}


void UIProducer::onLeftClick() {
	UnitObject* Soldier = new UnitObject(1, engine, 6, 4);
	engine->playerList[0]->allUnits.push_back(Soldier);
}

void UIProducer::update(sf::Time time) {

}