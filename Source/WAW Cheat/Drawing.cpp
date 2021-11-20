#include "pch.h"
#include "Drawing.h"
#include "Hook.h"
#include "Core.h"

BOOL Drawing::bInit = FALSE;
bool Drawing::bExit = false;
bool Drawing::bDisplay = true;
bool Drawing::bDisplayOverlay = true;

/**
 * EndScene hook, used to draw imgui menu and visual features like esp line
 * \param D3D9Device : DirectX device created in Hook
 * \return : HRESULT from the original EndScene function
 */
HRESULT Drawing::hkEndScene(const LPDIRECT3DDEVICE9 D3D9Device)
{
	if (!Hook::pDevice)
		Hook::pDevice = D3D9Device;

	if (bExit)
		Hook::UnHookEndSceneAndExit();

	if (!bInit)
		InitImGui(D3D9Device);

	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDisplay = !bDisplay;

	DisplayImGui();

	return Hook::oEndScene(D3D9Device);
}

/**
 * Function to init imgui
 * \param D3D9Device : DirectX device created in Hook
 */
void Drawing::InitImGui(const LPDIRECT3DDEVICE9 D3D9Device)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.IniFilename = nullptr;
	io.Fonts->AddFontDefault();

	ImGui::StyleColorsDark();
	ImGui_ImplWin32_Init(Hook::window);
	ImGui_ImplDX9_Init(D3D9Device);

	bInit = TRUE;
}

/**
 * Function to display imgui ui like the overlay and the menu
 */
void Drawing::DisplayImGui()
{
	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (bDisplay)
		DisplayImGuiMenu();

	if (bDisplayOverlay)
		DisplayImGuiOverlay();

	Core::Run();

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}

/**
 * Function to display the cheat menu
 */
void Drawing::DisplayImGuiMenu()
{
	const ImGuiViewport* main_viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x + 650, main_viewport->WorkPos.y + 20), ImGuiCond_FirstUseEver);
	ImGui::SetNextWindowSize(ImVec2(550, 680), ImGuiCond_FirstUseEver);

	if (!ImGui::Begin("Call Of Duty : World at War Zombie Cheat", &bDisplay, 0))
		ImGui::End();

	constexpr ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_FittingPolicyResizeDown;
	if (ImGui::BeginTabBar("Feature Tabs", tab_bar_flags))
	{
		if (ImGui::BeginTabItem("Host"))
		{
			ImGui::Checkbox("GodMode", &Core::bGodMode);
			ImGui::Checkbox("Infinite Point", &Core::bInfinitePoint);
			ImGui::Checkbox("Infinite Ammo", &Core::bInfiniteAmmo);
			ImGui::Checkbox("NoClip", &Core::bNoClip);
			ImGui::Checkbox("Super Knife", &Core::bSuperKnife);
			ImGui::Checkbox("No Target", &Core::bNoTarget);
			ImGui::Checkbox("OneShot Kill", &Core::bOneShotKill);
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Visual"))
		{
			ImGui::Checkbox("In-Game Overlay", &bDisplayOverlay);
			ImGui::Checkbox("Toggle Laser", &Core::bLaser);
			ImGui::Checkbox("FOV Changer", &Core::bFOV);
			ImGui::SliderFloat("FOV", &Core::fFOV, 10, 180);
			ImGui::Checkbox("Show FPS", &Core::bFPS);
			ImGui::Checkbox("Show Version", &Core::bVersion);
			ImGui::Checkbox("Third Person View", &Core::bThirdPerson);
			ImGui::InputText("Name", Core::sName, 16);
			if (ImGui::Button("Change Name"))
				Core::bNameSpoofer = true;
			ImGui::Checkbox("ESP Line", &Core::bESPLine);
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Teleport"))
		{
			ImGui::Text("Teleport Position :");
			ImGui::Text("X : %f", (double) Core::vTeleportPosition.x);
			ImGui::Text("Y : %f", (double)Core::vTeleportPosition.y);
			ImGui::Text("Z : %f", (double)Core::vTeleportPosition.z);
			if (ImGui::Button("Save Location"))
				Core::bSavePositionToTelelport = true;
			ImGui::Separator();
			ImGui::Checkbox("Teleport Zombies", &Core::bTeleportEntities);
			ImGui::EndTabItem();
		}

		if (ImGui::BeginTabItem("Config"))
		{
			if (ImGui::Button("Uninject Cheat"))
				bExit = true;
			ImGui::EndTabItem();
		}
		ImGui::EndTabBar();
	}

	ImGui::End();
}

/**
 * Function to display the cheat overlay
 */
void Drawing::DisplayImGuiOverlay()
{
	const ImGuiIO& io = ImGui::GetIO();
	constexpr ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav;
	ImGui::SetNextWindowBgAlpha(0.35f); // Transparent background
	if (ImGui::Begin("Call Of Duty : World at War", &bDisplayOverlay, window_flags))
	{
		ImGui::Text("Call Of Duty : World at War Zombie Cheat");
		ImGui::Separator();
		ImGui::Text("FPS : %.0f", (double)io.Framerate);
	}
	ImGui::End();
}

/**
 * Function to draw a line with DirectX 9
 * \param x : x coordinate of the fist point
 * \param y : y coordinate of the first point
 * \param x1 : x coordinate of the second point
 * \param y1 : y coordinate of the second point
 * \param thickness : width of the line
 * \param color : color of the line
 */
void Drawing::DrawLine(const int x, const int y, const int x1, const int y1, const int thickness, const D3DCOLOR color)
{
	ID3DXLine* LineL;
	D3DXCreateLine(Hook::pDevice, &LineL);

	D3DXVECTOR2 Line[2];
	Line[0] = D3DXVECTOR2((float)x, (float)y);
	Line[1] = D3DXVECTOR2((float)x1, (float)y1);
	LineL->SetWidth((float)thickness);
	LineL->Draw(Line, 2, color);
	LineL->Release();
}
