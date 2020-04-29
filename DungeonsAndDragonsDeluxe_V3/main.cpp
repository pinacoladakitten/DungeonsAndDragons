/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: anthony
 *
 * Created on October 18, 2019, 11:57 AM
 */

#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <stdlib.h> // rand()
#include <ctime>    //Time for rand
#include <queue>
#include <list>    // player and enemy queue

#include "Classes/Player.h"
#include "Classes/Enemies.h"
#include "Classes/GameSys.h"
#include "Classes/World.h"
#include "Classes/Actor.h"

void Battle(World* level, Player* player, GameSys* System, int);

using namespace std;
/*
 * 
 */

int main(int argc, char** argv) {
    //Initialize Classes
    Player* player = new Player;
    GameSys* System = new GameSys;
    
    //File Loading
    bool choice = false;
    player->readStats(choice);
    if(choice){player->getStats();}
    
    /*~~~~~~~~~~~~~~~~INTRO~~~~~~~~~~~~~~~~*/
    if(player->stage <= 1){
        //Intro
        System->getDia("[BEG]");

        /*~~~~~~~~~~~~~~~~SETUP PLAYER~~~~~~~~~~~~~~~~*/
        //Start Game Setup
        //Choose Name and set name for player
        System->getDia("[CHOOSE NAME]");
        player->setName();

        //Choose class for player
        System->getDia("[CHOOSE CLASS]");
        System->pressEnter();
        player->SetupChar();
        System->pressEnter();


        /*~~~~~~~~~~~~~~~~START~~~~~~~~~~~~~~~~*/
        //Start Campaign
        System->getDia("[CAMPAIGN START]");
        System->pressEnter();

        /*~~~~~~~~~~~~~~~~BATTLE 1~~~~~~~~~~~~~~~~*/
        System->getDia("[BATTLE1]");
        System->pressEnter();
        System->getPort("[BUNNY]");
        System->getDia("[BATTLE1.5]");
        System->pressEnter();

        //Setup Battle 1
        //Enemy Setup
        World* world = new World;
        Enemies* bunnyGuard = new Enemies(18, 7, 1, 3, 0, 11, "Bunny Guard");
        bunnyGuard->commands.insert( pair<string,int>("Bunny Attack",0) );
        bunnyGuard->SetTarget(player);

        //Create world and add enemies to array
        world->createEnSet(bunnyGuard);
        Battle(world, player, System, 1);

        /*~~~~~~~~~~~~~~~~END OF BATTLE 1~~~~~~~~~~~~~~~~*/
        player->LevelUp(2);
        System->pressEnter();
        player->stage = 2;
        player->writeStats();
        System->pressEnter();
        delete world;
    }
    if(player->stage == 2){
        /*~~~~~~~~~~~~~~~~BATTLE 2~~~~~~~~~~~~~~~~*/
        player->refillSpell();
        System->getDia("[BATTLE2]");
        System->pressEnter();
        System->getDia("[BATTLE2.5]");
        System->pressEnter();

        //Setup Battle 2
        //Enemy Setup
        World* world = new World;
        Enemies* bunnyGuard1 = new Enemies(18, 7, 1, 3, 0, 11, "Bunny Guard #1");
        Enemies* bunnyGuard2 = new Enemies(18, 7, 1, 2, 0, 11, "Bunny Guard #2");
        bunnyGuard1->commands.insert( pair<string,int>("Bunny Attack",0) );
        bunnyGuard2->commands.insert( pair<string,int>("Bunny Kick",0) );
        bunnyGuard1->SetTarget(player);
        bunnyGuard2->SetTarget(player);

        //Create world and add enemies to array
        world->createEnSet(bunnyGuard1, bunnyGuard2);
        Battle(world, player, System, 2);

         /*~~~~~~~~~~~~~~~~END OF BATTLE 2~~~~~~~~~~~~~~~~*/
        player->LevelUp(3);
        System->pressEnter();
        player->stage = 3;
        player->writeStats();
        System->pressEnter();
        delete world;
    }
    if(player->stage == 3){
        /*~~~~~~~~~~~~~~~~BATTLE 3~~~~~~~~~~~~~~~~*/
        World* world = new World;
        player->refillSpell();
        System->getDia("[BATTLE3]");
        System->pressEnter();
        System->getDia("[BATTLE3.5]");
        System->pressEnter();
        System->getDia("[BATTLE3.75]");
        System->pressEnter();
        System->getDia("[BATTLE3.95]");
        System->pressEnter();

        //Setup Battle 2
        //Enemy Setup
        Enemies* Lehr = new Enemies(200, 7, 2, 5, 8, 11, "Lehr");
        Lehr->commands.insert( pair<string,int>("Noose",0) );
        Lehr->commands.insert( pair<string,int>("Mark Sort",0) );
        Lehr->commands.insert( pair<string,int>("Magic Missile",0) );
        Lehr->commands.insert( pair<string,int>("Bitcoin",0) );
        Lehr->SetTarget(player);
        //Create world and add enemies to array
        world->createEnSet(Lehr);
        Battle(world, player, System, 3);

         /*~~~~~~~~~~~~~~~~END OF BATTLE 3~~~~~~~~~~~~~~~~*/
        System->pressEnter();
        player->stage = 3;
        player->writeStats();
        System->pressEnter();
        delete world;
    }
    
    delete player;
    delete System;
    return 0;
}

