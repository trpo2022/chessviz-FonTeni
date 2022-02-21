#include <stdio.h>
#include <stdlib.h>


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


int main () {
	int i, j, j2, t = 0, x0, y0, x1, y1, x2 = 0, y2 = 0;
	char m[9][9] = {0}, str[20], mk[12] = {'r', 'n', 'b', 'q', 'k', 'p', 'R', 'N', 'B', 'Q', 'K', 'P'}, mp[9] = {0}, mP[9] = {0};
	char mf[6] = {'r', 'n', 'b', 'q', 'k', 'p'};
	//char mF[6] = {'R', 'N', 'B', 'Q', 'K', 'P'};
	m[0][0] = ' ';
	m[0][1] = 'A';
	m[0][2] = 'B';
	m[0][3] = 'C';
	m[0][4] = 'D';
	m[0][5] = 'E';
	m[0][6] = 'F';
	m[0][7] = 'G';
	m[0][8] = 'H';
	
	m[1][0] = '8';
	m[2][0] = '7';
	m[3][0] = '6';
	m[4][0] = '5';
	m[5][0] = '4';
	m[6][0] = '3';
	m[7][0] = '2';
	m[8][0] = '1';
	
	for (i = 1; i < 9; i++)
		m[2][i] = 'p';
	for (i = 1; i < 9; i++)
		m[7][i] = 'P';
	
	m[1][1] = 'r';
	m[1][2] = 'n';
	m[1][3] = 'b';
	m[1][4] = 'q';
	m[1][5] = 'k';
	m[1][6] = 'b';
	m[1][7] = 'n';
	m[1][8] = 'r';
	
	m[8][1] = 'R';
	m[8][2] = 'N';
	m[8][3] = 'B';
	m[8][4] = 'Q';
	m[8][5] = 'K';
	m[8][6] = 'B';
	m[8][7] = 'N';
	m[8][8] = 'R';
	
	for (;;) {
		x0 = 0;
		y0 = 0;
		x1 = 0;
		y1 = 0;
		t++;
		printPole(m);
		printf("%d. ", t);
		scanf("%s", &str);
		
		for (i = 0, j = 0; i < 12; i++)
			if (str[0] == mk[i])
				j++;
		if (j != 1) {
			printf("Неверно указана фигура!\n");
			return;
		}
			
		for (i = 1; i < 9; i++) {
			if (m[i][0] == str[2]) {
				y0 = i;
			}
			if (m[0][i] == str[1]) {
				x0 = i;
			}
		}
		if (x0 == 0 || y0 == 0) {
			printf("Неверно написан номер клетки!\n");
			return;
		}
		if (str[0] != m[y0][x0]) {
			printf("Фигура не соотвецтвует клетке!\n");
			return;
		}
		for (i = 1; i < 9; i++) {
			if (m[i][0] == str[5]) {
				y1 = i;
			}
			if (m[0][i] == str[4]) {
				x1 = i;
			}
		}
		if (str[3] == '-') {
			if (m[y1][x1] != 0) {
				printf("Тип хода не соотвецтвует! '%c'\n", m[y1][x1]);
				return;
			}
			m[y1][x1] = m[y0][x0];
			m[y0][x0] = 0;
		} else if (str[3] == 'x') {
			for (i = 0, j = 0; i < 12; i++)
				if (m[y1][x1] == mk[i])
					j++;
			if (j != 1) {
				printf("Неверный синтаксис хода!\n");
				return;
			}
			for (i = 0, j = 0, j2 = 0; i < 6; i++) {
				if (str[0] == mf[i])
					j = 1;
				
				if (m[y1][x1] == mf[i])
					j2 = 1;
			}
			if (j == j2) {
				printf("Неверный синтаксис хода!\n");
				return;
			}
			m[y1][x1] = m[y0][x0];
			m[y0][x0] = 0;
		} else {
			printf("Неверный синтаксис хода!\n");
			return;
		}
		if (x0 == x1 && y0 == y1) {
			printf("Неверный синтаксис хода!\n");
			return;
		}
		if (str[0] == 'p' && str[3] == '-') {
			if (x1 != x0 && y1 != y0 +1 && y1 != y0 + 2) {
				printf("Неверный синтаксис хода для фигуры 'p'\n");
				return;
			}
			if (y1 == y0 + 2 && mp[x0] != 0){
				printf("Попытка сделать двойной шаг 2 раз!\n");
				return;
			}
			if (y1 == y0 + 2 && mp[x0] == 0) {
				mp[x0] = 1;
			}
		}
		if (str[0] == 'p' && str[0] == 'P' && str[3] == '+') {
			if (y1 != y0 + 1 && y1 != y0 - 1) {
				printf("Неверный синтаксис хода для фигуры 'p'\n");
				return;
			}
			if (x1 != x0 + 1 && x1 != x0 - 1) {
				printf("Неверный синтаксис хода для фигуры 'p'\n");
				return;
			}
		}
		if (str[0] == 'P' && str[3] == '-') {
			if (x1 != x0 && y1 != y0 - 1 && y1 != y0 - 2) {
				printf("Неверный синтаксис хода для фигуры 'p'\n");
				return;
			}
			if (y1 == y0 - 2 && mP[x0] != 0) {
				printf("Попытка сделать двойной шаг 2 раз!\n");
				return;
			}
			if (y1 == y0 - 2 && mP[x0] == 0) {
				mP[x0] = 1;
			}
		}
		if (str[0] == 'b' || str[0] == 'B') {
			if (y0 - y1 != x0 - x1 && (y0 - y1) * -1 != x0 - x1 && y0 - y1 != (x0 - x1) * -1) {
				printf("Неверный синтаксис хода для фигуры 'b' или 'B'!\n");
				return;
			}
			if (x1 - x0 != 1 || x1 - x0 != -1) {
				x2 = -10;
				if (x1 - x0 > 0) {
					for (i = 1; x2 < x1 - 1; i++) {
						x2 = x0 + i;
						if (y1 - y0 > 0) {
							y2 = y0 + i;
						} else {
							y2 = y0 - i;
						}
						if (m[y2][x2] != 0) {
							printf("'b' или 'B' не сможет перепрыгнуть '%c'  x0: %d  y0: %d", m[y2][x2], y2, x2);
							return;
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
						if (m[y2][x2] != 0) {
							printf("'b' или 'B' не сможет перепрыгнуть '%c'  x0: %d  y0: %d", m[y2][x2], y2, x2);
							return;
						}
					}
				}
			}
		}
		if (str[0] == 'n' || str[0] == 'N') {
			if (x0 - x1 == -2 || x0 - x1 == 2) {
				if (y0 - y1 == -1 || y0 - y1 == 1) {
				} else {
					printf("Неверный синтаксис хода фигуры 'n' или 'N'!\n");
					return;
				}
			} else if (x0 - x1 == -1 || x0 - x1 == 1) {
				if (y0 - y1 == -2 || y0 - y1 == 2) {
				} else {
					printf("Неверный синтаксис хода фигуры 'n' или 'N'!\n");
					return;
				}
			} else {
				printf("Неверный синтаксис хода фигуры 'n' или 'N'!\n");
				return;
			}
		}
		if (str[0] == 'r' || str[0] == 'R') {
			if (x0 - x1 == 0 && (y0 - y1 != 1 || y0 - y1 != -1)) {
				for (i = 1, y2 = -10; y2 < y1 - 1; i++) {
					if (y0 - y1 < 0) {
						y2 = y0 + i;
					} else {
						y2 = y0 - i;
					}
					if (m[y2][x0] != 0) {
						printf("Неверный синтаксис хода фигуры 'r' или 'R'!\n");
						return;
					}
				}
			} else if (y0 - y1 == 0 && (x0 - x1 != 1 || x0 - x1 != -1)) {
				for (i = 1, x2 = -10; x2 < x1 - 1; i++) {
					if (x0 - x1 < 0) {
						x2 = x0 + i;
					} else {
						x2 = x0 - i;
					}
					if (m[y0][x2] != 0) {
						printf("Неверный синтаксис хода фигуры 'r' или 'R'!\n");
						return;
					}
				}
			} else {
				printf("Неверный синтаксис хода фигуры 'r' или 'R'!\n");
				return;
			}
		}
		if (str[0] == 'q' || str[0] == 'Q') {
			if (y0 - y1 != x0 - x1 && (y0 - y1) * -1 != x0 - x1 && y0 - y1 != (x0 - x1) * -1) {
				if (x1 - x0 != 1 || x1 - x0 != -1) {
					x2 = -10;
					if (x1 - x0 > 0) {
						for (i = 1; x2 < x1 - 1; i++) {
							x2 = x0 + i;
							if (y1 - y0 > 0) {
								y2 = y0 + i;
							} else {
								y2 = y0 - i;
							}
							if (m[y2][x2] != 0) {
								printf("'b' или 'B' не сможет перепрыгнуть '%c'  x0: %d  y0: %d", m[y2][x2], y2, x2);
								return;
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
							if (m[y2][x2] != 0) {
								printf("'b' или 'B' не сможет перепрыгнуть '%c'  x0: %d  y0: %d", m[y2][x2], y2, x2);
								return;
							}
						}
					}
				}
			} else if (x0 - x1 == 0 && (y0 - y1 != 1 || y0 - y1 != -1)) {
				for (i = 1, y2 = -10; y2 < y1 - 1; i++) {
					if (y0 - y1 < 0) {
						y2 = y0 + i;
					} else {
						y2 = y0 - i;
					}
					if (m[y2][x0] != 0) {
						printf("Неверный синтаксис хода фигуры 'r' или 'R'!\n");
						return;
					}
				}
			} else if (y0 - y1 == 0 && (x0 - x1 != 1 || x0 - x1 != -1)) {
				for (i = 1, x2 = -10; x2 < x1 - 1; i++) {
					if (x0 - x1 < 0) {
						x2 = x0 + i;
					} else {
						x2 = x0 - i;
					}
					if (m[y0][x2] != 0) {
						printf("Неверный синтаксис хода фигуры 'r' или 'R'!\n");
						return;
					}
				}
			} else {
				printf("Неверный синтаксис хода фигуры 'q' или 'Q'!\n");
				return;
			}
		}
		if (str[0] == 'k' || str[0] == 'K') {
			if (x0 - x1 != 1 && x0 - x1 != -1 && y0 - y1 != 1 && y0 - y1 != -1) {
				printf("Неверный синтаксис хода фигуры 'k' или 'K'!\n");
				return;
			}
			if (x0 - x1 > 1 || x0 - x1 < -1 || y0 - y1 > 1 || y0 - y1 < -1) {
				printf("Неверный синтаксис хода фигуры 'k' или 'K'!\n");
				return;
			}
		}
		
		//printPole(m);
		//printf("%d. ", t);
		//scanf("%s", &str);
	}
}
