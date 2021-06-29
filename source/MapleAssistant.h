#pragma once


#include "JobStats.h"
#include "WeaponStats.h"
#include "resource.h"
#include "errhandlingapi.h"
#include "strsafe.h"
#include "winbase.h"
#include "windows.h"
#include "commctrl.h"


int mainWidth = 800;
int mainHeight = 600;

int rangeXLoc = 240;
int rangeYLoc = 140;
int rangeXDif = 100;
int rangeYDif = 40;


int classSel = -1;
int prevSel = 12;
int prevWep = 4;
int weakSel = -1;
int spdSel = -1;
int prevClass = -1;
int se[2] = { 0,0 };
double echo = 1;
int seCrit = 15;
int seCritDmg = 140;

int wepSel = 0;

//TCHAR szGettingText[80];

int comparingOne;
int comparingTwo;
int compAct;
BOOL dlgCheck;

JobStats jobArray[12];
WeaponStats wepArray[12];

HWND hWndMain;
HWND hWndTest;
HWND hWndTest2;

HWND hWndButtonCalc;
HWND hWndButtonSE;
HWND hWndButtonEcho;

HWND hWndMinD;
HWND hWndMaxD;
HWND hWndMinD2;
HWND hWndMaxD2;
HWND hWndDPS0;
HWND hWndDPS1;
HWND hWndDPS2;
HWND hWndDPS3;

HWND hWndSTR;
HWND hWndDEX;
HWND hWndINT;
HWND hWndLUK;
HWND hWndWA;
HWND hWndTM;

HWND hwndEditBCSub;
HWND hwndEditBCSubLabel;
HWND hwndEditRFSub;
HWND hwndEditRFSubLabel;
HWND hwndEditIdleSub;
HWND hwndEditIdleSubLabel;

HWND hwndLBClass;
HWND hwndLBEle;
HWND hwndLBSpd;
HWND hwndLBWep;

void initLabels(HDC hdc) {
	TextOut(hdc, mainWidth - 125, 0, "ANY WEAKNESS?", 14);

	//	TextOut(hdc, 240, 180, "DPS", 3);
	TextOut(hdc, 10, 200, "STR", 3);
	TextOut(hdc, 10, 220, "DEX", 3);
	TextOut(hdc, 10, 240, "INT", 3);
	TextOut(hdc, 10, 260, "LUK", 3);

	TextOut(hdc, rangeXLoc + 75, rangeYLoc - 20, "Range", 6);
	TextOut(hdc, 270, 145, "~", 1);

	TextOut(hdc, 60, 283, "Weapon Attack", 14);
	TextOut(hdc, 60, 323, "Total Magic", 12);
	TextOut(hdc, mainWidth - 120, 200, "Weapon Speed", 13);
}


typedef struct
{
	TCHAR achName[MAX_PATH];

} Jobs;

Jobs Roster[] =
{
	{TEXT("Bowmaster")},
	{TEXT("Marksman")},
	{TEXT("Dark Knight")},
	{TEXT("Hero")},
	{TEXT("Paladin")},
	{TEXT("Ice Lightning")},
	{TEXT("Fire Poison")},
	{TEXT("Bishop")},
	{TEXT("Shadower")},
	{TEXT("Night Lord")},
	{TEXT("Buccaneer")},
	{TEXT("Corsair")}
};


void ErrorExit(LPTSTR lpszFunction) {
	LPVOID lpMsgBuf;
	LPVOID lpDisplayBuf;
	DWORD dw = GetLastError();

	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR)&lpMsgBuf, 0, NULL);

	lpDisplayBuf = (LPVOID)LocalAlloc(LMEM_ZEROINIT, (lstrlen((LPCTSTR)lpMsgBuf) + lstrlen((LPCTSTR)lpszFunction) + 40) * sizeof(TCHAR));

	StringCchPrintf((LPTSTR)lpDisplayBuf, LocalSize(lpDisplayBuf) / sizeof(TCHAR), TEXT("%s failed with error %d: %s"), lpszFunction, dw, lpMsgBuf);

	MessageBox(NULL, (LPCTSTR)lpDisplayBuf, TEXT("ERROR"), MB_OK);

	LocalFree(lpMsgBuf);
	LocalFree(lpDisplayBuf);
	ExitProcess(dw);
}

bool initEleBox() {
	int pos;

	pos = (int)SendMessage(hwndLBEle, LB_ADDSTRING, 0,
		(LPARAM)TEXT("NONE"));
	SendMessage(hwndLBEle, LB_SETITEMDATA, pos, (LPARAM)0);

	pos = (int)SendMessage(hwndLBEle, LB_ADDSTRING, 0,
		(LPARAM)TEXT("Holy"));
	SendMessage(hwndLBEle, LB_SETITEMDATA, pos, (LPARAM)1);
	pos = (int)SendMessage(hwndLBEle, LB_ADDSTRING, 0,
		(LPARAM)TEXT("Lightning"));
	SendMessage(hwndLBEle, LB_SETITEMDATA, pos, (LPARAM)2);
	pos = (int)SendMessage(hwndLBEle, LB_ADDSTRING, 0,
		(LPARAM)TEXT("Fire"));
	SendMessage(hwndLBEle, LB_SETITEMDATA, pos, (LPARAM)3);
	pos = (int)SendMessage(hwndLBEle, LB_ADDSTRING, 0,
		(LPARAM)TEXT("Ice"));
	SendMessage(hwndLBEle, LB_SETITEMDATA, pos, (LPARAM)4);
	pos = (int)SendMessage(hwndLBEle, LB_ADDSTRING, 0,
		(LPARAM)TEXT("Poison"));
	SendMessage(hwndLBEle, LB_SETITEMDATA, pos, (LPARAM)5);

	return TRUE;
}

bool initSpeedBox() {
	int pos;

	pos = (int)SendMessage(hwndLBSpd, LB_ADDSTRING, 0,
		(LPARAM)TEXT("2"));
	SendMessage(hwndLBSpd, LB_SETITEMDATA, pos, (LPARAM)0);

	pos = (int)SendMessage(hwndLBSpd, LB_ADDSTRING, 0,
		(LPARAM)TEXT("3"));
	SendMessage(hwndLBSpd, LB_SETITEMDATA, pos, (LPARAM)1);
	pos = (int)SendMessage(hwndLBSpd, LB_ADDSTRING, 0,
		(LPARAM)TEXT("4"));
	SendMessage(hwndLBSpd, LB_SETITEMDATA, pos, (LPARAM)2);
	pos = (int)SendMessage(hwndLBSpd, LB_ADDSTRING, 0,
		(LPARAM)TEXT("5"));
	SendMessage(hwndLBSpd, LB_SETITEMDATA, pos, (LPARAM)3);
	pos = (int)SendMessage(hwndLBSpd, LB_ADDSTRING, 0,
		(LPARAM)TEXT("6"));
	SendMessage(hwndLBSpd, LB_SETITEMDATA, pos, (LPARAM)4);

	return TRUE;
}

bool initClassBox() {

	for (int i = 0; i < ARRAYSIZE(Roster); i++)
	{
		int pos = (int)SendMessage(hwndLBClass, LB_ADDSTRING, 0,
			(LPARAM)Roster[i].achName);
		// Set the array index of the player as item data.
		// This enables us to retrieve the item from the array
		// even after the items are sorted by the list box.
		SendMessage(hwndLBClass, LB_SETITEMDATA, pos, (LPARAM)i);

	}
	return TRUE;
}

