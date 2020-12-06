#include "Header.h"


void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
}

void GotoXY(int x, int y) {

	COORD coord;

	coord.X = x;

	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

}


bool IsWin() {
	int count = 0;
	int t = New.x - 4, k = New.y - 4;
	if (t < 0)t = 0;
	if (k < 0)k = 0;
	for (int i = t; i <= New.x + 4; i++)
	{
		if (_A[i][New.y].c == New.c) count += 1;
		else
		{
			count = 0;
		}
		if (count == 5 && _A[i + 1][New.y].c != New.c && (_A[i - 5][New.y].c == 0 || _A[i + 1][New.y].c == 0)) return true;
	}

	for (int i = k; i <= New.y + 4; i++)
	{

		if (_A[New.x][i].c == New.c) count += 1;
		else
		{
			count = 0;
		}
		if (count == 5 && _A[New.x][i + 1].c != New.c && (_A[New.x][i - 5].c == 0 || _A[New.x][i + 1].c == 0)) return true;
	}

	for (int i = -4; i <=4; i++)
	{
		if (_A[New.x+i][New.y+i].c == New.c) count += 1;
		else
		{
			count = 0;
		}
		if (count == 5 && _A[New.x + i+1][New.y + i+1].c != New.c && (_A[New.x + i-5][New.y + i-5].c == 0 || _A[New.x + i+1][New.y + i+1].c == 0)) return true;
	}

	for (int i = 4; i >=-4; i--)
	{
		if (_A[New.x + i][New.y - i].c == New.c) count += 1;
		else
		{
			count = 0;
		}
		if (count == 5 && _A[New.x + i - 1][New.y - i + 1].c != New.c && _A[New.x + i + 5][New.y - i - 5].c!=New.c&&(_A[New.x + i + 5][New.y - i - 5].c == 0 || _A[New.x + i - 1][New.y - i + 1].c == 0)) return true;
	}
	return false;
}

void DrawBoard(int pSize) {

	for (int i = 0; i <= pSize; i++) {

		for (int j = 0; j <= pSize; j++) {

			GotoXY(LEFT + 4 * i, TOP + 2 * j);

			printf(".");

		}
	}
}

void ResetData() {
	for (int i = 0; i < BOARD_SIZE; i++) {

		for (int j = 0; j < BOARD_SIZE; j++) {

			_A[i][j].x = 4 * j + LEFT + 2; // Trùng với hoành độ màn hình bàn cờ

			_A[i][j].y = 2 * i + TOP + 1; // Trùng với tung độ màn hình bàn cờ

			_A[i][j].c = 0; // 0 nghĩa là chưa ai đánh dấu, nếu đánh dấu phải theo quy
			//định như sau: -1 là lượt true đánh, 1 là lượt false đánh
		}

	}
	_TURN = true; _COMMAND = -1; // Gán lượt và phím mặc định
	_X = _A[0][0].x; _Y = _A[0][0].y; // Thiết lập lại tọa độ hiện hành ban đầu

}


int ProcessFinish(int pWhoWin) {

	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 2); // Nhảy tới vị trí
	 // thích hợp để in chuỗi thắng/thua/hòa

	switch (pWhoWin) {

	case -1:
		Win1++;
		printf("Nguoi choi %d da thang va nguoi choi %d da thua\n", true, false);
		flagLoad = 0;
		flagWin = 1;
		SaveGame(Name);
		break;

	case 1:
		Win2++;
		printf("Nguoi choi %d da thang va nguoi choi %d da thua\n", false, true);
		flagLoad = 0;
		flagWin = 1;
		SaveGame(Name);
		break;
	case 0:
		printf("Nguoi choi %d da hoa nguoi choi %d\n", false, true);
		break;
	case 2:
		_TURN = !_TURN; // Đổi lượt nếu không có gì xảy ra

	}
	GotoXY(_X, _Y); // Trả về vị trí hiện hành của con trỏ màn hình bàn cờ
	return pWhoWin;

}

int AskContinue() {
	GotoXY(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 4);
	printf("Nhan 'y/n' de tiep tuc/dung: ");
	return toupper(_getch());
}

