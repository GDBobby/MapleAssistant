#pragma once
#include <string>
#include <vector>
#include "JobStats.h"
#include <math.h>

struct damageData {
	double minRange;
	double maxRange;
	double min2Range = -1;
	double max2Range = -1;
	std::vector<double> DPS;
	std::vector<double> comboDPS;
};

enum jobs {
	bowmaster,
	marksman,
	windarcher,
	darkknight,
	hero,
	paladin,
	dawnwarrior,
	icelightning,
	firepoison,
	bishop,
	blazewizard,
	shadower,
	nightlord,
	nightwalker,
	bucc,
	corsair,
	thunderbreaker,
};

enum elements {
	none,
	holy,
	fire,
	lightning,
	ice,
	poison,
};

double minimum(double a, double b) {
	if (a > b) { return b; }
	else if (a <= b) { return a; }
}

struct charStats {
	double str;
	double dex;
	double intel;
	double luk;
	double watt;
	double matt;
	double mobCount;
};

double getMultMagic(int wepSel, int skillSel) {
	if (wepSel == 0 && skillSel == 0) {
		return static_cast<double>(1.25);
	}
	else if (wepSel == 1 && skillSel == 1) {
		return static_cast<double>(1.25);
	}
	else if (wepSel == 1 && skillSel == 0) {
		return static_cast<double>(1.05);
	}
	else if (wepSel == 0 && skillSel == 1) {
		return static_cast<double>(1.05);
	}
	else {
		return 1;
		return true;
	}
}

double eleApp(int classSel, int weakVal, int skillSel) {
	if (classSel == icelightning)
	{
		if (weakVal == lightning && skillSel == 0) {
			return 1.5;
		}
		else if (weakVal == ice && skillSel == 1) {
			return 1.5;
		}
	}
	if (classSel == firepoison)
	{
		if (weakVal == poison && skillSel == 0) {
			return 1.5;
		}
		else if (weakVal == fire && skillSel == 1) {
			return 1.5;
		}
	}
	if (classSel == bishop && weakVal == holy)
	{
		return 1.5;
	}
	return 1;
}



