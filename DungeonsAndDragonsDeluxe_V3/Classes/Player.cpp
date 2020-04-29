/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Player.cpp
 * Author: Anthony
 * 
 * Created on December 8, 2019, 6:01 PM
 */

#include <valarray>
#include "Player.h"
#include "GameSys.h"

Player::Player() {
    stage = 1;
    this->type="Player";
}

Player::~Player() {
}

//Set Player's Name
void Player::setName() {
    //get name from input
    cin >> name;
    //clear cin from any input in buffer
    cin.ignore();
    //If the name is longer than limit, set to default name
    if (name.size() > 20) {
        name = "Hero";
    }
    cout << endl;
}

//Refil Spell Slots
void Player::refillSpell() {
    //Refill Spell Slots
    commands.find("Fireblast")->second = 4+(this->GetWisdom()*0.5);
    commands.find("Protect")->second = 2+(this->GetWisdom()*0.5);
    commands.find("Lesser Heal")->second = 2+(this->GetWisdom()*0.5);
    commands.find("Healing Word")->second = 2+(this->GetWisdom()*0.5);
    commands.find("Vampiric Touch")->second = 2+(this->GetWisdom()*0.5);
}
void Player::printCommands(){
    //prompt player that it is their turn
    cout << "It is now your turn, what do you want to do?\n"
            "(Type in the value that precedes the command to use it.)" << endl;

    //give command list
    cout << "========================" << endl;
    cout << "~~COMMANDS~~" << endl;
    // Iterate through commands map
    map<string, int>::iterator it;
    int i = 0;
    
    // Print the command with its associated spell use
    for (it=commands.begin(); it!=commands.end(); ++it){
        (it->second > 0) ? cout << i << "=" << it->first << "(" <<
                it->second << ")" << ", " : cout << i << "=" << it->first << ", ";
        i++;
    }
    cout << endl << "========================" << endl;
}

