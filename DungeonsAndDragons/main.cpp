/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Anthony
 *
 * Created on July 17, 2019, 5:27 AM
 */

#include <cstdlib>
#include <iostream> // input/output
#include <iomanip> // setw()
#include <stdlib.h> // rand()
#include <ctime>    //Time for rand
#include <cstdlib>  //Srand to set seed
#include <fstream> // File I/O
#include <cmath> // Math functions
#include <vector> // for vectors

using namespace std;

/*
 * 
 */
//function prototypes
void displayStats(); //displays player's stats
void setName(string&); //sets name of player
void pressEnter(); // wait to press enter
int rollDice(int); //rolling dice
// player setup
char setupChar(char&,int&,int&,int&,vector<string>&commands,
        vector<int>&SpellU);
// event battle
void battleOne(char&,int&,int&,int&,string&,bool&,ofstream&,
        vector<string>&,vector<int>&,string, int,int,int,int);
//commence player's turn
string playerTurn(int&,int,vector<string>&,vector<int>&);
//if the player dies
void onDeath(bool&,ofstream&,string&,int&,int&,int&,char&);
// event after battle#1
void eventOne(char&,int&,int&,int&,string&,bool&,vector<string>&,
        vector<int>&);
//refill spell slots
void refillSpell(vector<string>&,vector<int>&,int&,int&);

/*main*/
int main(int argc, char** argv) {
    // Set random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare I/O file
    ifstream in;               //Input File
    ofstream out;              //Output File
    
    //Initialize variables
    string inName="InputHistory.dat";   //String Name
    char outName[]="OutputHistory.dat"; //Character Array Name
    in.open(inName.c_str());        //Open the Input file
    out.open(outName);         //Open the Output file
    
    // Variable setup & initialize
    string name = "Hero"; // hero name
    char heroJob = 'N'; // hero class
    int heroStr = 0, // hero's strength value
        heroInt = 0, // hero's intellect value
        heroArm = 0; // hero's armor value
    bool heroDead = false;
    //initialize arrays/vectors
    vector<string> commands;
    vector<int> SpellU;
    
    //Main Event
    cout << "~Welcome to the world of Dungeons & Dragons!\nUsually playing the "
            " normal game is quite complex,\nhowever I decided to simplify some"
            " things to make\nthe combat easier to understand. " << endl << endl;
    cout << "~Anyway, let's first choose a name for your character,\n"
            "please enter your hero's name:" << endl;
    
    //Call function to set name
    setName(name);
    
    cout << "~Now choose a class for " << name << " to be, this might be confusing right\n"
            "now, but as you play, you should be able to understand what\n"
            "each stat will contribute to:" << endl;
    cout << "(NOTE: When you see '....' press enter)" << endl;
    
    //Call function to wait for player to press enter
    pressEnter();
    //Setup player's stats for the game
    setupChar(heroJob, heroStr, heroInt, heroArm, commands, SpellU);
    
    cout << "Great! Now let's start the campaign!" << endl;
    
    pressEnter();
    
    cout << "You enter a dark cave seeking to find a mystical gem said to have\n"
            "immense power. You(" << name << ") have been hired by a guild to\n"
            "find this gem and to stop it from falling into the wrong hands." << endl;
    
    pressEnter();
    cout << "Wandering about in the dark you hear something approach you from\n"
            "behind! A goblin attacks! The battle begins!!!" << endl;
    pressEnter();
    
    //Commence the first battle!
    // parameters are: (hero: stats passed by value,
    // enemy's: name, strength, intellect, armor, command choice, output to file,
    // hero: command list, spell use list
    battleOne(heroJob, heroStr, heroInt, heroArm, name, heroDead, out, commands, 
            SpellU, "Goblin", 1, 0, 8, 1);
    
    //Commence more of the game!
    cout << "You defeated the Goblin! Now to continue your adventure!" << endl;
    //Level up player's stats based on class
    switch(heroJob){
        case 'W': //warrior
            cout << "~~From the battle, you gained~~" << endl 
                    << "+2 Strength" << setw(15) << "+1 Armor" << endl;
            heroStr += 2;
            heroArm += 1;
            break;
        case 'M': //mage
            cout << "~~From the battle, you gained~~" << endl 
                    << "+2 Intellect" << endl;
            heroInt += 2;
            break;
        case 'C': //cleric
            cout << "~~From the battle, you gained~~" << endl 
                    << "+1 Intellect, +1 Strength, +1 Armor" << endl;
            heroStr += 1;
            heroArm += 1;
            heroInt += 1;
            break;
        default:
            break;
    }
    pressEnter();
    
    //More Story...
    eventOne(heroJob, heroStr, heroInt, heroArm, name, heroDead, commands, SpellU);
    
    cout << "You proceed through the cave and find a room that's faintly lit up\n"
            "by small torches placed around the room. Suddently, a Skeleton Mage\n"
            "tries to ambush you! Commence the next battle!!" << endl;
    pressEnter();
    
    //Commence Battle 2!!
    battleOne(heroJob, heroStr, heroInt, heroArm, name, heroDead, out, commands, 
            SpellU, "Skeleton Lord", 3, 3, 11, 3);
    
    //commence second battle
    
    cout << "CONGRATS!! You've made it to the end! This is all I can do for now\n"
            "since I gotta turn this in. Thank you for playing!" << endl;
    
    //Output file for stats
    out << "~Here are your player statistics for this run!~" << endl;
    out << "Name: " << name << endl;
    out << "Class: ";
    (heroJob=='W') ? out << "Warrior" : out << "Mage";
    out << endl;
    out << "Strength: " << heroStr << endl;
    out << "Intellect: " << heroInt << endl;
    out << "Armor Rating: " << heroArm << endl;
    
}

