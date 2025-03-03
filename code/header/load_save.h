#pragma once

#include "character.h"
#include "menu.h"
#include "dungeon.h"
#include "music.h"

#include <iostream>
#include <string>
#include <conio.h>
#include <limits>
#include <fstream>
#include <filesystem>

extern class Character;

extern Character player;

struct MenuItem {
	int x, y;
	std::string text;
};


void TitleScreen();
void SaveGame();
void NewCharacter();
void LoadGame();