//Commence battle scene
void Battle(World* level, Player* player, GameSys* System, int stage){
    bool battleEnd = false;
    
    //Looped Battle
    while(player->GetHealth() > 0 && !battleEnd)
    {
        //Display Enemy
        switch(stage){
            case 1:
                System->getPort("[BUNNY]");
                break;
            case 2:
                System->getPort("[2BUNNY]");
                break;
            case 3:
                System->getPort("[SKELLY]");
                break;
            default:
                break;
        }
        
        /*---------------------DISPLAY STATS PER TURN---------------------*/
        cout << "========================" << endl;
        //display player health
        cout << player->GetName() << "'s HP:" << setw(2) << player->GetHealth() << endl;
        
        //display enemy health
        set <Enemies* > :: iterator itr;
        for (itr = level->enmSet.begin(); itr != level->enmSet.end(); ++itr) 
        {
            if((*itr)->GetHealth() > 0){
                cout << (*itr)->GetName() << "'s HP:" << setw(2) << (*itr)->GetHealth() << endl;
            }
        }
        cout << "---------------------------------------------" << endl;
        /*---------------------CREATE TURN ORDER---------------------*/
        queue<Actor*> Qbjs; // Objects in the queue
        list<Actor*> Lbjs; // List of objects to add to queue in random order
        
        // Add objects to list to be randomized
        Lbjs.push_back(player);
        for (itr = level->enmSet.begin(); itr != level->enmSet.end(); ++itr) { Lbjs.push_back(*itr); }
        
        // Randomize order of objects in list then add into queue
        while(Lbjs.size() > 0)
        {
            // Define int iterator and our get value
            int i=0, gets=rand() % Lbjs.size();
            list <Actor*> :: iterator itl;
            
            // Get the object that the random number lands on
            for(itl = Lbjs.begin(); itl != Lbjs.end(); ++itl){
                if(i==gets){
                    Qbjs.push(*itl);
                    Lbjs.erase(itl);
                    itl = Lbjs.end();
                }
                ++i;
            }
        }
        /*---------------------TURNS---------------------*/
        while(Qbjs.size() > 0)
        {
            // If we see the player in the list
            if(Qbjs.front()->GetType()=="Player"){
                player->Attack(level);
                System->pressEnter();
            }
            // If we see any Enemies in the list
            else if(Qbjs.front()->GetType()=="Enemy"){
                if(Qbjs.front()->GetHealth() > 0){
                    Qbjs.front()->Attack();
                    System->pressEnter();
                }
            }
            // Then pop what's in the list
            Qbjs.pop();
        }
        
        //Check if enemies are alive
        battleEnd = true;
        for (itr = level->enmSet.begin(); itr != level->enmSet.end(); ++itr) {
             if((*itr)->GetHealth() > 0){
                battleEnd = false;
            }
        }
        
        //Check if player is alive
        if(player->GetHealth() <= 0){
            player->onDeath();
        }
    }
}