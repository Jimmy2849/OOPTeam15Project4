#include "title.h"
#include "KeyboardBattle.h"
#include "Dice.h"
#include "MatchingGame.h"

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
	while(true) {
	
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

void title() {
	COORD menu = { 32, 20 };
	int distance = 2;
	vector<string> name = { {"1.     DICE"}, {"2. MATCHING GAME"}, {"3. KEYBOARD BATTLE"} };

	// 화면출력
	
	while (true) {
		system("cls");
		gotoxy(0, 4);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_LIGHTRED);
		cout << "                  ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_LIGHTBLUE);
		cout << "                         ▩▩▩▩  ▩▩▩  ▩▩    ▩▩▩" << endl
			<< "                         ▩ ▩ ▩    ▩    ▩  ▩    ▩" << endl
			<< "                         ▩    ▩  ▩▩▩  ▩  ▩  ▩▩▩" << endl << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_LIGHTYELLOW);
		cout << "                       ▩   ▩▩   ▩▩▩   ▩   ▩▩   ▩▩▩" << endl
			<< "                     ▩  ▩ ▩  ▩ ▩     ▩  ▩ ▩  ▩ ▩" << endl
			<< "                     ▩▩▩ ▩▩▩ ▩     ▩▩▩ ▩  ▩ ▩▩▩" << endl
			<< "                     ▩  ▩ ▩  ▩ ▩     ▩  ▩ ▩  ▩ ▩  " << endl
			<< "                     ▩  ▩ ▩  ▩ ▩▩▩ ▩  ▩ ▩▩   ▩▩▩" << endl;
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_LIGHTRED);
		cout << "                  ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛";

		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_PURPLE | (COLOR_BLUEGREEN << 4));

		gotoxy(30, 17);
		cout << "PRESS ENTER TO CONTINUE";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), COLOR_LIGHTWHITE);
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
			cout << "GAME1 SELECTED";
			break;
		case GAME2:
			system("cls");
			cout << "GAME2 SELECTED";
			break;
		case GAME3:
			system("cls");
			cout << "GAME3 SELECTED";
			break;
		}
	}
}