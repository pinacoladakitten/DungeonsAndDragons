/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Enm.h
 * Author: Anthony
 *
 * Created on December 8, 2019, 6:19 PM
 */

#ifndef ENEMIES_H
#define ENEMIES_H

#include "Actor.h"

class Enemies : public Actor{
private:
    
public:
    Enemies(int health, int mana, int level, int str, int wis, int arm, string name, int speed);
    virtual ~Enemies();
    
    Enemies* allyTarg;
    Enemies* allyTarg1;
    
    virtual void Attack() override;
    
    int ID = rand() % 10000; 

};

#endif /* ENM_H */

