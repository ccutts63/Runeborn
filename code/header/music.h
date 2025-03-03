#pragma once

//for sound
#include <iostream>
#include <string>
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

extern bool enable_music;

std::wstring StringToWString(const std::string& str);

void PlaySong(const std::string& Song_Title);

void MusicDialog();

