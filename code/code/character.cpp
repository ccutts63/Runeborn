#include "character.h"


Character::Character(std::string player_name, characterType player_type) {
	name = player_name;
	type = player_type;

	experience = 0; //set global initial values
	maxExperience = 144;
	gold = 100;
	level = 3;

	position.x = 28;
	position.y = 9;

	equippedWeapon = Weapon(0, 0, 0, 0);
	equippedArmor = Armor(0, 0, 0, 0);
	equippedShield = Shield(0, 0, 0, 0);

	
	switch (type) { // Set initial values based on class
	case characterType::WARRIOR:
		health = maxHealth = 52;
		attack = 11;
		defense = 8;
		block = 25;
		chr = 'B';
		//playerspeed

		sprite =
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

	case characterType::ROUGE:
		health = maxHealth = 39;
		attack = 10;
		defense = 5;
		block = 6;
		chr = 'K';

		sprite =
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

	case characterType::MAGE:
		health = maxHealth = 31;
		attack = 6;
		defense = 3;
		block = 0;
		chr = 'M';

		sprite =
			"        (#####)        \n"
			"       / ?   ? \\       \n"
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
		health = maxHealth = 0;
		attack = 0;
		defense = 0;
		sprite = "Unknown Class\n";
		break;
	}



}


bool Character::Attack(Enemy& enemy) {
	SetCursorPosition(2, 26);
	SlowPrint("You attacked...");

	//// Check if the enemy blocks the attack (optional: enemyBlockChance could be added for a more advanced system)
	//if (new_rnd_num(100) < enemy.enemyBlockChance) {
	//	SetCursorPosition(2, 26);
	//	SlowPrint("The enemy blocked your attack!");
	//	return false; // No damage dealt, continue battle
	//}

	//damage calculation with slight randomness (up to ±25%)
	short int baseDamage = attack - new_rnd_num(enemy.enemyDefense);
	short int variance = new_rnd_num(baseDamage / 4); // Adds variance
	short int dmg = (baseDamage + variance) * atkBoost;

	//ensure damage is at least 1
	if (dmg < 0) { dmg = 0; }

	enemy.enemyHealth -= dmg;
	if (enemy.enemyHealth < 0) { enemy.enemyHealth = 0; } //avoid negative health

	enemy.UpdateBattleHealthEnemy();

	SetCursorPosition(2, 26);
	SlowPrint("You dealt ", dmg, " damage!");

	//if the enemy is still alive, show their remaining health
	if (enemy.enemyHealth > 0) {
		SetCursorPosition(2, 26);
		SlowPrint("Enemy ", enemy.enemyName, "'s HP is: ", enemy.enemyHealth, "/", enemy.enemyMaxHealth);
		return false; //battle continues
	}

	//enemy fainted, handle defeat
	enemy.UpdateBattleEnemyFaint();

	SetCursorPosition(2, 26);
	SlowPrint("The wild ", enemy.enemyName, " died!");

	//play win music
	PlaySong("assets\\win.wav");

	//experience and gold calculation
	short int exp = enemy.enemyLevel * 15;
	exp = static_cast<short int>(exp * (static_cast<float>(level) / (level + enemy.enemyLevel)));
	exp *= expBoost;

	short int gld = enemy.enemyLevel * 4;
	gld *= gldBoost;

	experience += exp;
	gold += gld;

	SetCursorPosition(2, 26);
	SlowPrint("You gained ", exp, " experience!");

	SetCursorPosition(2, 26);
	SlowPrint("You collected ", gld, " gold!");

	//check if the player leveled up
	if (experience >= maxExperience) {
		LevelUp();
	}

	return true; //battle finished


}

void Character::LevelUp() {
	experience -= maxExperience;
	level++;

	maxExperience = static_cast<short int>(maxExperience * pow(1.2f, level - 1));

	switch (type) {
	case characterType::WARRIOR:
		maxHealth += new_rnd_num(15, 20);  // Significant health increase
		health = maxHealth;  // Reset health to max
		attack += new_rnd_num(3, 5);  // Moderate attack increase
		defense += new_rnd_num(2, 4);  // High defense increase
		block += 3;  // Moderate block chance increase
	case characterType::ROUGE:
		maxHealth += new_rnd_num(6, 9);  // Moderate health increase
		health = maxHealth;  // Reset health to max
		attack += new_rnd_num(4, 5);  // Moderate attack increase
		defense += new_rnd_num(1, 3);  // Slight defense increase
		block += 1;  // Slight block chance increase (low but evasion focus)
	case characterType::MAGE:
		maxHealth += new_rnd_num(5, 8);  // Small health increase
		health = maxHealth;  // Reset health to max
		attack += new_rnd_num(4, 6);  // Significant attack increase for spellcasting
		defense += new_rnd_num(1, 2);  // Low defense increase (if magical resistance is applied)
		block = 0;  // No block chance, focus on evasion or magical shields
	}

	SetCursorPosition(2, 26);
	SlowPrint("You grew to level ", level, "!");
}

