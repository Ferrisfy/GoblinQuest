#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct
{
    char name[50];
    int level;
    int experience;
    int health;
    int attack;
    int defense;
    int gold;
    int armor;
    int class;
    int abilityUsed;
    struct Weapon
    {
        char name[50];
        int price;
        int attackValue;
    } weapon;
} Player;

typedef struct
{
    char name[50];
    int health;
    int attack;
    int defense;
    int goldDrop;
} Enemy;

typedef struct
{
    char name[50];
    int price;
    int armorValue;
} Armor;

typedef struct
{
    char name[50];
    int price;
    int attackValue;
} Weapon;

typedef struct
{
    char name[50];
    int price;
    int healthValue;
} Potion;

typedef struct
{
    char name[50];
    char description[200];
    int specialAbility;
} Class;

typedef struct
{
    char name[50];
    char description[200];
    int specialAbility;
} SpecialAbility;

Class classes[] = {{"Warrior", "A strong and sturdy fighter.", 1},
                   {"Mage", "A powerful spellcaster with elemental magic.", 2},
                   {"Rogue", "A stealthy and agile dagger-wielding assassin.", 3}};

SpecialAbility abilities[] = {{"Berserk", "Does not have an ability, but has raw strength", 0},
                              {"Fireball", "Launches a fireball at the enemy.", 35},
                              {"Backstab", "Deals critical damage from behind.", 25}};

Armor armors[] = {{"Leather Armor", 10, 5},  {"Steel Armor", 20, 10},      {"Diamond Armor", 35, 20},
                  {"Mage Robe", 50, 30},     {"Enchanted Robe", 65, 40},   {"Shadow Cloak", 75, 45},
                  {"Thief's Garb", 120, 60}, {"Assassin's Suit", 215, 80}, {"Cloak of Shadows", 500, 150}};

Weapon weapons[] = {{"Dagger", 12, 6},         {"Staff", 10, 5},          {"Sword", 15, 10},       {"Enchanted Sword", 25, 12},
                    {"Magical Staff", 30, 15}, {"Poison Dagger", 35, 20}, {"Rogue Blade", 45, 30}, {"Assassin's Dagger", 65, 50},
                    {"Shadow Blade", 100, 75}};

Potion potions[] = {{"Health Potion", 10, 20}, {"Greater Health Potion", 20, 50}, {"Max Health Potion", 50, 100}};

void printTitleScreen()
{
    printf("\n***************************************\n");
    printf("******* WELCOME TO GOBLIN QUEST *******\n");
    printf("***************************************\n");
}

void printClasses()
{
    printf("Available Classes:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("%d. %s - %s\n", i + 1, classes[i].name, classes[i].description);
    }
}

void printWeapons(Weapon shopWeapons[], int numWeapons)
{
    printf("Available Weapons:\n");
    for (int i = 0; i < numWeapons; i++)
    {
        printf("%d. %s - Price: %d, Attack Value: %d\n", i + 1, shopWeapons[i].name, shopWeapons[i].price,
               shopWeapons[i].attackValue);
    }
}

void printArmors(Armor shopArmors[], int numArmors)
{
    printf("Available Armors:\n");
    for (int i = 0; i < numArmors; i++)
    {
        printf("%d. %s - Price: %d, Armor Value: %d\n", i + 1, shopArmors[i].name, shopArmors[i].price, shopArmors[i].armorValue);
    }
}

void printAbilities()
{
    printf("Available Abilities:\n");
    for (int i = 0; i < 3; i++)
    {
        printf("%d. %s - %s\n", i + 1, abilities[i].name, abilities[i].description);
    }
}

void createCharacter(Player *player)
{
    printf("\n--- Character Creation ---\n");

    printf("Enter your name: ");
    scanf("%s", player->name);

    printClasses();
    printf("Choose your class (1-3): ");
    scanf("%d", &player->class);

    // Assign a base weapon and bonus based on class
    if (player->class == 1) // Warrior
    {
        player->attack = 10;
        strcpy(player->weapon.name, "Sword");
        player->weapon.price = 15;
        player->weapon.attackValue = 10;
    }
    else if (player->class == 2) // Mage
    {
        player->attack = 5;
        strcpy(player->weapon.name, "Staff");
        player->weapon.price = 12;
        player->weapon.attackValue = 5;
    }
    else if (player->class == 3) // Rogue
    {
        player->attack = 6;
        strcpy(player->weapon.name, "Dagger");
        player->weapon.price = 10;
        player->weapon.attackValue = 6;
    }

    // Other initializations
    player->level = 1;
    player->experience = 0;
    player->health = 100;
    player->defense = 5;
    player->gold = 10;
    player->armor = 0;
    player->abilityUsed = 0;
}

