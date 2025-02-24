#include "character.h"
#include "item.h"
#include "random.h"
#include "slowprint.h"
#include "console_utils.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <limits>


using namespace std;

void WaitForUser();
void HideCursor();
bool CheckIfEnoughGold(const Item& item);
void ShopArmourMenu();
void ShopWeaponsMenu();
void ShopPotionsMenu();
void ShopShieldsMenu();
void PlayerMenu();
void NewCharacter();
void ShopMenu();
void LoadGame();
void TitleScreen();
void Battle(short int enemy_ID, short int enemy_level, short int enemy_attack = -1, short int enemy_defence= -1, short int enemy_health = -1);

//global
struct MenuItem {
	int x, y;
	std::string text;
};

//generate Random Items
Weapon w1 = Weapon(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Weapon w2 = Weapon(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Weapon w3 = Weapon(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Weapon w4 = Weapon(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Weapon w5 = Weapon(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));

Armour a1 = Armour(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Armour a2 = Armour(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Armour a3 = Armour(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Armour a4 = Armour(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Armour a5 = Armour(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));

Shield s1 = Shield(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Shield s2 = Shield(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Shield s3 = Shield(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Shield s4 = Shield(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Shield s5 = Shield(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));

Potion p1 = Potion(0); //minor
Potion p2 = Potion(1); //light
Potion p3 = Potion(2); //normal

Character player("", 0);
//global

int main() {

	//player.ShowInventoryMenu();

	TitleScreen();
	PlayerMenu();

	return 0;
}

void PlayerMenu() {
	system("cls");
	int selectedItem = 0; // Tracks which menu option is selected

	std::cout << "#############################################################" //0
		<< "\n#Player:                                                    #"     //1
		<< "\n#------------------------PLAYER_MENU------------------------#"//2
		<< "\n#                                                           #"		//3
		<< "\n#                                                           #"		//4
		<< "\n#                                                           #"		//5
		<< "\n#                                                           #"		//6
		<< "\n#                                                           #"		//7
		<< "\n#                                                           #"		//8
		<< "\n#                                                           #"		//9
		<< "\n#                                                           #"		//10
		<< "\n#                                                           #"		//11
		<< "\n#                                                           #"		//12
		<< "\n#                                                           #"		//13
		<< "\n#                                                           #"		//14
		<< "\n#                                                           #"		//15
		<< "\n#                                                           #"		//16
		<< "\n#                                                           #"		//17
		<< "\n#                                                           #"		//18
		<< "\n#                                                           #"		//19
		<< "\n#                                                           #"		//20
		<< "\n#-----------------------------------------------------------#"		//21
		<< "\n#---------------------------STATS---------------------------#"		//22
		<< "\n#  ATTACK:     | BLOCK:       | GOLD:        | HP:          #"		//23
		<< "\n# DEFENSE:     | LEVEL:       |  EXP:        |              #"		//24
		<< "\n#-----------------------------------------------------------#"		//25
		<< "\n#                                                  [Exit]   #"		//26
		<< "\n#############################################################";	//27

	
	player.PrintStats();

	MenuItem menu[] = {
		{ 6, 6, "Find Enemy"},
		{ 40, 6, "Shop"},
		{ 6, 8, "Inventory"},
		{ 44, 26, "[Save & Quit]" }
	};

	int menuSize = sizeof(menu) / sizeof(menu[0]);

	// Menu loop
	while (true) {

		for (int i = 0; i < menuSize; i++) {
			SetCursorPosition(menu[i].x, menu[i].y);
			cout << (i == selectedItem ? ">" : " ") << menu[i].text;
		}

		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			switch (input) {
			case 72: // Up arrow
				selectedItem = (selectedItem - 1 + menuSize) % menuSize;
				break;
			case 75: // Left arrow
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
			case 0: Battle(new_rnd_num(9), new_rnd_num(5)); break;
			case 1: ShopMenu(); break;
			case 2: player.ShowInventoryMenu(); break;
			case 3: TitleScreen(); break;
			}

			PlayerMenu(); //loop back to menu

		}

	}


}

void DrawBattle(Enemy * e) {
	system("cls");


	//Print Menu Borders
	std::cout << "======================RuneBorn===============================" //0
		<< "\n=                                    lvl----------     ==== ="     //1
		<< "\n=                                                      |  | ="		//2
		<< "\n=                                                      |  | ="		//3
		<< "\n=                                                      |  | ="     //4
		<< "\n=                                                      |  | ="		//5
		<< "\n=                                                      |  | ="		//6
		<< "\n=                                                      |  | ="		//7
		<< "\n=                                                      ==== ="		//8
		<< "\n=                                                           ="		//9
		<< "\n=                                                           ="		//10
		<< "\n=  HP                                                       ="		//11
		<< "\n= 25/40                                                     ="		//12
		<< "\n= ====                                                      ="		//13
		<< "\n= |  |                                                      ="		//14
		<< "\n= |  |                                                      ="		//15
		<< "\n= |  |                                                      ="		//16
		<< "\n= |  |                                                      ="		//17
		<< "\n= |  |                                                      ="		//18
		<< "\n= |  |                                                      ="		//19
		<< "\n= ====  ------------                                        ="		//20
		<< "\n#-----------------------------------------------------------#"		//21
		<< "\n#---------------------------MENU----------------------------#"		//22
		<< "\n#  ATTACK:                                                  #"		//23
		<< "\n#  INVENTORY:    RUN:                                       #"		//24
		<< "\n#-----------------------------------------------------------#"		//25
		<< "\n#                                                           #"		//26
		<< "\n#############################################################";	//27

	SetCursorPosition(34, 1);
	cout << "LVL: " << e->enemyLevel << " " << e->enemyName;

	PrintSpriteAt(30, 2, e->enemySprite);

	SetCursorPosition(2, 12);
	cout << player.playerHealth << "/" << player.playerMaxHealth;

	PrintSpriteAt(8, 4, player.playerSprite);

	SetCursorPosition(8, 20);
	cout << "LVL: " << player.playerLevel << " " << player.playerName;

	//player health bar
	float x = player.playerMaxHealth / 6.0f;
	int y = player.playerHealth / x;

	switch (y) {
	case 0: break;
	case 1: 
		PrintSpriteAt(3, 14, "  \n  \n  \n  \n  \n++");		
		break;
	case 2:
		PrintSpriteAt(3, 14, "  \n  \n  \n  \n++\n++");
		break;
	case 3:
		PrintSpriteAt(3, 14, "  \n  \n  \n++\n++\n++");
		break;
	case 4:
		PrintSpriteAt(3, 14, "  \n  \n++\n++\n++\n++");
		break;
	case 5:
		PrintSpriteAt(3, 14, "  \n++\n++\n++\n++\n++");
		break;
	case 6:
		PrintSpriteAt(3, 14, "++\n++\n++\n++\n++\n++");
		break;
	}

	//player health bar
	x = e->enemyMaxHealth / 6.0f;
	y = e->enemyHealth / x;

	switch (y) {
	case 0: break;
	case 1:
		PrintSpriteAt(56, 2, "  \n  \n  \n  \n  \n++");
		break;
	case 2:
		PrintSpriteAt(56, 2, "  \n  \n  \n  \n++\n++");
		break;
	case 3:
		PrintSpriteAt(56, 2, "  \n  \n  \n++\n++\n++");
		break;
	case 4:
		PrintSpriteAt(56, 2, "  \n  \n++\n++\n++\n++");
		break;
	case 5:
		PrintSpriteAt(56, 2, "  \n++\n++\n++\n++\n++");
		break;
	case 6:
		PrintSpriteAt(56, 2, "++\n++\n++\n++\n++\n++");
		break;
	}

}

void Battle(short int enemy_ID, short int enemy_level, short int enemy_attack, short int enemy_defence, short int enemy_health) {
	//create new enemy on heap
	Enemy* e1 = new Enemy(enemy_ID, enemy_level, enemy_attack, enemy_defence, enemy_health);

	int selectedItem = 0; // Tracks which menu option is selected


	MenuItem menu[] = {
		{ 3, 23, "ATTACK"},
		{ 3, 24, "INVENTORY"},
		{ 17, 24, "RUN" }
	};

	DrawBattle(e1);

	int menuSize = sizeof(menu) / sizeof(menu[0]);

	bool battleEnd = false;

	while (battleEnd == false) {

			for (int i = 0; i < menuSize; i++) {
				SetCursorPosition(menu[i].x, menu[i].y);
				cout << (i == selectedItem ? ">" : " ") << menu[i].text;
			}

			SetCursorPosition(2, 26);
			cout << "What Will you Do?";

			int input = _getch();

			if (input == 224) { // Arrow keys
				input = _getch();

				switch (input) {
				case 72: // Up arrow
					selectedItem = (selectedItem - 1 + menuSize) % menuSize;
					break;
				case 75: // Left arrow
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
				case 0:

					if (player.Attack(*e1)) {
						battleEnd = true;
						break;
					}
					if (e1->Attack(player)) {
						battleEnd = true;
						break;
					}
					DrawBattle(e1);

					break;
				case 1:
					player.ShowInventoryMenu();
					DrawBattle(e1);
					break;
				case 2:
					SetCursorPosition(2, 26);
					SlowPrint("Got away safely...");
					WaitForUser();

					battleEnd = true;
					break;
				}

			}	
	}

	delete e1; //delete monster battle finish
	e1 = nullptr;

	return;
}

void ShopMenu() {

	system("cls");
	int selectedItem = 0; // Tracks which menu option is selected

	std::cout << "#############################################################" //0
		<< "\n#Player:                                                    #"     //1
		<< "\n#-------------------------SHOP_MENU-------------------------#"//2
		<< "\n#                                                           #"		//3
		<< "\n#                                                           #"		//4
		<< "\n#                                                           #"		//5
		<< "\n#                                                           #"		//6
		<< "\n#                                                           #"		//7
		<< "\n#                                                           #"		//8
		<< "\n#                                                           #"		//9
		<< "\n#                                                           #"		//10
		<< "\n#                                                           #"		//11
		<< "\n#                                                           #"		//12
		<< "\n#                                                           #"		//13
		<< "\n#                                                           #"		//14
		<< "\n#                                                           #"		//15
		<< "\n#                                                           #"		//16
		<< "\n#                                                           #"		//17
		<< "\n#                                                           #"		//18
		<< "\n#                                                           #"		//19
		<< "\n#                                                           #"		//20
		<< "\n#-----------------------------------------------------------#"		//21
		<< "\n#---------------------------STATS---------------------------#"		//22
		<< "\n#  ATTACK:     | BLOCK:       | GOLD:        | HP:          #"		//23
		<< "\n# DEFENSE:     | LEVEL:       |  EXP:        |              #"		//24
		<< "\n#-----------------------------------------------------------#"		//25
		<< "\n#                                                  [Exit]   #"		//26
		<< "\n#############################################################";	//27


	player.PrintStats();

	MenuItem menu[] = {
		{ 4, 6, "Potions"},
		{ 4, 8, "Weapons"},
		{ 4, 10, "Armor"},
		{ 4, 12, "Shields"},
		{ 50, 26, "[Exit]" }
	};

	int menuSize = sizeof(menu) / sizeof(menu[0]);

	// Menu loop
	while (true) {

		for (int i = 0; i < menuSize; i++) {
			SetCursorPosition(menu[i].x, menu[i].y);
			cout << (i == selectedItem ? ">" : " ") << menu[i].text;
		}

		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			switch (input) {
			case 72: // Up arrow
				selectedItem = (selectedItem - 1 + menuSize) % menuSize;
				break;
			case 75: // Left arrow
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
			case 0: ShopPotionsMenu(); break;
			case 1: ShopWeaponsMenu(); break;
			case 2: ShopArmourMenu(); break;
			case 3: ShopShieldsMenu(); break;
			case 4: PlayerMenu(); break;
			}

		}

	}

}
void ShopPotionsMenu() {
	system("cls");
	int selectedItem = 0; // Tracks which menu option is selected

	std::cout << "#############################################################" //0
		<< "\n#Player:                                                    #"     //1
		<< "\n#-----------------------POTIONS_MENU------------------------#"//2
		<< "\n#                                                           #"		//3
		<< "\n#                                                           #"		//4
		<< "\n#                                                           #"		//5
		<< "\n#          -                                                #"        //6
		<< "\n#                                                           #"        //7
		<< "\n#                                                           #"        //8
		<< "\n#                                                           #"		//9
		<< "\n#                                                           #"		//10
		<< "\n#                                                           #"		//11
		<< "\n#                                                           #"		//12
		<< "\n#                                                           #"		//13
		<< "\n#                                                           #"		//14
		<< "\n#                                                           #"		//15
		<< "\n#                                                           #"		//16
		<< "\n#                                                           #"		//17
		<< "\n#                                                           #"		//18
		<< "\n#                                                           #"		//19
		<< "\n#                                                           #"		//20
		<< "\n#-----------------------------------------------------------#"		//21
		<< "\n#---------------------------STATS---------------------------#"		//22
		<< "\n#  ATTACK:     | BLOCK:       | GOLD:        | HP:          #"		//23
		<< "\n# DEFENSE:     | LEVEL:       |  EXP:        |              #"		//24
		<< "\n#-----------------------------------------------------------#"		//25
		<< "\n#                                                  [Exit]   #"		//26
		<< "\n#############################################################";	//27


	player.PrintStats();

	MenuItem menu[] = {
		{ 5, 6, p1.name},
		{ 5, 7, p2.name},
		{ 5, 8, p3.name},
		{ 50, 26, "[Exit]" }
	};

	//print descriptions
	SetCursorPosition(31, 6);
	cout << "- Restores " << p1.health << " HP";

	SetCursorPosition(31, 7);
	cout << "- Restores " << p2.health << " HP";

	SetCursorPosition(31, 8);
	cout << "- Restores " << p3.health << " HP";

	//print costs
	SetCursorPosition(49, 6);
	cout << "| " << p1.cost << " Gold";

	SetCursorPosition(49, 7);
	cout << "| " << p2.cost << " Gold";

	SetCursorPosition(49, 8);
	cout << "| " << p3.cost << " Gold";


	int menuSize = sizeof(menu) / sizeof(menu[0]);

	// Menu loop
	while (true) {

		for (int i = 0; i < menuSize; i++) {

			int cursorOffset = 0;

			if (i != menuSize - 1) {
				cursorOffset = 3;
			}

			SetCursorPosition(menu[i].x - cursorOffset, menu[i].y);


			// Highlight the selected item
			cout << (i == selectedItem ? ">" : " ");

			// Only print the number if it's NOT the last item [Exit]
			if (i != menuSize - 1) {
				cout << i + 1 << ") ";
			}

			// Print the menu item text
			cout << menu[i].text;
		}


		//get input
		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			switch (input) {
			case 72: // Up arrow
				selectedItem = (selectedItem - 1 + menuSize) % menuSize;
				break;
			case 75: // Left arrow
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
			case 0: 
				if (CheckIfEnoughGold(p1)) {
					player.playerGold -= p1.cost;
					player.potionInventory.push_back(p1);

					SetCursorPosition(2, 26); //info
					SlowPrint(0, p1.name, " added to Inventory...");

					WaitForUser();
					player.PrintStats();

					SetCursorPosition(2, 26); //clear line
					cout << "                                                  ";
				}
				else {
					SetCursorPosition(2, 26);

					SlowPrint(0, "Not enough gold...");
					WaitForUser();

					SetCursorPosition(2, 26); //clear line
					cout << "                                                  ";
				}

				break;
			case 1: 
				if (CheckIfEnoughGold(p2)) {
					player.playerGold -= p2.cost;
					player.potionInventory.push_back(p2);

					SetCursorPosition(2, 26); // Info
					SlowPrint(0, p2.name, " added to Inventory...");

					WaitForUser();
					player.PrintStats();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}
				else {
					SetCursorPosition(2, 26);
					SlowPrint(0, "Not enough gold...");
					WaitForUser();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}

				break;
			case 2: 
				if (CheckIfEnoughGold(p3)) {
					player.playerGold -= p3.cost;
					player.potionInventory.push_back(p3);

					SetCursorPosition(2, 26); // Info
					SlowPrint(0, p3.name, " added to Inventory...");

					WaitForUser();
					player.PrintStats();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}
				else {
					SetCursorPosition(2, 26);
					SlowPrint(0, "Not enough gold...");
					WaitForUser();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}

				break;
			case 3: ShopMenu();	break;
			}

		}
		else if (input == 'i') { //inventory
			player.ShowInventoryMenu();
		}

	}

}
void ShopWeaponsMenu() {
	system("cls");
	int selectedItem = 0; // Tracks which menu option is selected

	std::cout << "#############################################################" //0
		<< "\n#Player:                                                    #"     //1
		<< "\n#-----------------------WEAPONS_MENU------------------------#"//2
		<< "\n#                                                           #"		//3
		<< "\n#                                                           #"		//4
		<< "\n#                                                           #"		//5
		<< "\n#          -                                                #"        //6
		<< "\n#                                                           #"        //7
		<< "\n#                                                           #"        //8
		<< "\n#                                                           #"		//9
		<< "\n#                                                           #"		//10
		<< "\n#                                                           #"		//11
		<< "\n#                                                           #"		//12
		<< "\n#                                                           #"		//13
		<< "\n#                                                           #"		//14
		<< "\n#                                                           #"		//15
		<< "\n#                                                           #"		//16
		<< "\n#                                                           #"		//17
		<< "\n#                                                           #"		//18
		<< "\n#                                                           #"		//19
		<< "\n#                                                           #"		//20
		<< "\n#-----------------------------------------------------------#"		//21
		<< "\n#---------------------------STATS---------------------------#"		//22
		<< "\n#  ATTACK:     | BLOCK:       | GOLD:        | HP:          #"		//23
		<< "\n# DEFENSE:     | LEVEL:       |  EXP:        |              #"		//24
		<< "\n#-----------------------------------------------------------#"		//25
		<< "\n#                                                  [Exit]   #"		//26
		<< "\n#############################################################";	//27


	player.PrintStats();

	MenuItem menu[] = {
		{ 5, 6, w1.name},
		{ 5, 7, w2.name},
		{ 5, 8, w3.name},
		{ 5, 9, w4.name},
		{ 5, 10, w5.name},
		{ 50, 26, "[Exit]" }
	};

	//print descriptions
	SetCursorPosition(31, 6);
	cout << "- Attack [+" << w1.attack << "]";

	SetCursorPosition(31, 7);
	cout << "- Attack [+" << w2.attack << "]";

	SetCursorPosition(31, 8);
	cout << "- Attack [+" << w3.attack << "]";

	SetCursorPosition(31, 9);
	cout << "- Attack [+" << w4.attack << "]";

	SetCursorPosition(31, 10);
	cout << "- Attack [+" << w5.attack << "]";

	//print costs
	SetCursorPosition(49, 6);
	cout << "| " << w1.cost << " Gold";

	SetCursorPosition(49, 7);
	cout << "| " << w2.cost << " Gold";

	SetCursorPosition(49, 8);
	cout << "| " << w3.cost << " Gold";

	SetCursorPosition(49, 9);
	cout << "| " << w4.cost << " Gold";

	SetCursorPosition(49, 10);
	cout << "| " << w5.cost << " Gold";


	int menuSize = sizeof(menu) / sizeof(menu[0]);

	// Menu loop
	while (true) {

		for (int i = 0; i < menuSize; i++) {

			int cursorOffset = 0;

			if (i != menuSize - 1) {
				cursorOffset = 3;
			}

			SetCursorPosition(menu[i].x - cursorOffset, menu[i].y);


			// Highlight the selected item
			cout << (i == selectedItem ? ">" : " ");

			// Only print the number if it's NOT the last item [Exit]
			if (i != menuSize - 1) {
				cout << i + 1 << ") ";
			}

			// Print the menu item text
			cout << menu[i].text;
		}


		//get input
		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			switch (input) {
			case 72: // Up arrow
				selectedItem = (selectedItem - 1 + menuSize) % menuSize;
				break;
			case 75: // Left arrow
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
			case 0:
				if (CheckIfEnoughGold(w1)) {
					player.playerGold -= w1.cost;
					player.weaponInventory.push_back(w1);

					SetCursorPosition(2, 26); //info
					SlowPrint(0, w1.name, " added to Inventory...");

					WaitForUser();
					player.PrintStats();

					SetCursorPosition(2, 26); //clear line
					cout << "                                                  ";
				}
				else {
					SetCursorPosition(2, 26);

					SlowPrint(0, "Not enough gold...");
					WaitForUser();

					SetCursorPosition(2, 26); //clear line
					cout << "                                                  ";
				}

				break;
			case 1:
				if (CheckIfEnoughGold(w2)) {
					player.playerGold -= w2.cost;
					player.weaponInventory.push_back(w2);

					SetCursorPosition(2, 26); // Info
					SlowPrint(0, w2.name, " added to Inventory...");

					WaitForUser();
					player.PrintStats();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}
				else {
					SetCursorPosition(2, 26);
					SlowPrint(0, "Not enough gold...");
					WaitForUser();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}

				break;
			case 2:
				if (CheckIfEnoughGold(w3)) {
					player.playerGold -= w3.cost;
					player.weaponInventory.push_back(w3);

					SetCursorPosition(2, 26); // Info
					SlowPrint(0, w3.name, " added to Inventory...");

					WaitForUser();
					player.PrintStats();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}
				else {
					SetCursorPosition(2, 26);
					SlowPrint(0, "Not enough gold...");
					WaitForUser();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}

				break;
			case 3:
				if (CheckIfEnoughGold(w4)) {
					player.playerGold -= w4.cost;
					player.weaponInventory.push_back(w4);

					SetCursorPosition(2, 26); // Info
					SlowPrint(0, w4.name, " added to Inventory...");

					WaitForUser();
					player.PrintStats();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}
				else {
					SetCursorPosition(2, 26);
					SlowPrint(0, "Not enough gold...");
					WaitForUser();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}

				break;
			case 4:
				if (CheckIfEnoughGold(w5)) {
					player.playerGold -= w5.cost;
					player.weaponInventory.push_back(w5);

					SetCursorPosition(2, 26); // Info
					SlowPrint(0, w5.name, " added to Inventory...");

					WaitForUser();
					player.PrintStats();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}
				else {
					SetCursorPosition(2, 26);
					SlowPrint(0, "Not enough gold...");
					WaitForUser();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}

				break;
			case 5: ShopMenu(); break;
			}

		}

	}
}
void ShopArmourMenu() {
	system("cls");
	int selectedItem = 0; // Tracks which menu option is selected

	std::cout << "#############################################################" //0
		<< "\n#Player:                                                    #"     //1
		<< "\n#------------------------ARMOR_MENU-------------------------#"//2
		<< "\n#                                                           #"		//3
		<< "\n#                                                           #"		//4
		<< "\n#                                                           #"		//5
		<< "\n#          -                                                #"        //6
		<< "\n#                                                           #"        //7
		<< "\n#                                                           #"        //8
		<< "\n#                                                           #"		//9
		<< "\n#                                                           #"		//10
		<< "\n#                                                           #"		//11
		<< "\n#                                                           #"		//12
		<< "\n#                                                           #"		//13
		<< "\n#                                                           #"		//14
		<< "\n#                                                           #"		//15
		<< "\n#                                                           #"		//16
		<< "\n#                                                           #"		//17
		<< "\n#                                                           #"		//18
		<< "\n#                                                           #"		//19
		<< "\n#                                                           #"		//20
		<< "\n#-----------------------------------------------------------#"		//21
		<< "\n#---------------------------STATS---------------------------#"		//22
		<< "\n#  ATTACK:     | BLOCK:       | GOLD:        | HP:          #"		//23
		<< "\n# DEFENSE:     | LEVEL:       |  EXP:        |              #"		//24
		<< "\n#-----------------------------------------------------------#"		//25
		<< "\n#                                                  [Exit]   #"		//26
		<< "\n#############################################################";	//27


	player.PrintStats();

	MenuItem menu[] = {
		{ 5, 6, a1.name},
		{ 5, 7, a2.name},
		{ 5, 8, a3.name},
		{ 5, 9, a4.name},
		{ 5, 10, a5.name},
		{ 50, 26, "[Exit]" }
	};

	//print descriptions
	SetCursorPosition(31, 6);
	cout << "- Defense [+" << a1.defense << "]";

	SetCursorPosition(31, 7);
	cout << "- Defense [+" << a2.defense << "]";

	SetCursorPosition(31, 8);
	cout << "- Defense [+" << a3.defense << "]";

	SetCursorPosition(31, 9);
	cout << "- Defense [+" << a4.defense << "]";

	SetCursorPosition(31, 10);
	cout << "- Defense [+" << a5.defense << "]";

	//print costs
	SetCursorPosition(49, 6);
	cout << "| " << a1.cost << " Gold";

	SetCursorPosition(49, 7);
	cout << "| " << a2.cost << " Gold";

	SetCursorPosition(49, 8);
	cout << "| " << a3.cost << " Gold";

	SetCursorPosition(49, 9);
	cout << "| " << a4.cost << " Gold";

	SetCursorPosition(49, 10);
	cout << "| " << a5.cost << " Gold";


	int menuSize = sizeof(menu) / sizeof(menu[0]);

	// Menu loop
	while (true) {

		for (int i = 0; i < menuSize; i++) {

			int cursorOffset = 0;

			if (i != menuSize - 1) {
				cursorOffset = 3;
			}

			SetCursorPosition(menu[i].x - cursorOffset, menu[i].y);


			// Highlight the selected item
			cout << (i == selectedItem ? ">" : " ");

			// Only print the number if it's NOT the last item [Exit]
			if (i != menuSize - 1) {
				cout << i + 1 << ") ";
			}

			// Print the menu item text
			cout << menu[i].text;
		}


		//get input
		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			switch (input) {
			case 72: // Up arrow
				selectedItem = (selectedItem - 1 + menuSize) % menuSize;
				break;
			case 75: // Left arrow
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
			case 0:
				if (CheckIfEnoughGold(a1)) {
					player.playerGold -= a1.cost;
					player.armourInventory.push_back(a1);

					SetCursorPosition(2, 26); //info
					SlowPrint(0, a1.name, " added to Inventory...");

					WaitForUser();
					player.PrintStats();

					SetCursorPosition(2, 26); //clear line
					cout << "                                                  ";
				}
				else {
					SetCursorPosition(2, 26);

					SlowPrint(0, "Not enough gold...");
					WaitForUser();

					SetCursorPosition(2, 26); //clear line
					cout << "                                                  ";
				}

				break;
			case 1:
				if (CheckIfEnoughGold(a2)) {
					player.playerGold -= a2.cost;
					player.armourInventory.push_back(a2);

					SetCursorPosition(2, 26); // Info
					SlowPrint(0, a2.name, " added to Inventory...");

					WaitForUser();
					player.PrintStats();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}
				else {
					SetCursorPosition(2, 26);
					SlowPrint(0, "Not enough gold...");
					WaitForUser();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}

				break;
			case 2:
				if (CheckIfEnoughGold(a3)) {
					player.playerGold -= a3.cost;
					player.armourInventory.push_back(a3);

					SetCursorPosition(2, 26); // Info
					SlowPrint(0, a3.name, " added to Inventory...");

					WaitForUser();
					player.PrintStats();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}
				else {
					SetCursorPosition(2, 26);
					SlowPrint(0, "Not enough gold...");
					WaitForUser();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}

				break;
			case 3:
				if (CheckIfEnoughGold(a4)) {
					player.playerGold -= a4.cost;
					player.armourInventory.push_back(a4);

					SetCursorPosition(2, 26); // Info
					SlowPrint(0, a4.name, " added to Inventory...");

					WaitForUser();
					player.PrintStats();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}
				else {
					SetCursorPosition(2, 26);
					SlowPrint(0, "Not enough gold...");
					WaitForUser();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}

				break;
			case 4:
				if (CheckIfEnoughGold(a5)) {
					player.playerGold -= a5.cost;
					player.armourInventory.push_back(a5);

					SetCursorPosition(2, 26); // Info
					SlowPrint(0, a5.name, " added to Inventory...");

					WaitForUser();
					player.PrintStats();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}
				else {
					SetCursorPosition(2, 26);
					SlowPrint(0, "Not enough gold...");
					WaitForUser();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}

				break;
			case 5:	ShopMenu();	break;
			}

		}

	}

}
void ShopShieldsMenu() {


	system("cls");
	int selectedItem = 0; // Tracks which menu option is selected

	std::cout << "#############################################################" //0
		<< "\n#Player:                                                    #"     //1
		<< "\n#-----------------------SHIELDS_MENU------------------------#"//2
		<< "\n#                                                           #"		//3
		<< "\n#                                                           #"		//4
		<< "\n#                                                           #"		//5
		<< "\n#          -                                                #"        //6
		<< "\n#                                                           #"        //7
		<< "\n#                                                           #"        //8
		<< "\n#                                                           #"		//9
		<< "\n#                                                           #"		//10
		<< "\n#                                                           #"		//11
		<< "\n#                                                           #"		//12
		<< "\n#                                                           #"		//13
		<< "\n#                                                           #"		//14
		<< "\n#                                                           #"		//15
		<< "\n#                                                           #"		//16
		<< "\n#                                                           #"		//17
		<< "\n#                                                           #"		//18
		<< "\n#                                                           #"		//19
		<< "\n#                                                           #"		//20
		<< "\n#-----------------------------------------------------------#"		//21
		<< "\n#---------------------------STATS---------------------------#"		//22
		<< "\n#  ATTACK:     | BLOCK:       | GOLD:        | HP:          #"		//23
		<< "\n# DEFENSE:     | LEVEL:       |  EXP:        |              #"		//2
		<< "\n#-----------------------------------------------------------#"		//25
		<< "\n#                                                  [Exit]   #"		//26
		<< "\n#############################################################";	//27


	player.PrintStats();

	MenuItem menu[] = {
		{ 5, 6, s1.name},
		{ 5, 7, s2.name},
		{ 5, 8, s3.name},
		{ 5, 9, s4.name},
		{ 5, 10, s5.name},
		{ 50, 26, "[Exit]" }
	};

	//print descriptions
	SetCursorPosition(31, 6);
	cout << "- BlockChance [+" << s1.blockChance << "]";

	SetCursorPosition(31, 7);
	cout << "- BlockChance [+" << s2.blockChance << "]";

	SetCursorPosition(31, 8);
	cout << "- BlockChance [+" << s3.blockChance << "]";

	SetCursorPosition(31, 9);
	cout << "- BlockChance [+" << s4.blockChance << "]";

	SetCursorPosition(31, 10);
	cout << "- BlockChance [+" << s5.blockChance << "]";

	//print costs
	SetCursorPosition(49, 6);
	cout << "| " << s1.cost << " Gold";

	SetCursorPosition(49, 7);
	cout << "| " << s2.cost << " Gold";

	SetCursorPosition(49, 8);
	cout << "| " << s3.cost << " Gold";

	SetCursorPosition(49, 9);
	cout << "| " << s4.cost << " Gold";

	SetCursorPosition(49, 10);
	cout << "| " << s5.cost << " Gold";


	int menuSize = sizeof(menu) / sizeof(menu[0]);

	// Menu loop
	while (true) {

		for (int i = 0; i < menuSize; i++) {

			int cursorOffset = 0;

			if (i != menuSize - 1) {
				cursorOffset = 3;
			}

			SetCursorPosition(menu[i].x - cursorOffset, menu[i].y);


			// Highlight the selected item
			cout << (i == selectedItem ? ">" : " ");

			// Only print the number if it's NOT the last item [Exit]
			if (i != menuSize - 1) {
				cout << i + 1 << ") ";
			}

			// Print the menu item text
			cout << menu[i].text;
		}


		//get input
		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			switch (input) {
			case 72: // Up arrow
				selectedItem = (selectedItem - 1 + menuSize) % menuSize;
				break;
			case 75: // Left arrow
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
			case 0:
				if (CheckIfEnoughGold(s1)) {
					player.playerGold -= s1.cost;
					player.shieldInventory.push_back(s1);

					SetCursorPosition(2, 26); //info
					SlowPrint(0, s1.name, " added to Inventory...");

					WaitForUser();
					player.PrintStats();

					SetCursorPosition(2, 26); //clear line
					cout << "                                                  ";
				}
				else {
					SetCursorPosition(2, 26);

					SlowPrint(0, "Not enough gold...");
					WaitForUser();

					SetCursorPosition(2, 26); //clear line
					cout << "                                                  ";
				}

				break;
			case 1:
				if (CheckIfEnoughGold(s2)) {
					player.playerGold -= s2.cost;
					player.shieldInventory.push_back(s2);

					SetCursorPosition(2, 26); // Info
					SlowPrint(0, s2.name, " added to Inventory...");

					WaitForUser();
					player.PrintStats();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}
				else {
					SetCursorPosition(2, 26);
					SlowPrint(0, "Not enough gold...");
					WaitForUser();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}

				break;
			case 2:
				if (CheckIfEnoughGold(s3)) {
					player.playerGold -= s3.cost;
					player.shieldInventory.push_back(s3);

					SetCursorPosition(2, 26); // Info
					SlowPrint(0, s3.name, " added to Inventory...");

					WaitForUser();
					player.PrintStats();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}
				else {
					SetCursorPosition(2, 26);
					SlowPrint(0, "Not enough gold...");
					WaitForUser();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}

				break;
			case 3:
				if (CheckIfEnoughGold(s4)) {
					player.playerGold -= s4.cost;
					player.shieldInventory.push_back(s4);

					SetCursorPosition(2, 26); // Info
					SlowPrint(0, s4.name, " added to Inventory...");

					WaitForUser();
					player.PrintStats();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}
				else {
					SetCursorPosition(2, 26);
					SlowPrint(0, "Not enough gold...");
					WaitForUser();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}

				break;
			case 4:
				if (CheckIfEnoughGold(s5)) {
					player.playerGold -= s5.cost;
					player.shieldInventory.push_back(s5);

					SetCursorPosition(2, 26); // Info
					SlowPrint(0, s5.name, " added to Inventory...");

					WaitForUser();
					player.PrintStats();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}
				else {
					SetCursorPosition(2, 26);
					SlowPrint(0, "Not enough gold...");
					WaitForUser();

					SetCursorPosition(2, 26); // Clear line
					cout << "                                                  ";
				}

				break;
			case 5:	ShopMenu();	break;
			}

		}

	}

}

bool CheckIfEnoughGold(const Item& item) {
	if (player.playerGold < item.cost) {
		SlowPrint(0, "Not enough Gold");
		WaitForUser();
		return false;
	}
	return true;
}

void TitleScreen() {
	srand(time(0)); // Random seed
	HideCursor(); // Hide cursor

	system("cls");
	int selectedItem = 0; // Tracks which menu option is selected

	MenuItem menu[] = {
		{ 0, 10, "New Game"},
		{ 0, 11, "Load Game"},
		{ 0, 12, "Exit"}
	};

	int menuSize = sizeof(menu) / sizeof(menu[0]);

		cout << "\n ______    __   __  __    _  _______  _______  _______  ______    __    _ "
			<< "\n|    _ |  |  | |  ||  |  | ||       ||  _    ||       ||    _ |  |  |  | |"
			<< "\n|   | ||  |  | |  ||   |_| ||    ___|| |_|   ||   _   ||   | ||  |   |_| |"
			<< "\n|   |_||_ |  |_|  ||       ||   |___ |       ||  | |  ||   |_||_ |       |"
			<< "\n|    __  ||       ||  _    ||    ___||  _   | |  |_|  ||    __  ||  _    |"
			<< "\n|   |  | ||       || | |   ||   |___ | |_|   ||       ||   |  | || | |   |"
			<< "\n|___|  |_||_______||_|  |__||_______||_______||_______||___|  |_||_|  |__|";
		cout << "\nBy: Christian Cutts :0\n";

		// Menu loop
		while (true) {
			for (int i = 0; i < menuSize; i++) {
				SetCursorPosition(menu[i].x, menu[i].y);
				cout << (i == selectedItem ? ">" : " ) ") << menu[i].text << "   ";
			}

			int input = _getch();

			if (input == 224) { // Arrow keys
				input = _getch();

				switch (input) {
				case 72: // Up arrow
					selectedItem = (selectedItem - 1 + menuSize) % menuSize;
					break;
				case 80: // Down arrow
					selectedItem = (selectedItem + 1) % menuSize;
					break;
				}

			} else if (input == '\r') { // Enter key

				SetCursorPosition(0, menu[menuSize - 1].y + 2); // Move cursor below menu

				switch (selectedItem) {
				case 0: NewCharacter(); break;
				case 1: LoadGame(); break;;
				case 2: cout << "Quitting...\n"; exit(0);
			}
		}
	}
}

void NewCharacter() {
	string playerName = "";
	int playerClass = 0;
	
	system("cls");
	int selectedItem = 0; // Tracks which menu option is selected

	MenuItem menu[] = {
		{ 0, 2, "Barbarian"},
		{ 0, 3, "Knight"},
		{ 0, 4, "Mage"},
		{ 0, 5, "BACK" }
	};

	int menuSize = sizeof(menu) / sizeof(menu[0]);

	//Menu Title
	cout << "\n___Character Select___\n";

	// Menu loop
	while (true) {

		for (int i = 0; i < menuSize; i++) {
			SetCursorPosition(menu[i].x, menu[i].y);
			cout << (i == selectedItem ? ">" : " ) ") << menu[i].text << "   ";
		}

		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			switch (input) {
			case 72: // Up arrow
				selectedItem = (selectedItem - 1 + menuSize) % menuSize;
				break;
			case 80: // Down arrow
				selectedItem = (selectedItem + 1) % menuSize;
				break;
			}

		}
		else if (input == '\r') { // Enter key

			SetCursorPosition(0, menu[menuSize - 1].y + 2); // Move cursor below menu

			switch (selectedItem) {
			case 0: playerClass = 0; break;
			case 1: playerClass = 1; break;
			case 2: playerClass = 2; break;
			case 3: TitleScreen(); break;
			}

			cout << "Enter your name: ";

			getline(cin, playerName);

			Character* plr = new Character(playerName, playerClass);

			player = *plr;

			delete plr;

			PlayerMenu();

		}
	}

}

void LoadGame() {
	cout << "poo";
}



