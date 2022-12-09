#ifndef KEYBOARDBATTLE_H
#define KEYOBOARDBATTLE_H
#pragma comment(lib,"winmm.lib")
#pragma once
#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <conio.h>
#include <ctime>
#include <vector>
#include <string>
#include <algorithm>

#define WINDOW_WIDTH 100
#define WINDOW_HEIGHT 21
#define ARROW_NUM 224
#define MAXIMUM_LEVEL 15

using namespace std;

// 게임 상태를 나타내며 ONGOING을 제외한 상태에서는 모두 게임이 종료되어야 함.
enum GAME_STATE {
	ONGOING = 0,
	P1WIN,
	P2WIN,
	P1OVER,
	P2OVER
};

// ↑↓←→ 입력에 대한 코드값
enum KEYBOARD {
	UP = 72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80
};

// 전역변수
extern vector<int> questionvec[MAXIMUM_LEVEL];

// 클래스
class Player {
private:
	unsigned int life = 3;
	unsigned int level = 1;
	unsigned int numOfInput = 0;
	vector<int> answervec;
	string questionstr = "";
	string answerstr = "";
	COORD start = { 0, 1 }; // 맵 부분 제외하고 가용가능한 첫 좌표

public:
	Player() {}
	Player(short n) : start{ 0, 1 + 10 * n } {} // 플레이어 1,2 화면 구분
	~Player() {}

	unsigned int getLife() const {
		return life;
	}
	unsigned int getLevel() const {
		return level;
	}
	unsigned int getNumOfInput() const {
		return numOfInput;
	}
	vector<int>& getAvec() {
		return answervec;
	}
	string& getQstr() {
		return questionstr;
	}
	string& getAstr() {
		return answerstr;
	}
	COORD getStart() const {
		return start;
	}

	void isPressed() {
		++numOfInput;
	}
	void minusLife() {
		--life;
	}
	void nextLevel() {
		++level;
	}

	void clear();

	bool isOver() const {
		return life < 1;
	}
	bool isWin() const {
		return getLevel() > MAXIMUM_LEVEL;
	}
};

// 윈도우 함수
void setConsoleView();
void gotoxy(int x, int y);

// 게임 내 함수
void printTimer(int second);
void makeArrow();
void printArrow(Player& p);
void drawMap();
void drawInfo(const Player& p);
void checkAnswer(Player& p);
bool isNext(const Player& p);
void setNext(Player& p);
void gameOver(const Player& p);
void gameWin(const Player& p);
GAME_STATE getState(const Player& p1, const Player& p2);
void gameScreen();
#endif