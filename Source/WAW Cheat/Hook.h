#ifndef HOOK_H
#define HOOK_H

#include "pch.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam); // imgui control handler
typedef HRESULT(APIENTRY* tEndScene)(LPDIRECT3DDEVICE9 pDevice); // EndScene function type 

class Hook
{
public:
	static IDirect3DDevice9* pDevice; // DirectX 9 device
	static tEndScene oEndScene; // original EndScene address
	static HWND window; // game window
	static HMODULE hModule; // cheat dll module

	static void HookEndScene();
	static void UnHookEndScene();
	static void UnHookEndSceneAndExit();
	static void HookWindow();

private:
	static int windowHeight, windowWidth; // height and width of the game window
	static void* d3d9Device[119]; // DirectX 9 vtable
	static WNDPROC OWndProc; // original WNDPROC callback function


	static BOOL CALLBACK enumWind(HWND handle, LPARAM lp);
	static HWND GetProcessWindow();
	static BOOL GetD3D9Device(void** pTable, size_t size);
	static LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
};

#endif