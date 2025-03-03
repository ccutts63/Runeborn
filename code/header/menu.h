#pragma once
//#include "character.h"
#include "load_save.h"
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


//generate Random Items



void PlayerMenu();

void ShopBlacksmithMenu();

void ShopWitchMenu();

void ShopPriestMenu();

void ShopWeaponsMenu();

void ShopArmorMenu();

void ShopShieldsMenu();


void BuyItem(const Item* item);

void DrawShop(std::string name);