#ifndef NOBLE_H
#define NOBLE_H
#include <string>
#include <vector>
#include <iostream>


namespace WarriorCraft {
	class Protector;
	class Noble {
		public:
			Noble(const std::string& name);
			virtual double getStrength() const = 0;
			virtual void reduceStrength(double multiplier) = 0;
			void battle(Noble& nobleToBattle);
			std::string getName() const;
			virtual void toBattle() const;
		private:
			std::string name;
			bool alive;
		protected:
			bool getAlive() const;
	}; 

	class PersonWithStrengthToFight : public Noble {
		public:
			PersonWithStrengthToFight(const std::string& name, double strength);
			double getStrength() const;
			void reduceStrength(double multiplier);
		private:
			double strength;
	};

	class Lord : public Noble {
		public:
			Lord(const std::string& name);
			double getStrength() const;
			void hires(Protector& protectorToHire);
			void reduceStrength(double multiplier);
			void toBattle() const;
			void removeFighter(Protector* quitter); 
		private:
			std::vector<Protector*> protectors;
	};
}
#endif
