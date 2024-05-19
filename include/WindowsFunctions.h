//
// Created by HORIA on 19.05.2024.
//

#ifndef IMAGEBANANA_WINDOWSFUNCTIONS_H
#define IMAGEBANANA_WINDOWSFUNCTIONS_H

// Define necessary Windows types
typedef void* HMODULE;
typedef const char* LPCSTR;
typedef unsigned long DWORD;
typedef int BOOL;
typedef void* FARPROC;

__declspec(dllimport) HMODULE __stdcall LoadLibraryA(LPCSTR lpLibFileName);
__declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE hModule, LPCSTR lpProcName);
__declspec(dllimport) BOOL __stdcall FreeLibrary(HMODULE hModule);
__declspec(dllimport) DWORD __stdcall GetLastError();
__declspec(dllimport) BOOL __stdcall CopyFileA(LPCSTR lpExistingFileName, LPCSTR lpNewFileName, BOOL bFailIfExists);

#endif //IMAGEBANANA_WINDOWSFUNCTIONS_H
