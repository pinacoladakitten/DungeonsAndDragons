/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GameSys.h
 * Author: Anthony
 *
 * Created on December 8, 2019, 8:11 PM
 */

#ifndef GAMESYS_H
#define GAMESYS_H

#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

class GameSys {
public:
    GameSys();
    virtual ~GameSys();
    void getDia(string index);
    void getPort(string index);
    void pressEnter();
};

#endif /* GAMESYS_H */

