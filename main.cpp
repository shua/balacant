#include "Game.hpp"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
    const int width = 800;
    const int height = 300;
    string windowName = "Canabalt";

    Game GameA(width, height, windowName);
    GameA.Run();

    cout << "Goodbye" << endl;
    return 0;
}


