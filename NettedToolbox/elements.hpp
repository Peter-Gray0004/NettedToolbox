
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