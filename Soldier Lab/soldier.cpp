//---------------------------------------------------------
// File : soldier.cpp
// Class: COP 2006, Fall 2022
// Devel: Caleb Newman
// Desc : Conditional expressions for program that demos AI
//        for an NPC soldier character in an RPG
//---------------------------------------------------------
#include <iostream> // console input/output
#include <cstdlib>  // random numbers
#include <ctime>    // seed random

// Constants & Types
//---------------------------------------------------------

// Dice
const int HP_DIE = 20;
const int ENCOUNTER_DIE = 20;
const int TO_HIT_DIE = 3;
const int DAMAGE_DIE = 6;
const int HEAL_DIE = 3;
const int TO_HEAL_DIE = 6;

// Factors
const float ENCOUNTER_CHANCE = 0.5f;
const int ENGAGE_CHECK = 2;

// Soldier Modes
const int HOMING = 0;
const int PATROLLING = 1;
const int ATTACKING = 2;
const int DEFENDING = 3;
const int RETREATING = 4;

// Function Declaration (Prototypes)
//---------------------------------------------------------
int homing(int & soldierHP, int & soldierHealth);
int patrolling(int & soldierHealth, int & enemyHP, int & enemyHealth);
int attacking(int soldierHP, int enemyHP, int & soldierHealth, int & enemyHealth);
int defending(int soldierHP, int enemyHP, int & soldierHealth, int & enemyHealth);
int retreating(int soldierHP, int enemyHP, int & soldierHealth, int & enemyHealth);
bool hitRoll();
void combat(int & soldierHealth, int & enemyHealth, int soldierHP);
void randHeal(int & soldierHealth, int & enemyHealth, int soldierHP, int enemyHP);
bool healRoll();

// Function Definitions
//---------------------------------------------------------

int main() {

    // initialize random numbers
    std::srand(std::time(NULL));

    // roll for soldier hit points
    int soldierHP = std::rand() % HP_DIE + 1; // 1 to HP Dice
    int soldierHealth = soldierHP;  // soldier's current health

    int soldierMode = HOMING;

    int enemyHP = 0;
    int enemyHealth = 0;

    // keep game going until our soldier dies
    do {

        // eval soldier mode
        switch(soldierMode) {

            case HOMING:
                std::cout << "Soldier is in the barracks." << std::endl;
                soldierMode = homing(soldierHP, soldierHealth);
                break;

            case PATROLLING:
                std::cout << "Soldier is patrolling." << std::endl;
                soldierMode = patrolling(soldierHealth, enemyHP, enemyHealth);
                break;

            case ATTACKING:
                std::cout << "Soldier is attacking!" << std::endl;
                soldierMode = attacking(soldierHP,enemyHP, soldierHealth, enemyHealth);
                break;

            case DEFENDING:
                std::cout << "Soldier is defending!" << std::endl;
                soldierMode = defending(soldierHP,enemyHP, soldierHealth, enemyHealth);
                break;

            case RETREATING:
                std::cout << "Soldier is retreating!" << std::endl;
                soldierMode = retreating(soldierHP,enemyHP, soldierHealth, enemyHealth);

        } // end soldier mode

    } while (soldierHealth > 0); // end main game loop

    return 0;
} // end main

/**
 * Soldier is in the home fort
 * @param hitPoints - soldier's hit points
 * @param health - soldier's current health
 * @return - soldier's mode (default HOMING)
 */
int homing(int & soldierHP, int & soldierHealth){
    int retMode = HOMING;

    if (soldierHealth == soldierHP) {
        std::cout << "Soldier is at full health: " << soldierHealth << "/" << soldierHP << "HP"
        << std::endl;
        retMode = PATROLLING;
    } // soldier at full health and ready for patrol
    else {
        soldierHealth = soldierHP;
        std::cout << "Soldier fully healed: " << soldierHealth << "/" << soldierHP << "HP" <<
        " - returning to patrol." << std::endl;
        retMode = PATROLLING;
    } // if soldier not at full health, heal soldier to full original HP and return to patrol.
    return retMode;
} // end homing

