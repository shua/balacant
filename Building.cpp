#include "Building.hpp"

Building::Building() { cerr << "you need to include coordinates" << endl; };

Building::Building(sf::Vector2f center, float spd, bool hallt) {
	if (hallt) {
		hall = true;
		mImage.LoadFromFile("gfx/Hall.png");
	} else {
		hall = false;
		mImage.LoadFromFile("gfx/Building.png");
	}
	speed = spd;
	Running = true;
	mSprite.SetImage(mImage);
	mSprite.SetPosition(0,0);
	mSprite.Move(center.x + 320 + sf::Randomizer::Random(0,70), center.y + sf::Randomizer::Random(-20,20));
}

Building::Building(float x, float y, float spd, bool hallt) {
	if (hallt) {
		hall = true;
		mImage.LoadFromFile("gfx/Hall.png");
	} else {
		hall = false;
		mImage.LoadFromFile("gfx/Building.png");
	}
	speed = spd;
	Running = true;
	mSprite.SetImage(mImage);
	mSprite.SetPosition(0,0);
	mSprite.Move(x,y);
}

Building::~Building() {
};

bool Building::update(sf::Vector2f center) {
	if (Running) {
		if (speed == 400) {
			mSprite.Move(speed/-50, 0);
		} else {
			mSprite.Move(speed/-50, 0);
			speed ++;
		}
		distance = speed;
	} else {
		distance = 0;
	}
	if (mSprite.GetPosition().x <= center.x)
		return 1;
	else
		return 0;
}

sf::Sprite& Building::GetDraw() {
	return mSprite;
}

float Building::GetDist() {
	return distance;
}

float Building::GetSpeed() {
	return speed;
}
