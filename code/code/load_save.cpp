#pragma once
#include "load_save.h"

Character player("", characterType::WARRIOR); //create global player object

void TitleScreen() {

	HideCursor(); // Hide cursor

	system("cls");
	int selectedItem = 0; // Tracks which menu option is selected

	MenuItem menu[] = {
		{ 1, 17, "New Game"},
		{ 1, 18, "Load Game"},
		{ 1, 19, "Exit"}
	};

	int menuSize = sizeof(menu) / sizeof(menu[0]);

	std::cout << " (                 )         \n"
		<< " )\\ )           ( /(         \n"
		<< "(()/(      (    )\\())  (     \n"
		<< " /(_))     )\\  ((_)\   )\\    \n"
		<< "(_))    _ ((_)  _((_) ((_)   \n"
		<< "| _ \\  | | | | | \\| | | __|  \n"
		<< "|   /  | |_| | | .` | | _|   \n"
		<< "|_|_\\   \\__)/  |(|\\_| |___)  \n"
		<< "   (    ( /(    )\\ )   ( /(  \n"
		<< " ( )\\   )\\())  (()/(   )\\()) \n"
		<< " )((_) ((_)\    /(_)) ((_)\  \n"
		<< "((_)?    ((_))  (_))    _((_) \n"
		<< " | _ )  / _ \\  | _ \\  | \\| | \n"
		<< " | _ \\ | (_) | |   /  | .` | \n"
		<< " |___/  \\___/  |_|_\\  |_|\_|  \n";
	std::cout << "\nBy: Christian Cutts :0\n";

	PlaySong("assets\\title.wav");

	// Menu loop
	while (true) {
		for (int i = 0; i < menuSize; i++) {
			SetCursorPosition(menu[i].x, menu[i].y);
			std::cout << (i == selectedItem ? ">" : " ) ") << menu[i].text << "   ";
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

			SetCursorPosition(0, menu[menuSize - 1].y + 2); // Move cursor below menu

			switch (selectedItem) {
			case 0: NewCharacter(); break;
			case 1: LoadGame(); break;;
			case 2: std::cout << "Quitting...\n"; exit(0);
			}
		}
	}
}


void NewCharacter() {
	std::string name = "";
	characterType Class;

	system("cls");
	int selectedItem = 0; // Tracks which menu option is selected

	MenuItem menu[] = {
		{ 0, 2, "WARRIOR"},
		{ 0, 3, "ROUGE"},
		{ 0, 4, "MAGE"},
		{ 0, 6, "BACK" }
	};

	int menuSize = sizeof(menu) / sizeof(menu[0]);

	//Menu Title
	std::cout << "\n___Character Select___\n";

	// Menu loop
	while (true) {

		for (int i = 0; i < menuSize; i++) {
			SetCursorPosition(menu[i].x, menu[i].y);
			std::cout << (i == selectedItem ? ">" : " ) ") << menu[i].text << "   ";
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

			SetCursorPosition(0, menu[menuSize - 1].y + 2); // Move cursor below menu

			switch (selectedItem) {
			case 0: Class = characterType::WARRIOR; break;
			case 1: Class = characterType::ROUGE; break;
			case 2: Class = characterType::MAGE; break;
			case 3: return; break;
			}

			std::cout << "Enter your name: ";

			std::cin.ignore();
			std::getline(std::cin, name);

			if (name.empty())
			{

				switch (new_rnd_num(9)) {
				case 0: name = "Aeloris"; break;
				case 1: name = "Draven"; break;
				case 2: name = "Kael"; break;
				case 3: name = "Lyricus"; break;
				case 4: name = "Vaelin"; break;
				case 5: name = "Eldric"; break;
				case 6: name = "Runar"; break;
				case 7: name = "Taron"; break;
				case 8: name = "Sylwen"; break;
				case 9: name = "Orrin"; break;
				default: name = "Unknown_Hero"; break;

				}

			}
			Beep(1500, 200);

			Character* plr = new Character(name, Class);

			player = *plr;

			delete plr;

			player.position.x = 20;
			player.position.y = 20;
			ShowTown();

		}
	}

}

