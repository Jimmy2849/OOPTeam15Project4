#pragma once
#ifndef TITLE_H
#define TITLE_H

#include <iostream>
#include <Windows.h>
#include <vector>
#include <string>
#include <conio.h>
#include "Rhythm.h"
#include "Dice.h"
#include "MatchingGame.h"

#define ARROW_NUM 224
#define COLOR_BLACK 0x0000
#define COLOR_BLUE 0x0001
#define COLOR_GREEN 0x0002
#define COLOR_BLUEGREEN 0x0003
#define COLOR_RED 0x0004
#define COLOR_PURPLE 0x0005
#define COLOR_YELLOW 0x0006
#define COLOR_WHITE 0x0007
#define COLOR_GRAY 0x0008
#define COLOR_LIGHTBLUE 0x0009
#define COLOR_LIGHTGREEN 0x000A
#define COLOR_LIGHTBLUEGREEN 0x000B
#define COLOR_LIGHTRED 0x000C
#define COLOR_LIGHTPURPLE 0x000D
#define COLOR_LIGHTYELLOW 0x000E
#define COLOR_LIGHTWHITE 0x000F

using namespace std;

enum MENU {
	EXIT = -100,
	GAME1,
	GAME2,
	GAME3
};
enum KEYBOARD {
	UP = 72,
	DOWN = 80
};

void gotoxy(int x, int y);

//pos : 시작좌표 distance : 메뉴 간 간격 numOfItem : 메뉴 개수
MENU select(COORD pos, unsigned int distance, unsigned int numOfItem);

void setConsoleView();
void printScreen();
void title();

#endif