#include "dungeon.h"

Dungeon dungeon(10, 5);

std::vector<Dungeon>levelMaps;

int currentLevel = 0;

Dungeon::Dungeon(int num_of_rooms, int num_of_enemies) {
	srand(time(NULL));
	
	std::vector<Room>rooms;
	rooms.reserve(num_of_rooms);

	enemyCount = num_of_enemies;

	// Fill dungeon with walls
	for (int y = 0; y < HEIGHT; y++)
		for (int x = 0; x < WIDTH; x++)
			dungeonMap[x][y] = WALL;

	for (int i = 0; i < num_of_rooms; i++) {
		Room r;
		r.width = new_rnd_num(4, 8);  // Room width: 4-8
		r.height = new_rnd_num(4, 8); // Room height: 3-6
		r.x = new_rnd_num(1, WIDTH - (r.width + 1));
		r.y = new_rnd_num(1, HEIGHT - (r.height + 1));

		rooms.push_back(r); // Store the new room

		// Carve out the room
		for (int y = r.y; y < r.y + r.height; y++) {
			for (int x = r.x; x < r.x + r.width; x++) {
				dungeonMap[x][y] = FLOOR;
			}

		}

	}
	
	int r1centerX;
	int r2centerX;
	int r1centerY;
	int r2centerY;

	//connect rooms

	for (int i = 1; i < num_of_rooms; i++) {
		Room& r1 = rooms[i - 1];
		Room& r2 = rooms[i];

		r1centerX = r1.x + (r1.width / 2);
		r1centerY = r1.y + (r1.height / 2);

		r2centerX = r2.x + (r2.width / 2);
		r2centerY = r2.y + (r2.height / 2);

		ConnectRooms(r1centerX, r1centerY, r2centerX, r2centerY);
	}

	

	//set starcase position
	int x;
	int y;

	while (true) { //make sure we have around under for player
		x = new_rnd_num(WIDTH - 5);
		y = new_rnd_num(HEIGHT - 5);

		if (dungeonMap[x][y] == FLOOR && dungeonMap[x][y + 1] == FLOOR && dungeonMap[x][y - 1] == FLOOR && 
			dungeonMap[x + 1][y] == FLOOR && dungeonMap[x - 1][y] == FLOOR && dungeonMap[x + 1][y + 1] == FLOOR &&
			dungeonMap[x + 1][y - 1] == FLOOR && dungeonMap[x - 1][y + 1] == FLOOR && dungeonMap[x - 1][y - 1] == FLOOR) { //check if empty space
			
			dungeonMap[x][y] = STAIRCASE_UP;
			dungeonEntrance.x = x + 1;
			dungeonEntrance.y = y + 3;

			break;
		}

	}

	while (true) {
		x = new_rnd_num(WIDTH - 5);
		y = new_rnd_num(HEIGHT - 5);

		if (dungeonMap[x][y] == FLOOR && dungeonMap[x][y + 1] == FLOOR && dungeonMap[x][y - 1] == FLOOR &&
			dungeonMap[x + 1][y] == FLOOR && dungeonMap[x - 1][y] == FLOOR && dungeonMap[x + 1][y + 1] == FLOOR &&
			dungeonMap[x + 1][y - 1] == FLOOR && dungeonMap[x - 1][y + 1] == FLOOR && dungeonMap[x - 1][y - 1] == FLOOR) { //check if empty space
			
			dungeonMap[x][y] = STAIRCASE_DOWN;
			dungeonExit.x = x + 1;
			dungeonExit.y = y + 3;
			break;

		}

	}

	//connect staircases to ensure player wont get stuck
	ConnectRooms(dungeonEntrance.x, dungeonEntrance.y, dungeonExit.x, dungeonExit.y);




	SetInitialEnemyPosition();
		
	
}

void Dungeon::SetInitialEnemyPosition() {
	int x;
	int y;

	enemyPositionsVector.clear();

	int enemyNum = 0;

	while (enemyNum < enemyCount) {
		x = new_rnd_num(WIDTH);
		y = new_rnd_num(HEIGHT - 1);

		if (dungeonMap[x][y] == FLOOR) { //check if empty space
			Position e;
			e.x = x + 1;
			e.y = y + 3;

			enemyPositionsVector.push_back(e);

			enemyNum++;
		}
	}
	return;
}

