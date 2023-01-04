#pragma once 
#include <iostream> 
#include <vector> 
#include "Player.h"

using namespace std; 

class CollegeTeams{
    private:
    string name; 
    string mascot; 
    int offense = 30; 
    int defense = 30; 
    int coaching = 30; 
    int athleticism = 30; 
    int wins = 0; 
    int losses = 0; 
    int gameScore = 0;

    public:
    vector<Player> roster; 
    int winFactor = 0;
    CollegeTeams(string name, string mascot); 
    string getName(); 
    string getMascot(); 
    int playGame(); 
    void generateTeam(); 
    void generateTeam(vector<string> firstName, vector<string> lastName); 
    void calculateStats(); 
    void printStats(); 
    string getRecord(); 
    void addWin(); 
    void addLoss(); 
    int getOffense(); 
    int getDefense(); 
    int getCoaching(); 
    int getAthleticism(); 
    void resetFactors(); 
    int getWins(); 
    int getLosses(); 
    void resetRecord(); 
    void resetStats(); 
    void resetUserStats(); 
    void reorder(); 
    void updatePlayerStats(); 
    string generateName(vector<string> firstName, vector<string> lastName);
};