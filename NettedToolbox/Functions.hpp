// functions.hpp
#pragma once
#include <Windows.h>
#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")
#include <curl/curl.h>


HBRUSH GetAccentBrush(HWND hwnd) {
	DWORD colour;
	//Required for the theme var that gets colour to pass the bool - doesnt accept a direct passing.
	BOOL isOpaque = FALSE;

	// Gets the colour
	HRESULT theme = DwmGetColorizationColor(&colour, &isOpaque);
	if (SUCCEEDED(theme)) {
		COLORREF rgbColour = RGB((colour >> 16) & 0xFF, (colour >> 8) & 0xFF, colour & 0xFF);

		return CreateSolidBrush(rgbColour);
	}
	//Error if colour not got
	else {
		MessageBox(hwnd, L"Failed to get accent color", L"Debug", MB_OK);

		return nullptr;
	}
}


std::tuple<int, int, int> contrastTheme(HBRUSH backgroundColour) {

	LOGBRUSH lb = { 0 };
	GetObject(backgroundColour, sizeof(lb), &lb);
	COLORREF  colour = lb.lbColor;

	if (colour > 127.5) {
		return { 0, 0, 0 };
	}
	else
	{
		return { 255, 255, 255 };
	}
}

int horLocPercent(RECT rect, double percent) {
	int center = (rect.right - rect.left) * percent;
	
	return center;
}
int vertLocPercent(RECT rect, double percent) {
	int center = (rect.bottom - rect.top) * percent;

	return center;
}