#include <iostream>
#include <cstdlib> 
#include "Player.h"

using namespace std; 

Player::Player(){
    name = " ";
    offense = 0; 
    defense = 0; 
    coaching = 0; 
    athleticism = 0; 
    year = 1; 
    recruitmentOdds = 0; 
};

Player::Player(string name){
    this->name = name;
    offense = 0; 
    defense = 0; 
    coaching = 0; 
    athleticism = 0; 
    year = 1; 
    recruitmentOdds = 0; 
};

void Player::generateStats(){
    offense = rand() % 7 + 3; 
    defense = rand() % 7 + 3;
    coaching = rand() % 7 + 3;
    athleticism = rand() % 7 + 3;
    year = rand() % 4 + 1; 
    recruitmentOdds = rand() % 10 + 1; 
    overall = (offense + defense + coaching + athleticism)/4.0; 
}; 

void Player::printStats(){

    cout << name << " | " << getYearLabel() << endl; 
    cout << "Offense: " << offense << " | Defense: " << defense << " | Coaching: " 
    << coaching  << " | Athleticism: " << athleticism << " | Overall: " << overall << endl; 
};

int Player::getOffense(){
    return offense; 
};

int Player::getDefense(){
    return defense; 
};

int Player::getCoaching(){
    return coaching; 
};

int Player::getAthleticism(){
    return athleticism; 
};

int Player::getYear(){
    return year; 
};

string Player::getYearLabel(){
    if(year == 1){
        return "Freshman"; 
    }
    if(year == 2){
        return "Sophomore"; 
    }
    if(year == 3){
        return "Junior"; 
    }
    if(year == 4){
        return "Senior"; 
    }
    return ""; 
};

int Player::getRecruitmentOdds(){
    return recruitmentOdds; 
}

string Player::getName(){
    return name; 
}

void Player::updateStats(int wins){
    offense = float(offense + ((float)wins/20.0)); 
    defense = float(defense + ((float)wins/20.0));
    coaching = float(coaching + ((float)wins/20.0));
    athleticism = float(athleticism + ((float)wins/20.0));
    overall = (offense + defense + coaching + athleticism)/4.0;
    year = year + 1; 

}
