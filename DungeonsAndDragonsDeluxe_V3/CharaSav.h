/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CharaSav.h
 * Author: Anthony
 *
 * Created on October 24, 2019, 3:50 AM
 */

#ifndef CHARASAV_H
#define CHARASAV_H

struct CharaSav{
    int health, mana, str, arm, wis, armDef, stage, level;
    char job;
    char name[100];
};

#endif /* CHARASAV_H */