int wepBoxRectw = 100;
int wepBoxRecth = 100;

bool initWepBox(int a) {
	int pos;
	switch (a) {

	case 3:
		pos = (int)SendMessage(hwndLBWep, LB_ADDSTRING, 0,
			(LPARAM)TEXT("One-Handed Sword"));
		SendMessage(hwndLBWep, LB_SETITEMDATA, pos, (LPARAM)0);

		pos = (int)SendMessage(hwndLBWep, LB_ADDSTRING, 0,
			(LPARAM)TEXT("Two Handed Sword"));
		SendMessage(hwndLBWep, LB_SETITEMDATA, pos, (LPARAM)0);

		pos = (int)SendMessage(hwndLBWep, LB_ADDSTRING, 0,
			(LPARAM)TEXT("One-Handed Axe"));
		SendMessage(hwndLBWep, LB_SETITEMDATA, pos, (LPARAM)0);

		pos = (int)SendMessage(hwndLBWep, LB_ADDSTRING, 0,
			(LPARAM)TEXT("Two Handed Axe"));
		SendMessage(hwndLBWep, LB_SETITEMDATA, pos, (LPARAM)0);
		break;

	case 4:
		pos = (int)SendMessage(hwndLBWep, LB_ADDSTRING, 0,
			(LPARAM)TEXT("One-Handed Sword"));
		SendMessage(hwndLBWep, LB_SETITEMDATA, pos, (LPARAM)0);

		pos = (int)SendMessage(hwndLBWep, LB_ADDSTRING, 0,
			(LPARAM)TEXT("Two Handed Sword"));
		SendMessage(hwndLBWep, LB_SETITEMDATA, pos, (LPARAM)0);

		pos = (int)SendMessage(hwndLBWep, LB_ADDSTRING, 0,
			(LPARAM)TEXT("One-Handed Mace"));
		SendMessage(hwndLBWep, LB_SETITEMDATA, pos, (LPARAM)0);

		pos = (int)SendMessage(hwndLBWep, LB_ADDSTRING, 0,
			(LPARAM)TEXT("Two Handed Mace"));
		SendMessage(hwndLBWep, LB_SETITEMDATA, pos, (LPARAM)0);
		break;

	case 5:
	{
		pos = (int)SendMessage(hwndLBWep, LB_ADDSTRING, 0,
			(LPARAM)TEXT("Lightning Staff"));
		SendMessage(hwndLBWep, LB_SETITEMDATA, pos, (LPARAM)0);

		pos = (int)SendMessage(hwndLBWep, LB_ADDSTRING, 0,
			(LPARAM)TEXT("Ice Staff"));
		SendMessage(hwndLBWep, LB_SETITEMDATA, pos, (LPARAM)0);

		pos = (int)SendMessage(hwndLBWep, LB_ADDSTRING, 0,
			(LPARAM)TEXT("No EleStaff"));
		SendMessage(hwndLBWep, LB_SETITEMDATA, pos, (LPARAM)0);
		break;
	}
	case 6:
	{
		pos = (int)SendMessage(hwndLBWep, LB_ADDSTRING, 0,
			(LPARAM)TEXT("Poison Staff"));
		SendMessage(hwndLBWep, LB_SETITEMDATA, pos, (LPARAM)0);

		pos = (int)SendMessage(hwndLBWep, LB_ADDSTRING, 0,
			(LPARAM)TEXT("Fire Staff"));
		SendMessage(hwndLBWep, LB_SETITEMDATA, pos, (LPARAM)0);

		pos = (int)SendMessage(hwndLBWep, LB_ADDSTRING, 0,
			(LPARAM)TEXT("No EleStaff"));
		SendMessage(hwndLBWep, LB_SETITEMDATA, pos, (LPARAM)0);
		break;
	}

	default:
		MessageBox(hWndMain, "CLASS SEL IS FUCKED", "ERROR", MB_OK);
		break;
	}
	return TRUE;

}



RECT LBH4Rect;

BOOL prepLBH4Rect(int classSel, int x, int y, RECT &rect) {
	rect.top = y;

	switch (classSel) {
	case 0: //bm
		rect.right = 19 * 7;
		rect.left = x - rect.right;
		rect.bottom = 2 * 20;
		return true;
		break;
	case 1: //x
		rect.right = 15 * 7;
		rect.left = x - rect.right;
		rect.bottom = 4 * 20;
		return true;
		break;
	case 2: //drk
		rect.right = 14 * 7;
		rect.left = x - rect.right;
		rect.bottom = 2 * 20;
		return true;
		break;
	case 3: //hero
		rect.right = 9 * 7;
		rect.left = x - rect.right;
		rect.bottom = 1 * 20;
		return true;
		break;
	case 4: //pala
		rect.right = 23 * 7;
		rect.left = x - rect.right;
		rect.bottom = 2 * 20;
		return true;
		break;
	case 5: //ice
		rect.right = 15 * 7;
		rect.left = x - rect.right;
		rect.bottom = 2 * 20;
		return true;
		break;
	case 6: //fire
		rect.right = 15 * 7;
		rect.left = x - rect.right;
		rect.bottom = 2 * 20;
		return true;
		break;
	case 7: //bishop
		rect.right = 11 * 7;
		rect.left = x - rect.right;
		rect.bottom = 2 * 20;
		return true;
		break;
	case 8: //shad
		rect.right = 30 * 7;
		rect.left = x - rect.right;
		rect.bottom = 4 * 20;
		return true;
		break;
	case 9: //NL
		rect.right = 13 * 7;
		rect.left = x - rect.right;
		rect.bottom = 2 * 20;
		return true;
		break;
	case 10: //bucc
		rect.right = 23 * 7;
		rect.left = x - rect.right;
		rect.bottom = 4 * 20;
		return true;
		break;
	case 11: //sair
		rect.right = 23 * 7;
		rect.left = x - rect.right;
		rect.bottom = 4 * 20;
		return true;
		break;
	default:
		return false;
		break;
	}


	return false;
}

int DPSxLoc = 400;
int DPSyLoc = 240;

static RECT whiteRect;

void prepWhiteRect(RECT &wR) {
	wR.left = DPSxLoc;
	wR.top = DPSyLoc;
	wR.right = DPSxLoc - 160;
	wR.bottom = DPSyLoc + 80;
}

static RECT whiteRect2;

void prepWhiteRect2(RECT &wR) {
	wR.left = rangeXLoc;
	wR.top = rangeYLoc;
	wR.right = rangeXLoc - 90;
	wR.bottom = rangeYLoc + 60;
}

static RECT whiteRect3;

void prepWhiteRect3(RECT &wR) {
	wR.left = rangeXLoc+180;
	wR.top = rangeYLoc;
	wR.right = rangeXLoc + 265;
	wR.bottom = rangeYLoc + 60;
}


