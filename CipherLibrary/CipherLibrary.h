#pragma once
#ifdef CIPHERLIBRARY_EXPORTS
#define CIPHERLIBRARY_API __declspec(dllexport)
#else
#define CIPHERLIBRARY_API __declspec(dllimport)
#endif

#include <string>

extern "C" {
	CIPHERLIBRARY_API void getEncryptedResult(const char* inputFilePath, const char* outputFilePath, int key);
	CIPHERLIBRARY_API void getDecryptedResult(const char* inputFilePath, const char* outputFilePath, int key);
}
