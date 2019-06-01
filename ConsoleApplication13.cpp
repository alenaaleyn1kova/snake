#include "stdafx.h"
# include <iostream>

# include <windows.h>

# include <time.h>

# include <conio.h> // ����������, ����� ��� ������������� ������� kbhit() � getch()

using namespace std;

char main_color[] = "color ##"; // ������ ��� �����

int size; // ������ ������

int X, Y; // � ����� ������� �������� ������

int coordinates_x[1000], coordinates_y[1000]; // �������, �������� ���������� ������ ���� ������

int food_x = -1, food_y = -1; // ���������� ���

char symbol; // ������ ASCII ��� ������� �������

char �[1000][1000]; // �������, � ������� ���������� ��� ����

const int N = 15; // ������ �������

const int M = 20; // ������ �������

const int TIME = 100; // ����� �� ������� ������ ������������ �� ���� ������

void change_color()

// ������� ��������� ����� �������

{

	char x = rand() % 16, y = rand() % 16;

	if (x == y)

		++y;

	y %= 16;

	if (x > 9)

		x += 'A' - 10;

	else

		x += '0';

	if (y > 9)

		y += 'A' - 10;

	else

		y += '0';

	// �������� ��������� �����

	main_color[6] = x;

	main_color[7] = y;

	system(main_color);

	// ������ ����

}

void change_direction()

// �������, ����������� ������� �������

{

	symbol = _getch();

	switch (symbol)

	{

	case 119: if (X != 1 || Y != 0) { X = -1; Y = 0; } break;

	case 97: if (X != 0 || Y != 1) { X = 0; Y = -1; } break;

	case 115: if (X != -1 || Y != 0) { X = 1; Y = 0; } break;

	case 100: if (X != 0 || Y != -1) { X = 0; Y = 1; } break;

	case 32: change_color(); break;

	default: break;

	}

}

void show_table()

// ������� ��� ������ �������

{

	system("cls");

	// ������� �������

	for (int i = 0; i <= N + 1; ++i)

		for (int j = 0; j <= M + 1; ++j)

			cout << (i == 0 || j == 0 || i == N + 1 || j == M + 1 ? '#' : �[i][j]) << (j <= M ? "" : "\n");

	// ����� �������

}

void clear_snake_on_table()

// ������� ����������, � ������� ������������� ������

{

	for (int i = 1; i <= size; ++i)

		�[coordinates_x[i]][coordinates_y[i]] = ' ';

}

void show_snake_on_table()

// ���������� ���������� ������

{

	if (X == 1 && Y == 0) �[coordinates_x[1]][coordinates_y[1]] = 'v';

	if (X == -1 && Y == 0) �[coordinates_x[1]][coordinates_y[1]] = '^';

	if (X == 0 && Y == 1) �[coordinates_x[1]][coordinates_y[1]] = '>';

	if (X == 0 && Y == -1) �[coordinates_x[1]][coordinates_y[1]] = '<';

	// �������� ��� ������

	for (int i = 2; i <= size; ++i)

		�[coordinates_x[i]][coordinates_y[i]] = '8';

	// ������ ������

}

bool game_over()

// ���������, ����� �� ������ ���� ����

{

	for (int i = 2; i <= size; ++i)

		if (coordinates_x[1] == coordinates_x[i] && coordinates_y[1] == coordinates_y[i]) return true;

	// ���� ���������� ������ ������ ����� ���������� �����-���� ����� ���� ������, �� ������ ����� ���� ����

	return false;

}

void check_coordinates()

// ���������, �� ����� �� ������ �� ����, ���� �� �� ���������� �� �������

{

	if (coordinates_x[1] > N) coordinates_x[1] = 1;

	if (coordinates_x[1] < 1) coordinates_x[1] = N;

	if (coordinates_y[1] > M) coordinates_y[1] = 1;

	if (coordinates_y[1] < 1) coordinates_y[1] = M;

}

void next_step()

// ������� ����������� ������

{

	clear_snake_on_table();

	// ������ ������� �� ������

	for (int i = size; i >= 2; --i)

	{

		coordinates_x[i] = coordinates_x[i - 1];

		coordinates_y[i] = coordinates_y[i - 1];

	}

	// ����������� ���� ������

	coordinates_x[1] += X;

	coordinates_y[1] += Y;

	// ����������� ������ ������

	check_coordinates();

	// ��������� � ������� �� ����������

	if (coordinates_x[1] == food_x && coordinates_y[1] == food_y)

	{

		size++;

		food_x = -1;

		food_y = -1;

	}

	// ���� ������ ������ ��� �� ��� � ���, �� ����������� ������ ������

	show_snake_on_table();

	// ������ ������

	if (game_over() == true)

		// ���� ���� ������� ����

	{

		cout << "Vi proigrali! \n";

		system("pause");

		exit(0);

	}

}

bool food_check()

// ������� �������� �� ������� ��� �� �����

{

	if (food_x == -1 && food_y == -1) return false;

	// ���� ���������� ��� ������������� �� ���������� true

	return true;

	// � ��������� ������� false

}

void place_food()

// ������� ���������� ��� �� �����

{

	srand(time(NULL));

	for (int i = 1; i <= 9; ++i)

	{

		int x = rand(), y = rand();

		if (x < 0) x *= -1;

		if (y < 0) y *= -1;

		x %= (N + 1);

		y %= (M + 1);

		if (x == 0) ++x;

		if (y == 0) ++y;

		if (�[x][y] != '8' && �[x][y] != 'v' && �[x][y] != '^' && �[x][y] != '<' && �[x][y] != '>')

		{

			food_x = x;

			food_y = y;

			�[x][y] = '+';

			return;

		}

	}

	// ������ � ��������� ����� ���

}

void standart_settings()

// ��������� ���������

{

	size = 1;

	coordinates_x[1] = 5;

	coordinates_y[1] = 5;

	X = 0;

	Y = 1;

	// ������ �������� ������

}

int main()

{

	standart_settings();

	// ������ ����������� ���������

	while (1)

		// ����������� ����

	{

		if (_kbhit() == true)

			// ���� ������ �������

			change_direction();

		// ������������ ������� �������

		next_step();

		// ������� ������

		if (food_check() == false)

			place_food();

		// ���� ��� ���, �� ������ ��

		show_table();

		// ������ ������

		Sleep(TIME);

		// "��������" ��������� �� �������� ��������

	}

}