void calc(JobStats &job, charStats &stats, int classSel, int speedSel, int weakSel, bool seActive, int wepSel, damageData &returnData) {

	SharpEyes se;
	if (seActive) { se.crit = .15; se.critDmg = 1.4; }
	else { se.crit = 0; se.critDmg = 0; }

	double passDub;

	switch (classSel) {
	case bowmaster:		//bowmaster
	{
		returnData.maxRange = (stats.dex * 3.4 + stats.str) * stats.watt / 100;

		returnData.minRange = (stats.dex * 3.4 * .9 * job.getMastery() + stats.str) * stats.watt / 100;

		//hurricane
		double passDub1 = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(0, se) * 1000 / job.getSpeed(0, speedSel) * minimum(stats.mobCount, job.getSkillMobs(0));
		returnData.DPS.push_back(passDub1);

		//inferno/arrow rain
		passDub1 = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(1, se) * 1000 / job.getSpeed(1, speedSel) * minimum(stats.mobCount, job.getSkillMobs(1));
		if (weakSel == fire) { passDub1 *= 1.5; }
		returnData.DPS.push_back(passDub1);

		break;
	}
	case marksman:		//marksman
	{

		returnData.maxRange = (stats.dex * 3.6 + stats.str) * stats.watt / 100;

		returnData.minRange = (stats.dex * 3.6 * .9 * job.getMastery() + stats.str) * stats.watt / 100;

		//strafe
		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(0, se) * 1000 / job.getSpeed(0, speedSel) * minimum(stats.mobCount, job.getSkillMobs(0));
		returnData.DPS.push_back(passDub);

		//snipe
		//double snipeDPS = job.getSkillPerc(1) * 1000 / 15;
		double passDex = stats.dex;
		if (stats.dex < 500) {
			passDex = 500;
		}
		double passAtt = stats.watt;
		if (stats.watt < 50) {
			passAtt = 50;
		}

		double snipeDPS = (550000 + (240 * sqrt(passDex - 500) * pow((passAtt - 50),0.7))) * minimum(stats.mobCount, job.getSkillMobs(1));
		returnData.DPS.push_back(snipeDPS);

		//pierce
		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(2, se) * 1000 / job.getSpeed(2, speedSel) * 5 * (-1 + pow(1.2, minimum(stats.mobCount, job.getSkillMobs(2)))); //speed is skipped because attack speed is 1000ms
		returnData.DPS.push_back(passDub);

		//strafesnipe
		int strafesniperatio = floor((5000 - job.getSpeed(0, speedSel)) / job.getSpeed(0, speedSel));
		passDub = (((returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(0, se)) * minimum(stats.mobCount, job.getSkillMobs(0)) * strafesniperatio / 5) + snipeDPS * minimum(stats.mobCount, job.getSkillMobs(1));
		returnData.DPS.push_back(passDub);

		break;
	}
	case windarcher:
	{
		int windwalkDelay = 60;

		returnData.maxRange = (stats.dex * 3.4 + stats.str) * stats.watt / 100;

		returnData.minRange = (stats.dex * 3.4 * .9 * job.getMastery() + stats.str) * stats.watt / 100;

		//soh
		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(0, se) * 1000 / (job.getSpeed(0, speedSel) + windwalkDelay) * minimum(stats.mobCount, job.getSkillMobs(0));
		returnData.DPS.push_back(passDub);

		//other skill
		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(1, se) * 1000 / (job.getSpeed(1, speedSel) + windwalkDelay) * minimum(stats.mobCount, job.getSkillMobs(1));
		if (weakSel == holy) { passDub *= 1.5; }
		returnData.DPS.push_back(passDub);

		break;
	}

	case darkknight:		// dark knight
	{

		returnData.maxRange = (stats.str * 5 + stats.dex) * stats.watt / 100;

		returnData.minRange = (stats.str * 5 * .9 * job.getMastery() + stats.dex) * stats.watt / 100;

		//darkimpale
		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(0, se) * 1000 / job.getSpeed(0, speedSel) * minimum(stats.mobCount, job.getSkillMobs(0));
		returnData.DPS.push_back(passDub);

		//crusher
		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(1, se) * 1000 / job.getSpeed(1, speedSel) * minimum(stats.mobCount, job.getSkillMobs(1));
		returnData.DPS.push_back(passDub);

		//fury
		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(2, se) * 1000 / job.getSpeed(2, speedSel) * minimum(stats.mobCount, job.getSkillMobs(2));
		returnData.DPS.push_back(passDub);

		break;
	}
	case hero:		// hero
	{
		double multi;
		double stabMulti;
		switch (wepSel) {
		case 0: multi = 4.0; break;
		case 1: multi = 4.6; break;
		case 2: multi = 4.4; stabMulti = 3.2; break;
		case 3: multi = 4.8; stabMulti = 3.4; break;

		}

		if (wepSel == 2 || wepSel == 3) { //axe
			int wepVal = wepSel + 3;
			returnData.maxRange = (stats.str * multi + stats.dex) * stats.watt / 100;

			returnData.minRange = (stats.str * multi * .9 * job.getMastery() + stats.dex) * stats.watt / 100;

			returnData.max2Range = (stats.str * stabMulti + stats.dex) * stats.watt / 100;

			returnData.min2Range = (stats.str * stabMulti * .9 * job.getMastery() + stats.dex) * stats.watt / 100;

			passDub = ((returnData.minRange + returnData.maxRange) / 2 * .5 + (returnData.min2Range + returnData.max2Range) / 2 * .5) * job.getDPSValue(0, se) * 1000 / job.getSpeed(0, speedSel) * minimum(stats.mobCount, job.getSkillMobs(0));
			returnData.DPS.push_back(passDub);
		}
		else if (wepSel == 0 || wepSel == 1) { //sword
			int wepVal = wepSel + 3;

			returnData.maxRange = (stats.str * multi + stats.dex) * stats.watt / 100;

			returnData.minRange = (stats.str * multi * .9 * job.getMastery() + stats.dex) * stats.watt / 100;

			passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(0, se) * 1000 / job.getSpeed(0, speedSel) * minimum(stats.mobCount, job.getSkillMobs(0));
			returnData.DPS.push_back(passDub);
		}

		break;
	}
	case paladin:		// paladin
	{
		double multi;
		double stabMulti;
		switch (wepSel) {
		case 0: multi = 4.0; break;
		case 1: multi = 4.6; break;
		case 2: multi = 4.4; stabMulti = 3.2; break;
		case 3: multi = 4.8; stabMulti = 3.4; break;

		}

		int weakVal = weakSel;
		if (weakSel != none) {
			weakVal = weakSel - 1;
			if (weakSel == poison) {
				weakVal = 0;
			}
		}

		if (wepSel == 2 || wepSel == 3) { //mace

			returnData.maxRange = (stats.str * multi + stats.dex) * stats.watt / 100;

			returnData.minRange = (stats.str * multi * .9 * job.getMastery() + stats.dex) * stats.watt / 100;

			returnData.max2Range = (stats.str * stabMulti + stats.dex) * stats.watt / 100;

			returnData.min2Range = (stats.str * stabMulti * .9 * job.getMastery() + stats.dex) * stats.watt / 100;

			//blast mace
			passDub = ((returnData.minRange + returnData.maxRange) / 2 * .6 + (returnData.min2Range + returnData.max2Range) / 2 * .4) * job.getPalaDPS(0, weakVal, se) * 1000 / job.getSpeed(0, speedSel) * minimum(stats.mobCount, job.getSkillMobs(0));
			if (weakVal != weakSel && weakSel != 5) { passDub *= 1.5; }
			returnData.DPS.push_back(passDub);

			//acb mace
			passDub = ((returnData.minRange + returnData.maxRange) / 2 * .6 + (returnData.min2Range + returnData.max2Range) / 2 * .4) * job.getPalaDPS(1, weakVal, se) * 1000 / job.getSpeed(1, speedSel) * minimum(stats.mobCount, job.getSkillMobs(1));
			if (weakVal != weakSel && weakSel != 5) { passDub *= 1.5; }
			returnData.DPS.push_back(passDub);

		}
		else if (wepSel == 0 || wepSel == 1) { //sword

			returnData.maxRange = (stats.str * multi + stats.dex) * stats.watt / 100;

			returnData.minRange = (stats.str * multi * .9 * job.getMastery() + stats.dex) * stats.watt / 100;

			//blast sword
			passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getPalaDPS(0, weakVal, se) * 1000 / job.getSpeed(0, speedSel) * minimum(stats.mobCount, job.getSkillMobs(0));
			if (weakVal != weakSel && weakSel != 5) {
				passDub *= 1.5;
			}
			returnData.DPS.push_back(passDub);

			//acb sword
			passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getPalaDPS(1, weakVal, se) * 1000 / job.getSpeed(1, speedSel) * minimum(stats.mobCount, job.getSkillMobs(1));
			if (weakVal != weakSel && weakSel != 5) {
				passDub *= 1.5;
			}
			returnData.DPS.push_back(passDub);

		}


		break;
	}
	case dawnwarrior:
	{
		double multi;
		switch (wepSel) {
		case 0: multi = 4.0; break;
		case 1: multi = 4.6; break;

		}
		 //sword

		returnData.maxRange = (stats.str * multi + stats.dex) * stats.watt / 100;

		returnData.minRange = (stats.str * multi * .9 * job.getMastery() + stats.dex) * stats.watt / 100;

		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(0, se) * 1000 / job.getSpeed(0, speedSel) * minimum(stats.mobCount, job.getSkillMobs(0));
		returnData.DPS.push_back(passDub);

		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(1, se) * 1000 / job.getSpeed(1, speedSel) * minimum(stats.mobCount, job.getSkillMobs(1));
		returnData.DPS.push_back(passDub);
		

		break;
	}

	case icelightning:		// icelightning roll to bishop
	case firepoison:		// fp roll to bishop
	case bishop:		// bishop
	case blazewizard:
	{
		double mainStat = stats.intel;

		double magicMax = job.calcMagicMax(stats.matt, mainStat, 0, se) * getMultMagic(wepSel, 0); //single t
		magicMax *= eleApp(classSel, weakSel, 0);
		returnData.maxRange = magicMax;

		double magic2Max = job.calcMagicMax(stats.matt, mainStat, 1, se) * getMultMagic(wepSel, 1); //ult
		magic2Max *= eleApp(classSel, weakSel, 1);
		returnData.max2Range = magic2Max;

		double magicMin = job.calcMagicMin(stats.matt, mainStat, 0, se) * getMultMagic(wepSel, 0); //single t
		magicMin *= eleApp(classSel, weakSel, 0);
		returnData.minRange = magicMin;

		double magic2Min = job.calcMagicMin(stats.matt, mainStat, 1, se) * getMultMagic(wepSel, 1); // ult
		magic2Min *= eleApp(classSel, weakSel, 1);
		returnData.min2Range = magic2Min;

		double clMult = minimum(stats.mobCount, job.getSkillMobs(0));
		if (job.getJobName() == "IceLightning") {
			clMult = 10 / 3 * ( 1 - pow(.7, minimum(stats.mobCount, job.getSkillMobs(0))));
		}

		double magicDPS = job.calcMagicDPS(stats.matt, mainStat, 0, se) * getMultMagic(wepSel, 0) * 1000 / job.getSpeed(0, 0) * clMult; //cl
		magicDPS *= eleApp(classSel, weakSel, 0);
		returnData.DPS.push_back(magicDPS);

		magicDPS = job.calcMagicDPS(stats.matt, mainStat, 1, se) * getMultMagic(wepSel, 1) * 1000 / job.getSpeed(1, 0) * minimum(stats.mobCount, job.getSkillMobs(1)); //blizzard
		magicDPS *= eleApp(classSel, weakSel, 1);
		returnData.DPS.push_back(magicDPS);

		break;
	}

	case shadower:		//shadower
	{
		double dsDelay = 240; // delay from dark sight for boomerang step

		returnData.maxRange = (stats.luk * 3.6 + stats.dex + stats.str) * stats.watt / 100;

		returnData.minRange = (stats.luk * 3.6 * .9 * job.getMastery() + stats.dex + stats.str) * stats.watt / 100;

		double tempSpeed = speedSel;
		if (job.getSpammable(0)) {
			tempSpeed = speedSel;
		}
		else { tempSpeed = 5; }

		//ass only, skill ID 0
		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(0, se) * 1000 / (job.getSpeed(0, tempSpeed) + dsDelay) * minimum(stats.mobCount, job.getSkillMobs(0));
		returnData.DPS.push_back(passDub);

		//ass4th

		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(1, se) * 1000 / job.getSpeed(1, speedSel) * minimum(stats.mobCount, job.getSkillMobs(1));
		returnData.DPS.push_back(passDub);

		if (job.getSpammable(2)) {
			tempSpeed = speedSel;
		}
		else { tempSpeed = 5; }
		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(2, se) * 1000 / job.getSpeed(2, tempSpeed) * minimum(stats.mobCount, job.getSkillMobs(2));
		returnData.DPS.push_back(passDub);

		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(3, se) * 1000 / job.getSpeed(3, speedSel) * minimum(stats.mobCount, job.getSkillMobs(3));
		returnData.DPS.push_back(passDub);

		//combo crunch



		for (int a = 0; a < job.getComboNum(); a++) {		
			std::vector<int> skillIDs;
			double tempComboDmg = 0;
			double tempComboSpeed = 0;

			for (int c = 0; c < job.getComboSize(a); c++) {			
				for (int i = 0; i < job.getSkillNum(); i++) {
					if (job.getComboSkillName(a, c) == job.getSkillName(i)) {
					skillIDs.push_back(i);
					
					}
				}				
			}

			if (skillIDs.size() == 2 && skillIDs[0] == 2 && skillIDs[1] == 3) {
				tempComboSpeed = job.getSpeed(2, 5);
				tempComboDmg = job.getDPSValue(2, se) * minimum(stats.mobCount, job.getSkillMobs(2)) + job.getDPSValue(3, se) * minimum(stats.mobCount, job.getSkillMobs(3));
			}
			else {
				for (int d = 0; d < skillIDs.size(); d++) {
					tempComboDmg += job.getDPSValue(skillIDs[d], se) * minimum(stats.mobCount, job.getSkillMobs(skillIDs[d]));
					if (skillIDs[d] == 0 && d == 0) { tempComboSpeed += dsDelay; }
					tempComboSpeed += job.getSpeed(skillIDs[d], speedSel);
				}
			}
			passDub = (returnData.minRange + returnData.maxRange) / 2 * tempComboDmg * 1000 / tempComboSpeed;
			returnData.DPS.push_back(passDub);
		}
		


		break;
	}

	case nightlord:		//nightlord
	{
		//L7
		returnData.max2Range = (stats.luk * 5) * stats.watt / 100;

		returnData.min2Range = (stats.luk * 2.5) * stats.watt / 100;

		passDub = (returnData.max2Range + returnData.min2Range) / 2 * job.getDPSValue(0, se) * 1000 / job.getSpeed(0, speedSel) * minimum(stats.mobCount, job.getSkillMobs(0));
		returnData.DPS.push_back(passDub);

		//avenger
		returnData.maxRange = (stats.luk * 3.6 + stats.dex + stats.str) * stats.watt / 100;

		returnData.minRange = (stats.luk * 3.6 * .9 * job.getMastery() + stats.dex + stats.str) * stats.watt / 100;

		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(1, se) * 1000 / job.getSpeed(1, speedSel) * minimum(stats.mobCount, job.getSkillMobs(1));
		returnData.DPS.push_back(passDub);

		break;
	}
	case nightwalker:		//nightwalker
	{
		double vanishDelay = 60;

		//L7
		returnData.max2Range = (stats.luk * 5) * stats.watt / 100;

		returnData.min2Range = (stats.luk * 2.5) * stats.watt / 100;

		passDub = (returnData.max2Range + returnData.min2Range) / 2 * job.getDPSValue(0, se) * 1000 / (job.getSpeed(0, speedSel) + vanishDelay) * minimum(stats.mobCount, job.getSkillMobs(0));
		returnData.DPS.push_back(passDub);

		//vampire
		returnData.maxRange = (stats.luk * 3.6 + stats.dex + stats.str) * stats.watt / 100;

		returnData.minRange = (stats.luk * 3.6 * .9 * job.getMastery() + stats.dex + stats.str) * stats.watt / 100;

		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(1, se) * 1000 / (job.getSpeed(1, speedSel) + vanishDelay) * minimum(stats.mobCount, job.getSkillMobs(1));
		returnData.DPS.push_back(passDub);

		//avenger

		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(2, se) * 1000 / (job.getSpeed(2, speedSel) + vanishDelay) * minimum(stats.mobCount, job.getSkillMobs(2));
		returnData.DPS.push_back(passDub);

		break;
	}

	case bucc:	// bucc
	{

		returnData.maxRange = (stats.str * 4.8 + stats.dex) * stats.watt / 100;

		returnData.minRange = (stats.str * 4.8 * .9 * job.getMastery() + stats.dex) * stats.watt / 100;

		//demo only, skill ID 0
		int tempSpeed = 0;
		if (job.getSpammable(0)) {
			tempSpeed = speedSel;
		}
		else { tempSpeed = 5; }

		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(0, se) * 1000 / job.getSpeed(0, tempSpeed) * minimum(stats.mobCount, job.getSkillMobs(0));
		returnData.DPS.push_back(passDub);

		//barrage only, skill ID 1, attack speed is 3240, should be located at [1][5]
		if (job.getSpammable(1)) {
			tempSpeed = speedSel;
		}
		else { tempSpeed = 5; }

		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getBarrDPS(1, se) * 1000 / job.getSpeed(1, tempSpeed) * minimum(stats.mobCount, job.getSkillMobs(1));
		returnData.DPS.push_back(passDub);

		//3rd skill
		if (job.getSpammable(2)) {
			tempSpeed = speedSel;
		}
		else { tempSpeed = 5; }
		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(2, se) * 1000 / job.getSpeed(1, tempSpeed) * minimum(stats.mobCount, job.getSkillMobs(2));
		returnData.DPS.push_back(passDub);

		//4th skill
		if (job.getSpammable(3)) {
			tempSpeed = speedSel;
		}
		else { tempSpeed = 5; }
		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(3, se) * 1000 / job.getSpeed(1, tempSpeed) * minimum(stats.mobCount, job.getSkillMobs(3));
		returnData.DPS.push_back(passDub);

		// demo+barrage, adding the two delays together for now

		passDub = (returnData.minRange + returnData.maxRange) / 2 * (job.getDPSValue(0, se) * minimum(stats.mobCount, job.getSkillMobs(0)) + job.getBarrDPS(1, se) * minimum(stats.mobCount, job.getSkillMobs(1))) * 1000 / (job.getSpeed(0, speedSel) + job.getSpeed(1, speedSel));
		returnData.DPS.push_back(passDub);


		//DS + snatch, demo ID is 2, snatch ID is 3, attack speed is same as DS (2250) allegedly [2][5]
		passDub = (returnData.minRange + returnData.maxRange) / 2 * (job.getDPSValue(2, se) * minimum(stats.mobCount, job.getSkillMobs(2)) + job.getDPSValue(3, se) * minimum(stats.mobCount, job.getSkillMobs(3))) * 1000 / job.getSpeed(2, 5);
		returnData.DPS.push_back(passDub);

		break;
	}
	case corsair:	//corsair
	{

		returnData.maxRange = (stats.dex * 3.6 + stats.str) * stats.watt / 100;

		returnData.minRange = (stats.dex * 3.6 * .9 * job.getMastery() + stats.str) * stats.watt / 100;

		//cannon
		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(0, se) * 1000 / job.getSpeed(0, speedSel) * minimum(stats.mobCount, job.getSkillMobs(0));
		returnData.DPS.push_back(passDub);

		//rf
		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(1, se) * 1000 / job.getSpeed(1, speedSel) * minimum(stats.mobCount, job.getSkillMobs(1));
		returnData.DPS.push_back(passDub);

		//torpedo
		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(2, se) * 1000 / job.getSpeed(2, speedSel) * minimum(stats.mobCount, job.getSkillMobs(2));
		returnData.DPS.push_back(passDub);

		//custom mix 
		/*
		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(0, se) * job.getSpeed(0, speedSel)  * GetDlgItemInt(hWnd, ID_EDITBCS, &dlgCheck, FALSE) / (GetDlgItemInt(hWnd, ID_EDITBCS, &dlgCheck, FALSE) + GetDlgItemInt(hWnd, ID_EDITRFS, &dlgCheck, FALSE) + GetDlgItemInt(hWnd, ID_EDITIS, &dlgCheck, FALSE));

		passDub += (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(1, se) * job.getSpeed(1, speedSel)  * GetDlgItemInt(hWnd, ID_EDITRFS, &dlgCheck, FALSE) / (GetDlgItemInt(hWnd, ID_EDITBCS, &dlgCheck, FALSE) + GetDlgItemInt(hWnd, ID_EDITRFS, &dlgCheck, FALSE) + GetDlgItemInt(hWnd, ID_EDITIS, &dlgCheck, FALSE));

		returnData.DPS.push_back(passDub);
		*/

		break;
	}
	case thunderbreaker:	// tb
	{

		returnData.maxRange = (stats.str * 4.8 + stats.dex) * stats.watt / 100;

		returnData.minRange = (stats.str * 4.8 * .9 * job.getMastery() + stats.dex) * stats.watt / 100;

		//demo only, skill ID 0
		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getDPSValue(0, se) * 1000 / job.getSpeed(0, speedSel) * minimum(stats.mobCount, job.getSkillMobs(0));
		returnData.DPS.push_back(passDub);

		//barrage only, skill ID 1, attack speed is 3240, should be located at [1][5]
		passDub = (returnData.minRange + returnData.maxRange) / 2 * job.getBarrDPS(1, se) * 1000 / job.getSpeed(1, 5) * minimum(stats.mobCount, job.getSkillMobs(1));
		returnData.DPS.push_back(passDub);


		break;
	}
	}
}