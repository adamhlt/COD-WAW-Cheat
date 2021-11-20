#include "pch.h"
#include "Core.h"
#include "Hook.h"
#include "Drawing.h"

bool Core::bGodMode = false;
bool Core::bNoClip = false;
bool Core::bFOV = false;
bool Core::bLaser = false;
bool Core::bFPS = false;
bool Core::bVersion = false;
bool Core::bThirdPerson = false;
bool Core::bSuperKnife = false;
bool Core::bNameSpoofer = false;
bool Core::bNoTarget = false;
bool Core::bInfiniteAmmo = false;
bool Core::bInfinitePoint = false;
bool Core::bOneShotKill = false;
bool Core::bTeleportEntities = false;
bool Core::bSavePositionToTelelport = false;
bool Core::bESPLine = false;

bool Core::bEnableGodMode = false;
bool Core::bEnableNoClip = false;
bool Core::bEnableFOV = false;
bool Core::bEnableLaser = false;
bool Core::bEnableFPS = false;
bool Core::bEnableVersion = false;
bool Core::bEnableThirdPerson = false;
bool Core::bEnableSuperKnife = false;
bool Core::bEnableNoTarget = false;
bool Core::bEnableInfiniteAmmo = false;
bool Core::bEnableInfinitePoint = false;

float Core::fFOV = 65.0f;
char Core::sName[16];
Utils::Vec3 Core::vTeleportPosition = { 0, 0, 0 };

Utils::Entity Core::eEntityList[23];
unsigned char Core::OriginalBytesAmmo[7] = {0x89, 0x84, 0x8F, 0xFC, 0x05, 0x00, 0x00};
unsigned char Core::PatchedByteAmmo[7] = {0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x90};
unsigned char Core::OriginalBytesMoney[6] = {0x89, 0xB7, 0xBC, 0x20, 0x00, 0x00};
unsigned char Core::PatchedByteMoney[6] = {0x90, 0x90, 0x90, 0x90, 0x90, 0x90};

/**
 * Cheat loop which call every cheat features
 */
void Core::Run()
{
	if (!InGame())
	{
		// If the player is not in a game
		// reset the saved position and disable teleport
		vTeleportPosition = { 0, 0, 0 };
		bTeleportEntities = false;
		return;
	}

	GetEntities();
	OneShotKill();
	SavePositionToTeleport();
	FreezeEntitiesToPosition();
	GodMode();
	NoClip();
	FOV();
	ToggleLaser();
	ShowFPS();
	ShowVersion();
	ToogleThridPerson();
	SuperKnife();
	NameSpoofer();
	NoTarget();
	InfiniteAmmo();
	InfinitePoint();
	ESPLine();
}

/**
 * Godmode function
 */
void Core::GodMode()
{
	if (bGodMode && !bEnableGodMode)
	{
		*(DWORD*)(0x176C8A4) = *(int*)(0x176C8A4) ^ 1;
		bEnableGodMode = true;
	}

	if (!bGodMode && bEnableGodMode)
	{
		*(DWORD*)(0x176C8A4) = *(int*)(0x176C8A4) ^ 1;
		bEnableGodMode = false;
	}

	// check the state if the game restart or end
	const int iCurrentState = *(int*)(0x176C8A4);
	if ((iCurrentState == 2048 && bEnableGodMode) || (iCurrentState == 2052 && bEnableGodMode))
		bEnableGodMode = false;
}

/**
 * Noclip function
 */
void Core::NoClip()
{
	if (bNoClip && !bEnableNoClip)
	{
		*(DWORD*)(*(DWORD*)(0x176C6F0 + 0x180) + 0x223c) += 1;
		bEnableNoClip = true;
	}

	if (!bNoClip && bEnableNoClip)
	{
		*(DWORD*)(*(DWORD*)(0x176C6F0 + 0x180) + 0x223c) -= 1;
		bEnableNoClip = false;
	}

	// check the state if the game restart or end
	const int iCurrentState = *(int*)(*(DWORD*)(0x176C6F0 + 0x180) + 0x223c);
	if (iCurrentState == 0 && bEnableNoClip)
		bEnableNoClip = false;
}