void StartGame() {

	system("cls");

	ResetData(); // Khởi tạo dữ liệu gốc

	DrawBoard(BOARD_SIZE); // Vẽ màn hình game
	//LoadGame("Game");
}

void GabageCollect()

{

	// Dọn dẹp tài nguyên nếu có khai báo con trỏ

}



//Hàm thoát game (hàm nhóm Control)

void ExitGame() {

	system("cls");

	GabageCollect();
	//SaveGame("Game");
	//Có thể lưu game trước khi exit

}

int TestBoard()
{	
	if (_COUNT1+ _COUNT2==BOARD_SIZE*BOARD_SIZE) {
		return 0;
	}
	else
	{
		if (IsWin() == true)
		{	
			return (_TURN == true ? -1 : 1);
		}
		else return 2;
	}
}
//int TestBoard()
//{
//	
//		if (<Ma trận đầy>) return 0; // Hòa
//	
//		else {
//			
//				if (<tồn tại điều kiện thắng theo luật caro>)
//					
//					return (_TURN == true ? -1 : 1); // -1 nghĩa là lượt ‘true’ thắng
//				Else
//			
//				return 2; // 2 nghĩa là chưa ai thắng
//			
//		}
//}

int CheckBoard(int pX, int pY) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0) {
				if (_TURN == true) _A[i][j].c = -1; // Nếu lượt hiện hành là true thì c = -1
				else _A[i][j].c = 1; // Nếu lượt hiện hành là false thì c = 1
				New.c = _A[i][j].c;
				New.x = i;
				New.y = j;
				return _A[i][j].c;

			}

		}

	}
	return 0;
}


void MoveRight() {

	if (_X < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x)

	{

		_X += 4;

		GotoXY(_X, _Y);

	}

}

void MoveLeft() {
	if (_X > _A[0][0].x) {
		_X -= 4;
		GotoXY(_X, _Y);

	}

}
void MoveDown() {
	if (_Y < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y)
	{
		_Y += 2;
		GotoXY(_X, _Y);
	}
}

void MoveUp() {
	if (_Y > _A[0][0].y) {
		_Y -= 2;
		GotoXY(_X, _Y);

	}

}
void SaveGame(string name)
{
	fstream f;
	f.open(name + ".txt", ios::out);
	f.write(reinterpret_cast<char*>(&Win1), sizeof(int));
	f.write(reinterpret_cast<char*>(&Win2), sizeof(int));
	if (flagWin != 1)
	{
		f.write(reinterpret_cast<char*>(&_TURN), sizeof(bool));
		for (int i = 0; i < BOARD_SIZE; i++) {
			for (int j = 0; j < BOARD_SIZE; j++) {
				f.write(reinterpret_cast<char*>(&_A[i][j]), sizeof(_POINT));

			}
		}
	}
	f.close();
	GotoXY(52, ViTriIn);
	cout << "Da luu";
}

void LoadGame(string name)
{
	fstream f;
	f.open(name + ".txt", ios::in);
	f.read(reinterpret_cast<char*>(&Win1), sizeof(int));
	f.read(reinterpret_cast<char*>(&Win2), sizeof(int));
	f.read(reinterpret_cast<char*>(&_TURN), sizeof(bool));
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			f.read(reinterpret_cast<char*>(&_A[i][j]), sizeof(_POINT));
			GotoXY(_A[i][j].x, _A[i][j].y);
			if (_A[i][j].c == -1)
			{
				printf("X");
			}
			if (_A[i][j].c == 1)
			{
				printf("O");
			}
		}
	}
	f.close();
}

void GtxtColor(int x) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);
}

