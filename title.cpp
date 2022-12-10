#include "title.h"

void gotoxy(int x, int y) {
	COORD POS = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), POS);
}

//pos : 시작좌표 distance : 메뉴 간 간격 numOfItem : 메뉴 개수
MENU select(COORD pos, unsigned int distance, unsigned int numOfItem) {
	int input = 0;
	pos.X -= 3;
	int minY = pos.Y;
	int maxY = pos.Y + (numOfItem - 1) * distance;


	gotoxy(pos.X, pos.Y);
	cout << "▶";
	while (true) {

		if (_kbhit()) {
			input = _getch();
			if (input == ARROW_NUM) {
				gotoxy(pos.X, pos.Y);
				cout << "  ";
				switch (_getch()) {
				case UP:
					pos.Y -= distance;
					break;
				case DOWN:
					pos.Y += distance;
					break;
				}

				if (pos.Y > maxY) {
					pos.Y = minY;
				}

				if (pos.Y < minY) {
					pos.Y = maxY;
				}

				gotoxy(pos.X, pos.Y);
				cout << "▶";
			}
			if (input == VK_ESCAPE) {
				return EXIT;
			}
			if (input == VK_RETURN) {
				unsigned int num = (pos.Y - minY) / distance + 1;
				switch (num) {
				case 1:
					return GAME1;
				case 2:
					return GAME2;
				case 3:
					return GAME3;
				}
			}
		}
	}
}

void setConsoleView() {
	// 창 크기 고정
	HWND consoleWindow = GetConsoleWindow();
	SetWindowLong(consoleWindow, GWL_STYLE, GetWindowLong(consoleWindow, GWL_STYLE) & ~WS_MAXIMIZEBOX & ~WS_SIZEBOX);
	// 편집모드 해제
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_EXTENDED_FLAGS);

	// 커서 숨김
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void printScreen() {
	system("cls");
	system("title MINI ARCADE");
	gotoxy(0, 2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_LIGHTRED);
	cout << "                ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_LIGHTBLUE);
	cout << "                       ▩▩▩▩  ▩▩▩  ▩▩    ▩▩▩" << endl
		<< "                       ▩ ▩ ▩    ▩    ▩  ▩    ▩" << endl
		<< "                       ▩    ▩  ▩▩▩  ▩  ▩  ▩▩▩" << endl << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_LIGHTYELLOW);
	cout << "                     ▩   ▩▩   ▩▩▩   ▩   ▩▩   ▩▩▩" << endl
		<< "                   ▩  ▩ ▩  ▩ ▩     ▩  ▩ ▩  ▩ ▩" << endl
		<< "                   ▩▩▩ ▩▩▩ ▩     ▩▩▩ ▩  ▩ ▩▩▩" << endl
		<< "                   ▩  ▩ ▩  ▩ ▩     ▩  ▩ ▩  ▩ ▩  " << endl
		<< "                   ▩  ▩ ▩  ▩ ▩▩▩ ▩  ▩ ▩▩   ▩▩▩" << endl;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_LIGHTRED);
	cout << "                ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_PURPLE | (COLOR_BLUEGREEN << 4));

	gotoxy(28, 13);
	cout << "PRESS ENTER TO CONTINUE";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_LIGHTWHITE);
}

void title() {
	COORD menu = { 30, 15 };
	int distance = 2;
	vector<string> name = { {"1.     DICE"}, {"2. MATCHING GAME"}, {"3. KEYBOARD BATTLE"} };

	// 화면출력

	while (true) {
		Dice dice;
		Matching matchingGame;
		Rhythm rhythm;
		system("mode con: lines=24 cols=80");


		printScreen();
		for (int i = 0; i < name.size(); i++) {
			gotoxy(menu.X, menu.Y + i * distance);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_LIGHTGREEN + i);
			cout << name[i];
		}
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_LIGHTWHITE);

		// 메뉴 선택, 게임 실행
		switch (select(menu, distance, 3)) {
		case EXIT:
			return;
		case GAME1:
			system("cls");
			dice.start();
			break;
		case GAME2:
			system("cls");
			matchingGame.start();
			break;
		case GAME3:
			system("cls");
			rhythm.start();
			break;
		}
		FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
	}
}