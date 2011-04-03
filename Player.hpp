#ifndef PLAYER_HPP_INCLUDED
#define PLAYER_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class Player {
public:
	Player();
	Player(sf::Vector2f center);
	~Player();

	sf::Sprite& GetDraw();
	bool update(sf::Vector2f center);
	bool Jumping;
	bool Falling;
	bool dead;
private:
	sf::Sprite mSprite;
	sf::Image mImage;
	int JHeight;
};

#endif
