#include "stdafx.h"
#include <string>
#include <iostream>
#include <cmath>
#include <random>
#include <conio.h>
#include <windows.h>
using namespace std;

const char reset_key = 'q';
const char wall_symbol = '#';
const char end_symbol = 'X';
const char hero_symbol_up = '^';
const char hero_symbol_down = 'v';
const char hero_symbol_left = '<';
const char hero_symbol_right = '>';
const char troll_symbol = 'T';
const int width = 37, height = 23;

string maze = {
	"#####################################" //1
	"# #       #       #     #         # #" //2
	"# # ##### # ### ##### ### ### ### # #" //3
	"#       #   # #     #     # # #   # #" //4
	"##### # ##### ##### ### # # # ##### #" //5
	"#   # #       #     # # # # #     # #" //6
	"# # ####### # # ##### ### # ##### # #" //7
	"# #       # # #   #     #     #   # #" //8
	"# ####### ### ### # ### ##### # ### #" //9
	"#     #   # #   # #   #     # #     #" //10
	"# ### ### # ### # ##### # # # #######" //11 
	"#   #   # # #   #   #   # # #   #   #" //12
	"####### # # # ##### # ### # ### ### #" //13
	"#     # #     #   # #   # #   #     #" //14
	"# ### # ##### ### # ### ### ####### #" //15
	"# #   #     #     #   # # #       # #" //16
	"# # ##### # ### ##### # # ####### # #" //17
	"# #     # # # # #     #       # #   #" //18
	"# ##### # # # ### ##### ##### # #####" //19
	"# #   # # #     #     # #   #       #" //20
	"# # ### ### ### ##### ### # ##### # #" //21
	"# #         #     #       #       # #" //22
	"#X###################################" //23
};

