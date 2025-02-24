#include "enemy.h"

Enemy::Enemy(short int enemy_ID, short int enemy_Level, short int enemy_Attack, short int enemy_Defence, short int enemy_maxHealth) {
    enemyID = enemy_ID;
    enemyLevel = enemy_Level;
    enemySprite = "";

    //if stats are not provided, calculate them based on level
    enemyMaxHealth = (enemy_maxHealth == -1) ? (enemy_Level * 10 + new_rnd_num(5)) : enemy_maxHealth;
    enemyAttack = (enemy_Attack == -1) ? (enemy_Level * 2 + new_rnd_num(3)) : enemy_Attack;
    enemyDefence = (enemy_Defence == -1) ? (enemy_Level * 1 + new_rnd_num(2)) : enemy_Defence;

    //set current health
    enemyHealth = enemyMaxHealth;

    //get name from ID
    switch (enemyID) {
    case 0:
        enemyName = "Fallen";
        enemySprite =
            "        ,,,,,,,,        \n"
            "       (  o   o  )      \n"
            "      /    ∆    \\      \n"
            "     /  (     )  \\     \n"
            "       /  | |  \\       \n"
            "      /   | |   \\      \n"
            "     /    | |    \\     \n"
            "    /     | |     \\    ";
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

void Enemy::Defend(short int attack_damage) {
    short int dmg = attack_damage - new_rnd_num(enemyDefence);
    if (dmg < 0) { dmg = 0; } //cant have negative damage

    enemyHealth -= dmg;
    SetCursorPosition(2, 26);
    SlowPrint("You delt ", dmg, " Damage!");
}

bool Enemy::Attack(Character& player) {
    SetCursorPosition(2, 26);
    SlowPrint("The wild ", enemyName, " Attacked!");

    player.Defend(enemyAttack);

    if (player.playerHealth <= 0) { //if player health 0

        player.playerHealth = 0;

        SetCursorPosition(2, 26);
        SlowPrint(player.playerName, " Died...");

        int gld = player.playerGold / 2; //deduct gold
        player.playerGold -= gld;

        SetCursorPosition(2, 26);
        SlowPrint(player.playerName, " Lost ", gld, " Gold...");

        player.playerHealth = player.playerMaxHealth; //reset health

        return true;
    }
    return false;

}