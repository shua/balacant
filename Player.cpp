#include "Player.hpp"

Player::Player() { cerr << "Player needs a center" << endl; }

Player::Player(sf::Vector2f center) {
	dead = false;
	Jumping = false;
	Falling = true;
	JHeight = 0;
	mImage.LoadFromFile("gfx/Player.png");
	mImage.SetSmooth(false);
	mSprite.SetImage(mImage);
	mSprite.SetPosition(0,0);
	mSprite.Move(center.x, 0);
}

Player::~Player() {};

sf::Sprite& Player::GetDraw() {
	return mSprite;
}

bool Player::update(sf::Vector2f center) {
	if (Jumping) {
		mSprite.Move(0,-2);
		JHeight += 1;
		if (JHeight >= 15)
			Jumping = false;
	} else if (Falling) {
		mSprite.Move(0, 2);
	} else {
	JHeight = 0;
	}
	if (mSprite.GetPosition().y > center.y + 150) {
		Falling = false;
		dead = true;
		return 1;
	} else {
		return 0;
	}
}
