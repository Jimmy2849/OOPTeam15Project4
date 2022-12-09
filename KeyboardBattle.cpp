#include "KeyboardBattle.h"
// 문제 세트를 미리 설정, 플레이어 레벨에 따라 순차 접근
vector<int> questionvec[MAXIMUM_LEVEL];

void Player ::clear() {
	answervec.clear();
	questionstr.clear();
	answerstr.clear();
	numOfInput = 0;
}

void setConsoleView() {
	// 제목 설정
	system("title Keyboard Battle");
	// 창 크기 지정
	char* command = new char[30];
	sprintf_s(command, 30, "mode con: lines=%d cols=%d", WINDOW_HEIGHT, WINDOW_WIDTH);
	system(command);
	delete[] command;
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

void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}

// 게임 시작 또는 재시작 시 준비시간 부여
void printTimer(int second) {
	clock_t prevtime, curtime;
	prevtime = clock();
	for (int i = 0; i <= second; i++) {
		while (difftime(curtime = clock(), prevtime) < 1000 * (i + 1)) {};
		gotoxy(WINDOW_WIDTH / 2 - 5, WINDOW_HEIGHT / 2);
		cout << second - i;
	}
}

// 게임오버를 나타내는 출력용 함수
void gameOver(const Player& p) {
	DWORD dw;
	COORD pos = p.getStart();
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', WINDOW_WIDTH * (WINDOW_HEIGHT - 3) / 2, pos, &dw);
	gotoxy(0, pos.Y + 2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	cout << "           ■■■       ■      ■    ■  ■■■■    ■■   ■      ■  ■■■■  ■■■" << "\n"
		<< "         ■            ■■     ■■■■  ■        ■    ■  ■    ■   ■        ■   ■" << "\n"
		<< "         ■   ■■    ■  ■    ■ ■ ■  ■■■■  ■    ■   ■  ■    ■■■■  ■■■" << "\n"
		<< "          ■   ■    ■■■■   ■    ■  ■        ■    ■    ■■     ■        ■   ■" << "\n"
		<< "           ■■■   ■      ■  ■    ■  ■■■■    ■■       ■      ■■■■  ■    ■";

	(pos.Y < 10) ? pos.Y += 10 : pos.Y -= 10;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', WINDOW_WIDTH * (WINDOW_HEIGHT - 3) / 2, pos, &dw);
	gotoxy(0, pos.Y + 2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cout << "                                     ■    ■  ■■■■  ■    ■" << endl
		<< "                                     ■ ■ ■    ■■    ■■  ■" << endl
		<< "                                     ■ ■ ■    ■■    ■ ■ ■" << endl
		<< "                                      ■■■     ■■    ■  ■■" << endl
		<< "                                      ■  ■   ■■■■  ■    ■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

// 승자를 나타내는 출력용 함수
void gameWin(const Player& p) {
	DWORD dw;
	COORD pos = p.getStart();
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', WINDOW_WIDTH * (WINDOW_HEIGHT - 3) / 2, pos, &dw);
	gotoxy(0, pos.Y + 2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	cout << "                                     ■    ■  ■■■■  ■    ■" << endl
		<< "                                     ■ ■ ■    ■■    ■■  ■" << endl
		<< "                                     ■ ■ ■    ■■    ■ ■ ■" << endl
		<< "                                      ■■■     ■■    ■  ■■" << endl
		<< "                                      ■  ■   ■■■■  ■    ■";

	(pos.Y < 10) ? pos.Y += 10 : pos.Y -= 10;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', WINDOW_WIDTH * (WINDOW_HEIGHT - 3) / 2, pos, &dw);
	gotoxy(0, pos.Y + 2);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	cout << "                                 ■         ■■    ■■■■  ■■■■" << endl
		<< "                                 ■       ■    ■  ■        ■" << endl
		<< "                                 ■       ■    ■  ■■■■  ■■■■" << endl
		<< "                                 ■       ■    ■        ■  ■" << endl
		<< "                                 ■■■■   ■■    ■■■■  ■■■■";
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
}

// 0~MAXIMUM_LEVEL(현재는 20) 사이에 속하는 무작위 수 20개를 받아 배열크기 지정
// 배열의 크기 = 문제 화살표의 개수
// sort 사용하여 배열 크기를 오름차순으로 정렬
// ↑↓←→ 중 하나를 무작위로 각 배열에 저장하여 문제 생성
void makeArrow() {
	srand((unsigned int)time(NULL));
	int n;
	int temp[MAXIMUM_LEVEL];

	for (int i = 0; i < MAXIMUM_LEVEL; i++) {
		n = rand() % MAXIMUM_LEVEL + 1;
		temp[i] = n;
	}
	sort(temp, temp + MAXIMUM_LEVEL);

	for (int i = 0; i < MAXIMUM_LEVEL; i++) {
		for (int j = 0; j < temp[i]; j++) {
			n = rand() % 4;
			switch (n) {
			case 0:
				questionvec[i].push_back(UP);
				break;
			case 1:
				questionvec[i].push_back(DOWN);
				break;
			case 2:
				questionvec[i].push_back(LEFT);
				break;
			case 3:
				questionvec[i].push_back(RIGHT);
				break;
			}
		}

	}

}

// 플레이어 level 값에 따라 문제 표시
void printArrow(Player& p) {
	if (p.isWin()) return;
	vector<int>::const_iterator it;
	int index = p.getLevel() - 1;
	string questionStr = p.getQstr();
	for (it = questionvec[index].begin(); it != questionvec[index].end(); it++) {
		switch (*it) {
		case UP:
			questionStr += "↑ ";
			break;
		case DOWN:
			questionStr += "↓ ";
			break;
		case LEFT:
			questionStr += "← ";
			break;
		case RIGHT:
			questionStr += "→ ";
			break;
		}
	}
	gotoxy(p.getStart().X + 20, p.getStart().Y + 3);
	cout << questionStr;

}

void drawMap() {
	gotoxy(0, 0);
	for (int i = 0; i < WINDOW_WIDTH / 2; i++) {
		cout << "▦";
	}
	gotoxy(0, WINDOW_HEIGHT - 1);
	for (int i = 0; i < WINDOW_WIDTH / 2; i++) {
		cout << "▦";
	}

	gotoxy(0, (WINDOW_HEIGHT - 1) / 2);
	for (int i = 0; i < WINDOW_WIDTH; i++) {
		cout << "=";
	}

	gotoxy(0, 4);
	cout << "■■■    ■■" << endl
		<< "■   ■ ■■■" << endl
		<< "■■■    ■■" << endl
		<< "■        ■■" << endl
		<< "■        ■■";

	gotoxy(0, 14);
	cout << "■■■  ■■■" << endl
		<< "■   ■     ■" << endl
		<< "■■■  ■■■" << endl
		<< "■      ■" << endl
		<< "■      ■■■";

	gotoxy(WINDOW_WIDTH - 10, 7);
	cout << "↑";
	gotoxy(WINDOW_WIDTH - 12, 8);
	cout << "←";
	gotoxy(WINDOW_WIDTH - 10, 8);
	cout << "↓";
	gotoxy(WINDOW_WIDTH - 8, 8);
	cout << "→";

	gotoxy(WINDOW_WIDTH - 10, 17);
	cout << "W";
	gotoxy(WINDOW_WIDTH - 12, 18);
	cout << "A";
	gotoxy(WINDOW_WIDTH - 10, 18);
	cout << "S";
	gotoxy(WINDOW_WIDTH - 8, 18);
	cout << "D";

	gotoxy(16, 5);
	cout << ">>>";
	gotoxy(16, 15);
	cout << ">>>";
}

// 플레이어 상태 값에 따라 life 정보 표시
void drawInfo(const Player& p) {
	gotoxy(p.getStart().X, p.getStart().Y + 1);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
	for (int i = 0; i < p.getLife(); i++) {
		cout << "♥";
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for (int i = 0; i < 3 - p.getLife(); i++) {
		cout << "♡";
	}
	gotoxy(WINDOW_WIDTH - 20, p.getStart().Y + 1);
	cout << "Level : " << p.getLevel() << " / " << MAXIMUM_LEVEL;

}

// 플레이어의 한 입력에 대한 정오 판정
void checkAnswer(Player& p) {
	int index = p.getLevel() - 1;
	int inputNum = p.getNumOfInput();
	vector<int> currentInput = p.getAvec();

	if (questionvec[index].size() <= inputNum) return;
	if (questionvec[index][inputNum] != currentInput[inputNum]) p.minusLife();
	p.isPressed();
}

// 사용자의 방향키 입력수가 현재 문제보다 많아지는 상황
bool isNext(const Player& p) {
	int index = p.getLevel() - 1;
	int inputNum = p.getNumOfInput();
	return questionvec[index].size() <= inputNum;
}

// 입력 칸 비우고 다음 단계 설정
void setNext(Player& p) {
	DWORD dw;
	COORD pos = { p.getStart().X + 20, p.getStart().Y + 3 };
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', MAXIMUM_LEVEL * 3, pos, &dw);
	pos.Y++;
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), ' ', MAXIMUM_LEVEL * 3, pos, &dw);
	p.clear();
	p.nextLevel();
}

// 승패여부를 확인하여 게임 상태 값을 가져옴
GAME_STATE getState(const Player& p1, const Player& p2) {
	if (p1.isWin()) return P1WIN;
	if (p2.isWin()) return P2WIN;
	if (p1.isOver()) return P1OVER;
	if (p2.isOver()) return P2OVER;
	return ONGOING;
}

void gameScreen() {
	system("cls");
	GAME_STATE state = ONGOING;
	Player p1, p2(1);

	int input = 0;
	bool valid;

	printTimer(3);
	PlaySound(TEXT("8BitAdventure.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP | SND_NODEFAULT);
	drawMap();
	drawInfo(p1);
	drawInfo(p2);
	makeArrow();
	printArrow(p1);
	printArrow(p2);
	FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE)); // Sleep 이전 입력 제거

	while (state == ONGOING) {
		input = 0;
		valid = true;
		if (_kbhit()) {
			input = _getch();
			if ((input == ARROW_NUM) && !p1.isOver()) {
				switch (_getch()) {
				case UP:
					p1.getAvec().push_back(UP);
					p1.getAstr() += "↑ ";
					break;
				case DOWN:
					p1.getAvec().push_back(DOWN);
					p1.getAstr() += "↓ ";
					break;
				case LEFT:
					p1.getAvec().push_back(LEFT);
					p1.getAstr() += "← ";
					break;
				case RIGHT:
					p1.getAvec().push_back(RIGHT);
					p1.getAstr() += "→ ";
					break;
				default:
					valid = false;
					break;
				}
				// ↑↓←→만을 유효값으로 판정하고 문제 화살표 개수 == 유효 입력수이면 다음 문제 출력
				if (valid) {
					gotoxy(p1.getStart().X + 20, p1.getStart().Y + 4);
					cout << p1.getAstr();
					checkAnswer(p1);
				}
			}

			if (!p2.isOver()) {
				switch (input) {
				case 'W':
				case 'w':
					p2.getAvec().push_back(UP);
					p2.getAstr() += "↑ ";
					break;
				case 'S':
				case 's':
					p2.getAvec().push_back(DOWN);
					p2.getAstr() += "↓ ";
					break;
				case 'A':
				case 'a':
					p2.getAvec().push_back(LEFT);
					p2.getAstr() += "← ";
					break;
				case 'D':
				case 'd':
					p2.getAvec().push_back(RIGHT);
					p2.getAstr() += "→ ";
					break;
				default:
					valid = false;
					break;
				}
				// wasd(WASD)만을 유효값으로 판정
				if (valid) {
					gotoxy(p2.getStart().X + 20, p2.getStart().Y + 4);
					cout << p2.getAstr();
					checkAnswer(p2);
				}
			}
			if (isNext(p1)) {
				setNext(p1);
				printArrow(p1);
			}
			if (isNext(p2)) {
				setNext(p2);
				printArrow(p2);
			}
			drawInfo(p1);
			drawInfo(p2);
			// 플레이어 진행 상황에 따른 게임상태 업데이트
			state = getState(p1, p2);
			switch (state) {
			case ONGOING:
				break;
			case P1WIN:
				gameWin(p1);
				break;
			case P2WIN:
				gameWin(p2);
				break;
			case P1OVER:
				gameOver(p1);
				break;
			case P2OVER:
				gameOver(p2);
				break;
			}

		}
	}
	PlaySound(NULL, NULL, 0);
	// 승패 결과 확인
	PlaySound(TEXT("win.wav"), NULL, SND_NODEFAULT | SND_FILENAME);
	PlaySound(NULL, NULL, 0);
	Sleep(3000);
}