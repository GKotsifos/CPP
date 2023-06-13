#pragma once
#include <iostream>
#include <string>
#include "poster.h"

class Widget
{
	float m_color[3];

	bool m_highlighted = false;
	bool m_active = false;

public:

	float m_pos[10] = { -1.f,-1.f,-1.f,-1.f,-1.f,-1.f,-1.f,-1.f,-1.f,-1.f };

	void draw();
	void update();
	//Widget();

	//mallon tha vgoun logo klhronomikothtas
	float getPosX() { return m_pos[0]; }
	float getPosY() { return m_pos[1]; }
	void setPosX(float x) { m_pos[0] = x; }
	void setPosY(float y) { m_pos[1] = y; }
	void setPosX2(float x2) { m_pos[2] = x2; }
	void setPosX3(float x3) { m_pos[3] = x3; }
	void setPosX4(float x4) { m_pos[4] = x4; }
	void setPosX5(float x5) { m_pos[5] = x5; }
	void setPosX6(float x6) { m_pos[6] = x6; }
	void setPosX7(float x7) { m_pos[7] = x7; }
	void setPosX8(float x8) { m_pos[8] = x8; }
	void setPosX9(float x9) { m_pos[4] = x9; }


	//mallon tha vgoun logo klhronomikothtas
	void setHighlight(bool h) { m_highlighted = h; }
	void setActive(bool a) { m_active = a; }

	bool contains(float x, float y, float size); //elegxei ean vrisketai to pontiki mesa sto plaisio toy poster

	//bool intersect(Poster* tgt); //elegxei ean 2 posters peftoun to ena pano sto allo

	//void drawDescription(int current, int page_number);

	//void clickSound();
};

class Filter : public Widget
{
	bool highlighted;

public:

	void draw();
	void update();
	//Filter();

	bool contains(float x, float y, bool a);

	void chooseFilter();

};

class checkBox : public Widget
{
	bool highlighted;
	bool checked;//px titlo kai year 

public:
	void draw();
	void draw(bool ab, bool filter_pressed);
	void update();
	//checkBox();

	//void chooseFilter();

	bool contains(float x, float y);

	void setChecked(bool value) { checked = value; }
	bool getChecked() { return checked; }
	void click_unclick_box();
};

class Search :public Widget {
	//float m_pos[2];
	float m_color[3];

	bool m_highlighted = false;
	//bool m_active = false;
	bool search_bar_clicked = false;
	std::string search_name;
	std::string input = "";
	bool is_current_search = false;
	//enum upper_bar_enum_t { TRENDING, GENRE, RATING, YEAR, UPCOMING };

public:
	void draw(std::string words);
	void draw_search_rect();
	void update();
	bool contains(float x, float y);
	bool getSearchClicked() { return search_bar_clicked; };
	void setSearchClicked(bool value) { search_bar_clicked = value; };
	std::string getInput() { return input; };
	void setInput(std::string a) {
		input = a;
		//cout << "in widget the input is--->" << input << endl;
	};
	void set_search_name(std::string name) { search_name = name; };
	void set_Iscurrent_search(bool val) { is_current_search = val; };
	bool get_IScurrent_search() { return is_current_search; };

	//enum upper_bar_enum_t { TRENDING, GENRE, RATING, YEAR, UPCOMING };
protected:
	//upper_bar_enum_t upper_bar_state = TRENDING;
};
