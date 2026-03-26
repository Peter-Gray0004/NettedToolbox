#pragma once
#include <Windows.h>

struct Styling {
	HFONT fontHeader;
	HFONT fontNormal;
	HBRUSH bgColour;
	HBRUSH secBgColour;
	COLORREF fontColour;
};

static HFONT createHeaderFont(Styling style) {
	
	HFONT hFont = CreateFont(
		-24, 0, 0, 0, FW_LIGHT, FALSE, FALSE, FALSE,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Segoe UI"));

	return hFont;
}

static HFONT createNormalFont(Styling style) {
	

	HFONT hFont = CreateFont(
		-24, 0, 0, 0, FW_LIGHT, FALSE, FALSE, FALSE,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Segoe UI"));

	return hFont;
}

static void createIcon( HWND hwnd, HINSTANCE hInstance){
	NOTIFYICONDATA iconData = {};
	iconData.cbSize = sizeof(iconData);
	iconData.hWnd = hwnd;
	iconData.uID = 1;
	iconData.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
	iconData.uCallbackMessage = WM_APP + 1;
	iconData.uFlags |= NIF_ICON;
	iconData.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_NETTEDTOOLBOX));

	Shell_NotifyIconW(NIM_ADD, &iconData);
	wcscpy_s(iconData.szTip, L"Netted Toolbox");

}