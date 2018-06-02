#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <vector>

bool game_over{};
const int width{ 20 }, height{ 20 };
int x{  }, y{  }, fruit_x{  }, fruit_y{  }, score{  };
int tail_x[100], tail_y[100];
int size;

enum Directions { STOP = 0,	LEFT, RIGHT, UP, DOWN };
Directions dir;

void Setup()
{
	game_over = false;
	dir = STOP;
	x = width / 2 - 1;
	y = height / 2 - 1;
	fruit_x = rand() % width;
	fruit_y = rand() % height;
	score = 0;
}

void Draw()
{
	system("cls"); // system("clear");

	for (int i = 0; i < width + 1; i++)
		std::cout << "8";

	std::cout << std::endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0 || j == width - 1)
				std::cout << "8";
			if (i == y && j == x)
				std::cout << "0";
			else if (i == fruit_y && j == fruit_x)
				std::cout << "#";
			else
			{
				bool print = false;

				for (int k = 0; k < size; k++)
				{
					if (tail_x[k] == j && tail_y[k] == i)
					{
						print = true;
						std::cout << "O";
					}
				}
				if (!print)
					std::cout << " ";
			}	
		}
		std::cout << std::endl;
	}
	
	for (int i = 0; i < width + 1; i++)
		std::cout << "8";

	std::cout << std::endl;
	std::cout << "Score: " << score << std::endl;
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT; break;
		case 'd':
			dir = RIGHT; break;
		case 'w':
			dir = UP; break;
		case 's':
			dir = DOWN; break;
		case 'x':
			game_over = true; break;
		default:
			break;
		}
	}
}

void Logic()
{
	int prev_x = tail_x[0];
	int prev_y = tail_y[0];
	int prev_2x, prev_2y;
	tail_x[0] = x;
	tail_y[0] = y;

	for (int i = 1; i < size; i++)
	{
		prev_2x = tail_x[i];
		prev_2y = tail_y[i];

		tail_x[i] = prev_x;
		tail_y[i] = prev_y;

		prev_x = prev_2x;
		prev_y = prev_2y;
	}

	switch (dir)
	{
	case LEFT: x--; break;
	case RIGHT: x++; break;
	case UP: y--; break;
	case DOWN: y++;	break;
	}

	if (x >= width - 1)
		x = 0;
	else if (x < 0)
		x = width - 2;

	if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;

	for (int i = 0; i < size; i++)
	{
		if (tail_x[i] == x && tail_y[i] == y)
			game_over = true;
	}

	if (x == fruit_x && y == fruit_y)
	{
		score++;
		fruit_x = rand() % width;
		fruit_y = rand() % height;
		size++;
	}
}

int main()
{
	Setup();
	while (!game_over)
	{
		Draw();
		Input();
		Logic();
		Sleep(150);
	}

	return 0;
}