bool initSkillLabel(int a, HDC hdc) {
	int yDif = 20;
	std::string tempSS;

	if (!FillRect(hdc, &whiteRect, (HBRUSH)(COLOR_WINDOW + 1))) { MessageBox(hWndMain, "COULD NOT PAINT", "ERROR", MB_OK); }

	if (jobArray[classSel].getSkillName(0) != "") {
		TextOut(hdc, DPSxLoc - (jobArray[classSel].getSkillName(0).length() * 8), DPSyLoc, jobArray[classSel].getSkillName(0).c_str(), jobArray[classSel].getSkillName(0).length());
	}
	if (jobArray[classSel].getSkillName(1) != "") {
		if (classSel == 3) {}
		TextOut(hdc, DPSxLoc - (jobArray[classSel].getSkillName(1).length() * 8), DPSyLoc + yDif, jobArray[classSel].getSkillName(1).c_str(), jobArray[classSel].getSkillName(1).length());
	}


	switch (classSel) {

	case 1:
		if (jobArray[classSel].getSkillName(2) != "") {
			TextOut(hdc, DPSxLoc - (jobArray[classSel].getSkillName(2).length() * 8), DPSyLoc + yDif * 2, jobArray[classSel].getSkillName(2).c_str(), jobArray[classSel].getSkillName(2).length());
		}

		tempSS = "Strafe+Snipe";
		TextOut(hdc, DPSxLoc - tempSS.length() * 8, DPSyLoc + yDif * 3, tempSS.c_str(), tempSS.length());
		break;
	case 8:
		tempSS = "Ass2 + BStep";
		TextOut(hdc, DPSxLoc - tempSS.length() * 8, DPSyLoc + yDif * 2, tempSS.c_str(), tempSS.length());

		tempSS = "BStep + BoT";
		TextOut(hdc, DPSxLoc - tempSS.length() * 8, DPSyLoc + yDif * 3, tempSS.c_str(), tempSS.length());
		break;

	case 10:
		tempSS = "Demo + Barrage";
		TextOut(hdc, DPSxLoc - tempSS.length() * 8, DPSyLoc + yDif * 2, tempSS.c_str(), tempSS.length());

		tempSS = "Dragon Strike + Snatch";
		TextOut(hdc, DPSxLoc - tempSS.length() * 7, DPSyLoc + yDif * 3, tempSS.c_str(), tempSS.length());
		break;

	case 11:
		if (jobArray[classSel].getSkillName(2) != "") {
			TextOut(hdc, DPSxLoc - (jobArray[classSel].getSkillName(2).length() * 8), DPSyLoc + yDif * 2, jobArray[classSel].getSkillName(2).c_str(), jobArray[classSel].getSkillName(2).length());
		}

		tempSS = "Custom Mix";
		TextOut(hdc, DPSxLoc - tempSS.length() * 8, DPSyLoc + yDif * 3, tempSS.c_str(), tempSS.length());
		break;



	}


	return true;
}


std::ifstream file;


bool initJob(JobStats &jSt, int numOfSkills) {

	std::string pass;

	if (file.is_open()) {

		file >> pass; //jobName
		jSt.setJobName(pass);
		file >> pass;
		jSt.setMastery(pass);


		for (int y = 0; y < numOfSkills; y++) { //skill0, skill1, skill3
			file >> pass;
			jSt.setSkillName(y, pass);
			file >> pass;
			jSt.setSkillPerc(y, pass);
			file >> pass;
			jSt.setSkillLines(y, pass);
		}
		file >> pass;
		jSt.setCritChance(pass);

		file >> pass;
		jSt.setCritDmg(pass);

		for (int x = 0; x < 4; x++) {
			file >> pass;
			jSt.setModifier(pass, x);
		}
	}
	return true;
}

bool initializeWeps() {
	std::string wID; // weaponID for passing
	std::string wM; // weaponMultiplier for passing
	std::string wS; //weaponSpeed for passing

	//file.open("weaponinfo.txt");
	if (file.is_open()) {

		file >> wID; //should be bow
		wepArray[0].setWID(wID);

		file >> wM;
		wepArray[0].setMultH(wM);

		for (int c = 0; c < 5; c++) {
			for (int b = 0; b < 2; b++) {
				file >> wS;
				wepArray[0].setSS(wS, b, c);
			}
		}

		//bowmaster is finished

		file >> wID;
		wepArray[1].setWID(wID);

		file >> wM;
		wepArray[1].setMultH(wM);

		for (int c = 0; c < 5; c++) {
			file >> wS;
			wepArray[1].setSS(wS, 0, c);

		}

		//xbow is finished

		file >> wID;
		wepArray[2].setWID(wID);

		file >> wM;
		wepArray[2].setMultH(wM);

		for (int c = 0; c < 5; c++) {
			for (int b = 0; b < 2; b++) {
				file >> wS;
				wepArray[2].setSS(wS, b, c);
			}
		}
		//spear is finished


		file >> wID;
		wepArray[3].setWID(wID);

		file >> wM;
		wepArray[3].setMultH(wM);

		for (int c = 0; c < 5; c++) {
			for (int b = 0; b < 2; b++) {
				file >> wS;
				wepArray[3].setSS(wS, b, c);
			}
		}
		//1h sword is finished

		file >> wID;
		wepArray[4].setWID(wID);

		file >> wM;
		wepArray[4].setMultH(wM);

		for (int c = 0; c < 5; c++) {
			for (int b = 0; b < 2; b++) {
				file >> wS;
				wepArray[4].setSS(wS, b, c);
			}
		}

		//2hsword should be finished

		file >> wID;
		wepArray[5].setWID(wID);

		file >> wM;
		wepArray[5].setMultH(wM);
		file >> wM;
		wepArray[5].setMultL(wM);

		for (int c = 0; c < 5; c++) {
			for (int b = 0; b < 2; b++) {
				file >> wS;
				wepArray[5].setSS(wS, b, c);
			}
		}
		// 1ham is finished

		file >> wID;
		wepArray[6].setWID(wID);

		file >> wM;
		wepArray[6].setMultH(wM);
		file >> wM;
		wepArray[6].setMultL(wM);

		for (int c = 0; c < 5; c++) {
			for (int b = 0; b < 2; b++) {
				file >> wS;
				wepArray[6].setSS(wS, b, c);
			}
		}
		// 2ham is finished

		file >> wID;
		wepArray[7].setWID(wID);

		file >> wM;
		wepArray[7].setMultH(wM);
		file >> wM;
		wepArray[7].setMultL(wM);

		for (int c = 0; c < 3; c++) {
			for (int b = 0; b < 2; b++) {
				file >> wS;
				wepArray[7].setSS(wS, b, c);
			}
		}
		// elestaff is finished

		file >> wID;
		wepArray[8].setWID(wID);

		file >> wM;
		wepArray[8].setMultH(wM);

		for (int c = 0; c < 6; c++) {
			for (int b = 0; b < 2; b++) {
				file >> wS;
				if (wS != "NULL") { wepArray[8].setSS(wS, b, c); }
			}
		}
		// dagger is finished

		file >> wID;
		wepArray[9].setWID(wID);

		file >> wM;
		wepArray[9].setMultH(wM);

		for (int c = 0; c < 5; c++) {
			for (int b = 0; b < 2; b++) {
				file >> wS;
				if (wS != "NULL") { wepArray[9].setSS(wS, b, c); }
			}
		}
		//claw is finished
		file >> wID;
		wepArray[10].setWID(wID);

		file >> wM;
		wepArray[10].setMultH(wM);

		for (int c = 0; c < 6; c++) {
			for (int b = 0; b < 4; b++) {
				file >> wS;
				if (wS != "NULL") { wepArray[10].setSS(wS, b, c); }
			}
		}
		//knuckle is finished

		file >> wID;
		wepArray[11].setWID(wID);

		file >> wM;
		wepArray[11].setMultH(wM);

		for (int c = 0; c < 5; c++) {
			for (int b = 0; b < 3; b++) {
				file >> wS;
				wepArray[11].setSS(wS, b, c);
			}
		}

		//gun is finished




	}
	file.close();

	return true;
}


