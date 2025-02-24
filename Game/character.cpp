#include "character.h"

const enum playerClass {BARBARIAN, KNIGHT, MAGE}; //set names for switch case


//define global objects
Weapon equipedWeapon(0, 0, 0, 0);
Armour equipedArmour(0, 0, 0, 0);
Shield equipedShield(0, 0, 0, 0);

struct MenuItem {
	int x, y;
	std::string text;
};

Character::Character(std::string name, short int Class) {
	playerName = name;
	playerClass = Class;

	playerChanceToBlock = 0;
	playerExperience = 0; //set global initial values
	playerMaxExperience = 100;
	playerGold = 5000;
	playerLevel = 1;

	switch (playerClass) { // Set initial values based on class
	case BARBARIAN:
		playerHealth = playerMaxHealth = 10;
		playerAttack = 15;
		playerDefense = 15;

		playerSprite =
			"        (#####)        \n"
			"       /       \\       \n"
			"      |  O   O  |      \n"
			"      |    ∆    |      \n"
			"      |         |      \n"
			"     /|   ||   |\\     \n"
			"    / |   ||   | \\    \n"
			"      |   ||   |      \n"
			"      |   ||   |      \n"
			"      |   ||   |      \n"
			"      |   ||   |      \n"
			"     /     |     \\    \n"
			"    /      |      \\   \n"
			"   /       |       \\  \n"
			"  /        |        \\ \n"
			" /_________|_________\\\n";
		break;

	case KNIGHT:
		playerHealth = playerMaxHealth = 15;
		playerAttack = 10;
		playerDefense = 15;

		playerSprite =
			"        (#####)        \n"
			"       /       \\       \n"
			"      |  O   O  |      \n"
			"      |    ∆    |      \n"
			"      |  --|--  |      \n"
			"     /|    |    |\\     \n"
			"    / |    |    | \\    \n"
			"      |    |    |      \n"
			"      |    |    |      \n"
			"      |    |    |      \n"
			"      |    |    |      \n"
			"     /     |     \\    \n"
			"    /      |      \\   \n"
			"   /       |       \\  \n"
			"  /        |        \\ \n"
			" /_________|_________\\\n";
		break;

	case MAGE:
		playerHealth = playerMaxHealth = 15;
		playerAttack = 15;
		playerDefense = 10;

		playerSprite =
			"        (#####)        \n"
			"       /       \\       \n"
			"      |         |      \n"
			"      |    ∆    |      \n"
			"      |  ---|---|      \n"
			"     /|     |   |\\     \n"
			"    / |     |   | \\    \n"
			"      |     |   |      \n"
			"      |     |   |      \n"
			"      |     |   |      \n"
			"      |     |   |      \n"
			"     /      |    \\    \n"
			"    /       |     \\   \n"
			"   /        |      \\  \n"
			"  /         |       \\ \n"
			" /__________|_________\\\n";
		break;

	default:
		playerHealth = playerMaxHealth = 0;
		playerAttack = 0;
		playerDefense = 0;
		playerSprite = "Unknown Class\n";
		break;
	}



}

std::string Character::Class() {
	switch (playerClass) {
	case BARBARIAN: return "Barbarian";
	case KNIGHT: return "Knight";
	case MAGE: return "Mage";
	default: return "???";
	}
}

