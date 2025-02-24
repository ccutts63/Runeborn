#pragma once

#include <string>
#include <iostream>
#include "character.h"
#include "random.h"
#include "slowprint.h"

class Character;

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
	short int enemyDefence;


	//constructor
	Enemy(short int enemy_ID, short int enemy_Level,  short int enemy_Attack = -1, short int enemy_Defence = -1,  short int enemy_maxHealth = -1);

	void Defend(short int attack_damage);
	bool Attack(Character& player);

	void UpdateBattleHealthEnemy();

	void UpdateBattleEnemyFaint();
};

