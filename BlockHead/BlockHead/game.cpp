#include "game.h"

bool bFillingDic(DIC &dic)
{
	std::fstream f("Lib.RUS");
	if (!f.is_open())
		return false;
	int n = 0;
	char c[20];
	while (!f.eof())
	{
		f.getline(c,20);
		n++;
	}
	f.clear();
	f.seekg(0, std::ios::beg);
	std::string s;
	wchar_t *w;
	int i;
	while (!f.eof())
	{
		f.getline(c,20);
		i = MultiByteToWideChar(CP_ACP, 0, c, -1, 0, 0);
		if (i == 1)
			continue;
		w = new wchar_t[i];
		MultiByteToWideChar(CP_ACP, 0, c, -1, w, i);
		dic.push_back(w);
		delete w;
	}
	f.close();
	return true;
}
bool bInitField(WCHAR(&field)[5][5], DIC &dic, DIC &usedWords)
{
	for (unsigned int i = 0, j = 0, k = rand()%1460; i < dic.size(); i++)
		if (dic[i].length() == 5)
			if (j == k)
			{
				for (int l = 0; l < 5; l++)
					for (int m = 0; m < 5; m++)
					{
						if (l == 2)
							field[l][m] = dic[i][m];
						else
							field[l][m] = 0;
					}
				usedWords.push_back(dic[i]);
				break;
			}
			else
				j++;

	return true;
}
bool bShowField(const WCHAR(&field)[5][5], HWND(&hField)[5][5])
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (field[i][j] != 0)
				SendMessage(hField[i][j], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1 + field[i][j] - L'А')));
			else
			{
				SendMessage(hField[i][j], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP33)));
			}
		}
	}
	return true;
}
void flagReset(bool (&flag)[5][5])
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			flag[i][j] = false;
}
void flagReset(bool **flag, int i, int j)
{
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			flag[i][j] = false;
}
bool bLetterChoose(std::wstring &lpLetter, const int &id, bool &isAdded)
{
	lpLetter = L"А";
	lpLetter[0] += id - 1024;
	isAdded = true;
	return true;
}
bool bEnterWord(const int &id, int &curI, int &curJ, const HWND &hSend, BESTWORD &word, WCHAR (&field)[5][5], bool &isAdded, bool &isAddedUsed, std::wstring &lpLetter, bool (&flag)[5][5], const HWND (&hField)[5][5])
{
	int i = (id - FieldButton) / 5;
	int j = (id - FieldButton) % 5;
	if (curI == -1 && curJ == -1)
	{
		curI = i;
		curJ = j;
	}
	else
	{
		if ((((i - curI) > 1)||((curI - i) > 1) && curJ == j) || (curI == i && ((curJ - j) > 1)||((j - curJ) > 1))) 
			return false;
	}
	int n = GetWindowTextLength(hSend);
	WCHAR *buffer = new WCHAR[n + 1];
	GetWindowText(hSend, buffer, n + 1);
	word.word = buffer;
	delete buffer;
	if (field[i][j] == 0 && isAdded && !isAddedUsed)
	{
		if ((i > 0 && field[i - 1][j] != 0) || (i < 4 && field[i + 1][j] != 0) || (j > 0 && field[i][j - 1] != 0) || (j < 4 && field[i][j + 1] != 0))
		{
			word.word += lpLetter;
			isAddedUsed = true;
			flag[i][j] = true;
			SendMessage(hField[i][j], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1 + (lpLetter[0] - L'А'))));
			word.letter = lpLetter[0];
			word.xPos = i;
			word.yPos = j;
		}
	}
	if (field[i][j] != 0 && isAdded && flag[i][j] == false)
	{
		word.word += field[i][j];
		flag[i][j] = true;
	}
	curI = i;
	curJ = j;
	SetWindowText(hSend, word.word.c_str());
	flagReset(flag);
	return true;
}
bool bSendWord(DIC &dic, DIC &usedWords, BESTWORD &word, WCHAR (&field)[5][5], int &nScore, const HWND &hWords, const HWND &hInfo, std::wstring lpName, const HWND &hWnd, TURN &turn, int &lastI, int &lastJ)
{
	bool bFound = false;
	for (int i = 0; i < (int)usedWords.size(); i++)
		if (usedWords[i] == word.word)
		{
			MessageBox(hWnd, _T("Слово уже использовалось."), _T("Ошибка"), 0);
			return false;
		}
	for (int i = 0; i < (int)dic.size(); i++)
			if (dic[i] == word.word)
			{
				field[word.xPos][word.yPos] = word.letter;
				nScore += word.word.length();
				TCHAR *buffer = new TCHAR[10];
				_itot(nScore, buffer, 10);
				lpName += buffer;
				delete [] buffer;
				SetWindowText(hInfo, lpName.c_str());
				SendMessage(hWords, LB_ADDSTRING, 0, (LPARAM)word.word.c_str());
				turn = (turn == Player1)?Player2:Player1;
				bFound = true;
				lastI = -1;
				lastJ = -1;
				usedWords.push_back(word.word);
				break;
			}
	if (!bFound)
	{
		int nResult;
		nResult = MessageBox(hWnd, _T("Нет такого слова в словаре\nДобавить?"), _T("Ошибка"), MB_YESNO);
		switch (nResult)
		{
		case IDNO:
			return false;
			break;
		case IDYES:
			dic.push_back(word.word);
			bSendWord(dic, usedWords, word, field, nScore, hWords, hInfo, lpName, hWnd, turn, lastI, lastJ);
			break;
		}
	}
	return true;
}
bool bResetTurn(bool &isAdded, bool &isAddedUsed, int &curI, int &curJ, int &lastI, int &lastJ, std::wstring &lpLetter, const HWND &hSend, const HWND (&hField)[5][5], bool isCPU)
{
	isAdded = false;
	isAddedUsed = false;
	curI = -1;
	curJ = -1;
	lpLetter = L"А";
	SetWindowText(hSend, L"");
	if (lastI != -1 && lastJ != -1 && isCPU == false)
	{
		SendMessage(hField[lastI][lastJ], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP33)));
		lastI = -1;
		lastJ = -1;
	}
	return true;
}
bool bIsEnd(const WCHAR (&field)[5][5], const int &nP1Score, const int &nP2Score, HWND hWnd, bool bNeedToCheck)
{
	if (bNeedToCheck == true)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (field[i][j] == 0)
					return false;
			}
		}
	}
	if (nP1Score > nP2Score)
	{
		MessageBox(0, _T("Победил игрок №1"), 0, 0);
	}
	else if (nP1Score < nP2Score)
	{
		MessageBox(0, _T("Победил игрок №2"), 0, 0);
	}
	else if (nP1Score == nP2Score)
	{
		MessageBox(0, _T("Ничья!"), 0, 0);
	}
	return true;
}
bool bCPUTurn(WCHAR (&field)[5][5], BESTWORD &word, const DIC dic, DIC &usedWords, int &nScore, const HWND &hWords, const HWND &hInfo, const HWND (&hField)[5][5], std::wstring lpName, const HWND &hWnd)
{
	memset(&word, 0, sizeof(BESTWORD));
	BESTWORD temp;
	memset(&temp, 0, sizeof(BESTWORD));
	bool bWordUsed = false;
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++)
			if (field[i][j] != 0)
				for (unsigned int k = 0; k < dic.size(); k++)
				{
					if (dic[k].length() <= word.size)
						continue;
					for (unsigned int m = 0; m < usedWords.size(); m++)
					{
						if (dic[k] == usedWords[m])
						{
							bWordUsed = true;
						}
					}
					if (bWordUsed)
					{
						bWordUsed = false;
						continue;
					}
					for (unsigned int l = 0; l < dic[k].length(); l++)
						if (field[i][j] == dic[k][l])
						{
							if (l == 0)
								SearchForward(word, temp, dic[k], field, i, j);
							else if (l == 1)
								SearchBack(word, temp, dic[k], field, i, j);
						}
				}
	if (word.size != 0)
	{
		field[word.xPos][word.yPos] = word.letter;
		nScore += word.word.length();
		TCHAR *buffer = new TCHAR[10];
		_itot(nScore, buffer, 10);
		lpName += buffer;
		delete [] buffer;
		SetWindowText(hInfo, lpName.c_str());
		SendMessage(hWords, LB_ADDSTRING, 0, (LPARAM)word.word.c_str());
		SendMessage(hField[word.xPos][word.yPos], BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)LoadBitmap(GetModuleHandle(0), MAKEINTRESOURCE(IDB_BITMAP1 + (word.letter - L'А'))));
		usedWords.push_back(word.word);
		return true;
	}
	return false;
}
bool SearchForward(BESTWORD &findWord, BESTWORD &result, const std::wstring &word, const WCHAR (&field)[5][5], int xPos, int yPos, bool isAdd, int letterPos, std::wstring curWord, bool **flag, int xAdd, int yAdd, WCHAR lAdd)
{
	if (flag == NULL)
	{
		flag = new bool*[5];
		for (int i = 0; i < 5; i++)
			flag[i] = new bool[5];
		flagReset(flag);
	}
	if (isAdd == true)
	{
		result.letter = lAdd;
		result.xPos = xAdd;
		result.yPos = yAdd;
	}
	if (curWord == word && isAdd)
	{
		findWord.letter = lAdd;
		findWord.xPos = xAdd;
		findWord.yPos = yAdd;
		findWord.word = word;
		findWord.size = word.length();
		return true;
	}
	else if (curWord == word && !isAdd)
		return false;
	curWord += word[letterPos];
	letterPos++;
	flag[xPos][yPos] = true;
	if (xPos > 0)
	{
		if (field[xPos - 1][yPos] == word[letterPos] && flag[xPos - 1][yPos] == false)
			SearchForward(findWord, result, word, field, xPos - 1, yPos, isAdd, letterPos, curWord, flag, xAdd, yAdd, lAdd);
		else if (field[xPos - 1][yPos] == NULL && !isAdd)
			SearchForward(findWord, result, word, field, xPos - 1, yPos, true, letterPos, curWord, flag, xPos - 1, yPos, word[letterPos]);
	}
	if (xPos < 4)
	{
		if (field[xPos + 1][yPos] == word[letterPos] && flag[xPos + 1][yPos] == false)
			SearchForward(findWord, result, word, field, xPos + 1, yPos, isAdd, letterPos, curWord, flag, xAdd, yAdd, lAdd);
		else if (field[xPos + 1][yPos] == NULL && !isAdd)
			SearchForward(findWord, result, word, field, xPos + 1, yPos, true, letterPos, curWord, flag, xPos + 1, yPos, word[letterPos]);
	}
	if (yPos > 0)
	{
		if (field[xPos][yPos - 1] == word[letterPos] && flag[xPos][yPos - 1] == false)
			SearchForward(findWord, result, word, field, xPos, yPos - 1, isAdd, letterPos, curWord, flag, xAdd, yAdd, lAdd);
		else if (field[xPos][yPos - 1] == NULL && !isAdd)
			SearchForward(findWord, result, word, field, xPos, yPos - 1, true, letterPos, curWord, flag, xPos, yPos - 1, word[letterPos]);
	}
	if (yPos < 4)
	{
		if (field[xPos][yPos + 1] == word[letterPos] && flag[xPos][yPos + 1] == false)
			SearchForward(findWord, result, word, field, xPos, yPos + 1,isAdd, letterPos, curWord, flag, xAdd, yAdd, lAdd);
		else if (field[xPos][yPos + 1] == NULL && !isAdd)
			SearchForward(findWord, result, word, field, xPos, yPos + 1, true, letterPos, curWord, flag, xPos, yPos + 1, word[letterPos]);
	}
	flag[xPos][yPos] = false;
}
bool SearchBack(BESTWORD &findWord, BESTWORD &result, const std::wstring &word, const WCHAR (&field)[5][5], int xPos, int yPos)
{
	std::wstring curWord = L"";
	curWord += field[xPos][yPos];
	bool **flag = new bool*[5];
	for (int i = 0; i < 5; i++)
		flag[i] = new bool[5];
	flagReset(flag);
	if (xPos > 0)
		if (field[xPos - 1][yPos] == NULL)
		{
			flag[xPos][yPos] = true;
			flag[xPos - 1][yPos] = true;
			curWord = word[0];
			SearchForward(findWord, result, word, field, xPos, yPos, true, 1, curWord, flag, xPos - 1, yPos, word[0]);
			curWord = word[1];
			flagReset(flag);
		}
	if (xPos < 4)
		if (field[xPos + 1][yPos] == NULL)
		{
			flag[xPos][yPos] = true;
			flag[xPos + 1][yPos] = true;
			curWord = word[0];
			SearchForward(findWord, result, word, field, xPos, yPos, true, 1, curWord, flag, xPos + 1, yPos, word[0]);
			curWord = word[1];
			flagReset(flag);
		}
	if (yPos > 0)
		if (field[xPos][yPos - 1] == NULL)
		{
			flag[xPos][yPos] = true;
			flag[xPos][yPos - 1] = true;
			curWord = word[0];
			SearchForward(findWord, result, word, field, xPos, yPos, true, 1, curWord, flag, xPos, yPos - 1, word[0]);
			curWord = word[1];
			flagReset(flag);
		}
	if (yPos < 4)
		if (field[xPos][yPos + 1] == NULL)
		{
			flag[xPos][yPos] = true;
			flag[xPos][yPos + 1] = true;
			curWord = word[0];
			SearchForward(findWord, result, word, field, xPos, yPos, true, 1, curWord, flag, xPos, yPos + 1, word[0]);
			curWord = word[1];
			flagReset(flag);
		}
	for (int i = 0; i < 5; i++)
		delete[] flag[i];
	delete[] flag;
	return true;
}

bool bPassCount(int &nPassCount)
{
	if (nPassCount == 1)
		return true;
	else if (nPassCount == 0)
		nPassCount++;
	return false;
}