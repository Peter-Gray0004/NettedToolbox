#include <Windows.h>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>
#include <string>
#include "Functions.hpp"


using namespace std;



LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	static HBRUSH backgroundColour;
	DWORD colour = NULL;

	switch (msg) {
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		DeleteObject(backgroundColour);
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
	case WM_CREATE: {
		backgroundColour = GetAccentBrush(hwnd);
	

		return 0;

	}
	case WM_PAINT: {

		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hwnd, &ps);

		RECT rect;
		GetClientRect(hwnd, &rect);
		FillRect(hdc, &rect, backgroundColour);

		EndPaint(hwnd, &ps);
	}
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;

}

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_  int nCmdShow) {


	WNDCLASSEX windowClass = { 0 };
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.lpfnWndProc = WndProc;
	windowClass.hInstance = hInstance;
	windowClass.lpszClassName = L"NettedToolbox";

	if (!RegisterClassEx(&windowClass)) {
		MessageBox(nullptr, L"Window Registration Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	RECT desktopRect;
	if (!GetWindowRect(GetDesktopWindow(), &desktopRect)) { return FALSE; }



	//Sets the size of the window
	int windowWidth = GetSystemMetrics(SM_CXSCREEN) * 0.2;
	int windowHeight = GetSystemMetrics(SM_CYSCREEN) * 0.6;

	//Sets the location of the window
	int posX = desktopRect.right - windowWidth;
	int posY = desktopRect.bottom - windowHeight;

	//Creates the instance of the window using above features
	HWND hwnd = CreateWindowEx(WS_EX_TOOLWINDOW, L"NettedToolbox", L"Netted Toolbox", 
		WS_POPUP | WS_BORDER  , posX, posY, windowWidth- 50, windowHeight - 100,
		nullptr, nullptr, hInstance, nullptr);

	if (hwnd == nullptr) {
		MessageBox(nullptr, L"Window Creation Failed!", L"Error", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	NOTIFYICONDATA iconData;
	iconData.cbSize = sizeof(iconData);
	iconData.hWnd = hwnd;
	iconData.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	iconData.hIcon = (HICON)LoadImage(nullptr, L"NettedIco.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_SHARED);
	iconData.uCallbackMessage = WM_APP + 1;

	wcscpy_s(iconData.szTip, L"Netted Toolbox");
	
	Shell_NotifyIconW(NIM_ADD, &iconData);

	MSG msg;
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Shell_NotifyIconW(NIM_DELETE, &iconData);
	DestroyWindow(hwnd);

	return(0);
}