#include <stdio.h>
#include <windows.h>
#include <chrono>
#include <filesystem>
#include <string>
#include <iostream>


int main(int argc, char* argv[])
{

	printf("\nLoaderTester.exe - Module load test utility \n");
	printf("Created by Leonardo Fagundes. No rights reserved.\n\n");


	auto start = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed;

	HANDLE hModule = NULL;
	namespace fs = std::filesystem;

	CHAR szExePath[256] = {};
	CHAR szPath[256] = {};
	CHAR* pExename;
	int BuffSize = 256;
	int Exelen = 0;
	int PathLen = 0;

	GetModuleFileName(NULL, szExePath, BuffSize);

	pExename = strrchr(szExePath, L'\\') +1 ;

	Exelen = strlen(pExename) + 1;
	PathLen = strlen(szExePath) - Exelen;

	strncpy_s(szPath, 255, szExePath, PathLen);


	std::string path(szPath);

	printf("Searching and loading DLLs in path: %s\n", path.c_str());


	for (const auto& entry : fs::directory_iterator(path))
	{

		if (entry.path().extension().compare(".dll") == 0)
		{
			//printf("path: %S\n", entry.path().c_str());

			hModule = LoadLibraryW((LPCWSTR)entry.path().c_str());

			if (hModule == NULL)
			{
				printf("Error %d loading %S\n", GetLastError(), entry.path().c_str());

			}
			else {

				//capture Parcial time
				auto Parcial = std::chrono::high_resolution_clock::now();

				elapsed = Parcial - start;

				printf("%0.7f seconds loading %S\n", elapsed, entry.path().c_str());

			}

		}

	}
	

	//Capture and display elapsed time
	auto finish = std::chrono::high_resolution_clock::now();

	elapsed = finish - start;
	
	printf("\nTotal elapsed time: %0.7f seconds\n\n\Press ENTER to continue...", elapsed);


	
	(void)getchar();

}


