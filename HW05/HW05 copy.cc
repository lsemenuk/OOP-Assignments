#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class Noble;

class Warrior {//defining the warrior class
	friend ostream& operator<<(ostream& os, const Warrior& warrToDisp); 
public:
	Warrior (const string& name, int strength); 
	string getName() const;
	int getStrength() const;
	void setStrength(int stren);
	void fired();
	bool getHireStatus() const; 
	void hired(Noble* working); 
	void runaway();
private:
	string name;
	double strength;
	Noble* employer;
};

class Noble {//noble class
	friend ostream& operator<<(ostream& os, const Noble& rhs); 
public:
	Noble (const string& name);
	bool hire(Warrior& warriorToAdd); 
	int findWarr(const Warrior& warrToFind) const; 
	bool run(Warrior& warriorToRun); //checks to see if warrior can be fired
	bool fire(Warrior& warriorToFire); //checks to see if warrior can be fired
	void display() const;//prints noble anc calls warrior overloaded ouput
	double getArmystrength() const; 
	void reduceArmyStrength(double val); 
	void battle(Noble& nobleToBattle); 
private:
	string name;
	vector<Warrior*> army; 
	bool alive;
};


int main() {
    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");
	
    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);
	
    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
	
    cout << jim << endl;
    cout << lance << endl;
	cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;

    cheetah.runaway();
    cout << art << endl;
	
    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
}

//Warrior Methods
ostream& operator<<(ostream& os, const Warrior& warrToDisp) {
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

//Noble methods
ostream& operator<<(ostream& os, const Noble& rhs) {
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