//player's turn to do actions when attacking
string Player::playerTurn(World* level) {
    //Initialize variables
    int choice = -1;
    string comm = "";
    bool isAttk = false;
    this->target = *level->enmSet.begin();
    /*------------------------PICK COMMAND-----------------------*/
    //loop while player has not picked a command
    while(choice == -1) 
    {
        //check if command is valid
        if(cin >> choice)
        {
            // Create map iterators
            map<string, int>::iterator it;
            int i = 0;
            // Find command in map
            for (it=commands.begin(); it!=commands.end(); ++it){
                if(i==choice){
                    comm = it->first;
                }
                i++;
            }
        
            //Check command choice
            if (comm != "") {
                //ATTACK
                if(comm=="Attack") {
                    isAttk = true;
                }
                //FIREBLAST
                else if(comm=="Fireblast") {
                    if(commands.at(comm) > 0) {
                        --commands.at(comm);
                        isAttk = true;
                    }
                    else {
                        choice = -1;
                        cout << "NOT ENOUGH SPELL USES!!" << endl;
                    }
                }
                //LESSER HEAL
                else if(comm=="Lesser Heal") {
                     if(commands.at(comm) > 0) {
                        --commands.at(comm);
                        isAttk = false;
                    }
                    else {
                        choice = -1;
                        cout << "NOT ENOUGH SPELL USES!!" << endl;
                    }
                }
                //PROTECT
                else if(comm=="Protect") {
                    if(commands.at(comm) > 0) {
                        --commands.at(comm);
                        isAttk = false;
                    }
                    else {
                        choice = -1;
                        cout << "NOT ENOUGH SPELL USES!!" << endl;
                    }
                }
                //HEALING WORD
                else if(comm=="Healing Word") {
                    if(commands.at(comm) > 0) {
                        --commands.at(comm);
                        isAttk = false;
                    }
                    else {
                        choice = -1;
                        cout << "NOT ENOUGH SPELL USES!!" << endl;
                    }
                }
                //VAMPIRIC TOUCH
                else if(comm=="Vampiric Touch") {
                    if(commands.at(comm) > 0) {
                        --commands.at(comm);
                        isAttk = true;
                    }
                    else {
                        choice = -1;
                        cout << "NOT ENOUGH SPELL USES!!" << endl;
                    }
                }
                //WHIRLWIND
                else if(comm=="Whirlwind") {
                    isAttk = false;
                }
                else{
                    cout << "NOT A VALID INPUT!!" << endl;
                    choice = -1;
                }
            }
            else{
                //if command is not in bounds of vector
                cout << "NOT A VALID INPUT!!" << endl;
                choice = -1;
            }
        }
        else { //if command is not valid input
            cout << "NOT A VALID INPUT!!" << endl;
            choice = -1;
        }
        //Clear cin Buffer if looping
        cin.clear();
        cin.ignore();
    }
    
    /*------------------------GET TARGET------------------------*/
    //Get target for player
    cout << endl << "========================" << endl;
    choice = -1;
    
    //If we are attacking the target
    if(isAttk)
    {
        //Get Enemy from list and attack
        while(choice == -1){
            cout << "Who do you want to attack?" << endl;
            
            // Iterate through list
            set <Enemies* > :: iterator itr;
            
            //Loop through set of enemies and display them
            int i = 0;
            for (itr = level->enmSet.begin(); itr != level->enmSet.end(); ++itr) 
            {
                if( (*itr)->GetHealth() > 0 ){
                    cout << (*itr)->GetName() << " = " << i+1 << ", ";
                }
                ++i;
            }
            cout << endl;

            //Get choice from player
            if(cin >> choice){
                int i = 0;
                //Check command choice is less than array size & if it is not null
                if ((choice-1) < level->enmSet.size() && (choice) > 0) 
                {
                    i = 0;
                    for (itr = level->enmSet.begin(); itr != level->enmSet.end(); ++itr) 
                    {
                        if(i+1==choice){
                            if((*itr)->GetHealth() > 0 ){
                                this->target = (*itr);
                                cout << endl << "========================" << endl;
                            }
                        }
                        ++i;
                    }
                }
                else{
                    choice = -1;
                    cout << "NOT A VALID INPUT!!" << endl;
                }
            }
            else{
                choice = -1;
                cout << "NOT A VALID INPUT!!" << endl;
            }
            
            //clear cin buffer
            cin.clear();
            cin.ignore();
        }
        
        if(this->target){
            cout << "Target is: " << this->target->GetName() << endl;
        }
    }
    //Return player's command
    return comm;
}

