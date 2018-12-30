#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class Warrior {
	friend ostream& operator<<(ostream& os, const Warrior& warrToDisplay) {
		os << warrToDisplay.name << ": " << warrToDisplay.strength << endl;
		return os;
	}
public:
	Warrior(const string& name, int strength) : name(name), strength(strength)
	{hired = false;}
	string getName() const {
		return name;
	}
	int getStrength() {
		return strength;
	}
	void setStrength(int stren) {
		strength = stren;
	}
	bool getHire() const {
		return hired;
	}
	void setHire(bool isHired) { 
		hired = isHired;
	}

private:
	string name;
	double strength;
	bool hired;
};

class Noble {
	friend ostream& operator<<(ostream& os, const Noble& nobleToDisplay) {
		os << nobleToDisplay.name << " has an army of " << nobleToDisplay.army.size() << endl;
		for(Warrior* warrToDisplay: nobleToDisplay.army) {
			os << *warrToDisplay;
		}
		return os;
	}
	friend void clear(vector<Noble*>& nobleToDel);
public:
	Noble(const string& name) : name(name) {alive = true;}
	string getName() const {
		return name;
	}
	void hire(const string& hiredWarrior, vector<Warrior*> unemployed) {
		for(int i = 0; i < unemployed.size(); i++) {
			if(unemployed[i] -> getName() == hiredWarrior) {
				unemployed[i] -> setHire(true);
				army.push_back(unemployed[i]);
				unemployed.erase(unemployed.begin() + i);

			}
		}
	}
	void fire(string warrName, vector<Warrior*>& unemployed) {
		for(int i = 0; i < army.size(); i++) {
			if(army[i] -> getName() == warrName) {
				cout << "You dont work for me anymore -- " << name << endl;
				army[i] -> setHire(false);
				unemployed.push_back(army[i]);
				army.erase(army.begin() + i);
				return;
			}
		}
	}
	int getArmyStrength() {
		int totalStrength = 0;
		for(Warrior* warrior: army) {
			totalStrength += warrior -> getStrength();
		}
		return totalStrength;
	}
	void reduceArmyStrength(double val) {
		for(Warrior*& warr: army) {
			double tmpStr = (warr -> getStrength() * val);
			warr -> setStrength(tmpStr);
		}
	}
	void battle(Noble* nobleToBattle) {
		double army1Strength = getArmyStrength();	
		double army2Strength = nobleToBattle -> getArmyStrength();
		cout << name << " battles " << nobleToBattle -> name << endl;
		if(alive == true && nobleToBattle -> alive == false) {
			cout << "he's dead, " << name << endl;
		}
		else if(alive == false && nobleToBattle->alive == true) {
			cout <<" he's dead, " << nobleToBattle->name << endl;
		}
		else if(alive == false && nobleToBattle->alive == false) {
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
		else if(army1Strength > army2Strength) {
			cout << name << " defeats " <<nobleToBattle -> getName() <<endl;
			double reduction = (1 - (army2Strength / army1Strength));
			reduceArmyStrength(reduction);	
			nobleToBattle -> alive = false;
			nobleToBattle -> defeated();
		}
		else if(army2Strength > army1Strength) {
			cout << nobleToBattle -> name << " defeats  " << name << endl;
			double reduction = (1.0 - (army1Strength / army2Strength));
			nobleToBattle -> reduceArmyStrength(reduction);
			alive = false;
			defeated();
		}
		else if(army1Strength == army2Strength) {
			cout << "Mutual annihilation " << name << " and " << nobleToBattle -> name <<
				" die at eachothers hands." << endl;
			alive = false;
			nobleToBattle -> alive = false;
			defeated();
			nobleToBattle -> defeated();
		}
		
	}
	void defeated() {
		for(Warrior* warr: army) {
			warr -> setStrength(0);
		}
	}
private:
	string name;
	vector<Warrior*> army;
	bool alive;
};
//check stream
bool streamIntegrity(const string& fileName) {
	if (!ifstream(fileName)) {
			cerr << "There was an error opening " << fileName << endl;
			return false;
		}
	return true;
}
//create warrior
void addWarrior(ifstream& nobleWarriors, vector<Warrior*>& outOfWork) {
	string warriorName;
	int warriorStrength;
	nobleWarriors >> warriorName >> warriorStrength;
	for(Warrior*& warrior: outOfWork) {
		if(warrior -> getName() == warriorName) {
			cerr << "This warrior already exists." << endl;
			return;
		}
	}

	//Warrior warriorToAdd(warriorName, warriorStrength);
	outOfWork.push_back(new Warrior(warriorName, warriorStrength));
}
void addNoble(ifstream& nobleWarriors, vector<Noble*>& nobles) {
	string nobleName;
	nobleWarriors >> nobleName;
	for(Noble*& noble: nobles) {
		if(noble  -> getName() == nobleName) {
			cerr << "This noble	already exists." << endl;
			return;
		}
	}
	nobles.push_back(new Noble(nobleName));
}
bool nobleInNobles(const string& name, vector<Noble*>& nobles) {
	for(Noble*& noble:nobles) {
		if(noble -> getName() == name) {
			return true;
		}
	}
		return false;
}
bool warrNotHire(const string& name, vector<Warrior*>& warriors) {
	for(Warrior*& warrior:warriors) {
		if(warrior -> getName() == name && warrior -> getHire() == false) {
			return true;
		}
	}
		return false;
}
int findNoble(const string& name, const vector<Noble*>& nobles) {
	for(int i = 0; i<nobles.size(); i++) {
		if(nobles[i] -> getName() == name) {
			return i;
		}
	}
	return -1;
}
int findWarr(const string& name, const vector<Warrior*>& warriors) {
	for(int i = 0; i<warriors.size(); i++) {
		if(warriors[i] -> getName() == name) {
			return i;
		}
	}
	return -1;
}
void removeFromOutOfWork(const string& warrName, vector<Warrior*> toRemove){
	int indToErase;
	for(int i = 0; i < toRemove.size(); i++) {
		if(toRemove[i] -> getName() == warrName) {
			indToErase = i;
			Warrior* tmp = toRemove[toRemove.size()-1];
			toRemove[toRemove.size()-1] = toRemove[indToErase];
			toRemove[indToErase] = tmp;
			toRemove.pop_back();
			break;
		}
	}
}
void status(vector<Noble*> nobleVec) {
	cout <<  "Nobles:" << endl << "======" << endl;
	for(Noble* noble: nobleVec) {
		cout << *noble;
	}
}
void clear(vector<Noble*>& nobleToDel) {
	for(Noble* noble: nobleToDel) {
		for(Warrior* warr: noble -> army) {
			delete warr;
		}
	}
	for(Noble* noble: nobleToDel) {
		delete noble;	
	}
	nobleToDel.clear();
}
int main() {
	string fileName = "nobleWarriors.txt";
	if(streamIntegrity(fileName) != true) {
		throw exception();
	}	
	ifstream nobleWarriors(fileName);
	vector<Noble*> nobles;
	vector<Warrior*> outOfWork;
	string command;

	while(nobleWarriors >> command) {
		if(command == "Noble") {
			addNoble(nobleWarriors, nobles);
		}
		else if(command == "Warrior") {
			addWarrior(nobleWarriors, outOfWork);
		}
		else if(command == "Hire") {
			string noble;
			string warr;
			nobleWarriors >> noble >> warr;
			for(int i = 0; i < nobles.size(); i++) {
				if(nobles[i] -> getName() == noble) {
					nobles[i] -> hire(warr, outOfWork);
						break;
				}
			}
		}	
		else if(command == "Fire") {
			string noble;
			string warrior;
			nobleWarriors >> noble >>  warrior;
			for(int i = 0; i < nobles.size(); i++) {
				if (nobles[i] -> getName() == noble) {
					nobles[i] -> fire(warrior, outOfWork);
					break;
				} 
			}
		}
		else if(command == "Battle") {
			string nameNoble1, nameNoble2;
			Noble* noble1;
			Noble* noble2;
			nobleWarriors >> nameNoble1 >> nameNoble2;
			for(Noble* noble: nobles) {
				if(noble -> getName() == nameNoble1){
					noble1 = noble;
					break;
				}
			}
			for(Noble* noble: nobles) {
				if(noble -> getName() == nameNoble2){
					noble2 = noble;
					break;
				}
			}
			noble1 -> battle(noble2);
		}
		else if(command == "Status") {
			status(nobles);
		}
		else if(command == "Clear") {
			clear(nobles);
		}
		else {
			cout << "Invalid Command Skipping" << endl;
			fstream move;
			//getline(nobleWarriors, move);
		}
	}
}