void initializePlayer(Player *player)
{
    player->level = 1;
    player->experience = 0;
    player->health = 100;
    player->attack = player->attack + (player->level - 1) + 2;
    player->defense = 5 + (player->level - 1);
    player->gold = 0;
    player->armor = 0;
    player->abilityUsed = 0;
}

void initializeEnemy(Enemy *enemy, int level)
{
    strcpy(enemy->name, "Goblin");
    enemy->health = 50 + level * 10;
    enemy->attack = 5 + level * 3;
    enemy->defense = 2 + level * 2;
    enemy->goldDrop = 5 + level * 2;
}

void printPlayerStatus(Player player)
{
    printf("Player: %s\n", player.name);
    printf("Level: %d\n", player.level);
    printf("Experience: %d\n", player.experience);
    printf("Health: %d\n", player.health);
    printf("Attack: %d\n", player.attack);
    printf("Defense: %d\n", player.defense);
    printf("Gold: %d\n", player.gold);
    printf("Armor: %d\n", player.armor);
}

void printEnemyStatus(Enemy enemy)
{
    printf("Enemy: %s\n", enemy.name);
    printf("Health: %d\n", enemy.health);
    printf("Attack: %d\n", enemy.attack);
    printf("Defense: %d\n", enemy.defense);
    printf("Gold Drop: %d\n", enemy.goldDrop);
}

void attackEnemy(Player *player, Enemy *enemy)
{
    int damage = player->attack - enemy->defense;
    if (damage < 0)
        damage = 0;
    enemy->health -= damage;
}

void attackPlayer(Player *player, Enemy *enemy)
{
    int damage = enemy->attack - player->defense - player->armor;
    if (damage < 0)
        damage = 0;
    player->health -= damage;
}

void levelUp(Player *player)
{
    player->level++;
    player->experience = 0;
    player->health += player->level + 4;
    player->attack += player->level + 3;
    player->defense += player->level + 3;
}

void visitShop(Player *player, Armor shopArmors[], int numArmors, Weapon shopWeapons[], int numWeapons, Potion shopPotions[],
               int numPotions)
{
    printf("\n--- Welcome to the Shop ---\n");
    printf("Gold: %d\n", player->gold);
    printf("1. Buy Armor\n2. Visit Weapon Shop\n3. Buy Potion\n4. Leave Shop\n");

    int choice;
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            printf("Available Armors:\n");
            printArmors(shopArmors, numArmors);

            int armorChoice;
            printf("Enter the number of the armor you want to buy: ");
            scanf("%d", &armorChoice);

            if (player->gold >= shopArmors[armorChoice - 1].price)
            {
                player->gold -= shopArmors[armorChoice - 1].price;
                player->armor = shopArmors[armorChoice - 1].armorValue;
                printf("You bought %s!\n", shopArmors[armorChoice - 1].name);
            }
            else
            {
                printf("You don't have enough gold!\n");
            }
            break;

        case 2:
            printf("Available Weapons:\n");
            printWeapons(shopWeapons, numWeapons);

            int weaponChoice;
            printf("Enter the number of the weapon you want to buy: ");
            scanf("%d", &weaponChoice);

            if (player->gold >= shopWeapons[weaponChoice - 1].price)
            {
                player->gold -= shopWeapons[weaponChoice - 1].price;
                player->attack = shopWeapons[weaponChoice - 1].attackValue;
                printf("You bought %s!\n", shopWeapons[weaponChoice - 1].name);
            }
            else
            {
                printf("You don't have enough gold!\n");
            }
            break;

        case 3:
            printf("Available Potions:\n");
            for (int i = 0; i < numPotions; i++)
            {
                printf("%d. %s - Price: %d, Health Value: %d\n", i + 1, shopPotions[i].name, shopPotions[i].price,
                       shopPotions[i].healthValue);
            }
            printf("Enter the number of the potion you want to buy: ");
            int potionChoice;
            scanf("%d", &potionChoice);

            if (player->gold >= shopPotions[potionChoice - 1].price)
            {
                player->gold -= shopPotions[potionChoice - 1].price;
                player->health += shopPotions[potionChoice - 1].healthValue;
                printf("You bought %s!\n", shopPotions[potionChoice - 1].name);
            }
            else
            {
                printf("You don't have enough gold!\n");
            }
            break;

        case 4:
            printf("You left the shop.\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
    }
}