void printMenu(int selection)
{
	switch (selection)
	{
	case 1:
		GotoXY(52, 18);
		GtxtColor(12);
		cout << "NEW GAME";
		GotoXY(0, 19);
		GtxtColor(11);
		cout << "\t\t\t\t\t*\t    LOAD GAME             *";
		GotoXY(0, 20);
		GtxtColor(11);
		cout << "\t\t\t\t\t*\t    HELP                  *";
		GotoXY(0, 21);
		GtxtColor(11);
		cout << "\t\t\t\t\t*\t    ABOUT                 *";
		GotoXY(0, 22);
		GtxtColor(11);
		cout << "\t\t\t\t\t*\t    EXIT GAME             *";
		break;
	case 2:
		GotoXY(0, 18);
		GtxtColor(11);
		cout << "\t\t\t\t\t*\t    NEW GAME              *";
		GotoXY(52, 19);
		GtxtColor(12);
		cout << "LOAD GAME";
		GotoXY(0, 20);
		GtxtColor(11);
		cout << "\t\t\t\t\t*\t    HELP                  *";
		GotoXY(0, 24);
		break;
	case 3:
		GotoXY(0, 19);
		GtxtColor(11);
		cout << "\t\t\t\t\t*\t    LOAD GAME             *";
		GotoXY(52, 20);
		GtxtColor(12);
		cout << "HELP";
		GotoXY(0, 21);
		GtxtColor(11);
		cout << "\t\t\t\t\t*\t    ABOUT                 *";
		GotoXY(0, 24);
		break;
	case 4:
		GotoXY(0, 20);
		GtxtColor(11);
		cout << "\t\t\t\t\t*\t    HELP                  *";
		GotoXY(52, 21);
		GtxtColor(12);
		cout << "ABOUT";
		GotoXY(0, 22);
		GtxtColor(11);
		cout << "\t\t\t\t\t*\t    EXIT GAME             *";
		GotoXY(0, 24);
		break;
	case 5:
		GotoXY(0, 21);
		GtxtColor(11);
		cout << "\t\t\t\t\t*\t    ABOUT                 *";
		GotoXY(52, 22);
		GtxtColor(12);
		cout << "EXIT GAME";
		GotoXY(0, 18);
		GtxtColor(11);
		cout << "\t\t\t\t\t*\t    NEW GAME              *";
		GotoXY(0, 24);
		break;
	}
}

int selectMenu()
{
	int selection = 1;
	int choose = 0;
	printMenu(selection);
	while (1)
	{
		int move = _getch();
		move = toupper(move);
		if (move == 'S' || move == 80)
		{
			switch (selection)
			{
			case 1: case 2: case 3: case 4:
				selection++;
				break;
			case 5:
				selection = 1;
				break;
			}
			
			printMenu(selection);

		}
		if (move == 'W' || move == 72)
		{
			switch (selection)
			{
			case 1:
				selection = 5;
				break;
			case 2: case 3: case 4: case 5:
				selection--;
				break;
			}
			printMenu(selection);
		}
		if (move == 13)
			return selection;
	}
}

int NewGame()
{
	FixConsoleWindow();
	StartGame();
	bool validEnter = true;
	while (1)

	{

		_COMMAND = toupper(_getch());
		
		if (_COMMAND == 27)

		{
			ExitGame();

			return 0;

		}
		else {
			if (_COMMAND == 'A') MoveLeft();
			else if (_COMMAND == 'W') MoveUp();
			else if (_COMMAND == 'S') MoveDown();
			else if (_COMMAND == 'D') MoveRight();
			else if (_COMMAND == 'L')
			{
				if (flagLoad != 1) {
					GotoXY(52, ViTriIn);
					ViTriIn++;
					cout << "Nhap ten tap tin muon luu: ";
					cin >> Name;
				}
				SaveGame(Name);
			}
			else if (_COMMAND == 'T' || flagLoad==1) {
				GotoXY(52, ViTriIn);
				ViTriIn++;
				cout << "Nhap ten tap tin muon tai len: ";
				cin >> Name;
				LoadGame(Name);
				flagLoad = 1;
				GotoXY(52, ViTriIn);
				cout << "Da tai len";
			}
			else if (_COMMAND == 13) {// Người dùng đánh dấu trên màn hình bàn cờ
				switch (CheckBoard(_X, _Y)) {

				case -1:
					printf("X"); _COUNT1++;
					//cout << _X<<":" << _Y;
					break;

				case 1:
					printf("O"); _COUNT2++; break;
				case 0: validEnter = false; // Khi đánh vào ô đã đánh rồi

				}
				// Tiếp theo là kiểm tra và xử lý thắng/thua/hòa/tiếp tục
				if (validEnter == true) {

					switch (ProcessFinish(TestBoard())) {

					case -1: case 1: case 0:
						if (AskContinue() != 'Y') {

							ExitGame();
							return 0;

						}

						else StartGame();

					}

				}
				validEnter = true; // Mở khóa

			}

		}

	}
}

