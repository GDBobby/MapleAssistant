// MapleAssistant.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "MapleAssistant.h"


#define MAX_LOADSTRING 100


// Global Variables:

HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Initialize global strings
	LoadStringW(hInstance, IDC_MAPLEASSISTANT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
/*    if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}*/

	hWndMain = CreateWindowW(szWindowClass, (LPCWSTR)"Maple Assistant", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, mainWidth, mainHeight, nullptr, nullptr, hInstance, nullptr);

	ShowWindow(hWndMain, nCmdShow);
	UpdateWindow(hWndMain);


	HINSTANCE hInstRef = (HINSTANCE)GetWindowLongPtr(hWndMain, GWLP_HINSTANCE);

	initWindows(hInstRef);

	prepWhiteRect(whiteRect);
	prepWhiteRect2(whiteRect2);
	prepWhiteRect3(whiteRect3);


//	hWndTest = CreateWindowW(L"EDIT", L"TEST", WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_RIGHT | ES_READONLY,
//		550, 500, 100, 20, hWndMain, (HMENU)ID_EDITTEST, hInstRef, nullptr);

//	hWndTest2 = CreateWindowW(L"EDIT", L"TEST2", WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER | ES_RIGHT | ES_READONLY,
//		550, 520, 100, 20, hWndMain, (HMENU)ID_EDITTEST2, hInstRef, nullptr);


	hwndLBClass = CreateWindowW(L"LISTBOX", NULL, WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_NOTIFY,
		mainWidth - 115, mainHeight - 250, 100, 200, hWndMain, (HMENU)ID_LISTCLASS, hInstRef, NULL);

	hwndLBEle = CreateWindowW(L"LISTBOX", NULL, WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_NOTIFY,
		mainWidth - 115, 20, 100, 100, hWndMain, (HMENU)ID_LISTELE, hInstRef, NULL);

	hwndLBSpd = CreateWindowW(L"LISTBOX", NULL, WS_TABSTOP | WS_VISIBLE | WS_CHILD | WS_BORDER | LBS_NOTIFY,
		mainWidth-35, 220, 20, 90, hWndMain, (HMENU)ID_LISTSPD, hInstRef, NULL);


	file.open("resources\\jobinfo.txt");

	if (!initJob(jobArray[0], 2)) { MessageBox(hWndMain, "COULD NOT INITIALIZE BM", "ERROR", MB_OK); } //bm
	if (!initJob(jobArray[1], 3)) { MessageBox(hWndMain, "COULD NOT INITIALIZE MM", "ERROR", MB_OK); } //mm
	if (!initJob(jobArray[2], 2)) { MessageBox(hWndMain, "COULD NOT INITIALIZE DRK", "ERROR", MB_OK); } //drk
	if (!initJob(jobArray[3], 1)) { MessageBox(hWndMain, "COULD NOT INITIALIZE HERO", "ERROR", MB_OK); } //hero

	for (int i = 4; i < 8; i++) {
		if (!initJob(jobArray[i], 2)) { MessageBox(hWndMain, "COULD NOT INITIALIZE JOB 4-7", "ERROR", MB_OK); } //4-7
	}

	if (!initJob(jobArray[8], 3)) { MessageBox(hWndMain, "COULD NOT INITIALIZE shad", "ERROR", MB_OK); } //shad
	if (!initJob(jobArray[9], 2)) { MessageBox(hWndMain, "COULD NOT INITIALIZE NL", "ERROR", MB_OK); } //NL
	if (!initJob(jobArray[10], 4)) { MessageBox(hWndMain, "COULD NOT INITIALIZE bucc", "ERROR", MB_OK); } //bucc
	if (!initJob(jobArray[11], 3)) { MessageBox(hWndMain, "COULD NOT INITIALIZE sair", "ERROR", MB_OK); } //sair


/*	if (!initShadMMSair(jobArray[1])) { MessageBox(hWndMain, "COULD NOT INITIALIZE JOB", "ERROR", MB_OK); } //mm

	if (!initJob(jobArray[2])) { MessageBox(hWndMain, "COULD NOT INITIALIZE JOB", "ERROR", MB_OK); } //drk

	if (!initHero(jobArray[3])) { MessageBox(hWndMain, "COULD NOT INITIALIZE JOB", "ERROR", MB_OK); } //hero
	for (int ii = 4; ii < 8; ii++) {
		if(!initJob(jobArray[ii])) { MessageBox(hWndMain, "COULD NOT INITIALIZE JOB", "ERROR", MB_OK); }
	}

	if (!initShadMMSair(jobArray[8])) { MessageBox(hWndMain, "COULD NOT INITIALIZE Shad", "ERROR", MB_OK); }
	if (!initJob(jobArray[9])) { MessageBox(hWndMain, "COULD NOT INITIALIZE Night Lord", "ERROR", MB_OK); }
	if (!initBucc(jobArray[10])) { MessageBox(hWndMain, "COULD NOT INITIALIZE Bucc", "ERROR", MB_OK); }
	if (!initShadMMSair(jobArray[11])) { MessageBox(hWndMain, "COULD NOT INITIALIZE JOB", "ERROR", MB_OK); }
*/

	file.close();

	file.open("resources\\weaponinfo.txt");
	initializeWeps();
	file.close();

	dlgCheck = initEleBox();
	if (!dlgCheck) { MessageBox(hWndMain, "COULD NOT INITIALIZE ELEBOX", "ERROR", MB_OK); }

	dlgCheck = initSpeedBox();
	if (!dlgCheck) { MessageBox(hWndMain, "COULD NOT INITIALIZE SPEEDBOX", "ERROR", MB_OK); }

	dlgCheck = FALSE;
	dlgCheck = initClassBox();
	if (!dlgCheck) { MessageBox(hWndMain, "COULD NOT INITIALIZE CLASSBOX", "ERROR", MB_OK); }


	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MAPLEASSISTANT));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {

		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MAPLELEAF));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MAPLEASSISTANT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_MAPLELEAF));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
