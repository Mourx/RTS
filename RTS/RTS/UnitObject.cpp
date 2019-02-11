#include "UnitObject.h"
#include "UIElement.h"

UnitObject::UnitObject(int UnitTypeID, GameEngine* Engine, int nodeX, int nodeY):GameObject(){
	engine = Engine;
	if (UnitTypeID == 1) {
		SoldierConstructor(nodeX, nodeY);
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

void UnitObject::animate() {
	if (sprite == 1) {
		spriteIcon.loadFromFile("spritesheet.png", sf::IntRect(64, 0, 32, 32));
		icon.setTexture(spriteIcon);
		sprite = 2;
	}
	else {
		spriteIcon.loadFromFile("spritesheet.png", sf::IntRect(32, 0, 32, 32));
		icon.setTexture(spriteIcon);
		sprite = 1;
	}
	
}

int UnitObject::getValue(int whichValue) {
	switch (whichValue) {
	case VALUE_HEALTH:
		return health;
	case VALUE_SPEED:
		return speed;
	case VALUE_ARMOUR:
		return armour;
	default:
		return -9999999;
	}
}

void UnitObject::makePath(int x, int y, sf::Time time) {
	targetNode = engine->FindNode(x, y);
	currentNode = engine->FindNode(posX, posY);
	if (targetNode != currentNode) {
		GetNodePath();
		targetX = path.route[0]->x;
		targetY = path.route[0]->y;
		remainingDistX = targetX - posX;
		remainingDistY = targetY - posY;
		dirX = (remainingDistX <= 0) ? -1 : 1;
		dirY = (remainingDistY <= 0) ? -1 : 1;
		for (int i = 0; i < path.route.size(); i++) {
			printf("NodeX = %i, NodeY = %i \n", (int)path.route[i]->x, (int)path.route[i]->y);
		}
		bIsAtDest = false;
		startTime = time.asMicroseconds();
		bMoving = true;
		
	}


}

void UnitObject::onRightClick(int x,int y, sf::Time time) {
	
	makePath(x, y, time);
	printf("clicky");
}


void UnitObject::move(sf::Time time) {
	double diffTime = time.asMicroseconds() - startTime;
	int MICROSECOND_QUOTIENT = 1000000;
	currentNode->travelCost -= 999;

	setPosition(posX + ((std::abs(remainingDistX) >= std::abs(speed * diffTime/ MICROSECOND_QUOTIENT)) ? dirX * (speed *  diffTime/ MICROSECOND_QUOTIENT) : remainingDistX),
		posY + ((std::abs(remainingDistY) >= std::abs(speed * diffTime/ MICROSECOND_QUOTIENT)) ? dirY * (speed *   diffTime/ MICROSECOND_QUOTIENT) : remainingDistY));
	currentNode = engine->FindNode(posX, posY);


	if (remainingDistX == 0 && remainingDistY == 0) {
		
		if (path.route.size() > 0) {
			path.route.erase(path.route.begin());
		}

		if (path.route.size() > 0) {
			if (path.route[0]->travelCost <= 200) {
				targetX = path.route[0]->x;
				targetY = path.route[0]->y;
			}
			else {
				path.route.erase(path.route.begin());
			}
		}
		else {
			bMoving = false;
			bIsAtDest = true;
		}
	}
	remainingDistX = targetX - posX;
	remainingDistY = targetY - posY;
	dirX = (remainingDistX <= 0) ? -1 : 1;
	dirY = (remainingDistY <= 0) ? -1 : 1;
	startTime = time.asMicroseconds();
	currentNode->travelCost += 999;


}

void UnitObject::update(sf::Time time) {
	if (bMoving) {
		if (path.route[0] == currentNode || path.route[0]->travelCost <= 200) {
			move(time);
			if (path.route.size() > 0) {
				makePath(path.route[path.route.size() - 1]->x, path.route[path.route.size() - 1]->y, time);
			}
		}
		
		else {
			targetNode = currentNode;
			makePath(currentNode->x, currentNode->y, time);
			bMoving = false;
			bIsAtDest = true;
		}
		
		if (time.asMilliseconds() - animateTime >= 200) {
			animate();
			animateTime = time.asMilliseconds();
		}
	}
}

float getDistance(int x, int y, int targX, int targY) {
	return sqrt(pow((targX - x), 2) + pow((targY - y), 2));
}

float getDistance(Node* start, Node* target) {
	return sqrt(pow((target->x - start->x), 2) + pow((target->y - start->y), 2));
}

std::vector<Path> insertPath(std::vector<Path> pathList, Path newPath) {
	int k = 0;
	while (k < pathList.size() && newPath.fCost >= pathList[k].fCost) {
		k++;
	}
	if (k < pathList.size()) {
		pathList.insert(pathList.begin() + k, newPath);
	}
	else {
		pathList.push_back(newPath);
	}
	return pathList;
}

int UnitObject::GetNodePath() {


	// A*(ish) search
	// Explored nodes
	std::vector<Node*> closedSet;
	// Remaining Nodes
	std::vector<Path> openSet;

	openSet.push_back(*new Path(currentNode));

	int totalCost = 999999;

	float targX = targetNode->x;
	float targY = targetNode->y;


	float remainingDistance = 0;
	/* check if neighbour is target node
	if not, go through adjacent nodes and add each path to queue

	*/
	openSet[0].fCost = 9999999;
	Path current;
	Path newPath;
	for (int i = 0; i < 4; i++) {
		if (targetNode->x == currentNode->Adjacent[i]->x && targetNode->y == currentNode->Adjacent[i]->y && targetNode->travelCost <= 200) {
			Path easyPath = *new Path(currentNode);
			easyPath.route.push_back(currentNode->Adjacent[i]);
			easyPath.route.erase(easyPath.route.begin());

			path = easyPath;
			return 0;
		}
	}

	int storeCost = targetNode->travelCost;
	targetNode->travelCost = 1;
	while (openSet.size() > 0) {
		if (openSet[0].route[openSet[0].route.size() - 1] == targetNode) {
			targetNode->travelCost = storeCost;
			openSet[0].route[(openSet[0].route.size() - 1)]->travelCost = storeCost;
			targetNode->travelCost = storeCost;
			openSet[0].route.erase(openSet[0].route.begin());
			path = openSet[0];
			return 0;
		}
		current = openSet[0];
		openSet.erase(openSet.begin());
		if ((std::find(closedSet.begin(), closedSet.end(), current.route[current.route.size() - 1]) == closedSet.end())) {
			closedSet.push_back(current.route[current.route.size() - 1]);
		}
		for (int i = 0; i < 4; i++) {
			if ((std::find(closedSet.begin(), closedSet.end(), current.route[current.route.size() - 1]->Adjacent[i])) != closedSet.end()) {
				printf("Hello");
			}
			else {
				newPath = current;
				newPath.route.push_back(newPath.route[newPath.route.size() - 1]->Adjacent[i]);
				newPath.totalCost += newPath.route[newPath.route.size() - 1]->travelCost;
				newPath.remainingCost = getDistance(newPath.route[newPath.route.size() - 1], targetNode);
				newPath.fCost = newPath.remainingCost + newPath.totalCost;
				openSet = insertPath(openSet, newPath);
			}
		}
		
	}
}