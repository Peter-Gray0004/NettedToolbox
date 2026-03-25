#include "styling.hpp"
#include "network.hpp"
static void header(HDC hdc, RECT rect, Styling style) {
	
	HFONT oldFont = (HFONT)SelectObject(hdc, style.fontHeader);

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, style.fontColour);
	SetTextAlign(hdc, TA_CENTER | TA_BASELINE);

	TextOut(hdc,
		horLocPercent(rect, 0.5), 
		vertLocPercent(rect, 0.07),
		L"Netted Toolbox",
		lstrlen(L"Netted Toolbox"));

	SelectObject(hdc, oldFont);
}

static void pubIpDisplay(HDC hdc, RECT rect, Styling style, HWND hwnd, HINSTANCE hInstance, IPInfo ipAddresses) {

	HFONT hOldFont = (HFONT)SelectObject(hdc, style.fontNormal);


	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, style.fontColour);
	SetTextAlign(hdc, TA_CENTER | TA_BASELINE);

	//Gets the IP addresses
	
	
	LPCWSTR pubIPV4 = ipAddresses.ipv4.c_str();
	LPCWSTR pubIPV6 = ipAddresses.ipv6.c_str();


	// Creates, colours and sizes a rect
	RECT rect2;
	double height = double(rect.bottom) - double(rect.top);
	double width = double(rect.right) - double(rect.left);

	rect2 = { long(double(rect.left )+ (width * 0.05)),
					long(double(rect.top) + (height * 0.1)),
					long(double(rect.right) * 0.95),
					long(double(rect.bottom) * 0.3)  };


	FillRect(hdc, &rect2, style.secBgColour);

	//Outputs the Addresses
	TextOut(hdc, horLocPercent(rect, 0.5), vertLocPercent(rect2, 0.7), L"Public Addresses", lstrlen(L"Public Addresses"));
	

	

	SetTextAlign(hdc, TA_LEFT | TA_BASELINE);
	TextOut(hdc, horLocPercent(rect2, 0.13), vertLocPercent(rect2, 0.95), pubIPV4, lstrlen(pubIPV4));
	TextOut(hdc, horLocPercent(rect2, 0.13), vertLocPercent(rect2, 1.2), pubIPV6, lstrlen(pubIPV6));
	
	
	SelectObject(hdc, hOldFont);
	
}