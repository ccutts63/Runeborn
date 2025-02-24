#pragma once

#include "random.h"
#include "enemy.h"
#include "slowprint.h"
#include "console_utils.h"
#include "item.h"
#include <iostream>
#include <string>
#include <vector>

enum class ItemType { POTION, WEAPON, ARMOR, SHIELD };

class Enemy;

class Character
{
public:
	std::string playerName;
	std::string playerSprite;
	std::vector<Potion> potionInventory;
	std::vector<Weapon> weaponInventory;
	std::vector<Armour> armourInventory;
	std::vector<Shield> shieldInventory;
	short int playerClass; //up to 255
	int playerGold;
	int playerMaxExperience;
	short int playerChanceToBlock;
	short int playerMaxHealth;
	short int playerHealth; //up to 65535 \/
	short int playerAttack;
	short int playerDefense;
	short int playerExperience;
	short int playerLevel; //upto 255 (100 is max)

	Weapon equipedWeapon;
	Armour equipedArmour;
	Shield equipedShield;

	//constructor
	Character(std::string name, short int Class);

	//functions
	std::string Class(); //returns players class string

	bool Attack(Enemy& enemy);
	void Defend(short int attack_damage);
	
	void DrawInventoryMenu();
	void ShowInventoryMenu();

	void UseInventoryItem(int index, ItemType type);

	void ShowInventoryPotion();
	void ShowInventoryWeapon();
	void ShowInventoryArmour();
	void ShowInventoryShield();

	void PrintStats();

	void UpdateBattleHealthPlayer();

	void UpdateBattlePlayerFaint();
};

