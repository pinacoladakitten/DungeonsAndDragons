/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enm.cpp
 * Author: Anthony
 * 
 * Created on December 8, 2019, 6:19 PM
 */

#include "Enemies.h"

Enemies::Enemies(int health, int mana, int level, int str, int wis, int arm, string name, int speed) {
    SetLevel(level);
    SetHealth(health * (GetLevel() * 1.10));
    SetMana(mana * (GetLevel() * 1.10));
    SetStrength(str * (GetLevel() * 1.10));
    SetWisdom(wis * (GetLevel() * 1.10));
    SetArmor(arm * (GetLevel() * 1.10));
    SetSpeed(speed);
    this->name = name;
    this->type = "Enemy";
}

Enemies::~Enemies() {
}

//Player's overall turn
void Enemies::Attack(){
    /*---------------Enemy's Turn---------------*/
    //roll which attack
    int size = commands.size();
    int command = rollDice(size) - 1;
    string selectCom;
    
    // Init map values
     // Create iterator for map
    unordered_map<string, int>::iterator it;
    int i = 0;
    // Get the command picked from the dice
    for (it=commands.begin(); it!=commands.end(); ++it){
        if(i == command){
            selectCom = it->first;
        }
        i++;
    }
    
    // roll to hit for attacks
    int roll = rollDice(20);
    bool isAttack = false;
    bool crit = false;
    
    /*-----------BUNNY ATTACKS-----------*/
    //check which command the player picked
    //ATTACK
    if(selectCom == "Bunny Attack") {
        //cout << "Rolling Dice to hit...1d20+Strength" << endl;
        
        cout << this->name << " rolled: *" << roll << "(+" << this->GetStrength() << ")*" << endl;
        isAttack = true;
    }
    //KICK
    if(selectCom == "Bunny Kick") {
        //cout << "Rolling Dice to hit...1d20+Strength" << endl;
        
        cout << this->name << " rolled: *" << roll << "(+" << this->GetStrength() << ")*" << endl;
        isAttack = true;
    }
    
    // WEIRD THING ATTACKS----------------
    if(selectCom == "Rapid Jab") {
        //cout << "Rolling Dice to hit...1d20+Strength" << endl;
        
        cout << this->name << " rolled: *" << roll << "(+" << this->GetStrength() << ")*" << endl;
        isAttack = true;
    }
    if(selectCom == "Healing Word") {
        //cout << "Rolling Dice to hit...1d20+Strength" << endl;
        Enemies* randAlly;
        
        int choice = rand() % 2;
        if(choice)randAlly = allyTarg;
        else randAlly = allyTarg1;
        
        roll = rollDice(6);
        cout << this->name << " Healed: " << allyTarg->GetName() << " for " << "*" << roll << "(+" << this->GetWisdom() << ")*" << " health " << endl;
        allyTarg->SetHealth(allyTarg->GetHealth()+roll+this->GetWisdom());
        isAttack = false;
    }
    /*-----------LEHR ATTACKS-----------*/
    //check which command the player picked
    //NOOSE
    if(selectCom == "Noose") {
        //cout << "Rolling Dice to hit...1d20+Strength" << endl;
        
        cout << this->name << " rolled: *" << roll << "(+" << this->GetStrength() << ")*" << endl;
        isAttack = true;
    }
    //SORT
    if(selectCom == "Mark Sort") {
        //cout << "Rolling Dice to hit...1d20+Strength" << endl;
        
        cout << this->name << " rolled: *" << roll << "(+" << this->GetWisdom() << ")*" << endl;
        isAttack = true;
    }
    //MISSILE
    if(selectCom == "Magic Missile") {
        //cout << "Rolling Dice to hit...1d20+Strength" << endl;
        
        cout << this->name << " rolled: *" << roll << "(+" << this->GetWisdom() << ")*" << endl;
        isAttack = true;
    }
    //BITCOIN
    if(selectCom == "Bitcoin") {
        //cout << "Rolling Dice to hit...1d20+Strength" << endl;
        
        cout << this->name << " rolled: *" << roll << "(+" << this->GetStrength() << ")*" << endl;
        isAttack = true;
    }

    // check for critical hits (roll 20)
    if (roll == 20 && isAttack == true) {
        cout << "***CRITICAL HIT!***" << endl;
        crit = true;
    }

    // execute the attack
    if(isAttack) {
        //show the enemy's armor rating to the player if attacking
        cout << "Your Armor Rating is: " << this->target->GetArmor() << endl;
        //if the player makes a successful roll (roll > enemy armor)
        //then roll to attack the enemy
        if(roll+GetStrength() >= target->GetArmor() || roll+GetWisdom() >= target->GetArmor())
        {
            //roll for damage to the player
            /*-----------BUNNY ATTACKS-----------*/
            //ATTACK
            if(selectCom == "Bunny Attack") {
                roll = rollDice(10);
                //if critical damage, double damage
                (crit) ? roll*=2 : roll *=1;
                //show roll for damage amount if hit
                //cout << "The attack hits! Now rolling for damage...1d10+Strength" << endl;
                
                cout << this->name << " deals: *" << roll << "(+" << GetStrength() << ")*" << 
                        " damage with a beefy punch! Ouch!" << endl;
                //add strength modifier
                roll += GetStrength();
            }
            //KICK
            if(selectCom == "Bunny Kick") {
                roll = rollDice(12);
                //if critical damage, double damage
                (crit) ? roll*=2 : roll *=1;
                //show roll for damage amount if hit
                //cout << "The attack hits! Now rolling for damage...1d12+Strength" << endl;
                
                cout << this->name << " deals: *" << roll << "(+" << GetStrength() << ")*" << 
                        " damage with a strong kick!" << endl;
                //add strength modifier
                roll += GetStrength();
            }
            
            /*-----------LEHR ATTACKS-----------*/
            //NOOSE
            if(selectCom == "Noose") {
                roll = rollDice(20);
                //if critical damage, double damage
                (crit) ? roll*=2 : roll *=1;
                //show roll for damage amount if hit
                //cout << "The attack hits! Now rolling for damage...1d10+Strength" << endl;
                
                cout << this->name << " deals: *" << roll << "(+" << GetStrength() << ")*" << 
                        " damage by constricting you with a noose!! Your stats have been lowered!" << endl;
                //add strength modifier
                roll += GetStrength();
                --target;
            }
            //SORT
            if(selectCom == "Mark Sort") {
                roll = rollDice(10);
                //if critical damage, double damage
                (crit) ? roll*=2 : roll *=1;
                //show roll for damage amount if hit
                //cout << "The attack hits! Now rolling for damage...1d12+Strength" << endl;
                
                cout << this->name << " deals: *" << roll << "(+" << GetWisdom() << ")*" << 
                        " psychic damage by sorting an array of numbers!" << endl;
                //add strength modifier
                roll += GetWisdom();
            }
            //MISSILE
            if(selectCom == "Magic Missile") {
                roll = rollDice(12);
                //if critical damage, double damage
                (crit) ? roll*=2 : roll *=1;
                //show roll for damage amount if hit
                //cout << "The attack hits! Now rolling for damage...1d12+Strength" << endl;
                
                cout << this->name << " deals: *" << roll << "(+" << GetWisdom() << ")*" << 
                        " damage by firing a magic missile!" << endl;
                //add strength modifier
                roll += GetWisdom();
            }
            //BITCOIN
            if(selectCom == "Bitcoin") {
                roll = rollDice(rollDice(15));
                //if critical damage, double damage
                (crit) ? roll*=2 : roll *=1;
                //show roll for damage amount if hit
                //cout << "The attack hits! Now rolling for damage...1d12+Strength" << endl;
                
                cout << this->name << " deals: *" << roll << "(+" << GetStrength() << ")*" << 
                        " damage by causing the price of BitCoin to drop!" << endl
                        << "causing you to go into debt!!" << endl;
                //add strength modifier
                roll += GetStrength();
            }
            //deal damage
            DealDamage(target, roll);
        }
        else {
            //if hit roll is not high enough, miss attack
            cout << "The attack does not hit!!" << endl;
        }
    }
}