/**
 * FOV changer function
 */
void Core::FOV()
{
	if (bFOV && !bEnableFOV)
	{
		*(float*)(*(DWORD*)(0x368EB70) + 0x10) = fFOV;
		bEnableFOV = true;
	}

	if (!bFOV && bEnableFOV)
	{
		*(float*)(*(DWORD*)(0x368EB70) + 0x10) = 65.0f;
		bEnableFOV = false;
	}

	// check the state if the game restart or end
	const float fCurrentFOV = *(float*)(*(DWORD*)(0x368EB70) + 0x10);
	if (fFOV != fCurrentFOV && bFOV)
		*(float*)(*(DWORD*)(0x368EB70) + 0x10) = fFOV;
}

/**
 * Display laser function
 */
void Core::ToggleLaser()
{
	if (bLaser && !bEnableLaser)
	{
		*(DWORD*)(*(DWORD*)(0x3688A1C) + 0x10) += 1;
		bEnableLaser = true;
	}

	if (!bLaser && bEnableLaser)
	{
		*(DWORD*)(*(DWORD*)(0x3688A1C) + 0x10) -= 1;
		bEnableLaser = false;
	}

	// check the state if the game restart or end
	const int iCurrentState = *(int*)(*(DWORD*)(0x3688A1C) + 0x10);
	if (iCurrentState == 0 && bEnableLaser)
		bEnableLaser = false;
}

/*
 * Display FPS function
 */
void Core::ShowFPS()
{
	if (bFPS && !bEnableFPS)
	{
		*(DWORD*)(*(DWORD*)(0x339CC00) + 0x10) += 1;
		bEnableFPS = true;
	}

	if (!bFPS && bEnableFPS)
	{
		*(DWORD*)(*(DWORD*)(0x339CC00) + 0x10) -= 1;
		bEnableFPS = false;
	}

	// check the state if the game restart or end
	const int iCurrentState = *(int*)(*(DWORD*)(0x339CC00) + 0x10);
	if (iCurrentState == 0 && bEnableFPS)
		bEnableFPS = false;
}

/**
 * Display version function
 */
void Core::ShowVersion()
{
	if (bVersion && !bEnableVersion)
	{
		*(DWORD*)(*(DWORD*)(0x339B748) + 0x10) += 1;
		bEnableVersion = true;
	}

	if (!bVersion && bEnableVersion)
	{
		*(DWORD*)(*(DWORD*)(0x339B748) + 0x10) -= 1;
		bEnableVersion = false;
	}

	// check the state if the game restart or end
	const int iCurrentState = *(int*)(*(DWORD*)(0x339B748) + 0x10);
	if (iCurrentState == 0 && bEnableVersion)
		bEnableVersion = false;
}

/**
 * Third person view function
 */
void Core::ToogleThridPerson()
{
	if (bThirdPerson && !bEnableThirdPerson)
	{
		*(DWORD*)(*(DWORD*)(0x339CC14) + 0x10) += 1;
		bEnableThirdPerson = true;
	}

	if (!bThirdPerson && bEnableThirdPerson)
	{
		*(DWORD*)(*(DWORD*)(0x339CC14) + 0x10) -= 1;
		bEnableThirdPerson = false;
	}

	// check the state if the game restart or end
	const int iCurrentState = *(int*)(*(DWORD*)(0x339CC14) + 0x10);
	if (iCurrentState == 0 && bEnableThirdPerson)
		bEnableThirdPerson = false;
}

/**
 * Increase melee range function
 */