bool Character::Attack(Enemy& enemy) {
	SetCursorPosition(2, 26);
	SlowPrint("You Attacked...");

	enemy.Defend(playerAttack);

	if (enemy.enemyHealth <= 0) {

		enemy.enemyHealth = 0;

		SetCursorPosition(2, 26);
		SlowPrint("The wild ", enemy.enemyName, " Fainted!");

		short int exp = enemy.enemyLevel * 15;
		short int gld = enemy.enemyLevel * 5 - new_rnd_num(enemy.enemyLevel * 2);

		playerExperience += exp;
		playerGold += gld;

		SetCursorPosition(2, 26);
		SlowPrint("You gained ", exp, " Experience!");

		SetCursorPosition(2, 26);
		SlowPrint("You collected ", gld, " Gold!");

		if (playerExperience >= playerMaxExperience) { //level up
			playerExperience -= playerMaxExperience;

			playerLevel += 1;
			SetCursorPosition(2, 26);
			SlowPrint("You Leveled Up!");
			WaitForUser();
		}

		return true; //battle finished
	}

	SetCursorPosition(2, 26);
	SlowPrint("Enemy ", enemy.enemyName, "'s HP is: ", enemy.enemyHealth, "/", enemy.enemyMaxHealth);

	return false; //battle continue
}
void Character::Defend(short int attack_damage) {
	short int dmg = attack_damage - new_rnd_num(playerDefense);
	if (dmg < 0) { dmg = 0; } //cant have negative damage

	playerHealth -= dmg;
	SetCursorPosition(2, 26);
	SlowPrint("You took ", dmg, " Damage!");

}

void Character::DrawInventoryMenu() {
	system("cls");



	MenuItem menu[] = {
		{ 4, 10, "POTIONS"},
		{ 19, 10, "WEAPONS"},
		{ 34, 10, "ARMOUR" },
		{ 49, 10, "SHIELDS" },
		{ 50, 26, "[Exit]" }
	};
	int menuSize = sizeof(menu) / sizeof(menu[0]);

	//Print Menu Borders
	std::cout << "#############################################################" //0
		<< "\n#Player:                                                    #"     //1
		<< "\n#--------------------------EQUIPPED-------------------------#"		//2
		<< "\n#                                                           #"		//3
		<< "\n#      WEAPON:      |      ARMOUR:      |       SHIELD:     #"     //4
		<< "\n#                   |                   |                   #"		//5
		<< "\n#                   |                   |                   #"		//6
		<< "\n#                   |                   |                   #"		//7
		<< "\n#-----------------------------------------------------------#"		//8
		<< "\n#--------------+----------INVENTORY----------+--------------#"		//9
		<< "\n#   POTIONS    |   WEAPONS    |    ARMOUR    |    SHIELDS   #"		//10
		<< "\n#              |              |              |              #"		//11
		<< "\n#              |              |              |              #"		//12
		<< "\n#              |              |              |              #"		//13
		<< "\n#              |              |              |              #"		//14
		<< "\n#              |              |              |              #"		//15
		<< "\n#              |              |              |              #"		//16
		<< "\n#              |              |              |              #"		//17
		<< "\n#              |              |              |              #"		//18
		<< "\n#              |              |              |              #"		//19
		<< "\n#              |              |              |              #"		//20
		<< "\n#-----------------------------------------------------------#"		//21
		<< "\n#---------------------------STATS---------------------------#"		//22
		<< "\n#  ATTACK:     | BLOCK:       | GOLD:        | HP:          #"		//23
		<< "\n# DEFENSE:     | LEVEL:       |  EXP:        |              #"		//24
		<< "\n#-----------------------------------------------------------#"		//25
		<< "\n#                                                  [Exit]   #"		//26
		<< "\n#############################################################";	//27

	//print player stats
	PrintStats();

	//print equipped items
	SetCursorPosition(2, 5);
	std::cout << equipedWeapon.name;

	SetCursorPosition(2, 6);
	std::cout << "[+" << equipedWeapon.attack << "]";

	SetCursorPosition(22, 5);
	std::cout << equipedArmour.name;

	SetCursorPosition(22, 6);
	std::cout << "[+" << equipedArmour.defense << "]";

	SetCursorPosition(42, 5);
	std::cout << equipedShield.name;

	SetCursorPosition(42, 6);
	std::cout << "[+" << equipedShield.blockChance << "]";



	//print Inventory
	//potions
	if (potionInventory.size() == 0) {
		SetCursorPosition(1, 11);
		std::cout << "Empty";
	}
	else {

		for (int i = 0; i < potionInventory.size(); i++) {
			SetCursorPosition(1, 11 + i);

			if (i == 9) {
				std::cout << "+++++MORE+++++";
				break;
			} //only print 9 items

			if (potionInventory[i].name.length() > 12) {
				std::cout << i + 1 << "(" << potionInventory[i].name.substr(0, 10) << "..";
			}
			else {
				std::cout << i + 1 << "(" << potionInventory[i].name;
			}

		}


	}
	//weapons
	if (weaponInventory.size() == 0) {
		SetCursorPosition(16, 11);
		std::cout << "Empty";
	}
	else {


		for (int i = 0; i < weaponInventory.size(); i++) {
			if (weaponInventory[i].name.length() > 12) {
				SetCursorPosition(16, 11 + i);
				std::cout << i + 1 << "(" << weaponInventory[i].name.substr(0, 10) << "..";
			}
			else {
				SetCursorPosition(16, 11 + i);
				std::cout << i + 1 << "(" << weaponInventory[i].name;
			}

		}


	}
	//armour
	if (armourInventory.size() == 0) {
		SetCursorPosition(31, 11);
		std::cout << "Empty";
	}
	else {


		for (int i = 0; i < armourInventory.size(); i++) {
			if (armourInventory[i].name.length() > 12) {
				SetCursorPosition(31, 11 + i);
				std::cout << i + 1 << "(" << armourInventory[i].name.substr(0, 10) << "..";
			}
			else {
				SetCursorPosition(31, 11 + i);
				std::cout << i + 1 << "(" << armourInventory[i].name;
			}

		}


	}
	//shields
	if (shieldInventory.size() == 0) {
		SetCursorPosition(46, 11);
		std::cout << "Empty";
	}
	else {


		for (int i = 0; i < shieldInventory.size(); i++) {
			if (shieldInventory[i].name.length() > 12) {
				SetCursorPosition(46, 11 + i);
				std::cout << i + 1 << "(" << shieldInventory[i].name.substr(0, 10) << "..";
			}
			else {
				SetCursorPosition(46, 11 + i);
				std::cout << i + 1 << "(" << shieldInventory[i].name;
			}

		}


	}

}

