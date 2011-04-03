#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED

#include <SFML/Graphics.hpp>

#include <iostream>
#include <sstream>
#include "Player.hpp"
#include "Building.hpp"

using namespace std;

class Game {
public:
	Game();
	Game(int width, int height, const string windowName);
	~Game();

	void Run();
	void Init();
	void Destroy();
	int Collide(sf::Sprite& spr1, sf::Sprite& spr2);
	void AllBldngs(bool run);
	void AllBldngs();
	string Convert(string mess, float num);
private:
	sf::RenderWindow mRenderWin;
	sf::Image Icon;
	sf::Clock mClock;
	sf::Font mFont;

	sf::Vector2f center;
	Player* players[2];
	bool playervar[2];
	Building* buildings[5];
	Building* buildingt[5];
	bool Paused;
};

#endif
