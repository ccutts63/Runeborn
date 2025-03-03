#include "enemy.h"

Enemy::Enemy(short int enemy_ID, short int enemy_Level, short int enemy_Attack, short int enemy_Defense, short int enemy_maxHealth) {
    enemyID = enemy_ID;
    enemyLevel = enemy_Level;
    enemySprite = "";

    enemyLevel++;

    enemyAttack = (enemy_Attack == -1) ? (player.attack + new_rnd_num(10) - 5) : enemy_Attack;
    enemyDefense = (enemy_Defense == -1) ? (player.defense + new_rnd_num(10) - 5) : enemy_Defense;
    enemyMaxHealth = (enemy_maxHealth == -1) ? (player.maxHealth + new_rnd_num(10) - 5) : enemy_maxHealth;

    enemyHealth = enemyMaxHealth;

    //get name from ID
    switch (enemyID) {
    case 0:
        enemyName = "Pikachu";
        
        enemySprite =
            "`;-.          ___,\n"
            "  `.`\_...._/`.-''\n"
            "    \        /      ,\n"
            "    /()   () \    .' `-._\n"
            "   |)  .    ()\  /   _.'\n"
            "   \  -'-     ,; '. <\n"
            "    ;.__     ,;|   > \ \n"
            "   / ,    / ,  |.-'.-'\n"
            "  (_/    (_/ ,;|.<`\n"
            "    \    ,     ;-`\n"
            "     >   \    /\n"
            "    (_,-'`> .'\n"
            "         (_,'\n";
        break;

    case 1:
        enemyName = "Skeleton";
        enemySprite =
            "       ________        \n"
            "      |  O  O  |       \n"
            "      |   --   |       \n"
            "       \\ ---- /       \n"
            "        [ || ]        \n"
            "        [ || ]        \n"
            "        | || |        \n"
            "        | || |        ";
        break;

    case 2:
        enemyName = "Zombie";
        enemySprite =
            "       ( X   X )      \n"
            "      /    ∆    \\     \n"
            "     /  [     ]  \\    \n"
            "    /   /  |  \\   \\   \n"
            "        /  |  \\       \n"
            "       /   |   \\      \n"
            "      /    |    \\     \n"
            "     /     |     \\    ";
        break;

    case 3:
        enemyName = "Dark Mage";
        enemySprite =
            "        /------\\       \n"
            "       /        \\      \n"
            "      (  O  O   )      \n"
            "       |   --   |      \n"
            "      /|   ||   |\\     \n"
            "     / |   ||   | \\    \n"
            "       /   ||   \\      \n"
            "      /    ||    \\     ";
        break;

    case 4:
        enemyName = "Gargantuan Beast";
        enemySprite =
            "      /\\/\\/\\/\\/\\     \n"
            "     (   O    O  )    \n"
            "     /      ∆    \\    \n"
            "    /   [  |  ]   \\   \n"
            "   /    [  |  ]    \\  \n"
            "       /   |   \\      \n"
            "      /    |    \\     \n"
            "     /     |     \\    ";
        break;

    case 5:
        enemyName = "Sand Raider";
        enemySprite =
            "       ( O   O )      \n"
            "       /   ∆   \\      \n"
            "     <\\ | | | | />    \n"
            "      \\|  | |  |/     \n"
            "       |   |   |      \n"
            "      /    |    \\     \n"
            "     /     |     \\    \n"
            "    /      |      \\   ";
        break;

    case 6:
        enemyName = "Claw Viper";
        enemySprite =
            "      /\\/\\/\\/\\/\\     \n"
            "      (  O   O  )     \n"
            "       \\   ∆   /      \n"
            "        \\_____/       \n"
            "          ||||        \n"
            "          ||||        \n"
            "          ||||        \n"
            "          ||||        ";
        break;

    case 7:
        enemyName = "Demon Imp";
        enemySprite =
            "      ,,,,,,,,,,       \n"
            "     (  O   O  )       \n"
            "      \\   ∆   /       \n"
            "     < (  | |  ) >    \n"
            "       /  | |  \\      \n"
            "      /   | |   \\     \n"
            "     /    | |    \\    \n"
            "    /     | |     \\   ";
        break;

    case 8:
        enemyName = "Council Member";
        enemySprite =
            "      (\\      /)      \n"
            "      ( O    O )      \n"
            "      /    ∆    \\     \n"
            "     < (  | |  ) >    \n"
            "       /  | |  \\      \n"
            "      /   | |   \\     \n"
            "     /    | |    \\    \n"
            "    /     | |     \\   ";
        break;

    case 9:
        enemyName = "Blood Hawk";
        enemySprite =
            "      ^   ^   ^       \n"
            "      ( O   O )       \n"
            "      /   ∆   \\      \n"
            "     / |  | |  | \\   \n"
            "       |  | |  |      \n"
            "      /   | |   \\     \n"
            "     /    | |    \\    \n"
            "    /     | |     \\   ";
        break;

    default:
        enemyName = "Unknown";
        enemySprite =
            "      ( ??? )         \n"
            "      /  ?  \\        \n"
            "      |  ?  |        \n"
            "      |  ?  |        \n"
            "      |  ?  |        \n"
            "      |  ?  |        \n"
            "      |  ?  |        \n"
            "      |  ?  |        ";
        break;
    }

    SetCursorPosition(2, 26);
    SlowPrint("A Wild ", enemyName, " Appeared!");

}


