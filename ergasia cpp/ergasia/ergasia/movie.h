#pragma once
#include <list>
#include "poster.h"
#include "event.h"
#include "widget.h"
#include <array>
#include <string>
#include <vector>

using namespace std;

class Movie
{
public:

	enum game_state_t { STATE_INIT, STATE_LOADING, STATE_RUNNING };

protected:

	static Movie* m_instance; //static-prepei na arxikopoihthei

	std::list<Poster*> m_posters;
	std::list<Button*> m_buttons;
	std::list<Event*> m_events;
	std::list<Poster*>m_posters_reversed;
	array<Poster*, 4> finalposters;
	array< checkBox*, 5> array_checboxes;
	array<Search*, 5> array_searches;
	array<char[9], 5> search_boxes_names = { "Title","Director","Stars","Year","Genre" };
	vector<int> anazhtoumeno;

	int current = -1;
	int page_number = 1;
	int bpressed = 0;
	bool flag = false;
	int current_search_num = -1;

	Filter* filter = new Filter();
	bool flag_in_filter = false;

	//list<Poster*> m_posters;
	Poster* m_active_poster = nullptr;
	Button* m_active_button = nullptr;
	float m_init_pos_x;
	float m_init_pos_y;
	game_state_t m_state = STATE_INIT; //arxikh katastash

	Movie() {}

public:
	void draw();
	void update();
	void init();

	virtual ~Movie();

	static void releaseInstance() { if (m_instance) delete m_instance; m_instance = nullptr; }
	static Movie* getInstance();

	void processEvents();
	void addEvent(Event* evt);
};