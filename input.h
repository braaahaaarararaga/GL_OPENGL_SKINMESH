#pragma once
#include "Mouse.h"
#include "Keyboard.h"


using namespace DirectX;
class CInput
{
public:
	static void Init();
	static void Uninit();
	static void Update();
	static bool GetKeyPress(BYTE KeyCode);
	static bool GetKeyTrigger(BYTE KeyCode);
};