void Character::UpdateBattleHealthPlayer() {

	if (health == maxHealth) {
		PrintSpriteAt(3, 14, "\033[41m++\n++\n++\n++\n++\n++\033[0m");
		return;
	}
	else if (health == 0){
		PrintSpriteAt(3, 14, "  \n  \n  \n  \n  \n  ");
		return;
	}


	//player health bar
	float x = maxHealth / 6.0f;
	int y = health / x;

	switch (y) {
	case 0: 
		PrintSpriteAt(3, 14, "  \n  \n  \n  \n  \n\033[41m++\033[0m");
		break;
	case 1:
		PrintSpriteAt(3, 14, "  \n  \n  \n  \n\033[41m++\n++\033[0m");
		break;
	case 2:
		PrintSpriteAt(3, 14, "  \n  \n  \n\033[41m++\n++\n++\033[0m");
		break;
	case 3:
		PrintSpriteAt(3, 14, "  \n  \n\033[41m++\n++\n++\n++\033[0m");
		break;
	case 4:
		PrintSpriteAt(3, 14, "  \n\033[41m++\n++\n++\n++\n++\033[0m");
		break;
	case 5:
		PrintSpriteAt(3, 14, "  \n\033[41m++\n++\n++\n++\n++\033[0m");
		break;
	}
}

void Character::UpdateBattlePlayerFaint() {
	std::vector<std::string> frames = {
		// Initial standing frame
		"^*^*^*^*^*^*^*^*^*^*^*^\n"
		"*^*^*^*^*^*^*^*^*^*^*^*\n"
		"^*^*^*^*^*^*^*^*^*^*^*^\n"
		"*^*^*^*^*^*^*^*^*^*^*^*\n"
		"^*^*^*^*^*^*^*^*^*^*^*^\n"
		"*^*^*^*^*^*^*^*^*^*^*^*\n"
		"^*^*^*^*^*^*^*^*^*^*^*^\n"
		"*^*^*^*^*^*^*^*^*^*^*^*",

		// Midway collapsing
		"    ^*^*^*^*^*^*^*^*^*^\n"
		"  *^*^*^*^*^*^*^*^*^*^*\n"
		"   ^*^*^*^*^*^*^*^*^*^\n"
		"    *^*^*^*^*^*^*^*^*^*\n"
		"     ^*^*^*^*^*^*^*^*^\n"
		"       *^*^*^*^*^*^*^*\n"
		"         ^*^*^*^*^*^*^\n"
		"           *^*^*^*^*^*",

		// Almost fallen
		"                 ^*^*^\n"
		"               *^*^*^*\n"
		"             ^*^*^*^*^\n"
		"           *^*^*^*^*^*\n"
		"         ^*^*^*^*^*^*^\n"
		"       *^*^*^*^*^*^*^*\n"
		"     ^*^*^*^*^*^*^*^*^\n"
		"   *^*^*^*^*^*^*^*^*^*",

		// Fully collapsed
		" ^*^*^*^*^*^*^*^*^*^*^\n"
		"*^*^*^*^*^*^*^*^*^*^*^*\n"
		" ^*^*^*^*^*^*^*^*^*^*^\n"
		"*^*^*^*^*^*^*^*^*^*^*^*\n"
		"                         \n"
		"                         \n"
		"                         \n"
		"                         ",

		// Disappeared
		"                         \n"
		"                         \n"
		"                         \n"
		"                         \n"
		"                         \n"
		"                         \n"
		"                         \n"
		"                         "
	};


	for (const auto frame : frames) {
		PrintSpriteAt(8, 10, frame);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}

}

