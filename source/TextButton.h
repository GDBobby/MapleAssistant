#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include <string>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27


class Label
{
private:
	sf::Text label;
	int fontSize;
	int stringLength;
	char relPos = 0; //0 is left, 1 is above, 2 is to the right, 3 is below, 4 is no relation
	sf::Vector2f position;
	sf::Vector2f posDiff;
	bool isActive = true;

public:
	Label() {}
	Label(sf::Vector2f pos, int fontSz, std::string string, char relation, sf::Font& font, sf::Vector2f relationSize = { 100,0 }) {
		stringLength = string.length();
		fontSize = fontSz;


		label.setCharacterSize(fontSize);
		label.setFillColor(sf::Color::Black);

		label.setString(string);
		setFont(font);

		setPosition(pos, relation, relationSize);
	}

	void setFont(sf::Font &font) {
		label.setFont(font);
	}
	void setPosition(sf::Vector2f pos, char relation, sf::Vector2f posDif = { 100,0 }) {
		position = pos;
		relPos = relation;
		posDiff = posDif;

		float offset = label.getLocalBounds().left + label.getLocalBounds().width + 5;
		std::string coutString = label.getString();
		
		switch (relPos) {
		case 0:

			//label.setPosition({ pos.x - (stringLength * 2 / 3 * fontSize), pos.y });
			label.setPosition({ pos.x - offset, pos.y });
			break;

		case 1:
			label.setPosition({ pos.x,pos.y - 20 });
			break;

		case 2:
			label.setPosition({ pos.x + posDif.x + 2, pos.y });
			break;

		case 3:
			label.setPosition({ pos.x,pos.y + 20 });
			break;
		case 4:
			label.setPosition(pos);
			break;
		}
	}

	void setText(std::string setter) {
		label.setString(setter);
		setPosition(position, relPos, posDiff);
	}

	void setActivity(bool activity) {
		isActive = activity;
	}

	void drawTo(sf::RenderWindow &window) {
		if (isActive) {
			window.draw(label);
		}
	}

};



class Textbox
{
public:

	bool numberOnly = true;

private:
	sf::Text textbox;
	sf::RectangleShape textRect;
	std::ostringstream text;
	bool isSelected = false;
	bool hasLimit = true;
	int limit = 5;
	bool hasLabel = false;
	bool canEdit = true;
	bool isActive = true;

	void inputLogic(int charTyped) {
		if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY) {
			if (isdigit(static_cast<char>(charTyped)) && numberOnly) {

				text << static_cast<char>(charTyped);
			}
			else if(!numberOnly) {
				text << static_cast<char>(charTyped);
			}
			else {

			}
		}
		else if (charTyped == DELETE_KEY) {
			if (text.str().length() > 0) {
				deleteLastChar();
			}
		}
		textbox.setString(text.str());

	}

	void deleteLastChar() {
		std::string t = text.str();
		std::string newT = "";
		for (int i = 0; i < t.length() - 1; i++) {
			newT += t[i];
		}
		text.str("");
		text << newT;

		textbox.setString(text.str());
	}