//Player's overall turn
void Player::Attack(World* level){
    //Print commands
    printCommands();
    
    //set attacking to false and get hero's command
    int hroAttk = false;
    string heroCmd = playerTurn(level);
    int crit = false;

    /*---------------Player's Turn---------------*/
    // roll to hit for attacks
    int roll = rollDice(20);

    //check which command the player picked
    //ATTACK
    if(heroCmd == "Attack") {
        //cout << "Rolling Dice to hit...1d20+Strength" << endl;
        
        cout << this->name << " rolled: *" << roll << "(+" << this->GetStrength() << ")*" << endl;
        hroAttk = true;
    }
    //FIREBLAST
    else if(heroCmd == "Fireblast") {
        //cout << "Rolling Dice to hit...1d20+Intellect" << endl;
        
        cout << this->name << " rolled: *" << roll << "(+" << this->GetWisdom() << ")*" << endl;
        hroAttk = true;
    }
    //LESSER HEAL
    else if(heroCmd == "Lesser Heal") {
        roll = rollDice(12);
        //cout << "Rolling Dice for amount to heal...1d12+Intellect" << endl;
        
        cout << this->name << " rolled: *" << roll << "(+" << this->GetWisdom() << ")*" << 
            " health restored!" << endl;
        roll += this->GetWisdom();
        SetHealth(GetHealth() + roll);
        hroAttk = false;
    }
    //HEALING WORD
    else if(heroCmd == "Healing Word") {
        roll = rollDice(4);
        //cout << "Rolling Dice for amount to heal...1d4+Intellect" << endl;
        
        cout << this->name << " rolled: *" << roll << "(+" << this->GetWisdom() << ")*" << 
            " health restored!" << endl;
        roll += GetWisdom();
        SetHealth(GetHealth() + roll);
        hroAttk = false;
    }
    //PROTECT
    else if(heroCmd == "Protect") { //Only roll for armor increase
        roll = rollDice(4);
        //cout << "Rolling Dice for armor increase...1d4+Intellect" << endl;
        
        cout << this->name << " rolled: *" << roll << "(+" << this->GetWisdom() << ")*" << 
            " Armor Rating!" << endl;
        roll += this->GetWisdom();
        SetArmor(GetArmor() + roll);
        protLng = 3;
        hroAttk = false;
    }
    //VAMPIRIC TOUCH
    else if(heroCmd == "Vampiric Touch") {
        //cout << "Rolling Dice to hit...1d20+Intellect" << endl;
        
        cout << this->name << " rolled: *" << roll << "(+" << this->GetWisdom() << ")*" << endl;
        hroAttk = true;
    }
    //WHIRLWIND
    else if(heroCmd == "Whirlwind") {
        //cout << "Rolling Dice to hit...1d20+Strength" << endl;
        
        cout << this->name << " rolled: *" << roll << "(+" << this->GetStrength() << ")*" << endl;
        hroAttk = true;
    }
    else {
        cout << "You do nothing..." << endl;
        hroAttk = false;
    }

    // check for critical hits (roll 20)
    if (roll == 20 && hroAttk == true) {
        cout << "***CRITICAL HIT!***" << endl;
        crit = true;
    }

    // execute the attack
    if(hroAttk) {
        //show the enemy's armor rating to the player if attacking
        cout << "The enemy's Armor Rating is: " << this->target->GetArmor() << endl;
        
        //if the player makes a successful roll (roll > enemy armor)
        //then roll to attack the enemy
        if(roll+GetStrength() >= target->GetArmor() || roll+GetWisdom() >= target->GetArmor())
        {
            roll = 0;
            //roll for damage to the enemy
            //ATTACK
            if(heroCmd == "Attack") {
                roll = rollDice(10);
                //if critical damage, double damage
                (crit) ? roll*=2 : roll *=1;
                //show roll for damage amount if hit
                //cout << "The attack hits! Now rolling for damage...1d10+Strength" << endl;
                
                cout << this->name << " deals: *" << roll << "(+" << GetStrength() << ")*" << 
                        " damage to the enemy by swinging a sharp broadsword!" << endl;
                //add strength modifier
                roll += GetStrength();
            }
            //FIREBLAST
            else if(heroCmd == "Fireblast") {
                roll = rollDice(12);
                //if critical damage, double damage
                (crit) ? roll*=2 : roll *=1;
                //show roll for damage amount if hit
                //cout << "The attack hits! Now rolling for damage...1d12+Intellect" << endl;
                
                cout << this->name << " deals: *" << roll << "(+" << GetWisdom() << ")*" << 
                " fire damage to the enemy by conjuring a small fireball and throwing it!" << endl;
                //add intellect modifier
                roll += GetWisdom();
            }
            //VAMPIRIC TOUCH
            else if(heroCmd == "Vampiric Touch") {
                roll = rollDice(6) + rollDice(6) + rollDice(6);
                //if critical damage, double damage
                (crit) ? roll*=2 : roll *=1;
                //show roll for damage amount if hit
                //cout << "The attack hits! Now rolling for damage...3d6 damage" << endl;
                
                cout << this->name << " deals: *" << roll <<"* necrotic damage to the enemy\n"
                    << "by siphoning the enemy's life through their palms!" << endl;
                //heal hero
                cout << this->name << " restores *" << roll/2 << "* health!!" << endl;
                SetHealth(GetHealth() + roll/2);
            }
            else{
                roll=0;
            }
            //deal damage
            DealDamage(target, roll);
            
            //~~~AOE ATTACKS~~~
        
            //WHIRLWIND
            if(heroCmd == "Whirlwind") {
                roll = rollDice(8);
                //if critical damage, double damage
                (crit) ? roll*=2 : roll *=1;
                //show roll for damage amount if hit
                //cout << "The attack hits! Now rolling for damage...1d10+Strength" << endl;

                cout << this->name << " deals: *" << roll << "(+" << GetStrength() << ")*" << 
                        " damage to all enemies by spinning and creating a bladed tornado!!" << endl;
                //add strength modifier
                roll += GetStrength();
                
                //Loop through set of enemies and damage them by aoe
                set <Enemies* > :: iterator itr;
                for (itr = level->enmSet.begin(); itr != level->enmSet.end(); ++itr) 
                {
                    if((*itr)->GetHealth() > 0) {
                        DealDamage((*itr), roll);
                    }
                    else {
                        //if hit roll is not high enough, miss attack
                        cout << "The attack does not hit!!" << endl;
                    }
                }
            }
        }
    }
    
    //check if player warrior job 'protect' ends after amount of turns
    (protLng == 1) ? cout << "**Protect has faded!**" << endl : cout << " ";
    if (protLng > 0) {
        --protLng;
    }
    if (protLng <= 0) {
        //Set hero armor to default
        SetArmor(GetArmBns());
    }
}

