// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "CipherLibrary.h"
#include <fstream>
#include <iostream>

#pragma unmanaged



BOOL APIENTRY CipherLibrary( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

static std::string encryptFile(const std::string& input, int key)
{
	std::string result = input;
	for (char& c : result)
	{
		c = static_cast<char>(c + key - 100929);
	}
	return result;
}

static std::string decryptFile(const std::string& input, int key)
{
	std::string result = input;
	for (char& c : result)
	{
		c = static_cast<char>(c - key + 100929);
	}
	return result;
}

CIPHERLIBRARY_API void getEncryptedResult(const char* inputFilePath, const char* outputFilePath, int key)
{
	try
	{
		std::ifstream inputFile(inputFilePath);
		std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
		inputFile.close();

		std::string encryptedContent = encryptFile(content, key);

		std::ofstream outputFile(outputFilePath);
		outputFile << encryptedContent;
		outputFile.close();
	}
	catch (const std::exception& ex)
	{
		MessageBoxA(nullptr, ("An error occurred: " + std::string(ex.what())).c_str(), "Error", MB_OK);
	}
}

CIPHERLIBRARY_API void getDecryptedResult(const char* inputFilePath, const char* outputFilePath, int key)
{
	try
	{
		std::ifstream inputFile(inputFilePath);
		std::string content((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());
		inputFile.close();

		std::string decryptedContent = decryptFile(content, key);

		std::ofstream outputFile(outputFilePath);
		outputFile << decryptedContent;
		outputFile.close();
	}
	catch (const std::exception& ex)
	{
		MessageBoxA(nullptr, ("An error occurred: " + std::string(ex.what())).c_str(), "Error", MB_OK);
	}
}

