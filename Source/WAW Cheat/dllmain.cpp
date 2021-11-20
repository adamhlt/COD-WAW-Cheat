#include "pch.h"
#include "Hook.h"

// Intialize the cheat routine
void Initialize(const HMODULE hModule)
{
	Hook::hModule = hModule;
	Hook::HookEndScene();
}

// DLL Entrypoint  
BOOL WINAPI DllMain(const HINSTANCE hinstDLL, const DWORD fdwReason, LPVOID lpReserved)
{
	if (fdwReason == DLL_PROCESS_ATTACH)
	{
		const HANDLE hThread = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Initialize, hinstDLL, 0, nullptr);
		if (hThread != INVALID_HANDLE_VALUE && hThread != nullptr)
			CloseHandle(hThread);
	}

	return TRUE;
}