/**
 * Soldier is patrolling
 * @param soldierHealth - soldier's health
 * @param enemyHP - enemy hit points
 * @param enemyHealth - enemy health
 * @return - soldier's mode (default is PATROLLING)
 */
int patrolling(int & soldierHealth, int & enemyHP, int & enemyHealth){
    int retMode = PATROLLING;

    if (enemyHealth == 0) {
        float enemyEncounter = std::rand() % ENCOUNTER_DIE + 1;
        if (enemyEncounter >= ENCOUNTER_DIE * ENCOUNTER_CHANCE) {
            //roll for enemy hit points
            enemyHP = rand() % HP_DIE + 1; // 1 to hp dice
            enemyHealth = enemyHP; // enemy's current health
            std::cout << "Soldier encountered an enemy with " << enemyHP << " HP!" <<
            std::endl;

            int maxEnemyHP = enemyHP + ENGAGE_CHECK; //
            int minEnemyHP = enemyHP - ENGAGE_CHECK;

            if (soldierHealth > maxEnemyHP)
                retMode = ATTACKING;
            else if (soldierHealth < minEnemyHP)
                retMode = RETREATING;
            else
                retMode = DEFENDING;

        }

    } // if enemy health is zero then there is no enemy present, spawn an enemy
      // then compare enemy HP to soldier health to determine soldier state

    return retMode;
} // end patrolling

/**
 * soldier is attacking an enemy
 * @param soldierHealth - soldier's current health
 * @param enemyHealth - enemy's current health
 * @return - soldiers mode, default is attacking
 */
int attacking(int soldierHP,int enemyHP, int & soldierHealth, int & enemyHealth){
    int retMode = ATTACKING;
    randHeal(soldierHealth, enemyHealth, soldierHP,enemyHP);
    // call random heal to randomly heal soldier and enemy

    combat(soldierHealth, enemyHealth, soldierHP);
    // call combat function to determine damage done

    if (enemyHealth <= 0) {
        if (soldierHealth >= (soldierHP / 2)) {
            std::cout << "Soldier has defeated the enemy, returning to patrol!" << std::endl;
            retMode = PATROLLING;
        } // enemy was defeated, retrun to patrolling mode
        else {
            std::cout << "Soldier has defeated the enemy, returning to barracks to heal!" << std::endl;
            retMode = HOMING;
        }
    } // enemy was defeated, return to patrolling mode if health high enough, otherwise return to barracks
    if (soldierHealth < (soldierHP / 2)) {
        std::cout << "Soldier is below half health, assuming defensive position!" << std::endl;
        retMode = DEFENDING;
    } // if soldier health falls below half, switch to defending mode

    return retMode;
} // end attacking

/**
 * soldier defending against an enemy
 * @param soldierHealth - soldier's current health
 * @param enemyHealth - enemy's current health
 * @return - soldiers mode - default is attacking
 */
int defending(int soldierHP, int enemyHP, int & soldierHealth, int & enemyHealth){
    int retMode = DEFENDING;
    randHeal(soldierHealth, enemyHealth, soldierHP, enemyHP);
    // call random heal to randomly heal soldier and enemy

    combat(soldierHealth, enemyHealth, soldierHP);
    // call combat function to determine damage done

    if (enemyHealth <= 0) {
            std::cout << "Soldier has defeated the enemy, returning to barracks to heal!" << std::endl;
            retMode = HOMING;
        } // enemy defeated, return to barracks to heal

    if (soldierHealth < (soldierHP / 4) && soldierHealth > 0) {
        std::cout << "Soldier is very low on health, retreating!" << std::endl;
        retMode = RETREATING;
    } // if soldier below quarter health, switch to retreating mode

    if (soldierHealth >= (soldierHP * (0.75f)) && soldierHealth != soldierHP) {
        std::cout << "Soldier has regained enough health, pressing the attack!" << std::endl;
        retMode = ATTACKING;
    } // if soldier regains health to over 75%, switch to attacking mode

    return retMode;
} // end defending

/**
 * Soldier retreating from an enemy
 * @param soldierHealth - soldier's current health
 * @param enemyHealth - enemy's current health
 * @return - soldier's mode (default is retreating)
 */
