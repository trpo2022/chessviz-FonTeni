#pragma once


void printPole (char m[][9]);

int checksafetytraj(char m[][9], char mp[], char mP[], char f, int y0, int x0);

int dangertocell (char m[][9], char mp[], char mP[], char f, int y0, int x0, int *ygry0, int *ygrx0);

int mat (char m[][9], char mp[], char mP[], char f);

int sintaksis (char str[], char m[][9], char mp[], char mP[], char rRkK[]);

int logikXod (char fig, char xod, int x0, int y0, int x1, int y1, char m[][9], char mp[], char mP[], char rRkK[]);//


