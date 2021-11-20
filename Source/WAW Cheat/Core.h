#ifndef CORE_H
#define CORE_H

#include "Utils.h"

class Core
{
public:
	static bool bGodMode; // boolean to enable godmode
	static bool bNoClip; // boolean to enable noclip
	static bool bFOV; // boolean to change fov
	static bool bLaser; // boolean to show weapon laser
	static bool bFPS; // boolean to show fps
	static bool bVersion; // boolean to show version
	static bool bThirdPerson; // boolean to enable third person view
	static bool bSuperKnife; // boolean to increase melee range
	static bool bNameSpoofer; // boolean to change player username
	static bool bNoTarget; // boolean to disable zombies attack
	static bool bInfiniteAmmo; // boolean to enable infinite ammo
	static bool bInfinitePoint; // boolean to enable infinite point
	static bool bOneShotKill; // boolean to enable one shot kill on zombies
	static bool bTeleportEntities; // boolean to teleport all zombies
	static bool bSavePositionToTelelport; // boolean to save the current position
	static bool bESPLine; // boolean to enable esp line

	static float fFOV; // float fov value
	static char sName[16]; // char array to store the new username
	static Utils::Vec3 vTeleportPosition; // vec3 structure to store the teleport position

	static void Run(); // function to call every features functions

private:
	static bool bEnableGodMode; // boolean of the godmode status 
	static bool bEnableNoClip; // boolean of the noclip status 
	static bool bEnableFOV; // boolean of the fov changer status 
	static bool bEnableLaser; // boolean of the laser status
	static bool bEnableFPS; // boolean of the show fps status 
	static bool bEnableVersion; // boolean of the show version status
	static bool bEnableThirdPerson; // boolean of the third view status
	static bool bEnableSuperKnife; // boolean of the melee increase status
	static bool bEnableNoTarget; // boolean of the notarget status
	static bool bEnableInfiniteAmmo; // boolean of the infinite ammo status
	static bool bEnableInfinitePoint; // boolean of the infinite point status

	static unsigned char OriginalBytesAmmo[7]; // buffer of the original opcode of infinite ammo
	static unsigned char PatchedByteAmmo[7]; // buffer of the patched opcode of infinite ammo
	static unsigned char OriginalBytesMoney[6]; // buffer of the original opcode of infinite point
	static unsigned char PatchedByteMoney[6]; // buffer of the patched opcode of infinite point
	static Utils::Entity eEntityList[23]; // Zombies entity list

	static void GodMode();
	static void NoClip();
	static void FOV();
	static void ToggleLaser();
	static void ShowFPS();
	static void ShowVersion();
	static void ToogleThridPerson();
	static void SuperKnife();
	static void NameSpoofer();
	static void NoTarget();
	static void InfiniteAmmo();
	static void InfinitePoint();
	static void GetEntities();
	static void OneShotKill();
	static void FreezeEntitiesToPosition();
	static void SavePositionToTeleport();
	static void ESPLine();

	static bool InGame();
};


#endif