bool initWindows(HINSTANCE hInstRef) { //default page, 1 skill at a time DPS
	hWndButtonCalc = CreateWindowW(L"BUTTON", L"CALCULATE", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | WS_BORDER,
		100, mainHeight - 100, 100, 20, hWndMain, (HMENU)ID_BUTTONCALC, hInstRef, nullptr);

	hWndButtonSE = CreateWindowW(L"BUTTON", L"SE", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_AUTOCHECKBOX,
		120, 60, 100, 20, hWndMain, (HMENU)ID_BUTTONSE, hInstRef, nullptr);

	hWndButtonEcho = CreateWindowW(L"BUTTON", L"Echo", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_AUTOCHECKBOX,
		120, 40, 100, 20, hWndMain, (HMENU)ID_BUTTONECHO, hInstRef, nullptr);

	hWndMinD = CreateWindowW(L"EDIT", L"", WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_RIGHT | ES_READONLY,
		rangeXLoc, rangeYLoc, 80, 20, hWndMain, (HMENU)ID_EDITMIND, hInstRef, nullptr);

	hWndMaxD = CreateWindowW(L"EDIT", L"", WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_LEFT | ES_READONLY,
		rangeXLoc + rangeXDif, rangeYLoc, 80, 20, hWndMain, (HMENU)ID_EDITMAXD, hInstRef, nullptr);

	hWndSTR = CreateWindowW(L"EDIT", L"4", WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_RIGHT,
		40, 200, 80, 20, hWndMain, (HMENU)ID_EDITSTR, hInstRef, nullptr);

	hWndDEX = CreateWindowW(L"EDIT", L"4", WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_RIGHT,
		40, 220, 80, 20, hWndMain, (HMENU)ID_EDITDEX, hInstRef, nullptr);

	hWndINT = CreateWindowW(L"EDIT", L"4", WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_RIGHT,
		40, 240, 80, 20, hWndMain, (HMENU)ID_EDITINT, hInstRef, nullptr);

	hWndLUK = CreateWindowW(L"EDIT", L"4", WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_RIGHT,
		40, 260, 80, 20, hWndMain, (HMENU)ID_EDITLUK, hInstRef, nullptr);

	hWndWA = CreateWindowW(L"EDIT", L"100", WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_RIGHT,
		60, 300, 40, 20, hWndMain, (HMENU)ID_EDITWA, hInstRef, nullptr);
	hWndTM = CreateWindowW(L"EDIT", L"200", WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_RIGHT,
		60, 340, 40, 20, hWndMain, (HMENU)ID_EDITTM, hInstRef, nullptr);

	return true;
}


double eleApp(int cS, int wV, int skillSel) {
	if (cS == 5)
	{
		if (wV == 2 && skillSel == 0) {
			return 1.5;
		}
		else if(wV == 4 && skillSel == 1){
			return 1.5;
		}
	}
	if (cS == 6)
	{
		if (wV == 5 && skillSel == 0) {
			return 1.5;
		}
		else if (wV == 3 && skillSel == 1) {
			return 1.5;
		}
	}
	if (cS == 7 && wV == 1)
	{
		return 1.5;
	}
	return 1;
}


