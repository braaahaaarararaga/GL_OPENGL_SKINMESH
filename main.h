#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define NOMINMAX
#include <windows.h>
#undef NOMINMAX
#include <assert.h>

#include <GL/gl.h>
#include <GL/glu.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "xaudio2.lib")

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/matrix4x4.h>>
#include <string>
#include <iostream>
#pragma comment(lib, "assimp.lib")


#define SCREEN_WIDTH	(960)			// ウインドウの幅
#define SCREEN_HEIGHT	(540)			// ウインドウの高さ


HWND GetWindow();

void Init(HWND wnd);

void Uninit();

void Update();

void Draw();