int retreating(int soldierHP, int enemyHP, int & soldierHealth, int & enemyHealth){
    int retMode = RETREATING;
    randHeal(soldierHealth, enemyHealth, soldierHP, enemyHP);
    // call random heal to randomly heal soldier and enemy

    combat(soldierHealth, enemyHealth, soldierHP);
    // call combat function to determine damage done

    if (enemyHealth <= 0 && soldierHealth > (soldierHP / 4) && soldierHealth > 0) {
        std::cout << "Soldier has defeated the enemy, returning to barracks to heal!" << std::endl;
        retMode = HOMING;
    } // soldier defeated enemy, returns to barracks to heal

    else if (soldierHealth >= (soldierHP / 2) && soldierHealth != soldierHP) {
        std::cout << "Soldier has regained enough health, taking a defensive position!" << std::endl;
        retMode = DEFENDING;
    } // if soldier regains health to half or above, switch to defending

    return retMode;
} // end retreating

/**
 * Roll to-hit dice
 * @return - true if a hit is rolled
 */
bool hitRoll() {
    bool toHit = false;

    // roll die to determine if there is a hit
    int hitRoll = rand() % TO_HIT_DIE + 1;

    if (hitRoll == 1) // only score a hit if roll a 1
        toHit = true;

    return toHit;
} // end hit roll

/**
 * Determine combat damage done.
 * @param soldierHealth - soldier's current health
 * @param enemyHealth - enemy's current health
 */
void combat(int & soldierHealth, int & enemyHealth, int soldierHP){


    int soldierDamage = rand() % DAMAGE_DIE + 1;
    int enemyDamage = rand() % DAMAGE_DIE + 1;


    if(hitRoll()) {
        enemyHealth = enemyHealth - soldierDamage;
        std::cout << "Solider hit enemy for " << soldierDamage << std::endl;
        if (enemyHealth < 0) {
            enemyHealth = 0;
        }
    } // determine amount of damage done by soldier, if hitRoll returns true
    else {
        std::cout << "Soldier missed." << std::endl;
    } // if hitRoll false, return "missed" message.

    if(hitRoll() && enemyHealth > 0) {
        soldierHealth = soldierHealth - enemyDamage;
        std::cout << "Enemy hit soldier for " << enemyDamage << std::endl;

        if (soldierHealth <= 0) {
            std::cout << "Soldier has died, game over!" << std::endl;
        } // if soldier gets to zero health or below, game over message

    } // determine amount of damage done by enemy, if hitRoll returns true

    else if ( !hitRoll() && enemyHealth > 0) {
        std::cout << "Enemy missed." << std::endl;
    } // if hitRoll false, return "missed" message.
} // end combat

/**
 * Determine amount of random heal.
 * @param soldierHealth - soldier's current health
 * @param enemyHealth - enemy's current health
 */
void randHeal(int & soldierHealth, int & enemyHealth, int soldierHP, int enemyHP) {

     if (soldierHealth < (soldierHP - 6)) {
         if (healRoll()) {
             int soldierHeal = rand() % HEAL_DIE + 4;
             soldierHealth = soldierHealth + soldierHeal;
             std::cout << "Soldier gains " << soldierHeal << " HP." << std::endl;
         }
     } // heal soldier by random amount (up to 6) as long as solider is below max health by 6

    if (enemyHealth < (enemyHP - 6)) {
        if (healRoll()) {
            int enemyHeal = rand() % HEAL_DIE + 1;
            enemyHealth = enemyHealth + enemyHeal;
            std::cout << "Enemy gains " << enemyHeal << " HP." << std::endl;
        }
    } // heal enemy by random amount (up to 6) as long as enemy is below max health by 6

} // end randHeal

/**
 * Roll to determine if heal
 * @return - true if heal is rolled
 */
bool healRoll() {
    bool toHeal = false;

    // roll the TO_HEAL_DIE
    int healRoll = rand() % TO_HEAL_DIE + 1;

    // only heal if roll is a 1
    if (healRoll == 1)
        toHeal = true;

    return toHeal;
} // end healRoll