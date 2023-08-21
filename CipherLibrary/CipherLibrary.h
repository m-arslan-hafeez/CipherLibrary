#pragma once
#include <sstream>
#include <iostream>
#include <stdio.h>

#ifdef CIPHERLIBRARY_EXPORTS
#define CIPHERLIBRARY_API __declspec(dllexport)
#else
#define CIPHERLIBRARY_API __declspec(dllimport)
#endif

using namespace std;

extern "C" {
	CIPHERLIBRARY_API void getEncryptedResult(const char* inputFilePath, const char* outputFilePath, int key);
	CIPHERLIBRARY_API void getDecryptedResult(const char* inputFilePath, const char* outputFilePath, int key);
	CIPHERLIBRARY_API const char* __stdcall getString();
	CIPHERLIBRARY_API void setMessage(const char* message);
	CIPHERLIBRARY_API const char* __stdcall getMessage();
}