void Dungeon::ConnectRooms(int r1centerX, int r1centerY, int r2centerX, int r2centerY) {

		//draw
		if (r2centerY < r1centerY) {
			for (int y = r1centerY; y > r2centerY; y--) { //Y
				if (dungeonMap[r1centerX][y] == STAIRCASE_UP || dungeonMap[r1centerX][y] == STAIRCASE_DOWN || //make sure were not writing over staircase
					dungeonMap[r1centerX - 1][y] == STAIRCASE_UP || dungeonMap[r1centerX - 1][y] == STAIRCASE_DOWN) {
					continue;
				}
				dungeonMap[r1centerX][y] = FLOOR;
				if (r1centerX != 0) { //this is to widen the passages
					dungeonMap[r1centerX - 1][y] = FLOOR;
				}
			}
			if (r2centerX < r1centerX) {
				for (int x = r2centerX; x < r1centerX; x++) {//X
					if (dungeonMap[x][r2centerY] == STAIRCASE_UP || dungeonMap[x][r2centerY] == STAIRCASE_DOWN ||
						dungeonMap[x][r2centerY - 1] == STAIRCASE_UP || dungeonMap[x][r2centerY - 1] == STAIRCASE_DOWN) {
						continue;
					}
					dungeonMap[x][r2centerY] = FLOOR;
					if (r2centerY != 0) { //this is to widen the passages
						dungeonMap[x][r2centerY - 1] = FLOOR;
					}
				}
			}
			else if (r2centerX > r1centerX) {
				for (int x = r2centerX; x > r1centerX; x--) {//X
					if (dungeonMap[x][r2centerY] == STAIRCASE_UP || dungeonMap[x][r2centerY] == STAIRCASE_DOWN ||
						dungeonMap[x][r2centerY - 1] == STAIRCASE_UP || dungeonMap[x][r2centerY - 1] == STAIRCASE_DOWN) {
						continue;
					}
					dungeonMap[x][r2centerY] = FLOOR;
					if (r2centerY != 0) { //this is to widen the passages
						dungeonMap[x][r2centerY - 1] = FLOOR;
					}
				}
			}
		}
		else if (r2centerY > r1centerY) {
			for (int y = r1centerY; y < r2centerY; y++) {//Y
				if (dungeonMap[r1centerX][y] == STAIRCASE_UP || dungeonMap[r1centerX][y] == STAIRCASE_DOWN ||
					dungeonMap[r1centerX - 1][y] == STAIRCASE_UP || dungeonMap[r1centerX - 1][y] == STAIRCASE_DOWN) {
					continue;
				}
				dungeonMap[r1centerX][y] = FLOOR;
				if (r1centerX != 0) { //this is to widen the passages
					dungeonMap[r1centerX - 1][y] = FLOOR;
				}
			}
			if (r2centerX < r1centerX) {
				for (int x = r2centerX; x < r1centerX; x++) {//X
					if (dungeonMap[x][r2centerY] == STAIRCASE_UP || dungeonMap[x][r2centerY] == STAIRCASE_DOWN ||
						dungeonMap[x][r2centerY - 1] == STAIRCASE_UP || dungeonMap[x][r2centerY - 1] == STAIRCASE_DOWN) {
						continue;
					}
					dungeonMap[x][r2centerY] = FLOOR;
					if (r2centerY != 0) { //this is to widen the passages
						dungeonMap[x][r2centerY - 1] = FLOOR;
					}
				}
			}
			else if (r2centerX > r1centerX) {
				for (int x = r2centerX; x > r1centerX; x--) {//X
					if (dungeonMap[x][r2centerY] == STAIRCASE_UP || dungeonMap[x][r2centerY] == STAIRCASE_DOWN ||
						dungeonMap[x][r2centerY - 1] == STAIRCASE_UP || dungeonMap[x][r2centerY - 1] == STAIRCASE_DOWN) {
						continue;
					}
					dungeonMap[x][r2centerY] = FLOOR;
					if (r2centerY != 0) { //this is to widen the passages
						dungeonMap[x][r2centerY - 1] = FLOOR;
					}
				}
			}
		}
}


