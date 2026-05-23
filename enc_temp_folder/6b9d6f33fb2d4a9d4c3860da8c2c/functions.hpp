#pragma once
#include <Windows.h>
#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")
#include <curl/curl.h>





HBRUSH getBackgroundColour(HWND hwnd) {
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


COLORREF contrastTheme(HBRUSH backgroundColour) {

	LOGBRUSH lb = { 0 };
	GetObject(backgroundColour, sizeof(lb), &lb);
	COLORREF  colour = lb.lbColor;

	if (colour > 127.5) {

		return RGB(0, 0, 0);
	}
	else
	{
		
		return RGB(255, 255, 255);
	}
}

int horLocPercent(RECT rect, double percent) {
	int center = std::trunc((rect.right - rect.left) * percent);
	
	return center;
}
int vertLocPercent(RECT rect, double percent) {
	int center = std::trunc((rect.bottom - rect.top) * percent);

	return center;
}

size_t WriteCallback(char* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}


  HBRUSH  backgroundAdjust(HBRUSH backgroundColour) {
	  LOGBRUSH lb = { };
	  GetObject(backgroundColour, sizeof(lb), &lb);
	  COLORREF  colour = lb.lbColor;

	  int r = GetRValue(colour);
	  int g = GetGValue(colour);
	  int b = GetBValue(colour);

	  if (colour > 127.5) {
		  HBRUSH adjBgColour = CreateSolidBrush(RGB(r - 20, g - 20, b - 20));

		  return  adjBgColour;
	  }
	  else
	  {
		  HBRUSH adjBgColour = CreateSolidBrush(RGB(r + 20, g + 20, b + 20));

		  return  adjBgColour;
	  }
  }
