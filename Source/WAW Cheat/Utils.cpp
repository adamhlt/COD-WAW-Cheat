#include "Utils.h"

/**
 * World to screen method, it's convert 3d position to 2d position to draw on screen.
 * \param pos : entity vec3 (3d) position
 * \param screen : structure to store the position to draw on screen
 * \param matrix : address of the view matrix 
 * \param windowWidth : width of the game window
 * \param windowHeight : height of the game window
 * \return : boolean true if success else false
 */
bool Utils::WorldToScreen(const Vec3 pos, Vec2& screen, float matrix[16], const int windowWidth, const int windowHeight)
{
	Vec4 clipCoords = {};
	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
	clipCoords.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
	clipCoords.z = pos.x * matrix[8] + pos.y * matrix[9] + pos.z * matrix[10] + matrix[11];
	clipCoords.w = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];

	if (clipCoords.w < 0.1f)
		return false;

	Vec3 NDC = {};
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = ((float)windowWidth / static_cast<float>(2) * NDC.x) + (NDC.x + (float)windowWidth / static_cast<float>(2));
	screen.y = -((float)windowHeight / static_cast<float>(2) * NDC.y) + (NDC.y + (float)windowHeight / static_cast<float>(2));
	return true;
}