// dns-sd-client-app.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <thread>
#include <chrono>
using namespace std;

//extern "C"
//{
__declspec(dllimport)	int oldMain(int argc, char **argv);
__declspec(dllimport) bool getResolution(string name, string &ip);
//}


void call_from_thread(int argc, char **argv)
{
	oldMain(argc, argv);
	//std::cout << "Hello, World" << std::endl;
	
	
}

int main(int argc, char **argv)
{
	auto t1 = std::thread(call_from_thread, argc, argv);
	string ip;
	while (true)
	{
		if (getResolution("ROSCore.local.",ip))
		{
			printf("res:%s\n", ip.c_str());
		}

		printf("poll...\n");
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	t1.join();


    return 0;
}

