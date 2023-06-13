#include "poster.h"
#include "sgg/graphics.h"
#include "defines.h"
#include <string>
#include <fstream>
#include "widget.h"
#include <string>

using namespace std;

void Filter::draw()
{
	graphics::Brush br;
	br.fill_opacity = 0.5f;
	SETCOLOR(br.fill_color, 0.5f, 0.2f, 0.8f);
	graphics::drawRect(CANVAS_WIDTH - 3.0f, 1.0f, 2.0f, 0.6f, br);
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	br.fill_opacity = 1.0f;
	graphics::drawText(CANVAS_WIDTH - 3.5f, 1.15f, 0.5f, "Filter", br);

}


bool Widget::contains(float x, float y, float size)
{
	for (int i = 0; i < 10; i++) {
		if (i == 1) {
			continue;
		}if (m_pos[i] == -1.f) {
			continue;
		}

		if (distance(x, y, m_pos[i], m_pos[1]) < size * 1.0f) {
			return true;
		}

	}return false;
}


bool Filter::contains(float x, float y, bool a)
{

	if (a) {
		return distance(x, y, CANVAS_WIDTH - 2.4f, 3.9f) < 3.2f;
	}
	else {
		return Widget::contains(x, y, FILTER_SIZE);
	}

}

void Filter::chooseFilter()
{
	graphics::Brush br;
	br.fill_opacity = 1.0f;


	SETCOLOR(br.fill_color, 0.5f, 0.2f, 0.8f);
	graphics::drawText(CANVAS_WIDTH - 3.5f, 2.5f, 0.5f, "Title", br);
	graphics::drawText(CANVAS_WIDTH - 3.5f, 3.0f, 0.5f, "Director", br);
	graphics::drawText(CANVAS_WIDTH - 3.5f, 3.5f, 0.5f, "Stars", br);
	graphics::drawText(CANVAS_WIDTH - 3.5f, 4.0f, 0.5f, "Year", br);
	graphics::drawText(CANVAS_WIDTH - 3.5f, 4.5f, 0.5f, "Genre", br);


	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);
	br.fill_opacity = 0.5f;
	graphics::drawRect(CANVAS_WIDTH - 2.4f, 3.9f, 3.2f, 3.8f, br); //big grey box

	//checkboxes
	graphics::drawRect(CANVAS_WIDTH - 1.5f, 2.4f, 0.4f, 0.4f, br);
	graphics::drawRect(CANVAS_WIDTH - 1.5f, 2.9f, 0.4f, 0.4f, br);
	graphics::drawRect(CANVAS_WIDTH - 1.5f, 3.4f, 0.4f, 0.4f, br);
	graphics::drawRect(CANVAS_WIDTH - 1.5f, 3.9f, 0.4f, 0.4f, br);
	graphics::drawRect(CANVAS_WIDTH - 1.5f, 4.4f, 0.4f, 0.4f, br);

}

bool checkBox::contains(float x, float y)
{
	return Widget::contains(x, y, CHECKBOX_SIZE);
}

void checkBox::draw(bool ab, bool filter_pressed)
{
	graphics::Brush br;
	if (ab && filter_pressed)
	{
		graphics::drawText(getPosX() - 0.1, getPosY() + 0.15f, 0.35f, "X", br);
	}
	else {
		graphics::drawText(getPosX(), getPosY(), 0.3f, "", br);
	}
}


void checkBox::click_unclick_box()
{

}

void Filter::update()
{

}

void Search::draw(std::string words)
{
	graphics::Brush br;
	graphics::setFont("PlayfairDisplay-BoldItalic.otf");
	graphics::drawText(25, m_pos[1] - 0.4f, 0.5f, search_name, br);
	graphics::setFont("Aller_Lt.ttf");
	if (words == "__") {
		std::string txt = "Search ";

		graphics::drawText(m_pos[0] - 1.7f, m_pos[1] + 0.16f, 0.5f, txt + (string)search_name, br);
	}
	else {
		br.fill_opacity = 1.f;
		graphics::drawText(m_pos[0] - 1.7f, m_pos[1] + 0.16f, 0.5f, input, br);
	};
}


void Search::draw_search_rect() {
	graphics::Brush br;
	br.fill_opacity = 0.f;
	graphics::drawRect(m_pos[0], m_pos[1], 4.f, 0.6f, br);
}



bool Search::contains(float x, float y) {
	if (Widget::contains(x, y, CHECKBOX_SIZE)) {
		cout << true;
	}
	return Widget::contains(x, y, CHECKBOX_SIZE);
}