#pragma once 
#include <iostream>
#include <cstdlib> 

using namespace std; 

class Player{
    private: 
    string name; 
    float offense; 
    float defense; 
    float coaching; 
    float athleticism;
    int year; 
    int recruitmentOdds; 
    float overall; 

    public:
    Player();
    Player(string name);  
    void generateStats(); 
    void printStats(); 
    int getOffense(); 
    int getDefense(); 
    int getCoaching(); 
    int getAthleticism(); 
    int getYear(); 
    string getYearLabel(); 
    int getRecruitmentOdds(); 
    string getName(); 
    void updateStats(int wins);

};
