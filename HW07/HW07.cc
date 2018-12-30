#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Protector;

class Noble {
public:
	Noble(const string& name);
	virtual double getStrength() const = 0;
	virtual void reduceStrength(double multiplier) = 0;
	void battle(Noble& nobleToBattle);
	string getName() const;
	virtual void toBattle() const;
private:
	string name;
	bool alive;
protected:
	bool getAlive() const;
}; 

class PersonWithStrengthToFight : public Noble {
public:
	PersonWithStrengthToFight(const string& name, double strength);
	double getStrength() const;
	void reduceStrength(double multiplier);
private:
	double strength;
};

class Lord : public Noble {
public:
	Lord(const string& name);
	double getStrength() const;
	void hires(Protector& protectorToHire);
	void reduceStrength(double multiplier);
	void toBattle() const;
private:
	vector<Protector*> protectors;
};

class Protector {
public:
	Protector(const string& name, double strength);
	double getStrength() const;
	bool getHired() const; 
	void setHire(Lord* bossLord);
	void setStrength(double num);
	virtual void fight() = 0;
private:
	string name;
	double strength;
	Noble* boss;
	bool alive;
protected:
	string getName() {return name;}
	Noble* getBoss() {return boss;}
};

class Warrior : public Protector {
	using Protector::Protector;
};

class Wizard : public Protector {
	using Protector::Protector;
public:
	void fight();
};

class Swordsman : public Warrior {
	using Warrior::Warrior;
public:
	void fight();
};

class Archer : public Warrior {
	using Warrior::Warrior;
public:
	void fight();
};

int main() {
    Lord sam("Sam");
    Archer samantha("Samantha", 200);
    sam.hires(samantha);
    Lord joe("Joe");
    PersonWithStrengthToFight randy("Randolf the Elder", 250);
    joe.battle(randy);
    joe.battle(sam);
    Lord janet("Janet");
    Swordsman hardy("TuckTuckTheHardy", 100);
    Swordsman stout("TuckTuckTheStout", 80);
    janet.hires(hardy);
    janet.hires(stout);
    PersonWithStrengthToFight barclay("Barclay the Bold", 300);
    janet.battle(barclay);
    janet.hires(samantha);
    Archer pethora("Pethora", 50);
    Archer thora("Thorapleth", 60);
    Wizard merlin("Merlin", 150);
    janet.hires(pethora);
    janet.hires(thora);
    sam.hires(merlin);
    janet.battle(barclay);
    sam.battle(barclay);
    joe.battle(barclay);
}
//Noble methods
Noble::Noble(const string& name) : name(name) {alive = true;}
string Noble::getName() const {return name;}
bool Noble::getAlive() const {return alive;}
void Noble::toBattle() const {}
void Noble::battle(Noble& nobleToBattle) {
	double lhsNobleStren = getStrength();
	double rhsNobleStren = nobleToBattle.getStrength();
	cout << name << "battles " << nobleToBattle.name << endl;

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
		cout << name << " defeat s" << nobleToBattle.name << endl;
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
//Protector
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