struct character {
	int pos_x;
	int pos_y;
	int hp;
	int color;
	int sightDistance;
	bool powerup;
	char symbol;
public:
	void randPos(int width, int height, string maze) {
		bool done = false;
		random_device rd;
		mt19937 mt(rd());
		uniform_real_distribution<double> x(1, width);
		uniform_real_distribution<double> y(1, height);
		while (done == false) {
			pos_x = floor(x(mt));
			pos_y = floor(y(mt));
			//cout << pos_x << " " << pos_y << endl;
			if (maze[pos_x + pos_y * width] == wall_symbol) {
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
	int color;
	bool alive;
	char symbol;
public:
	void randPos(int width, int height, string maze) {
		bool done = false;
		random_device rd;
		mt19937 mt(rd());
		uniform_real_distribution<double> x(1, width);
		uniform_real_distribution<double> y(1, height);
		while (done == false) {
			pos_x = floor(x(mt));
			pos_y = floor(y(mt));
			//cout << pos_x << " " << pos_y << endl;
			if (maze[pos_x + pos_y * width] == wall_symbol) {
				done = false;
			}
			else {
				done = true;
			}
		}
	};
};

void drawMap(int pos_x, int pos_y, int width, int height, int sight, string maze) {
	system("CLS");
	int i = 0;
	for (int y = 0; y < height; y++) {
		cout << endl;
		for (int x = 0; x < width; x++) {
			i = x + y * width;
			if (sqrt(pow(pos_x - x, 2) + pow(pos_y - y, 2)) < sight) {
				cout << maze[i];
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

void showCursor(bool showFlag) //hide console cursor
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

int main()
{
	char next_spot;
	char next_spot_wall;
	char key_pressed = ' ';
	bool update = true;
	character hero;
	troll troll;
	
	hero.symbol = hero_symbol_down;
	hero.powerup = true;
	hero.sightDistance = 10;
	
	troll.symbol = troll_symbol;
	troll.alive = true;

	hero.randPos(width, height, maze);
	troll.randPos(width, height, maze);
	
	showCursor(false); //hide console cursor

	while (key_pressed != reset_key) {
		if (update == true) {
			//update hero position
			maze[hero.pos_x + hero.pos_y * width] = hero.symbol;
			//update troll position
			if (troll.alive == true) {
				maze[troll.pos_x + troll.pos_y * width] = troll.symbol;
			}
			//draw map
			drawMap(hero.pos_x, hero.pos_y, width, height, hero.sightDistance, maze);
		}
		//get current key input
		key_pressed = _getch();

		//decide on what to do
		switch (key_pressed) {
			case 'w':
				next_spot = maze[hero.pos_x + (hero.pos_y - 1) * width];
				if (hero.pos_y <= 1) {
					next_spot_wall = wall_symbol;
				}
				else {
					next_spot_wall = maze[hero.pos_x + (hero.pos_y - 2) * width];
				}
				switch (next_spot) {
					case wall_symbol:
						if (next_spot_wall == wall_symbol || next_spot_wall == end_symbol) {
							update = false;
						}
						else if (hero.powerup == true) {
							if (next_spot_wall == troll.symbol) { troll.alive = false; }
							maze[hero.pos_x + (hero.pos_y - 1) * width] = ' ';
							maze[hero.pos_x + (hero.pos_y - 2) * width] = wall_symbol;
							maze[hero.pos_x + hero.pos_y * width] = ' ';
							hero.pos_y--;
							hero.symbol = hero_symbol_up;
							update = true;
						}
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
						maze[hero.pos_x + hero.pos_y * width] = ' ';
						hero.pos_y--;
						hero.symbol = hero_symbol_up;
						update = true;
				}
				break;
			case 's':
				next_spot = maze[hero.pos_x + (hero.pos_y + 1) * width];
				if (hero.pos_y >= height - 2) {
					next_spot_wall = wall_symbol;
				}
				else {
					next_spot_wall = maze[hero.pos_x + (hero.pos_y + 2) * width];
				}
				switch (next_spot) {
					case wall_symbol:
						if (next_spot_wall == wall_symbol || next_spot_wall == end_symbol) {
							update = false;
						}
						else if (hero.powerup == true) {
							if (next_spot_wall == troll.symbol) { troll.alive = false; }
							maze[hero.pos_x + (hero.pos_y + 1) * width] = ' ';
							maze[hero.pos_x + (hero.pos_y + 2) * width] = wall_symbol;
							maze[hero.pos_x + hero.pos_y * width] = ' ';
							hero.pos_y++;
							hero.symbol = hero_symbol_down;
							update = true;
						}
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
						maze[hero.pos_x + hero.pos_y * width] = ' ';
						hero.pos_y++;
						hero.symbol = hero_symbol_down;
						update = true;
				}
				break;
			case 'a':
				next_spot = maze[hero.pos_x - 1 + hero.pos_y * width];
				if (hero.pos_x <= 1) {
					next_spot_wall = wall_symbol;
				}
				else {
					next_spot_wall = maze[hero.pos_x - 2 + hero.pos_y * width];
				}
				switch (next_spot) {
					case wall_symbol:
						if (next_spot_wall == wall_symbol || next_spot_wall == end_symbol) {
							update = false;
						}
						else if (hero.powerup == true) {
							if (next_spot_wall == troll.symbol) { troll.alive = false; }
							maze[hero.pos_x - 1 + hero.pos_y * width] = ' ';
							maze[hero.pos_x - 2 + hero.pos_y * width] = wall_symbol;
							maze[hero.pos_x + hero.pos_y * width] = ' ';
							hero.pos_x--;
							hero.symbol = hero_symbol_left;
							update = true;
						}
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
						maze[hero.pos_x + hero.pos_y * width] = ' ';
						hero.pos_x--;
						hero.symbol = hero_symbol_left;
						update = true;
				}
				break;
			case 'd':
				next_spot = maze[hero.pos_x + 1 + hero.pos_y * width];
				if (hero.pos_x >= width - 2) {
					next_spot_wall = wall_symbol;
				}
				else {
					next_spot_wall = maze[hero.pos_x + 2 + hero.pos_y * width];
				}
				switch (next_spot) {
					case wall_symbol:
						if (next_spot_wall == wall_symbol || next_spot_wall == end_symbol) {
							update = false;
						}
						else if (hero.powerup == true) {
							if (next_spot_wall == troll.symbol) { troll.alive = false; }
							maze[hero.pos_x + 1 + hero.pos_y * width] = ' ';
							maze[hero.pos_x + 2 + hero.pos_y * width] = wall_symbol;
							maze[hero.pos_x + hero.pos_y * width] = ' ';
							hero.pos_x++;
							hero.symbol = hero_symbol_right;
							update = true;
						}
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
						maze[hero.pos_x + hero.pos_y * width] = ' ';
						hero.pos_x++;
						hero.symbol = hero_symbol_right;
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