public:
	Textbox() {}
	Textbox(sf::Vector2f pos, int fontSize, sf::Font& font, sf::Vector2f boxSize, sf::Color color, int limitInit, std::string string = "") {
		setPosition(pos);

		textbox.setCharacterSize(fontSize);
		textbox.setFillColor(sf::Color::Black);

		textbox.setString(string);
		text.str(string);

		setFont(font);
		textRect.setSize(boxSize);
		textRect.setFillColor(color);

		limit = limitInit;

		textRect.setOutlineThickness(1);
		textRect.setOutlineColor(sf::Color::Black);
	}
	Textbox(sf::Vector2f pos, int fontSize, sf::Vector2f boxSize, sf::Color color, int limitInit, std::string string, bool isEditable) {
		setPosition(pos);
		canEdit = isEditable;

		textbox.setCharacterSize(fontSize);
		textbox.setFillColor(sf::Color::Black);

		textbox.setString(string);
		text.str(string);

		textRect.setSize(boxSize);
		textRect.setFillColor(color);

		limit = limitInit;

		textRect.setOutlineThickness(1);
		textRect.setOutlineColor(sf::Color::Black);
	}

	void setFont(sf::Font &font) {
		textbox.setFont(font);
	}
	void setPosition(sf::Vector2f pos) {
		textRect.setPosition(pos);
		textbox.setPosition(pos);
	}

	void setSelected(bool sel) {
		isSelected = sel;
		if (!sel) {
			std::string t = text.str();
			std::string newT = "";
			for (int i = 0; i < t.length(); i++) {
				newT += t[i];
			}
			textbox.setString(newT);
		}
	}
	
	void setActivity(bool activity) {
		isActive = activity;
	}

	std::string getText() {
		return textbox.getString();
	}

	void setText(std::string setter) {
		textbox.setString(setter);
		text.str(setter);
	}

	void drawTo(sf::RenderWindow &window) {
		if (isActive) {
			window.draw(textRect);
			window.draw(textbox);
		}
	}
	void typedOn(sf::Event input) {
		if (isSelected && canEdit) {
			int charTyped = input.text.unicode;
			if (charTyped < 128) {
				if (hasLimit) {
					if (text.str().length() < limit) {
						inputLogic(charTyped);
					}
					else if (text.str().length() >= limit && charTyped == DELETE_KEY) {
						deleteLastChar();
					}
				}
				else {
					inputLogic(charTyped);
				}
			}
		}
	}
	bool isMouseOver(sf::RenderWindow &window) {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = textRect.getPosition().x;
		float btnPosY = textRect.getPosition().y;

		float btnxPosWidth = textRect.getPosition().x + textRect.getLocalBounds().width;
		float btnyPosHeight = textRect.getPosition().y + textRect.getLocalBounds().height;

		if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
			isSelected = true;
			return true;
		}
		isSelected = false;
		return false;
	}

};

class TextboxWLabel {
private:
	
public:
	Label label;
	Textbox textbox;
	//Textbox(sf::Vector2f pos, int fontSize, sf::Vector2f boxSize, sf::Color color, int limitInit, std::string string = "") {
	//Label(sf::Vector2f pos, int fontSz, std::string string, char relation, sf::Font &font, sf::Vector2f relationSize = { 100,0 }) {

	TextboxWLabel(sf::Vector2f pos, int fontSize, sf::Font& font, std::string labstring, std::string boxstring, sf::Vector2f boxSize, sf::Color color, int limitInit, char relation) {

		label = Label(pos, fontSize, labstring, relation, font, boxSize);
		textbox = Textbox(pos, fontSize, font, boxSize, color, limitInit, boxstring);

	}


	void draw(sf::RenderWindow &window) {
		label.drawTo(window);
		textbox.drawTo(window);
	}

};





class TextButton
{
private:
	sf::RectangleShape button;
	sf::Font bst;
	
	sf::Text text;
	float buttonSize = 0;


public:
	TextButton(std::string t, sf::Vector2f pos, int charSize, sf::Color bgColor, sf::Color tColor, sf::Font& font, float butSz) {

		text.setString(t);
		text.setFillColor(tColor);
		text.setCharacterSize(charSize);
		text.setFont(font);

		buttonSize = butSz;
		text.setPosition(pos);
		//button position needs to called to fix the sizing, because text doesn't have a size off the jump

		button.setFillColor({ 150, 150, 150, 255 });
		button.setOutlineColor(sf::Color::Black);
		button.setOutlineThickness(2);
	}

	void setFont(sf::Font &font) {
		text.setFont(font);
	}

	void setBGColor(sf::Color color) {
		button.setFillColor(color);
	}

	void setPosition(sf::Vector2f pos) {

		sf::Vector2f buttSz = { text.getLocalBounds().width, text.getLocalBounds().height };
		button.setSize({ buttSz.x + buttonSize * 2, buttSz.y + buttonSize * 2 });

		button.setPosition({ pos.x + text.getLocalBounds().left - buttonSize, pos.y + text.getLocalBounds().top - buttonSize });
		text.setPosition(pos);





	}
	void draw(sf::RenderWindow &window) {

		window.draw(button);
		window.draw(text);
	}

	bool isMouseOver(sf::RenderWindow &window) {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = button.getPosition().x;
		float btnPosY = button.getPosition().y;

		float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
		float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

		if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
			return true;
		}
		return false;
	}



};



class ImageButton
{
private:
	sf::RectangleShape button;
	bool isSelected = false;


public:
	ImageButton(sf::Vector2f size, sf::Color bgColor) {


		button.setSize(size);
		button.setFillColor(bgColor);
	}

	void setBGColor(sf::Color color) {
		button.setFillColor(color);
	}

