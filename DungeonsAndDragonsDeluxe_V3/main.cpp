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
#include "BSTree.h"

void Battle(World* level, Player* player, GameSys* System, int);
void emptyQueue(queue<Actor*>, Player*, GameSys*, World*);
void selectionSort(vector<Actor*>, int, int);
void selectionSort2(vector<Actor*>, int, int&, int, int);
void swap(Actor *, Actor *);

using namespace std;
/*
 * 
 */

int main(int argc, char** argv) {
    //Initialize Classes
    srand(time(0));
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
        Enemies* bunnyGuard = new Enemies(18, 7, 1, 3, 0, 11, "Bunny Guard", rand()%10);
        bunnyGuard->commands.insert( make_pair("Bunny Attack",0) );
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
        Enemies* bunnyGuard1 = new Enemies(18, 7, 1, 3, 0, 11, "Bunny Guard #1",rand()%10);
        Enemies* bunnyGuard2 = new Enemies(18, 7, 1, 2, 0, 11, "Bunny Guard #2",rand()%10);
        bunnyGuard1->commands.insert( make_pair("Bunny Attack",0) );
        bunnyGuard2->commands.insert( make_pair("Bunny Kick",0) );
        bunnyGuard1->SetTarget(player);
        bunnyGuard2->SetTarget(player);

        //Create world and add enemies to array
        world->createEnSet(bunnyGuard1, bunnyGuard2);
        Battle(world, player, System, 2);

         /*~~~~~~~~~~~~~~~~END OF BATTLE 2~~~~~~~~~~~~~~~~*/
        player->LevelUp(3);
        System->pressEnter();
        player->stage = 4;
        player->writeStats();
        System->pressEnter();
        delete world;
    }
    
    if(player->stage == 4){
        /*~~~~~~~~~~~~~~~~BATTLE 4~~~~~~~~~~~~~~~~*/
        player->refillSpell();
        System->getDia("[BATTLE4]");
        System->pressEnter();
        System->getDia("[BATTLE4.5]");
        System->pressEnter();

        //Setup Battle 2
        //Enemy Setup
        World* world = new World;
        Enemies* bunnyGuard1 = new Enemies(21, 7, 1, 2, 0, 11, "Bunny Guard #1",rand()%10);
        Enemies* bunnyGuard2 = new Enemies(21, 7, 1, 2, 0, 11, "Bunny Guard #2",rand()%10);
        Enemies* weirdThing = new Enemies(16, 2, 1, 1, 2, 6, "Weird Thing #1",rand()%3);
        bunnyGuard1->commands.insert( make_pair("Bunny Attack",0) );
        bunnyGuard2->commands.insert( make_pair("Bunny Kick",0) );
        weirdThing->commands.insert( make_pair("Rapid Jab",0) );
        weirdThing->commands.insert( make_pair("Healing Word",0) );
        bunnyGuard1->SetTarget(player);
        bunnyGuard2->SetTarget(player);
        weirdThing->SetTarget(player);

        //Create world and add enemies to array
        world->createEnSet(bunnyGuard1, bunnyGuard2, weirdThing);
        Battle(world, player, System, 4);

         /*~~~~~~~~~~~~~~~~END OF BATTLE 4~~~~~~~~~~~~~~~~*/
        player->LevelUp(4);
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
        Enemies* Lehr = new Enemies(200, 7, 2, 5, 8, 11, "Lehr", rand()%20);
        Lehr->commands.insert( make_pair("Noose",0) );
        Lehr->commands.insert( make_pair("Mark Sort",0) );
        Lehr->commands.insert( make_pair("Magic Missile",0) );
        Lehr->commands.insert( make_pair("Bitcoin",0) );
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
            case 4:
                System->getPort("[3BUNNY]");
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
        list<Actor*> Lbjs; // List of objects to add to vector in random order
        vector<Actor*> Vbjs; // Vector to get objects and sort using recursions
        BSTree<Actor*> bsTree;
        
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
                    Vbjs.push_back(*itl);
                    Lbjs.erase(itl);
                    itl = Lbjs.end();
                }
                ++i;
            }
        }
        /*---------------------SORT TURNS---------------------*/
        selectionSort(Vbjs, Vbjs.size(), 0);
        
        for(int i = 0; i < Vbjs.size(); i++) {
            bsTree.AddNode(Vbjs[i]);
        }
        
        Qbjs.push(bsTree.InOrder(bsTree.root));
        /*---------------------TURNS---------------------*/
        emptyQueue(Qbjs, player, System, level);
        
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

void emptyQueue(queue<Actor*> queue, Player* player, GameSys* System, World* level) {
    if(queue.size() > 0) {
        // If we see the player in the list
        if(queue.front()->GetType()=="Player"){
            player->Attack(level);
            System->pressEnter();
        }
        // If we see any Enemies in the list
        else if(queue.front()->GetType()=="Enemy"){
            if(queue.front()->GetHealth() > 0){
                queue.front()->Attack();
                System->pressEnter();
            }
        }
        // Then pop what's in the list
        queue.pop();
        emptyQueue(queue, player, System, level);
    }
}

void swap(Actor *xp, Actor *yp)  
{  
    Actor* temp = xp;  
    xp = yp;
    yp = temp;
}  
  
void selectionSort(vector<Actor*> arr, int n, int i)
{  
    if(i < n-1) {
        int min_idx = i;
        selectionSort2(arr, n, min_idx, i, i+1);
        // Swap the found minimum element with the first element  
        swap(arr[min_idx], arr[i]);
        selectionSort(arr, n, i+1);
    }
    return;
}

void selectionSort2(vector<Actor*> arr, int n, int& min_idx, int i, int j){
    if(j < n) {
        if (arr[j] > arr[min_idx]){min_idx = j;}
        selectionSort2(arr, n, min_idx, i, j+1);
    }
    return;
}