void Core::SuperKnife()
{
	if (bSuperKnife && !bEnableSuperKnife)
	{
		*(float*)(0x021CCADC) = 999.0f;
		bEnableSuperKnife = true;
	}

	if (!bSuperKnife && bEnableSuperKnife)
	{
		*(float*)(0x021CCADC) = 64.0f;
		bEnableSuperKnife = false;
	}

	// check the state if the game restart or end
	const float iCurrentState = *(float*)(0x021CCADC);
	if (iCurrentState != 999.0f && bEnableSuperKnife)
		bEnableSuperKnife = false;
}

/**
 * Name spoofer function
 */
void Core::NameSpoofer()
{
	if (bNameSpoofer)
	{
		memset((void*)0x018EF258, 0, 16);
		memcpy((void*)0x018EF258, &sName, 16);
		bNameSpoofer = false;
	}
}

/**
 * Disable zombies attack function
 */
void Core::NoTarget()
{
	if (bNoTarget && !bEnableNoTarget)
	{
		*(DWORD*)(0x176C8A4) = *(int*)(0x176C8A4) ^ 4;
		bEnableNoTarget = true;
	}

	if (!bNoTarget && bEnableNoTarget)
	{
		*(DWORD*)(0x176C8A4) = *(int*)(0x176C8A4) ^ 4;
		bEnableNoTarget = false;
	}

	// Check the state if the game restart or end
	const int iCurrentState = *(int*)(0x176C8A4);
	if ((iCurrentState == 2048 && bEnableNoTarget) || (iCurrentState == 2049 && bEnableNoTarget))
		bEnableNoTarget = false;
}

/**
 * Infinite ammo function
 */
void Core::InfiniteAmmo()
{
	if (bInfiniteAmmo && !bEnableInfiniteAmmo)
	{
		DWORD dOldProtect = 0;
		DWORD dLastProtect = 0;

		// Change memory protection to not trigger access violation
		if (VirtualProtect((void*)0x41E619, 7, PAGE_EXECUTE_READWRITE, &dOldProtect) == 0) 
			return;

		memcpy((void*)0x41E619, &PatchedByteAmmo, 7);
		bEnableInfiniteAmmo = true;

		// Restore memory protection
		VirtualProtect((void*)0x41E619, 7, dOldProtect, &dLastProtect);
	}

	if (!bInfiniteAmmo && bEnableInfiniteAmmo)
	{
		DWORD dOldProtect = 0;
		DWORD dLastProtect = 0;

		// Change memory protection to not trigger access violation
		if (VirtualProtect((void*)0x41E619, 7, PAGE_EXECUTE_READWRITE, &dOldProtect) == 0)
			return;

		memcpy((void*)0x41E619, &OriginalBytesAmmo, 7);
		bEnableInfiniteAmmo = false;

		// Restore memory protection
		VirtualProtect((void*)0x41E619, 7, dOldProtect, &dLastProtect);
	}
}

/**
 * Function to give points to the player and block the amount of points
 */
void Core::InfinitePoint()
{
	if (bInfinitePoint && !bEnableInfinitePoint)
	{
		DWORD dOldProtect = 0;
		DWORD dLastProtect = 0;

		if (VirtualProtect((void*)0x4ED2F5, 6, PAGE_EXECUTE_READWRITE, &dOldProtect) == 0)
			return;

		memcpy((void*)0x4ED2F5, &PatchedByteMoney, 6);
		*(int*)(0x018EF124) = 100000;
		bEnableInfinitePoint = true;

		VirtualProtect((void*)0x4ED2F5, 6, dOldProtect, &dLastProtect);
	}

	if (!bInfinitePoint && bEnableInfinitePoint)
	{
		DWORD dOldProtect = 0;
		DWORD dLastProtect = 0;

		if (VirtualProtect((void*)0x4ED2F5, 6, PAGE_EXECUTE_READWRITE, &dOldProtect) == 0)
			return;

		memcpy((void*)0x4ED2F5, &OriginalBytesMoney, 6);
		bEnableInfinitePoint = false;

		VirtualProtect((void*)0x4ED2F5, 6, dOldProtect, &dLastProtect);
	}

	// check the state if the game restart or end
	const int iCurrentState = *(int*)(0x018EF124);
	if (iCurrentState < 100000 && bEnableInfinitePoint)
		*(int*)(0x018EF124) = 100000;
}