//On Death
void Player::onDeath() {
    cout << "~YOU HAVE FALLEN!! YOUR STORY ENDS HERE!~" << endl;
    //Output file for stats
    writeStats();
    exit(0);
}

//Save Stats to file
void Player::writeStats()
{
    char ans;
    cout << "Would you like to save? (Y/N)" << endl;
    cin >> ans;
    
    if(ans == 'y' || ans == 'Y')
    {
        //Output Stats
        fstream outFile;
        outFile.open("PlayerStats.dat", ios::trunc | ios::out | ios::binary);
        
        //Create Save Structure
        CharaSav playSav;
        
        //Transfer Stats to save struct
        playSav.health = GetHealth();
        playSav.str = GetStrength();
        playSav.wis = GetWisdom();
        playSav.arm = GetArmor();
        playSav.job = this->job;
        playSav.level = GetLevel();
        playSav.stage = stage;
        
        //Save name
        for(int i = 0; i < 100; ++i){
            playSav.name[i] = name[i];
        }
        
        //Write the file
        outFile.write(reinterpret_cast<char *>(&playSav), sizeof(playSav));
        
        cout << "Game Saved!" << endl;
        outFile.close();
    }
}

//Read Stats from file
void Player::readStats(bool &choice)
{
    //Vars
    char ans;
    //Read Stats
    fstream inFile;
    inFile.open("PlayerStats.dat", ios::in | ios::binary);
    inFile.seekg(0, ios::beg);
    
    //Create save struct
    CharaSav playSav;
    
    //read from file
    inFile.read(reinterpret_cast<char *>(&playSav), sizeof(playSav));
    
    //print loaded stats
    cout << "~[LAST SAVE]~" << endl;
    cout << "Name:            " << playSav.name << endl;
    cout << "Health:          " << playSav.health << endl;
    cout << "Strength:        " << playSav.str << endl;
    cout << "Wisdom:          " << playSav.wis << endl;
    cout << "Armor:           " << playSav.arm << endl;
    cout << "Job:             ";
    //Print Job
    switch(playSav.job){
        case 'W':
            cout << "Warrior";
            break;
        case 'M':
            cout << "Mage";
            break;
        case 'C':
            cout << "Cleric";
            break;
        default:
            cout << "NULL";
            break;
    }
    cout << endl;
    //Print rest
    cout << "Level:           " << playSav.level << endl;
    cout << "Stage:           " << playSav.stage << endl;
    
    cout << endl << "Would you like to load this data? (Y/N)" << endl;
    cin >> ans;
    
    if(ans == 'N' || ans == 'n'){
        cout << "Save Not Loaded!" << endl;
        choice = false;
    }
    else{
        if(playSav.stage != 0)
        {
            //transfer stats of loaded save struct to player
            name = playSav.name;
            SetHealth(playSav.health);
            SetStrength(playSav.str);
            SetWisdom(playSav.wis);
            SetArmor(playSav.arm);
            SetArmBns(playSav.arm);
            job = playSav.job;
            SetLevel(playSav.level);
            stage = playSav.stage;
            
            choice = true;
            cout << "Save Loaded!" << endl;
        }
        else{
            cout << "Save is empty!" << endl;
        }
    }
    inFile.close();
}

