#include "Common.hpp"

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "advapi32.lib")
#pragma comment (lib, "crypt32.lib")

#define CURL_STATICLIB

#include "curl/curl.h"

#pragma comment (lib, "curl/libcurl_a.lib")



size_t WriteCallback(char* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

size_t write_data(void* ptr, size_t size, size_t nmemb, void* stream) {
	std::string data((const char*)ptr, (size_t)size * nmemb);
	*((std::stringstream*)stream) << data << std::endl;
	return size * nmemb;
}



namespace Big
{
	namespace authhhhhhhhhhhhhhhhhh {

		std::string username = ReadStringFromIni("C:\\Viper\\auth.ini", "auth", "username");
		std::string password = ReadStringFromIni("C:\\Viper\\auth.ini", "auth", "password");
		
	}
	

	std::string string_of_bytes;
	uintptr_t bytes;
	uintptr_t get_total_physical_memory()
	{
		MEMORYSTATUSEX status;
		status.dwLength = sizeof(status);
		GlobalMemoryStatusEx(&status);

		bytes = status.ullTotalPhys;;
		return bytes;
	}

	static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
	{
		std::string& text = *static_cast<std::string*>(param);
		size_t totalsize = size * nmemb;
		text.append(static_cast<char*>(buffer), totalsize);
		return totalsize;
	}

	BOOL AUTH(std::string username123, std::string password123)
	{
		using namespace std;
		std::string result;
		CURL* curl;
		CURLcode res;
		curl_global_init(CURL_GLOBAL_DEFAULT);
		curl = curl_easy_init();

		authhhhhhhhhhhhhhhhhh::username = username123;
		authhhhhhhhhhhhhhhhhh::password = password123;

		if (curl) {
			string uwu = "https://systemlocker.net/auth.php?username=" + authhhhhhhhhhhhhhhhhh::username + "&password=" + authhhhhhhhhhhhhhhhhh::password + "&system=ea82c9e842617fcc301e&hwid=" + std::to_string(get_total_physical_memory()) + "&version=1";
			curl_easy_setopt(curl, CURLOPT_URL, uwu.c_str());
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result);
			res = curl_easy_perform(curl);
			curl_easy_cleanup(curl);
			if (CURLE_OK != res) {
				std::cerr << "CURL error: " << res << '\n';
			}
		}
		curl_global_cleanup();
		if (!strcmp(result.c_str(), "true"))
		{
			std::cout << "Logged In!";

			return 1;
		}
		else if (!strcmp(result.c_str(), "false"))
		{
			std::cout << "Error Logging In";
			return 0;
		}
		else if (!strcmp(result.c_str(), "no u/p"))
		{
			std::cout << "No Username Or Password Inputted";
			return 0;
		}
		else if (!strcmp(result.c_str(), "no sys"))
		{
			std::cout << "Invalid HTTP Request";
			return 0;
		}
		else if (!strcmp(result.c_str(), "not verified"))
		{
			std::cout << "Account Does Not Own Menu.";
			return 0;
		}
		else if (!strcmp(result.c_str(), "bad u/p"))
		{
			std::cout << "Invalid Username Or Password";
			return 0;
		}
		else if (!strcmp(result.c_str(), "bad keys"))
		{
			std::cout << "Invalid License Key.";
			return 0;
		}
		else if (!strcmp(result.c_str(), "expired key"))
		{
			std::cout << "Your Key Is Expired";
			return 0;
		}
		else if (!strcmp(result.c_str(), "frozen"))
		{
			std::cout << "Account Is Frozen";
			return 0;
		}
		else if (!strcmp(result.c_str(), "hwid"))
		{
			std::cout << "Invalid HWID";
			return 0;
		}
		else if (!strcmp(result.c_str(), "spoofsuspected"))
		{
			std::cout << "HWID Spoofing Suspected";
			return 0;
		}
		else if (!strcmp(result.c_str(), "outdated"))
		{
			std::cout << "Menu Version Outdated";
			return 0;
		}
		else if (!strcmp(result.c_str(), "dbe"))
		{
			//std::cout << "Internal Auth Server Error";
			return 0;
		}
		else
		{
			//std::cout << "Unknwon Error";
			return 0;
		}

			

	}





		
}

