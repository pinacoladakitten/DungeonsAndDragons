/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.h
 * Author: Anthony
 *
 * Created on December 8, 2019, 6:01 PM
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"
#include "../CharaSav.h"
#include "World.h"

class Player : public Actor {
private:
    char job;
    int protLng;
    
public:
    Player();
    virtual ~Player();
    int stage;
    
    char GetJob(){return job;}
    void refillSpell();
    string playerTurn(World* level);
    void Attack(World* level);
    void onDeath();
    void writeStats();
    void readStats(bool &choice);
    void printCommands();
    void SetupChar();
    void getStats();
    void setName();
    void LevelUp(int level);

};

#endif /* PLAYER_H */