//Setup Character
void Player::SetupChar(){
    //Init Job
    job = 'N';
    
    //set class (warrior or mage or cleric)
    cout << "---SELECT YOUR CLASS---" << endl;
    cout << "===================================================================" << endl;
    cout << "~~WARRIOR~~" << setw(19) << "~~MAGE~~" << setw(26) << "~~CLERIC~~" 
            << endl;
    cout << "===================================================================" << endl;
    
    cout << "Strength:" << setw(2) << 2 << setw(20) << //warrior strength
            "Strength:" << setw(2) << 1 << setw(22) << // mage strength
            "Strength:" << setw(2) << 2 << endl; // cleric strength
    
    cout << "Intellect:" << setw(2) << 0 << setw(20) <<  //warrior intellect
            "Intellect:" << setw(2) << 3 <<  setw(22) <<  //mage intellect
            "Intellect:" << setw(2) << 2 << endl;  //cleric intellect
    
    cout << "Armor Rating:" << setw(2) << 12 << setw(20) <<  //warrior armor
            "Armor Rating:" << setw(2) << 8 << setw(22) << //mage armor
            "Armor Rating:" << setw(2) << 10 << endl; //cleric armor
    
    cout << "Magic known:" << setw(4) << "Protect" << setw(15) <<  //warrior magic
            "Magic known:" << setw(2) << "Fireblast" << setw(15) << //mage magic
            "Magic known:" << setw(2) << "Lesser Heal" << endl; //cleric magic
    
    //loop while the hero's job is Nothing
    while(job == 'N')
    {
        //prompt player for input
        cout << endl << "Enter ('w'/'W') for WARRIOR, ('m'/'M') for MAGE\n"
                "or ('c'/'C') for CLERIC" << endl;
        //get player's input
        cin >> job;
        //clear cin just incase
        cin.ignore();
        
        //if picked warrior
        if(job == 'W' || job == 'w'){
            cout << "You've chosen Warrior!" << endl;
            //Set stats based on class
            SetStrength(2);
            SetWisdom(0);
            SetArmor(12);
            job = 'W';
            // Add to commands list
            // Then add to another list of Spell Uses
            commands.insert( pair<string,int>("Attack", 0) );
            commands.insert( pair<string,int>("Protect",2) );
        }
        else if(job == 'M' || job == 'm'){ //if picked mage
            cout << "You've chosen Mage!" << endl;
            //Set stats based on class
            SetStrength(1);
            SetWisdom(3);
            SetArmor(8);
            job = 'M';
            // Add to commands list
            // Then add to another list of Spell Uses
            commands.insert( pair<string,int>("Attack",0) );
            commands.insert( pair<string,int>("Fireblast",4) );
        }
        else if(job == 'C' || job == 'c'){ //if picked mage
            cout << "You've chosen Cleric!" << endl;
            //Set stats based on class
            SetStrength(2);
            SetWisdom(2);
            SetArmor(10);
            job = 'C';
            // Add to commands list
            // Then add to another list of Spell Uses
            commands.insert( pair<string,int>("Attack",0) );
            commands.insert( pair<string,int>("Lesser Heal",3) );
        }
        else{
            //if invalid, reset and ask again
            cout << "NOT A VALID INPUT!!";
            job = 'N';
        }
    }
    
    //Set base stats based off of these
    //Set Hero's Stats
    SetHealth(85.f * (GetArmor()*0.08)); // hero health 
    SetArmBns(GetArmor());
    protLng = 0;
}

