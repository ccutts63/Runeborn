#pragma once

#include "battle.h"
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
#include <vector>

enum class characterType { WARRIOR, ROUGE, MAGE };



class Dungeon;

class Enemy;

class Character
{
private:
	void DrawInventory();
	void DrawInventoryMenu();
	void UseInventoryItem(int index, ItemType item_type);

public:
	std::string name;
	std::string sprite;
	std::vector<Misc> miscInventory;
	std::vector<Weapon> weaponInventory;
	std::vector<Armor> armorInventory;
	std::vector<Shield> shieldInventory;

	struct Position {
		int x, y;
	};
	Position position;

	char chr;
	characterType type; //up to 255
	int gold;
	int maxExperience;
	short int block;
	short int maxHealth;
	short int health; //up to 65535 \/
	short int attack;
	short int defense;
	short int experience;
	short int level; //upto 255 (100 is max)

	//player stat multipliers
	float atkBoost = 1;
	float defBoost = 1;
	float ctbBoost = 1;
	float hpBoost = 1;
	float gldBoost = 1;
	float expBoost = 1;

	bool inTown = true;

	Weapon equippedWeapon;
	Armor equippedArmor;
	Shield equippedShield;




	//constructor
	Character(std::string player_name, characterType player_type);

	bool Attack(Enemy& enemy);
	void Defend(short int attack_damage);
	

	void ShowInventoryMenu();

	

	void ShowInventoryMisc();
	void ShowInventoryWeapon();
	void ShowInventoryArmor();
	void ShowInventoryShield();

	void LevelUp();

	void PrintStats();

	void UpdateBattleHealthPlayer();

	void UpdateBattlePlayerFaint();

	std::string CharacterType();
};

