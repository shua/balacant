default:
	g++ -Wall -O2 -lsfml-graphics -lsfml-window -lsfml-system -o canabalt.bin ./*.cpp

debug:
	g++ -Wall -g -lsfml-graphics -lsfml-window -lsfml-system -o canabalt.bin ./*.cpp
