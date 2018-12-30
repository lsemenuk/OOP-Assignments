#include "Noble.h"
#include "Warrior.h"
#include <string>
#include <iostream>
#include <vector>
using namespace std;
using namespace WarriorCraft;

//Noble methods
ostream& WarriorCraft::operator<<(ostream& os, const Noble& rhs) {
	os << rhs.name << " has an army of " << rhs.army.size() << endl;
	for(Warrior* warr: rhs.army) {
		os << *warr;
	}
	return os;
} 
Noble::Noble (const string& name) : name(name) {alive = true;}
bool Noble::hire(Warrior& warriorToAdd) {
	if(warriorToAdd.getHireStatus() == false && alive == true) {
		army.push_back(&warriorToAdd);
		warriorToAdd.hired(this);
		return true;
	}
	return false;
}
int Noble::findWarr(const Warrior& warrToFind) const {
	int ind = -1;
	for(size_t i = 0; i < army.size(); ++i) {
		if(army[i] == &warrToFind) {
			return i;
		}
	}
	return ind;
}
bool Noble::run(Warrior& warriorToRun) {//checks to see if warrior can be fired
	int ind = findWarr(warriorToRun);
	if(ind == -1){
		cerr << warriorToRun.getName() << "is not a valid warrior." << endl;
		return false;
	}
	cout << warriorToRun.getName() << "flees in terror, abandoning his lord" <<
		name << endl;
	warriorToRun.fired();//so i dont have to make same method with diff name
	army.erase(army.begin() + ind);
	return true;
}

bool Noble::fire(Warrior& warriorToFire) {//checks to see if warrior can be fired
	int ind = findWarr(warriorToFire);
	if(ind == -1){
		cerr << warriorToFire.getName() << "is not part of this army." << endl;
		return false;
	}
	cout << warriorToFire.getName() << " You are fired --" << name << endl;
	warriorToFire.fired();
	army.erase(army.begin() + ind);
	return true;
}
void Noble::display() const {//prints noble anc calls warrior overloaded ouput
	cout << name << " has an army of " << army.size() << endl;
	for(const Warrior* warr: army) {
		cout << *warr << endl;
	}
}
double Noble::getArmystrength() const {
	double armyStrength = 0;
	for(Warrior* warr: army) {
		armyStrength = armyStrength +(warr -> getStrength());
	}
	return armyStrength;
}
void Noble::reduceArmyStrength(double val) {
	for(Warrior* warr: army) {
		double tmpStr = warr -> getStrength();
		warr -> setStrength((tmpStr*val));
	} 
}
void Noble::battle(Noble& nobleToBattle) {
	int army1Strength = getArmystrength();
	int army2Strength = nobleToBattle.getArmystrength();
	cout << name << " battles " << nobleToBattle.name << endl;

	if(alive == true  && nobleToBattle.alive == false) {//one dead one alive
		cout << "He's dead, " << name << endl;
	}
	else if(alive == false && nobleToBattle.alive == true) {//one dead one alive
		cout << "He's dead, " << nobleToBattle.name << endl;
	}
	else if(alive == false && nobleToBattle.alive == false) {//both dead
		cout << "Oh, NO!  They're both dead!  Yuck!" << endl; 
	}
	else if(army1Strength > army2Strength) {//noble 1 beat noble 2
		cout << name << " defeats " << nobleToBattle.name << endl;
		reduceArmyStrength((1-(army2Strength / army1Strength)));
		nobleToBattle.alive = false;;
	}
	else if(army2Strength > army1Strength) {//noble2 beat noble 1
		cout << nobleToBattle.name << " defeats " << name << endl;
		nobleToBattle.reduceArmyStrength((1- (army1Strength / army2Strength)));
		alive = false;
	}
	else if(army1Strength == army2Strength) {//nobles equal both die
		cout << "Mutual annihilation " << name << " and " << nobleToBattle.name
			<< " die at eachothers hands." << endl;
		nobleToBattle.alive = false;
		alive = false;
	}
} 
