#include <iostream>
#include <vector> 
#include <string> 
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include "CollegeTeams.h"

using namespace std; 

/*
***AT this point the game runs full infinite regular seasons and post seasons
*/

int generateSeed(string name){
    int seed; 
    for(int i = 0; i < name.length(); i++){
        seed = seed + int(name.at(i));
    }

    return seed; 
}

void printStandings(vector<CollegeTeams> conference, int week){
    vector<pair<int, string>> standings;  
    int temp; 
    for (int i = 0; i < conference.size(); i++){
        standings.push_back(make_pair(conference[i].getWins(),conference[i].getName())); 
    }
    sort(standings.begin(), standings.end(), greater <>()); 
    cout << "Week " << week << " Standings:" << endl; 
    for (int i = 0; i < conference.size(); i++){
        for(int j = 0; j < conference.size(); j++){
            if(standings[i].second == conference[j].getName()){
                temp = j; 
            }
        }
        cout << i + 1 << ". " <<  standings[i].second << " " << conference[temp].getRecord() << endl; 
    }
    
}; 

void printAwards(unordered_map<string, int> map){
    cout << "Here are your current awards! " << endl; 
    cout << "Conference Titles: " << map["Conference Titles"] << endl; 
    cout << "Round of 64 Appearences: " << map["Round of 64 Appearences"] << endl; 
    cout << "Round of 32 Appearences: " << map["Round of 32 Appearences"] << endl; 
    cout << "Sweet 16 Appearences: " << map["Sweet 16 Appearences"] << endl; 
    cout << "Elite 8 Appearences: " << map["Elite 8 Appearences"] << endl; 
    cout << "Final 4 Appearences: " << map["Final 4 Appearences"] << endl;
    cout << "National Championship Appearences: " << map["National Championship Appearences"] << endl;
    cout << "National Titles: " << map["National Titles"] << endl;
    cout << "\n"; 
    
}

void gameCalculate(CollegeTeams &team1, CollegeTeams &team2){
    int score1; 
    int score2; 
    score1 = team1.playGame(); 
    score2 = team2.playGame(); 
     
    if(score1 > score2){
        cout << team1.getName() << " " << score1 << " " << score2 << " " << team2.getName() << endl;
        team1.addWin(); 
        team2.addLoss();
        team1.resetFactors(); 
        team2.resetFactors();  
    }
    else if(score1 < score2){
        cout << team1.getName() << " " << score1 << " " << score2 << " " << team2.getName() << endl;
        team1.addLoss(); 
        team2.addWin(); 
        team1.resetFactors(); 
        team2.resetFactors(); 
    }
    else{
        gameCalculate(team1, team2); 
    }

}

bool gameTieCalculate(CollegeTeams &team1, CollegeTeams &team2, vector<CollegeTeams> &conference){
    int score1; 
    int score2; 
    string bleh; 
    score1 = team1.playGame(); 
    score2 = team2.playGame(); 

    cout << "\n Press any key to see result!" << endl; 
    cin >> bleh; 
     
    if(score1 > score2){
        cout << team1.getName() << " " << score1 << " " << score2 << " " << team2.getName() << endl;
        cin >> bleh; 
        team1.addWin(); 
        team2.addLoss();
        printStandings(conference, 14);
        team1.resetFactors(); 
        team2.resetFactors();  
        return true; 
    }
    else if(score1 < score2){
        cout << team1.getName() << " " << score1 << " " << score2 << " " << team2.getName() << endl;
        cin >> bleh;
        team1.addLoss(); 
        team2.addWin(); 
        printStandings(conference, 14);
        team1.resetFactors(); 
        team2.resetFactors(); 
        return false; 
    }
    else{
        gameTieCalculate(team1, team2, conference); 
    }
    return true; 
}

int gameCalculatePlayoff(CollegeTeams &team1, CollegeTeams &team2){
    int score1; 
    int score2; 
    score1 = team1.playGame(); 
    score2 = team2.playGame(); 
     
    if(score1 > score2){
        cout << team1.getName() << " " << score1 << " " << score2 << " " << team2.getName() << endl;
        team1.addWin(); 
        team2.addLoss();
        team1.resetFactors(); 
        team2.resetFactors();  
        return 0;
    }
    else if(score1 < score2){
        cout << team1.getName() << " " << score1 << " " << score2 << " " << team2.getName() << endl;
        team1.addLoss(); 
        team2.addWin(); 
        team1.resetFactors(); 
        team2.resetFactors();
        return 1;
    }
    else{
        return gameCalculatePlayoff(team1, team2); 
    }
    return 1; 
}