void Dungeon::SetInitialPlayerPosition(bool goingUp) {
	int x;
	int y;

	if (goingUp) {
		x = dungeonExit.x;
		y = dungeonExit.y + 1;

		player.position.x = x;
		player.position.y = y;
	}
	else {
		x = dungeonEntrance.x;
		y = dungeonEntrance.y + 1;

		player.position.x = x;
		player.position.y = y;
	}
	

	
}

void Dungeon::UpdateEnemyPositions() {
	enemyAggretion = (50.0f + currentLevel); //the lower in the dungeon you go the more aggressive the enemies get
	if (enemyAggretion > 100) { enemyAggretion = 100; } //make sure we dont go below 100% chase rate
	
	int newX;
	int newY;

	for (int i = 0; i < enemyCount; i++) {
		
		//makes it more likely for enemy to follow player
		if (player.position.x > enemyPositionsVector[i].x) {
			newX = enemyPositionsVector[i].x + -(BiasedRandom(2, enemyAggretion)) + 1; //-1 0 or 1, 1 being more likely
		}
		else {
			newX = enemyPositionsVector[i].x + BiasedRandom(2, enemyAggretion) - 1; //-1 0 or -1, -1 being more likely
		}

		if (player.position.y > enemyPositionsVector[i].y) {
			newY = enemyPositionsVector[i].y + -(BiasedRandom(2, enemyAggretion)) + 1; //-1 0 or 1, 1 being more likely
		}
		else {
			newY = enemyPositionsVector[i].y + BiasedRandom(2, enemyAggretion) - 1; //-1 0 or -1, -1 being more likely
		}
		

		if (newX > 1 && newX < WIDTH + 1 && newY > 2 && newY < HEIGHT + 3 && dungeonMap[newX - 1][newY - 3] == FLOOR) {
			//clear old position
			SetCursorPosition(enemyPositionsVector[i].x, enemyPositionsVector[i].y);
			std::cout << " ";

			//update position
			enemyPositionsVector[i].x = newX;
			enemyPositionsVector[i].y = newY;

			//print new location
			Sleep(10);
			SetCursorPosition(enemyPositionsVector[i].x, enemyPositionsVector[i].y);
			std::cout << "\033[31mE\033[0m";
		}



		
	}
}

