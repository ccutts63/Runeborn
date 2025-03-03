#pragma once
//#include "character.h"
#include "load_save.h"
#include "enemy.h"
#include "menu.h"
#include "dungeon.h"
#include "music.h"
#include "item.h"
#include "random.h"
#include "slowprint.h"
#include "console_utils.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <limits>
#include <fstream>
#include <filesystem>

class Enemy;



void DrawBattleBackground(Enemy* e);

void Battle(short int enemy_ID, short int enemy_level, short int enemy_attack = -1, short int enemy_Defense = -1, short int enemy_health = -1);
