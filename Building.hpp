#ifndef BUILDING_HPP_INCLUDED
#define BUILDING_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Building {
public:
	Building();
	Building(sf::Vector2f center, float spd, bool hallt);
	Building(float x, float y, float spd, bool hallt);
	~Building();

	sf::Sprite& GetDraw();
	float GetDist();
	float GetSpeed();
	bool update(sf::Vector2f center);
	bool hall;
	bool Running;

private:
	int distance;
	int speed;
	sf::Image mImage;
	sf::Sprite mSprite;
};
#endif
