/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameSys.cpp
 * Author: Anthony
 * 
 * Created on December 8, 2019, 8:11 PM
 */

#include "GameSys.h"

GameSys::GameSys() {
}

GameSys::~GameSys() {
}

void GameSys::getDia(string index){
    //Init Stream
    ifstream diaFile;
    diaFile.open("dialogue.txt");
    
    //Init vars
    bool read = false;
    string i, j;
    static int byte = 0;
    
    //Print out contents of the file
    diaFile.seekg(byte, ios::beg);
    
    //Check to see where to stop
    while(i.compare("(STOP)") != 0 || !read)
    {
        //get line and see where to start printing from index
        getline(diaFile, i);
        if(read){
            j = i;
        }
        if(i.compare(index) == 0){
            read = true;
        }
        if(read){
            if(j.compare("(STOP)") != 0){cout << j << endl;}
        }
    }
    
    read = false;
    diaFile.close();
}

//press enter
void GameSys::pressEnter() {
    //set input to default
    string input = " ";
    //show the prompt to press enter to player
    cout << "...." << endl;
    //get player input to press enter
    getline(cin, input);
}

void GameSys::getPort(string index){
    //Init Stream
    ifstream diaFile;
    diaFile.open("enemyPort01.txt");
    
    //Init vars
    bool read = false;
    string i, j;
    static int byte = 0;
    
    //Print out contents of the file
    diaFile.seekg(byte, ios::beg);
    
    //Check to see where to stop
    while(i.compare("(STOP)") != 0 || !read)
    {
        //get line and see where to start printing from index
        getline(diaFile, i);
        if(read){
            j = i;
        }
        if(i.compare(index) == 0){
            read = true;
        }
        if(read){
            if(j.compare("(STOP)") != 0){cout << j << endl;}
        }
    }
    
    read = false;
    diaFile.close();
}

