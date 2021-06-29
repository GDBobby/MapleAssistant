#include <fstream>
#include <string>
#include <iostream>

class WeaponStats {

	std::string weaponID;
	int multiplier;
	int multiplierL;
	int multiplierB;
	int skillSpeed[4][6];

public:

	void setWID(std::string a) {
		weaponID = a;
	}


	void setMultH(std::string a) {
		multiplier = stoi(a);
	}
	double getMult() {
		return static_cast<double>(multiplier) / 10;
	}

	double getMult(int a) {
		return static_cast<double>(multiplierL) / 10;
	}

	double getMultMagic(int wS, int skillSel) {
		if (wS == 0 && skillSel == 0) {
			return static_cast<double>(multiplier) / 100;
		}
		else if (wS == 1 && skillSel == 1) {
			return static_cast<double>(multiplier) / 100;
		}
		else if (wS == 1 && skillSel == 0) {
			return static_cast<double>(multiplierL) / 100;
		}
		else if (wS == 0 && skillSel == 1) {
			return static_cast<double>(multiplierL) / 100;
		}
		else {
			return 1;
			return true;
		}
	}

	void setMultL(std::string a) {
		multiplierL = stoi(a);
	}


	void setSS(std::string a, int b, int c) { //[b][c] = a
		skillSpeed[b][c] = stoi(a);
	}
	
	// [skill ID][speed ID, (0) is speed2, (4) is speed 6 (5) is spamming]
	// mage is	CL, Bliz
	//			para, meteor
	//			AR, genesis
	int getSS(int a, int b) { 
		return skillSpeed[a][b];
	}



};