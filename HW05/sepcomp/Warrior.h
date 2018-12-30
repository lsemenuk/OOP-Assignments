#ifndef WARRIOR_H
#define WARRIOR_H
#include<string>
#include<iostream>

namespace WarriorCraft {
	class Noble;
	class Warrior {//defining the warrior class
		friend std::ostream& operator<<(std::ostream& os, const Warrior& warrToDisp); 
		public:
		Warrior (const std::string& name, int strength); 
		std::string getName() const;
		int getStrength() const;
		void setStrength(int stren);
		void fired();
		bool getHireStatus() const; 
		void hired(Noble* working); 
		void runaway();
		private:
		std::string name;
		double strength;
		Noble* employer;
	};
}
#endif