bool buttDPSCalc(HWND hWnd) {
	int prepAtt = GetDlgItemInt(hWnd, ID_EDITWA, &dlgCheck, FALSE);
	if (!dlgCheck) { MessageBox(hWnd, "COULD NOT GET INT FROM EDITWA", "ERROR", MB_OK); }
	double prepMagic = GetDlgItemInt(hWnd, ID_EDITTM, &dlgCheck, FALSE) * echo;
	if (!dlgCheck) { MessageBox(hWnd, "COULD NOT GET INT FROM EDITTM", "ERROR", MB_OK); }

	int passInt;
	int weakVal = weakSel;

	switch (classSel) {
	case 0:		//bowmaster
	{
		int mainStat = GetDlgItemInt(hWnd, ID_EDITDEX, &dlgCheck, FALSE);
		int sub1Stat = GetDlgItemInt(hWnd, ID_EDITSTR, &dlgCheck, FALSE);

		double maxRange = (mainStat * wepArray[0].getMult() + sub1Stat) * prepAtt / 100;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMAXD, maxRange, FALSE);

		double minRange = (mainStat * wepArray[0].getMult() * .9 * jobArray[classSel].getMastery() + sub1Stat) * prepAtt / 100;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMIND, minRange, FALSE);

		//hurricane
		passInt = (minRange + maxRange) / 2 * jobArray[classSel].getDPSValue(0, se) * 1000 / wepArray[classSel].getSS(0, spdSel) * echo;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS0, passInt, FALSE);

		//inferno/arrow rain
		passInt = (minRange + maxRange) / 2 * jobArray[classSel].getDPSValue(1, se) * 1000 / wepArray[classSel].getSS(1, spdSel) * echo;
		if (weakSel == 3) { passInt *= 1.5; }
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS1, passInt, FALSE);

		break;
	}
	case 1:		//marksman
	{
		int mainStat = GetDlgItemInt(hWnd, ID_EDITDEX, &dlgCheck, FALSE);
		int sub1Stat = GetDlgItemInt(hWnd, ID_EDITSTR, &dlgCheck, FALSE);

		double maxRange = (mainStat * wepArray[1].getMult() + sub1Stat) * prepAtt / 100;
		passInt = maxRange;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMAXD, passInt, FALSE);

		double minRange = (mainStat * wepArray[1].getMult() * .9 * jobArray[classSel].getMastery() + sub1Stat) * prepAtt / 100;
		passInt = minRange;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMIND, passInt, FALSE);

		//strafe
		passInt = (minRange + maxRange) / 2 * jobArray[classSel].getDPSValue(0, se) * 1000 / wepArray[classSel].getSS(0, spdSel) * echo;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS0, passInt, FALSE);

		//snipe
		double strafedps = jobArray[classSel].getSkillPerc(1) * 100 / 15;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS1, strafedps, FALSE);

		//pierce
		passInt = (minRange + maxRange) / 2 * jobArray[classSel].getDPSValue(2, se) * echo; //speed is skipped because attack speed is 1000ms
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS2, passInt, FALSE);

		//strafesnipe
		int strafesniperatio = floor((15000 - wepArray[classSel].getSS(0, spdSel)) / wepArray[classSel].getSS(0, spdSel));
		passInt = (((minRange + maxRange) / 2 * jobArray[classSel].getDPSValue(0, se)) * strafesniperatio / 15) * echo + strafedps;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS3, passInt, FALSE);

		break;
	}

	case 2:		// dark knight
	{
		int mainStat = GetDlgItemInt(hWnd, ID_EDITSTR, &dlgCheck, FALSE);
		int sub1Stat = GetDlgItemInt(hWnd, ID_EDITDEX, &dlgCheck, FALSE);

		double maxRange = (mainStat * wepArray[2].getMult() + sub1Stat) * prepAtt / 100;
		passInt = maxRange;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMAXD, passInt, FALSE);

		double minRange = (mainStat * wepArray[2].getMult() * .9 * jobArray[classSel].getMastery() + sub1Stat) * prepAtt / 100;
		passInt = minRange;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMIND, passInt, FALSE);

		//crusher
		passInt = (minRange + maxRange) / 2 * jobArray[classSel].getDPSValue(0, se) * 1000 / wepArray[classSel].getSS(0, spdSel) * echo;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS0, passInt, FALSE);

		//fury
		passInt = (minRange + maxRange) / 2 * jobArray[classSel].getDPSValue(1, se) * 1000 / wepArray[classSel].getSS(1, spdSel) * echo;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS1, passInt, FALSE);

		break;
	}
	case 3:		// hero
	{
		int mainStat = GetDlgItemInt(hWnd, ID_EDITSTR, &dlgCheck, FALSE);
		int sub1Stat = GetDlgItemInt(hWnd, ID_EDITDEX, &dlgCheck, FALSE);


		if (wepSel == 2 || wepSel == 3) { //axe
			int wepVal = wepSel + 3;
			double maxRange = (mainStat * wepArray[wepVal].getMult() + sub1Stat) * prepAtt / 100;
			dlgCheck = SetDlgItemInt(hWnd, ID_EDITMAXD, maxRange, FALSE);

			double minRange = (mainStat * wepArray[4].getMult() * .9 * jobArray[classSel].getMastery() + sub1Stat) * prepAtt / 100;
			dlgCheck = SetDlgItemInt(hWnd, ID_EDITMAXD2, minRange, FALSE);

			double stabMaxRange = (mainStat * wepArray[wepVal].getMult(1) + sub1Stat) * prepAtt / 100;
			dlgCheck = SetDlgItemInt(hWnd, ID_EDITMIND2, stabMaxRange, FALSE);

			double stabMinRange = (mainStat * wepArray[wepVal].getMult(1) * .9 * jobArray[classSel].getMastery() + sub1Stat) * prepAtt / 100;
			dlgCheck = SetDlgItemInt(hWnd, ID_EDITMIND, stabMinRange , FALSE);

			passInt = ((minRange + maxRange) / 2 * .5 + (stabMinRange + stabMaxRange) / 2 * .5) * jobArray[classSel].getDPSValue(0, se) * (1000 / wepArray[classSel].getSS(0, spdSel)) * echo;
			dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS0, passInt, FALSE);
		}
		else if (wepSel == 0 || wepSel == 1) { //sword
			int wepVal = wepSel + 3;

			double maxRange = (mainStat * wepArray[wepVal].getMult() + sub1Stat) * prepAtt / 100;
			dlgCheck = SetDlgItemInt(hWnd, ID_EDITMAXD, maxRange, FALSE);

			double minRange = (mainStat * wepArray[wepVal].getMult() * .9 * jobArray[classSel].getMastery() + sub1Stat) * prepAtt / 100;

			dlgCheck = SetDlgItemInt(hWnd, ID_EDITMIND, minRange, FALSE);

			passInt = (minRange + maxRange) / 2 * jobArray[classSel].getDPSValue(0, se) * 1000 / wepArray[classSel].getSS(0, spdSel) * echo;
			dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS0, passInt, FALSE);
		}

		break;
	}
	case 4:		// paladin
	{
		int mainStat = GetDlgItemInt(hWnd, ID_EDITSTR, &dlgCheck, FALSE);
		int sub1Stat = GetDlgItemInt(hWnd, ID_EDITDEX, &dlgCheck, FALSE);

		weakVal = weakSel;
		if (weakSel != 0) {
			weakVal = weakSel - 1;
			if (weakSel == 5) {
				weakVal = 0;
			}
		}

		if (wepSel == 2 || wepSel == 3) { //mace
			int wepVal = wepSel + 3;

			double maxRange = (mainStat * wepArray[wepVal].getMult() + sub1Stat) * prepAtt / 100;
			dlgCheck = SetDlgItemInt(hWnd, ID_EDITMAXD, maxRange, FALSE);

			double minRange = (mainStat * wepArray[4].getMult() * .9 * jobArray[classSel].getMastery() + sub1Stat) * prepAtt / 100;
			dlgCheck = SetDlgItemInt(hWnd, ID_EDITMAXD2, minRange, FALSE);

			double stabMaxRange = (mainStat * wepArray[wepVal].getMult(1) + sub1Stat) * prepAtt / 100;
			dlgCheck = SetDlgItemInt(hWnd, ID_EDITMIND2, stabMaxRange, FALSE);

			double stabMinRange = (mainStat * wepArray[wepVal].getMult(1) * .9 * jobArray[classSel].getMastery() + sub1Stat) * prepAtt / 100;
			dlgCheck = SetDlgItemInt(hWnd, ID_EDITMIND, stabMinRange, FALSE);

			passInt = stabMinRange;
			dlgCheck = SetDlgItemInt(hWnd, ID_EDITMIND, passInt, FALSE);

			//blast mace
			passInt = ((minRange + maxRange) / 2 * .6 + (stabMinRange + stabMaxRange) / 2 * .4) * jobArray[classSel].getPalaDPS(0, weakVal, se) * 1000 / wepArray[classSel].getSS(0, spdSel) * echo;
			if (weakVal != weakSel && weakSel != 5) {
				passInt *= 1.5;
			}
			dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS0, passInt, FALSE);

			//acb mace
			passInt = ((minRange + maxRange) / 2 * .6 + (stabMinRange + stabMaxRange) / 2 * .4) * jobArray[classSel].getPalaDPS(1, weakVal, se) * 1000 / wepArray[classSel].getSS(1, spdSel) * echo;
			if (weakVal != weakSel && weakSel != 5) { passInt *= 1.5; }
			dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS1, passInt, FALSE);

		}
		else if (wepSel == 0 || wepSel == 1) { //sword
			int wepVal = wepSel + 3;

			double maxRange = (mainStat * wepArray[wepVal].getMult() + sub1Stat) * prepAtt / 100;
			passInt = maxRange;
			dlgCheck = SetDlgItemInt(hWnd, ID_EDITMAXD, passInt, FALSE);

			double minRange = (mainStat * wepArray[wepVal].getMult() * .9 * jobArray[classSel].getMastery() + sub1Stat) * prepAtt / 100;
			passInt = minRange;

			dlgCheck = SetDlgItemInt(hWnd, ID_EDITMIND, passInt, FALSE);

			passInt = (minRange + maxRange) / 2 * jobArray[classSel].getPalaDPS(0, weakVal, se) * 1000 / wepArray[classSel].getSS(0, spdSel) * echo;
			if (weakVal != weakSel && weakSel != 5) {
				passInt *= 1.5;
			}
			dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS0, passInt, FALSE); //blast sword

			passInt = (minRange + maxRange) / 2 * jobArray[classSel].getPalaDPS(1, weakVal, se) * 1000 / wepArray[classSel].getSS(1, spdSel) * echo;
			if (weakVal != weakSel && weakSel != 5) {
				passInt *= 1.5;
			}
			dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS1, passInt, FALSE); //acb sword

		}


		break;
	}

	case 5:		// icelightning roll to bishop
	case 6:		// fp roll to bishop
	case 7:		// bishop
	{
		int mainStat = GetDlgItemInt(hWnd, ID_EDITINT, &dlgCheck, FALSE);
		int sub1Stat = GetDlgItemInt(hWnd, ID_EDITLUK, &dlgCheck, FALSE);

		double magicMax = jobArray[classSel].calcMagicMax(prepMagic, mainStat, 0, se) * wepArray[7].getMultMagic(wepSel,0); //single t
		magicMax *= eleApp(classSel, weakSel, 0);
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMAXD, magicMax, FALSE);

		double magic2Max = jobArray[classSel].calcMagicMax(prepMagic, mainStat, 1, se) * wepArray[7].getMultMagic(wepSel,1); //ult
		magic2Max *= eleApp(classSel, weakSel, 1);
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMAXD2, magic2Max, FALSE);

		double magicMin = jobArray[classSel].calcMagicMin(prepMagic, mainStat, 0, se) * wepArray[7].getMultMagic(wepSel,0); //single t
		magicMin *= eleApp(classSel, weakSel, 0);
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMIND, magicMin, FALSE);

		double magic2Min = jobArray[classSel].calcMagicMin(prepMagic, mainStat, 1, se) * wepArray[7].getMultMagic(wepSel,1); // ult
		magic2Min *= eleApp(classSel, weakSel, 1);
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMIND2, magic2Min, FALSE);

		double magicDPS = jobArray[classSel].calcMagicDPS(prepMagic, mainStat, 0, se) * wepArray[7].getMultMagic(wepSel,0) * (1000 / static_cast<double>(wepArray[7].getSS(0, 2)));; //cl
		magicDPS *= eleApp(classSel, weakSel, 0);
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS0, magicDPS, FALSE);

		magicDPS = jobArray[classSel].calcMagicDPS(prepMagic, mainStat, 1, se) * wepArray[7].getMultMagic(wepSel,1) * (1000 / static_cast<double>(wepArray[7].getSS(1, 2)));; //blizzard
		magicDPS *= eleApp(classSel, weakSel, 1);
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS1, magicDPS, FALSE);

		break;
	}

	case 8:		//shadower
	{
		int mainStat = GetDlgItemInt(hWnd, ID_EDITLUK, &dlgCheck, FALSE);
		int sub1Stat = GetDlgItemInt(hWnd, ID_EDITDEX, &dlgCheck, FALSE);
		int sub2Stat = GetDlgItemInt(hWnd, ID_EDITSTR, &dlgCheck, FALSE);
		int dsDelay = 240; // delay from dark sight for boomerang step

		double maxRange = (mainStat * wepArray[8].getMult() + sub1Stat + sub2Stat) * prepAtt / 100;
		passInt = maxRange;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMAXD, passInt, FALSE);

		double minRange = (mainStat * wepArray[8].getMult() * .9 * jobArray[classSel].getMastery() + sub1Stat + sub2Stat) * prepAtt / 100;
		passInt = minRange;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMIND, passInt, FALSE);


		//ass only, skill ID 0
		passInt = (minRange + maxRange) / 2 * jobArray[classSel].getDPSValue(0, se) * 1000 / (wepArray[classSel].getSS(0, spdSel) + dsDelay) * echo;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS0, passInt, FALSE);

		//bstep only, skill ID 1, attack speed is 1950, should be located at [1][5]
		passInt = (minRange + maxRange) / 2 * jobArray[classSel].getDPSValue(1, se) * 1000 / wepArray[classSel].getSS(1, 5) * echo;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS1, passInt, FALSE);

		//ass+bstep, adding the two delays together for now

		passInt = (minRange + maxRange) / 2 * (jobArray[classSel].getDPSValue(0, se) + jobArray[classSel].getDPSValue(1, se)) * 1000 / (wepArray[classSel].getSS(0, spdSel) + wepArray[classSel].getSS(0, spdSel)) * echo;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS2, passInt, FALSE);


		//Bstep + BoT, BoT ID is 2, attack speed is 1950

		passInt = (minRange + maxRange) / 2 * (jobArray[classSel].getDPSValue(1, se) + jobArray[classSel].getDPSValue(2, se)) * 1000 / wepArray[classSel].getSS(1, 5) * echo;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS3, passInt, FALSE);

		break;
	}

	case 9:		//nightlord
	{


		int mainStat = GetDlgItemInt(hWnd, ID_EDITLUK, &dlgCheck, FALSE);
		int sub1Stat = GetDlgItemInt(hWnd, ID_EDITDEX, &dlgCheck, FALSE);
		int sub2Stat = GetDlgItemInt(hWnd, ID_EDITSTR, &dlgCheck, FALSE);

		//L7
		double maxL7Range = (mainStat * 5) * prepAtt / 100;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMAXD2, maxL7Range, FALSE);

		double minL7Range = (mainStat * 2.5) * prepAtt / 100;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMIND2, minL7Range, FALSE);

		int passInt;

		passInt = (maxL7Range + minL7Range) / 2 * jobArray[classSel].getDPSValue(0, se) * 1000 / wepArray[classSel].getSS(0, spdSel) * echo;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS0, passInt, FALSE);

		//avenger
		double maxRange = (mainStat * wepArray[9].getMult() + sub1Stat + sub2Stat) * prepAtt / 100;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMAXD, maxRange, FALSE);

		double minRange = (mainStat * wepArray[9].getMult() * .9 * jobArray[classSel].getMastery() + sub1Stat + sub2Stat) * prepAtt / 100;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMIND, minRange, FALSE);

		passInt = (minRange + maxRange) / 2 * jobArray[classSel].getDPSValue(1, se) * 1000 / wepArray[classSel].getSS(1, spdSel) * echo;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS1, passInt, FALSE);

		break;
	}

	case 10:	// bucc
	{
		int mainStat = GetDlgItemInt(hWnd, ID_EDITSTR, &dlgCheck, FALSE);
		int sub1Stat = GetDlgItemInt(hWnd, ID_EDITDEX, &dlgCheck, FALSE);

		double maxRange = (mainStat * wepArray[10].getMult() + sub1Stat) * prepAtt / 100;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMAXD, maxRange, FALSE);

		double minRange = (mainStat * wepArray[10].getMult() * .9 * jobArray[classSel].getMastery() + sub1Stat) * prepAtt / 100;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMIND, minRange, FALSE);

		//demo only, skill ID 0
		passInt = (minRange + maxRange) / 2 * jobArray[classSel].getDPSValue(0,  se) * 1000 / wepArray[classSel].getSS(0, spdSel) * echo;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS0, passInt, FALSE);

		//barrage only, skill ID 1, attack speed is 3240, should be located at [1][5]
		passInt = (minRange + maxRange) / 2 * jobArray[classSel].getBarrDPS(1, se) * 1000 / wepArray[classSel].getSS(1, 5) * echo;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS1, passInt, FALSE);

		// demo+barrage, adding the two delays together for now

		passInt = (minRange + maxRange) / 2 * (jobArray[classSel].getDPSValue(0, se) + jobArray[classSel].getBarrDPS(1, se)) * 1000 / (wepArray[classSel].getSS(0, spdSel) + wepArray[classSel].getSS(1, spdSel)) * echo;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS2, passInt, FALSE);


		//DS + snatch, demo ID is 2, snatch ID is 3, attack speed is same as DS (2250) allegedly [2][5]
		passInt = (minRange + maxRange) / 2 * (jobArray[classSel].getDPSValue(2, se) + jobArray[classSel].getDPSValue(3, se)) * 1000 / wepArray[classSel].getSS(2, 5) * echo;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS3, passInt, FALSE);


		break;
	}
	case 11:	//corsair
	{
		int mainStat = GetDlgItemInt(hWnd, ID_EDITDEX, &dlgCheck, FALSE);
		int sub1Stat = GetDlgItemInt(hWnd, ID_EDITSTR, &dlgCheck, FALSE);

		double maxRange = (mainStat * wepArray[11].getMult() + sub1Stat) * prepAtt / 100;
		passInt = maxRange;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMAXD, passInt, FALSE);

		double minRange = (mainStat * wepArray[11].getMult() * .9 * jobArray[classSel].getMastery() + sub1Stat) * prepAtt / 100;
		passInt = minRange;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITMIND, passInt, FALSE);


		//cannon
		passInt = (minRange + maxRange) / 2 * jobArray[classSel].getDPSValue(0, se) * 1000 / wepArray[classSel].getSS(0, spdSel) * echo;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS0, passInt, FALSE);

		//rf
		passInt = (minRange + maxRange) / 2 * jobArray[classSel].getDPSValue(1, se) * 1000 / wepArray[classSel].getSS(1, spdSel) * echo;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS1, passInt, FALSE);

		//torpedo
		passInt = (minRange + maxRange) / 2 * jobArray[classSel].getDPSValue(2, se) * 1000 / wepArray[classSel].getSS(2, spdSel) * echo;
		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS2, passInt, FALSE);

		//custom mix
		passInt = (minRange + maxRange) / 2 * jobArray[classSel].getDPSValue(0, se) * 1000 / wepArray[classSel].getSS(0, spdSel) * echo * GetDlgItemInt(hWnd, ID_EDITBCS, &dlgCheck, FALSE) / (GetDlgItemInt(hWnd, ID_EDITBCS, &dlgCheck, FALSE) + GetDlgItemInt(hWnd, ID_EDITRFS, &dlgCheck, FALSE) + GetDlgItemInt(hWnd, ID_EDITIS, &dlgCheck, FALSE));

		passInt += (minRange + maxRange) / 2 * jobArray[classSel].getDPSValue(1, se) * 1000 / wepArray[classSel].getSS(1, spdSel) * echo * GetDlgItemInt(hWnd, ID_EDITRFS, &dlgCheck, FALSE) / (GetDlgItemInt(hWnd, ID_EDITBCS, &dlgCheck, FALSE) + GetDlgItemInt(hWnd, ID_EDITRFS, &dlgCheck, FALSE) + GetDlgItemInt(hWnd, ID_EDITIS, &dlgCheck, FALSE));

		dlgCheck = SetDlgItemInt(hWnd, ID_EDITDPS3, passInt, FALSE);


		break;
	}


	return true;
	}
}

