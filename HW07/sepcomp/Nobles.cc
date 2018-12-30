#include "Nobles.h"
#include "Protector.h"
#include <string>
#include <vector>
#include <iostream>
using namespace std;
using namespace WarriorCraft;

Noble::Noble(const string& name) : name(name) {alive = true;}
string Noble::getName() const {return name;}
bool Noble::getAlive() const {return alive;}
void Noble::toBattle() const {}
void Noble::battle(Noble& nobleToBattle) {
	double lhsNobleStren = getStrength();
	double rhsNobleStren = nobleToBattle.getStrength();
	cout << name << " battles " << nobleToBattle.name << endl;

	if(alive == true && nobleToBattle.alive == false) {
		cout << "He's dead, " << name << endl;
	}
	else if(alive == false && nobleToBattle.alive == true) {
		cout << "He's dead, " << nobleToBattle.name << endl;
	}
	else if(alive == false && nobleToBattle.alive == false) {
		cout << "Oh, NO! They're both dead! Yuck!" << endl;
	}
	else if(lhsNobleStren > rhsNobleStren) {
		toBattle();	
		nobleToBattle.toBattle();
		cout << name << " defeats " << nobleToBattle.name << endl;
		reduceStrength((1-(rhsNobleStren/lhsNobleStren)));
		nobleToBattle.reduceStrength(0);
		nobleToBattle.alive = false;
	}
	else if(lhsNobleStren < rhsNobleStren) {
		toBattle();	
		nobleToBattle.toBattle();
		cout << nobleToBattle.name << " defeats " << name << endl;
		reduceStrength((1-(lhsNobleStren/rhsNobleStren)));
		reduceStrength(0);//warrior dead when stren is 0
		alive = false;

	}
	else if(lhsNobleStren == rhsNobleStren) {
		cout << "Mutual annihilation " << name << " and " << nobleToBattle.name <<
			" die at eachothers hands." << endl;
		nobleToBattle.alive = false;
		nobleToBattle.reduceStrength(0);
		alive = false;
		reduceStrength(0);
	}
}
//Person with strength to fight
PersonWithStrengthToFight::PersonWithStrengthToFight(const string& name, double strength) : Noble(name), strength(strength) {}
double PersonWithStrengthToFight::getStrength() const {return strength;}
void PersonWithStrengthToFight::reduceStrength(double multiplier) {
	strength = (strength*multiplier);
}
//Lord
Lord::Lord(const string& name) : Noble(name) {}
double Lord::getStrength() const {
	double total = 0;
	for(Protector* fighter: protectors) {
		total += fighter->getStrength();
	}
	return total;
}
void Lord::hires(Protector& protectorToHire) {
	if(protectorToHire.getHired() == true && getAlive() == true) {
		cerr << "This protector is already hired or this lord is dead" << endl;
		return;
	}
	protectorToHire.setHire(this);
	protectors.push_back(&protectorToHire);
	return;
}
void Lord::reduceStrength(double multiplier) {
	for(Protector*& prot: protectors) {
		int stren = prot->getStrength();
		prot->setStrength((multiplier*stren));
	}
}
void Lord::toBattle() const {
	for(Protector* protector: protectors) {
		protector->fight();
	}
}
void Lord::removeFighter(Protector* quitter) {
	for(size_t i = 0; i < protectors.size(); ++i) {
		if(protectors[i] == quitter) {
			protectors.erase(protectors.begin() + i);
			return;
		}
	}
	return;
}

