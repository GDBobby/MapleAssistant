#pragma once

#include <fstream>
#include <string>
#include <iostream>
#include <vector>

struct SharpEyes {
	double crit = 0.15;
	double critDmg = 1.4;
};

bool isNumber(std::string s)
{
	for (int i = 0; i < s.length(); i++)
		if (isdigit(s[i]) == false)
			return false;

	return true;
}

struct skillData {
	std::string name;
	double percent;
	int lines;
	int mobCount;
	std::vector<double> speed;
};
struct comboData {
	std::vector<std::string> skillNames;
};

class JobStats { //object name is class;
	//24 items
	std::string jobName;
	//std::string skillName[4];

	double mastery;

	int skillNum = 0;
	int comboNum = 0;

	std::vector<skillData> skills;
	std::vector<comboData> combos;

	//double skillPerc[4];
	//int skillLines[4];
	//double wepSpeed[4][6];
	//int mobCount[4];

	double critChance;
	double critDmg;
	double modifier[4]; //holy, lightning, fire, ice

public:
	JobStats(std::ifstream &file) {
		std::string pass;

		if (file.is_open()) {

			file >> jobName;

			file >> pass;
			mastery = static_cast<double>(stoi(pass)) / 100;

			file >> pass;
			critChance = static_cast<double>(stoi(pass)) / 100;

			file >> pass;
			critDmg = static_cast<double>(stoi(pass)) / 100;

			for (int x = 0; x < 4; x++) {
				file >> pass;
				modifier[x] = static_cast<double>(stoi(pass)) / 100;
			}

			bool firstRead = true;
			while (pass != "endof" && pass != "combo") { //reads skills here, loops until endof read
				skillData tempSkill;

				if (firstRead) { file >> pass; }
				firstRead = true;
				tempSkill.name = pass;

				file >> pass;
				tempSkill.percent = static_cast<double>(stoi(pass)) / 100;

				file >> pass;
				tempSkill.lines = stoi(pass);

				file >> pass;
				tempSkill.mobCount = stoi(pass);

				for (int i = 0; i < 100; i++) {
					file >> pass;
					if (isNumber(pass)) {
						tempSkill.speed.push_back(static_cast<double>(stoi(pass)));
					}
					else { firstRead = false; break; }
				}

				skills.push_back(tempSkill);
				skillNum++;
			}
			while (pass == "combo") {
				file >> pass;
				comboData tempCombo;
				while (pass != "combo" && pass != "endof") {
					tempCombo.skillNames.push_back(pass);
					file >> pass;
				}
				if (tempCombo.skillNames.size() > 0) {
					combos.push_back(tempCombo);
				}
				comboNum++;
			}


		}

		/**
		std::cout << jobName << " : " << mastery << " : " << critChance << " : " << critDmg << std::endl;


		for (int i = 0; i < skills.size(); i++) {
			std::cout << skills[i].name << " : " << skills[i].percent << " : " << skills[i].lines << " : " << skills[i].mobCount << std::endl;


			for (int ii = 0; ii < skills[i].speed.size(); ii++) {
				std::cout << skills[i].speed[ii] << " : ";
			}
			std::cout << std::endl;
		}
		
		for (int i = 0; i < combos.size(); i++) {
			std::cout << "combo" << std::endl;
			for (int ii = 0; ii < combos[i].skillNames.size(); ii++) {
				std::cout << combos[i].skillNames[ii] << " : ";
			}
		}
		std::cout << std::endl << "endof" << std::endl;
		*/
	}

	/*   legacy code?
	void setJobName(std::string a) { jobName = a; }
	void setMastery(std::string a) { mastery = static_cast<double>(stoi(a)) / 100; }
	void setSkillName(int a, std::string b) { skillName[a] = b; } // a is name, b is array loc
	void setSkillPerc(int a, std::string b) { skillPerc[a] = static_cast<double>(stoi(b)); } //a is value, b is array loc
	void setSkillLines(int a, std::string b) { skillLines[a] = stoi(b); } //a is value, b is array loc
	void setMobCount(int a, std::string b) { mobCount[a] = stoi(b); }
	void setCritChance(std::string a) { critChance = static_cast<double>(stoi(a)); }
	void setCritDmg(std::string a) { critDmg = static_cast<double>(stoi(a)); }
	void setModifier(std::string a, int b) { modifier[b] = static_cast<double>(stoi(a)) / 100; }
	void setWepSpeed(int a, int b, std::string c) { wepSpeed[a][b] = static_cast<double>(stoi(c)) / 1000; }
	*/