void Character::DrawInventoryMenu() {
	system("cls");



	MenuItem menu[] = {
		{ 6, 10, "MISC"},
		{ 19, 10, "WEAPONS"},
		{ 34, 10, "ARMOR" },
		{ 49, 10, "SHIELDS" },
		{ 50, 26, "[Exit]" }
	};
	int menuSize = sizeof(menu) / sizeof(menu[0]);

	//Print Menu Borders
	std::cout << "#############################################################" //0
		<< "\n#Player:                                                    #"     //1
		<< "\n#--------------------------EQUIPPED-------------------------#"		//2
		<< "\n#                                                           #"		//3
		<< "\n#      WEAPON:      |       ARMOR:      |       SHIELD:     #"     //4
		<< "\n#                   |                   |                   #"		//5
		<< "\n#                   |                   |                   #"		//6
		<< "\n#                   |                   |                   #"		//7
		<< "\n#-----------------------------------------------------------#"		//8
		<< "\n#--------------+----------INVENTORY----------+--------------#"		//9
		<< "\n#     MISC     |   WEAPONS    |    ARMOR     |    SHIELDS   #"		//10
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
	std::cout << equippedWeapon.name;

	SetCursorPosition(2, 6);
	std::cout << "[+" << equippedWeapon.attack << "]";

	SetCursorPosition(22, 5);
	std::cout << equippedArmor.name;

	SetCursorPosition(22, 6);
	std::cout << "[+" << equippedArmor.defense << "]";

	SetCursorPosition(42, 5);
	std::cout << equippedShield.name;

	SetCursorPosition(42, 6);
	std::cout << "[+" << equippedShield.blockChance << "]";



	//print Inventory
	//miscs
	if (miscInventory.size() == 0) {
		SetCursorPosition(1, 11);
		std::cout << "Empty";
	}
	else {

		for (int i = 0; i < miscInventory.size(); i++) {
			SetCursorPosition(1, 11 + i);

			if (i == 9) {
				std::cout << "+++++MORE+++++";
				break;
			} //only print 9 items

			if (miscInventory[i].name.length() > 12) {
				std::cout << i + 1 << "(" << miscInventory[i].name.substr(0, 10) << "..";
			}
			else {
				std::cout << i + 1 << "(" << miscInventory[i].name;
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
	//Armor
	if (armorInventory.size() == 0) {
		SetCursorPosition(31, 11);
		std::cout << "Empty";
	}
	else {


		for (int i = 0; i < armorInventory.size(); i++) {
			if (armorInventory[i].name.length() > 12) {
				SetCursorPosition(31, 11 + i);
				std::cout << i + 1 << "(" << armorInventory[i].name.substr(0, 10) << "..";
			}
			else {
				SetCursorPosition(31, 11 + i);
				std::cout << i + 1 << "(" << armorInventory[i].name;
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

void Character::DrawInventory() {

	std::cout << "#############################################################" //0
		<< "\n#Player:                                                    #"     //1
		<< "\n#---------------------------NAME----------------------------#";		//2

	for (int i = 0; i < 18; i++) {
		std::cout << "\n#                             |                             #";
	}


	std::cout << "\n#-----------------------------------------------------------#"		//21
		<< "\n#---------------------------STATS---------------------------#"		//22
		<< "\n#  ATTACK:     | BLOCK:       | GOLD:        | HP:          #"		//23
		<< "\n# DEFENSE:     | LEVEL:       |  EXP:        |              #"		//24
		<< "\n#-----------------------------------------------------------#"		//25
		<< "\n#                                                  [Exit]   #"		//26
		<< "\n#############################################################";	//27
}

void Character::ShowInventoryMenu() {

	MenuItem menu[] = {
	{ 6, 10, "MISC"},
	{ 19, 10, "WEAPONS"},
	{ 34, 10, "ARMOR" },
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

				switch (selectedItem) {
				case 0: ShowInventoryMisc(); break;
				case 1: ShowInventoryWeapon(); break;
				case 2: ShowInventoryArmor(); break;
				case 3: ShowInventoryShield(); break;
				case 4:
					return;

					break;
				}
				DrawInventoryMenu();
			}

		}

}

void Character::ShowInventoryMisc() {
	system("cls");

	int selectedItem = 0; // Tracks which menu option is selected
	int menuSize = miscInventory.size() + 1;

	MenuItem* menu = new MenuItem[menuSize];

	DrawInventory();

	//print inventory name
	SetCursorPosition(28, 2);
	std::cout << "MISC";

	//print inventory contents
	for (int i = 0; i < miscInventory.size(); i++) {

		if (i > 17) { //wrap around

			SetCursorPosition(33, i - 15);
			std::cout << i + 1 << ") " << miscInventory[i].name;
			menu[i] = { 32, i - 15, miscInventory[i].name };

		}
		else {

			SetCursorPosition(3, i + 3);
			std::cout << i + 1 << ") " << miscInventory[i].name;
			menu[i] = { 3, i + 3, miscInventory[i].name };
		}


	}

	//always have exit as last menu item
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

			if (selectedItem == menuSize - 1) { //if exit is selected
				return;
			}

			UseInventoryItem(selectedItem, ItemType::MISC);

			break;
		}

	}
}
void Character::ShowInventoryWeapon() {
	system("cls");

	int selectedItem = 0; // Tracks which menu option is selected
	int menuSize = weaponInventory.size() + 1;

	MenuItem* menu = new MenuItem[menuSize];

	DrawInventory();

	//print inventory name
	SetCursorPosition(27, 2);
	std::cout << "WEAPONS";

	//print inventory contents
	for (int i = 0; i < weaponInventory.size(); i++) {

		if (i > 17) { //wrap around

			SetCursorPosition(33, i - 15);
			std::cout << i + 1 << ") " << weaponInventory[i].name;
			menu[i] = { 32, i - 15, weaponInventory[i].name };

		}
		else {

			SetCursorPosition(3, i + 3);
			std::cout << i + 1 << ") " << weaponInventory[i].name;
			menu[i] = { 3, i + 3, weaponInventory[i].name };
		}


	}

	//always have exit as last menu item
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

			if (selectedItem == menuSize - 1) { //if exit is selected
				return;
			}

			UseInventoryItem(selectedItem, ItemType::WEAPON);

			break;
		}

	}
}
void Character::ShowInventoryArmor() {
	system("cls");

	int selectedItem = 0; // Tracks which menu option is selected
	int menuSize = armorInventory.size() + 1;

	MenuItem* menu = new MenuItem[menuSize];

	DrawInventory();

	//print inventory name
	SetCursorPosition(28, 2);
	std::cout << "ARMOR";

	//print inventory contents
	for (int i = 0; i < armorInventory.size(); i++) {

		if (i > 17) { //wrap around

			SetCursorPosition(33, i - 15);
			std::cout << i + 1 << ") " << armorInventory[i].name;
			menu[i] = { 32, i - 15, armorInventory[i].name };

		}
		else {

			SetCursorPosition(3, i + 3);
			std::cout << i + 1 << ") " << armorInventory[i].name;
			menu[i] = { 3, i + 3, armorInventory[i].name };
		}


	}

	//always have exit as last menu item
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

			if (selectedItem == menuSize - 1) { //if exit is selected
				return;
			}

			UseInventoryItem(selectedItem, ItemType::ARMOR);

			break;
		}

	}
}
void Character::ShowInventoryShield() {
	system("cls");

	int selectedItem = 0; // Tracks which menu option is selected
	int menuSize = shieldInventory.size() + 1;

	MenuItem* menu = new MenuItem[menuSize];

	DrawInventory();

	//print inventory name
	SetCursorPosition(27, 2);
	std::cout << "SHIELDS";

	//print inventory contents
	for (int i = 0; i < shieldInventory.size(); i++) {

		if (i > 17) { //wrap around

			SetCursorPosition(33, i - 15);
			std::cout << i + 1 << ") " << shieldInventory[i].name;
			menu[i] = { 32, i - 15, shieldInventory[i].name };

		}
		else {

			SetCursorPosition(3, i + 3);
			std::cout << i + 1 << ") " << shieldInventory[i].name;
			menu[i] = { 3, i + 3, shieldInventory[i].name };
		}


	}

	//always have exit as last menu item
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

			if (selectedItem == menuSize - 1) { //if exit is selected
				return;
			}

			UseInventoryItem(selectedItem, ItemType::SHIELD);

			break;
		}

	}
}