HBITMAP skillTag = NULL;

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_CREATE:
	{
		break;
	}

	case WM_COMMAND:
	{

		int wmId = LOWORD(wParam);
		int wmEvent = HIWORD(wParam);

		// Parse the menu selections:
		switch (wmId)
		{
		case ID_BUTTONCALC:
		{
			
			if(wmEvent == BN_CLICKED) 
			{
				if (classSel != -1) {
					defaultSelections(hWnd);
					buttDPSCalc(hWnd);
				}


		break;
		} 
		case ID_BUTTONSE:
			if (wmEvent == BN_CLICKED)
			{
				 UINT buttCheck = IsDlgButtonChecked( hWnd, ID_BUTTONSE);
				 if (buttCheck == BST_CHECKED) {
					 se[0] = 15;
					 se[1] = 140;
				 }
				 else if (buttCheck == BST_UNCHECKED) { 
					 se[0] = 0;
					 se[1] = 0;
				 }
				 
				 break;
			}
		case ID_BUTTONECHO:
			if (wmEvent == BN_CLICKED)
			{
				UINT buttCheck = IsDlgButtonChecked(hWnd, ID_BUTTONECHO);
				if (buttCheck == BST_CHECKED) { echo = 1.04; }
				else if (buttCheck == BST_UNCHECKED) { echo = 1; }

				break;
			}


		case ID_LISTCLASS:
		{
			if (wmEvent == LBN_SELCHANGE) { 


				classSel = SendDlgItemMessageA(hWnd, ID_LISTCLASS, LB_GETCURSEL, 0, 0);

				wepSel = 0;



				if (classSel != prevClass) {

					dlgCheck = prepLBH4Rect(classSel, DPSxLoc, DPSyLoc, LBH4Rect);

					destCustomMix();
					destLBWindows();
					destDPS2();
					initLBWindows(classSel);
					destDPSWindows();
					initDPS2((HINSTANCE)GetWindowLongPtr(hWndMain, GWLP_HINSTANCE));
					initDPSWindows((HINSTANCE)GetWindowLongPtr(hWndMain, GWLP_HINSTANCE));
					initCustomMix();

					
					dlgCheck = SetDlgItemTextW(hWnd, ID_EDITMIND, L"");
					dlgCheck = SetDlgItemTextW(hWnd, ID_EDITMAXD, L"");
					dlgCheck = SetDlgItemTextW(hWnd, ID_EDITDPS0, L"");
					dlgCheck = SetDlgItemTextW(hWnd, ID_EDITDPS1, L"");
					dlgCheck = SetDlgItemTextW(hWnd, ID_EDITDPS2, L"");
					dlgCheck = SetDlgItemTextW(hWnd, ID_EDITDPS3, L"");
				}



				prevClass = classSel;


				if (prevSel != classSel) { RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE); }


			}
		break;
		}
		case ID_LISTELE:
		{
			if (wmEvent == LBN_SELCHANGE) {
				weakSel = SendDlgItemMessageA(hWnd, ID_LISTELE, LB_GETCURSEL, 0, 0);
			}
			break;
		}

		case ID_LISTSPD:
		{
			if (wmEvent == LBN_SELCHANGE) {
				spdSel = SendDlgItemMessageA(hWnd, ID_LISTSPD, LB_GETCURSEL, 0, 0);
			}
			break;
		}
		case ID_LISTWEP:
		{
			if (wmEvent == LBN_SELCHANGE) {
				wepSel = SendDlgItemMessageA(hWnd, ID_LISTWEP, LB_GETCURSEL, 0, 0);

				if (classSel == 3 || classSel == 4) {
					if (prevWep != wepSel) {
						destDPS2();
						initDPS2((HINSTANCE)GetWindowLongPtr(hWndMain, GWLP_HINSTANCE));

						RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE); 
					}
				}

				prevWep = wepSel;
			}
			break;
		}
		

		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;

		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
		}
	break;
	}
	}

	case WM_PAINT:
	{
		if((prevSel != classSel) && (classSel > -1) && (classSel != LB_ERR)){
			DeleteObject(skillTag);
			
			prevSel = classSel;

			skillTag = (HBITMAP)LoadImageA(GetModuleHandle(NULL), MAKEINTRESOURCEA(IDB_BITMAP1 + prevSel), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
			if (skillTag == NULL) { MessageBox(hWnd, "COULD NOT LOAD BITMAP", "ERROR", MB_OK); }
		}
		else if (prevSel == 12 && skillTag == NULL) {
			skillTag = (HBITMAP)LoadImageA(GetModuleHandle(NULL), MAKEINTRESOURCEA(IDB_BITMAP1 + prevSel), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
			if (skillTag == NULL) { MessageBox(hWnd, "COULD NOT LOAD BITMAP", "ERROR", MB_OK); }
		}

		PAINTSTRUCT ps;
		BITMAP bm;

		HDC hdc = BeginPaint(hWnd, &ps);

		initLabels(hdc);

		dlgCheck = FALSE;
		if (classSel != -1) {
			dlgCheck = initSkillLabel(classSel, hdc);
			tFDPS2(hdc, classSel, wepSel);
			if (!dlgCheck) { MessageBox(hWnd, "COULD NOT TEXOUT", "ERROR", MB_OK); }
		}



		// TODO: Add any drawing code that uses hdc here...
		HDC hdcMem = CreateCompatibleDC(hdc);

		HGDIOBJ hbmOld = SelectObject(hdcMem, skillTag);

		GetObject(skillTag, sizeof(bm), &bm);


		BitBlt(hdc, 685, 318, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
		SelectObject(hdcMem, hbmOld);
		DeleteDC(hdcMem);

		EndPaint(hWnd, &ps);
	}
	break;
	case WM_DESTROY:
		DeleteObject(skillTag);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