	void setPosition(sf::Vector2f pos, sf::Sprite &sprite) {
		button.setPosition(pos);
		sprite.setPosition({ pos.x + 4, pos.y + 4 });
	}
	void drawTo(sf::RenderWindow &window) {
		window.draw(button);
	}

	bool isMouseOver(sf::RenderWindow &window) {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = button.getPosition().x;
		float btnPosY = button.getPosition().y;

		float btnxPosWidth = button.getPosition().x + button.getLocalBounds().width;
		float btnyPosHeight = button.getPosition().y + button.getLocalBounds().height;

		if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
			return true;
		}
		return false;
	}

	void setSelected(bool sel) {
		isSelected = sel;
	}

	bool getSelected() {
		return isSelected;
	}



};


class SelectableText {
private:
	sf::Text textContents;
	sf::RectangleShape boxSelect;
	int fontSize = 18;
	bool isSelected = false;
	bool isActive = true;

public:
	SelectableText(float initWidth, std::string string, int fontSz, sf::Font& font) {
		textContents.setCharacterSize(fontSize);
		textContents.setFillColor(sf::Color::Black);

		textContents.setString(string);
		fontSize = fontSz;

		boxSelect.setSize({ initWidth, 20 });

		textContents.setFont(font);
	}

	bool isMouseOver(sf::RenderWindow &window) {
		if (isActive) {
			float mouseX = sf::Mouse::getPosition(window).x;
			float mouseY = sf::Mouse::getPosition(window).y;

			float btnPosX = boxSelect.getPosition().x;
			float btnPosY = boxSelect.getPosition().y;

			float btnxPosWidth = boxSelect.getPosition().x + boxSelect.getLocalBounds().width;
			float btnyPosHeight = boxSelect.getPosition().y + boxSelect.getLocalBounds().height;

			if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {
				boxSelect.setFillColor(sf::Color::Blue);
				textContents.setFillColor(sf::Color::White);
				return true;
			}
		}
		return false;
	}
	void draw(sf::RenderWindow &window) {
		if (isActive) {
			window.draw(boxSelect);
			window.draw(textContents);
		}
	}
	void setPosition(sf::Vector2f pos) {
		textContents.setPosition(pos);
		boxSelect.setPosition(pos);
	}
	void setActivity(bool active) {
		isActive = active;
	}

	void changeWidth(float a) {
		boxSelect.setSize({ a, 20 });
	}
	void setSelection() {
		boxSelect.setFillColor(sf::Color::Blue);
		textContents.setFillColor(sf::Color::White);
		isSelected = true;
	}
	void stopSelection() {
		boxSelect.setFillColor({ 0,0,0,0 });
		textContents.setFillColor(sf::Color::Black);
		isSelected = false;
	}
	void setFont(sf::Font &font) {
		textContents.setFont(font);
	}
	std::string getString() {
		return textContents.getString();
	}

};


class ListBox {

private:
	char numberOfItems = 0;
	char selection = -1;
	std::vector<SelectableText> contents;
	float width;
	sf::RectangleShape contBox;
	sf::Vector2f lbPosition;
	sf::Font font;
	int highestLength = 0;
	int fontSize;
	bool sizeAdjustable = true;



	void updateSize() {
		contBox.setSize({ width, static_cast<float>(numberOfItems) * 20 });
		for (int i = 0; i < numberOfItems; i++) {
			contents[i].changeWidth(width);
		}
	}


public:
	ListBox(sf::Vector2f pos, int fontSz, sf::Font& fnt, float initWidth = -1) {
		if (initWidth != -1) { sizeAdjustable = false; }
		lbPosition = pos;
		width = initWidth;
		fontSize = fontSz;

		font = fnt;

		contBox.setSize({ initWidth,0 });
		contBox.setPosition(pos);
		contBox.setOutlineThickness(1);
		contBox.setOutlineColor(sf::Color::Black);

	}


	void pushback(std::string string){
		if (string.length() > highestLength && sizeAdjustable) {
			highestLength = string.length();
			width = static_cast<float>(fontSize) * (static_cast<float>(highestLength) / 2);
		}
		contents.push_back(SelectableText(width,string,fontSize, font));
		numberOfItems++;
		contents[numberOfItems - 1].setPosition({lbPosition.x, lbPosition.y + 20 * (numberOfItems-1)});

		this->updateSize();

	}
	void popback() {
		contents.pop_back();
		numberOfItems--;
		this->updateSize();
	}
	void clear() {
		contents.clear();
		numberOfItems = 0;
		highestLength = 0;
		selection = -1;
	}

