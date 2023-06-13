#include "poster.h"
#include "sgg/graphics.h"
#include "defines.h"
#include <string>
#include <fstream>
#include "movie.h"

using namespace std;

void Poster::draw(int postNum) 
{
	graphics::Brush br;

	float h = 1.0f * m_highlighted; //gia hover

	SETCOLOR(br.fill_color, h, h, h);
	br.outline_opacity = 1.0f * m_active;
	graphics::drawRect(m_pos[0], m_pos[1], POSTER_SIZE * 1.02f, POSTER_SIZE * 1.02f, br);

	SETCOLOR(br.fill_color, m_color[0], m_color[1], m_color[2]);
	br.texture = ASSET_PATH + string(posterNames[postNum]);
	br.outline_opacity = 0.0f;
	graphics::drawRect(m_pos[0], m_pos[1], POSTER_SIZE, POSTER_SIZE, br);
}

void Button::drawB(bool flag) //if true aristero button eikona else deksi + xrwmata
{
	graphics::Brush br;

	float h = 1.0f * m_highlighted;

	SETCOLOR(br.fill_color, h, h, h);
	br.outline_opacity = 1.0f * m_active;
	graphics::drawRect(m_posb[0], m_posb[1], BUTTON_SIZE * 1.01f, BUTTON_SIZE * 1.02f, br);

	SETCOLOR(br.fill_color, m_color[0], m_color[1], m_color[2]);
	if (flag == true)
	{
		br.texture = ASSET_PATH + string("arrow_left.png");
	}
	else
	{
		br.texture = ASSET_PATH + string("arrow_right.png");
	}
	br.outline_opacity = 0.0f;
	graphics::drawRect(m_posb[0], m_posb[1], BUTTON_SIZE, BUTTON_SIZE, br);
}

Button::Button() //constructor definition
{
	SETCOLOR(m_color, 1.0f, 1.0f, 1.0f); //xoris auto mavrizoun ta posters
}

void Poster::update()
{
}

void Button::update()
{
}

Poster::Poster() //constructor definition
{
	SETCOLOR(m_color, 1.0f, 1.0f, 1.0f); //xoris auto mavrizoun ta posters
}

bool Poster::contains(float x, float y)
{
	return distance(x, y, m_pos[0], m_pos[1]) < POSTER_SIZE * 0.6f; //den ksero gt doulevei me to 0.6 kai oxi sketo
}

bool Poster::intersect(Poster* tgt)
{
	return distance(m_pos[0], m_pos[1], tgt->m_pos[0], tgt->m_pos[1]) < POSTER_SIZE * 2.02f; //2 fores to size tou poster
}

bool Button::containsB(float x, float y)
{
	return distance(x, y, m_posb[0], m_posb[1]) < BUTTON_SIZE * 0.6f;
}

void Poster::drawDescription(int current, int page_number)//zwgrafizei ta stoixeia enos movie
{

	graphics::Brush br;
	fstream newfile;
	//int line_number = 2;
	newfile.open(ASSET_PATH + string("cpp.txt"), ios::in); //open a file to perform read operation using file object
	float i = 8.0f;
	int counter = 0;
	string s2 = "Whipl";

	if (page_number == 2)
	{
		counter -= 4;
	}
	if (newfile.is_open() && current >= 0) { //checking whether the file is open
		string tp;
		while (getline(newfile, tp)) { //read data from file object and put it into string.
			//cout << tp << "\n"; //print the data of the string

			if (tp.find("<") != std::string::npos && tp != "<Title>") {
				continue;
			}

			if (counter == current) {
				if (tp == "<Title>") {
					tag_m = tag_title; continue;
				}

				if (tag_m == tag_title) {
					graphics::setFont("PlayfairDisplay-BoldItalic.otf");
					graphics::drawText(2.5f, i, 1.0f, tp, br);
					i += 0.6f;
					tag_m = tag_description;
					continue;
				}
				if (tp != "---" and tag_m == tag_description) {
					graphics::setFont("Aller_Lt.ttf");
					graphics::drawText(2.5f, i, 0.7f, tp, br);
					i += 0.6f;
				}
				else
				{
					break;
				}
			}
			if (tp == "---") {
				counter++;
			}

		}
		newfile.close();
	}
}

void Poster::clickSound() //paizei hxo gia asset
{
	graphics::playSound(ASSET_PATH + string("posterSound.wav"), 0.5f);
}

void Button::clickSound() //paizei hxo gia buttom
{
	graphics::playSound(ASSET_PATH + string("buttonSound.wav"), 0.5f);
}