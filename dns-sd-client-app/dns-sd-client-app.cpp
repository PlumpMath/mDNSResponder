// dns-sd-client-app.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

extern "C"
{
	int oldMain(int argc, char **argv);
}


int main(int argc, char **argv)
{
	oldMain(argc, argv);

    return 0;
}