void LoadGame() {
	std::string filename = "";

	system("cls");

	std::cout << "----------------My Characters-----------------\n";

	system("ls './' -d *.SAV"); //must have linux subsystem installed

	std::cout << "----------------------------------------------\n";
	std::cout << "\nName of The File to Load: ";
	std::getline(std::cin, filename);

	Beep(1500, 200);

	std::ifstream inFile(filename);

	if (inFile.is_open()) {
		std::string line;

		// Read player stats
		std::string name;
		int cls;

		std::getline(inFile, name);
		inFile >> cls;

		characterType Class;
		switch (cls) {
		case 0: Class = characterType::WARRIOR; break;
		case 1: Class = characterType::ROUGE; break;
		case 2: Class = characterType::MAGE; break;
		}

		player = Character(name, Class); //sets sprite
		std::cout << name << '\n' << cls;

		inFile >> player.health >> player.maxHealth
			>> player.attack >> player.defense
			>> player.experience >> player.maxExperience
			>> player.gold >> player.level;

		std::cout << player.health << '\n' << player.maxHealth << '\n'
			<< player.attack << '\n' << player.defense << '\n'
			<< player.experience << '\n' << player.maxExperience << '\n'
			<< player.gold << '\n' << player.level << '\n';




		int id = 0,
			cost = 0,
			sell = 0,
			atk = 0,
			def = 0,
			ctb = 0;

		// Load equipped items
		//weapon
		inFile >> id >> cost >> sell >> atk;
		Weapon* w1 = new Weapon(id, cost, sell, atk);

		player.equippedWeapon = *w1;

		std::cout << id << '\n' << cost << '\n' << sell << '\n' << atk << '\n';

		delete w1;

		//Armor
		inFile >> id >> cost >> sell >> def;
		Armor* a1 = new Armor(id, cost, sell, def);

		player.equippedArmor = *a1;

		std::cout << id << '\n' << cost << '\n' << sell << '\n' << def << '\n';

		delete a1;

		//shield
		inFile >> id >> cost >> sell >> ctb;
		Shield* s1 = new Shield(id, cost, sell, ctb);

		player.equippedShield = *s1;

		std::cout << id << '\n' << cost << '\n' << sell << '\n' << ctb << '\n';

		delete s1;


		// Load inventory data for miscs
		short int count;

		inFile >> count;

		for (int i = 0; i < count; ++i) {
			inFile >> id;
			player.miscInventory.push_back(Misc(id));
		}

		// Load inventory data for Weapons
		inFile >> count;

		for (int i = 0; i < count; ++i) {
			inFile >> id >> cost >> sell >> atk;
			player.weaponInventory.push_back(Weapon(id, cost, sell, atk));
		}



		// Load inventory data for Armors
		inFile >> count;

		for (int i = 0; i < count; ++i) {
			inFile >> id >> cost >> sell >> def;
			player.armorInventory.push_back(Armor(id, cost, sell, def));
		}

		// Load inventory data for Shields
		inFile >> count;

		for (int i = 0; i < count; ++i) {
			inFile >> id >> cost >> sell >> ctb;
			player.shieldInventory.push_back(Shield(id, cost, sell, ctb));
		}

		inFile.close();

		Beep(1500, 200);
		dungeon.SetInitialPlayerPosition();
		dungeon.ShowDungeon();
	}
	else {
		SlowPrint("Error loading character data!");
		return;
	}
}

void SaveGame() {
	std::string filename = player.name + ".SAV";
	int Class;
	switch (player.type) {
	case characterType::WARRIOR: Class = 0; break;
	case characterType::ROUGE: Class = 1; break;
	case characterType::MAGE: Class = 2; break;
	}

	std::ofstream outFile(filename);
	if (outFile.is_open()) {
		// Save player stats
		outFile << player.name << "\n"
			<< Class << "\n"
			<< player.health << "\n"
			<< player.maxHealth << "\n"
			<< player.attack << "\n"
			<< player.defense << "\n"
			<< player.experience << "\n"
			<< player.maxExperience << "\n"
			<< player.gold << "\n"
			<< player.level << "\n"
			<< player.equippedWeapon.id << '\n'
			<< player.equippedWeapon.cost << "\n"
			<< player.equippedWeapon.sellPrice << "\n"
			<< player.equippedWeapon.attack << "\n"
			<< player.equippedArmor.id << "\n"
			<< player.equippedArmor.cost << "\n"
			<< player.equippedArmor.sellPrice << "\n"
			<< player.equippedArmor.defense << "\n"
			<< player.equippedShield.id << "\n"
			<< player.equippedShield.cost << "\n"
			<< player.equippedShield.sellPrice << '\n'
			<< player.equippedShield.blockChance << "\n";


		// Save inventory data for miscs
		outFile << player.miscInventory.size() << "\n";  // Save number of miscs
		for (const auto& misc : player.miscInventory) {
			//save each misc id
			outFile << misc.id << "\n";
		}

		// Save inventory data for Weapons
		outFile << player.weaponInventory.size() << "\n";  // Save number of weapons
		for (const auto& weapon : player.weaponInventory) {
			// Save weapon properties
			outFile << weapon.id << "\n"
				<< weapon.cost << "\n"
				<< weapon.sellPrice << "\n"
				<< weapon.attack << "\n";
		}

		// Save inventory data for Armors
		outFile << player.armorInventory.size() << "\n";  // Save number of armors
		for (const auto& Armor : player.armorInventory) {
			// Save armor properties
			outFile << Armor.id << "\n"
				<< Armor.cost << "\n"
				<< Armor.sellPrice << "\n"
				<< Armor.defense << "\n";
		}

		// Save inventory data for Shields
		outFile << player.shieldInventory.size() << "\n";  // Save number of shields
		for (const auto& shield : player.shieldInventory) {
			// Save shield properties
			outFile << shield.id << "\n"
				<< shield.cost << "\n"
				<< shield.sellPrice << "\n"
				<< shield.blockChance << "\n";
		}

		outFile.close();
		SetCursorPosition(2, 26);
		SlowPrint("Saved.");
		return;
	}
	else {
		SlowPrint("Error..");
		PlayerMenu();
	}

}