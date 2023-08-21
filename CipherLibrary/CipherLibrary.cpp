// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "CipherLibrary.h"
#include <mutex>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

static string gMessage;
static mutex gMessageMutex;

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

static string encryptFile(const string& input, int key)
{
	string result = input;
	for (char& c : result)
	{
		c = static_cast<char>(c + key + 835294858);
	}
	return result;
}

static string decryptFile(const string& input, int key)
{
	string result = input;
	for (char& c : result)
	{
		c = static_cast<char>(c - key - 835294858);
	}
	return result;
}

CIPHERLIBRARY_API void getEncryptedResult(const char* inputFilePath, const char* outputFilePath, int key)
{
	try
	{
		ifstream inputFile(inputFilePath);
		string content((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
		inputFile.close();
		string encryptedContent = encryptFile(content, key);
		ofstream outputFile(outputFilePath);
		outputFile << encryptedContent;
		outputFile.close();
	}
	catch (const exception& ex)
	{
		MessageBoxA(nullptr, ("An error occurred: " + string(ex.what())).c_str(), "Error", MB_OK);
	}
}

CIPHERLIBRARY_API void getDecryptedResult(const char* inputFilePath, const char* outputFilePath, int key)
{
	try
	{
		ifstream inputFile(inputFilePath);
		string content((istreambuf_iterator<char>(inputFile)), istreambuf_iterator<char>());
		inputFile.close();

		string decryptedContent = decryptFile(content, key);

		ofstream outputFile(outputFilePath);
		outputFile << decryptedContent;
		outputFile.close();
	}
	catch (const exception& ex)
	{
		MessageBoxA(nullptr, ("An error occurred: " + string(ex.what())).c_str(), "Error", MB_OK);
	}
}

CIPHERLIBRARY_API const char* __stdcall getString()
{
	return "Hello from Cipher!";	 
}

CIPHERLIBRARY_API void setMessage(const char* message)
{
	std::lock_guard<std::mutex> lock(gMessageMutex);
	gMessage = message;
}

CIPHERLIBRARY_API const char* __stdcall getMessage()
{
	std::lock_guard<std::mutex> lock(gMessageMutex);
	return gMessage.c_str();
}


