#include <vector>
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

class Warrior {
	friend ostream& operator<<(ostream& os, const Warrior& nameFromWarrior);
	class Weapon {
		friend ostream& operator<<(ostream& os, const Warrior& nameFromWarrior);
		string weaponName;
		int weaponStrength;
	public:
		void setName(const string& wepName) {
			weaponName = wepName;
		}
		void setStrength(const int wepStrength) {
			weaponStrength = wepStrength;
		}
		int getStrength() {
			return weaponStrength;
		}
	};
	string warriorName;
	Weapon warriorWeapon;
public:
	Warrior(const string& warrname, const string& wepname, int wepstren) {
		warriorName = warrname;
		warriorWeapon.setName(wepname);
		warriorWeapon.setStrength(wepstren);
	}
	string getWarriorName() const {
		return warriorName;
	}
	int getwepStrength() {
		return warriorWeapon.getStrength();
	}
	void setWepStrength(int str) {
		warriorWeapon.setStrength(str);
	}
};

//overloading cout to print warr name
ostream& operator<<(ostream& os, const Warrior& nameFromWarrior) {
    os << "Warrior: " << nameFromWarrior.warriorName << ", weapon: " << 
	nameFromWarrior.warriorWeapon.weaponName << ", " << 
	nameFromWarrior.warriorWeapon.weaponStrength;
    return os;
	}
//checking for valid stream
bool streamIntegrity(const string& fileName) {
	if (!ifstream(fileName)) {
		cerr << "There was an error opening " << fileName << endl;
		return false;
	}
	return true;
}

//adding a warrior
void addWarrior(ifstream& warriorFile, vector<Warrior>& warriors ) {
	string warrName;
	string wepName;
	int wepStrength;
	warriorFile >> warrName >> wepName >> wepStrength;
	Warrior newWarrior(warrName, wepName, wepStrength);
	warriors.push_back(newWarrior);
}

void status(const vector<Warrior>& vOfWarriors) {
	cout << "There are: " << vOfWarriors.size() << " Warriors" << endl;
	for(const Warrior& x: vOfWarriors) {
		cout << x << endl;
	}
}
// find each warrior in the list to help the battle function
vector<int> getWarriorInd(const string& fighter1, const string& fighter2, 
const vector<Warrior>& warriors) {
    vector<int> warriorInd;
    for(int i = 0; i < warriors.size(); i++) { //loop through to get the first warrior
        if(warriors[i].getWarriorName() == fighter1) {
            warriorInd.push_back(i);
            break;
        }
    }

    for(int j = 0; j < warriors.size(); j++) { //loop through to get the second warrior
        if(warriors[j].getWarriorName() == fighter2) {
            warriorInd.push_back(j);
            break;
        }
    }
    return warriorInd;
}

void battle(ifstream& warriorTxt, vector<Warrior>& warriors) {
	string fighter1, fighter2;
	warriorTxt >> fighter1 >> fighter2;
	vector<int> warriorId = getWarriorInd(fighter1, fighter2, warriors);
	int warr1 = warriorId[0], warr2 = warriorId[1];
	cout << fighter1 << " battles " << fighter2 << endl;

	if(warriors[warr1].getwepStrength() == 0 && warriors[warr2].getwepStrength() == 0) {
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
        
    } //draw each warrior has 0 stren
    else if(warriors[warr1].getwepStrength() == warriors[warr2].getwepStrength()) { 
        cout << "Mutual annihilation " << fighter1 << " and " << fighter2 <<
		 " die at each other's hands" << endl;
        warriors[warr1].setWepStrength(0);
        warriors[warr2].setWepStrength(0);
    } //warr 1 wins
    else if(warriors[warr1].getwepStrength() > warriors[warr2].getwepStrength() && 
	warriors[warr2].getwepStrength() != 0) {
        cout << fighter1 << " defeats " << fighter2 << endl;
        warriors[warr1].setWepStrength(warriors[warr1].getwepStrength() - 
		warriors[warr2].getwepStrength());
        warriors[warr2].setWepStrength(0);
    } // warr 2 wins
    else if(warriors[warr2].getwepStrength() > warriors[warr1].getwepStrength() && 
	warriors[warr1].getwepStrength() != 0) {
        cout << fighter2 << " defeats " << fighter1 << endl;
        warriors[warr2].setWepStrength(warriors[warr2].getwepStrength() - 
		warriors[warr1].getwepStrength());
        warriors[warr1].setWepStrength(0);
    } //warr 2 already dead
    else if(warriors[warr1].getwepStrength() > 0 && warriors[warr2].getwepStrength() == 0) { 
        cout << "He's dead, " << fighter1 << endl;
        
    } //warr 1 already dead
    else if(warriors[warr2].getwepStrength() > 0 && warriors[warr1].getwepStrength() == 0) { 
        cout << "He's dead, " << fighter2 <<  endl;
        
    }

}

int main () {
	string fileName = "warriors2.txt";
	streamIntegrity(fileName);
	ifstream warriorStream(fileName);
	vector<Warrior> vOfWarriors;
	string command;


	while(warriorStream >> command) {
        if(command == "Warrior") {
            addWarrior(warriorStream, vOfWarriors);
        }
        else if(command == "Status") {
            status(vOfWarriors);
        }
        else if(command == "Battle") {
            battle(warriorStream, vOfWarriors);
        }
    }
}
