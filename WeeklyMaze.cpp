#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <random>
#include <conio.h>

using namespace std;

struct character {
	int pos_x;
	int pos_y;
	int hp;
	int sightDistance;
	char symbol;
public:
	void randPos(int maxX, int maxY, string maze[]) {
		bool done = false;
		random_device rd;
		mt19937 mt(rd());
		uniform_real_distribution<double> x(1, maxX);
		uniform_real_distribution<double> y(1, maxY);
		while (done == false) {
			pos_x = floor(x(mt));
			pos_y = floor(y(mt));
			//cout << pos_x << " " << pos_y << endl;
			if (maze[pos_y][pos_x] == '#') {
				done = false;
			}
			else {
				done = true;
			}
		}
	};
};

struct troll {
	int pos_x;
	int pos_y;
	int hp;
	char symbol;
public:
	void randPos(int maxX, int maxY, string maze[]) {
		bool done = false;
		random_device rd;
		mt19937 mt(rd());
		uniform_real_distribution<double> x(1, maxX);
		uniform_real_distribution<double> y(1, maxY);
		while (done == false) {
			pos_x = floor(x(mt));
			pos_y = floor(y(mt));
			//cout << pos_x << " " << pos_y << endl;
			if (maze[pos_y][pos_x] == '#') {
				done = false;
			}
			else {
				done = true;
			}
		}
	};
};

void drawMap(int pos_x, int pos_y, int width, int height, int sight, string maze[]) {
	system("CLS");
	for (int y = 0; y < height; y++) {
		cout << endl;
		for (int x = 0; x < width; x++) {
			if (sqrt(pow(pos_x - x, 2) + pow(pos_y - y, 2)) < sight) {
				cout << maze[y][x];
			}
			else {
				cout << ' ';
			}
		}
	}
};

void gameWin() {
	system("CLS");
	cout << "YOU WIN!!!" << endl;
}
void gameOver() {
	system("CLS");
	cout << "YOU LOSE!!!" << endl;
}

int main()
{
	const char reset_key = 'q';
	const char wall_symbol = '#';
	const char end_symbol = 'X';
	const char hero_symbol = 'v';
	const char troll_symbol = 'T';
	const char width = 37, height = 23;
	char next_spot;
	char key_pressed = ' ';
	bool update = true;
	character hero;
	troll troll;

	string maze_string[height] = {
		"#####################################", //1
		"# #       #       #     #         # #", //2
		"# # ##### # ### ##### ### ### ### # #", //3
		"#       #   # #     #     # # #   # #", //4
		"##### # ##### ##### ### # # # ##### #", //5
		"#   # #       #     # # # # #     # #", //6
		"# # ####### # # ##### ### # ##### # #", //7
		"# #       # # #   #     #     #   # #", //8
		"# ####### ### ### # ### ##### # ### #", //9
		"#     #   # #   # #   #     # #     #", //10
		"# ### ### # ### # ##### # # # #######", //11 
		"#   #   # # #   #   #   # # #   #   #", //12
		"####### # # # ##### # ### # ### ### #", //13
		"#     # #     #   # #   # #   #     #", //14
		"# ### # ##### ### # ### ### ####### #", //15
		"# #   #     #     #   # # #       # #", //16
		"# # ##### # ### ##### # # ####### # #", //17
		"# #     # # # # #     #       # #   #", //18
		"# ##### # # # ### ##### ##### # #####", //19
		"# #   # # #     #     # #   #       #", //20
		"# # ### ### ### ##### ### # ##### # #", //21
		"# #         #     #       #       # #", //22
		"#X###################################"  //23
		};

		hero.symbol = hero_symbol;
		hero.sightDistance = 10;
		hero.randPos(width, height, maze_string);

		troll.symbol = troll_symbol;
		troll.randPos(width, height, maze_string);
		

	while (key_pressed != reset_key) {
		if (update == true) {
			//update hero position
			maze_string[hero.pos_y][hero.pos_x] = hero.symbol;
			//update troll position
			maze_string[troll.pos_y][troll.pos_x] = troll.symbol;
			//draw map
			drawMap(hero.pos_x, hero.pos_y, width, height, hero.sightDistance, maze_string);
		}
		//get current key input
		key_pressed = _getch();

		//decide on what to do
		switch (key_pressed) {
			case 'w':
				next_spot = maze_string[hero.pos_y - 1][hero.pos_x];
				switch (next_spot) {
					case wall_symbol:
						update = false;
						break;
					case troll_symbol:
						gameOver();
						return 0;
						break;
					case end_symbol:
						gameWin();  
						return 0;
						break;
					default:
						maze_string[hero.pos_y][hero.pos_x] = ' ';
						hero.pos_y--;
						hero.symbol = '^';
						update = true;
				}
				break;
			case 's':
				next_spot = maze_string[hero.pos_y + 1][hero.pos_x];
				switch (next_spot) {
					case wall_symbol:
						update = false;
						break;
					case troll_symbol:
						gameOver();
						return 0;
						break;
					case end_symbol:
						gameWin();
						return 0;
						break;
					default:
						maze_string[hero.pos_y][hero.pos_x] = ' ';
						hero.pos_y++;
						hero.symbol = 'v';
						update = true;
				}
				break;
			case 'a':
				next_spot = maze_string[hero.pos_y][hero.pos_x - 1];
				switch (next_spot) {
					case wall_symbol:
						update = false;
						break;
					case troll_symbol:
						gameOver();
						return 0;
						break;
					case end_symbol:
						gameWin();
						return 0;
						break;
					default:
						maze_string[hero.pos_y][hero.pos_x] = ' ';
						hero.pos_x--;
						hero.symbol = '<';
						update = true;
				}
				break;
			case 'd':
				next_spot = maze_string[hero.pos_y][hero.pos_x + 1];
				switch (next_spot) {
					case wall_symbol:
						update = false;
						break;
					case troll_symbol:
						gameOver();
						return 0;
						break;
					case end_symbol:
						gameWin();
						return 0;
						break;
					default:
						maze_string[hero.pos_y][hero.pos_x] = ' ';
						hero.pos_x++;
						hero.symbol = '>';
						update = true;
				}
				break;
			default:
				update = false;
				break;
		}
	}
    return 0;
}
