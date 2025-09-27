#include <thread>
#include <atomic>

static void header(HDC hdc, RECT rect, HBRUSH backgroundColour) {
	auto [r, g, b] = contrastTheme(backgroundColour);

	HFONT hFont = CreateFont(
		-24, 0, 0, 0, FW_LIGHT, FALSE, FALSE, FALSE,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Segoe UI"));

	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(r,g,b));
	SetTextAlign(hdc, TA_CENTER | TA_BASELINE);
	TextOut(hdc, horLocPercent(rect, 0.5), vertLocPercent(rect, 0.07), L"Netted Toolbox", lstrlen(L"Netted Toolbox"));
	
	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);

}

static void pubIpDisplay(HDC hdc, RECT rect, HBRUSH backgroundColour, HWND hwnd, HINSTANCE hInstance) {
	auto [r, g, b] = contrastTheme(backgroundColour);

	HFONT hFont = CreateFont(
		-18, 0, 0, 0, FW_LIGHT, FALSE, FALSE, FALSE,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE,
		TEXT("Segoe UI"));

	HFONT hOldFont = (HFONT)SelectObject(hdc, hFont);
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(r, g, b));
	SetTextAlign(hdc, TA_CENTER | TA_BASELINE);

	//Gets the IP addresses
	std::string  getPublicIPV4 = fetchPublicIPV4();
	std::wstring tmpWide (getPublicIPV4.begin(), getPublicIPV4.end());
	LPCWSTR pubIPV4 = tmpWide.c_str();
	std::string  getPublicIPV6 = fetchPublicIPV6();
	std::wstring tmpWide2(getPublicIPV6.begin(), getPublicIPV6.end());
	LPCWSTR pubIPV6 = tmpWide2.c_str();;


	// Creates, colours and sizes a rect
	RECT rect2;
	HBRUSH backgroundColour2 = backgroundAdjust(backgroundColour);
	double height = double(rect.bottom) - double(rect.top);
	double width = double(rect.right) - double(rect.left);

	rect2 = { long(double(rect.left )+ (width * 0.1)),
					long(double(rect.top) + (height * 0.1)),
					long(double(rect.right) * 0.9),
					long(double(rect.bottom) * 0.3)  };


	FillRect(hdc, &rect2, backgroundColour2);


	//Outputs the Addresses
	TextOut(hdc, horLocPercent(rect, 0.5), vertLocPercent(rect2, 0.65), L"Public Addresses", lstrlen(L"Public Addresses"));
	
	HWND showIP = CreateWindow(
		L"BUTTON", L"Show IP",
		WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
		horLocPercent(rect, 0.5), vertLocPercent(rect2, 1.4), 80, 30,
		hwnd, (HMENU)1001, hInstance, NULL);
	

	SetTextAlign(hdc, TA_LEFT | TA_BASELINE);
	TextOut(hdc, horLocPercent(rect2, 0.2), vertLocPercent(rect2, 0.85), pubIPV4, lstrlen(pubIPV4));
	TextOut(hdc, horLocPercent(rect2, 0.2), vertLocPercent(rect2, 1), pubIPV6, lstrlen(pubIPV6));

	SelectObject(hdc, hOldFont);
	DeleteObject(hFont);
}