void Character::UseInventoryItem(int index, ItemType type) {
	if (index < 0) return;

	int def = 0;
	int atk = 0;
	int block = 0;

	switch (type) {
	case ItemType::MISC:

		if (index >= miscInventory.size()) {
			return;
		}

		SetCursorPosition(3, 26);

		switch (miscInventory[index].type) {
		case MiscType::POTION: //potion
			SlowPrint("Replenished ", miscInventory[index].health, " HP");

			health += miscInventory[index].health;

			if (health > maxHealth) {
				health = maxHealth;
			}

			miscInventory.erase(miscInventory.begin() + index);
			ShowInventoryMisc();

			break;
		case MiscType::PRAYER: //prayer
			SlowPrint("Teleported back to Town. ");

			player.position.x = 25;
			player.position.y = 15;


			miscInventory.erase(miscInventory.begin() + index);
			
			currentLevel = 0;

			ShowTown();
			break;

		case MiscType::RUNE: //rune
			if (miscInventory[index].atkBoost > 1) {//check what kind of rune
				SlowPrint("Boosted attack stat for 1 round");

				atkBoost += miscInventory[index].atkBoost;
			}
			if (miscInventory[index].defBoost > 1) {
				SlowPrint("Boosted defense stat for 1 round");

				defBoost += miscInventory[index].defBoost;
			}
			if (miscInventory[index].ctbBoost > 1) {
				SlowPrint("Boosted block stat for 1 round");

				ctbBoost += miscInventory[index].ctbBoost;
			}
			if (miscInventory[index].hpBoost > 1) {
				SlowPrint("Boosted HP stat for 1 round");

				hpBoost += miscInventory[index].hpBoost;
			}
			if (miscInventory[index].gldBoost > 1) {
				SlowPrint("Boosted gold drop for 1 round");

				gldBoost += miscInventory[index].gldBoost;
			}
			if (miscInventory[index].expBoost > 1) {
				SlowPrint("Boosted experience for 1 round");

				expBoost += miscInventory[index].expBoost;
			}

			miscInventory.erase(miscInventory.begin() + index);

			ShowInventoryMisc();
			break;
	}

		break;
	case ItemType::WEAPON:

		atk = attack - equippedWeapon.attack + weaponInventory[index].attack;

		SetCursorPosition(3, 26);

		SlowPrint(atk > attack ? "Equipping... +[" : "Equipping... -[", weaponInventory[index].attack, "] to your ATK STAT");

		attack = atk;

		if (!equippedWeapon.name.empty()) { // If a weapon is already equipped
			weaponInventory.push_back(equippedWeapon); // Add it to inventory
		}

		equippedWeapon = weaponInventory[index]; // Equip new weapon
		weaponInventory.erase(weaponInventory.begin() + index);

		ShowInventoryWeapon();
		break;

	case ItemType::ARMOR:

		def = defense - equippedArmor.defense + armorInventory[index].defense;

		SetCursorPosition(3, 26);

		SlowPrint(def > defense ? "Equipping... +[" : "Equipping... -[", armorInventory[index].defense, "] to your DEF STAT");

		defense = def;

		if (!equippedArmor.name.empty()) {
			armorInventory.push_back(equippedArmor);
		}

		equippedArmor = armorInventory[index]; // Equip new armor
		armorInventory.erase(armorInventory.begin() + index);

		ShowInventoryArmor();
		break;

	case ItemType::SHIELD:

		block = block - equippedShield.blockChance + shieldInventory[index].blockChance;

		SetCursorPosition(3, 26);

		SlowPrint(block > block ? "Equipping... +[" : "Equipping... -[", shieldInventory[index].blockChance, "] to your BLOCK STAT");

		block = block;

		if (!equippedShield.name.empty()) {
			shieldInventory.push_back(equippedShield);
		}

		equippedShield = shieldInventory[index]; // Equip new shield
		shieldInventory.erase(shieldInventory.begin() + index);

		ShowInventoryShield();
		break;
	}

}

void Character::PrintStats() {
	//Print Character Stats
	SetCursorPosition(11, 23);
	std::cout << attack;

	SetCursorPosition(11, 24);
	std::cout << defense;

	SetCursorPosition(24, 23);
	std::cout << block;

	SetCursorPosition(24, 24);
	std::cout << level;

	SetCursorPosition(38, 23);
	std::cout << "    ";
	SetCursorPosition(38, 23);
	std::cout << gold;

	SetCursorPosition(38, 24);
	std::cout << experience << '/' << maxExperience;

	SetCursorPosition(51, 23);
	std::cout << health << '/' << maxHealth;

	//print class and name
	SetCursorPosition(9, 1);
	std::cout << name << " the " << CharacterType();

}

std::string Character::CharacterType() {
	switch (type) {
	case characterType::WARRIOR: return "Warrior";
	case characterType::ROUGE: return "Rouge";
	case characterType::MAGE: return "Mage";
	default: return "Unknown";
	}
}