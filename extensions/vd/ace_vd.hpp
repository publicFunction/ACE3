#pragma once

#if defined(_DLL)
extern "C" {
	__declspec (dllexport) void __stdcall RVExtension(char *output, int outputSize, const char *function);
};
#elif defined(_STATIC)
extern "C" {
	void __stdcall RVExtension(char *output, int outputSize, const char *function);
};
#endif

#if defined(_IMPORT_VD)
extern "C" {
	__declspec (dllimport) void __stdcall RVExtension(char *output, int outputSize, const char *function);
};
#else
extern "C" {
	void __stdcall RVExtension(char *output, int outputSize, const char *function);
};
#endif