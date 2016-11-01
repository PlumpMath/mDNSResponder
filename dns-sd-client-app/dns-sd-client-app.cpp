// dns-sd-client-app.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <thread>
#include <chrono>
#include "windows.h"
#include <iostream>
#include <rtcapi.h>
using namespace std;

//extern "C"
//{
//__declspec(dllimport)	int callDNSSDWithCL(int argc, char **argv);
__declspec(dllimport) bool getResolution(char * name, char *ip);
__declspec(dllimport) void stopDNS();
__declspec(dllimport) void runDNSSDFromThread(int argc, char **argv);


//extern "C"
//{
//	bool getResolution(char * name, char *ip);
//	void runDNSSDFromThread(int argc, char **argv);
//}
//}


//void call_from_thread(int argc, char **argv)
//{
//	callDNSSDWithCL(argc, argv);
//	//std::cout << "Hello, World" << std::endl;
//	
//	
//}
int cnt = 0;

bool g_showCrashDialog = false;




typedef void(*LPrunDNSSDFromThread)(int, char**);
typedef bool(*LPgetResolution)(char*,char*);

int errorhandler = 0;
void myInvalidParameterHandler(const wchar_t* expression,
	const wchar_t* function,
	const wchar_t* file,
	unsigned int line,
	uintptr_t pReserved)
{
	wprintf(L"Invalid parameter detected in function %s."
		L" File: %s Line: %d\n", function, file, line);
	wprintf(L"Expression: %s\n", expression);
	abort();
}


int main(int argc, char **argv)
{
	char* formatString;

	_invalid_parameter_handler oldHandler, newHandler;
	newHandler = myInvalidParameterHandler;
	oldHandler = _set_invalid_parameter_handler(newHandler);



	// Disable the message box for assertions.
	_CrtSetReportMode(_CRT_ASSERT, 0);

	// Call printf_s with invalid parameters.

//	newfunc = _RTC_SetErrorFuncW(oldfunction);


	auto hDLL = LoadLibraryA(R"(D:\repos\mDNSResponder\Clients\DNS-SD.VisualStudio\x64\release\dns-sd.dll)");
//	auto t1 = std::thread(call_from_thread, argc, argv);

	auto _LPrunDNSSDFromThread = (LPrunDNSSDFromThread)GetProcAddress((HMODULE)hDLL, "runDNSSDFromThread");
	auto _LPgetResolution = (LPgetResolution)GetProcAddress((HMODULE)hDLL, "getResolution");

	(*_LPrunDNSSDFromThread)( argc,  argv);




	char ip[512];
	while (cnt<5)
	{
		if ((*_LPgetResolution)("ROSCore.local.",ip))
		{
			printf("res:%s\n", ip);
		}

		printf("poll...\n");
		cnt++;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	printf("Control-C sent...\n");
	std::this_thread::sleep_for(std::chrono::seconds(2));
	auto b=FreeLibrary(hDLL);
	printf("FreeLibrary called first...%d\n", b);
	try
	{

		b = FreeLibrary(hDLL);
	}
	catch (...)
	{

	}
	printf("FreeLibrary called second...%d\n",b);
	std::this_thread::sleep_for(std::chrono::seconds(2));
	//stopDNS();
//	t1.join();


    return 0;
}

