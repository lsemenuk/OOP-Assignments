#include "Nobles.h"
#include "Protector.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace WarriorCraft;

Protector::Protector(const string& name, double strength) : name(name), strength(strength) {
	boss = nullptr;
	alive = true;
}
double Protector::getStrength() const {return strength;}
bool Protector::getHired() const {
	if(boss) {
		return true;
	}
	return false;
}
void Protector:: setHire(Lord* bossLord) {
	boss = bossLord;
}
void Protector::setStrength(double num) {
	strength = num;
}
void Protector::quit() {
	boss->removeFighter(this);
	boss = nullptr;
}
//archer
void Archer::fight() {
	cout << "TWANG! " << getName() << " says take that in the name of my lord " << getBoss()->getName() << endl;
}
//swordsman
void Swordsman::fight() {
	cout << "CLANG! " << getName() << " says take that in the name of my lord " << getBoss()->getName() << endl;
}
//wizard
void Wizard::fight() {
	cout << "POOF!" << endl;
}
