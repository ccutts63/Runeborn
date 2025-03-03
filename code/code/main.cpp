
//#include "character.h"
#include "menu.h"
#include "load_save.h"
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


using namespace std;


void TitleScreen();


//global

int main() {
	SetConsoleAppearance();

	SetConsoleSize(61, 28);

	SetConsoleTitle(TEXT("RuneBorn : A Text Based RPG"));

	MusicDialog(); //ask if we want music

	srand(time(NULL)); // Random seed


	TitleScreen();

	return 0;
}


