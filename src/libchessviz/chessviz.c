#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "libchessviz/chessviz.h"


//Прототип
//int logikXod (char fig, char xod, int x0, int y0, int x1, int y1, char m[][9], char mp[], char mP[], char rRkK[]);


void printPole (char m[][9]) {
	int i, j;
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			printf(" %c", m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}
int checksafetytraj(char m[][9], char mp[], char mP[], char f, int y0, int x0) {
	char mf[6] = {'r', 'n', 'b', 'q', 'p', 'k'}, bf[6] = {'R', 'N', 'B', 'Q', 'P', 'K'}, nf[6];
	int i, j;
	if (f == 'k') {
		for (i = 0; i < 6; i++)
			nf[i] = mf[i];
	} else {
		for (i = 0; i < 6; i++)
			nf[i] = bf[i];
	}
		//диагональ + +
		for (i = 1, j = 1; i < 9 - y0 && j < 9 - x0; i++, j++) {
			if (m[y0 + i][x0 + j] == nf[2] || m[y0 + i][x0 + j] == nf[3]) {
				return 0;
			} else if (m[y0 + i][x0 + j] != ' ')
				break;
		}
		//диагональ + -
		for (i = 1, j = -1; i < 9 - y0 && j > -x0; i++, j--) {
			if (m[y0 + i][x0 + j] == nf[2] || m[y0 + i][x0 + j] == nf[3]) {
				return 0;
			} else if (m[y0 + i][x0 + j] != ' ')
				break;
		}
		//диагональ - -
		for (i = -1, j = -1; i > -y0 && j > -x0; i--, j--) {
			if (m[y0 + i][x0 + j] == nf[2] || m[y0 + i][x0 + j] == nf[3]) {
				return 0;
			} else if (m[y0 + i][x0 + j] != ' ')
				break;
		}
		//диагональ - +
		for (i = -1, j = 1; i > -y0 && j < 9 - x0; i--, j++) {
			if (m[y0 + i][x0 + j] == nf[2] || m[y0 + i][x0 + j] == nf[3]) {
				return 0;
			} else if (m[y0 + i][x0 + j] != ' ')
				break;
		}
		//проверка пешек
		if (f = 'k') {
			if (y0 == 4 && m[2][x0] == 'p' && m[3][x0] == ' ')
				return 0;
			if (m[y0 - 1][x0] == 'p')
				return 0;
		} else {
			if (y0 == 5 && m[7][x0] == 'P' && m[6][x0] == ' ')
				return 0;
			if (m[y0 + 1][x0] == 'P')
				return 0;
		}
		//проверка горизонтали и вертикали
		//горизонталь +
		for (i = 1; i < 9 - x0; i++) {
			if (m[y0][x0 + i] == nf[0] || m[y0][x0 + i] == nf[3]) {
				return 0;
			} else if (m[y0][x0 + i] != ' ')
				break;
		}
		//горизонталь -
		for (i = -1; i > -x0; i--) {
			if (m[y0][x0 + i] == nf[0] || m[y0][x0 + i] == nf[3]) {
				return 0;
			} else if (m[y0][x0 + i] != ' ')
				break;
		}
		//вертикаль +
		for (i = 1; i < 9 - y0; i++) {
			if (m[y0 + i][x0] == nf[0] || m[y0 + i][x0] == nf[3]) {
				return 0;
			} else if (m[y0 + i][x0] != ' ')
				break;
		}
		//вертикаль -
		for (i = -1; i > -y0; i--) {
			if (m[y0 + i][x0] == nf[0] || m[y0 + i][x0] == nf[3]) {
				return 0;
			} else if (m[y0 + i][x0] != ' ')
				break;
		}
		//проверка коня
		if (m[y0 + 1][x0 + 2] == nf[1])
			return 0;
		if (m[y0 - 1][x0 + 2] == nf[1])
			return 0;
		if (m[y0 + 1][x0 - 2] == nf[1])
			return 0;
		if (m[y0 - 1][x0 - 2] == nf[1])
			return 0;
		if (m[y0 + 2][x0 + 1] == nf[1])
			return 0;
		if (m[y0 + 2][x0 - 1] == nf[1])
			return 0;
		if (m[y0 - 2][x0 + 1] == nf[1])
			return 0;
		if (m[y0 - 2][x0 - 1] == nf[1])
			return 0;
	return 1;
}
int dangertocell (char m[][9], char mp[], char mP[], char f, int y0, int x0, int *ygry0, int *ygrx0) {
	char mf[6] = {'r', 'n', 'b', 'q', 'p', 'k'}, bf[6] = {'R', 'N', 'B', 'Q', 'P', 'K'}, nf[6];
	int i, j, ygroz = 0;
	if (f == 'k') {
		for (i = 0; i < 6; i++)
			nf[i] = bf[i];
	} else {
		for (i = 0; i < 6; i++)
			nf[i] = mf[i];
	}
		//диагональ + +
		for (i = 1, j = 1; i < 9 - y0 && j < 9 - x0; i++, j++) {
			//printf("(+ +)m[%d + i][%d + j]: '%c'\n", y0, x0, m[y0 + i][x0 + j]);
			if (m[y0 + i][x0 + j] == nf[2] || m[y0 + i][x0 + j] == nf[3]) {
				//printf("диагональ + +\n");
				*ygry0 = y0 + i;
				*ygrx0 = x0 + j;
				ygroz++;
			} else if (m[y0 + i][x0 + j] != ' ')
				break;
		}
		//диагональ + -
		for (i = 1, j = -1; i < 9 - y0 && j > -x0; i++, j--) {
			//printf("(+ -)m[%d + i][%d + j]: '%c'\n", y0, x0, m[y0 + i][x0 + j]);
			if (m[y0 + i][x0 + j] == nf[2] || m[y0 + i][x0 + j] == nf[3]) {
				//printf("диагональ + -\n");
				*ygry0 = y0 + i;
				*ygrx0 = x0 + j;
				ygroz++;
			} else if (m[y0 + i][x0 + j] != ' ')
				break;
		}
		//диагональ - -
		for (i = -1, j = -1; i > -y0 && j > -x0; i--, j--) {
			if (m[y0 + i][x0 + j] == nf[2] || m[y0 + i][x0 + j] == nf[3]) {
				//printf("диагональ - -\n");
				*ygry0 = y0 + i;
				*ygrx0 = x0 + j;
				ygroz++;
			} else if (m[y0 + i][x0 + j] != ' ')
				break;
		}
		//диагональ - +
		for (i = -1, j = 1; i > -y0 && j < 9 - x0; i--, j++) {
			if (m[y0 + i][x0 + j] == nf[2] || m[y0 + i][x0 + j] == nf[3]) {
				//printf("диагональ - +\n");
				*ygry0 = y0 + i;
				*ygrx0 = x0 + j;
				ygroz++;
			} else if (m[y0 + i][x0 + j] != ' ')
				break;
		}
		//Проверка наличия рядом пешек или короля
		if (m[y0 + 1][x0 + 1] == nf[5] || m[y0 + 1][x0 + 1] == nf[4]) {
			*ygry0 = y0 + 1;
			*ygrx0 = x0 + 1;
			ygroz++;
		}
		if (m[y0 + 1][x0 - 1] == nf[5] || m[y0 + 1][x0 - 1] == nf[4]) {
			*ygry0 = y0 + 1;
			*ygrx0 = x0 - 1;
			ygroz++;
		}
		if (m[y0 - 1][x0 - 1] == nf[5] || m[y0 - 1][x0 - 1] == nf[4]) {
			*ygry0 = y0 - 1;
			*ygrx0 = x0 - 1;
			ygroz++;
		}
		if (m[y0 - 1][x0 + 1] == nf[5] || m[y0 - 1][x0 + 1] == nf[4]) {
			*ygry0 = y0 - 1;
			*ygrx0 = x0 + 1;
			ygroz++;
		}
		if (m[y0][x0 + 1] == nf[5]) {
			*ygry0 = y0;
			*ygrx0 = x0 + 1;
			ygroz++;
		}
		if (m[y0][x0 - 1] == nf[5]) {
			*ygry0 = y0;
			*ygrx0 = x0 - 1;
			ygroz++;
		}
		if (m[y0 + 1][x0] == nf[5]) {
			*ygry0 = y0 + 1;
			*ygrx0 = x0;
			ygroz++;
		}
		if (m[y0 - 1][x0] == nf[5]) {
			*ygry0 = y0 - 1;
			*ygrx0 = x0;
			ygroz++;
		}
		//проверка горизонтали и вертикали
		//горизонталь +
		for (i = 1; i < 9 - x0; i++) {
			if (m[y0][x0 + i] == nf[0] || m[y0][x0 + i] == nf[3]) {
				//printf("горизонталь +\n");
				*ygry0 = y0;
				*ygrx0 = x0 + i;
				ygroz++;
			} else if (m[y0][x0 + i] != ' ')
				break;
		}
		//горизонталь -
		for (i = -1; i > -x0; i--) {
			if (m[y0][x0 + i] == nf[0] || m[y0][x0 + i] == nf[3]) {
				//printf("горизонталь -\n");
				*ygry0 = y0;
				*ygrx0 = x0 + i;
				ygroz++;
			} else if (m[y0][x0 + i] != ' ')
				break;
		}
		//вертикаль +
		for (i = 1; i < 9 - y0; i++) {
			if (m[y0 + i][x0] == nf[0] || m[y0 + i][x0] == nf[3]) {
				//printf("вертикаль +\n");
				*ygry0 = y0 + i;
				*ygrx0 = x0;
				ygroz++;
			} else if (m[y0 + i][x0] != ' ')
				break;
		}
		//вертикаль -
		for (i = -1; i > -y0; i--) {
			if (m[y0 + i][x0] == nf[0] || m[y0 + i][x0] == nf[3]) {
				//printf("вертикаль -\n");
				*ygry0 = y0 + i;
				*ygrx0 = x0;
				ygroz++;
			} else if (m[y0 + i][x0] != ' ')
				break;
		}
		//проверка коня
		if (m[y0 + 1][x0 + 2] == nf[1]) {
			*ygry0 = y0 + 1;
			*ygrx0 = x0 + 2;
			ygroz++;
		}
		if (m[y0 - 1][x0 + 2] == nf[1]) {
			*ygry0 = y0 - 1;
			*ygrx0 = x0 + 2;
			ygroz++;
		}
		if (m[y0 + 1][x0 - 2] == nf[1]) {
			*ygry0 = y0 + 1;
			*ygrx0 = x0 - 2;
			ygroz++;
		}
		if (m[y0 - 1][x0 - 2] == nf[1]) {
			*ygry0 = y0 - 1;
			*ygrx0 = x0 - 2;
			ygroz++;
		}
		if (m[y0 + 2][x0 + 1] == nf[1]) {
			*ygry0 = y0 + 2;
			*ygrx0 = x0 + 1;
			ygroz++;
		}
		if (m[y0 + 2][x0 - 1] == nf[1]) {
			*ygry0 = y0 + 2;
			*ygrx0 = x0 - 1;
			ygroz++;
		}
		if (m[y0 - 2][x0 + 1] == nf[1]) {
			*ygry0 = y0 - 2;
			*ygrx0 = x0 + 1;
			ygroz++;
		}
		if (m[y0 - 2][x0 - 1] == nf[1]) {
			*ygry0 = y0 - 2;
			*ygrx0 = x0 - 1;
			ygroz++;
		}
	return ygroz;
}
int mat (char m[][9], char mp[], char mP[], char f) {
	char mf[6] = {'r', 'n', 'b', 'q', 'p', 'k'}, bf[6] = {'R', 'N', 'B', 'Q', 'P', 'K'}, nf[6];
	int i, j, x0, y0, ygry0, ygrx0, pygry0, pygrx0;
	for (i = 1; i < 9; i++)
		for (j = 1; j < 9; j++)
			if (m[i][j] == f) {
				y0 = i;
				x0 = j;
			}
	if (f == 'k') {
		for (i = 0; i < 6; i++)
			nf[i] = bf[i];
	} else {
		for (i = 0; i < 6; i++)
			nf[i] = mf[i];
	}
	if (dangertocell(m, mp, mP, f, y0, x0, &ygry0, &ygrx0) > 0) {
		printf("Начинаются проверки мата\n");
		//массив safety заполняется по часовой стрелке, где нулевой эл. - это 12 часов
		if (y0 - 1 != 0) {
			for (i = 0; i < 6; i++) {
				if (m[y0 - 1][x0] == nf[i]) {
					if (dangertocell(m, mp, mP, f, y0 - 1, x0, &ygry0, &ygrx0) == 0)
						return 0;
				}
			}
			if (m[y0 - 1][x0] == ' ') {
				if (dangertocell(m, mp, mP, f, y0 - 1, x0, &ygry0, &ygrx0) == 0)
						return 0;
			}
		}
		if (x0 + 1 != 9 && y0 - 1 != 0) {
			for (i = 0; i < 6; i++) {
				if (m[y0 - 1][x0 + 1] == nf[i]) {
					if (dangertocell(m, mp, mP, f, y0 - 1, x0 + 1, &ygry0, &ygrx0) == 0)
						return 0;
				}
			}
			if (m[y0 - 1][x0 + 1] == ' ') {
				if (dangertocell(m, mp, mP, f, y0 - 1, x0 + 1, &ygry0, &ygrx0) == 0)
					return 0;
			}
		}
		if (x0 + 1 != 9) {
			for (i = 0; i < 6; i++) {
				if (m[y0][x0 + 1] == nf[i]) {
					if (dangertocell(m, mp, mP, f, y0, x0 + 1, &ygry0, &ygrx0) == 0)
						return 0;
				}
			}
			if (m[y0][x0 + 1] == ' ') {
				if (dangertocell(m, mp, mP, f, y0, x0 + 1, &ygry0, &ygrx0) == 0)
					return 0;
			}
		}
		if (y0 + 1 != 9 && x0 + 1 != 9) {
			for (i = 0; i < 6; i++) {
				if (m[y0 + 1][x0 + 1] == nf[i]) {
					if (dangertocell(m, mp, mP, f, y0 + 1, x0 + 1, &ygry0, &ygrx0) == 0)
						return 0;
				}
			}
			if (m[y0 + 1][x0 + 1] == ' ') {
					if (dangertocell(m, mp, mP, f, y0 + 1, x0 + 1, &ygry0, &ygrx0) == 0)
					return 0;
			}
		}
		if (y0 + 1 != 9) {
			for (i = 0; i < 6; i++) {
				if (m[y0 + 1][x0] == nf[i]) {
					if (dangertocell(m, mp, mP, f, y0 + 1, x0, &ygry0, &ygrx0) == 0)
						return 0;
				}
			}
			if (m[y0 + 1][x0] == ' ') {
				if (dangertocell(m, mp, mP, f, y0 + 1, x0, &ygry0, &ygrx0) == 0)
					return 0;
			}
		}
		if (x0 - 1 != 0 && y0 + 1 != 9) {
			for (i = 0; i < 6; i++) {
				if (m[y0 + 1][x0 - 1] == nf[i]) {
					if (dangertocell(m, mp, mP, f, y0 + 1, x0 - 1, &ygry0, &ygrx0) == 0)
						return 0;
				}
			}
			if (m[y0 + 1][x0 - 1] == ' ') {
				if (dangertocell(m, mp, mP, f, y0 + 1, x0 - 1, &ygry0, &ygrx0) == 0)
					return 0;
			}
		}
		if (x0 - 1 != 0) {
			for (i = 0; i < 6; i++) {
				if (m[y0][x0 - 1] == nf[i]) {
					if (dangertocell(m, mp, mP, f, y0, x0 - 1, &ygry0, &ygrx0) == 0)
						return 0;
				}
			}
			if (m[y0][x0 - 1] == ' ') {
				if (dangertocell(m, mp, mP, f, y0, x0 - 1, &ygry0, &ygrx0) == 0)
					return 0;
			}
		}
		if (x0 - 1 != 0 && y0 - 1 != 0) {
			for (i = 0; i < 6; i++) {
				if (m[y0 - 1][x0 - 1] == nf[i]) {
					if (dangertocell(m, mp, mP, f, y0 - 1, x0 - 1, &ygry0, &ygrx0) == 0)
						return 0;
				}
			}
			if (m[y0 - 1][x0 - 1] == ' ') {
				if (dangertocell(m, mp, mP, f, y0 - 1, x0 - 1, &ygry0, &ygrx0) == 0)
					return 0;
			}
		}
		//работает, только если угр.Ф одна
		if (dangertocell(m, mp, mP, f, y0, x0, &ygry0, &ygrx0) == 1) {
			//можно ли срубить угр.Ф, союзной фигурой
			pygry0 = ygry0;
			pygrx0 = ygrx0;
			if (f == 'k') {
				if (dangertocell(m, mp, mP, 'K', pygry0, pygrx0, &ygry0, &ygrx0) > 0)
					return 0;
			} else {
				if (dangertocell(m, mp, mP, 'k', pygry0, pygrx0, &ygry0, &ygrx0) > 0)
					return 0;
			}
			//можно ли прикрыться от угр.Ф, союзной фигрурой
			//горизонталь, вертикаль
			if (m[pygry0][pygrx0] == nf[0] || m[pygry0][pygrx0] == nf[3]) {
				if (pygry0 == y0) {
					if (pygrx0 < x0) {
						for (i = 1; i < x0 - pygrx0; i++)
							if (checksafetytraj(m, mp, mP, f, y0, pygrx0 + i) == 0)
								return 0;
					} else {
						for (i = -1; i > x0 - pygrx0; i--)
							if (checksafetytraj(m, mp, mP, f, y0, pygrx0 + i) == 0)
								return 0;
					}
				} else if (pygrx0 == x0) {
					if (pygry0 < y0) {
						for (i = 1; i < y0 - pygry0; i++)
							if (checksafetytraj(m, mp, mP, f, pygry0 + i, x0) == 0)
								return 0;
					} else {
						for (i = -1; i > y0 - pygry0; i--)
							if (checksafetytraj(m, mp, mP, f, pygry0 + i, x0) == 0)
								return 0;
					}
				}
			}
			//диагонали
			if (m[pygry0][pygrx0] == nf[2] || m[pygry0][pygrx0] == nf[3]) {
				if (pygry0 < y0) {
					if (pygrx0 < x0) {
						for (i = -1, j = -1; i > pygry0 - y0; i--, j--)
							if (checksafetytraj(m, mp, mP, f, y0 + i, x0 + j) == 0)
								return 0;
					} else {
						for (i = -1, j = 1; i > pygry0 - y0; i--, j++)
							if (checksafetytraj(m, mp, mP, f, y0 + i, x0 + j) == 0)
								return 0;
					}
				} else {
					if (pygrx0 < x0) {
						for (i = 1, j = -1; i < pygry0 - y0; i++, j--)
							if (checksafetytraj(m, mp, mP, f, y0 + i, x0 + j) == 0)
								return 0;
					} else {
						for (i = 1, j = 1; i < pygry0 - y0; i++, j++)
							if (checksafetytraj(m, mp, mP, f, y0 + i, x0 + j) == 0)
								return 0;
					}
				}
			}
		}
		return 1;
	}
	return 0;
}
int sintaksis (char str[], char m[][9], char mp[], char mP[], char rRkK[]) {
	char mk[12] = {'r', 'n', 'b', 'q', 'k', 'p', 'R', 'N', 'B', 'Q', 'K', 'P'};
	char mf[6] = {'r', 'n', 'b', 'q', 'k', 'p'}, x;
	int i, j, y0, x0, y1, x1, j2, x2, y2, ygry0, ygrx0;
	if (!strcmp(str, "RETURN"))
		return 1;
	if (!(strcmp(str, "f0-0")) || !(strcmp(str, "F0-0"))) {
		if (str[0] == 'f') {
			if (rRkK[4] == 1) {
				printf("Рокировка невозможна, король уже ходил!\n");
				return 1;
			}
			if (rRkK[1] == 1) {
				printf("Рокировка невозможна, ладья уже ходила!\n");
				return 1;
			}
			//проверка шаха королю
			for (i = 1; i < 9; i++)
				for (j = 1; j < 9; j++)
					if (m[i][j] == 'k') {
						y0 = i;
						x0 = j;
					}
			if (dangertocell(m, mp, mP, 'k', y0, x0, &ygry0, &ygrx0) > 0) {
				printf("Рокировка невозможна, так как королю поставлен шах!\n");
				return 1;
			}
			//проверка безопасности полей
			if (dangertocell(m, mp, mP, 'k', 1, 6, &ygry0, &ygrx0) > 0) {
				printf("Рокировка невозможна!\n");
				return 1;
			}
			if (dangertocell(m, mp, mP, 'k', 1, 7, &ygry0, &ygrx0) > 0) {
				printf("Рокировка невозможна!\n");
				return 1;
			}
			if (m[1][6] != ' ' || m[1][7] != ' ') {
				printf("Рокировка невозможна!\n");
				return 1;
			}
			m[1][7] = 'k';
			m[1][6] = 'r';
			m[1][5] = m[2][8] = ' ';
			return 0;
		} else {
			if (rRkK[5] == 1) {
				printf("Рокировка невозможна, король уже ходил!\n");
				return 1;
			}
			if (rRkK[3] == 1) {
				printf("Рокировка невозможна, ладья уже ходила!\n");
				return 1;
			}
			//проверка шаха королю
			for (i = 1; i < 9; i++)
				for (j = 1; j < 9; j++)
					if (m[i][j] == 'K') {
						y0 = i;
						x0 = j;
					}
			if (dangertocell(m, mp, mP, 'K', y0, x0, &ygry0, &ygrx0) > 0) {
				printf("Рокировка невозможна, так как королю поставлен шах!\n");
				return 1;
			}
			//проверка безопасности полей
			if (dangertocell(m, mp, mP, 'K', 8, 6, &ygry0, &ygrx0) > 0) {
				printf("Рокировка невозможна!\n");
				return 1;
			}
			if (dangertocell(m, mp, mP, 'K', 8, 7, &ygry0, &ygrx0) > 0) {
				printf("Рокировка невозможна!\n");
				return 1;
			}
			if (m[8][6] != ' ' || m[8][7] != ' ') {
				printf("Рокировка невозможна!\n");
				return 1;
			}
			m[8][7] = 'K';
			m[8][6] = 'R';
			m[8][5] = m[8][8] = ' ';
			return 0;
		}
	}
	if (!(strcmp(str, "f0-0-0")) || !(strcmp(str, "F0-0-0"))) {
		if (str[0] == 'f') {
			if (rRkK[4] == 1) {
				printf("Рокировка невозможна, король уже ходил!\n");
				return 1;
			}
			if (rRkK[0] == 1) {
				printf("Рокировка невозможна, ладья уже ходила!\n");
				return 1;
			}
			//проверка шаха королю
			for (i = 1; i < 9; i++)
				for (j = 1; j < 9; j++)
					if (m[i][j] == 'k') {
						y0 = i;
						x0 = j;
					}
			if (dangertocell(m, mp, mP, 'k', y0, x0, &ygry0, &ygrx0) > 0) {
				printf("Рокировка невозможна, так как королю поставлен шах!\n");
				return 1;
			}
			//проверка безопасности полей
			if (dangertocell(m, mp, mP, 'k', 1, 2, &ygry0, &ygrx0) > 0) {
				printf("Рокировка невозможна!\n");
				return 1;
			}
			if (dangertocell(m, mp, mP, 'k', 1, 3, &ygry0, &ygrx0) > 0) {
				printf("Рокировка невозможна!\n");
				return 1;
			}
			if (dangertocell(m, mp, mP, 'k', 1, 4, &ygry0, &ygrx0) > 0) {
				printf("Рокировка невозможна!\n");
				return 1;
			}
			if (m[1][2] != ' ' || m[1][3] != ' ' || m[1][4] != ' ') {
				printf("Рокировка невозможна!\n");
				return 1;
			}
			m[1][4] = 'k';
			m[1][6] = 'r';
			m[1][5] = m[2][1] = ' ';
			return 0;
		} else {
			if (rRkK[5] == 1) {
				printf("Рокировка невозможна, король уже ходил!\n");
				return 1;
			}
			if (rRkK[2] == 1) {
				printf("Рокировка невозможна, ладья уже ходила!\n");
				return 1;
			}
			//проверка шаха королю
			for (i = 1; i < 9; i++)
				for (j = 1; j < 9; j++)
					if (m[i][j] == 'K') {
						y0 = i;
						x0 = j;
					}
			if (dangertocell(m, mp, mP, 'K', y0, x0, &ygry0, &ygrx0) > 0) {
				printf("Рокировка невозможна, так как королю поставлен шах!\n");
				return 1;
			}
			//проверка безопасности полей
			if (dangertocell(m, mp, mP, 'K', 8, 2, &ygry0, &ygrx0) > 0) {
				printf("Рокировка невозможна!\n");
				return 1;
			}
			if (dangertocell(m, mp, mP, 'K', 8, 3, &ygry0, &ygrx0) > 0) {
				printf("Рокировка невозможна!\n");
				return 1;
			}
			if (dangertocell(m, mp, mP, 'K', 8, 4, &ygry0, &ygrx0) > 0) {
				printf("Рокировка невозможна!\n");
				return 1;
			}
			if (m[8][2] != ' ' || m[8][3] != ' ' || m[8][4] != ' ') {
				printf("Рокировка невозможна!\n");
				return 1;
			}
			m[8][4] = 'K';
			m[8][6] = 'R';
			m[8][5] = m[8][1] = ' ';
			return 0;
		}
	}
	for (i = 0, j = 0; i < 12; i++) {
		if (str[0] == mk[i])
			j++;
	}
	if (j != 1) {
		printf("Неверно указана фигура!\n");
		return 1;
	}
	for (i = 1, x0 = -1, y0 = - 1; i < 9; i++) {
		if (m[i][0] == str[2])
			y0 = i;
		if (m[0][i] == str[1])
			x0 = i;
	}
	if (x0 == -1 || y0 == -1) {
		printf("Неверный синтаксис хода!\n");
		return 1;
	}
	if (x0 == 0 || y0 == 0) {
		printf("Неверно написан номер клетки!\n");
		return 1;
	}
	if (str[0] != m[y0][x0]) {
		printf("Фигура не соотвецтвует клетке!\n");
		return 1;
	}
	for (i = 1, x1 = -1, y1 = -1; i < 9; i++) {
		if (m[i][0] == str[5])
			y1 = i;
		if (m[0][i] == str[4])
			x1 = i;
	}
	if (x1 == -1 || y1 == -1) {
		printf("Неверный синтаксис хода!\n");
		return 1;
	}
	if (x0 == x1 && y0 == y1) {
		printf("Неверный синтаксис хода!\n");
		return 1;
	}
	if (str[3] == '-') {
		if (m[y1][x1] != ' ') {
			printf("Тип хода не соотвецтвует!\n");
			return 1;
		}
	} else if (str[3] == 'x') {
		for (i = 0, j = 0; i < 12; i++)
			if (m[y1][x1] == mk[i])
				j++;
		if (j != 1) {
			printf("Неверный синтаксис хода!\n");
			return 1;
		}
		for (i = 0, j = 0, j2 = 0; i < 6; i++) {
			if (str[0] == mf[i])
				j = 1;
			if (m[y1][x1] == mf[i])
				j2 = 1;
			}
		if (j == j2) {
			printf("Неверный синтаксис хода!\n");
			return 1;
		}
	} else {
		printf("Неверный синтаксис хода!\n");
		return 1;
	}
	logikXod(str[0], str[3], x0, y0, x1, y1 , m, mp, mP, rRkK);
}
int logikXod (char fig, char xod, int x0, int y0, int x1, int y1, char m[][9], char mp[], char mP[], char rRkK[]) {
	char mk[12] = {'r', 'n', 'b', 'q', 'k', 'p', 'R', 'N', 'B', 'Q', 'K', 'P'};
	char mf[6] = {'r', 'n', 'b', 'q', 'k', 'p'}, x, p;
	int i, j, j2, x2, y2, ygry0, ygrx0;
	//Пешки
	if (fig == 'p' && xod == '-') {
		if (y1 != y0 +1 && y1 != y0 + 2) {
			printf("Неверный синтаксис хода для фигуры 'p'\n");
			return 1;
		}
		if (y1 == y0 + 1) {
			mp[x0] = 1;
		} else {
			if (y1 == y0 + 2 && mp[x0] != 0){
				printf("Попытка сделать двойной шаг!\n");
				return 1;
			}
			if (y1 == y0 + 2 && mp[x0] == 0) {
				if (m[y0 + 1][x0] != ' ') {
					printf("Неверный синтаксис хода для фигуры 'p''\n");
					return 1;
				}
				mp[x0] = 1;
			}
		}
	}
	if (fig == 'P' && xod == '-') {
		if (y1 != y0 - 1 && y1 != y0 - 2) {
			printf("Неверный синтаксис хода для фигуры 'p'\n");
			return 1;
		}
		if (y1 == y0 - 1) {
			mP[x0] = 1;
		} else {
			if (y1 == y0 - 2 && mP[x0] != 0) {
				printf("Попытка сделать двойной шаг!\n");
				return 1;
			}
			if (y1 == y0 - 2 && mP[x0] == 0) {
				if (m[y0 - 1][x0] != ' ') {
					printf("Неверный синтаксис хода для фигуры 'P'\n");
					return 1;
				}
				mP[x0] = 1;
			}
		}
	}
	if ((fig == 'p' || fig == 'P') && xod == 'x') {
		if (y1 != y0 + 1 && y1 != y0 - 1) {
			printf("Неверный синтаксис хода для фигуры 'p'\n");
			return 1;
		}
		if (x1 != x0 + 1 && x1 != x0 - 1) {
			printf("Неверный синтаксис хода для фигуры 'p'\n");
			return 1;
		}
	}
	//Ладья
	if (fig == 'b' || fig == 'B') {
		if (y0 - y1 != x0 - x1 && (y0 - y1) * -1 != x0 - x1) {
			printf("Неверный синтаксис хода для фигуры '%c'!\n", fig);
			return 1;
		}
		if (x1 - x0 != 1 && x1 - x0 != -1) {
			x2 = -10;
			if (x1 - x0 > 0) {
				for (i = 1; x2 < x1 - 1; i++) {
					x2 = x0 + i;
					if (y1 - y0 > 0) {
						y2 = y0 + i;
					} else {
						y2 = y0 - i;
					}
					if (m[y2][x2] != ' ') {
						printf("'%c' не сможет перепрыгнуть '%c'  x2: %d  y2: %d", fig, m[y2][x2], y2, x2);
						return 1;
					}
				}
			} else {
				for (i = 1; x2 < x1 - 1; i++) {
					x2 = x0 - i;
					if (y1 - y0 > 0) {
						y2 = y0 + i;
					} else {
						y2 = y0 - i;
					}
					if (m[y2][x2] != ' ') {
						printf("'%c' не сможет перепрыгнуть '%c'  x2: %d  y2: %d", fig, m[y2][x2], y2, x2);
						return 1;
					}
				}
			}
		}
	}
	//Конь
	if (fig == 'n' || fig == 'N') {
		if (x0 - x1 == -2 || x0 - x1 == 2) {
			if (y0 - y1 == -1 || y0 - y1 == 1) {
			} else {
				printf("Неверный синтаксис хода фигуры '%c'!\n", fig);
				return 1;
			}
		} else if (x0 - x1 == -1 || x0 - x1 == 1) {
			if (y0 - y1 == -2 || y0 - y1 == 2) {
			} else {
				printf("Неверный синтаксис хода фигуры '%c'!\n", fig);
				return 1;
			}
		} else {
			printf("Неверный синтаксис хода фигуры '%c'!\n", fig);
			return 1;
		}
	}
	//Слон
	if (fig == 'r' || fig == 'R') {
		if (x0 - x1 == 0 || y0 - y1 == 0) {
			if (y0 - y1 > 1 || y0 - y1 < -1) {
				for (i = 1, y2 = -10; y2 < y1 - 1; i++) {
					if (y0 - y1 < 0) {
						y2 = y0 + i;
					} else {
						y2 = y0 - i;
					}
					if (m[y2][x0] != ' ') {
						printf("Неверный синтаксис хода фигуры '%c'!\n", fig);
						return 1;
					}
				}
			} else if (x0 - x1 > 1 || x0 - x1 < -1) {
				for (i = 1, x2 = -10; x2 < x1 - 1; i++) {
					if (x0 - x1 < 0) {
						x2 = x0 + i;
					} else {
						x2 = x0 - i;
					}
					if (m[y0][x2] != ' ') {
						printf("Неверный синтаксис хода фигуры '%c'!\n", fig);
						return 1;
					}
				}
			}
		} else {
			printf("Неверный синтаксис хода фигуры '%c'!\n", fig);
			return 1;
		}
		if (fig == 'r') {
			if (x0 == 1) {
				rRkK[0] = 1;
			} else {
				rRkK[1] = 1;
			}
		} else {
			if (x0 == 1) {
				rRkK[2] = 1;
			} else {
				rRkK[3] = 1;
			}
		}
	}
	//Ферзь
	if (fig == 'q' || fig == 'Q') {
		if (y0 - y1 == x0 - x1 || (y0 - y1) * -1 == x0 - x1) {
			if (x1 - x0 > 1 || x1 - x0 < -1) {
				x2 = -10;
				if (x1 - x0 > 0) {
					for (i = 1; x2 < x1 - 1; i++) {
						x2 = x0 + i;
						if (y1 - y0 > 0) {
							y2 = y0 + i;
						} else {
							y2 = y0 - i;
						}
						if (m[y2][x2] != ' ') {
							printf("'%c' не сможет перепрыгнуть '%c'  x2: %d  y2: %d", fig, m[y2][x2], y2, x2);
							return 1;
						}
					}
				} else {
					for (i = 1; x2 < x1 - 1; i++) {
						x2 = x0 - i;
						if (y1 - y0 > 0) {
							y2 = y0 + i;
						} else {
							y2 = y0 - i;
						}
						if (m[y2][x2] != ' ') {
							printf("'%c' не сможет перепрыгнуть '%c'  x2: %d  y2: %d", fig, m[y2][x2], y2, x2);
							return 1;
						}
					}
				}
			}
		} else if (x0 - x1 == 0 || y0 - y1 == 0) {
			if (y0 - y1 > 1 || y0 - y1 < -1) {
				for (i = 1, y2 = -10; y2 < y1 - 1; i++) {
					if (y0 - y1 < 0) {
						y2 = y0 + i;
					} else {
						y2 = y0 - i;
					}
					if (m[y2][x0] != ' ') {
						printf("Неверный синтаксис хода фигуры '%c'!\n", fig);
						return 1;
					}
				}
			} else if (x0 - x1 > 1 || x0 - x1 < -1) {
				for (i = 1, x2 = -10; x2 < x1 - 1; i++) {
					if (x0 - x1 < 0) {
						x2 = x0 + i;
					} else {
						x2 = x0 - i;
					}
					if (m[y0][x2] != ' ') {
						printf("Неверный синтаксис хода фигуры '%c'!\n", fig);
						return 1;
					}
				}
			}
		} else {
			printf("Неверный синтаксис хода фигуры '%c'!\n", fig);
			return 1;
		}
	}
	//Король
	if (fig == 'k' || fig == 'K') {
		if (x0 - x1 > 1 || x0 - x1 < -1 || y0 - y1 > 1 || y0 - y1 < -1) {
			printf("Неверный синтаксис хода фигуры '%c'!\n", fig);
			return 1;
		}
		if (fig == 'k') {
			rRkK[4] = 1;
		} else {
			rRkK[5] = 1;
		}
	}
	p = m[y1][x1];
	m[y1][x1] = m[y0][x0];
	m[y0][x0] = ' ';
	if (fig == 'p' && y1 == 8) {
		printf("Пешка дошла до конца поля, выберите фигуру 'b', 'n', 'q', 'r': ");
		scanf("%c", &x);
		if (x == 'b') {
			m[y1][x1] = x;
		} else if (x == 'n') {
			m[y1][x1] = x;
		} else if (x == 'q') {
			m[y1][x1] = x;
		}else if (x == 'r') {
			m[y1][x1] = x;
		} else {
			printf("Неверно введина фигура!\n");
			m[y0][x0] = m[y1][x1];
			m[y1][x1] = p;
			return 1;
		}
	} else if (fig == 'P' && y1 == 1) {
		printf("Пешка дошла до конца поля, выберите фигуру 'B', 'N', 'Q', 'R': ");
		scanf("%c", &x);
		if (x == 'B') {
			m[y1][x1] = x;
		} else if (x == 'N') {
			m[y1][x1] = x;
		} else if (x == 'Q') {
			m[y1][x1] = x;
		}else if (x == 'R') {
			m[y1][x1] = x;
		} else {
			printf("Неверно введина фигура!\n");
			m[y0][x0] = m[y1][x1];
			m[y1][x1] = p;
			return 1;
		}
	}
	return 0;
}
