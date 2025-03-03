#pragma once

//#include "character.h"
#include "battle.h"
#include "menu.h"
#include "load_save.h"
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



class Enemy
{
public:
	std::string enemyName;
	std::string enemySprite;
	short int enemyLevel;
	short int enemyID;
	short int enemyMaxHealth;
	short int enemyHealth;
	short int enemyAttack;
	short int enemyDefense;


	//constructor
	Enemy(short int enemy_ID, short int enemy_Level,  short int enemy_Attack = -1, short int enemy_Defense = -1,  short int enemy_maxHealth = -1);

	bool Attack();

	void UpdateBattleHealthEnemy();

	void UpdateBattleEnemyFaint();
};

