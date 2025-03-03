#include "menu.h"


Weapon w1 = Weapon(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Weapon w2 = Weapon(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Weapon w3 = Weapon(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Weapon w4 = Weapon(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Weapon w5 = Weapon(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));

Armor a1 = Armor(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Armor a2 = Armor(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Armor a3 = Armor(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Armor a4 = Armor(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Armor a5 = Armor(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));

Shield s1 = Shield(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Shield s2 = Shield(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Shield s3 = Shield(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Shield s4 = Shield(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));
Shield s5 = Shield(new_rnd_num(31), new_rnd_num(999), new_rnd_num(200), new_rnd_num(30));

Misc p1 = Misc(0); //minor
Misc p2 = Misc(1); //light
Misc p3 = Misc(2); //normal

Misc m1 = Misc(4); //tp

Misc r1 = Misc(5); //runes
Misc r2 = Misc(6);
Misc r3 = Misc(7);
Misc r4 = Misc(8);
Misc r5 = Misc(9);
Misc r6 = Misc(10);



void PlayerMenu() {

	const char* menuSprite = "+-------------+\n|             |\n|             |\n|             |\n|             |\n|             |\n|             |\n|             |\n|             |\n|             |\n+-------------+";

	Beep(1500, 200);

	int selectedItem = 0; // Tracks which menu option is selected

	bool cheat_trigger = false;

	PrintSpriteAt(40, 3, menuSprite);

	player.PrintStats();

	MenuItem menu[] = {
		{ 42, 5, "INVENTORY"},
		{ 42, 7, "BACK"},
		{ 42, 9, "SAVE"},
		{ 42, 11, "Save & Quit" }
	};

	int menuSize = sizeof(menu) / sizeof(menu[0]);

	// Menu loop
	while (true) {

		for (int i = 0; i < menuSize; i++) {
			SetCursorPosition(menu[i].x, menu[i].y);
			std::cout << (i == selectedItem ? ">" : " ") << menu[i].text;
		}

		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			Beep(1000, 100);

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

			Beep(1500, 200);

			switch (selectedItem) {
			case 0: player.ShowInventoryMenu(); break;
			case 1: 
				if (!player.inTown) {
					dungeon.ShowDungeon();
				}
				ShowTown();
				break;
			case 2: SaveGame(); break;
			case 3: SaveGame(); TitleScreen(); break;
			}

			PlayerMenu(); //loop back to menu

		}
		else if (input == 'c') {
			cheat_trigger = true;
		}
		else if (input == 'h' && cheat_trigger) {
			player.gold = 9999;
			player.PrintStats();
		}
		else if (input == 27) {//esc
			if (!player.inTown) {
				dungeon.ShowDungeon();
			}
			ShowTown();
		}

	}


}


void ShopWitchMenu() {
	system("cls");
	
	//to change contents in shop add item to array and add a case at the bottom
	Misc item[] = { p1, p2, p3 };
	DrawShop("WITCH'S SHOP");

	int cursorOffset = 0; 
	int selectedItem = 0; // Tracks which menu option is selected
	int size = sizeof(item) / sizeof(item[0]);

	//populate menu items
	MenuItem* menu = new MenuItem[size + 1];

	for (int i = 0; i < size; i++) {
		menu[i] = { 5, 6 + i, item[i].name };
	}
	
	menu[size] = { 50, 26, "[Exit]" };

	//populate descriptions and cost
	for (int i = 0; i < size; i++) {
		SetCursorPosition(31, 6 + i);
		std::cout << " - " << item[i].desc;
		SetCursorPosition(49, 6 + i);
		std::cout << "| " << item[i].cost << " Gold";
	}

	// Menu loop
	while (true) {

		for (int i = 0; i <= size; i++) {

			cursorOffset = (i != size) ? 3 : 0;
			SetCursorPosition(menu[i].x - cursorOffset, menu[i].y);

			// Highlight the selected item
			std::cout << (i == selectedItem ? ">" : " ");

			// Only print the number if it's NOT the last item [Exit]
			if (i != size) {
				std::cout << i + 1 << ") ";
			}

			// Print the menu item text
			std::cout << menu[i].text;
		}

		//get input
		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			Beep(1000, 100);

			switch (input) {
			case 72: if (selectedItem != 0) { selectedItem -= 1; } break;
			case 80: if (selectedItem != size) { selectedItem += 1; } break;
			}

		}
		else if (input == '\r') { // Enter key

			Beep(1500, 200);
			switch (selectedItem) {
			case 0: BuyItem(&p1); break;
			case 1: BuyItem(&p2); break;
			case 2: BuyItem(&p3); break;
			case 3: delete[] menu; ShowTown(); break;
			}

		}

	}
}
void ShopPriestMenu() {
	system("cls");

	//to change contents in shop add item to array and add a case at the bottom
	Misc item[] = { m1, r1, r2, r3, r4, r5, r6 };
	DrawShop("PRIEST'S SHOP");

	int cursorOffset = 0;
	int selectedItem = 0; // Tracks which menu option is selected
	int size = sizeof(item) / sizeof(item[0]);


	//populate menu items
	MenuItem* menu = new MenuItem[size + 1];

	for (int i = 0; i < size; i++) {
		menu[i] = { 5, 6 + i, item[i].name };
	}

	menu[size] = { 50, 26, "[Exit]" };

	//populate descriptions and cost
	for (int i = 0; i < size; i++) {
		SetCursorPosition(31, 6 + i);
		std::cout << " - " << item[i].desc;
		SetCursorPosition(49, 6 + i);
		std::cout << "| " << item[i].cost << " Gold";
	}

	// Menu loop
	while (true) {

		for (int i = 0; i <= size; i++) {

			cursorOffset = (i != size) ? 3 : 0;
			SetCursorPosition(menu[i].x - cursorOffset, menu[i].y);

			// Highlight the selected item
			std::cout << (i == selectedItem ? ">" : " ");

			// Only print the number if it's NOT the last item [Exit]
			if (i != size) {
				std::cout << i + 1 << ") ";
			}

			// Print the menu item text
			std::cout << menu[i].text;
		}

		//get input
		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			Beep(1000, 100);

			switch (input) {
			case 72: if (selectedItem != 0) { selectedItem -= 1; } break;
			case 80: if (selectedItem != size) { selectedItem += 1; } break;
			}

		}
		else if (input == '\r') { // Enter key

			Beep(1500, 200);
			switch (selectedItem) {
			case 0: BuyItem(&m1); break;
			case 1: BuyItem(&r1); break;
			case 2: BuyItem(&r2); break;
			case 3: BuyItem(&r3); break;
			case 4: BuyItem(&r4); break;
			case 5: BuyItem(&r5); break;
			case 6: BuyItem(&r6); break;
			case 7: delete[] menu; ShowTown(); break;
			}

		}

	}

} 


void ShopBlacksmithMenu() {
	system("cls");

	DrawShop("BLACKSMITH'S SHOP");

	int cursorOffset = 0;
	int selectedItem = 0; // Tracks which menu option is selected
	int size = 3;


	//populate menu items
	MenuItem* menu = new MenuItem[size + 1];

	menu[0] = { 5,6,"WEAPONS" };
	menu[1] = { 5,7,"ARMOR" };
	menu[2] = { 5,8,"SHIELDS" };
	menu[3] = { 50, 26, "[Exit]" };

	// Menu loop
	while (true) {

		for (int i = 0; i <= size; i++) {

			cursorOffset = (i != size) ? 3 : 0;
			SetCursorPosition(menu[i].x - cursorOffset, menu[i].y);

			// Highlight the selected item
			std::cout << (i == selectedItem ? ">" : " ");

			// Only print the number if it's NOT the last item [Exit]
			if (i != size) {
				std::cout << i + 1 << ") ";
			}

			// Print the menu item text
			std::cout << menu[i].text;
		}

		//get input
		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			Beep(1000, 100);

			switch (input) {
			case 72: if (selectedItem != 0) { selectedItem -= 1; } break;
			case 80: if (selectedItem != size) { selectedItem += 1; } break;
			}

		}
		else if (input == '\r') { // Enter key

			Beep(1500, 200);
			switch (selectedItem) {
			case 0: ShopWeaponsMenu(); break;
			case 1: ShopArmorMenu(); break;
			case 2: ShopShieldsMenu(); break;
			case 3: delete[] menu; ShowTown(); break;
			}

		}

	}

}

void ShopWeaponsMenu() {
	system("cls");

	//to change contents in shop add item to array and add a case at the bottom
	Weapon item[] = { w1, w2, w3, w4, w5};
	DrawShop("WEAPONS");

	int cursorOffset = 0;
	int selectedItem = 0; // Tracks which menu option is selected
	int size = sizeof(item) / sizeof(item[0]);


	//populate menu items
	MenuItem* menu = new MenuItem[size + 1];

	for (int i = 0; i < size; i++) {
		menu[i] = { 5, 6 + i, item[i].name };
	}

	menu[size] = { 50, 26, "[Exit]" };

	//populate descriptions and cost
	for (int i = 0; i < size; i++) {
		SetCursorPosition(31, 6 + i);
		std::cout << " - " << item[i].desc;
		SetCursorPosition(49, 6 + i);
		std::cout << "| " << item[i].cost << " Gold";
	}

	// Menu loop
	while (true) {

		for (int i = 0; i <= size; i++) {

			cursorOffset = (i != size) ? 3 : 0;
			SetCursorPosition(menu[i].x - cursorOffset, menu[i].y);

			// Highlight the selected item
			std::cout << (i == selectedItem ? ">" : " ");

			// Only print the number if it's NOT the last item [Exit]
			if (i != size) {
				std::cout << i + 1 << ") ";
			}

			// Print the menu item text
			std::cout << menu[i].text;
		}

		//get input
		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			Beep(1000, 100);

			switch (input) {
			case 72: if (selectedItem != 0) { selectedItem -= 1; } break;
			case 80: if (selectedItem != size) { selectedItem += 1; } break;
			}

		}
		else if (input == '\r') { // Enter key

			Beep(1500, 200);
			switch (selectedItem) {
			case 0: BuyItem(&w1); break;
			case 1: BuyItem(&w2); break;
			case 2: BuyItem(&w3); break;
			case 3: BuyItem(&w4); break;
			case 4: BuyItem(&w5); break;
			case 5: delete[] menu; ShopBlacksmithMenu(); break;
			}

		}

	}
}
void ShopArmorMenu() {
	system("cls");

	//to change contents in shop add item to array and add a case at the bottom
	Armor item[] = { a1, a2, a3, a4, a5 };
	DrawShop("ARMOR");

	int cursorOffset = 0;
	int selectedItem = 0; // Tracks which menu option is selected
	int size = sizeof(item) / sizeof(item[0]);


	//populate menu items
	MenuItem* menu = new MenuItem[size + 1];

	for (int i = 0; i < size; i++) {
		menu[i] = { 5, 6 + i, item[i].name };
	}

	menu[size] = { 50, 26, "[Exit]" };

	//populate descriptions and cost
	for (int i = 0; i < size; i++) {
		SetCursorPosition(31, 6 + i);
		std::cout << " - " << item[i].desc;
		SetCursorPosition(49, 6 + i);
		std::cout << "| " << item[i].cost << " Gold";
	}

	// Menu loop
	while (true) {

		for (int i = 0; i <= size; i++) {

			cursorOffset = (i != size) ? 3 : 0;
			SetCursorPosition(menu[i].x - cursorOffset, menu[i].y);

			// Highlight the selected item
			std::cout << (i == selectedItem ? ">" : " ");

			// Only print the number if it's NOT the last item [Exit]
			if (i != size) {
				std::cout << i + 1 << ") ";
			}

			// Print the menu item text
			std::cout << menu[i].text;
		}

		//get input
		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			Beep(1000, 100);

			switch (input) {
			case 72: if (selectedItem != 0) { selectedItem -= 1; } break;
			case 80: if (selectedItem != size) { selectedItem += 1; } break;
			}

		}
		else if (input == '\r') { // Enter key

			Beep(1500, 200);
			switch (selectedItem) {
			case 0: BuyItem(&a1); break;
			case 1: BuyItem(&a2); break;
			case 2: BuyItem(&a3); break;
			case 3: BuyItem(&a4); break;
			case 4: BuyItem(&a5); break;
			case 5: delete[] menu; ShopBlacksmithMenu(); break;
			}

		}

	}

}
void ShopShieldsMenu() {
	system("cls");

	//to change contents in shop add item to array and add a case at the bottom
	Shield item[] = { s1, s2, s3, s4, s5 };
	DrawShop("SHIELDS");

	int cursorOffset = 0;
	int selectedItem = 0; // Tracks which menu option is selected
	int size = sizeof(item) / sizeof(item[0]);


	//populate menu items
	MenuItem* menu = new MenuItem[size + 1];

	for (int i = 0; i < size; i++) {
		menu[i] = { 5, 6 + i, item[i].name };
	}

	menu[size] = { 50, 26, "[Exit]" };

	//populate descriptions and cost
	for (int i = 0; i < size; i++) {
		SetCursorPosition(31, 6 + i);
		std::cout << " - " << item[i].desc;
		SetCursorPosition(49, 6 + i);
		std::cout << "| " << item[i].cost << " Gold";
	}

	// Menu loop
	while (true) {

		for (int i = 0; i <= size; i++) {

			cursorOffset = (i != size) ? 3 : 0;
			SetCursorPosition(menu[i].x - cursorOffset, menu[i].y);

			// Highlight the selected item
			std::cout << (i == selectedItem ? ">" : " ");

			// Only print the number if it's NOT the last item [Exit]
			if (i != size) {
				std::cout << i + 1 << ") ";
			}

			// Print the menu item text
			std::cout << menu[i].text;
		}

		//get input
		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			Beep(1000, 100);

			switch (input) {
			case 72: if (selectedItem != 0) { selectedItem -= 1; } break;
			case 80: if (selectedItem != size) { selectedItem += 1; } break;
			}

		}
		else if (input == '\r') { // Enter key

			Beep(1500, 200);
			switch (selectedItem) {
			case 0: BuyItem(&s1); break;
			case 1: BuyItem(&s2); break;
			case 2: BuyItem(&s3); break;
			case 3: BuyItem(&s4); break;
			case 4: BuyItem(&s5); break;
			case 5: delete[] menu; ShopBlacksmithMenu(); break;
			}

		}

	}
}


void BuyItem(const Item* item) {
	if (player.gold < item->cost) {
		SetCursorPosition(2, 26);
		SlowPrint("Not enough Gold");

		return;
	}

	player.gold -= item->cost;
	

	// Check the type of the item and add it to the correct inventory
	if (const Misc* miscItem = dynamic_cast<const Misc*>(item)) {
		player.miscInventory.push_back(*miscItem);
	}
	else if (const Armor* armorItem = dynamic_cast<const Armor*>(item)) {
		player.armorInventory.push_back(*armorItem);
	}
	else if (const Shield* shieldItem = dynamic_cast<const Shield*>(item)) {
		player.shieldInventory.push_back(*shieldItem);
	}
	else if (const Weapon* weaponItem = dynamic_cast<const Weapon*>(item)) {
		player.weaponInventory.push_back(*weaponItem);
	}

	SetCursorPosition(2, 26); //info
	SlowPrint(item->name, " added to Inventory...");

	player.PrintStats();

	SetCursorPosition(2, 26); //clear line
	std::cout << "                                                  ";
}

void DrawShop(std::string name) {

	std::cout << "#############################################################" //0
		<< "\n#Player:                                                    #"     //1
		<< "\n#---------------------------NAME----------------------------#";		//2

	for (int i = 0; i < 18; i++) {
		std::cout << "\n#                                                           #";
	}


	std::cout << "\n#-----------------------------------------------------------#"		//21
		<< "\n#---------------------------STATS---------------------------#"		//22
		<< "\n#  ATTACK:     | BLOCK:       | GOLD:        | HP:          #"		//23
		<< "\n# DEFENSE:     | LEVEL:       |  EXP:        |              #"		//24
		<< "\n#-----------------------------------------------------------#"		//25
		<< "\n#                                                  [Exit]   #"		//26
		<< "\n#############################################################";	//27

	int offset = name.length() / 2;
	int startX = 31 - offset;

	SetCursorPosition(startX, 2);
	std::cout << name;

	player.PrintStats();
}
