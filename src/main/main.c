#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "libchessviz/chessviz.h"



int main () {
	setlocale(LC_ALL, "RUS");
	int i, j, t = 1;
	char m[9][9] = {0}, str[20], mp[9] = {0}, mP[9] = {0}, mf[6] = {'r', 'n', 'b', 'q', 'k', 'p'}, rRkK[6] = {0};
	
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
	for (i = 3; i < 7; i++)
		for (j = 1; j < 9; j++)
			m[i][j] = ' ';
	
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
		printPole(m);
		do {
			if (mat(m, mp, mP, 'k') == 1) {
				printf("Geim over! 2ply WIN!");
				return 0;
			}
			printf("%d.1игрок) ", t);
			scanf("%s", str);
			for (i = 0, j = 0; i < 6; i++) {
				if (str[0] == mf[i])
					j = 1;
			}
			if (!strcmp(str, "0-0")) {
				strcpy(str, "f0-0");
			} else if (!strcmp(str, "0-0-0")) {
				strcpy(str, "f0-0-0");
			} else {
				if (j != 1) {
					printf("Фигура другого игрока!\n");
					strcpy(str, "RETURN");
				}
			}
		} while (sintaksis(str, m, mp, mP, rRkK));
		printPole(m);
		do {
			if (mat(m, mp, mP, 'K') == 1) {
				printf("Geim over! 1ply WIN!");
				return 0;
			}
			
			printf("%d.2игрок) ", t);
			scanf("%s", str);
			for (i = 0, j = 0; i < 6; i++) {
				if (str[0] == mf[i])
					j = 1;
			}
			if (!strcmp(str, "0-0")) {
				strcpy(str, "F0-0");
			} else if (!strcmp(str, "0-0-0")) {
				strcpy(str, "F0-0-0");
			} else {
				if (j == 1) {
					printf("Фигура другого игрока!\n");
					strcpy(str, "RETURN");
				}
			}
		} while (sintaksis(str, m, mp, mP, rRkK));
		t++;
	}
}
