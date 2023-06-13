#pragma once
#include <iostream>
#include "widget.h"

class Poster
{
	float m_pos[2];
	float m_color[3];

	bool m_highlighted = false;
	bool m_active = false;

public:

	enum movie_tags { tag_title, tag_director, tag_stars, tag_year, tag_genre, tag_description };
	movie_tags tag_m = tag_title; //arxikh katastash

	void draw(int postNum);
	void update();
	Poster(); // constructor declaration

	const char* posterNames[8] = { "download.png", "shawsank.png", "django.png", "bateman.png",
	"strangelove.png","travis.png","truman.png", "forrest.png" };

	float getPosX() { return m_pos[0]; }
	float getPosY() { return m_pos[1]; }
	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }

	void setHighlight(bool h) { m_highlighted = h; }
	void setActive(bool a) { m_active = a; }

	bool contains(float x, float y); //elegxei ean vrisketai to pontiki mesa sto plaisio toy poster

	bool intersect(Poster* tgt); //elegxei ean 2 posters peftoun to ena pano sto allo

	void drawDescription(int current, int page_number);

	void clickSound();
};

class Button : private Poster //inheriting from class Poster
{
	float m_posb[2];
	float m_color[3];

	bool m_highlighted = false;
	bool m_active = false;
	bool flag;

public:
	void drawB(bool flag);
	void update();
	Button(); // constructor declaration

	int* bpressed = 0; //na ftiakso statheri topothesia pointer
	float getPosX() { return m_posb[0]; }
	float getPosY() { return m_posb[1]; }
	void setPosX(float x) { m_posb[0] = x; }
	void setPosY(float y) { m_posb[1] = y; }

	void setHighlight(bool h) { m_highlighted = h; }
	void setActive(bool a) { m_active = a; }

	bool containsB(float x, float y); //elegxei ean vrisketai to pontiki mesa sto plaisio toy poster

	void clickSound();


};