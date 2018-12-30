//Logan Semenuk- This program takes in a string of commands which create
//nobles and warriors on the heap which can then interact with eachother as 
//outlined by the methods in the noble class.
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
	{hired = false;}//default not hired
	string getName() const {
		return name;
	}
	int getStrength() const {
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
				return;
			}
		}//warrior does not exist if fun doesnt  return
		cerr << hiredWarrior << " does not exist." << endl;
	}
	void fire(string warrName, vector<Warrior*>& unemployed) {
		for(int i = 0; i < army.size(); i++) {
			if(army[i] -> getName() == warrName) {
				cout << "You dont work for me anymore -- " << name << endl;
				army[i] -> setHire(false);
				army.erase(army.begin() + i);
				return;
			}
		}//warrior does not belong to noble army if func doesnt return above
		cerr << warrName << " does not belong to this noble." << endl;
	}
	int getArmyStrength() const {
		int totalStrength = 0;
		for(Warrior* warrior: army) {
			totalStrength += warrior -> getStrength();
		}//returns addition of army stren
		return totalStrength;
	}
	void reduceArmyStrength(double val) {//required double because wont always be an int
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
		else if(alive == false && nobleToBattle->alive == false) {//both dead
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
		else if(army1Strength > army2Strength) {//army1 beats army2
			cout << name << " defeats " <<nobleToBattle -> getName() <<endl;
			double reduction = (1 - (army2Strength / army1Strength));
			reduceArmyStrength(reduction);	//winning army str reduced by reduction
			nobleToBattle -> alive = false;//noble dies
			nobleToBattle -> defeated();//losing armies warriors die
		}
		else if(army2Strength > army1Strength) {//army2 beats army1
			cout << nobleToBattle -> name << " defeats  " << name << endl;
			double reduction = (1.0 - (army1Strength / army2Strength));
			nobleToBattle -> reduceArmyStrength(reduction);
			alive = false;
			defeated();
		}
		else if(army1Strength == army2Strength) {//armies are equal and draw
			cout << "Mutual annihilation " << name << " and " << nobleToBattle -> name <<
				" die at eachothers hands." << endl;
			alive = false;
			nobleToBattle -> alive = false;
			defeated();
			nobleToBattle -> defeated();
		}
		
	}
	void defeated() {//losing army warriors all die
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
		if(warrior -> getName() == warriorName) {//check for duplicate
			cerr << "This warrior already exists." << endl;
			return;
		}
	}
	outOfWork.push_back(new Warrior(warriorName, warriorStrength));
}
void addNoble(ifstream& nobleWarriors, vector<Noble*>& nobles) {
	string nobleName;
	nobleWarriors >> nobleName;
	for(Noble*& noble: nobles) {
		if(noble  -> getName() == nobleName) {//check for duplicate
			cerr << "This noble	already exists." << endl;
			return;
		}
	}
	nobles.push_back(new Noble(nobleName));
}
void status(const vector<Noble*>& nobleVec) {
	cout <<  "Status" << endl << "======" << endl << "Nobles: " << endl;
	for(Noble* noble: nobleVec) {
		cout << *noble;//warrior and noble overloaded ouput
	}
}
void clearWarr(vector<Warrior*>& warrToDel) {
	for(Warrior* warr: warrToDel) {
		delete warr;
	}
}
void clearNoble(vector<Noble*> nobleToDel) {
	for(Noble* noble: nobleToDel) {
		delete noble;
	}
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
			int flag = 0;
			for(int i = 0; i < nobles.size(); i++) {
				if (nobles[i] -> getName() == noble) {
					flag++;
					nobles[i] -> fire(warrior, outOfWork);
					break;
				}
			}
			if(flag == 0) {
				cout << "Noble does not exist." << endl;
			}
		}
		else if(command == "Battle") {
			string nameNoble1, nameNoble2;
			Noble* noble1;
			Noble* noble2;
			nobleWarriors >> nameNoble1 >> nameNoble2;
			int flag = 0; //checking if both nobles exist else error
			for(Noble* noble: nobles) {
				if(noble -> getName() == nameNoble1){
					noble1 = noble;
					flag++;
					break;
				}
			}
			for(Noble* noble: nobles) {
				if(noble -> getName() == nameNoble2){
					noble2 = noble;
					flag++;
					break;
				}
			}
			if(flag == 2) {
			noble1 -> battle(noble2);
			}
			else {//One of the nobles doesnt exist
				cout << "Your nobles don't exist, skipping" << endl;
			}
		}
		else if(command == "Status") {
			status(nobles);
		}
		else if(command == "Clear") {
			clearWarr(outOfWork);
			clearNoble(nobles);
		}
		else {
			cout << "Invalid command. Skipping and moving to next valid command." << endl;
			char c;
			while(nobleWarriors >> c) {//if command not recognized moves stream to next line
			if(c == EOF)
				break;
			}
		}
	}
	nobleWarriors.close();
}

