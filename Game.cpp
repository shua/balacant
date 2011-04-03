#include "Game.hpp"

Game::Game() { cerr << "Something's wrong with startup" << endl; }

Game::Game(int width, int height, const string windowName) {
	mRenderWin.Create(sf::VideoMode(width, height, 32), windowName);
	// set icon {
	Icon.LoadFromFile("gfx/Icon.bmp");
	mRenderWin.SetIcon(16,16,Icon.GetPixelsPtr());
	// } now font {
	mFont.LoadFromFile("canela_roman.otf");
	mRenderWin.ShowMouseCursor(false);
	mRenderWin.SetCursorPosition(width/2, height/2);
	center.x = mRenderWin.GetWidth() / 2;
	center.y = mRenderWin.GetHeight() / 2;
	Paused = false;
	Init();
}

Game::~Game() {
	Destroy();
}

void Game::Init() {
        players[0] = new Player(center);
        playervar[0] = true;
// Starting buildings
        buildings[0] = new Building(center.x - 640, center.y, 0, 0);
        buildings[1] = new Building(center.x - 340, center.y, 0, 0);
        buildings[2] = new Building(center.x, center.y, 0, 0);
        buildings[3] = new Building(center.x + 340, center.y + 5, 0, 0);
        buildings[4] = new Building(center.x + 680, center.y + 10, 0, 0);
}

void Game::Destroy() {
        for (int i = 0; i != 1; i++) {
        delete players[i];
        }
        for (int i = 0; i != 5; i++) {
        if (buildings[i]->hall)
                delete buildingt[i];
        delete buildings[i];
        }
}

void Game::Run() {
float dt = 1.f/60.f;
float elapsed = 0.f;
float distance = 0.f;
string deathmess = "You died at : ";
bool drawn = false;
AllBldngs(true);

while (mRenderWin.IsOpened())
{
	sf::Event Event;
	if (Paused) {
		while (mRenderWin.GetEvent(Event)) {
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::P)) {
				cout << "Unpaused" << endl;
				Paused = false;
			} else
				cout << "Still paused" << endl;
			if ((Event.Type == sf::Event::Closed) || ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape))) {
				mRenderWin.Close();
			}
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::R)) {
				Destroy();
				elapsed = 0.f;
				Init();
			}
		}
	mClock.Reset();
	} else {
		while (mRenderWin.GetEvent(Event)) {
			if ((Event.Type == sf::Event::Closed) || ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Escape)))
				mRenderWin.Close();
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::P))
				Paused = true;
                        if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::R)) {
                                Destroy();
				elapsed = 0.f;
                                Init();
                        } 
			if ((Event.Type == sf::Event::KeyPressed) && (Event.Key.Code == sf::Key::Space) && (playervar[0])) {
				players[0]->Jumping = true;
				playervar[0] = false;
			}
		}
		elapsed += mClock.GetElapsedTime();
		mClock.Reset();
		while (elapsed >= dt) {
// draw buildings is seperate because there could be multiple players, and we wouldn't want to re-draw buildings for each player in the above loop.
			for (int i = 0; i != 5; i++) {
				bool crossed = buildings[i]->update(center);
				if (buildings[i]->hall) {
					buildingt[i]->update(center);
				}
				if ((crossed) && (i == 3)) {
					AllBldngs();
					i--;
				}
			}
			distance += buildings[2]->GetDist();
// check collisions for each player and building
	                for (int i = 0; i != 1; i++) {
	                        for (int j = 0; j != 5; j++) {
	                                int collide = Collide(players[i]->GetDraw(), buildings[j]->GetDraw());
					int collidet = 0;
                                        if (buildings[j]->hall)
                                                collidet = Collide(players[i]->GetDraw(), buildingt[j]->GetDraw());
                                        if (collidet == 1) {
                                                players[i]->Jumping = false;
                                                players[i]->Falling = true;
                                                j = 4;
                                        } else if (collidet == 3) {
                                                cout << "hall collide" << endl;
						AllBldngs(false);
                                                j = 4;
                                        } else if (collide == 1) {
	                                        players[i]->Jumping = false;
	                                        players[i]->Falling = true;
						j = 4;
	                                } else if (collide == 2) {
	                                        players[i]->Falling = false;
	                                        playervar[i] = true;
						j = 4;
	                                } else if (collide == 3) {
						AllBldngs(false);
						j = 4;
	                                } else {
						players[i]->Falling = true;
	                                }
	                        }
				if (players[i]->update(center)) {
					AllBldngs(false);
				}
	                }
			elapsed -= dt;
			drawn = false;
		}
		if (drawn)
			sf::Sleep(0.01);
		else {
			mRenderWin.Clear(sf::Color(10,10,10));
			for (int i = 0; i != 1; i++)
				mRenderWin.Draw(players[i]->GetDraw());
			for (int i = 0; i != 5; i++) {
				mRenderWin.Draw(buildings[i]->GetDraw());
				if (buildings[i]->hall) {
					mRenderWin.Draw(buildingt[i]->GetDraw());
				}
			}
			if (players[0]->dead) {
				sf::String Text(Convert(deathmess, distance), mFont, 50);
				Text.SetPosition(center);
				mRenderWin.Draw(Text);
			}
			mRenderWin.Display();
			drawn = true;
		}
	}
	center.x = mRenderWin.GetWidth() / 2;
	center.y = mRenderWin.GetHeight() / 2;
}
}

