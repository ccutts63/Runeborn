#pragma once
#include <string>

enum class ItemType { MISC, WEAPON, ARMOR, SHIELD };
enum class MiscType { POTION, PRAYER, RUNE };

class Item {
public:
    std::string name;
    std::string desc = "null";
    short int id;
    short int cost;
    short int sellPrice;

    //destructor
    virtual ~Item() = default;

    // Constructor
    /*virtual Item(std::string itemName, short int itemCost, short int itemSellPrice)
        : name(itemName), cost(itemCost), sellPrice(itemSellPrice) {
    }*/
};

class Misc : public Item {
public:
    MiscType type;
    short int health = 0;
    float atkBoost = 1;
    float defBoost = 1;
    float ctbBoost = 1;
    float hpBoost = 1;
    float gldBoost = 1;
    float expBoost = 1;



    //constructor
    Misc(short int miscID = 0) {
        id = miscID;


        switch (miscID) {
        case 0: 
            health = 50;
            type = MiscType::POTION;
            name = "Minor Healing potion";
            desc = "Heals +[" + std::to_string(health) + "] HP";
            cost = 50;
            sellPrice = 15;
            
            break;
        case 1: 
            health = 115;
            type = MiscType::POTION;
            name = "Light Healing potion";
            desc = "Heals +[" + std::to_string(health) + "] HP";
            cost = 100;
            sellPrice = 30;
            
            break;
        case 2: 
            health = 250;
            type = MiscType::POTION;
            name = "Healing potion"; 
            desc = "Heals +[" + std::to_string(health) + "] HP";
            cost = 150;
            sellPrice = 15;
            
            break;
        case 3: 
            health = 999;
            type = MiscType::POTION;
            name = "Full Healing potion";
            desc = "Heals +[" + std::to_string(health) + "] HP";
            cost = 500;
            sellPrice = 1;
            
            break;
        case 4:
            type = MiscType::PRAYER;
            name = "Prayer of Teleport";
            desc = "Brings you back to Town";
            cost = 50;
            sellPrice = 25;

            break;
        case 5:
            atkBoost = 2.5;
            type = MiscType::RUNE;
            name = "Rune of Garnet"; //boost attack
            desc = "Boosts Attack";
            cost = 65;
            sellPrice = 0;
            
            break;
        case 6:
            defBoost = 2.5;
            type = MiscType::RUNE;
            name = "Rune of Amethyst"; //boost defense
            desc = "Boosts Defense";
            cost = 65;
            sellPrice = 0;
            
            break;
        case 7:
            ctbBoost = 2.5;
            type = MiscType::RUNE;
            name = "Rune of Aquamarine"; //boost ctb
            desc = "Boosts Block";
            cost = 65;
            sellPrice = 0;
            
            break;
        case 8:
            hpBoost = 2.5;
            type = MiscType::RUNE;
            name = "Rune of Diamond"; //boost hp
            desc = "Boosts HP";
            cost = 65;
            sellPrice = 0;
            
            break;
        case 9:
            gldBoost = 2.5;
            type = MiscType::RUNE;
            name = "Rune of Emerald"; //boost gold
            desc = "Boosts Gold";
            cost = 65;
            sellPrice = 0;
            
            break;
        case 10:
            expBoost = 2.5;
            type = MiscType::RUNE;
            name = "Rune of Alexandrite"; //boost exp
            desc = "Boosts EXP";
            cost = 65;
            sellPrice = 0;

            break;
        }
        
    }


};

// Weapon Class - Dynamic Creation
class Weapon : public Item {
public:
    short int attack;

    // Constructor
    Weapon(short int weaponID = 0, short int weaponCost = 0, short int weaponSellPrice = 0, short int attackValue = 0) {
        id = weaponID;
        cost = weaponCost;
        sellPrice = weaponSellPrice;
        attack = attackValue;
        desc = "Attack +[" + std::to_string(attack) + "]";

        switch (weaponID) {
        case 0: name = ""; break; //for global initialization
        case 1: name = "Rusty Dagger"; break;
        case 2: name = "Iron Sword"; break;
        case 3: name = "Steel Longsword"; break;
        case 4: name = "Battle Axe"; break;
        case 5: name = "Warhammer"; break;
        case 6: name = "Greatsword"; break;
        case 7: name = "Elven Dagger"; break;
        case 8: name = "Silver Rapier"; break;
        case 9: name = "Obsidian Blade"; break;
        case 10: name = "Dragonfang Saber"; break;
        case 11: name = "Shadow Katana"; break;
        case 12: name = "Demonic Scythe"; break;
        case 13: name = "Paladin's Mace"; break;
        case 14: name = "Viking War Axe"; break;
        case 15: name = "Runed Shortsword"; break;
        case 16: name = "Thunder Hammer"; break;
        case 17: name = "Phoenix Claws"; break;
        case 18: name = "Venomous Dirk"; break;
        case 19: name = "ROUGE's Halberd"; break;
        case 20: name = "Flaming Claymore"; break;
        case 21: name = "Frozen Spear"; break;
        case 22: name = "Stormcaller’s Blade"; break;
        case 23: name = "Bloodied Cutlass"; break;
        case 24: name = "Spectral Shiv"; break;
        case 25: name = "Infernal Blade"; break;
        case 26: name = "Celestial War Staff"; break;
        case 27: name = "Titan's Maul"; break;
        case 28: name = "Necromancer's Fang"; break;
        case 29: name = "Warlord's Greataxe"; break;
        case 30: name = "Ancient Bone Spear"; break;
        case 31: name = "Golden Crescent Blade"; break;
        case 32: name = "Arcane Energy Saber"; break;
        default: name = "Unknown Weapon"; break;
        }

    }
};

