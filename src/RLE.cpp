// RLE.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PackMachine.h"
#include "UnpackMachine.h"

void PrintUsageData(const char programPath[])
{
	printf("Usage: %s [ pack / unpack ] <input file> <output file>\n", programPath);
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (argc == 4)
	{
		if (strcmp(argv[1], "pack") == 0)
		{
			try
			{
				CPackMachine packMachine(argv[3]);
				packMachine.SendFile(argv[2]);
				return 0;
			}
			catch (std::runtime_error const& e)
			{
				puts(e.what());
				return 1;
			}
		}
		else if (strcmp(argv[1], "unpack") == 0)
		{
			try
			{
				CUnpackMachine unpackMachine(argv[3]);
				unpackMachine.SendFile(argv[2]);
				return 0;
			}
			catch (std::runtime_error const& e)
			{
				puts(e.what());
				return 1;
			}
		}
		else
		{
			assert(argc > 0);
			PrintUsageData(argv[0]);
			return 2;
		}
	}
	else
	{
		assert(argc > 0);
		PrintUsageData(argv[0]);
		return 2;
	}
}
