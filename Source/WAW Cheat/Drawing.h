#ifndef DRAWING_H
#define DRAWING_H

#include "pch.h"

class Drawing
{
public:
	static bool bExit; // boolean to unhook the dll
	static bool bDisplay; // boolean to display the cheat menu
	static bool bDisplayOverlay; // boolean to display the cheat overlay
	static BOOL bInit; // boolean to initialize imgui

	static HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 D3D9Device);
	static void DrawLine(int x, int y, int x1, int y1, int thickness, D3DCOLOR color); // 

private:
	static void InitImGui(LPDIRECT3DDEVICE9 D3D9Device);
	static void DisplayImGui();
	static void DisplayImGuiMenu();
	static void DisplayImGuiOverlay();
};

#endif