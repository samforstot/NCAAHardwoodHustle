#include <iostream>
#include <cstdlib> 
#include <vector> 
#include <string>
#include <algorithm> 
#include "CollegeTeams.h"
#include "Player.h"

using namespace std; 


CollegeTeams::CollegeTeams(string name, string mascot){
    this->name = name; 
    this->mascot = mascot; 
}

string CollegeTeams::getName(){
    return name; 
}

string CollegeTeams::getMascot(){
    return mascot; 
}

int CollegeTeams::playGame(){
    int score; 
    score = winFactor + (rand() % 30 + 50); 
    return score;

}

void CollegeTeams::generateTeam(){
    roster.push_back(Player("Player")); 
    roster.push_back(Player("Player")); 
    roster.push_back(Player("Player")); 
    roster.push_back(Player("Player")); 
    roster.push_back(Player("Player")); 
    roster.push_back(Player("Player")); 
    roster.push_back(Player("Player")); 
    roster.push_back(Player("Player")); 
    roster.push_back(Player("Player")); 
    for(int i = 0; i < roster.size(); i++){
        roster[i].generateStats(); 
    }
}

void CollegeTeams::generateTeam(vector<string> firstName, vector<string> lastName){
    roster.push_back(Player(generateName(firstName,lastName))); 
    roster.push_back(Player(generateName(firstName,lastName)));
    roster.push_back(Player(generateName(firstName,lastName)));
    roster.push_back(Player(generateName(firstName,lastName)));
    roster.push_back(Player(generateName(firstName,lastName)));
    roster.push_back(Player(generateName(firstName,lastName)));
    roster.push_back(Player(generateName(firstName,lastName)));
    roster.push_back(Player(generateName(firstName,lastName)));

    for(int i = 0; i < roster.size(); i++){
        roster[i].generateStats(); 
    }

     sort(roster.begin(), roster.end(), [](Player& lhs, Player& rhs) {
      return lhs.getYear() < rhs.getYear();
   });
}

void CollegeTeams::calculateStats(){
    for(int i = 0; i < roster.size(); i++){
        offense = offense + roster[i].getOffense(); 
        defense = defense + roster[i].getDefense(); 
        coaching = coaching + roster[i].getCoaching(); 
        athleticism = athleticism + roster[i].getAthleticism(); 
    }
}

void CollegeTeams::printStats(){
    cout << "\n" << name << " Stats:" << endl; 
    cout << "Offense: " << offense << endl; 
    cout << "Defense: " << defense << endl; 
    cout << "Coaching: " << coaching << endl; 
    cout << "Athleticism: " << athleticism << endl; 
}

string CollegeTeams::getRecord(){
    string record; 
    record = "(" + to_string(wins) + "-" + to_string(losses) + ")"; 
    return record; 
}

void CollegeTeams::addWin(){
    wins = wins + 1; 
}

void CollegeTeams::addLoss(){
    losses = losses + 1; 
}

int CollegeTeams::getOffense(){
    return offense; 
}

int CollegeTeams::getDefense(){
    return defense; 
}

int CollegeTeams::getCoaching(){
    return coaching; 
}

int CollegeTeams::getAthleticism(){
    return athleticism; 
}

void CollegeTeams::resetFactors(){
    winFactor = 0; 
}

int CollegeTeams::getWins(){
    return wins; 
}

int CollegeTeams::getLosses(){
    return losses; 
}

void CollegeTeams::resetRecord(){
    wins = 0; 
    losses = 0; 
}

void CollegeTeams::resetStats(){
    offense = 35; 
    defense = 35; 
    coaching = 35; 
    athleticism = 35;
}

void CollegeTeams::resetUserStats(){
    offense = 30; 
    defense = 30; 
    coaching = 30; 
    athleticism = 30;
}

void CollegeTeams::reorder(){
    sort(roster.begin(), roster.end(), [](Player& lhs, Player& rhs) {
      return lhs.getYear() < rhs.getYear();
   });
}

void CollegeTeams::updatePlayerStats(){
    for(int i = 0; i < roster.size(); i++){
        roster[i].updateStats(wins); 
    }
}

string CollegeTeams::generateName(vector<string> firstName, vector<string> lastName){
    int indexF; 
    int indexL; 
    string fullName; 

    indexF = rand() % firstName.size(); 
    indexL = rand() % lastName.size(); 

    fullName = firstName[indexF] + " " + lastName[indexL];
    return fullName; 
}
