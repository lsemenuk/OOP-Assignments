#ifndef NOBLE_H
#define NOBLE_H
#include<string>
#include<vector>
#include<iostream>

namespace WarriorCraft {
	class Warrior;
	class Noble {//noble class
		friend std::ostream& operator<<(std::ostream& os, const Noble& rhs); 
		public:
		Noble (const std::string& name);
		bool hire(Warrior& warriorToAdd); 
		int findWarr(const Warrior& warrToFind) const; 
		bool run(Warrior& warriorToRun); //checks to see if warrior can be fired
		bool fire(Warrior& warriorToFire); //checks to see if warrior can be fired
		void display() const;//prints noble anc calls warrior overloaded ouput
		double getArmystrength() const; 
		void reduceArmyStrength(double val); 
		void battle(Noble& nobleToBattle); 
		private:
		std::string name;
		std::vector<Warrior*> army; 
		bool alive;
	};
}
#endif