void gameSizeUp(CollegeTeams &team1, CollegeTeams &team2){

    if(team1.getOffense() > team2.getOffense()){
        team1.winFactor = team1.winFactor + team1.getOffense() - team2.getOffense(); 
    }
    else{
        team2.winFactor = team2.winFactor + team2.getOffense() - team1.getOffense(); 
    }

    if(team1.getDefense() > team2.getDefense()){
        team1.winFactor = team1.winFactor + team1.getDefense() - team2.getDefense(); 
    }
    else{
        team2.winFactor = team2.winFactor + team2.getDefense() - team1.getDefense(); 
    }

    if(team1.getCoaching() > team2.getCoaching()){
        team1.winFactor = team1.winFactor + team1.getCoaching() - team2.getCoaching(); 
    }
    else{
        team2.winFactor = team2.winFactor + team2.getCoaching() - team1.getCoaching(); 
    }

    if(team1.getAthleticism() > team2.getAthleticism()){
        team1.winFactor = team1.winFactor + team1.getAthleticism() - team2.getAthleticism(); 
    }
    else{
        team2.winFactor = team2.winFactor + team2.getAthleticism() - team1.getAthleticism(); 
    }
}

int findTeam(vector<CollegeTeams> conference, string name){
    for(int i = 0; i < conference.size(); i++){
        if(conference[i].getName() == name){
            return i; 
        }
    }
    return 0; 
}

bool checkConferenceChamp(vector<CollegeTeams> &conference, string name){
    vector<pair<int, string>> standings;  
    int temp; 
    for (int i = 0; i < conference.size(); i++){
        standings.push_back(make_pair(conference[i].getWins(),conference[i].getName())); 
    }
    sort(standings.begin(), standings.end(), greater <>()); 
    
    // First place no tie
    if(standings.front().second == name && standings[0].first != standings[1].first){
        return true;  
    }
    
    // Tie but your number 2 
    else if(standings[0].second == name && standings[0].first == standings[1].first){
        cout << "Tie Breaker!" << endl; 
        cout << "A conference title match will be played between the " << conference[findTeam(conference, standings[0].second)].getName() <<
        " " << conference[findTeam(conference, standings[0].second)].getMascot() << " and " << conference[findTeam(conference, standings[1].second)].getName() <<
        " " << conference[findTeam(conference, standings[1].second)].getMascot(); 

        cout << endl; 

        gameSizeUp(conference[findTeam(conference, standings[0].second)], conference[findTeam(conference, standings[1].second)]); 
        return gameTieCalculate(conference[findTeam(conference, standings[0].second)], conference[findTeam(conference, standings[1].second)],conference);
    }

    else if(standings[1].second == name && standings[0].first == standings[1].first){
        cout << "Tie Breaker!" << endl; 
        cout << "A conference title match will be played between the " << conference[findTeam(conference, standings[1].second)].getName() <<
        " " << conference[findTeam(conference, standings[1].second)].getMascot() << " and " << conference[findTeam(conference, standings[0].second)].getName() <<
        " " << conference[findTeam(conference, standings[0].second)].getMascot(); 

        cout << endl; 

        gameSizeUp(conference[findTeam(conference, standings[1].second)], conference[findTeam(conference, standings[0].second)]); 
        return gameTieCalculate(conference[findTeam(conference, standings[1].second)], conference[findTeam(conference, standings[0].second)],conference);
    }

    else{
        return false; 
    }
    return false; 
}

string generateName(vector<string> firstName, vector<string> lastName){
    int indexF; 
    int indexL; 
    string fullName; 

    indexF = rand() % firstName.size(); 
    indexL = rand() % lastName.size(); 

    fullName = firstName[indexF] + " " + lastName[indexL];
    return fullName; 
}