//displays stats of characters
void displayStats() {
    cout << "";
}

//if the player is defeated
void onDeath(bool& heroDead, ofstream& out, string& name, int& heroStr, 
        int& heroInt, int& heroArm, char& heroJob) {
    cout << "~YOU HAVE FALLEN!! YOUR STORY ENDS HERE!~" << endl;
    //Output file for stats
    out << "~Here are your player statistics for this run!~" << endl;
    out << "Name: " << name << endl;
    out << "Class: ";
    switch(heroJob){
        case 'W':
            out << "Warrior";
            break;
        case 'M':
            out << "Mage";
            break;
        case 'C':
            out << "Cleric";
            break;
        default:
            out << "Hero";
    }
    out << endl;
    out << "Strength: " << heroStr << endl;
    out << "Intellect: " << heroInt << endl;
    out << "Armor Rating: " << heroArm << endl;
    exit(0);
}

//set hero's name
void setName(string& name) {
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

//press enter
void pressEnter() {
    //set input to default
    string input = " ";
    //show the prompt to press enter to player
    cout << "...." << endl;
    //get player input to press enter
    getline(cin, input);
}

//roll dice function
int rollDice(int diceAmt) {
    //Get Roll Amount from Random(0-diceAmt)
    int roll = rand() % diceAmt + 1;
    //Return Roll
    return roll;
}

//character setup and class pick
char setupChar(char& heroJob, int& heroStr, int& heroInt, int& heroArm,
        vector<string> &commands, vector<int> &SpellU){
    //set class (warrior or mage)
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
    while(heroJob == 'N')
    {
        //prompt player for input
        cout << endl << "Enter ('w'/'W') for WARRIOR, ('m'/'M') for MAGE\n"
                "or ('c'/'C') for CLERIC" << endl;
        //get player's input
        cin >> heroJob;
        //clear cin just incase
        cin.ignore();
        
        //if picked warrior
        if(heroJob == 'W' || heroJob == 'w'){
            cout << "You've chosen Warrior!" << endl;
            //Set stats based on class
            heroStr = 2;
            heroInt = 0;
            heroArm = 12;
            heroJob = 'W';
            // Add to commands list
            // Then add to another list of Spell Uses
            commands.push_back("Attack");
            SpellU.push_back(0);
            commands.push_back("Protect");
            SpellU.push_back(2);
        }
        else if(heroJob == 'M' || heroJob == 'm'){ //if picked mage
            cout << "You've chosen Mage!" << endl;
            //Set stats based on class
            heroStr = 1;
            heroInt = 3;
            heroArm = 8;
            heroJob = 'M';
            // Add to commands list
            // Then add to another list of Spell Uses
            commands.push_back("Attack");
            SpellU.push_back(0);
            commands.push_back("Fireblast");
            SpellU.push_back(4);
        }
        else if(heroJob == 'C' || heroJob == 'c'){ //if picked mage
            cout << "You've chosen Cleric!" << endl;
            //Set stats based on class
            heroStr = 2;
            heroInt = 2;
            heroArm = 10;
            heroJob = 'C';
            // Add to commands list
            // Then add to another list of Spell Uses
            commands.push_back("Attack");
            SpellU.push_back(0);
            commands.push_back("Lesser Heal");
            SpellU.push_back(3);
        }
        else{
            //if invalid, reset and ask again
            cout << "NOT A VALID INPUT!!";
            heroJob = 'N';
        }
    }
}

//player's turn to do actions
string playerTurn(char& heroJob, vector<string> &commands, vector<int> &SpellU) {
    //initialize variables
    int choice = -1;
    
    //prompt player that it is their turn
    cout << "It is now your turn, what do you want to do?\n"
            "(Type in the value that precedes the command to use it.)" << endl;
    
    //give command list
    cout << "========================" << endl;
    cout << "~~COMMANDS~~" << endl;
    for(int i = 0; i < commands.size(); ++i) {
        (SpellU.at(i) > 0) ? cout << i << "=" << commands.at(i) << "(" << 
            SpellU.at(i) << ")" <<  ", " : cout << i << "=" << commands.at(i) << 
            ", ";
    }
    cout << endl << "========================" << endl;
    //loop while player has not picked a command
    while(choice == -1) {
        //check if command is valid
        if(cin >> choice){
            //clear cin buffer
            cin.ignore();
            //Check command choice
            if (choice < commands.size()) {
                if(commands.at(choice)=="Attack") {
                    return "Attack";
                }
                else if(commands.at(choice)=="Fireblast") {
                    if(SpellU.at(choice) > 0) {
                        --SpellU.at(choice);
                        return "Fireblast";
                    }
                    else {
                        choice = -1;
                        cout << "NOT ENOUGH SPELL USES!!" << endl;
                    }
                }
                else if(commands.at(choice)=="Lesser Heal") {
                    if(SpellU.at(choice) > 0) {
                        --SpellU.at(choice);
                        return "Lesser Heal";
                    }
                    else {
                        choice = -1;
                        cout << "NOT ENOUGH SPELL USES!!" << endl;
                    }
                }
                else if(commands.at(choice)=="Protect") {
                    if(SpellU.at(choice) > 0) {
                        --SpellU.at(choice);
                        return "Protect";
                    }
                    else {
                        choice = -1;
                        cout << "NOT ENOUGH SPELL USES!!" << endl;
                    }
                }
                else if(commands.at(choice)=="Healing Word") {
                    if(SpellU.at(choice) > 0) {
                        --SpellU.at(choice);
                        return "Healing Word";
                    }
                    else {
                        choice = -1;
                        cout << "NOT ENOUGH SPELL USES!!" << endl;
                    }
                }
                else{
                    cout << "NOT A VALID INPUT!!" << endl;
                    choice = -1;
                    cin.clear();
                    cin.ignore();
                }
            }
            else{
                cout << "NOT A VALID INPUT!!" << endl;
                choice = -1;
                cin.clear();
                cin.ignore();
            }
        }
        else { //if command is not valid
            cout << "NOT A VALID INPUT!!" << endl;
            choice = -1;
            cin.clear();
            cin.ignore();
        }
    }
}

//Commence First Battle!
void battleOne(char& heroJob, int& heroStr, int& heroInt, 
        int& heroArm, string& name, bool& heroDead, ofstream& out, 
        vector<string>&commands, vector<int>&SpellU, string enmName="Enemy", 
        int enmStr=0, int enmInt=0, int enmArm=0, int enmChce=1)
{   
    const float BENM_HP = 40.f;
    const float BHERO_HP = 65.f;
    
    //Set Hero's Stats
    static int heroHP = BHERO_HP * (heroArm*0.08), // hero health 
    armDef = heroArm; // get default armor value for hero
    bool crit = false; // critical hit check
    int protLng = 0; // warrior protection length
    string heroCmd = "NULL";
    bool hroAttk = false;
    
    // Set Enemy's Stats
    int enmHP = BENM_HP * (enmArm*0.1); // enemy health
    int enmCmd = 1; // enemy command
    // Roll Dice Initialize
    int roll = 0;
    bool enmAttk = false;
    
    /*---------------Loop battle until one is defeated---------------*/
    while(enmHP > 0 && heroHP > 0) {
        //display each object's hp
        cout << name << "'s HP:" << setw(2) << heroHP << setw(3) << "|" << setw(12)
                << enmName << "'s HP:" << setw(2) << enmHP << endl;
        cout << "---------------------------------------------" << endl;
        //set attacking to false and get hero's command
        hroAttk = false;
        heroCmd = playerTurn(heroJob, commands, SpellU);
        crit = false;
        
        /*---------------Player's Turn---------------*/
        // roll to hit for attacks
        roll = rollDice(20);
        
        //check which command the player picked
        if(heroCmd == "Attack") {
            cout << "Rolling Dice to hit...1d20+Strength" << endl;
            cout << name << " rolled: *" << roll << "(+" << heroStr << ")*" << endl;
            hroAttk = true;
        }
        else if(heroCmd == "Fireblast") {
            cout << "Rolling Dice to hit...1d20+Intellect" << endl;
            cout << name << " rolled: *" << roll << "(+" << heroInt << ")*" << endl;
            hroAttk = true;
        }
        else if(heroCmd == "Lesser Heal") {
            roll = rollDice(12);
            cout << "Rolling Dice for amount to heal...1d12+Intellect" << endl;
            cout << name << " rolled: *" << roll << "(+" << heroInt << ")*" << 
                " health restored!" << endl;
            roll += heroInt;
            heroHP += roll;
            hroAttk = false;
        }
        else if(heroCmd == "Healing Word") {
            roll = rollDice(4);
            cout << "Rolling Dice for amount to heal...1d4+Intellect" << endl;
            cout << name << " rolled: *" << roll << "(+" << heroInt << ")*" << 
                " health restored!" << endl;
            roll += heroInt;
            heroHP += roll;
            hroAttk = false;
        }
        else if(heroCmd == "Protect") { //Only roll for armor increase
            roll = rollDice(4);
            cout << "Rolling Dice for armor increase...1d4+Intellect" << endl;
            cout << name << " rolled: *" << roll << "(+" << heroInt << ")*" << 
                " Armor Rating!" << endl;
            roll += heroInt;
            heroArm += roll;
            protLng = 3;
            hroAttk = false;
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
            cout << "The enemy's Armor Rating is: " << enmArm << endl <<
                "----------" << endl;
            //if the player makes a successful roll (roll > enemy armor)
            //then roll to attack the enemy
            if(roll+heroStr >= enmArm || roll+heroInt >= enmArm)
            {
                //roll for damage to the enemy
                if(heroCmd == "Attack") {
                    roll = rollDice(10);
                    //if critical damage, double damage
                    (crit) ? roll*=2 : roll *=1;
                    //show roll for damage amount if hit
                    cout << "The attack hits! Now rolling for damage...1d10+Strength" << endl;
                    cout << name << " deals: *" << roll << "(+" << heroStr << ")*" << 
                            " damage to the enemy by\nswinging a sharp broadsword!" << endl;
                    //add strength modifier
                    roll += heroStr;
                }
                if(heroCmd == "Fireblast") {
                    roll = rollDice(12);
                    //if critical damage, double damage
                    (crit) ? roll*=2 : roll *=1;
                    //show roll for damage amount if hit
                    cout << "The attack hits! Now rolling for damage...1d12+Intellect" << endl;
                    cout << name << " deals: *" << roll << "(+" << heroInt << ")*" << 
                    " fire damage to the enemy\nby conjuring a small fireball and throwing it!" << endl;
                    //add intellect modifier
                    roll += heroInt;
                }
                //deal damage
                enmHP -= roll;
            }
            else {
                //if hit roll is not high enough, miss attack
                cout << "The attack does not hit!!" << endl;
            }
        }
        pressEnter();
        
        /*---------------Enemy's Turn---------------*/
        //Roll enemy's attack command and set if enemy is attacking
        enmCmd = rollDice(enmChce);
        enmAttk = false;
        crit = false;
        //Enemy's turn
        //roll for hit
        roll = rollDice(20);
        switch(enmCmd) {
            //enemy's attack
            case 1:
                cout << "The enemy is rolling to attack you!..." << endl;
                cout << "The " << enmName << " rolled: *" << roll << "(+" << enmStr << ")*" << endl;
                enmAttk = true;
                break;
            case 2:
                cout << "The enemy is rolling to attack you!..." << endl;
                cout << "The " << enmName << " rolled: *" << roll << "(+" << enmInt << ")*" << endl;
                enmAttk = true;
                break;
            case 3:
                cout << "The enemy is rolling to attack you!..." << endl;
                cout << "The " << enmName << " rolled: *" << roll << "(+" << enmInt << ")*" << endl;
                enmAttk = true;
                break;
            default:
                cout << "The enemy does nothing..." << endl;
                break;
        }
        //if critical
        if (roll == 20) {
            cout << "**CRITICAL HIT!**" << endl;
            crit = true;
        }
        //if the enemy is attacking
        if(enmAttk) {
            //show player armor rating
            cout << name << "'s Armor Rating is: " << heroArm << endl <<
                "----------" << endl;
            //if successful roll
            if(roll+enmStr >= heroArm || roll+enmInt >= heroArm ) {
                switch(enmCmd){
                    case 1:
                        //roll for damage
                        roll = rollDice(10);
                        //if critical damage, double damage
                        (crit) ? roll*=2 : roll *=1;
                        //show that the attack had hit
                        cout << "The attack hits! Now rolling for damage..." << endl;
                        cout << "The " << enmName << " deals: *" << roll << "(+" << enmStr << ")*" 
                                << " damage to you by\nslashing you with a small dagger!!" << endl;
                        //add modifier
                        roll += enmStr;
                        break;
                    case 2:
                        //roll for damage
                        roll = rollDice(12);
                        //if critical damage, double damage
                        (crit) ? roll*=2 : roll *=1;
                        //show that the attack had hit
                        cout << "The attack hits! Now rolling for damage..." << endl;
                        cout << "The " << enmName << " deals: *" << roll << "(+" << enmInt << ")*" 
                                << " dark damage to you by\nhurling a ball of shadows!!" << endl;
                        //add modifier
                        roll += enmInt;
                        break;
                    case 3:
                        //roll for damage
                        roll = rollDice(12);
                        //if critical damage, double damage
                        (crit) ? roll*=2 : roll *=1;
                        //show that the attack had hit
                        cout << "The attack hits! Now rolling for damage..." << endl;
                        cout << "The " << enmName << " deals: *" << roll << "(+" << enmInt << ")*" 
                                << " dark damage to you by\ndraining your health with"
                                "its palms!!" << endl;
                        //amount that enemy healed
                        cout << "The " << enmName << " also restores " << 4 << " health!" << endl;
                        //add modifier
                        roll += enmInt;
                        //heal enemy
                        enmHP += 4;
                        break;
                }
                //deal damage
                heroHP -= roll;
            }
            else {
                //if unsuccessful attack
                cout << "The " << enmName << "'s attack does not hit!!" << endl;
            }
        }
        
        /*---------------MISC after turns---------------*/
        //check if warrior protect ends after amount of turns
        (protLng == 1) ? cout << "**Protect has faded!**" << endl : cout << " ";
        if (protLng > 0) {
            --protLng;
        }
        if (protLng <= 0) {
            //Set hero armor to default
            heroArm = armDef;
        }
        //press enter
        pressEnter();
    }
    
    /*---------------After battle---------------*/
    //Set hero armor to default
    heroArm = armDef;
    //check if player dies
    if (heroHP <= 0) {
        onDeath(heroDead, out, name, heroStr, 
        heroInt, heroArm, heroJob);
    }
    //Refill Spells
    refillSpell(commands, SpellU, heroInt, heroStr);
}

//Refil Spell Slots
void refillSpell(vector<string>&commands, vector<int>&SpellU,
        int& heroInt, int& heroStr) {
    //Refill Spell Slots
    for(int i = 0; i < commands.size(); ++i) {
        if(commands.at(i)=="Fireblast"){
            SpellU.at(i) = 4+(heroInt*0.5);
        }
        if(commands.at(i)=="Protect"){
            SpellU.at(i) = 2+(heroInt*0.5);
        }
        if(commands.at(i)=="Lesser Heal"){
            SpellU.at(i) = 2+(heroInt*0.5);
        }
        if(commands.at(i)=="Healing Word"){
            SpellU.at(i) = 2+(heroInt*0.5);
        }
    }
}

//event after battle one
void eventOne(char& heroJob, int& heroStr, int& heroInt, 
        int& heroArm, string& name, bool& heroDead, 
        vector<string>&commands, vector<int>&SpellU){
    //initialize variables
    bool choice;
    char input = 0;
    int roll = 0;
    //display story
    cout << name << " sees a grimoire lying on the floor, it's a book that contains\n"
            "writing that's mystifying to the eye." << endl << endl;
    cout << "Do you want to try and translate the writing? (Type 'y' or 'n')" << endl
            << "You must succeed an Intellect roll of (5 or greater)" << endl;
    do{
        //get player's choice
        cin >> input;
        cin.ignore();
        if(input == 'Y' || input == 'y') {
            choice = true;
        }
        else if(input == 'N' || input == 'n') {
            choice = false;
        }
        else{
            choice = false;
            cout << "NOT A VALID INPUT!!" << endl;
            input = 0;
        }
    }while(input == 0);
    
    if(choice) {
        roll = rollDice(20);
        cout << "Rolling...1d20+Intellect" << endl;
        cout << name << " rolled: " << roll << "(+" << heroInt << ")" << endl;
        roll += heroInt;
        
        pressEnter();
        if(roll >= 5) {
            cout << "You successfully translate the grimoire!" << endl
                    << "~~Armor Rating +2, Intellect +1!~~" << endl 
                    << "~~YOU LEARNED HEALING WORD!!~~" << endl
                    << "The grimoire lights up and you feel a protective barrier\n"
                    "around you!" << endl;
            commands.push_back("Healing Word");
            SpellU.push_back(3);
            heroArm += 2;
            heroInt += 1;
        }
        else {
            cout << "You did not successfully translate the grimoire..." << endl;
        }
    }
    else {
        cout << "You place the grimoire back and move on." << endl;
    }
    pressEnter();
}