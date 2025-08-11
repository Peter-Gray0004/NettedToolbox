// functions.hpp
#pragma once
#include <Windows.h>
#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")



HBRUSH GetAccentBrush(HWND hwnd) {
	DWORD colour;
	BOOL isOpaque = FALSE;

	HRESULT theme = DwmGetColorizationColor(&colour, &isOpaque);
	if (SUCCEEDED(theme)) {
		COLORREF rgbColour = RGB((colour >> 16) & 0xFF, (colour >> 8) & 0xFF, colour & 0xFF);

		return CreateSolidBrush(rgbColour);
	}
	else {
		MessageBox(hwnd, L"Failed to get accent color", L"Debug", MB_OK);

		return nullptr;
	}
}