void bracketOrganize(vector<pair<int,CollegeTeams>> &tournament){
    iter_swap(tournament.begin() + 2, tournament.begin() + 14);
    iter_swap(tournament.begin() + 3, tournament.begin() + 15);
    iter_swap(tournament.begin() + 4, tournament.begin() + 8);
    iter_swap(tournament.begin() + 5, tournament.begin() + 9);
    iter_swap(tournament.begin() + 8, tournament.begin() + 10);
    iter_swap(tournament.begin() + 9, tournament.begin() + 11);

    iter_swap(tournament.begin() + 18, tournament.begin() + 30);
    iter_swap(tournament.begin() + 19, tournament.begin() + 31);
    iter_swap(tournament.begin() + 20, tournament.begin() + 24);
    iter_swap(tournament.begin() + 21, tournament.begin() + 25);
    iter_swap(tournament.begin() + 24, tournament.begin() + 26);
    iter_swap(tournament.begin() + 25, tournament.begin() + 27);

    iter_swap(tournament.begin() + 34, tournament.begin() + 46);
    iter_swap(tournament.begin() + 35, tournament.begin() + 47);
    iter_swap(tournament.begin() + 36, tournament.begin() + 40);
    iter_swap(tournament.begin() + 37, tournament.begin() + 41);
    iter_swap(tournament.begin() + 40, tournament.begin() + 42);
    iter_swap(tournament.begin() + 41, tournament.begin() + 43);

    iter_swap(tournament.begin() + 50, tournament.begin() + 62);
    iter_swap(tournament.begin() + 51, tournament.begin() + 63);
    iter_swap(tournament.begin() + 52, tournament.begin() + 56);
    iter_swap(tournament.begin() + 53, tournament.begin() + 57);
    iter_swap(tournament.begin() + 56, tournament.begin() + 58);
    iter_swap(tournament.begin() + 57, tournament.begin() + 59);
}

