#pragma once
#include <Windows.h>
#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")
#include <curl/curl.h>

struct IPInfo {
	std::wstring ipv4;
	std::wstring ipv6;
};



std::wstring fetchPublicIPV4()
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

		std::wstring wide = std::wstring(readBuffer.begin(), readBuffer.end());
		std::wstring res = L"IPV4: " + wide;
	
		curl_easy_cleanup(curl);
		return res;
	}

	else {
		return L"IPV4: UNAVAILABLE";
	}


}

std::wstring fetchPublicIPV6()
{
	CURL* curl = curl_easy_init();
	if (curl) {
		std::string readBuffer;

		//Gets IPV6 addr 
		curl_easy_setopt(curl, CURLOPT_URL, "https://api64.ipify.org");
		curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V6);
		curl_easy_setopt(curl, CURLOPT_CONNECTTIMEOUT, 5L);   // 5 seconds
		curl_easy_setopt(curl, CURLOPT_HTTPGET, 1L);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		CURLcode res 	= curl_easy_perform(curl);


		if (res != CURLE_OK || readBuffer.empty()){
			return L"IPV6: UNAVAILABLE";
		}

		std::wstring wide = std::wstring(readBuffer.begin(), readBuffer.end());
		curl_easy_cleanup(curl);

		return L"IPV6: " + wide;;
	}

	else {
		return L"IPV6: UNAVAILABLE";
	}

}