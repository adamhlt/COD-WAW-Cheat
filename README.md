![Banner](https://github.com/adamhlt/COD-WAW-Cheat/blob/main/Ressources/img/banner.png)

# Call of Duty : World at War Cheat

 [![C++](https://img.shields.io/badge/language-C%2B%2B-%23f34b7d.svg?style=for-the-badge&logo=appveyor)](https://en.wikipedia.org/wiki/C%2B%2B)  [![Windows](https://img.shields.io/badge/platform-Windows-0078d7.svg?style=for-the-badge&logo=appveyor)](https://en.wikipedia.org/wiki/Microsoft_Windows)  [![x86](https://img.shields.io/badge/arch-x86-red.svg?style=for-the-badge&logo=appveyor)](https://en.wikipedia.org/wiki/X86) 

## :page_facing_up: Project Overview :

This is a Call Of Duty : World At War Zombie cheat written in C++.

This cheat is based on my [D3D9 Hook ImGui](https://github.com/adamhlt/D3D9-Hook-ImGui) project.

#### This cheat was created with these tools :

- [Cheat Engine](https://www.cheatengine.org/)
- [x32dbg](https://x64dbg.com/#start)
- [IDA Pro](https://hex-rays.com/ida-pro/)
- [Ghidra](https://ghidra-sre.org/)

You can look at my Cheat Engine table (incomplete but can help) [here](https://github.com/adamhlt/COD-WAW-Cheat/blob/main/Ressources/CoDWaW.CT).

#### Used librairies :

- [MS Detours](https://www.microsoft.com/en-us/research/project/detours/)
- [DirectX SDK](https://www.microsoft.com/en-us/download/details.aspx?id=6812)
- [ImGui](https://github.com/ocornut/imgui)

## :books: Features :

The cheat has several features :

- God Mode 
- Infinite Point
- Infinite Ammo
- Noclip
- Super Knife (increase melee range)
- No Target (zombies don't attack)
- One Shot Kill (every zombie has 1hp)
- Display Cheat Overlay
- Display Gun Laser
- FOV Changer
- Display FPS
- Display Game Version
- Toggle Third Person View
- Name Spoofer
- ESP Line
- Save Current Location
- Teleport zombies to the saved location

## :rocket: Getting Started :

Make sure you already installed DirectX 9 SDK and the environment variable "DXSDK_DIR" is set.

If it's not the case download DirectX 9 SDK [**here**](https://www.microsoft.com/en-us/download/details.aspx?id=6812).

### Visual Studio :

1. Open the solution file (.sln).
2. Build the project in Realese (x86)

Every configuration in x86 (Debug and Realese) are already configured with librairies and includes.

**You cannot compile this project in x64 because the game is a x86 executable.**

### Other IDE using CMAKE :

This **CMakeLists.txt** should compile the project.

```cmake
cmake_minimum_required(VERSION 3.0)
project(WAW)

set(CMAKE_CXX_STANDARD 17)
include_directories(Detours/include $ENV{DXSDK_DIR}Include)
link_directories(Detours/x86 $ENV{DXSDK_DIR}Lib/x86/)
file(GLOB ImGui ImGui/*.cpp ImGui/*.h)

add_library(WAW SHARED framework.h pch.h dllmain.cpp Hook.h Hook.cpp Drawing.h Drawing.cpp Core.h Core.cpp Utils.h Utils.cpp ${ImGui})
target_link_libraries(WAW detours.lib d3d9.lib d3dx9.lib)
```

Tested on CLion with MSVC compiler, you can get Visual Studio Build Tools [**here**](https://visualstudio.microsoft.com/fr/downloads/?q=build+tools).
