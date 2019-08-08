#include <windows.h>
#include "Kulka.h"
#include "Pret.h"

#define ID_MDI_FIRSTCHILD  50000

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
void CreateFront(HINSTANCE hInstance);
void Odczyt(HWND h);
void Refresh();

char szClassName[] = "KlasaOkna";
char szChildName[] = "KlasaOknaDziecka";

HWND hwnd;
HWND hMDIClient;
HWND hMasaKulki;
HWND hMasaPreta;
HWND hPredkoscKulki;
HWND hPrzycisk;
HWND hChild;

const WORD ID_TIMER = 1;
Kulka kulka;
Pret pret;
LPSTR Bufor;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	MSG messages;
	WNDCLASSEX wincl;

	// Klasa okna g³ównego

	wincl.hInstance = hInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;
	wincl.style = 0;
	wincl.cbSize = sizeof(WNDCLASSEX);
	wincl.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(hInstance, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;
	wincl.cbClsExtra = 0;
	wincl.cbWndExtra = 0;
	wincl.hbrBackground = (HBRUSH)COLOR_WINDOW;

	if (!RegisterClassEx(&wincl))
		return FALSE;

	// Klasa okna dziecka 

	wincl.lpfnWndProc = ChildWindowProcedure;
	wincl.lpszMenuName = (LPCTSTR)NULL;
	wincl.lpszClassName = "KlasaOknaDziecka";
	wincl.style = CS_HREDRAW | CS_VREDRAW | CS_NOCLOSE;

	if (!RegisterClassEx(&wincl))
		return FALSE;

	hwnd = CreateWindowEx(
		0,
		szClassName,
		"Aplikacja MDI",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		950,
		760,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	CLIENTCREATESTRUCT ccs;

	ccs.hWindowMenu = NULL;
	ccs.idFirstChild = ID_MDI_FIRSTCHILD;

	hMDIClient = CreateWindowEx(0, "MDICLIENT", (LPCTSTR)NULL,
		WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL,
		5, 5, 700, 700, hwnd, (HMENU)0xCAC, hInstance, (LPSTR)& ccs);

	ShowWindow(hMDIClient, nCmdShow);
	//------------------------------------------------KOD-------------------------------------------------
	CreateFront(hInstance);
	if (SetTimer(hChild, ID_TIMER, 10, NULL) == 0)
		MessageBox(hChild, "Nie mo¿na utworzyæ timera", "damn", MB_ICONSTOP);
	//----------------------------------------------------------------------------------------------------

	while (GetMessage(&messages, NULL, 0, 0)) {
		if (!TranslateMDISysAccel(hMDIClient, &messages)) {
			TranslateMessage(&messages);
			DispatchMessage(&messages);
		}
	}
	return messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_COMMAND:
		if ((HWND)lParam == hPrzycisk) {
			Odczyt(hPredkoscKulki);			
			kulka.SetSpeed(atoi(Bufor));
			GlobalFree(Bufor);
	}
	break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_SIZE:

		break;
	default:
		return DefFrameProc(hwnd, hMDIClient, message, wParam, lParam);
	}
	return 0;
}

LRESULT CALLBACK ChildWindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	switch (message) {
	case WM_TIMER:
		//InvalidateRect(hwnd, NULL,NULL);
		break;
	case WM_PAINT:
		RECT rcOkno;
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rcOkno);
		SetMapMode(hdc, MM_ANISOTROPIC);
		SetWindowExtEx(hdc, 700, 700, NULL);
		SetViewportExtEx(hdc, rcOkno.right, rcOkno.bottom, NULL);
		kulka.Rysuj(hwnd, hdc, rcOkno);
		pret.Rysuj(hwnd, hdc, rcOkno);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hChild, ID_TIMER);
	default:
		return DefMDIChildProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

void CreateFront(HINSTANCE hInstance) {
	CreateWindowEx(0, "STATIC", "Masa Prêta:", WS_CHILD | WS_VISIBLE | SS_LEFT,
		720, 30, 150, 20, hwnd, NULL, hInstance, NULL);

	hMasaPreta = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "0", WS_CHILD | WS_BORDER | WS_VISIBLE,
		830, 30, 50, 20, hwnd, NULL, hInstance, NULL);

	CreateWindowEx(0, "STATIC", "Kg", WS_CHILD | WS_VISIBLE | SS_LEFT,
		890, 30, 150, 20, hwnd, NULL, hInstance, NULL);

	CreateWindowEx(0, "STATIC", "Masa kulki:", WS_CHILD | WS_VISIBLE | SS_LEFT,
		720, 80, 150, 20, hwnd, NULL, hInstance, NULL);

	hMasaKulki = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "0", WS_CHILD | WS_BORDER | WS_VISIBLE,
		830, 80, 50, 20, hwnd, NULL, hInstance, NULL);

	CreateWindowEx(0, "STATIC", "Kg", WS_CHILD | WS_VISIBLE | SS_LEFT,
		890, 80, 150, 20, hwnd, NULL, hInstance, NULL);

	CreateWindowEx(0, "STATIC", "Prêdkoœæ kulki:", WS_CHILD | WS_VISIBLE | SS_LEFT,
		720, 130, 150, 20, hwnd, NULL, hInstance, NULL);

	hPredkoscKulki = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "0", WS_CHILD | WS_BORDER | WS_VISIBLE,
		830, 130, 50, 20, hwnd, NULL, hInstance, NULL);

	CreateWindowEx(0, "STATIC", "Km/h", WS_CHILD | WS_VISIBLE | SS_LEFT,
		890, 130, 150, 20, hwnd, NULL, hInstance, NULL);

	hPrzycisk = CreateWindowEx(0, "BUTTON", "Start", WS_CHILD | WS_VISIBLE, 745, 180, 150, 30, hwnd, NULL, hInstance, NULL);

	HWND Footer = CreateWindowEx(0, "STATIC", "Kamil Waligóra 2019", WS_CHILD | WS_VISIBLE | SS_RIGHT,
		730, 700, 150, 20, hwnd, NULL, hInstance, NULL);

	MDICREATESTRUCT mcs;

	mcs.szTitle = "Nowe okno MDI";
	mcs.szClass = szChildName; // zak³adam, ¿e korzystasz z szablonu (punkt 1.5) 
	mcs.hOwner = GetModuleHandle(NULL); // pobieramy instancjê aplikacji
	mcs.x = 0;
	mcs.y = 0;
	mcs.cx = 700; // domyœlne wymiary
	mcs.cy = 700;
	//mcs.style = MDIS_ALLCHILDSTYLES;
	mcs.style &= ~WS_MAXIMIZE;

	hChild = (HWND)SendMessage(hMDIClient, WM_MDICREATE, 0, (LONG)& mcs);

	if (!hChild) {
		MessageBox(hwnd, "Nie uda³o siê utworzyæ okienka MDI!", "A to szkoda...",
			MB_ICONEXCLAMATION | MB_OK);
	}
	HBRUSH brush = CreateSolidBrush(RGB(255, 255, 255)); //zmiana koloru t³a
	SetClassLongPtr(hChild, GCLP_HBRBACKGROUND, (LONG)brush);
}
void Odczyt(HWND h) {
	DWORD dlugosc = GetWindowTextLength(h);
	Bufor = (LPSTR)GlobalAlloc(GPTR, dlugosc + 1);
	GetWindowText(h, Bufor, dlugosc + 1);
}