bool Enemy::Attack() {
    SetCursorPosition(2, 26);
    SlowPrint("The wild ", enemyName, " attacked!");

    //check if the player successfully blocks the attack
    if (new_rnd_num(100) < player.block * player.ctbBoost) {
        SetCursorPosition(2, 26);
        SlowPrint("You blocked the attack!");
        return false; //no damage taken, continue battle
    }

    //damage calculation with variance
    short int baseDamage = enemyAttack - (player.defense * player.defBoost);
    short int variance = new_rnd_num(baseDamage / 4); //adds slight randomness (up to ±25%)
    short int dmg = baseDamage + variance;

    if (dmg <= 0) dmg = 1;

    player.health -= dmg;
    if (player.health < 0) player.health = 0;

    player.UpdateBattleHealthPlayer();

    SetCursorPosition(2, 26);
    SlowPrint("You took ", dmg, " damage!");

    //if player still alive, continue the battle
    if (player.health > 0) {
        return false;
    }

    //player fainted, handle defeat
    player.UpdateBattlePlayerFaint();

    SetCursorPosition(2, 26);
    SlowPrint(player.name, " has fallen...");

    //gold penalty
    int gld = (player.gold / 2) > 0 ? (player.gold / 2) : 1;
    player.gold -= gld;

    SetCursorPosition(2, 26);
    SlowPrint(player.name, " lost ", gld, " gold...");

    //respawn mechanics (reset health)
    player.health = player.maxHealth;

    return true;

}

void Enemy::UpdateBattleHealthEnemy() {
    if (enemyHealth == enemyMaxHealth) {
        PrintSpriteAt(56, 2, "\033[41m++\n++\n++\n++\n++\n++\033[0m");
        return;
    }
    else if (enemyHealth == 0) {
        PrintSpriteAt(56, 2, "  \n  \n  \n  \n  \n  ");
        return;
    }


    //enemy health bar
    float x = enemyMaxHealth / 6.0f;
    int y = enemyHealth / x;

    switch (y) {
    case 0:
        PrintSpriteAt(56, 2, "  \n  \n  \n  \n  \n\033[41m++\033[0m");
        break;
    case 1:
        PrintSpriteAt(56, 2, "  \n  \n  \n  \n\033[41m++\n++\033[0m");
        break;
    case 2:
        PrintSpriteAt(56, 2, "  \n  \n  \n\033[41m++\n++\n++\033[0m");
        break;
    case 3:
        PrintSpriteAt(56, 2, "  \n  \n\033[41m++\n++\n++\n++\033[0m");
        break;
    case 4:
        PrintSpriteAt(56, 2, "  \n\033[41m++\n++\n++\n++\n++\033[0m");
        break;
    case 5:
        PrintSpriteAt(56, 2, "  \n\033[41m++\n++\n++\n++\n++\033[0m");
        break;
    }
}

void Enemy::UpdateBattleEnemyFaint() {
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
        PrintSpriteAt(30, 2, frame);
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

}