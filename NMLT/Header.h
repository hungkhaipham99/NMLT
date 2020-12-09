#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>
#include<iostream>
#include <fstream>
using namespace std;

#define BOARD_SIZE 12 // Kích thức ma trận bàn cờ
#define LEFT 3 // Tọa độ trái màn hình bàn cờ
#define TOP 1 // Tọa độ trên màn hình bàn cờ
// Khai báo kiểu dữ liệu
struct _POINT { int x, y, c; }; // x: tọa độ dòng, y: tọa độ cột, c: đánh dấu
_POINT _A[BOARD_SIZE][BOARD_SIZE]; //Ma trận bàn cờ
_POINT New;
bool _TURN; //true là lượt người thứ nhất và false là lượt người thứ hai
int _COMMAND; // Biến nhận giá trị phím người dùng nhập
int _X, _Y; //Tọa độ hiện hành trên màn hình bàn cờ
int _COUNT1 = 0;//Dem nuoc co nguoi choi 1;
int _COUNT2 = 0;//Dem nuoc co nguoi choi 2;
int Win1 = 0;//So lan thang cua nguoi choi 1
int Win2 = 0;//So lan thang cua nguoi choi 2
int flagLoad = 0;//Kiem tra game moi hay game cu
int flagWin = 0;//Thay doi luu tru khi thang game
string Name;
int ViTriIn = 13;


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
bool IsWin();
void SaveGame(string a);
void LoadGame(string a);
void GtxtColor(int x);
void printMenu(int selection);
int selectMenu();
int NewGame();
int OldGame();
void Win_Lose();
int AskSave();


void Online();