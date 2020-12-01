#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
using namespace std;

#define BOARD_SIZE 12 // Kích thức ma trận bàn cờ
#define LEFT 3 // Tọa độ trái màn hình bàn cờ
#define TOP 1 // Tọa độ trên màn hình bàn cờ
// Khai báo kiểu dữ liệu
struct _POINT { int x, y, c; }; // x: tọa độ dòng, y: tọa độ cột, c: đánh dấu
_POINT _A[BOARD_SIZE][BOARD_SIZE]; //Ma trận bàn cờ
bool _TURN; //true là lượt người thứ nhất và false là lượt người thứ hai
int _COMMAND; // Biến nhận giá trị phím người dùng nhập
int _X, _Y; //Tọa độ hiện hành trên màn hình bàn cờ


void FixConsoleWindow();
void GotoXY(int x, int y);
void DrawBoard(int pSize);
void ResetData();
int ProcessFinish(int pWhoWin);
int AskContinue();
void StartGame();
void GabageCollect();
void ExitGame();
int CheckBoard(int pX, int pY);
void MoveRight();
void MoveLeft();
void MoveDown();

void MoveUp();
int TestBoard();