/**
 * Function to retrieve every alive zombies and put them in a list
 */
void Core::GetEntities()
{
	memset(eEntityList, 0, 23*sizeof(Utils::Entity));
	int iNumberOfEntities = 0;
	for (int i = 1; i < 40; ++i)
	{
		const DWORD dEntityPtr = (0x18E73C0 + (0x88 * i));
		const DWORD dEntityAddress = *(DWORD*)(dEntityPtr);
		if (dEntityAddress == 0)
			continue;

		const int iEntityType = *(int*)(dEntityAddress + 0x4);
		if (iEntityType != 16)
			continue;

		const int iEntityhealth = *(int*)(dEntityAddress + 0x1C8);
		if (iEntityhealth <= 0)
			continue;

		eEntityList[iNumberOfEntities] = Utils::Entity{
			(Utils::Vec3*)(dEntityAddress + 0x160),
			(Utils::Vec3*)(dEntityAddress + 0x154),
			(int*)(dEntityAddress + 0x1C8),
			(int*)(dEntityAddress + 0x1CC)
		};
		iNumberOfEntities++;
	}
}

/**
 * Function to put zombie's health to 1 
 */
void Core::OneShotKill()
{
	if (bOneShotKill)
	{
		for (int i = 0; i < 23; ++i)
		{
			if (eEntityList[i].entityPos != nullptr)
			{
				const int iCurrentHealth = *(eEntityList[i].iHealth);
				if (iCurrentHealth > 1)
					*(eEntityList[i].iHealth) = 1;
			}
		}
	}
}

/**
 * Function to freeze all zombies and teleport them to the saved position
 */
void Core::FreezeEntitiesToPosition()
{
	const bool bSavedPosition = (vTeleportPosition.x != 0 && vTeleportPosition.y != 0 && vTeleportPosition.z != 0);
	if (bTeleportEntities && bSavedPosition)
	{
		for (int i = 0; i < 23; ++i)
		{
			if (eEntityList[i].entityPos != nullptr)
			{
				eEntityList[i].entityPos->x = vTeleportPosition.x;
				eEntityList[i].entityPos->y = vTeleportPosition.y;
				eEntityList[i].entityPos->z = vTeleportPosition.z;
			}
		}
	}
}

/**
 * Function to save the current position of the locaplayer
 */
void Core::SavePositionToTeleport()
{
	if (bSavePositionToTelelport)
	{
		vTeleportPosition.x = *(float*)(0x0176C850);
		vTeleportPosition.y = *(float*)(0x0176C854);
		vTeleportPosition.z = *(float*)(0x0176C858);
		bSavePositionToTelelport = false;
	}
}

/**
 * Function to ESP lines to every alive zombies
 */
void Core::ESPLine()
{
	if (bESPLine)
	{
		auto* pViewMatrix = (float*)(0x008E870C);
		RECT rect;
		for (int i = 0; i < 23; ++i)
		{
			if (eEntityList[i].entityPos == nullptr)
				return;

			if (!GetWindowRect(Hook::window, &rect))
				return;
				
			const int width = rect.right - rect.left;
			const int height = rect.bottom - rect.top;

			const Utils::Vec3 vPos = *(eEntityList[i].entityPos);
			Utils::Vec2 vEntityPos;

			if (Utils::WorldToScreen(vPos, vEntityPos, pViewMatrix, width, height))
				Drawing::DrawLine((int)vEntityPos.x, (int)vEntityPos.y, width/2, height, 1, D3DCOLOR_ARGB(255, 0, 255, 0));
		}
	}
}

/**
 * Function to check the localplayer state
 * \return : true if the is in a game, else false
 */
bool Core::InGame()
{
	return *(DWORD*)(0x176C8A4) != 0;
}