bool destLBWindows() {
	if (IsWindow(hwndLBWep)) { 
		dlgCheck = DestroyWindow(hwndLBWep); 
	wepSel = -1;
	}
	return true;
}

bool initLBWindows(int cS) { //weapon boxes, for hero/paladin, arch mage, and skill subboxes
	if (cS == 3 || cS == 4) {
		hwndLBWep = CreateWindowW(L"LISTBOX", NULL, WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_NOTIFY,
			mainWidth - 180, 250, 135, 80, hWndMain, (HMENU)ID_LISTWEP, (HINSTANCE)GetWindowLongPtr(hWndMain, GWLP_HINSTANCE), NULL);

		dlgCheck = initWepBox(classSel);
	}
	if (cS == 5 || cS == 6) {
		hwndLBWep = CreateWindowW(L"LISTBOX", NULL, WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_NOTIFY,
			mainWidth - 180, 250, 135, 60, hWndMain, (HMENU)ID_LISTWEP, (HINSTANCE)GetWindowLongPtr(hWndMain, GWLP_HINSTANCE), NULL);

		dlgCheck = initWepBox(classSel);
	}

	dlgCheck = AdjustWindowRect(&LBH4Rect, WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_NOTIFY, FALSE);

	return true;
}

bool defaultSelections(HWND hWnd) { //if no weak, speed, weapon, or skill is selected when calculate is clicked
	if (weakSel == -1) {
		SendDlgItemMessageA(hWnd, ID_LISTELE, LB_SETCURSEL, 0, 0);
		weakSel = 0;
	}
	if (spdSel == -1) {
		SendDlgItemMessageA(hWnd, ID_LISTSPD, LB_SETCURSEL, 2, 0);
		spdSel = 2;
	}

	if (SendDlgItemMessageA(hWnd, ID_LISTWEP, LB_GETCURSEL, 0, 0) == LB_ERR && IsWindow(hwndLBWep)) {
		SendDlgItemMessageA(hWnd, ID_LISTWEP, LB_SETCURSEL, 0, 0);
		wepSel = 0;
	}
	return true;
}