void Character::ShowInventoryMenu() {

	MenuItem menu[] = {
	{ 4, 10, "POTIONS"},
	{ 19, 10, "WEAPONS"},
	{ 34, 10, "ARMOUR" },
	{ 49, 10, "SHIELDS" },
	{ 50, 26, "[Exit]" }
	};


	int menuSize = sizeof(menu) / sizeof(menu[0]);

	DrawInventoryMenu();

	int selectedItem = 0; // Tracks which menu option is selected

		// Menu loop
		while (true) {

			for (int i = 0; i < menuSize; i++) {
				SetCursorPosition(menu[i].x, menu[i].y);
				std::cout << (i == selectedItem ? ">" : " ") << menu[i].text;
			}

			int input = _getch();

			if (input == 224) { // Arrow keys
				input = _getch();

				switch (input) {
				case 72: // Up arrow
					selectedItem = (selectedItem - 1 + menuSize) % menuSize;
					break;
				case 75: // Left Arrow
					selectedItem = (selectedItem - 1 + menuSize) % menuSize;
					break;
				case 80: // Down arrow
					selectedItem = (selectedItem + 1) % menuSize;
					break;
				case 77: // Right arrow
					selectedItem = (selectedItem + 1) % menuSize;
					break;
				}

			}
			else if (input == '\r') { // Enter key

				SetCursorPosition(0, menu[menuSize - 1].y + 2); // Move cursor below menu



				switch (selectedItem) {
				case 0: ShowInventoryPotion(); break;
				case 1: ShowInventoryWeapon(); break;
				case 2: ShowInventoryArmour(); break;
				case 3: ShowInventoryShield(); break;
				case 4:
					return;

					break;
				}
				DrawInventoryMenu();
			}

		}

}