//Get Loaded map stuff from file cus I'm too lazy to save maps to files
void Player::getStats(){
    switch(job){
        case 'W':
            commands.insert( pair<string,int>("Attack",0) );
            commands.insert( pair<string,int>("Protect",2) );
            break;
        case 'M':
            commands.insert( pair<string,int>("Attack",0) );
            commands.insert( pair<string,int>("Fireblast",4) );
            break;
        case 'C':
            commands.insert( pair<string,int>("Attack",0) );
            commands.insert( pair<string,int>("Lesser Heal",3) );
            break;
    }
    
    if(GetLevel() >= 2){
        if(job == 'W'){
            commands.insert( pair<string,int>("Whirlwind",0) );
        }
        if(job == 'M'){
            commands.insert( pair<string,int>("Healing Word",4) );
        }
        if(job == 'C'){
            commands.insert( pair<string,int>("Healing Word",4) );
        }
    }
    if(GetLevel() >= 3){
        if(job == 'W'){
            commands.insert( pair<string,int>("Healing Word",4) );
        }
        if(job == 'M'){
            commands.insert( pair<string,int>("Vampiric Touch",3) );
        }
        if(job == 'C'){
            commands.insert( pair<string,int>("Protect",4) );
            commands.insert( pair<string,int>("Whirlwind",0) );
        }
    }
}

//Basic level up system
void Player::LevelUp(int level){
    cout << "~~YOU LEVELED UP!!!~~" << endl;
    
    SetLevel(level);
    SetStrength(GetStrength() + level*1.5);
    SetWisdom(GetWisdom() + level*1.5);
    SetArmor(GetArmor() + level*1.5);
    SetHealth(GetHealth() + GetArmor());
    
    cout << "===========================" << endl;
    cout << "Level:         " << GetLevel() << endl;
    cout << "Health:        " << GetHealth() << endl;
    cout << "Strength:      " << GetStrength() << endl;
    cout << "Wisdom:        " << GetWisdom() << endl;
    cout << "Armor:         " << GetArmor() << endl;
    cout << "===========================" << endl;
    
    switch(GetLevel()){
        case 2:
            if(job == 'W'){
                cout << "~You learned WHIRLWIND!!~" << endl;
                commands.insert( pair<string,int>("Whirlwind",0) );
            }
            if(job == 'M'){
                cout << "~You learned HEALING WORD!!~" << endl;
                commands.insert( pair<string,int>("Healing Word",4) );
            }
            if(job == 'C'){
                cout << "~You learned HEALING WORD!!~" << endl;
                commands.insert( pair<string,int>("Healing Word",4) );
            }
            break;
        case 3:
            if(job == 'W'){
                cout << "~You learned HEALING WORD!!~" << endl;
                commands.insert( pair<string,int>("Healing Word",4) );
            }
            if(job == 'M'){
                cout << "~You learned VAMPIRIC TOUCH!!~" << endl;
                commands.insert( pair<string,int>("Vampiric Touch",3) );
            }
            if(job == 'C'){
                cout << "~You learned PROTECT!!~" << endl;
                cout << "~You learned WHIRLWIND!!~" << endl;
                commands.insert( pair<string,int>("Protect",4) );
                commands.insert( pair<string,int>("Whirlwind",0) );
            }
            break;
        default:
            break;
    }
    
}
