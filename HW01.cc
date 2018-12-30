#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;


struct Warrior {
    string name;
    int strength;
};
void verifyStreamIntegrity(const string& fileName) {
    if(!ifstream(fileName)) {
        cerr << fileName << " could not be opened." << endl;
    }
}

void addWarrior(vector<Warrior>& warriors, ifstream& warriorTxt) { // adds a warrior to the vector of warriors
    Warrior toAdd;
    string name;
    int strength;
    warriorTxt >> name >> strength; //gets name and strength from file stream
    toAdd.name = name, toAdd.strength = strength;
    warriors.push_back(toAdd);
}

void status(const vector<Warrior>& warriors) { //displays warrior status
    cout << "There are: " << warriors.size() << " warriors" << endl; //number of warriors
    for(const Warrior& fighter: warriors) {
        cout << "Warrior: " << fighter.name << ", strength: " << fighter.strength << endl; //warrior stats
    }
}

vector<int> getWarriorInd(const string& fighter1, const string& fighter2, const vector<Warrior>& warriors) {// find each warrior in the list to help the battle function
    vector<int> warriorInd;
    for(int i = 0; i < warriors.size(); i++) { //loop through to get the first warrior
        if(warriors[i].name == fighter1) {
            warriorInd.push_back(i);
            break;
        }
    }

    for(int j = 0; j < warriors.size(); j++) { //loop through to get the second warrior
        if(warriors[j].name == fighter2) {
            warriorInd.push_back(j);
            break;
        }
    }
    return warriorInd;
}

void battle(ifstream& warriorTxt, vector<Warrior>& warriors) {
    string fighter1, fighter2;
    warriorTxt >> fighter1 >> fighter2;
    vector<int> fighterInds = getWarriorInd(fighter1, fighter2, warriors);
    int warr1 = fighterInds[0], warr2 = fighterInds[1];
    cout << fighter1 << " battles " << fighter2 << endl;

    if(warriors[warr1].strength == 0 && warriors[warr2].strength == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
        
    }
    else if(warriors[warr1].strength == warriors[warr2].strength) { //draw each warrior has 0 stren
        cout << "Mutual annihilation " << fighter1 << " and " << fighter2 << " die at each other's hands" << endl;
        warriors[warr1].strength = 0;
        warriors[warr2].strength = 0;
    }
    else if(warriors[warr1].strength > warriors[warr2].strength && warriors[warr2].strength != 0) {//warr 1 wins
        cout << fighter1 << " defeats " << fighter2 << endl;
        warriors[warr1].strength = (warriors[warr1].strength - warriors[warr2].strength);
        warriors[warr2].strength = 0;
    }
    else if(warriors[warr2].strength > warriors[warr1].strength && warriors[warr1].strength != 0) {// warr 2 wins
        cout << fighter2 << " defeats " << fighter1 << endl;
        warriors[warr2].strength = (warriors[warr2].strength - warriors[warr1].strength);
        warriors[warr1].strength = 0;
    }
    else if(warriors[warr1].strength > 0 && warriors[warr2].strength == 0) { //warr 2 already dead
        cout << "He's dead, " << fighter1 << endl;
        
    }
    else if(warriors[warr2].strength > 0 && warriors[warr1].strength == 0) { //warr 1 already dead
        cout << "He's dead, " << fighter2 <<  endl;
        
    }

}


int main() {
    string fileName = "warriors.txt";
    verifyStreamIntegrity(fileName);
    ifstream warriorStream(fileName);
    vector<Warrior> vOfWarriors;
    string command;

    while(warriorStream >> command) {
        if(command == "Warrior") {
            addWarrior(vOfWarriors, warriorStream);
        }
        else if(command == "Status") {
            status(vOfWarriors);
        }
        else if(command == "Battle") {
            battle(warriorStream, vOfWarriors);
        }
    }

}