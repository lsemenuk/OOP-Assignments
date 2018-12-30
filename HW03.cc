#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class Warrior {//defining the warrior class
public:
	friend ostream& operator<<(ostream& os, const Warrior& warrToDisp) {
		os << warrToDisp.name << ": " << warrToDisp.strength;
		return os;
	}
	Warrior (const string& name, int strength) : name(name), strength(strength) {hired = false;}
	bool getHireStatus() {
		return hired;
	}
	string getName()  {
		return name;
	}
	int getStrength() {
		return strength;
	}
	void setHireStatus(bool hireFire) {//shows if warrior is hired or not
		hired = hireFire;
	}
	void setStrength(int stren) {
		strength = stren;
	}
private:
	string name;
	int strength;
	bool hired;
};

class Noble {//noble class
public:
	Noble (const string& name) : name(name) {alive = true;}
	bool hire(Warrior& warriorToAdd) {
	if(warriorToAdd.getHireStatus() == false && alive == true) {
		army.push_back(&warriorToAdd);
		warriorToAdd.setHireStatus(true);
		return true;
	}
	else {
		return false;
	}
	}
	bool fire(Warrior& warriorToFire) {//checks to see if warrior can be fired
		int indToErase = -1;
		for(int i = 0; i<army.size();i++) {
			if(army[i] -> getName() == warriorToFire.getName()){
				indToErase = i;
				Warrior* tmp = army[army.size()-1];
				army[army.size()-1] = army[indToErase];
				army[indToErase] = tmp;
				break;
			}
		}
		if(indToErase == -1 || alive == false) {
			return false;
		}
		else {
			//army.erase(army.begin() + (indToErase-1));
			army[indToErase] -> setHireStatus(false);
			cout << warriorToFire.getName() << ", you are fired!--" << name << endl;
			army.pop_back();//popback warrior off cant use iterators
			return true;
		}
	}
	void display() {//prints noble anc calls warrior overloaded ouput
		cout << name << " has an army of " << army.size() << endl;
		for(const Warrior* warr: army) {
			cout << *warr << endl;
		}
	}
	int getArmystrength() {
		int armyStrength = 0;
		for(Warrior* warr: army) {
			armyStrength = armyStrength +(warr -> getStrength());
		}
		return armyStrength;
	}
	void reduceArmyStrength(int val) {
		for(Warrior* warr: army) {
			int tmpStr = warr -> getStrength();
			warr -> setStrength((tmpStr*val));
		} 
	}
	void battle(Noble& nobleToBattle) {
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
			reduceArmyStrength((army2Strength / army1Strength));
			nobleToBattle.alive = false;;
		}
		else if(army2Strength > army1Strength) {//noble2 beat noble 1
			cout << nobleToBattle.name << " defeats " << name << endl;
			nobleToBattle.reduceArmyStrength((army1Strength / army2Strength));
			alive = false;
		}
		else if(army1Strength == army2Strength) {//nobles equal both die
			cout << "Mutual annihilation " << name << " and " << nobleToBattle.name
				<< " die at eachothers hands." << endl;
			nobleToBattle.alive = false;
			alive = false;
		}
	} 
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

    jim.display();
    lance.display();
    art.display();
    linus.display();
    billie.display();

    art.fire(cheetah);
    art.display();

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);
}
