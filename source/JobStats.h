#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <windows.h>


class JobStats { //object name is class;
	//24 items
	std::string jobName;
	std::string skillName[4];

	double mastery;

	int skillPerc[4];
	int skillLines[4];

	int critChance;
	int critDmg;
	int modifier[4]; //holy, lightning, fire, ice

	int weaponatt = 100;
	int dpsValue;

public:

	LPCWSTR getJobName() {
		return (LPCWSTR)jobName.c_str();
	}
	void setJobName(std::string a) { a.c_str(); }
	void setMastery(std::string a) { mastery = static_cast<double>(stoi(a)) / 100; }

	void setSkillName(int a, std::string b) { skillName[a] = b; } // a is name, b is array loc 
	void setSkillPerc(int a, std::string b) { skillPerc[a] = stoi(b); } //a is value, b is array loc
	void setSkillLines(int a, std::string b) { skillLines[a] = stoi(b); } //a is value, b is array loc

	std::string getSkillName(int a) {
		return skillName[a];
	}

	double getSkillPerc(int a) {
		return static_cast<double>(skillPerc[a]) / 100;
	}

	void setCritChance(std::string a) { critChance = stoi(a); }
	void setCritDmg(std::string a) { critDmg = stoi(a); }


	void setModifier(std::string a, int b) { modifier[b] = stoi(a); }

	void setWeaponAtt(std::string a) { weaponatt = stoi(a); }

	double getMastery() { return mastery; }

	int getModifier(int a) { return modifier[a]; }

	double getDPSValue(int skillID, int se[]) {
		// ((percent + critdmg) * critchance + percent * (1-critchance) * lines * (modifiers / 100) ~~~ wepspeed is in another object, applied separately
		double dpsValue;

		double modTotal = (static_cast<double>(modifier[0]) * static_cast<double>(modifier[1]) * static_cast<double>(modifier[2]) * static_cast<double>(modifier[3])) / 100000000;

		dpsValue = (((static_cast<double>(skillPerc[skillID]) + static_cast<double>(critDmg) + se[1]) * static_cast<double>(critChance + se[0]) / 100)
			+ (static_cast<double>(skillPerc[skillID]) * ((100 - se[0]) - static_cast<double>(critChance)) / 100)) / 100
			* static_cast<double>(skillLines[skillID]) * modTotal;

		return dpsValue;
	}

	double getPalaDPS(int skillID, int eleType, int se[]) {
		// ((percent + critdmg) * critchance + percent * (1-critchance) * lines * (modifiers / 100) ~~~ wepspeed is in another object, applied separately
		double eleMod = 0;
		double dpsValue;

		eleMod = static_cast<double>(modifier[eleType]) / 100;

		dpsValue = (((static_cast<double>(skillPerc[skillID]) + static_cast<double>(critDmg) + se[1]) * static_cast<double>(critChance + se[0]) / 100)
			+ (static_cast<double>(skillPerc[skillID]) * ((100 - se[0]) - static_cast<double>(critChance)) / 100)) / 100
			* static_cast<double>(skillLines[skillID]) * eleMod;

		return dpsValue;
	}

	double calcMagicMax(int magic, int intel, int skillID, int se[]) {
		double modTotal = static_cast<double>(modifier[0]) / 100 * static_cast<double>(modifier[1]) / 100 * static_cast<double>(modifier[2]) / 100 * static_cast<double>(modifier[3]) / 100;

		double magicMax = ((static_cast<double>(magic)*static_cast<double>(magic) / 1000 + static_cast<double>(magic)) / 30 + (static_cast<double>(intel) / 200))
			* static_cast<double>(skillPerc[skillID]) * static_cast<double>(skillLines[skillID]) * modTotal;
		return magicMax;
	}
	double calcMagicMin(int magic, int intel, int skillID, int se[]) {
		double modTotal = static_cast<double>(modifier[0]) / 100 * static_cast<double>(modifier[1]) / 100 * static_cast<double>(modifier[2]) / 100 * static_cast<double>(modifier[3]) / 100;

		double magicMin = ((static_cast<double>(magic)*static_cast<double>(magic) / 1000 + static_cast<double>(magic) * mastery * .9) / 30 + (static_cast<double>(intel) / 200)) 
			* static_cast<double>(skillPerc[skillID]) * static_cast<double>(skillLines[skillID]) * modTotal;

		return magicMin;
	}
	double calcMagicDPS(int magic, int intel, int skillID, int se[]) {
		double modTotal = static_cast<double>(modifier[0]) / 100 * static_cast<double>(modifier[1]) / 100 * static_cast<double>(modifier[2]) / 100 * static_cast<double>(modifier[3]) / 100;

		double magicDps = ((static_cast<double>(magic)*static_cast<double>(magic) / 1000 + static_cast<double>(magic) * (1 + mastery * .9) / 2) / 30 + (static_cast<double>(intel) / 200)) 
			* (((static_cast<double>(skillPerc[skillID]) + se[1]) * se[0] / 100) + static_cast<double>(skillPerc[skillID]) * (100 - se[0]) / 100) * static_cast<double>(skillLines[skillID]) * modTotal;


		return magicDps;
	}

	double getBarrDPS(int skillID, int se[]) {
		// ((percent + critdmg) * critchance + percent * (1-critchance) * lines * (modifiers / 100) ~~~ wepspeed is in another object, applied separately
		double dpsValue;
		double temp = static_cast<double>(skillPerc[skillID]) * 10 / 6;
		double modTotal = (static_cast<double>(modifier[0]) * static_cast<double>(modifier[1]) * static_cast<double>(modifier[2]) * static_cast<double>(modifier[3])) / 100000000;

		dpsValue = (((temp + static_cast<double>(critDmg) + se[1]) * static_cast<double>(critChance + se[0]) / 100)
			+ (temp * ((100 - se[0]) - static_cast<double>(critChance)) / 100)) / 100
			* static_cast<double>(skillLines[skillID]) * modTotal;

		return dpsValue;
	}

};