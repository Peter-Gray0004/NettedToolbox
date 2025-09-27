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

size_t WriteCallback(char* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

  std::string fetchPublicIPV4()
{
	CURL* curl = curl_easy_init();
	if (curl) {
		std::string readBuffer;

		//Gets IPV4 addr
		curl_easy_setopt(curl, CURLOPT_URL, "https://api.ipify.org");
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		curl_easy_perform(curl);

		std::string res = "IPV4: " + readBuffer;
		curl_easy_cleanup(curl);
		return res;
	}
	
	else {
		return "IPV4: UNAVAILABLE";
	}
	
	 
}
 
  std::string fetchPublicIPV6()
  {
	  CURL* curl = curl_easy_init();
	  if (curl) {
		  std::string readBuffer;

		  //Gets IPV6 addr 
		  curl_easy_setopt(curl, CURLOPT_URL, "https://api64.ipify.org");
		  curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
		  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		  curl_easy_perform(curl);

		  std::string res = "IPV6: " + readBuffer;
		  curl_easy_cleanup(curl);
		  return res;
	  }

	  else {
		  return "IPV6: UNAVAILABLE";
	  }


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