	char isMouseOver(sf::RenderWindow &window) {
		for (int i = 0; i < numberOfItems; i++) {
			if (contents[i].isMouseOver(window)) {
				for (int ii = 0; ii < numberOfItems; ii++) {
					if (i != ii) { contents[ii].stopSelection(); }
				}
				if (selection != i) {
					selection = i;
					return selection;
				}
				return -2;
			}
		}
		return -1;
	}

	void setSelection(int a) {
		for (int ii = 0; ii < numberOfItems; ii++) {
			if (a != ii) { contents[ii].stopSelection(); }
		}
		if (numberOfItems > 0) {
			selection = a;
			contents[a].setSelection();
		}
	}

	char getSelection() {
		return selection;
	}

	void draw(sf::RenderWindow &window) {
		if (numberOfItems > 0) {

			window.draw(contBox);
			for (int i = 0; i < numberOfItems; i++) {
				contents[i].draw(window);
			}
		}
	}

	void setFont(sf::Font &fnt) {
		font = fnt;
	}

	void setPosition(sf::Vector2f pos) {
		lbPosition = pos;
		contBox.setPosition(pos);
		for (int i = 0; i < numberOfItems; i++) {
			contents[i].setPosition({ pos.x, pos.y + 20 * i });
		}
	}

	sf::RectangleShape getRectangle(){
		return contBox;
	}

};

class comboBox {

private:
	sf::Texture dropTexture;
	sf::Sprite ravelledSprite;
	sf::Sprite droppedSprite;
	bool isDropped = false;
	sf::Text text;

	char numberOfItems = 0;
	char selection = -1;
	std::vector<SelectableText> contents;
	float width;
	sf::RectangleShape contBox;
	sf::Vector2f cbPosition;
	sf::Font font;
	int highestLength = 0;
	int fontSize;
	bool sizeAdjustable = true;



	void dropDown() {
		contBox.setSize({ width, static_cast<float>(numberOfItems + 1) * 20 });
		for (int i = 0; i < numberOfItems; i++) {
			contents[i].setActivity(true);
		}
		isDropped = true;
	}

	void ravelUp() {
		contBox.setSize({ width, 20 });
		for (int i = 0; i < numberOfItems; i++) {
			contents[i].setActivity(false);
		}
		isDropped = false;
	}

	void updateSize() {
		contBox.setSize({ width, 20 });
		for (int i = 0; i < numberOfItems; i++) {
			contents[i].changeWidth(width);
		}
		droppedSprite.setPosition({ contBox.getPosition().x + contBox.getLocalBounds().width, contBox.getPosition().y });
		ravelledSprite.setPosition({ contBox.getPosition().x + contBox.getLocalBounds().width, contBox.getPosition().y });
	}


public:
	comboBox(sf::Vector2f pos, int fontSz, sf::Font& fnt, float initWidth = -1) {
		if (initWidth != -1) { sizeAdjustable = false; }
		cbPosition = pos;
		width = initWidth;
		fontSize = fontSz;

		dropTexture.loadFromFile("resources\\dropbox.png");

		ravelledSprite.setTexture(dropTexture);
		ravelledSprite.setTextureRect({ 16,0,16,16 });
		droppedSprite.setTexture(dropTexture);
		droppedSprite.setTextureRect({ 0,0,16,16 });
		text.setString("");
		text.setFillColor(sf::Color::Black);
		text.setCharacterSize(18);

		//ravelledSprite.setPosition({ pos.x + width, pos.y });
		//droppedSprite.setPosition({ pos.x + width, pos.y });
		text.setPosition(pos);

		contBox.setSize({ initWidth,0 });
		contBox.setPosition(pos);
		contBox.setOutlineThickness(1);
		contBox.setOutlineColor(sf::Color::Black);
		text.setFont(fnt);
		font = fnt;
	}


	void pushback(std::string string) {
		if (string.length() > highestLength && sizeAdjustable) {
			highestLength = string.length();
			width = static_cast<float>(fontSize) * (static_cast<float>(highestLength) / 2);
		}
		contents.push_back(SelectableText(width, string, fontSize, font));
		numberOfItems++;
		contents[numberOfItems - 1].setPosition({ cbPosition.x, cbPosition.y + 20 * (numberOfItems) });
		contents[numberOfItems - 1].setActivity(isDropped);
		this->updateSize();

	}
	void popback() {
		contents.pop_back();
		numberOfItems--;
		this->updateSize();
	}
	void clear() {
		contents.clear();
		numberOfItems = 0;
		highestLength = 0;
		selection = -1;
		text.setString("");
	}

