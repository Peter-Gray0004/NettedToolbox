#include <Windows.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <string>

using namespace std;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	switch (msg) {
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_APP + 1:
		if (lParam == WM_LBUTTONDOWN) {

			if (!IsWindowVisible(hwnd))
			{
				ShowWindow(hwnd, SW_SHOW);
				SetForegroundWindow(hwnd);
			}
			else {
				ShowWindow(hwnd, SW_HIDE);

			}

		}
		break;
	case WM_PAINT: {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);


		HKEY hkey;

		
	
		
		COLORREF color =0x00F10FFFF ;



		HBRUSH hbrush = CreateSolidBrush(0x00FFFFFF);
		RECT rect;


		GetClientRect(hwnd, &rect);
		FillRect(hdc, &rect, hbrush);

		DeleteObject(hbrush);
		EndPaint(hwnd, &ps);
	}
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;

}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {


	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.lpfnWndProc = WndProc;
	windowClass.hInstance = hInstance;
	windowClass.lpszClassName = L"NettedToolbox";

	if (!RegisterClassEx(&windowClass)) {
		MessageBox(NULL, L"Window Registration Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	RECT desktopRect;
	if (!GetWindowRect(GetDesktopWindow(), &desktopRect)) { return FALSE; }
	//Sets the size of the window
	int windowWidth = 400;
	int windowHeight = 650;

	//Sets the location of the window
	int posX = desktopRect.right - windowWidth;
	int posY = desktopRect.bottom - windowHeight;

	//Creates the instance of the window using above features
	HWND hwnd = CreateWindowEx(WS_EX_TOOLWINDOW, L"NettedToolbox", L"Netted Toolbox", 
		WS_POPUP | WS_BORDER  , posX, posY, windowWidth- 50, windowHeight - 100,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL) {
		MessageBox(NULL, L"Window Creation Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	NOTIFYICONDATA iconData;
	iconData.cbSize = sizeof(iconData);
	iconData.hWnd = hwnd;
	iconData.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	iconData.hIcon = (HICON)LoadImage(NULL, L"NettedIco.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_SHARED);
	iconData.uCallbackMessage = WM_APP + 1;

	wcscpy_s(iconData.szTip, L"Netted Toolbox");
	
	Shell_NotifyIconW(NIM_ADD, &iconData);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Shell_NotifyIconW(NIM_DELETE, &iconData);
	DestroyWindow(hwnd);

	return(0);
}