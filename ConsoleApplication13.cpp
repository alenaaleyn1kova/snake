#include "stdafx.h"
# include <iostream>

# include <windows.h>

# include <time.h>

# include <conio.h> // библиотека, нужна для использования функций kbhit() и getch()

using namespace std;

char main_color[] = "color ##"; // шаблон для цвета

int size; // размер змейки

int X, Y; // в какую сторону движется змейка

int coordinates_x[1000], coordinates_y[1000]; // массивы, хранящие координаты частей тела змейки

int food_x = -1, food_y = -1; // координаты еды

char symbol; // хранит ASCII код нажатой клавиши

char А[1000][1000]; // таблица, в которой происходит вся игра

const int N = 15; // высота таблицы

const int M = 20; // ширина таблицы

const int TIME = 100; // время за которое змейка перемещается на одну клетку

void change_color()

// функция изменения цвета консоли

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

	// выбираем рандомные цвета

	main_color[6] = x;

	main_color[7] = y;

	system(main_color);

	// меняем цвет

}

void change_direction()

// функция, считывающая нажатую клавишу

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

// функция для вывода таблицы

{

	system("cls");

	// очистка консоли

	for (int i = 0; i <= N + 1; ++i)

		for (int j = 0; j <= M + 1; ++j)

			cout << (i == 0 || j == 0 || i == N + 1 || j == M + 1 ? '#' : А[i][j]) << (j <= M ? "" : "\n");

	// вывод таблицы

}

void clear_snake_on_table()

// очищаем координаты, в которых располагалась змейка

{

	for (int i = 1; i <= size; ++i)

		А[coordinates_x[i]][coordinates_y[i]] = ' ';

}

void show_snake_on_table()

// обозначаем координаты змейки

{

	if (X == 1 && Y == 0) А[coordinates_x[1]][coordinates_y[1]] = 'v';

	if (X == -1 && Y == 0) А[coordinates_x[1]][coordinates_y[1]] = '^';

	if (X == 0 && Y == 1) А[coordinates_x[1]][coordinates_y[1]] = '>';

	if (X == 0 && Y == -1) А[coordinates_x[1]][coordinates_y[1]] = '<';

	// изменяем тип головы

	for (int i = 2; i <= size; ++i)

		А[coordinates_x[i]][coordinates_y[i]] = '8';

	// красим змейку

}

bool game_over()

// проверяем, съела ли змейка саму себя

{

	for (int i = 2; i <= size; ++i)

		if (coordinates_x[1] == coordinates_x[i] && coordinates_y[1] == coordinates_y[i]) return true;

	// если координаты головы змейки равны координате какой-либо части тела змейки, то змейка съела саму себя

	return false;

}

void check_coordinates()

// проверяем, не вышла ли змейка за поле, если да то возвращаем ее обратно

{

	if (coordinates_x[1] > N) coordinates_x[1] = 1;

	if (coordinates_x[1] < 1) coordinates_x[1] = N;

	if (coordinates_y[1] > M) coordinates_y[1] = 1;

	if (coordinates_y[1] < 1) coordinates_y[1] = M;

}

void next_step()

// функция перемещения змейки

{

	clear_snake_on_table();

	// чистим таблицу от змейки

	for (int i = size; i >= 2; --i)

	{

		coordinates_x[i] = coordinates_x[i - 1];

		coordinates_y[i] = coordinates_y[i - 1];

	}

	// передвигаем тело змейки

	coordinates_x[1] += X;

	coordinates_y[1] += Y;

	// передвигаем голову змейки

	check_coordinates();

	// проверяем в порядке ли координаты

	if (coordinates_x[1] == food_x && coordinates_y[1] == food_y)

	{

		size++;

		food_x = -1;

		food_y = -1;

	}

	// если голова змейки там же где и еда, то увеличиваем размер змейки

	show_snake_on_table();

	// рисуем змейку

	if (game_over() == true)

		// если змея укусила себя

	{

		cout << "Vi proigrali! \n";

		system("pause");

		exit(0);

	}

}

bool food_check()

// функция проверки на наличие еды на карте

{

	if (food_x == -1 && food_y == -1) return false;

	// если координаты еды неопределенны то возвращаем true

	return true;

	// в остальных случаях false

}

void place_food()

// функция добавления еды на карту

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

		if (А[x][y] != '8' && А[x][y] != 'v' && А[x][y] != '^' && А[x][y] != '<' && А[x][y] != '>')

		{

			food_x = x;

			food_y = y;

			А[x][y] = '+';

			return;

		}

	}

	// ставим в рандомное место еду

}

void standart_settings()

// начальные установки

{

	size = 1;

	coordinates_x[1] = 5;

	coordinates_y[1] = 5;

	X = 0;

	Y = 1;

	// змейка движется вправо

}

int main()

{

	standart_settings();

	// задаем стандартные настройки

	while (1)

		// бесконечный цикл

	{

		if (_kbhit() == true)

			// если нажата клавиша

			change_direction();

		// обрабатываем нажатую клавишу

		next_step();

		// двигаем змейку

		if (food_check() == false)

			place_food();

		// если нет еды, то ставим ее

		show_table();

		// рисуем змейку

		Sleep(TIME);

		// "усыпляем" программу на заданный интервал

	}

}