void Character::ShowInventoryPotion() {
	system("cls");

	int selectedItem = 0; // Tracks which menu option is selected
	int menuSize = potionInventory.size() + 1;

	MenuItem* menu = new MenuItem[menuSize];

	std::cout << "#############################################################" //0
		<< "\n#Player:                                                    #"     //1
		<< "\n#--------------------------POTIONS--------------------------#"		//2
		<< "\n#                             |                             #"		//3
		<< "\n#                             |                             #"		//4
		<< "\n#                             |                             #"		//5
		<< "\n#                             |                             #"		//6
		<< "\n#                             |                             #"		//7
		<< "\n#                             |                             #"		//8
		<< "\n#                             |                             #"		//9
		<< "\n#                             |                             #"		//10
		<< "\n#                             |                             #"		//11
		<< "\n#                             |                             #"		//12
		<< "\n#                             |                             #"		//13
		<< "\n#                             |                             #"		//14
		<< "\n#                             |                             #"		//15
		<< "\n#                             |                             #"		//16
		<< "\n#                             |                             #"		//17
		<< "\n#                             |                             #"		//18
		<< "\n#                             |                             #"		//19
		<< "\n#                             |                             #"		//20
		<< "\n#-----------------------------------------------------------#"		//21
		<< "\n#---------------------------STATS---------------------------#"		//22
		<< "\n#  ATTACK:     | BLOCK:       | GOLD:        | HP:          #"		//23
		<< "\n# DEFENSE:     | LEVEL:       |  EXP:        |              #"		//24
		<< "\n#-----------------------------------------------------------#"		//25
		<< "\n#                                                  [Exit]   #"		//26
		<< "\n#############################################################";	//27

	if (potionInventory.size() > 0) {


		for (int i = 0; i < potionInventory.size(); i++) {

			if (i > 17) { //wrap around

				SetCursorPosition(33, i - 15);
				std::cout << i + 1 << ") " << potionInventory[i].name;
				menu[i] = { 32, i - 15, potionInventory[i].name };

			}
			else {

				SetCursorPosition(3, i + 3);
				std::cout << i + 1 << ") " << potionInventory[i].name;
				menu[i] = { 3, i + 3, potionInventory[i].name };
			}

			std::cout << " [+" << potionInventory[i].health << "]";

		}

	}

	menu[menuSize - 1] = { 50, 26, "[Exit]" };

	//Print Character Stats
	PrintStats();

	// Menu loop
	while (true) {

		for (int i = 0; i < menuSize; i++) {
			SetCursorPosition(menu[i].x - 1, menu[i].y);
			std::cout << (i == selectedItem ? ">" : " ");
		}

		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			switch (input) {
			case 72: // Up arrow
				selectedItem = (selectedItem - 1 + menuSize) % menuSize;
				break;
			case 75: // Left Arrow
				selectedItem = (selectedItem - 18 + menuSize) % menuSize;
				break;
			case 80: // Down arrow
				selectedItem = (selectedItem + 1) % menuSize;
				break;
			case 77: // Right arrow
				selectedItem = (selectedItem + 18) % menuSize;
				break;
			}

		}
		else if (input == '\r') { // Enter key

			if (selectedItem != menuSize - 1) { //if not exit

				UseInventoryItem(selectedItem, ItemType::POTION);

				break;
			}
			else {

				return;
			}

		}

	}

}
void Character::ShowInventoryWeapon() {
	system("cls");

	int selectedItem = 0; // Tracks which menu option is selected
	int menuSize = weaponInventory.size() + 1;

	MenuItem* menu = new MenuItem[menuSize];

	std::cout << "#############################################################" //0
		<< "\n#Player:                                                    #"     //1
		<< "\n#--------------------------WEAPONS-------------------------#"		//2
		<< "\n#                             |                             #"		//3
		<< "\n#                             |                             #"		//4
		<< "\n#                             |                             #"		//5
		<< "\n#                             |                             #"		//6
		<< "\n#                             |                             #"		//7
		<< "\n#                             |                             #"		//8
		<< "\n#                             |                             #"		//9
		<< "\n#                             |                             #"		//10
		<< "\n#                             |                             #"		//11
		<< "\n#                             |                             #"		//12
		<< "\n#                             |                             #"		//13
		<< "\n#                             |                             #"		//14
		<< "\n#                             |                             #"		//15
		<< "\n#                             |                             #"		//16
		<< "\n#                             |                             #"		//17
		<< "\n#                             |                             #"		//18
		<< "\n#                             |                             #"		//19
		<< "\n#                             |                             #"		//20
		<< "\n#-----------------------------------------------------------#"		//21
		<< "\n#---------------------------STATS---------------------------#"		//22
		<< "\n#  ATTACK:     | BLOCK:       | GOLD:        | HP:          #"		//23
		<< "\n# DEFENSE:     | LEVEL:       |  EXP:        |              #"		//24
		<< "\n#-----------------------------------------------------------#"		//25
		<< "\n#                                                  [Exit]   #"		//26
		<< "\n#############################################################";	//27

	if (weaponInventory.size() > 0) {


		for (int i = 0; i < weaponInventory.size(); i++) {

			if (i > 18) {

				SetCursorPosition(33, i + 3);
				std::cout << i + 1 << ") " << weaponInventory[i].name;
				menu[i] = { 32, i + 3, weaponInventory[i].name };

			}
			else {

				SetCursorPosition(3, i + 3);
				std::cout << i + 1 << ") " << weaponInventory[i].name;
				menu[i] = { 3, i + 3, weaponInventory[i].name };
			}

			std::cout << " [+" << weaponInventory[i].attack << "]";

		}

	}

	menu[menuSize - 1] = { 50, 26, "[Exit]" };

	PrintStats();

	// Menu loop
	while (true) {

		for (int i = 0; i < menuSize; i++) {
			SetCursorPosition(menu[i].x - 1, menu[i].y);
			std::cout << (i == selectedItem ? ">" : " ");
		}

		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			switch (input) {
			case 72: // Up arrow
				selectedItem = (selectedItem - 1 + menuSize) % menuSize;
				break;
			case 75: // Left Arrow
				selectedItem = (selectedItem - 1 + menuSize) % menuSize;
				break;
			case 80: // Down arrow
				selectedItem = (selectedItem + 1) % menuSize;
				break;
			case 77: // Right arrow
				selectedItem = (selectedItem + 1) % menuSize;
				break;
			}

		}
		else if (input == '\r') { // Enter key

			if (selectedItem != menuSize - 1) { //if not exit

				UseInventoryItem(selectedItem, ItemType::WEAPON);

				break;
			}
			else {

				return;
			}

		}

	}
}
void Character::ShowInventoryArmour() {
	system("cls");

	int selectedItem = 0; // Tracks which menu option is selected
	int menuSize = armourInventory.size() + 1;

	MenuItem* menu = new MenuItem[menuSize];

	std::cout << "#############################################################" //0
		<< "\n#Player:                                                    #"     //1
		<< "\n#---------------------------ARMOR---------------------------#"		//2
		<< "\n#                             |                             #"		//3
		<< "\n#                             |                             #"		//4
		<< "\n#                             |                             #"		//5
		<< "\n#                             |                             #"		//6
		<< "\n#                             |                             #"		//7
		<< "\n#                             |                             #"		//8
		<< "\n#                             |                             #"		//9
		<< "\n#                             |                             #"		//10
		<< "\n#                             |                             #"		//11
		<< "\n#                             |                             #"		//12
		<< "\n#                             |                             #"		//13
		<< "\n#                             |                             #"		//14
		<< "\n#                             |                             #"		//15
		<< "\n#                             |                             #"		//16
		<< "\n#                             |                             #"		//17
		<< "\n#                             |                             #"		//18
		<< "\n#                             |                             #"		//19
		<< "\n#                             |                             #"		//20
		<< "\n#-----------------------------------------------------------#"		//21
		<< "\n#---------------------------STATS---------------------------#"		//22
		<< "\n#  ATTACK:     | BLOCK:       | GOLD:        | HP:          #"		//23
		<< "\n# DEFENSE:     | LEVEL:       |  EXP:        |              #"		//24
		<< "\n#-----------------------------------------------------------#"		//25
		<< "\n#                                                  [Exit]   #"		//26
		<< "\n#############################################################";	//27

	if (armourInventory.size() > 0) {


		for (int i = 0; i < armourInventory.size(); i++) {

			if (i > 18) {

				SetCursorPosition(33, i + 3);
				std::cout << i + 1 << ") " << armourInventory[i].name;
				menu[i] = { 32, i + 3, armourInventory[i].name };

			}
			else {

				SetCursorPosition(3, i + 3);
				std::cout << i + 1 << ") " << armourInventory[i].name;
				menu[i] = { 3, i + 3, armourInventory[i].name };
			}

			std::cout << " [+" << armourInventory[i].defense << "]";

		}

	}

	menu[menuSize - 1] = { 50, 26, "[Exit]" };

	PrintStats();

	// Menu loop
	while (true) {

		for (int i = 0; i < menuSize; i++) {
			SetCursorPosition(menu[i].x - 1, menu[i].y);
			std::cout << (i == selectedItem ? ">" : " ");
		}

		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			switch (input) {
			case 72: // Up arrow
				selectedItem = (selectedItem - 1 + menuSize) % menuSize;
				break;
			case 75: // Left Arrow
				selectedItem = (selectedItem - 1 + menuSize) % menuSize;
				break;
			case 80: // Down arrow
				selectedItem = (selectedItem + 1) % menuSize;
				break;
			case 77: // Right arrow
				selectedItem = (selectedItem + 1) % menuSize;
				break;
			}

		}
		else if (input == '\r') { // Enter key

			if (selectedItem != menuSize - 1) { //if not exit

				UseInventoryItem(selectedItem, ItemType::ARMOR);

				break;
			}
			else {

				return;
			}

		}

	}
}
void Character::ShowInventoryShield() {
	system("cls");

	int selectedItem = 0; // Tracks which menu option is selected
	int menuSize = shieldInventory.size() + 1;

	MenuItem* menu = new MenuItem[menuSize];

	std::cout << "#############################################################" //0
		<< "\n#Player:                                                    #"     //1
		<< "\n#--------------------------SHIELDS--------------------------#"		//2
		<< "\n#                             |                             #"		//3
		<< "\n#                             |                             #"		//4
		<< "\n#                             |                             #"		//5
		<< "\n#                             |                             #"		//6
		<< "\n#                             |                             #"		//7
		<< "\n#                             |                             #"		//8
		<< "\n#                             |                             #"		//9
		<< "\n#                             |                             #"		//10
		<< "\n#                             |                             #"		//11
		<< "\n#                             |                             #"		//12
		<< "\n#                             |                             #"		//13
		<< "\n#                             |                             #"		//14
		<< "\n#                             |                             #"		//15
		<< "\n#                             |                             #"		//16
		<< "\n#                             |                             #"		//17
		<< "\n#                             |                             #"		//18
		<< "\n#                             |                             #"		//19
		<< "\n#                             |                             #"		//20
		<< "\n#-----------------------------------------------------------#"		//21
		<< "\n#---------------------------STATS---------------------------#"		//22
		<< "\n#  ATTACK:     | BLOCK:       | GOLD:        | HP:          #"		//23
		<< "\n# DEFENSE:     | LEVEL:       |  EXP:        |              #"		//24
		<< "\n#-----------------------------------------------------------#"		//25
		<< "\n#                                                  [Exit]   #"		//26
		<< "\n#############################################################";	//27

	if (shieldInventory.size() > 0) {


		for (int i = 0; i < shieldInventory.size(); i++) {

			if (i > 18) {

				SetCursorPosition(33, i + 3);
				std::cout << i + 1 << ") " << shieldInventory[i].name;
				menu[i] = { 32, i + 3, shieldInventory[i].name };

			}
			else {

				SetCursorPosition(3, i + 3);
				std::cout << i + 1 << ") " << shieldInventory[i].name;
				menu[i] = { 3, i + 3, shieldInventory[i].name };
			}

			std::cout << " [+" << shieldInventory[i].blockChance << "]";

		}

	}

	menu[menuSize - 1] = { 50, 26, "[Exit]" };

	PrintStats();

	// Menu loop
	while (true) {

		for (int i = 0; i < menuSize; i++) {
			SetCursorPosition(menu[i].x - 1, menu[i].y);
			std::cout << (i == selectedItem ? ">" : " ");
		}

		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			switch (input) {
			case 72: // Up arrow
				selectedItem = (selectedItem - 1 + menuSize) % menuSize;
				break;
			case 75: // Left Arrow
				selectedItem = (selectedItem - 1 + menuSize) % menuSize;
				break;
			case 80: // Down arrow
				selectedItem = (selectedItem + 1) % menuSize;
				break;
			case 77: // Right arrow
				selectedItem = (selectedItem + 1) % menuSize;
				break;
			}

		}
		else if (input == '\r') { // Enter key

			if (selectedItem != menuSize - 1) { //if not exit

				UseInventoryItem(selectedItem, ItemType::SHIELD);

				break;
			}
			else {

				return;
			}

		}

	}
}

