/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   World.h
 * Author: Anthony
 *
 * Created on December 8, 2019, 6:03 PM
 */

#ifndef WORLD_H
#define WORLD_H

#include "Actor.h"
#include "Enemies.h"
#include <set>
#include <stack>

using namespace std;

class World {
private:
    int difficulty, size, totalEnmHP;
    
public:
    World();
    virtual ~World();
    
    // Make enemy set
    int GetListSize(){return size;}
    set <Enemies*> enmSet;
    
    void createEnSet(Enemies* enemy1, Enemies* enemy2 = nullptr, Enemies* enemy3 = nullptr, Enemies* enemy4 = nullptr);
    
    // Delete items in set
    void operator --(){
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
    
    // For inserting objects
    friend bool operator< (const Enemies &left, const Enemies &right);

};

#endif /* WORLD_H */