// 1 = top, 2 = bottom, 3 = right (no left collisions as player doesn't move backwards)
int Game::Collide(sf::Sprite& spr1, sf::Sprite& spr2) {
	int collisions = 0;
	int left1, right1, top1, bottom1;
	int left2, right2, top2, bottom2;
	
	left1 = spr1.GetPosition().x;
	right1 = spr1.GetPosition().x + spr1.GetSize().x;
	top1 = spr1.GetPosition().y;
	bottom1 = spr1.GetPosition().y + spr1.GetSize().y;
	left2 = spr2.GetPosition().x;
	right2 = spr2.GetPosition().x + spr2.GetSize().x;
	top2 = spr2.GetPosition().y;
	bottom2 = spr2.GetPosition().y + spr2.GetSize().y;

	if (((left1 <= right2) && (right1 >= left2)) && (((bottom1 <=  top2 + 1) && (top1 <= top2)) || ((top1 >= bottom2 - 1) && (bottom1 >= bottom2)))) {
		if (bottom1 == top2) {
			collisions = 2;
		} else if ((bottom1 == top2 + 1) && (top1 < top2)) {
// If that's true, it means the sprite is stuck in the wall, and this pushes them out just the right amount.
			spr1.Move(0,top2 - bottom1);
			collisions = 2;
		}
		if (top1 == bottom2) {
			collisions = 1;
		} else if ((top1 < bottom2) && (bottom1 >= bottom2)) {
// same here as before
			spr1.Move(0,bottom2 - top1);
			collisions = 1;
		}
	} else if ((right1 >= left2) && (left1 < left2)) {
// we don't really care if the sprite is stuck a little bit in the wall, because if you hit a wall's side, game over.
		spr1.Move(left2 - (right1 + 1), 0);
		collisions = 3;
	} else {
		collisions = 0;
	}
	return collisions;
}

void Game::AllBldngs(bool run) {
	for (int i = 0; i != 5; i++) {
		buildings[i]->Running = run;
		if (buildings[i]->hall)
			buildingt[i]->Running = run;
	}
}

void Game::AllBldngs() {
	if (buildings[0]->hall) {
		delete buildingt[0];
	}
	delete buildings[0];
	for (int i = 1; i != 5; i++) {
		if (buildings[i]->hall) {
			buildingt[i-1] = buildingt[i];
			buildingt[i] = 0;
		}
		buildings[i-1] = buildings[i];
	}
	if (sf::Randomizer::Random(1,6) == 6) {
		buildings[4] = new Building(buildings[3]->GetDraw().GetPosition(), buildings[0]->GetSpeed(), 1);
		buildingt[4] = new Building(buildings[4]->GetDraw().GetPosition().x, buildings[4]->GetDraw().GetPosition().y - 340, buildings[0]->GetSpeed(), 1);
	} else {
		buildings[4] = new Building(buildings[3]->GetDraw().GetPosition(), buildings[0]->GetSpeed(), 0);
	}
}

string Game::Convert(string mess, float num) {
        ostringstream buff;
        buff << mess << num / 1000 << "ft";
        return buff.str();
}