void Character::UseInventoryItem(int index, ItemType type) {
	if (index < 0) return;

	int def = 0;
	int atk = 0;
	int block = 0;

	switch (type) {
	case ItemType::POTION:

		if (index >= potionInventory.size()) {
			return;
		}

		SetCursorPosition(3, 26);

		SlowPrint(0, "Replenished ", potionInventory[index].health, " HP");
		WaitForUser();

		playerHealth += potionInventory[index].health;

		if (playerHealth > playerMaxHealth) {
			playerHealth = playerMaxHealth;
		}

		potionInventory.erase(potionInventory.begin() + index);
		ShowInventoryPotion();
		break;

	case ItemType::WEAPON:

		atk = playerAttack - equipedWeapon.attack + weaponInventory[index].attack;

		SetCursorPosition(3, 26);

		SlowPrint(0, atk > playerAttack ? "Equipping... +[" : "Equipping... -[", weaponInventory[index].attack, "] to your ATK STAT");
		WaitForUser();

		playerAttack = atk;

		if (!equipedWeapon.name.empty()) { // If a weapon is already equipped
			weaponInventory.push_back(equipedWeapon); // Add it to inventory
		}

		equipedWeapon = weaponInventory[index]; // Equip new weapon
		weaponInventory.erase(weaponInventory.begin() + index);

		ShowInventoryWeapon();
		break;

	case ItemType::ARMOR:

		def = playerDefense - equipedArmour.defense + armourInventory[index].defense;

		SetCursorPosition(3, 26);

		SlowPrint(0, def > playerDefense ? "Equipping... +[" : "Equipping... -[", armourInventory[index].defense, "] to your DEF STAT");
		WaitForUser();

		playerDefense = def;

		if (!equipedArmour.name.empty()) {
			armourInventory.push_back(equipedArmour);
		}

		equipedArmour = armourInventory[index]; // Equip new armor
		armourInventory.erase(armourInventory.begin() + index);

		ShowInventoryArmour();
		break;

	case ItemType::SHIELD:

		block = playerChanceToBlock - equipedShield.blockChance + shieldInventory[index].blockChance;

		SetCursorPosition(3, 26);

		SlowPrint(0, block > playerChanceToBlock ? "Equipping... +[" : "Equipping... -[", shieldInventory[index].blockChance, "] to your BLOCK STAT");
		WaitForUser();

		playerChanceToBlock = block;

		if (!equipedShield.name.empty()) {
			shieldInventory.push_back(equipedShield);
		}

		equipedShield = shieldInventory[index]; // Equip new shield
		shieldInventory.erase(shieldInventory.begin() + index);

		ShowInventoryShield();
		break;
	}

}

void Character::PrintStats() {
	//Print Character Stats
	SetCursorPosition(11, 23);
	std::cout << playerAttack;

	SetCursorPosition(11, 24);
	std::cout << playerDefense;

	SetCursorPosition(24, 23);
	std::cout << playerChanceToBlock;

	SetCursorPosition(24, 24);
	std::cout << playerLevel;

	SetCursorPosition(38, 23);
	std::cout << playerGold;

	SetCursorPosition(38, 24);
	std::cout << playerExperience << '/' << playerMaxExperience;

	SetCursorPosition(51, 23);
	std::cout << playerHealth << '/' << playerMaxHealth;

	//print class and name
	SetCursorPosition(9, 1);
	std::cout << playerName << " the " << Class();

}