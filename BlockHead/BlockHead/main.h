#pragma once
#include <Windows.h>
#include <tchar.h>
#include <WindowsX.h>
#include <vector>
#include <algorithm>
#include <string>
#include <CommCtrl.h>
#include <fstream>
#include <locale>
#include "resource.h"

#pragma comment(lib, "comctl32")

#define LetterButton WM_USER
#define FieldButton (WM_USER + 50)
#define ID_SEND 136
#define ID_CLEAR 137
#define ID_PASS 138

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMessage, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK DlgProc(HWND hDlg, UINT uMessage, WPARAM wParam, LPARAM lParam);

void OnDestroy(HWND hwnd);
BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void OnTimer(HWND hwnd, UINT id);

BOOL OnInit(HWND hDlg, HWND hwndFocus, LPARAM lParam);
void OnCommandDlg(HWND hDlg, int id, HWND hwndCtl, UINT codeNotify);

bool StartGame();
bool StopGame();
bool ResetTimer();
bool SaveGame();
bool bWritePlayerInfo(std::basic_fstream<WCHAR> &fOut, HWND hWords, int nScore, int nPassCount);
bool LoadGame();
bool bReadPlayerData(std::basic_fstream<WCHAR> &fIn, HWND hWords, int &nScore, int &nPassCount);