void visitWeaponShop(Player *player, Weapon allWeapons[], int numWeapons)
{
    printf("\n--- Welcome to the Weapon Shop ---\n");
    printf("Gold: %d\n", player->gold);

    // Print available weapons
    printWeapons(allWeapons, numWeapons);

    // Player chooses a weapon
    int weaponChoice;
    printf("Enter the number of the weapon you want to buy: ");
    scanf("%d", &weaponChoice);

    // Check if the player has enough gold
    if (player->gold >= allWeapons[weaponChoice - 1].price)
    {
        player->gold -= allWeapons[weaponChoice - 1].price;
        player->attack = allWeapons[weaponChoice - 1].attackValue;
        printf("You bought %s!\n", allWeapons[weaponChoice - 1].name);
    }
    else
    {
        printf("You don't have enough gold!\n");
    }
}

void visitArmorShop(Player *player, Armor allArmors[], int numArmors)
{
    printf("\n--- Welcome to the Armor Shop ---\n");
    printf("Gold: %d\n", player->gold);

    // Print available armors
    printArmors(allArmors, numArmors);

    // Player chooses an armor
    int armorChoice;
    printf("Enter the number of the armor you want to buy: ");
    scanf("%d", &armorChoice);

    // Check if the player has enough gold
    if (player->gold >= allArmors[armorChoice - 1].price)
    {
        player->gold -= allArmors[armorChoice - 1].price;
        player->armor = allArmors[armorChoice - 1].armorValue;
        printf("You bought %s!\n", allArmors[armorChoice - 1].name);
    }
    else
    {
        printf("You don't have enough gold!\n");
    }
}

void printSeparator()
{
    printf("\n---------------------------------------------\n\n");
}

void useAbility(Player *player, Enemy *enemy)
{
    int abilityIndex = player->class - 1;
    int damage = abilities[abilityIndex].specialAbility;

    enemy->health -= damage;
    printf("You used %s and dealt %d damage!\n", abilities[abilityIndex].name, damage);
}

void playerTurn(Player *player, Enemy *enemy)
{
    int choice;
    printf("\nYour turn!\n");
    printf("1. Attack\n2. Use Ability\nEnter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            attackEnemy(player, enemy);
            break;
        case 2:
            if (player->class != 1)
            {
                if (player->abilityUsed == 0)
                {
                    useAbility(player, enemy);
                    player->abilityUsed = 1;
                }
                else
                {
                    printf("You've already used your special ability this level!\n");
                }
            }
            else
            {
                printf("Warriors can't use abilities!\n");
            }
            break;
        default:
            printf("Invalid choice. Please try again.\n");
    }
}

int main()
{
    printTitleScreen();
    Player player;
    Enemy enemy;

    int gameOver = 0;
    while (!gameOver)
    {
        createCharacter(&player);

        while (player.health > 0)
        {
            initializeEnemy(&enemy, player.level);

            printf("\n--- Level %d ---\n", player.level);

            while (player.health > 0 && enemy.health > 0)
            {
                printPlayerStatus(player);
                printSeparator();

                printEnemyStatus(enemy);

                playerTurn(&player, &enemy);

                if (enemy.health <= 0)
                {
                    player.experience += 20 + (player.level - 1) * 2;
                    player.gold += enemy.goldDrop;
                    printf("You defeated the enemy and gained %d experience and %d gold!\n", 20, enemy.goldDrop);
                    player.abilityUsed = 0;
                    break;
                }

                attackPlayer(&player, &enemy);

                if (player.health <= 0)
                {
                    printf("You were defeated by the enemy!\n");
                    break;
                }

                printSeparator();
                sleep(1);
            }

            if (player.experience >= 100)
            {
                levelUp(&player);
                printf("Congratulations! You leveled up!\n");
            }

            visitShop(&player, armors, sizeof(armors) / sizeof(armors[0]), weapons, sizeof(weapons) / sizeof(weapons[0]), potions,
                      sizeof(potions) / sizeof(potions[0]));

            if (player.health <= 0)
            {
                int continueChoice;
                printf("\nDo you want to continue Goblin Quest?\n1. Yes\n2. No\nEnter your choice: ");
                scanf("%d", &continueChoice);

                if (continueChoice != 1)
                {
                    gameOver = 1;
                    break;
                }
            }
        }
    }

    printf("\n--- Game Over ---\n");
    return 0;
}
