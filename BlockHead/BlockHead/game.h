#pragma once
#include <time.h>
#include <fstream>
#include "main.h"

typedef std::vector<std::wstring> DIC;

enum TURN{Player1, Player2};

struct BESTWORD
{
	std::wstring word;
	unsigned int size;
	int xPos;
	int yPos;
	WCHAR letter;
};

bool bFillingDic(DIC &dic);
bool bInitField(WCHAR(&field)[5][5], DIC &dic, DIC &usedWord);
bool bShowField(const WCHAR (&field)[5][5], HWND(&hLetters)[5][5]);
void flagReset(bool (&flag)[5][5]);
void flagReset(bool **flag, int i = 5, int j = 5);
bool bLetterChoose(std::wstring &lpLetter, const int &id, bool &isAdded);
bool bEnterWord(const int &id, int &curI, int &curJ, const HWND &hSend, BESTWORD &word, WCHAR (&field)[5][5], bool &isAdded, bool &isAddedUsed, std::wstring &lpLetter, bool (&flag)[5][5], const HWND (&hField)[5][5]);
bool bSendWord(DIC &dic, DIC &usedWords, BESTWORD &word, WCHAR (&field)[5][5], int &nScore, const HWND &hScore, const HWND &hInfo, std::wstring lpName, const HWND &hWnd, TURN &turn, int &lastI, int &lastJ);
bool bResetTurn(bool &isAdded, bool &isAddedUsed, int &curI, int &curJ, int &lastI, int &lastJ, std::wstring &lpLetter, const HWND &hSend, const HWND (&field)[5][5], bool isCPU = false);
bool bIsEnd(const WCHAR (&field)[5][5], const int &nP1Score, const int &nP2Score, HWND hWnd, bool bNeedToCheck = true);
bool bCPUTurn(WCHAR (&field)[5][5], BESTWORD &word, const DIC dic, DIC &usedWords, int &nScore, const HWND &hWords, const HWND &hInfo, const HWND (&hField)[5][5], std::wstring lpName, const HWND &hWnd);
bool SearchForward(BESTWORD &findWord, BESTWORD &result, const std::wstring &word, const WCHAR (&field)[5][5], int xPos, int yPos, bool isAdd = false, int letterPos = 0, std::wstring curWord = L"", bool **flag = NULL, int xAdd = -1, int yAdd = -1, WCHAR lAdd = 0);
bool SearchBack(BESTWORD &findWord, BESTWORD &result, const std::wstring &word, const WCHAR (&field)[5][5], int xPos, int yPos);
bool bPassCount(int &nPassCount);