	char isMouseOver(sf::RenderWindow &window) {

		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = droppedSprite.getPosition().x;
		float btnPosY = droppedSprite.getPosition().y;

		float btnxPosWidth = droppedSprite.getPosition().x + droppedSprite.getLocalBounds().width;
		float btnyPosHeight = droppedSprite.getPosition().y + droppedSprite.getLocalBounds().height;

		if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {

			if (isDropped) {
				isDropped = false;
				ravelUp();
			}
			else {
				isDropped = true;
				dropDown();
			}
		}



		for (int i = 0; i < numberOfItems; i++) {
			if (contents[i].isMouseOver(window)) {
				for (int ii = 0; ii < numberOfItems; ii++) {
					if (i != ii) { contents[ii].stopSelection(); }
				}
				if (selection != i) {
					selection = i;
					text.setString(contents[i].getString());
					return selection;
				}
				return -2;
			}
		}
		return -1;
	}

	void setSelection(int a) {
		for (int ii = 0; ii < numberOfItems; ii++) {
			if (a != ii) { contents[ii].stopSelection(); }
		}
		if (numberOfItems > 0) {
			selection = a;
			contents[a].setSelection();
		}
		text.setString(contents[a].getString());
	}

	char getSelection() {
		return selection;
	}

	void draw(sf::RenderWindow &window) {
		if (numberOfItems > 0) {
			window.draw(contBox);
			for (int i = 0; i < numberOfItems; i++) {
				contents[i].draw(window);
			}
		}
		if (isDropped) { window.draw(droppedSprite); }
		else { window.draw(ravelledSprite); }
		window.draw(text);
	}

	void setFont(sf::Font &fnt) {
		font = fnt;
	}

	void setPosition(sf::Vector2f pos) {
		cbPosition = pos;
		contBox.setPosition(pos);
		for (int i = 0; i < numberOfItems; i++) {
			contents[i].setPosition({ pos.x, pos.y + 20 * i });
		}
	}

	sf::RectangleShape getRectangle() {
		return contBox;
	}

};

class checkBox {
private:
	sf::Texture checkTexture;
	sf::Sprite uncheckedSprite;
	sf::Sprite checkedSprite;
	sf::Text text;
	bool isChecked = false;

public:
	checkBox( std::string string, sf::Vector2f pos, sf::Font &font) {
		checkTexture.loadFromFile("resources\\checkbox.png");
		uncheckedSprite.setTexture(checkTexture);
		uncheckedSprite.setTextureRect({ 0,0,16,16 });
		checkedSprite.setTexture(checkTexture);
		checkedSprite.setTextureRect({ 16,0,16,16 });
		text.setString(string);
		text.setFillColor(sf::Color::Black);
		text.setCharacterSize(18);

		uncheckedSprite.setPosition(pos);
		checkedSprite.setPosition(pos);
		text.setPosition({ pos.x + 20, pos.y - 4 });

		text.setFont(font);
	}
	void setPosition() {

	}

	void setFont(sf::Font &font) {
		text.setFont(font);
	}

	void isMouseOver(sf::RenderWindow &window) {
		float mouseX = sf::Mouse::getPosition(window).x;
		float mouseY = sf::Mouse::getPosition(window).y;

		float btnPosX = checkedSprite.getPosition().x;
		float btnPosY = checkedSprite.getPosition().y;

		float btnxPosWidth = checkedSprite.getPosition().x + checkedSprite.getLocalBounds().width;
		float btnyPosHeight = checkedSprite.getPosition().y + checkedSprite.getLocalBounds().height;

		if (mouseX < btnxPosWidth && mouseX > btnPosX && mouseY < btnyPosHeight && mouseY > btnPosY) {

			if (isChecked) {
				isChecked = false;
			}
			else {
				isChecked = true;
			}
		}
	}
	void draw(sf::RenderWindow &window) {
		if (isChecked) { window.draw(checkedSprite); }
		else { window.draw(uncheckedSprite); }
		window.draw(text);
	}

	bool getChecked() {
		return isChecked;
	}

};