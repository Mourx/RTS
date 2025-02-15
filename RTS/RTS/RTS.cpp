// RTS.cpp : Defines the entry point for the console application.
//

#include <vector>
#include <SFML/Graphics.hpp>
#include "GameEngine.h"
#include "GameObject.h"
#include "BuildingObject.h"
#include "UnitObject.h"

#include <cstdio>
#include <iostream>



sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "SFML works!");
sf::View camera = window.getDefaultView();
GameEngine* Engine = new GameEngine();
UIElement* Background = new UIElement(2, Engine);


void onLeftClick(sf::Vector2f positionf) {
	bool bNothing = true;
	bool bUIClicked = false;
	for (int i = 0; i < Engine->playerList[0]->selectedUnits.size(); i++) {
		if (Engine->playerList[0]->selectedUnits[i]->abilityIcons.size() >= 1) {
			for (int j = 0; j < Engine->playerList[0]->selectedUnits[i]->abilityIcons.size(); j++) {
				if (Engine->playerList[0]->selectedUnits[i]->abilityIcons[j]->icon.getGlobalBounds().contains(positionf)) {
					bUIClicked = true;
					Engine->playerList[0]->selectedUnits[i]->abilityIcons[j]->onLeftClick();
				}
			}
		}
	}
	if (!bUIClicked) {
		Engine->playerList[0]->selectedUnits.clear();
		for (int i = 0; i < Engine->playerList[0]->allUnits.size(); i++) {
			if (Engine->playerList[0]->selectionRect.getGlobalBounds().contains(Engine->playerList[0]->allUnits[i]->icon.getPosition()) || Engine->playerList[0]->allUnits[i]->icon.getGlobalBounds().contains(positionf)) {
				bNothing = false;
				bool bIsSelected = false;
				for (int j = 0; j < Engine->playerList[0]->selectedUnits.size(); j++) {
					if (Engine->playerList[0]->selectedUnits[j] == Engine->playerList[0]->allUnits[i]) {
						bIsSelected = true;
						break;
					}
				}
				if (!bIsSelected) {
					Engine->playerList[0]->selectedUnits.push_back(Engine->playerList[0]->allUnits[i]);
				}
				//printf("%d\n", Engine->playerList[0]->selectedUnits.size());
			}
		}

		if (bNothing == true) {
			Engine->playerList[0]->selectedUnits.clear();
			//printf("%d\n", Engine->playerList[0]->selectedUnits.size());

		}
	}
}

void checkMouse(sf::Time time) {
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2f positionf = window.mapPixelToCoords(sf::Mouse::getPosition(window), camera);
		Engine->playerList[0]->bMouseHeld = true;
		Engine->playerList[0]->selectionRect.setPosition(positionf);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		sf::Vector2f positionf = window.mapPixelToCoords(sf::Mouse::getPosition(window), camera);
		for (int j = 0; j < Engine->playerList[0]->selectedUnits.size(); j++) {
			Engine->playerList[0]->selectedUnits[j]->onRightClick(positionf.x,positionf.y,time);
		}
	}
}

void checkKeyboard() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		camera.move(0, -1);
		Background->setPosition(camera.getCenter().x - camera.getSize().x/2 + 0, camera.getCenter().y - camera.getSize().y/2 + WINDOW_HEIGHT-200 );
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		camera.move(0, 1);
		Background->setPosition(camera.getCenter().x - camera.getSize().x/2 + 0, camera.getCenter().y - camera.getSize().y/2 + WINDOW_HEIGHT - 200);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		camera.move(-1, 0);
		Background->setPosition(camera.getCenter().x - camera.getSize().x/2 + 0, camera.getCenter().y - camera.getSize().y/2 + WINDOW_HEIGHT - 200);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		camera.move(1, 0);
		Background->setPosition(camera.getCenter().x - camera.getSize().x/2 + 0, camera.getCenter().y - camera.getSize().y/2 + WINDOW_HEIGHT - 200);
	}
}

void update(sf::Time currentTime) {
	
	for (int i = 0; i < Engine->playerList[0]->allUnits.size(); i++) {
		Engine->playerList[0]->allUnits[i]->update(currentTime);
	}
}

int main()
{

	
	sf::Clock clock;
	BuildingObject* House1 = new BuildingObject(0, Engine, 4, 4);
	BuildingObject* House2 = new BuildingObject(0, Engine, 10, 4);
	BuildingObject* House3 = new BuildingObject(0, Engine, 10, 6);
	BuildingObject* House4 = new BuildingObject(0, Engine, 10, 8);
	BuildingObject* House5 = new BuildingObject(0, Engine, 10, 10);
	BuildingObject* House6 = new BuildingObject(0, Engine, 10, 12);
	UnitObject* Soldier = new UnitObject(1, Engine, 6, 4);
	
	Engine->playerList[0]->allUnits.push_back(Soldier);
	Engine->playerList[0]->allUnits.push_back(House1);
	Engine->playerList[0]->allUnits.push_back(House2);
	Engine->playerList[0]->allUnits.push_back(House3);
	Engine->playerList[0]->allUnits.push_back(House4);
	Engine->playerList[0]->allUnits.push_back(House5);
	Engine->playerList[0]->allUnits.push_back(House6);
	//std::cout << House1->getValue(VALUE_HEALTH) << ", " << House1->getValue(VALUE_SPEED) << ", " << House1->getValue(VALUE_ARMOUR) << std::endl;
	camera = window.getDefaultView();
	camera.zoom(1);
	camera.setCenter(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	sf::Time currentTime = clock.getElapsedTime();

	while (window.isOpen())
	{
		currentTime = clock.getElapsedTime();
		update(currentTime);
		window.setView(camera);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				checkKeyboard();
			}
			if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Button::Left) {
					Engine->playerList[0]->bMouseHeld = false;
					onLeftClick(window.mapPixelToCoords(sf::Mouse::getPosition(window), camera));

				}
			}
			if (event.type == sf::Event::MouseButtonPressed) {
				checkMouse(currentTime);
			}
		}
		sf::Vector2f positionf = window.mapPixelToCoords(sf::Mouse::getPosition(window), camera);
		Engine->playerList[0]->selectionRect.setSize(sf::Vector2f(positionf.x - Engine->playerList[0]->selectionRect.getPosition().x ,
																positionf.y - Engine->playerList[0]->selectionRect.getPosition().y));
		window.clear(sf::Color::Blue);
		for (int i = 0; i < Engine->playerList[0]->allUnits.size(); i++) {
			window.draw(Engine->playerList[0]->allUnits[i]->icon);
		}
		if (Engine->playerList[0]->bMouseHeld) {
			window.draw(Engine->playerList[0]->selectionRect);
		}
		window.draw(Background->icon);
		for (int i = 0; i < Engine->playerList[0]->selectedUnits.size(); i++) {
			if (Engine->playerList[0]->selectedUnits[i]->abilityIcons.size() >= 1) {
				for (int j = 0; j < Engine->playerList[0]->selectedUnits[i]->abilityIcons.size(); j++) {
					
					window.draw(Engine->playerList[0]->selectedUnits[i]->abilityIcons[j]->icon);
				}
			}
			for (int k = 0; k < 4; k++) {
				window.draw(Engine->playerList[0]->selectedUnits[i]->healthBars[k]->icon);
			}
		}
		

		window.display();
	}

	return 0;
}