bool initCustomMix() {
	if (classSel == 11) {

		int xDif = 280;
		int yDif = 60;
		int yDif2 = yDif - 20;

		hwndEditBCSub = CreateWindowW(L"EDIT", L"80", WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			LBH4Rect.left + xDif, LBH4Rect.top + yDif, 30, 20, hWndMain, (HMENU)ID_EDITBCS, (HINSTANCE)GetWindowLongPtr(hWndMain, GWLP_HINSTANCE), NULL);
		hwndEditBCSubLabel = CreateWindowW(L"EDIT", L"BC", WS_TABSTOP | WS_VISIBLE | WS_CHILD | ES_READONLY,
			LBH4Rect.left + xDif, LBH4Rect.top + yDif2, 30, 20, hWndMain, (HMENU)ID_EDITBCST, (HINSTANCE)GetWindowLongPtr(hWndMain, GWLP_HINSTANCE), NULL);

		hwndEditRFSub = CreateWindowW(L"EDIT", L"15", WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			LBH4Rect.left + xDif + 40, LBH4Rect.top + yDif, 30, 20, hWndMain, (HMENU)ID_EDITRFS, (HINSTANCE)GetWindowLongPtr(hWndMain, GWLP_HINSTANCE), NULL);
		hwndEditRFSubLabel = CreateWindowW(L"EDIT", L"RF", WS_TABSTOP | WS_VISIBLE | WS_CHILD | ES_READONLY,
			LBH4Rect.left + xDif + 40, LBH4Rect.top + yDif2, 30, 20, hWndMain, (HMENU)ID_EDITRFST, (HINSTANCE)GetWindowLongPtr(hWndMain, GWLP_HINSTANCE), NULL);

		hwndEditIdleSub = CreateWindowW(L"EDIT", L"5", WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER,
			LBH4Rect.left + xDif + 80, LBH4Rect.top + yDif, 30, 20, hWndMain, (HMENU)ID_EDITIS, (HINSTANCE)GetWindowLongPtr(hWndMain, GWLP_HINSTANCE), NULL);
		hwndEditIdleSubLabel = CreateWindowW(L"EDIT", L"IDLE", WS_TABSTOP | WS_VISIBLE | WS_CHILD | ES_READONLY,
			LBH4Rect.left + xDif + 80, LBH4Rect.top + yDif2, 35, 20, hWndMain, (HMENU)ID_EDITIST, (HINSTANCE)GetWindowLongPtr(hWndMain, GWLP_HINSTANCE), NULL);

	}
	return true;
}

