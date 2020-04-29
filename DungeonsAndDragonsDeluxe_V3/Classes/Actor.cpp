/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Actor.cpp
 * Author: Anthony
 * 
 * Created on December 8, 2019, 5:53 PM
 */

#include "Actor.h"

Actor::Actor() {
    srand(static_cast<unsigned int>(time(0)));
}

Actor::~Actor() {
}

void Actor::DealDamage(Actor* target, int amount){
    target->SetHealth(target->GetHealth() - amount);
}
void Actor::TakeDamage(int amount){
    this->SetHealth(GetHealth() - amount);
}

void Actor::SetHealth(int amount){this->health = amount;}
void Actor::SetMana(int amount){this->mana = amount;}
void Actor::SetStrength(int amount){this->str = amount;}
void Actor::SetArmor(int amount){this->arm = amount;}
void Actor::SetWisdom(int amount){this->wis = amount;}
void Actor::SetArmBns(int amount){this->armDef = amount;}
void Actor::SetLevel(int amount){this->level = amount;}
void Actor::SetTarget(Actor* target){this->target = target;}

/*
//roll dice function
int Actor::rollDice(int diceAmt) {
    //Get Roll Amount from Random(0-diceAmt)
    int roll = rand() % diceAmt + 1;
    //Return Roll
    return roll;
}

//roll dice function for floats
int Actor::rollDice(float diceAmt) {
    int fDice = round(diceAmt);
    //Get Roll Amount from Random(0-diceAmt)
    int roll = rand() % fDice + 1;
    //Return Roll
    return roll;
}
*/

void Actor::Attack(){
    
}
