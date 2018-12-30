#ifndef PROTECTOR_H
#define PROTECTOR_H
#include <string>
#include <iostream>
#include <vector>

namespace WarriorCraft {
	class Noble;
	class Lord;
	class Protector {
		public:
			Protector(const std::string& name, double strength);
			double getStrength() const;
			bool getHired() const; 
			void setHire(Lord* bossLord);
			void setStrength(double num);
			virtual void fight() = 0;
			void quit();
		private:
			std::string name;
			double strength;
			Lord* boss;
			bool alive;
		protected:
			std::string getName() {return name;}
			Lord* getBoss() {return boss;}
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

}
#endif
