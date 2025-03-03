#include "battle.h"


void DrawBattleBackground(Enemy* e) {
	system("cls");


	//Print Menu Borders
	std::cout << "======================RuneBorn===============================" //0
		<< "\n=        .           ,      ,        lvl----------    @@@@@@="     //1
		<< "\n=     ,                                                @  @ ="		//2
		<< "\n=       ______                      .       .          @  @ ="		//3
		<< "\n=      /######\\           .                            @  @ ="     //4
		<< "\n=     |########|   .                                   @  @ ="		//5
		<< "\n=      \\######/        ,                        ,      @  @ ="		//6
		<< "\n=                                                      @  @ ="		//7
		<< "\n=                               .                     @@@@@@="		//8
		<< "\n=         .                                                 ="		//9
		<< "\n=                      ,                                    ="		//10
		<< "\n=  HP                                               .       ="		//11
		<< "\n= 25/40                                        .            ="		//12
		<< "\n=@@@@@@                            ,                        ="		//13
		<< "\n= @  @        .               ,                             ="		//14
		<< "\n= @  @                                        _________     ="		//15
		<< "\n= @  @   ,                          ,        /#########\\    ="		//16
		<< "\n= @  @         .              __ .          |###########|   ="		//17
		<< "\n= @  @                       /##\\            \\#########/    ="		//18
		<< "\n= @  @                       \\##/,   ,,                     ="		//19
		<< "\n=@@@@@@ ------------                                        ="		//20
		<< "\n#-----------------------------------------------------------#"		//21
		<< "\n#---------------------------MENU----------------------------#"		//22
		<< "\n#  ATTACK:                                                  #"		//23
		<< "\n#  INVENTORY:    RUN:                                       #"		//24
		<< "\n#-----------------------------------------------------------#"		//25
		<< "\n#                                                           #"		//26
		<< "\n#############################################################";	//27

	SetCursorPosition(34, 1);
	std::cout << "LVL: " << e->enemyLevel << " " << e->enemyName;

	PrintSpriteAt(29, 2, e->enemySprite);

	SetCursorPosition(2, 12);
	std::cout << player.health << "/" << player.maxHealth;

	PrintSpriteAt(8, 4, player.sprite);

	SetCursorPosition(8, 20);
	std::cout << "LVL: " << player.level << " " << player.name;

}

void Battle(short int enemy_ID, short int enemy_level, short int enemy_attack, short int enemy_Defense, short int enemy_health) {

	HideCursor();

	PlaySong("assets\\battle.wav");


	//create new enemy on heap
	Enemy* e1 = new Enemy(enemy_ID, enemy_level, enemy_attack, enemy_Defense, enemy_health);

	int selectedItem = 0; // Tracks which menu option is selected


	MenuItem menu[] = {
		{ 3, 23, "ATTACK"},
		{ 3, 24, "INVENTORY"},
		{ 17, 24, "RUN" }
	};

	DrawBattleBackground(e1);
	player.UpdateBattleHealthPlayer();
	e1->UpdateBattleHealthEnemy();

	int menuSize = sizeof(menu) / sizeof(menu[0]);

	bool battleEnd = false;

	while (battleEnd == false) {

		for (int i = 0; i < menuSize; i++) {
			SetCursorPosition(menu[i].x, menu[i].y);
			std::cout << (i == selectedItem ? ">" : " ") << menu[i].text;
		}

		SetCursorPosition(2, 26);
		std::cout << "What Will you Do?";

		int input = _getch();

		if (input == 224) { // Arrow keys
			input = _getch();

			Beep(1000, 100);

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

			Beep(1500, 200);

			SetCursorPosition(2, 26);
			std::cout << "                                          ";

			switch (selectedItem) {
			case 0:

				if (player.Attack(*e1)) { battleEnd = true; break; } //if player attack wins

				if (e1->Attack()) { battleEnd = true; break; } //if enemy attack wins

				break;

			case 1:
				player.ShowInventoryMenu();

				//redraw
				DrawBattleBackground(e1);
				player.UpdateBattleHealthPlayer();
				e1->UpdateBattleHealthEnemy();

				break;
			case 2:
				SetCursorPosition(2, 26);
				SlowPrint("Got away safely...");

				battleEnd = true;
				break;
			}

		}
	}

	//reset boosts
	player.atkBoost = 1;
	player.defBoost = 1;
	player.ctbBoost = 1;
	player.gldBoost = 1;
	player.hpBoost = 1;
	player.expBoost = 1;

	delete e1; //delete monster battle finish
	e1 = nullptr;

	return;
}