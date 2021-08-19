#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "TextButton.h"
#include "JobStats.h"
#include "calculator.h"

class DPSCalc {

private:
	int fontSize = 18;

	sf::Color firstBoxColor = { 217,242,167,255 };
	sf::Color secondBoxColor = { 115, 120, 130,255 };

	sf::Vector2f statBoxPos = { 50, 200 };
	sf::Vector2f statBoxSize = { 50,20 };

	sf::Vector2f minRangePos = { 300,150 };
	sf::Vector2f maxRangeDiff = { 100,0 };

	sf::Vector2f rangeSize = { 75,20 };


	sf::Vector2f classBoxPos = { 400,300 };
	sf::Vector2f speedBoxPos = { 600,100 };
	sf::Vector2f weakBoxPos = { 600, 300 };

	float statBoxDiff = 25;
	float wattDiff = 150;

	sf::Font bst;

	char classSel = -1;
	char weakSel = -1;
	char speedSel = -1;

	bool sharpeyes;
	bool echo;

	int wepSel;
	

	void setAllFonts() {

		classBox.setFont(bst);
		speedBox.setFont(bst);
		weakBox.setFont(bst);
		weaponBox.setFont(bst);

		//calcButton.setFont(bst);
		targetCount.setFont(bst);
	}
	std::vector<JobStats> jobVector;
	std::vector<TextboxWLabel> skillDPS;

public:
	std::vector<TextboxWLabel> tbwL;

	DPSCalc(int windowWidth, int windowHeight) {
		bst.loadFromFile("bahnschrift.ttf");
		setAllFonts();

		std::ifstream file;
		file.open("resources\\jobinfo.txt");

		while(!file.eof()) {
			jobVector.push_back(JobStats(file));
			classBox.pushback(jobVector[jobVector.size() - 1].getJobName());
		}
		file.close();

		speedBox.pushback("2");
		speedBox.pushback("3");
		speedBox.pushback("4");
		speedBox.pushback("5");
		speedBox.pushback("6");
		weakBox.pushback("None");
		weakBox.pushback("Holy");
		weakBox.pushback("Fire");
		weakBox.pushback("Lightning");
		weakBox.pushback("Ice");
		weakBox.pushback("Poison");

		for (int i = 1; i <= 15; i++) {
			targetCount.pushback(std::to_string(i));
		}
		targetCount.setSelection(0);
		

		tbwL.push_back(TextboxWLabel(statBoxPos, fontSize, bst, "STR", "4", statBoxSize, firstBoxColor, 5, 0)); //0
		tbwL.push_back(TextboxWLabel({ statBoxPos.x, statBoxPos.y + statBoxDiff }, fontSize, bst, "DEX", "4", statBoxSize, firstBoxColor, 5, 0));
		tbwL.push_back(TextboxWLabel({ statBoxPos.x, statBoxPos.y + statBoxDiff * 2 }, fontSize, bst, "INT", "4", statBoxSize, firstBoxColor, 5, 0));
		tbwL.push_back(TextboxWLabel({ statBoxPos.x, statBoxPos.y + statBoxDiff * 3 }, fontSize, bst, "LUK", "4", statBoxSize, firstBoxColor, 5, 0));
		tbwL.push_back(TextboxWLabel({ statBoxPos.x, statBoxPos.y + wattDiff }, fontSize, bst, "Attack", "1", statBoxSize, firstBoxColor, 5, 1));
		tbwL.push_back(TextboxWLabel({ statBoxPos.x, statBoxPos.y + wattDiff + statBoxDiff}, fontSize, bst, "Magic", "4", statBoxSize, firstBoxColor, 5, 3));

		tbwL.push_back(TextboxWLabel(minRangePos, fontSize, bst, "Min", "0", rangeSize, secondBoxColor, 5, 0)); //6
		tbwL.push_back(TextboxWLabel(minRangePos + maxRangeDiff, fontSize, bst, "Max", "0", rangeSize, secondBoxColor, 5, 2)); //7

		tbwL.push_back(TextboxWLabel({ minRangePos.x, minRangePos.y + statBoxDiff }, fontSize, bst, "Min2", "0", rangeSize, secondBoxColor, 5, 0)); //8
		tbwL.push_back(TextboxWLabel({ minRangePos.x + maxRangeDiff.x, minRangePos.y + statBoxDiff }, fontSize, bst, "Max2", "0", rangeSize, secondBoxColor, 5, 2)); //9

		tbwL[8].label.setActivity(false);
		tbwL[8].textbox.setActivity(false);
		tbwL[9].label.setActivity(false);
		tbwL[9].textbox.setActivity(false);


		classBox.setPosition({ windowWidth - classBox.getRectangle().getLocalBounds().width, windowHeight - classBox.getRectangle().getLocalBounds().height });


		weakBox.setPosition({ windowWidth - weakBox.getRectangle().getLocalBounds().width, 30 });
		weakBoxLabel.setPosition({ windowWidth - weakBox.getRectangle().getLocalBounds().width, 30 }, 1);

		speedBox.setPosition({ windowWidth - speedBox.getRectangle().getLocalBounds().width, weakBox.getRectangle().getLocalBounds().height + 50});

		calcButton.setPosition({ 4, static_cast<float>(windowHeight) - 43 });

	}

