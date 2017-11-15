#include "stdafx.h"
#include <iostream>
#include <sstream>
using namespace std;
char win;
int k_quit;
int ex;

void show_cells(char *cells) {
	cout << "   1   2   3   4   5" << endl;
	cout << " +---+---+---+---+---+" << endl;
	cout << "a| " << cells[0] << " | " << cells[1] << " | " << cells[2] << " | " << cells[3] << " | " << cells[4] << " |"  << endl;
	cout << " +---+---+---+---+---+" << endl;
	cout << "b| " << cells[5] << " | " << cells[6] << " | " << cells[7] << " | " << cells[8] << " | " << cells[9] << " |"  << endl;
	cout << " +---+---+---+---+---+" << endl;
	cout << "c| " << cells[10] << " | " << cells[11] << " | " << cells[12] << " | " << cells[13] << " | " << cells[14] << " |" << endl;
	cout << " +---+---+---+---+---+" << endl;
	cout << "d| " << cells[15] << " | " << cells[16] << " | " << cells[17] << " | " << cells[18] << " | " << cells[19] << " |" << endl;
	cout << " +---+---+---+---+---+" << endl;
	cout << "e| " << cells[20] << " | " << cells[21] << " | " << cells[22] << " | " << cells[23] << " | " << cells[24] << " |" << endl;
	cout << " +---+---+---+---+---+" << endl;
}

void show_available_moves(char op, char *cells) {

	int k = 0;
	for (int i = 0; i < 25; i++) {
		if (!(cells[i] == 'X' || cells[i] == 'O')) {
			if (i < 5) {
				cout << ++k << ". mark cell a" << i + 1 << " as " << op << endl;
			}
			if (i > 4 && i < 10) {
				cout << ++k << ". mark cell b" << i - 4 << " as " << op << endl;
			}
			if (i > 9 && i < 15) {
				cout << ++k << ". mark cell c" << i - 9 << " as " << op << endl;
			}
			if (i > 14 && i < 20) {
				cout << ++k << ". mark cell d" << i - 14 << " as " << op << endl;
			}
			if (i > 19 && i < 25) {
				cout << ++k << ". mark cell e" << i - 19 << " as " << op << endl;
			}
		}
	}
	cout << ++k << ". quit" << endl;
	k_quit = k;
}

int make_move(int move, char op, char *cells) {
	int cell;
	string string;
	getline(cin, string);
	istringstream stream(string);
	stream >> cell;
	while (cell < 1 || cell >(27 - move)) {
		cout << endl << "You can not use this move. Enter another move" << endl;
		getline(cin, string);
		istringstream stream(string);
		stream >> cell;
	}
	int k = 0;
	for (int i = 0; i < 25; i++) {
		if (cells[i] == ' ') {
			k++;
		}
		if (k == cell) {
			cells[i] = op;
			show_cells(cells);
			return 0;
		}
	}
	if (cell == k_quit) {
		cout << "GAME OVER" << endl;
		ex = k_quit;
		return -1;
	}
	return 0;
}

char check(char *cells) {
	for (int i = 0; i < 5; i++) {

		if ((cells[i] == cells[i + 1] && cells[i + 1] == cells[i + 2] && cells[i + 2] == cells[i + 3] && cells[i +3] == cells[i + 4]) && cells[i] != ' ') {

			return cells[i]; //проверка строк
		}
		if ((cells[i] == cells[i + 5] && cells[i + 5] == cells[i + 10] && cells[i + 10] == cells[i + 15] && cells[i + 15] == cells[i + 20]) && cells[i] != ' ') {

			return cells[i]; // проверка столбцов
		}
		if ((cells[0] == cells[6] && cells[6] == cells[12] && cells[12] == cells[18] && cells[18] == cells[24]) && cells[i] != ' ') {

			return cells[i]; // проверка главной диагонали
		}
		if ((cells[4] == cells[8] && cells[8] == cells[12] && cells[12] == cells[16] && cells[16] == cells[20]) && cells[i] != ' ') {

			return cells[i]; // проверка побочной диагонали
		}
	}

	return ' ';

}

int main() {
	char cells[25] = { ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ' };
	char op;
	show_cells(cells);
	for (int move = 1; move <= 25; move++) {
		if (move % 2) {
			op = 'X';
			show_available_moves(op, cells);
			make_move(move, op, cells);
		}
		else {
			op = 'O';
			show_available_moves(op, cells);
			make_move(move, op, cells);
		}
		if (k_quit == ex) {
			return -1;
		}
		if (move >= 5) {
			check(cells);
			char  win = check(cells);
			if (win == 'X') {
				cout << "X win" << endl;
				return -1;
			}
			if (win == 'O') {
				cout << "O win" << endl;
				return -1;
			}
			if (move == 25 && win != 'X' && win != 'O') {
				cout << "Draw!" << endl;
				return -1;
			}
		}
	}
	if (k_quit == ex) {
		return -1;
	}
	return 0;
}