void Dungeon::ShowDungeon() {
	system("cls");

	player.inTown = false;

	PlaySong("assets\\dungeon.wav");


	std::cout << "#############################################################" //0
		<< "\n#Player:                                                    #"     //1
		<< "\n#--------LEVEL:2-----------DUNGEON--------------------------#"//2
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
		<< "\n#                                          [esc for menu]   #"		//26
		<< "\n#############################################################";	//27


	player.PrintStats();


	//print dungeon
	for (int y = 0; y < HEIGHT; y++) {
		SetCursorPosition(1, y + 3);

		for (int x = 0; x < WIDTH; x++) {
			switch (dungeonMap[x][y]) {//color
			case 'A':
				std::cout << "\033[30;42mH\033[0m";//black on green
				break;
			case 'V':
				std::cout << "\033[37;41mH\033[0m";//white on red
				break;
			default:
				std::cout << dungeonMap[x][y];
				break;
			}
			
		}
	}

	//print player
	SetCursorPosition(player.position.x, player.position.y);
	std::cout << "\033[34m" << player.chr << "\033[0m";

	//print enemies
	for (int i = 0; i < enemyCount; i++) {
		SetCursorPosition(enemyPositionsVector[i].x, enemyPositionsVector[i].y);
		std::cout << "\033[31mE\033[0m";
	}

	//print dungeon level
	SetCursorPosition(15, 2);
	std::cout << currentLevel;

	// dungeon loop
	while (true) {

		for (int i = 0; i < enemyCount; i++) { //if player is touching enemy
			if (enemyPositionsVector[i].x == player.position.x && enemyPositionsVector[i].y == player.position.y) {

				DungeonBattleIntro();
				
				Battle(new_rnd_num(10), new_rnd_num(player.level));
				enemyPositionsVector.erase(enemyPositionsVector.begin() + i);
				enemyCount--;
				ShowDungeon();//reprint
			}
		}


		int input = _getch();

		if (input == 224) { // Arrow keys

			input = _getch();

			Beep(500, 5);
			Beep(500, 5);

			

			

			SetCursorPosition(player.position.x, player.position.y);//remove old player
			std::cout << " ";

			switch (input) {//check for collision
			case 72: // Up arrow
				if (player.position.y > 3 && dungeonMap[player.position.x - 1][player.position.y - 4] != WALL) {
					player.position.y -= 1;
				}
				break;
			case 75: // Left arrow
				if (player.position.x > 1 && dungeonMap[player.position.x - 2][player.position.y - 3] != WALL) {
					player.position.x -= 1;
				}
				break;
			case 80: // Down arrow
				if (player.position.y < HEIGHT + 2 && dungeonMap[player.position.x - 1][player.position.y - 2] != WALL) {
					player.position.y += 1;
				}
				break;
			case 77: // Right arrow
				if (player.position.x < WIDTH && dungeonMap[player.position.x][player.position.y - 3] != WALL) {
					player.position.x += 1;
				}
				break;
			}
			//check for stair collision
			if (dungeonMap[player.position.x - 1][player.position.y - 3] == STAIRCASE_UP) {//up

				if (currentLevel > 0) {// we are not at level 0

					currentLevel--;

					dungeon = levelMaps[currentLevel];

					SetInitialPlayerPosition(true);
					ShowDungeon();
				}
				else {
					player.position.x = 27; //set player to dungeon entrance
					player.position.y = 20;
					ShowTown();
				}

			}
			else if (dungeonMap[player.position.x - 1][player.position.y - 3] == STAIRCASE_DOWN) {//down

				if (levelMaps.size() == 0) {
					levelMaps.push_back(dungeon); //add first dungeon to array
				}

				if (currentLevel == levelMaps.size() - 1) { 

					Dungeon newDungeon(10, new_rnd_num(10));

					currentLevel++;

					dungeon = newDungeon; //set next dungeon
					levelMaps.push_back(dungeon); //add new dungeon to array

					SetInitialPlayerPosition();
					ShowDungeon();
				}
				if (currentLevel < levelMaps.size()) {

					currentLevel++;

					dungeon = levelMaps[currentLevel];


					SetInitialPlayerPosition();
					ShowDungeon();
				}
			}


		}
		else if (input == 27) { // esc key

			PlayerMenu();
				
			
		}

		SetCursorPosition(player.position.x, player.position.y); //print new player
		std::cout << "\033[34m" << player.chr << "\033[0m";

		UpdateEnemyPositions();



	}

	return;
}