bool initDPSWindows(HINSTANCE hInstRef) {


	if (jobArray[classSel].getSkillName(0) != "") {
		hWndDPS0 = CreateWindowW(L"EDIT", NULL, WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_RIGHT | ES_READONLY,
			DPSxLoc, DPSyLoc, 100, 20, hWndMain, (HMENU)ID_EDITDPS0, hInstRef, nullptr);
	}
	if (jobArray[classSel].getSkillName(1) != "") {
		hWndDPS1 = CreateWindowW(L"EDIT", NULL, WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_RIGHT | ES_READONLY,
			DPSxLoc, DPSyLoc + 20, 100, 20, hWndMain, (HMENU)ID_EDITDPS1, hInstRef, nullptr);
	}
	if (jobArray[classSel].getSkillName(2) != "") {
		hWndDPS2 = CreateWindowW(L"EDIT", NULL, WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_RIGHT | ES_READONLY,
			DPSxLoc, DPSyLoc + 40, 100, 20, hWndMain, (HMENU)ID_EDITDPS2, hInstRef, nullptr);
	}
	if ((jobArray[classSel].getSkillName(3) != "") || (classSel == 1) || (classSel == 8) || (classSel == 11)) {
		hWndDPS3 = CreateWindowW(L"EDIT", NULL, WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_RIGHT | ES_READONLY,
			DPSxLoc, DPSyLoc + 60, 100, 20, hWndMain, (HMENU)ID_EDITDPS3, hInstRef, nullptr);
	}
	return true;
}

void tFDPS2(HDC hdc, int cS, int wS) {
	int yDif = 20;

	if (!FillRect(hdc, &whiteRect2, (HBRUSH)(COLOR_WINDOW + 1))) { MessageBox(hWndMain, "COULD NOT PAINT", "ERROR", MB_OK); }
	if (!FillRect(hdc, &whiteRect3, (HBRUSH)(COLOR_WINDOW + 1))) { MessageBox(hWndMain, "COULD NOT PAINT", "ERROR", MB_OK); }


	switch (cS) {
	case 3:
	case 4:
	{
		if (wS == 2 || wS == 3) {
			TextOut(hdc, rangeXLoc - (9 * 8), rangeYLoc, "Stab Min", 9);
			TextOut(hdc, rangeXLoc - (9 * 8), rangeYLoc + rangeYDif, "Stab Max", 9);
			TextOut(hdc, rangeXLoc + 185, rangeYLoc, "Swing Max", 10);
			TextOut(hdc, rangeXLoc + 185, rangeYLoc + rangeYDif, "Swing Min", 10);
		}
		break;
	}
	case 5: {


		TextOut(hdc, rangeXLoc - (7 * 8), rangeYLoc, "CL Min", 7);
		TextOut(hdc, rangeXLoc - (9 * 8), rangeYLoc + rangeYDif, "Bliz Min", 9);
		TextOut(hdc, rangeXLoc + 185, rangeYLoc, "CL Max", 7);
		TextOut(hdc, rangeXLoc + 185, rangeYLoc + rangeYDif, "Bliz Max", 9);
		break;
	}
	case 6: {


		TextOut(hdc, rangeXLoc - (9 * 8), rangeYLoc, "Para Min", 9);
		TextOut(hdc, rangeXLoc - (11 * 8), rangeYLoc + rangeYDif, "Meteor Min", 11);
		TextOut(hdc, rangeXLoc + 185, rangeYLoc, "Para Max", 11);
		TextOut(hdc, rangeXLoc + 185, rangeYLoc + rangeYDif, "Meteor Max", 11);
		break;
	}
	case 7: {


		TextOut(hdc, rangeXLoc - (7 * 8), rangeYLoc, "AR Min", 7);
		TextOut(hdc, rangeXLoc - (8 * 8), rangeYLoc + rangeYDif, "Gen Min", 8);
		TextOut(hdc, rangeXLoc + 185, rangeYLoc, "AR Max", 7);
		TextOut(hdc, rangeXLoc + 185, rangeYLoc + rangeYDif, "Gen Max", 8);
		break;
	}
	case 9: {
		TextOut(hdc, rangeXLoc - (7 * 8), rangeYLoc + rangeYDif, "L7 Min", 7);
		TextOut(hdc, rangeXLoc + 185, rangeYLoc + rangeYDif, "L7 Max", 7);
		break;
	}
	default:
		break;
	}

}

void initDPS2(HINSTANCE hInstRef) {

	if (classSel == 5 || classSel == 6 || classSel == 7 || classSel == 9 || ((classSel == 3 || classSel == 4) && (wepSel == 2 || wepSel == 3))) {
	

		hWndMinD2 = CreateWindowW(L"EDIT", L"", WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_RIGHT | ES_READONLY,
			rangeXLoc, rangeYLoc + rangeYDif, 80, 20, hWndMain, (HMENU)ID_EDITMIND2, hInstRef, nullptr);

		hWndMaxD2 = CreateWindowW(L"EDIT", L"", WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_LEFT | ES_READONLY,
			rangeXLoc + rangeXDif, rangeYLoc + rangeYDif, 80, 20, hWndMain, (HMENU)ID_EDITMAXD2, hInstRef, nullptr);

	}
}

void destDPS2() {
	if (IsWindow(hWndMinD2)) { dlgCheck = DestroyWindow(hWndMinD2); }
	if (IsWindow(hWndMaxD2)) { dlgCheck = DestroyWindow(hWndMaxD2); }
}

void destDPSWindows() {
	if (IsWindow(hWndDPS0)) { dlgCheck = DestroyWindow(hWndDPS0); }
	if (IsWindow(hWndDPS1)) { dlgCheck = DestroyWindow(hWndDPS1); }
	if (IsWindow(hWndDPS2)) { dlgCheck = DestroyWindow(hWndDPS2); }
	if (IsWindow(hWndDPS3)) { dlgCheck = DestroyWindow(hWndDPS3); }
}


bool destCustomMix() {
	if (hwndEditBCSub) { dlgCheck = DestroyWindow(hwndEditBCSub); }
	if (hwndEditBCSubLabel) { dlgCheck = DestroyWindow(hwndEditBCSubLabel); }

	if (hwndEditRFSub) { dlgCheck = DestroyWindow(hwndEditRFSub); }
	if (hwndEditRFSubLabel) { dlgCheck = DestroyWindow(hwndEditRFSubLabel); }

	if (hwndEditIdleSub) { dlgCheck = DestroyWindow(hwndEditIdleSub); }
	if (hwndEditIdleSubLabel) { dlgCheck = DestroyWindow(hwndEditIdleSubLabel); }

	return true;
}