main(){
    string schedule = "1234567123456712345671234567";
    int userInput; 
    char anyKey; 
    char otherKey; 
    int playerSelect; 
    int conferenceSelect; 
    string recruitSelect; 
    bool gameStatus = true;  
    bool completeRoster = true; 
    bool teamSelect = false; 
    bool inPostSeason = false; 
    string nameCoach; 
    vector<CollegeTeams> conference;
    vector<Player> recruits; 
    vector<Player> tryouts; 
    vector<Player> temp; 
    vector<string> firstName; 
    vector<string> lastName; 
    vector<string> colleges; 
    vector<CollegeTeams> marchMadness; 
    vector<pair<int,CollegeTeams>> bracketPlay; 
    unordered_map<string, int> awardMap; 
    fstream file; 

    // Read in all First Names
    file.open("firstNames.txt",ios::in);
    if(file.is_open()){
        string nameFirst; 
        while(getline(file,nameFirst)){
            firstName.push_back(nameFirst);
        }
    }
    file.close(); 

    // Read in all Last Names
    file.open("lastNames.txt",ios::in);
    if(file.is_open()){
        string nameLast; 
        while(getline(file,nameLast)){
            lastName.push_back(nameLast);
        }
    }
    file.close(); 

    // Read in all Colleges
    file.open("colleges.txt",ios::in);
    if(file.is_open()){
        string collegeName; 
        while(getline(file,collegeName)){
            colleges.push_back(collegeName);
        }
    }

    // Set up award count so we can keep track of achievements 
    awardMap["Conference Titles"] = 0; 
    awardMap["Round of 64 Appearences"] = 0;
    awardMap["Round of 32 Appearences"] = 0;
    awardMap["Sweet 16 Appearences"] = 0;
    awardMap["Elite 8 Appearences"] = 0;
    awardMap["Final Four Appearences"] = 0;
    awardMap["National Championship Appearences"] = 0;
    awardMap["National Titles"] = 0;

    // Begin Game
    cout << "Be the coach!" << endl; 
    cout << "Enter name:" << endl; 
    getline(cin, nameCoach);
    srand(generateSeed(nameCoach));
    cout << "Select Conference to view teams:" << endl;
    cout << "*You may see some D2 or D3 Teams Mixed in if you really want to create a dynast :)" << endl;
    int count = 1; 
    for(int i = 0; i < colleges.size(); i = i + 9){
        replace(colleges[i].begin(), colleges[i].end(), '_', ' ');
        cout << count << ". "<< colleges[i] << endl;
        count++;  
    } 

    // Team Selection
    while(!teamSelect){
        cout << "\nPlease select a conference: "; 
        cin >> conferenceSelect;
        string schoolName; 
        string schoolMascot; 
        for(int i = 0; i < 8; i++){
            schoolName = colleges[(conferenceSelect-1)*9 + (i + 1)].substr(0,colleges[(conferenceSelect-1)*9 + (i + 1)].find(' ') );
            replace(schoolName.begin(),schoolName.end(),'_',' ');
            schoolMascot = colleges[(conferenceSelect-1)*9 + (i + 1)].substr(colleges[(conferenceSelect-1)*9 + (i + 1)].find(' ') + 1,colleges[(conferenceSelect-1)*9 + (i + 1)].length());
            replace(schoolMascot.begin(),schoolMascot.end(),'_',' ');
            cout << i + 1 << ". " << schoolName << " " << schoolMascot << endl; 
        }

        cout << "If you would like to choose a different conference, type 0" << endl; 
        cout << "If you would like to choose a team, select its number ";
        cin >> userInput; 

        while(userInput >= 9){
            cout << "Select something, retard: " << endl; 
            cin >> userInput; 
        }

        if(userInput == 0){
            teamSelect = false; 
        }
        else {
            teamSelect = true; 
        } 
    }

    string collegeName; 
    string collegeMascot; 
    // Seperates College and Mascots so you can see in selection
    for (int i = 0; i < 8; i++){
        collegeName = colleges[(conferenceSelect-1)*9 + (i + 1)].substr(0,colleges[(conferenceSelect-1)*9 + (i + 1)].find(' '));
        replace(collegeName.begin(),collegeName.end(),'_',' ');
        collegeMascot = colleges[(conferenceSelect-1)*9 + (i + 1)].substr(colleges[(conferenceSelect-1)*9 + (i + 1)].find(' ') + 1,colleges[(conferenceSelect-1)*9 + (i + 1)].length());
        replace(collegeMascot.begin(),collegeMascot.end(),'_',' ');
        conference.push_back(CollegeTeams(collegeName,collegeMascot));
    }
    

    for (int i = 0; i < conference.size(); i++){
        conference[i].generateTeam(firstName,lastName); 
        conference[i].calculateStats(); 
        cout << i + 1 << ". " << conference[i].getName() << endl; 
    }

    // Game Truly Start

    cout << "Welcome Head Coach " << nameCoach << "!" << endl; 
    cout << "New beginnings for the " << conference[userInput - 1].getName() << " " << conference[userInput - 1].getMascot() << "!" << endl; 

    int userWins = 0; 
    int userLosses = 0; 
    int weekNum = 0; 
    int userWinsTemp = 0; 
    int userLossesTemp = 0; 
    int seasonCount = 1; 
    int seniorCount = 0; 
    cout << "Coach " << nameCoach << " all time record: " "(" << userWins << "-" << userLosses << ")" << endl;


    while(gameStatus){

        cout << "\nSeason " << seasonCount << endl; 
        cout << "Roster:" << endl; 
        for (int i = 0; i <  conference[userInput-1].roster.size(); i++){
            conference[userInput-1].roster[i].printStats(); 
            if(conference[userInput-1].roster[i].getYear() == 4){
                seniorCount++; 
            }
        }
        cout << "\n";
        printStandings(conference,weekNum);  
        weekNum++;  
        int i = 0; 

        // Regular Season Schedule (Play each team 2 times)
        for(int i = 0; i < 14; i++){
            cout << "\nWeek " << weekNum << " Schedule:" << endl; 
            cout << conference[0].getName() << " vs " << conference[(int)schedule.at(i+6) - 48].getName() << endl; 
            cout << conference[(int)schedule.at(i) - 48].getName() << " vs " << conference[(int)schedule.at(i+5) - 48].getName() << endl; 
            cout << conference[(int)schedule.at(i+1) - 48].getName() << " vs " << conference[(int)schedule.at(i+4) - 48].getName() << endl; 
            cout << conference[(int)schedule.at(i+2) - 48].getName() << " vs " << conference[(int)schedule.at(i+3) - 48].getName() << endl;
            cout << "Press any key to continue: "; 
            cout << "\n";
            cin >> anyKey;
            cout << "\n";

            gameSizeUp(conference[0], conference[(int)schedule.at(i+6) - 48]);
            gameSizeUp(conference[(int)schedule.at(i) - 48], conference[(int)schedule.at(i+5) - 48]);
            gameSizeUp(conference[(int)schedule.at(i+1) - 48], conference[(int)schedule.at(i+4) - 48]);
            gameSizeUp(conference[(int)schedule.at(i+2) - 48], conference[(int)schedule.at(i+3) - 48]);
        
            gameCalculate(conference[0], conference[(int)schedule.at(i+6) - 48]); 
            gameCalculate(conference[(int)schedule.at(i) - 48], conference[(int)schedule.at(i+5) - 48]); 
            gameCalculate(conference[(int)schedule.at(i+1) - 48], conference[(int)schedule.at(i+4) - 48]); 
            gameCalculate(conference[(int)schedule.at(i+2) - 48], conference[(int)schedule.at(i+3) - 48]); 

            userWins = userWins + (conference[userInput-1].getWins() - userWinsTemp);
            userWinsTemp = conference[userInput-1].getWins(); 
            userLosses = userLosses + (conference[userInput-1].getLosses() - userLossesTemp);
            userLossesTemp = conference[userInput-1].getLosses(); 

            cout << "\n";
            cout << "Press any key to continue: "; 
            cout << "\n";
            cin >> anyKey;
            cout << "\n";

            printStandings(conference,weekNum);
            cout << "Press any key to continue: "; 
            cout << "\n";
            cin >> anyKey;


            weekNum++; 
            cout << "\nCoach " << nameCoach << " all time record: " "(" << userWins << "-" << userLosses << ")" << endl;
        }

        cout << "Season " << seasonCount << " Results: " << endl; 
        cout << "Final Record: " << conference[userInput-1].getRecord() << endl; 

        // Checks to see if you won your conference + Determines if you make playoffs
        if(checkConferenceChamp(conference,conference[userInput-1].getName())){
            cout << "Congratulations! You won your conference! :)" << endl;
            userWins = userWins + (conference[userInput-1].getWins() - userWinsTemp);
            userWinsTemp = conference[userInput-1].getWins(); 
            awardMap["Conference Titles"]++; 
            inPostSeason = true; 
        }

        else if(conference[userInput-1].getWins() >= 7){
            cout << "You did not win the conference, but you made it to the dance!" << endl; 
            inPostSeason = true; 
        }


        else{
            cout << "Sadly, you did not finish at the top of your conference. :(" << endl; 
            userLosses = userLosses + (conference[userInput-1].getLosses() - userLossesTemp);
            userLossesTemp = conference[userInput-1].getLosses();
        }

        // March Madness!
        while(inPostSeason){
            cout << "Welcome to the Postseason! Press any to continue: "; 
            cin >> anyKey; 

            int count = 0; 
            int standing = 1; 
            int seeding; 
            int randConference = conferenceSelect; 
            string schoolName; 
            string mascotName; 
            int randTeam; 
            bool inTourney = true; 

            if(conference[userInput-1].getLosses() == 0){
                seeding = rand() % 3; 
            }
            else if(conference[userInput-1].getLosses() == 1){
                seeding = rand() % 7; 
            }
            else if(conference[userInput-1].getLosses() == 2){
                seeding = rand() % 3 + 8; 
            }
            else if(conference[userInput-1].getLosses() == 3){
                seeding = rand() % 3 + 12; 
            }
            else if(conference[userInput-1].getLosses() == 4){
                seeding = rand() % 7 + 16; 
            }
            else if(conference[userInput-1].getLosses() == 5){
                seeding = rand() % 12 + 24; 
            }
            else if(conference[userInput-1].getLosses() == 6){
                seeding = rand() % 14  + 37; 
            }
            else if(conference[userInput-1].getLosses() == 7){
                seeding = rand() % 11 + 52; 
            }
            
            

            for(int i = 0; i < 64; i++){
                if( i == seeding){
                    marchMadness.push_back(conference[userInput - 1]);
                }
                else{
                    while(inTourney){
                        inTourney = false; 
                         while(randConference == conferenceSelect){
                            randConference = rand() % 62 + 1;
                        }
                        randTeam = rand() % 8 + 1;
                        schoolName = colleges[(randConference-1)*9 + (randTeam)].substr(0,colleges[(randConference-1)*9 + (randTeam)].find(' '));
                        replace(schoolName.begin(),schoolName.end(),'_',' ');
                        mascotName = colleges[(randConference-1)*9 + (randTeam)].substr(colleges[(randConference-1)*9 + (randTeam)].find(' ') + 1,colleges[(randConference-1)*9 + (randTeam)].length());
                        replace(collegeMascot.begin(),collegeMascot.end(),'_',' ');
                        for(int i = 0; i < marchMadness.size(); i++){
                            if(schoolName == marchMadness[i].getName()){
                                inTourney = true; 
                            }
                            else{
                                continue;
                            }
                        }
                    }

                    marchMadness.push_back(CollegeTeams(schoolName,mascotName));
                    marchMadness[i].generateTeam();
                    marchMadness[i].calculateStats(); 
                    randConference = conferenceSelect;
                }
                if(count == 4){
                    standing++;
                    count = 0; 
                }
                cout << standing << ". " << marchMadness[i].getName() << endl; 
                count++; 
                inTourney = true; 
            }

            int roundNumber = 1; 
            
            
            for(int i = 0; i < 8; i++){
                bracketPlay.push_back(make_pair(i+1,marchMadness[i + (i*3)])); 
                bracketPlay.push_back(make_pair(16-i,marchMadness[(60) - (i*4)]));
            }

            for(int i = 0; i < 8; i++){
                bracketPlay.push_back(make_pair(i+1,marchMadness[i + 1 + (i*3)])); 
                bracketPlay.push_back(make_pair(16-i,marchMadness[(61) - (i*4)]));
            }

            for(int i = 0; i < 8; i++){
                bracketPlay.push_back(make_pair(i+1,marchMadness[i + 2 + (i*3)])); 
                bracketPlay.push_back(make_pair(16-i,marchMadness[(62) - (i*4)]));
            }

            for(int i = 0; i < 8; i++){
                bracketPlay.push_back(make_pair(i+1,marchMadness[i + 3 + (i*3)])); 
                bracketPlay.push_back(make_pair(16-i,marchMadness[(63) - (i*4)]));
            }

            bracketOrganize(bracketPlay);

            cout << "\nRound of 64 Schedule: " << endl; 
            awardMap["Round of 64 Appearences"]++;

            for(int i = 0; i < bracketPlay.size(); i++){
                if(i == 0){
                    cout << "South" << endl; 
                }
                if(i == 16){
                    cout << "West" << endl; 
                }
                if(i == 32){
                    cout << "East" << endl; 
                }
                if(i == 48){
                    cout << "Midwest" << endl; 
                }
                cout << bracketPlay[i].first << ". " << bracketPlay[i].second.getName() << endl; 
                if(i % 2 == 1){
                    cout << "\n";
                }
            }

            cout << "Press any to continue: "; 
            cin >> anyKey; 
            int winner; 
            bool isEliminated = false; 

            for(int i = 0; i < 32; i++){
                gameSizeUp(bracketPlay[i].second,bracketPlay[i+1].second);
                winner = gameCalculatePlayoff(bracketPlay[i].second,bracketPlay[i+1].second);
                if(winner == 0){
                    bracketPlay.erase(bracketPlay.begin() + (i + 1));
                }
                else{
                    bracketPlay.erase(bracketPlay.begin() + i); 
                }
            } 

            for(int i = 0; i < bracketPlay.size(); i++){
                if(conference[userInput - 1].getName() == bracketPlay[i].second.getName()){
                    cout << "Congrats on making it to the next round!" << endl; 
                    awardMap["Round of 32 Appearences"]++;
                    isEliminated = false; 
                    break; 
                }
                else{
                    isEliminated = true; 
                }
            }    

            if(isEliminated){
                cout << "Sorry but you are done!" << endl; 
            }    

            cout << "Press any to continue: "; 
            cin >> anyKey; 
            cout << "\nRound of 32 Schedule: " << endl; 
            roundNumber++; 

            for(int i = 0; i < bracketPlay.size(); i++){
                if(i == 0){
                    cout << "South" << endl; 
                }
                if(i == 8){
                    cout << "West" << endl; 
                }
                if(i == 16){
                    cout << "East" << endl; 
                }
                if(i == 24){
                    cout << "Midwest" << endl; 
                }
                cout << bracketPlay[i].first << ". " << bracketPlay[i].second.getName() << endl; 
                if(i % 2 == 1){
                    cout << "\n";
                }

            }

            cout << "Press any to continue: "; 
            cin >> anyKey; 

            for(int i = 0; i < 16; i++){
                gameSizeUp(bracketPlay[i].second,bracketPlay[i+1].second);
                winner = gameCalculatePlayoff(bracketPlay[i].second,bracketPlay[i+1].second);
                if(winner == 0){
                    bracketPlay.erase(bracketPlay.begin() + (i + 1));
                }
                else{
                    bracketPlay.erase(bracketPlay.begin() + i); 
                }
            } 

            for(int i = 0; i < bracketPlay.size(); i++){
                if(conference[userInput - 1].getName() == bracketPlay[i].second.getName()){
                    cout << "Congrats on making it to the next round!" << endl; 
                    awardMap["Sweet 16 Appearences"]++;
                    isEliminated = false; 
                    break; 
                }
                else{
                    isEliminated = true; 
                }
            }    

            if(isEliminated){
                cout << "Sorry but you are done!" << endl; 
            }    

            cout << "Press any to continue: "; 
            cin >> anyKey; 
            cout << "\nSweet 16 Schedule: " << endl; 
            roundNumber++; 

            for(int i = 0; i < bracketPlay.size(); i++){
                if(i == 0){
                    cout << "South" << endl; 
                }
                if(i == 4){
                    cout << "West" << endl; 
                }
                if(i == 8){
                    cout << "East" << endl; 
                }
                if(i == 12){
                    cout << "Midwest" << endl; 
                }
                cout << bracketPlay[i].first << ". " << bracketPlay[i].second.getName() << endl; 
                if(i % 2 == 1){
                    cout << "\n";
                }

            }

            cout << "Press any to continue: "; 
            cin >> anyKey; 

            for(int i = 0; i < 8; i++){
                gameSizeUp(bracketPlay[i].second,bracketPlay[i+1].second);
                winner = gameCalculatePlayoff(bracketPlay[i].second,bracketPlay[i+1].second);
                if(winner == 0){
                    bracketPlay.erase(bracketPlay.begin() + (i + 1));
                }
                else{
                    bracketPlay.erase(bracketPlay.begin() + i); 
                }
            } 

            for(int i = 0; i < bracketPlay.size(); i++){
                if(conference[userInput - 1].getName() == bracketPlay[i].second.getName()){
                    cout << "Congrats on making it to the next round!" << endl; 
                    awardMap["Elite 8 Appearences"]++;
                    isEliminated = false; 
                    break; 
                }
                else{
                    isEliminated = true; 
                }
            }    

            if(isEliminated){
                cout << "Sorry but you are done!" << endl; 
            }    

            cout << "Press any to continue: "; 
            cin >> anyKey; 
            cout << "\nElite 8 Schedule: " << endl; 
            roundNumber++;

            for(int i = 0; i < bracketPlay.size(); i++){
                if(i == 0){
                    cout << "South" << endl; 
                }
                if(i == 2){
                    cout << "West" << endl; 
                }
                if(i == 4){
                    cout << "East" << endl; 
                }
                if(i == 6){
                    cout << "Midwest" << endl; 
                }
                cout << bracketPlay[i].first << ". " << bracketPlay[i].second.getName() << endl; 
                if(i % 2 == 1){
                    cout << "\n";
                }

            }

            cout << "Press any to continue: "; 
            cin >> anyKey; 

            for(int i = 0; i < 4; i++){
                gameSizeUp(bracketPlay[i].second,bracketPlay[i+1].second);
                winner = gameCalculatePlayoff(bracketPlay[i].second,bracketPlay[i+1].second);
                if(winner == 0){
                    bracketPlay.erase(bracketPlay.begin() + (i + 1));
                }
                else{
                    bracketPlay.erase(bracketPlay.begin() + i); 
                }
            } 

            for(int i = 0; i < bracketPlay.size(); i++){
                if(conference[userInput - 1].getName() == bracketPlay[i].second.getName()){
                    cout << "Congrats on making it to the next round!" << endl; 
                    awardMap["Final 4 Appearences"]++;
                    isEliminated = false; 
                    break; 
                }
                else{
                    isEliminated = true; 
                }
            }    

            if(isEliminated){
                cout << "Sorry but you are done!" << endl; 
            }    

            cout << "Press any to continue: "; 
            cin >> anyKey; 
            cout << "\nFinal 4: " << endl; 
            roundNumber++;

            for(int i = 0; i < bracketPlay.size(); i++){
                cout << bracketPlay[i].first << ". " << bracketPlay[i].second.getName() << endl; 
                if(i % 2 == 1){
                    cout << "\n";
                }

            }

            cout << "Press any to continue: "; 
            cin >> anyKey; 

            for(int i = 0; i < 2; i++){
                gameSizeUp(bracketPlay[i].second,bracketPlay[i+1].second);
                winner = gameCalculatePlayoff(bracketPlay[i].second,bracketPlay[i+1].second);
                if(winner == 0){
                    bracketPlay.erase(bracketPlay.begin() + (i + 1));
                }
                else{
                    bracketPlay.erase(bracketPlay.begin() + i); 
                }
            } 

            for(int i = 0; i < bracketPlay.size(); i++){
                if(conference[userInput - 1].getName() == bracketPlay[i].second.getName()){
                    cout << "Congrats on making it to the next round!" << endl; 
                    awardMap["National Championship Appearences"]++;
                    isEliminated = false; 
                    break; 
                }
                else{
                    isEliminated = true; 
                }
            }    

            if(isEliminated){
                cout << "Sorry but you are done!" << endl; 
            }    

            cout << "Press any to continue: "; 
            cin >> anyKey; 
            cout << "\nFinals: " << endl; 
            roundNumber++;

            for(int i = 0; i < bracketPlay.size(); i++){
                cout << bracketPlay[i].first << ". " << bracketPlay[i].second.getName() << endl; 
                if(i % 2 == 1){
                    cout << "\n";
                }

            }

            cout << "Press any to continue: "; 
            cin >> anyKey; 

            for(int i = 0; i < 1; i++){
                gameSizeUp(bracketPlay[i].second,bracketPlay[i+1].second);
                winner = gameCalculatePlayoff(bracketPlay[i].second,bracketPlay[i+1].second);
                if(winner == 0){
                    bracketPlay.erase(bracketPlay.begin() + (i + 1));
                }
                else{
                    bracketPlay.erase(bracketPlay.begin() + i); 
                }
            } 

            if(bracketPlay[0].second.getName() == conference[userInput - 1].getName()){
                cout << "Congratulations! You are truly building a dynasty! Champs!" << endl; 
            }

            inPostSeason = false;
            bracketPlay.clear();
            marchMadness.clear(); 
        }
        cout << "Do you wish to play again? (Type n if you wish to stop or any to continue)" << endl; 
        
        cin >> otherKey; 

        
        if(otherKey == 'n' || otherKey == 'N'){
            gameStatus = false; 
            break; 
        }
        printAwards(awardMap);
        seasonCount++; 
        conference[userInput-1].updatePlayerStats();
        // Reset all teams in conference stats
        for(int i = 0; i < conference.size(); i++){
            conference[i].resetRecord(); 
        }
        userWinsTemp = 0; 
        userLossesTemp = 0; 
        weekNum = 0; 

        for (int i = 0; i < conference.size(); i++){
            if(i + 1 != userInput){
                conference[i].resetStats(); 
                conference[i].roster.clear(); 
                conference[i].generateTeam(firstName,lastName); 
                conference[i].calculateStats(); 
               
            } 
        }

        cout << "Press any to continue: "; 
        cin >> anyKey; 

        // Updates so you can see returning players + Recruit
        if (seniorCount != 0){
           cout << "These players will not be making a return: " << endl; 
            for(int i = 0; i < seniorCount; i++){
                conference[userInput-1].roster.back().printStats(); 
                conference[userInput-1].roster.pop_back(); 
            } 
        }

        cout << "\nHere are your improved returning players!" << endl;  
        for(int i = 0; i < conference[userInput-1].roster.size(); i++){
            conference[userInput-1].roster[i].printStats(); 
        }
        

        seniorCount = 0; 
        cout << "\n";
        completeRoster = false; 
        if(conference[userInput-1].roster.size() == 8){
            cout << "You have a full roster already, do you wish to recruit?"; 
            cin >> otherKey; 

            if(otherKey == 'n' || otherKey == 'N'){
                completeRoster = true; 
        }

        cout << "\n";

        }
        while(!completeRoster){
            cout << "It's time to recruit! Select a few players to invite to your tryout! (They are not guranteed to show up)" << endl; 
            recruits.push_back(Player(generateName(firstName,lastName)));
            recruits.push_back(Player(generateName(firstName,lastName)));
            recruits.push_back(Player(generateName(firstName,lastName))); 
            recruits.push_back(Player(generateName(firstName,lastName)));
            recruits.push_back(Player(generateName(firstName,lastName)));
            for(int i = 0; i < 5; i++){
                recruits[i].generateStats(); 
                cout << i+1 << ". "; 
                recruits[i].printStats(); 
            }

            cout << "\n Type in the number of the recruits you'd like to invite: " << endl;
            cout << "Ex: If you want #2 and #3 type '23' / type '0' if you don't want any" << endl;  
            cin >> recruitSelect; 

            for(int i = 0; i < 5; i++){
                for(int j = 0; j < recruitSelect.size(); j++){
                    if(i+1 == (int)recruitSelect.at(j)-48){
                        temp.push_back(recruits[i]);
                    }
                }
            }

            recruits.clear(); 

            for(int i = 0; i < conference[userInput-1].roster.size(); i++){
                tryouts.push_back(conference[userInput-1].roster[i]); 
            }

            for(int i = 0; i < temp.size(); i++){
                if(temp[i].getRecruitmentOdds() > 5){
                    tryouts.push_back(temp[i]);
                }
            }
            temp.clear(); 

            int remainingPlayers = 16 - tryouts.size(); 
            for(int i = 0; i < remainingPlayers; i++){
                tryouts.push_back(Player(generateName(firstName,lastName))); 
                tryouts[tryouts.size()-1].generateStats(); 
            }

            for(int i = 0; i < tryouts.size(); i++){ 
                cout << i+1 << ". "; 
                tryouts[i].printStats();
                cout << endl; 
            }
            
            conference[userInput-1].roster.clear(); 

            cout << "Please select 8 players you would like" << endl; 
            while(conference[userInput-1].roster.size() < 8){
                cin >> playerSelect; 
                cout << "You selected: " << tryouts[playerSelect-1].getName() << endl; 
                conference[userInput-1].roster.push_back(tryouts[playerSelect - 1]);
            }

            completeRoster = true; 

            tryouts.clear(); 
            conference[userInput-1].resetUserStats(); 
            conference[userInput-1].reorder(); 
            conference[userInput-1].calculateStats(); 

        }

    }
    
}   


