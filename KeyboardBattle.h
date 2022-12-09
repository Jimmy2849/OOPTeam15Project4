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

// ���� ���¸� ��Ÿ���� ONGOING�� ������ ���¿����� ��� ������ ����Ǿ�� ��.
enum GAME_STATE {
	ONGOING = 0,
	P1WIN,
	P2WIN,
	P1OVER,
	P2OVER
};

// ����� �Է¿� ���� �ڵ尪
enum KEYBOARD {
	UP = 72,
	LEFT = 75,
	RIGHT = 77,
	DOWN = 80
};

// ��������
extern vector<int> questionvec[MAXIMUM_LEVEL];

// Ŭ����
class Player {
private:
	unsigned int life = 3;
	unsigned int level = 1;
	unsigned int numOfInput = 0;
	vector<int> answervec;
	string questionstr = "";
	string answerstr = "";
	COORD start = { 0, 1 }; // �� �κ� �����ϰ� ���밡���� ù ��ǥ

public:
	Player() {}
	Player(short n) : start{ 0, 1 + 10 * n } {} // �÷��̾� 1,2 ȭ�� ����
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

// ������ �Լ�
void setConsoleView();
void gotoxy(int x, int y);

// ���� �� �Լ�
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