int OldGame()
{
	FixConsoleWindow();
	StartGame();
	bool validEnter = true;
	GotoXY(52, ViTriIn);
	ViTriIn++;
	cout << "Nhap ten tap tin muon tai len: ";
	cin >> Name;
	LoadGame(Name);
	flagLoad = 1;
	GotoXY(52, ViTriIn);
	cout << "Da tai len";
	while (1)

	{

		_COMMAND = toupper(_getch());
		
		if (_COMMAND == 27)

		{
			ExitGame();

			return 0;

		}
		else {
			if (_COMMAND == 'A') MoveLeft();
			else if (_COMMAND == 'W') MoveUp();
			else if (_COMMAND == 'S') MoveDown();
			else if (_COMMAND == 'D') MoveRight();
			else if (_COMMAND == 'L')
			{
				if (flagLoad != 1) {
					GotoXY(52, ViTriIn);
					ViTriIn++;
					cout << "Nhap ten tap tin muon luu: ";
					cin >> Name;
				}
				SaveGame(Name);
			}
			else if (_COMMAND == 'T') {
				GotoXY(52, ViTriIn);
				ViTriIn++;
				cout << "Nhap ten tap tin muon tai len: ";
				cin >> Name;
				LoadGame(Name);
				flagLoad = 1;
				GotoXY(52, ViTriIn);
				cout << "Da tai len";
			}
			else if (_COMMAND == 13) {// Người dùng đánh dấu trên màn hình bàn cờ
				switch (CheckBoard(_X, _Y)) {

				case -1:
					printf("X"); _COUNT1++;
					//cout << _X<<":" << _Y;
					break;

				case 1:
					printf("O"); _COUNT2++; break;
				case 0: validEnter = false; // Khi đánh vào ô đã đánh rồi

				}
				// Tiếp theo là kiểm tra và xử lý thắng/thua/hòa/tiếp tục
				if (validEnter == true) {

					switch (ProcessFinish(TestBoard())) {

					case -1: case 1: case 0:
						if (AskContinue() != 'Y') {

							ExitGame();
							return 0;

						}

						else StartGame();

					}

				}
				validEnter = true; // Mở khóa

			}

		}

	}
}

int main()
{
	while(1){
		FixConsoleWindow();
		GotoXY(0, 18);
		GtxtColor(11);
		cout << "\t\t\t\t\t*\t    NEW GAME              *" << endl;
		cout << "\t\t\t\t\t*\t    LOAD GAME             *" << endl;
		cout << "\t\t\t\t\t*\t    HELP                  *" << endl;
		cout << "\t\t\t\t\t*\t    ABOUT                 *" << endl;
		cout << "\t\t\t\t\t*\t    EXIT GAME             *" << endl;
		cout << "\t\t\t\t\t***********************************" << endl;
		int x = selectMenu();
		switch (x)
		{
		case 1:
			NewGame();
			break;
		case 2:
			OldGame();
			break;
		case 3:
			system("cls");
			GtxtColor(14);
			cout << "\t========TRONG GIAO DIEN TRO CHOI========" << endl;
			GtxtColor(11);
			cout << "\t1. Su dung cac phim W, A, S, D hoac cac phim mui ten de di chuyen." << endl;
			GtxtColor(14);
			cout << "\t2. Su dung phim Space hoac Enter de thuc hien 1 nuoc danh." << endl;
			GtxtColor(11);
			cout << "\t3. Su dung ESC de thoat khoi tro choi." << endl;
			GtxtColor(14);
			cout << "\t******************************************" << endl;
			system("pause");
			system("cls");
			break;
		case 4:
			break;
		case 5:
			system("cls");
			break;
		default:
			break;
		}
		if (x == 5) return 0;
	}
}



