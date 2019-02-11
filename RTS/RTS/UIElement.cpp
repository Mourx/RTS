#include "UIElement.h"

UIElement::UIElement(int UIElementID, GameEngine* Engine) :GameObject() {
	engine = Engine;
	if (UIElementID == 2) {
		spriteIcon.loadFromFile("spritesheet.png", sf::IntRect(96, 0, 32, 32));
		icon.setTexture(spriteIcon);
		icon.setScale(800.0 / 32, 200.0 / 32);
		icon.setPosition(0, WINDOW_HEIGHT-200);
	}
}

UIElement::UIElement() : GameObject() {

}
void UIElement::update(sf::Time time) {

}