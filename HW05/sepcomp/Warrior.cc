#include "Noble.h"
#include "Warrior.h"
#include <iostream>
#include<string>
#include<vector>
using namespace std;
using namespace WarriorCraft;

//Warrior Methods
ostream& WarriorCraft::operator<<(ostream& os, const Warrior& warrToDisp) {
	os << warrToDisp.name << ": " << warrToDisp.strength << endl;
	return os;
}
Warrior::Warrior (const string& name, int strength) : name(name), strength(strength) {
	employer = nullptr;
}
string Warrior::getName() const {return name;}
int Warrior::getStrength() const {return strength;}
void Warrior::setStrength(int stren) {
	strength = stren;
}
void Warrior::fired() {employer = nullptr;}
bool Warrior::getHireStatus() const{
	if(employer == nullptr) {
		return false;
	}
	return true;
}
void Warrior::hired(Noble* working) {
	employer = working;
}

void Warrior::runaway() {
	employer -> run(*this);
}


