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
#include <vector>
#include <limits>
#include <fstream>
#include <filesystem>


struct Room {
    int x, y, width, height;
};

struct Position {
    int x, y;
};

static const int WIDTH = 59;
static const int HEIGHT = 18;
static const char WALL = '@';
static const char FLOOR = ' ';
static const char STAIRCASE_DOWN = 'V';
static const char STAIRCASE_UP = 'A';

static const char* witchSprite = " ______\n/|||||\\\n|WITCH|";
static const char* blacksmithSprite = "  _______[]\n /______/  \\\n|_____|_""_|\n|BLACKSM||H|";
static const char* innSprite = "      []_____\n     /\  INN \\\n ___/  \__/\__\__\n/\___\ |''''''|__\\\n||'''| |''||''|''|";
static const char* priestSprite = "         +\n  _______|\n /////////\\\n|||||||||_""_|\n|PRIEST| || |";
static const char* dungeonEntranceSprite = " Dungeon Entrance \n[     |####|     ]\n[_____|####|_____]";

extern int currentLevel;

extern class Dungeon {
private:

  
    int enemyCount;
    std::vector<Position>enemyPositionsVector;
    Position dungeonEntrance;
    Position dungeonExit;

    void ConnectRooms(int pos1_X, int pos1_Y, int pos2_X, int pos2_Y);
    void SetInitialEnemyPosition();
public:

    float enemyAggretion;
    
    char dungeonMap[WIDTH][HEIGHT];

    Dungeon(int max_rooms, int num_of_enemies);

    void DungeonBattleIntro();

    void ShowDungeon();

    void SetInitialPlayerPosition(bool goingUp = false);

    
    void UpdateEnemyPositions();

};

inline void CollideEntranceTown();

inline void ShowTown();

inline bool CollideTown();

extern Dungeon dungeon;

 // 2D char array for the dungeon




