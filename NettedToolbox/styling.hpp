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