void ShowTown() {
	system("cls");

	player.inTown = true;

	PlaySong("assets\\town.wav");


	std::cout << "#############################################################" //0
		<< "\n#Player:                                                    #"     //1
		<< "\n#---------------------------TOWN----------------------------#"     //2
		<< "\n#                                                           #"		//3
		<< "\n#                                                           #"		//4
		<< "\n#                                                           #"		//5
		<< "\n#                                                           #"		//6
		<< "\n#                                                           #"		//7
		<< "\n#                                                           #"		//8
		<< "\n#                                                           #"		//9
		<< "\n#                           (*)                             #"		//10
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
		<< "\n#                                          [esc for menu]   #"		//26
		<< "\n#############################################################";	//27


	player.PrintStats();

	//print Sprites
	PrintSpriteAt(9, 5, witchSprite);
	PrintSpriteAt(40, 4, blacksmithSprite);
	PrintSpriteAt(3, 10, innSprite);
	PrintSpriteAt(40, 10, priestSprite);
	PrintSpriteAt(20, 17, dungeonEntranceSprite);

	//print player
	SetCursorPosition(player.position.x, player.position.y);
	std::cout << "\033[34m" << player.chr << "\033[0m";

	while (true) {

		int input = _getch();

		if (input == 224) { // Arrow keys

			input = _getch();

			Beep(500, 5);
			Beep(500, 5);

			SetCursorPosition(player.position.x, player.position.y); //remove old player
			std::cout << " ";


			switch (input) {//check for collision
			case 72: // Up arrow
				player.position.y--;

				CollideEntranceTown(); //check if we collide with entrances

				if (!CollideTown()) { //check if we collide with entities
					break;
				}

				player.position.y++;

				break;

			case 75: // Left arrow
				player.position.x--;

				CollideEntranceTown();

				if (!CollideTown()) {
					break;
				}

				player.position.x++;

				break;
			case 80: // Down arrow
				player.position.y++;

				CollideEntranceTown();

				if (!CollideTown()) {
					break;
				}

				player.position.y--;

				break;
			case 77: // Right arrow
				player.position.x++;

				CollideEntranceTown();

				if (!CollideTown()) {
					break;
				}

				player.position.x--;

				break;
			}

			

			

		}
		else if (input == 27) { // esc key

			PlayerMenu();


		}

		SetCursorPosition(player.position.x, player.position.y); //print new player
		std::cout << "\033[34m" << player.chr << "\033[0m";

	}


}


void CollideEntranceTown() {
	//check for entrance collision
	if (player.position.y == 7 && player.position.x > 9 && player.position.x < 15) {//witch

		player.position.y++;
		ShopWitchMenu();

	}
	else if (player.position.y == 7 && player.position.x > 40 && player.position.x < 52) {//blacksmith

		player.position.y++;
		ShopBlacksmithMenu();

	}
	else if (player.position.y == 14 && player.position.x > 3 && player.position.x < 20) {//inn

		player.health = player.maxHealth;

		SetCursorPosition(2, 26);
		SlowPrint("Your HP was restored.");
		std::cout << "                                          ";

		player.position.y++;

	}
	else if (player.position.y == 14 && player.position.x > 40 && player.position.x < 52) {//priest

		player.position.y++;
		ShopPriestMenu();

	}
	else if (player.position.y == 19 && player.position.x > 26 && player.position.x < 31) {//dungeon

		dungeon.SetInitialPlayerPosition();
		dungeon.ShowDungeon();

	}
}

bool CollideTown() {
	if (player.position.x < 1 || player.position.x > WIDTH || player.position.y < 3 || player.position.y > HEIGHT + 2) {//outterwalls
		return true;
	}
	if (player.position.y == 10 && player.position.x > 27 && player.position.x < 31) {//fountain
		return true;
	}
	if (player.position.y > 4 && player.position.y < 8) {//witch
		if (player.position.x > 8 && player.position.x < 16) {
			return true;
		}
	}
	if (player.position.y > 3 && player.position.y < 8) {//blacksmith
		if (player.position.x > 39 && player.position.x < 53) {
			return true;
		}
	}
	if (player.position.y > 9 && player.position.y < 15) {//inn
		if (player.position.x > 2 && player.position.x < 21) {
			return true;
		}
	}
	if (player.position.y > 9 && player.position.y < 15) {//priest
		if (player.position.x > 39 && player.position.x < 53) {
			return true;
		}
	}
	if (player.position.y > 16 && player.position.y < 20) {//dungeon
		if (player.position.x > 19 && player.position.x < 38) {
			return true;
		}
	}
	return false;

}

void Dungeon::DungeonBattleIntro() {
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			SetCursorPosition(x + 1, y + 3);
			std::cout << "\033[7m" << dungeonMap[x][y] << "\033[0m";
		}
	}
	Sleep(10);
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			SetCursorPosition(x + 1, y + 3);
			std::cout << dungeonMap[x][y];
		}
	}
	Sleep(10);
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			SetCursorPosition(x + 1, y + 3);
			std::cout << "\033[7m" << dungeonMap[x][y] << "\033[0m";
		}
	}
	SetCursorPosition(player.position.x, player.position.y); //print new player
	std::cout << "\033[34m" << player.chr << "\033[0m";
}