	std::string getJobName() { return jobName; }
	std::string getSkillName(int a) { return skills[a].name; }

	double getSkillPerc(int a) { return skills[a].percent; }

	double getMastery() { return mastery; }

	int getModifier(int a) { return modifier[a]; }

	double getSkillMobs(int a) { return skills[a].mobCount; }

	double getSpeed(int skillID, int spd) {
		return skills[skillID].speed[spd];
	}

	skillData getSkillData(int a) {
		return skills[a];
	}
	std::string getComboSkillName(int comboNum, int skillNum) {
		return combos[comboNum].skillNames[skillNum];
	}
	int getComboSize(int a) {
		return combos[a].skillNames.size();
	}

	int getSkillNum() {
		return skillNum;
	}
	int getComboNum() {
		return comboNum;
	}

	bool getSpammable(int skillID) {
		if (skills[skillID].speed.size() == 6) { return false; }
		else return true;
	}

	double getDPSValue(int skillID, SharpEyes se) {
		// ((percent + critdmg) * critchance + percent * (1-critchance) * lines * (modifiers / 100)
		double dpsValue;

		double modTotal = (modifier[0] * modifier[1] * modifier[2] * modifier[3]);

		dpsValue = (((skills[skillID].percent + critDmg + se.critDmg) * (critChance + se.crit)) + (skills[skillID].percent * ((1 - se.crit) - critChance))) * static_cast<double>(skills[skillID].lines) * modTotal;

		return dpsValue;
	}

	double getPalaDPS(int skillID, int eleType, SharpEyes se) {
		// ((percent + critdmg) * critchance + percent * (1-critchance) * lines * (modifiers / 100)
		double eleMod = 0;
		double dpsValue;

		eleMod = modifier[eleType];

		dpsValue = (((skills[skillID].percent + critDmg + se.critDmg) * (critChance + se.crit)) + (skills[skillID].percent * ((1 - se.crit) - critChance))) * static_cast<double>(skills[skillID].lines) * eleMod;

		return dpsValue;
	}

	double calcMagicMax(int iMagic, int iIntel, int skillID, SharpEyes se) {
		double magic = static_cast<double>(iMagic);
		double intel = static_cast<double>(iIntel);
		double modTotal = modifier[0] * modifier[1] * modifier[2] * modifier[3];

		double magicMax = ((magic*magic / 1000 + magic) / 30 + (intel / 200)) * skills[skillID].percent * 100 * static_cast<double>(skills[skillID].lines) * modTotal;
		return magicMax;
	}
	double calcMagicMin(int iMagic, int iIntel, int skillID, SharpEyes se) {
		double magic = static_cast<double>(iMagic);
		double intel = static_cast<double>(iIntel);
		double modTotal = modifier[0] * modifier[1] * modifier[2] * modifier[3];

		double magicMin = (((magic*magic / 1000 + magic) * mastery * .9) / 30 + (intel / 200)) * skills[skillID].percent * 100 * static_cast<double>(skills[skillID].lines) * modTotal;

		return magicMin;
	}
	double calcMagicDPS(int magic, int intel, int skillID, SharpEyes se) {
		double modTotal = modifier[0] * modifier[1] * modifier[2] * modifier[3];

		double magicDps = ((magic*magic / 1000 + magic * (1 + mastery * .9) / 2) / 30 + (intel / 200)) * (((skills[skillID].percent * 100 + se.critDmg * 100) * se.crit) + skills[skillID].percent * 100 * (1 - se.crit)) * static_cast<double>(skills[skillID].lines) * modTotal;


		return magicDps;
	}

	double getBarrDPS(int skillID, SharpEyes se) {
		// ((percent + critdmg) * critchance + percent * (1-critchance) * lines * (modifiers / 100)
		double dpsValue;
		double barrPerc = skills[skillID].percent * 10 / 6;
		double modTotal = modifier[0] * modifier[1] * modifier[2] * modifier[3];

		dpsValue = (((barrPerc + critDmg + se.critDmg) * (critChance + se.crit)) + (barrPerc * ((1 - se.crit) - critChance))) * static_cast<double>(skills[skillID].lines) * modTotal;

		return dpsValue;
	}

};