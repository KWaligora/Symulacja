#include <windows.h>

#define ID_MDI_FIRSTCHILD  50000
#define ID_NEW 30222

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ChildWindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

char szClassName[] = "KlasaOkna";
char szChildName[] = "KlasaOknaDziecka";

HWND hMDIClient;
HWND hNew;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	HWND hwnd;
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
	wincl.lpszClassName = "Main";

	if (!RegisterClassEx(&wincl))
		return FALSE;

	hwnd = CreateWindowEx(
		0,
		szClassName,
		"Symulacja",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		900,
		700,
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
		5, 5, 400, 300, hwnd, (HMENU)0xCAC, hInstance, (LPSTR)& ccs);

	ShowWindow(hMDIClient, SW_SHOW);

	hNew = CreateWindowEx(0, "BUTTON", "NOWY", WS_CHILD | WS_VISIBLE, 660, 5, 150, 30, hwnd, (HMENU)ID_NEW, hInstance, NULL);

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

		// tu mo¿esz daæ ró¿ne case'y

	default:
		return DefMDIChildProc(hwnd, message, wParam, lParam);
	}
	return 0;
}