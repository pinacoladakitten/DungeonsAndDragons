/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   World.cpp
 * Author: Anthony
 * 
 * Created on December 8, 2019, 6:03 PM
 */

#include "World.h"

World::World() {
}

World::~World() {
    // Delete all items in set
    set <Enemies*> :: iterator itr;
    stack <Enemies*> delEnm;
    for (itr = enmSet.begin(); itr != enmSet.end(); ++itr) 
    { 
        delEnm.push(*itr);
    }
    
    while(!delEnm.empty()){
        delete delEnm.top();
        delEnm.pop();
    }
}

//Create Enemy Array up to 4 enemies
void World::createEnSet(Enemies* enemy1, Enemies* enemy2, Enemies* enemy3, Enemies* enemy4)
{
    this->size = size;
    enmSet.insert(enemy1);
    if(enemy2 != nullptr) enmSet.insert(enemy2);
    if(enemy3 != nullptr) enmSet.insert(enemy3);
    if(enemy4 != nullptr) enmSet.insert(enemy4);
}

// Inserting objects into set
bool operator< (const Enemies &left, const Enemies &right)
{
    return left.ID < right.ID;
}