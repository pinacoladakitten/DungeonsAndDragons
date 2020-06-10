/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Actor.h
 * Author: Anthony
 *
 * Created on December 8, 2019, 5:53 PM
 */

#ifndef ACTOR_H
#define ACTOR_H

#include <iostream>
#include <cstdlib>
#include <stdlib.h> // rand()
#include <ctime>    //Time for rand
#include <unordered_map>
#include <cmath>
#include <iomanip>

using namespace std;

class Actor {
private:
    int health, mana, str, arm, wis, armDef, level, speed;
    
protected:
    string name; // name
    Actor *target; //target
    string type="";
    
public:
    Actor();
    virtual ~Actor();
    
    unordered_map<string, int> commands; // command list <Command Name, Spell Use>
    
    int GetHealth(){return health;}
    int GetSpeed(){return speed;}
    int GetMana(){return mana;}
    int GetStrength(){return str;}
    int GetArmor(){return arm;}
    int GetWisdom(){return wis;}
    int GetArmBns(){return armDef;}
    int GetLevel(){return level;}
    string GetName(){return name;}
    string GetType(){return type;}
    
    void SetHealth(int amount);
    void SetMana(int amount);
    void SetStrength(int amount);
    void SetArmor(int amount);
    void SetWisdom(int amount);
    void SetArmBns(int amount);
    void SetLevel(int amount);
    void SetTarget(Actor* target);
    void SetSpeed(int amount);
    
    void DealDamage(Actor* target, int amount);
    void TakeDamage(int amount);

    template <class T>
    T rollDice (T a) {
        T fDice = round(a);
        //Get Roll Amount from Random(0-diceAmt)
        T roll = rand() % fDice + 1;
        //Return Roll
        return roll;
    }
    
    //int rollDice(int diceAmt);
    //int rollDice(float diceAmt);
    
    virtual void Attack();
    
    void operator --(){
        this->SetHealth(GetHealth()-2);
        this->SetMana(GetMana()-2);
        this->SetStrength(GetStrength()-2);
        this->SetArmor(GetArmor()-2);
        this->SetWisdom(GetWisdom()-2);
        this->SetArmBns(GetArmBns()-2);
        this->SetLevel(GetLevel()-2);
    } 
    
    friend bool operator< ( Actor & lhs, Actor & rhs) {
        return (lhs.GetSpeed() < rhs.GetSpeed());
    }
    friend bool operator> ( Actor & lhs, Actor & rhs) {
        return (lhs.GetSpeed() > rhs.GetSpeed());
    }
    
    friend bool operator<= ( Actor & lhs, Actor & rhs) {
        return (lhs.GetSpeed() <= rhs.GetSpeed());
    }
    friend bool operator>= ( Actor & lhs, Actor & rhs) {
        return (lhs.GetSpeed() >= rhs.GetSpeed());
    }
};

#endif /* ACTOR_H */