	TextButton calcButton{ "Calculate",{200,40}, 36, sf::Color::Black,sf::Color::Blue, bst, 5 };

	Label rangeLabel{ {minRangePos.x + maxRangeDiff.x / 2, minRangePos.y - 30}, fontSize, "Range", 4, bst };


	ListBox classBox{ {0,0}, fontSize, bst };
	ListBox speedBox{ {0,0}, fontSize, bst, 20 };
	ListBox weakBox{ {0,0}, fontSize, bst };
	Label weakBoxLabel{ {0,0}, fontSize, "Weakness", 1, bst };

	ListBox weaponBox{ {0,0}, fontSize, bst };
	
	checkBox seCheck{"Sharp Eyes", {100, 100}, bst };
	checkBox echoCheck{"Echo", {100, 120}, bst };

	//comboBox(sf::Vector2f pos, int fontSz, float initWidth = -1) {
	comboBox targetCount{ {510,200}, fontSize, bst };
	Label countLabel{ {425,200}, fontSize, "Mob Count", 0, bst };




	void isMouseOver(sf::RenderWindow &window) {

		for (int i = 0; i < tbwL.size(); i++) {
			tbwL[i].textbox.isMouseOver(window);
		}
		seCheck.isMouseOver(window);
		echoCheck.isMouseOver(window);

		targetCount.isMouseOver(window);
		

		if (int temp = classBox.isMouseOver(window) != -1) {	//class was changed
			classSel = classBox.getSelection();

			tbwL[6].label.setText("Min");
			tbwL[7].label.setText("Max");

			tbwL[8].label.setActivity(false);
			tbwL[8].textbox.setActivity(false);
			tbwL[9].label.setActivity(false);
			tbwL[9].textbox.setActivity(false);
			weaponBox.clear();
			skillDPS.clear();

			if (temp != -2) {
				int skillNum = jobVector[classSel].getSkillNum();
				for (int i = 0; i < skillNum; i++) {

					skillDPS.push_back(TextboxWLabel({ 360,300 + 23 * static_cast<float>(i) }, fontSize, bst, jobVector[classSel].getSkillName(i), "", rangeSize, secondBoxColor, 5, 0));

				}
				int comboNum = jobVector[classSel].getComboNum();
				for (int i = 0; i < comboNum; i++) {
					std::string tempComboString = "";
					for (int ii = 0; ii < jobVector[classSel].getComboSize(i); ii++) {
						tempComboString += jobVector[classSel].getComboSkillName(i, ii).substr(0, 4) + ".";
					}
					skillDPS.push_back(TextboxWLabel({ 360,300 + 23 * static_cast<float>(i) + skillNum * 23 }, fontSize, bst, tempComboString, "", rangeSize, secondBoxColor, 5, 0));
				}
			}
			if (classSel == hero) {
				weaponBox.pushback("1h sword");
				weaponBox.pushback("2h sword");
				weaponBox.pushback("1h axe");
				weaponBox.pushback("2h axe");
				weaponBox.setPosition({ classBox.getRectangle().getPosition().x - weaponBox.getRectangle().getLocalBounds().width, classBox.getRectangle().getPosition().y });
			}
			else if (classSel == paladin) {
				weaponBox.pushback("1h sword");
				weaponBox.pushback("2h sword");
				weaponBox.pushback("1h mace");
				weaponBox.pushback("2h mace");
				weaponBox.setPosition({ classBox.getRectangle().getPosition().x - weaponBox.getRectangle().getLocalBounds().width, classBox.getRectangle().getPosition().y });
			}
			else if (classSel == dawnwarrior) {
				weaponBox.pushback("1h sword");
				weaponBox.pushback("2h sword");
				weaponBox.setPosition({ classBox.getRectangle().getPosition().x - weaponBox.getRectangle().getLocalBounds().width, classBox.getRectangle().getPosition().y });
			}
			else if (classSel == icelightning) {
				weaponBox.pushback("Lightning Staff");
				weaponBox.pushback("Ice Staff");
				weaponBox.pushback("No ele staff");

				weaponBox.setPosition({ classBox.getRectangle().getPosition().x - weaponBox.getRectangle().getLocalBounds().width, classBox.getRectangle().getPosition().y });

				tbwL[6].label.setText(jobVector[icelightning].getSkillName(0) + " Min");
				tbwL[7].label.setText(jobVector[icelightning].getSkillName(0) + " Max");

				tbwL[8].label.setActivity(true);
				tbwL[8].textbox.setActivity(true);
				tbwL[8].label.setText(jobVector[icelightning].getSkillName(1) + " Min");

				tbwL[9].label.setActivity(true);
				tbwL[9].textbox.setActivity(true);
				tbwL[9].label.setText(jobVector[icelightning].getSkillName(1) + " Max");
			}
			else if (classSel == firepoison) {
				tbwL[6].label.setText("Min");
				tbwL[7].label.setText("Max");

				weaponBox.pushback("Poison Staff");
				weaponBox.pushback("Fire Staff");
				weaponBox.pushback("No ele staff");
				weaponBox.setPosition({ classBox.getRectangle().getPosition().x - weaponBox.getRectangle().getLocalBounds().width, classBox.getRectangle().getPosition().y });

				tbwL[6].label.setText(jobVector[firepoison].getSkillName(0) + " Min");
				tbwL[7].label.setText(jobVector[firepoison].getSkillName(0) + " Max");

				tbwL[8].label.setActivity(true);
				tbwL[8].textbox.setActivity(true);
				tbwL[8].label.setText(jobVector[firepoison].getSkillName(1) + " Min");

				tbwL[9].label.setActivity(true);
				tbwL[9].textbox.setActivity(true);
				tbwL[9].label.setText(jobVector[firepoison].getSkillName(1) + " Max");
			}
			else if (classSel == bishop) {
				tbwL[6].label.setText(jobVector[bishop].getSkillName(0) + " Min");
				tbwL[7].label.setText(jobVector[bishop].getSkillName(0) + " Max");

				tbwL[8].label.setActivity(true);
				tbwL[8].textbox.setActivity(true);
				tbwL[8].label.setText(jobVector[bishop].getSkillName(1) + " Min");

				tbwL[9].label.setActivity(true);
				tbwL[9].textbox.setActivity(true);
				tbwL[9].label.setText(jobVector[bishop].getSkillName(1) + " Max");
			}
			else if (classSel == nightlord) {
				tbwL[8].label.setActivity(true);
				tbwL[8].textbox.setActivity(true);
				tbwL[8].label.setText("Lucky Seven Min");
				tbwL[9].label.setActivity(true);
				tbwL[9].textbox.setActivity(true);
				tbwL[9].label.setText("Lucky Seven Max");
			}
			
		}
		if (weakBox.isMouseOver(window) != -1) {
			weakSel = weakBox.getSelection();
		}
		if (speedBox.isMouseOver(window) != -1) {
			speedSel = speedBox.getSelection();
		}
		if (weaponBox.isMouseOver(window) != -1) {
			wepSel = weaponBox.getSelection();
			if (classSel == hero || classSel == paladin) {
				if (wepSel == 2 || wepSel == 3) {
					tbwL[6].label.setText("Swing Min");
					tbwL[7].label.setText("Swing Max");

					tbwL[8].label.setActivity(true);
					tbwL[8].textbox.setActivity(true);
					tbwL[8].label.setText("Stab Min");
					tbwL[9].label.setActivity(true);
					tbwL[9].textbox.setActivity(true);
					tbwL[9].label.setText("Stab Max");


				}
				else if (wepSel == 1 || wepSel == 0) {
					tbwL[6].label.setText("Min");
					tbwL[7].label.setText("Max");

					tbwL[8].label.setActivity(false);
					tbwL[8].textbox.setActivity(false);
					tbwL[9].label.setActivity(false);
					tbwL[9].textbox.setActivity(false);
				}
			}
		}

		if (calcButton.isMouseOver(window)) {
			if (tbwL[0].textbox.getText() == "") {
				tbwL[0].textbox.setText("4");
			}
			if (tbwL[1].textbox.getText() == "") {
				tbwL[1].textbox.setText("4");
			}
			if (tbwL[2].textbox.getText() == "") {
				tbwL[2].textbox.setText("4");
			}
			if (tbwL[3].textbox.getText() == "") {
				tbwL[3].textbox.setText("4");
			}			
			if (tbwL[4].textbox.getText() == "") {
				tbwL[4].textbox.setText("1");
			}
			if (tbwL[5].textbox.getText() == "") {
				tbwL[5].textbox.setText(tbwL[2].textbox.getText());
			}
			if (stoi(tbwL[2].textbox.getText()) > stoi(tbwL[5].textbox.getText())) {
				tbwL[5].textbox.setText(tbwL[2].textbox.getText());
			}



			if (classSel != -1) {
				if (weakBox.getSelection() == -1) {
					weakBox.setSelection(0);
					weakSel = 0;
				}
				if (speedBox.getSelection() == -1) {
					speedBox.setSelection(2);
					speedSel = 2;
				}
				if (weaponBox.getSelection() == -1) {
					weaponBox.setSelection(0);
					wepSel = 0;
				}

				weakSel = weakBox.getSelection();
				speedSel = speedBox.getSelection();
				wepSel = weaponBox.getSelection();
				

				charStats calcStats;


				calcStats.str = static_cast<double>(stoi(tbwL[0].textbox.getText()));
				calcStats.dex = static_cast<double>(stoi(tbwL[1].textbox.getText()));
				calcStats.intel = static_cast<double>(stoi(tbwL[2].textbox.getText()));
				calcStats.luk = static_cast<double>(stoi(tbwL[3].textbox.getText()));
				calcStats.watt = static_cast<double>(stoi(tbwL[4].textbox.getText()));
				calcStats.matt = static_cast<double>(stoi(tbwL[5].textbox.getText()));
				calcStats.mobCount = targetCount.getSelection() + 1;
				if (echoCheck.getChecked()) {
					calcStats.watt *= 1.04;
				}
				if (seCheck.getChecked()) {sharpeyes = true;}
				else {sharpeyes = false;}

				damageData returnData;

				// (JobStats &job, charStats &stats, int classSel, int speedSel, int weakSel, bool seActive, int wepSel, damageData &returnData)
				calc(jobVector[classSel], calcStats, classSel, speedSel, weakSel, sharpeyes, wepSel, returnData);

				tbwL[6].textbox.setText(std::to_string(static_cast<int>(returnData.minRange)));
				tbwL[7].textbox.setText(std::to_string(static_cast<int>(returnData.maxRange)));

				if (returnData.min2Range != -1) {
					tbwL[8].textbox.setText(std::to_string(static_cast<int>(returnData.min2Range)));
				}
				if (returnData.max2Range != -1) {
					tbwL[9].textbox.setText(std::to_string(static_cast<int>(returnData.max2Range)));
				}
			

				/*
				for (int i = 0; i < returnData.DPS.size(); i++) {
					skillDPS[i].textbox.setText(std::to_string(static_cast<int>(returnData.DPS[i])));
				}
				*/

				int holdingNum = jobVector[classSel].getSkillNum();
				for (int i = 0; i < returnData.DPS.size(); i++) {
					skillDPS[i].textbox.setText(std::to_string(static_cast<int>(returnData.DPS[i])));
				}

				//for (int i = 0; i < jobVector[classSel].getComboNum(); i++) {
				//	skillDPS[i + holdingNum].textbox.setText(std::to_string(static_cast<int>(returnData.comboDPS[i])));
				//}

			}
			
		}


	}

	void draw(sf::RenderWindow &window) {

		for (int i = 0; i < tbwL.size(); i++) {
			tbwL[i].draw(window);
		}


		rangeLabel.drawTo(window);

		classBox.draw(window);
		weakBox.draw(window);
		speedBox.draw(window);
		weaponBox.draw(window);

		weakBoxLabel.drawTo(window);

		calcButton.draw(window);
		
		seCheck.draw(window);
		echoCheck.draw(window);
		targetCount.draw(window);
		countLabel.drawTo(window);

		if (skillDPS.size() != 0) {
			for (int i = 0; i < skillDPS.size(); i++) {
				skillDPS[i].draw(window);			
			}
		}

	}

	




};