// Armor Class - Dynamic Creation
class Armor : public Item {
public:
    short int defense;

    // Constructor
    Armor(short int ArmorID = 0, short int ArmorCost = 0, short int ArmorSellPrice = 0, short int defenseValue = 0) {
        id = ArmorID;
        cost = ArmorCost;
        sellPrice = ArmorSellPrice;
        defense = defenseValue;
        desc = "Defense +[" + std::to_string(defense) + "]";

        switch (ArmorID) {
        case 0: name = ""; break;
        case 1: name = "Rags"; break;
        case 2: name = "Studded Leather"; break;
        case 3: name = "Chainmail"; break;
        case 4: name = "Scale Mail"; break;
        case 5: name = "Splint Mail"; break;
        case 6: name = "Plate Mail"; break;
        case 7: name = "Full Plate"; break;
        case 8: name = "Dragon Scale"; break;
        case 9: name = "Iron Armor"; break;
        case 10: name = "Steel Armor"; break;
        case 11: name = "Silver Armor"; break;
        case 12: name = "Gold Armor"; break;
        case 13: name = "Dwarven Armor"; break;
        case 14: name = "Elven Robes"; break;
        case 15: name = "Shadow Cloak"; break;
        case 16: name = "Necromancer’s Shroud"; break;
        case 17: name = "Holy Vestments"; break;
        case 18: name = "Battle Robe"; break;
        case 19: name = "Warlord’s Plate"; break;
        case 20: name = "Assassin’s Garb"; break;
        case 21: name = "Berserker’s Armor"; break;
        case 22: name = "ROUGE’s Plate"; break;
        case 23: name = "Gladiator’s Armor"; break;
        case 24: name = "Phantom Cloak"; break;
        case 25: name = "Demonhide Armor"; break;
        case 26: name = "Crimson Mail"; break;
        case 27: name = "Frostguard Plate"; break;
        case 28: name = "Stormcaller’s Armor"; break;
        case 29: name = "Infernal Chestplate"; break;
        case 30: name = "Celestial Robes"; break;
        case 31: name = "Titan’s Battlegear"; break;
        case 32: name = "Ancient Relic Armor"; break;
        default: name = "Unknown Armor"; break;
        }

    }
};

// Shield Class - Dynamic Creation
class Shield : public Item {
public:
    short int blockChance;

    // Constructor
    Shield(short shieldID = 0, short int shieldCost = 0, short int sheildSellPrice = 0, short int chance_toBlock = 0) {
        id = shieldID;
        cost = shieldCost;
		sellPrice = sheildSellPrice;
		blockChance = chance_toBlock;
        desc = "Block +[" + std::to_string(blockChance) + "]";

        switch (shieldID) {
        case 0: name = ""; break;
        case 1: name = "Wooden Buckler"; break;
        case 2: name = "Round Shield"; break;
        case 3: name = "Kite Shield"; break;
        case 4: name = "Tower Shield"; break;
        case 5: name = "Pavise"; break;
        case 6: name = "Heater Shield"; break;
        case 7: name = "Scutum"; break;
        case 8: name = "Dragonhide Aegis"; break;
        case 9: name = "Iron Bulwark"; break;
        case 10: name = "Steel Defender"; break;
        case 11: name = "Silver Guard"; break;
        case 12: name = "Golden Aegis"; break;
        case 13: name = "Dwarven Wall"; break;
        case 14: name = "Elven Warden"; break;
        case 15: name = "Phantom Barrier"; break;
        case 16: name = "Necrotic Ward"; break;
        case 17: name = "Divine Bastion"; break;
        case 18: name = "Battleborn Shield"; break;
        case 19: name = "Warlord’s Rampart"; break;
        case 20: name = "Assassin’s Deflector"; break;
        case 21: name = "Berserker’s Guard"; break;
        case 22: name = "ROUGE’s Aegis"; break;
        case 23: name = "Gladiator’s Shield"; break;
        case 24: name = "Shadow Veil"; break;
        case 25: name = "Demonhide Ward"; break;
        case 26: name = "Crimson Barrier"; break;
        case 27: name = "Frostguard Shield"; break;
        case 28: name = "Stormcaller’s Ward"; break;
        case 29: name = "Infernal Bulwark"; break;
        case 30: name = "Celestial Guardian"; break;
        case 31: name = "Titan’s Shield"; break;
        case 32: name = "Ancient Relic Shield"; break;
        default: name = "Unknown Shield"; break;
        }

    }

};


