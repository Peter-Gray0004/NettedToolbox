#include <Windows.h>
#include <dwmapi.h>
#pragma comment(lib, "Dwmapi.lib")
#include <curl/curl.h>
#pragma once

struct ipInfo {
	std::string ipv4;
	std::string ipv6;
};




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