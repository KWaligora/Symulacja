#include <windows.h>

#define ID_MDI_FIRSTCHILD  50000

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

char szClassName[] = "KlasaOkna";
char szChildName[] = "KlasaOknaDziecka";

HWND hMDIClient;
HWND hMasaKulki;
HWND hMasaPreta;
HWND hPredkoscKulki;
HWND hPrzycisk;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	HWND hwnd;
	MSG messages;
	WNDCLASSEX wincl;

	// Klasa okna g��wnego

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

	CLIENTCREATESTRUCT ccs;

	ccs.hWindowMenu = NULL;
	ccs.idFirstChild = ID_MDI_FIRSTCHILD;

	hMDIClient = CreateWindowEx(0, "MDICLIENT", (LPCTSTR)NULL,
		WS_CHILD | WS_CLIPCHILDREN | WS_VSCROLL | WS_HSCROLL,
		5, 5, 700, 700, hwnd, (HMENU)0xCAC, hInstance, (LPSTR)& ccs);

	ShowWindow(hMDIClient, SW_SHOW);

	CreateWindowEx(0, "STATIC", "Masa Pr�ta:", WS_CHILD | WS_VISIBLE | SS_LEFT,
		720, 30, 150, 20, hwnd, NULL, hInstance, NULL);

	hMasaPreta = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_BORDER | WS_VISIBLE,
		830, 30, 50, 20, hwnd, NULL, hInstance, NULL);

	CreateWindowEx(0, "STATIC", "Kg", WS_CHILD | WS_VISIBLE | SS_LEFT,
		890, 30, 150, 20, hwnd, NULL, hInstance, NULL);

	CreateWindowEx(0, "STATIC", "Masa kulki:", WS_CHILD | WS_VISIBLE | SS_LEFT,
		720, 80, 150, 20, hwnd, NULL, hInstance, NULL);

	hMasaKulki = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_BORDER | WS_VISIBLE,
		830, 80, 50, 20, hwnd, NULL, hInstance, NULL);

	CreateWindowEx(0, "STATIC", "Kg", WS_CHILD | WS_VISIBLE | SS_LEFT,
		890, 80, 150, 20, hwnd, NULL, hInstance, NULL);

	CreateWindowEx(0, "STATIC", "Pr�dko�� kulki:" , WS_CHILD | WS_VISIBLE | SS_LEFT,
		720, 130, 150, 20, hwnd, NULL, hInstance, NULL);

	hPredkoscKulki = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_BORDER | WS_VISIBLE,
		830, 130, 50, 20, hwnd, NULL, hInstance, NULL);

	CreateWindowEx(0, "STATIC", "Km/h", WS_CHILD | WS_VISIBLE | SS_LEFT,
		890, 130, 150, 20, hwnd, NULL, hInstance, NULL);


	hPrzycisk = CreateWindowEx(0, "BUTTON", "Start", WS_CHILD | WS_VISIBLE, 745, 180, 150, 30, hwnd, NULL, hInstance, NULL);

	HWND Footer = CreateWindowEx(0, "STATIC", "Kamil Walig�ra 2019", WS_CHILD | WS_VISIBLE | SS_RIGHT,
		730, 700, 150, 20, hwnd, NULL, hInstance, NULL);

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

		// tu mo�esz da� r�ne case'y

	default:
		return DefMDIChildProc(hwnd, message, wParam, lParam);
	}
	return 0;
}