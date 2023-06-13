#include "defines.h"
#include "movie.h"
#include <sgg/graphics.h>
#include <string>
#include <iostream>
#include <fstream>
#include "poster.h"
#include "widget.h"
#include <vector>
#include <algorithm>

using namespace std;

void Movie::draw()
{
	graphics::Brush br;
	br.outline_opacity = 0.0f;
	SETCOLOR(br.fill_color, 1.0f, 1.0f, 1.0f);

	if (m_state == STATE_INIT)
	{
		graphics::setFont("Aller_Lt.ttf"); //sets font style
		graphics::drawText(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, 1.0f, "loading the app...", br);
		m_state = STATE_LOADING;
		return;
	}


	br.outline_opacity = 0.0f;
	br.texture = ASSET_PATH + string("ba.png");

	SETCOLOR(br.fill_color, 0.0f, 0.0f, 0.3f);

	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	int postername1 = -1;
	int postername2 = 3;
	int counter1 = -1;
	int counter2 = 3;
	if (anazhtoumeno.size() != 0) {
		if (bpressed % 2 == 0) {
			page_number = 1;
			for (auto poster : m_posters_reversed)
			{
				counter1++;
				for (int i = 0; i <anazhtoumeno.size(); i++)
				{
					if (anazhtoumeno[i] == counter1)
					{
						poster->draw(3 - counter1);
					}
				}
				if (counter1 >= 3)
				{
					counter1 = 0;
				}
			}
		}
		else if (bpressed % 2 == 1)
		{
			page_number = 2;
			for (auto poster : m_posters_reversed)
			{
				counter2++;
				for (int i = 0; i < anazhtoumeno.size(); i++)
				{
					if (anazhtoumeno[i] == counter2)
					{
						poster->draw(11 - counter2);
					}
				}
				if (counter2 >= 7)
				{
					counter2 = 3;
				}
			}
		}
	}
	else {
		if (bpressed % 2 == 0) {
			page_number = 1;
			for (auto poster : m_posters) // draws posters
			{
				postername1++;
				poster->draw(postername1);
				if (postername1 >= 3) {
					break;
				}
			}
		}
		else if (bpressed % 2 == 1)
		{
			page_number = 2;
			for (auto poster : m_posters) // draws posters
			{
				postername2++;
				poster->draw(postername2);
				if (postername2 >= 7) {
					break;
				}
			}
		}
	}


	for (auto button : m_buttons) // draws arrows
	{
		if (button->getPosX() == CANVAS_WIDTH * (0.5f) / 10.0f)
		{
			button->drawB(true);
		}
		else {
			button->drawB(false);
		}
	}

	filter->draw();

	if (flag_in_filter)
	{
		filter->chooseFilter();
	}

	for (auto check : array_checboxes) {
		check->draw(check->getChecked(), flag_in_filter);
	}

	if (!flag_in_filter) { //einai eksw ap to koutaki filter
		for (int i = 0; i < array_checboxes.size(); i++) {
			if (array_checboxes[i]->getChecked()) { //ta check_box pou einai checked me "x"
				array_searches[i]->draw_search_rect(); // //draw mono ta search bar without textattr
				if (array_searches[i]->contains(getMX(), getMY()) && left_key_pressed()) {
					array_searches[i]->setSearchClicked(true);
					if (current_search_num == -1)
						current_search_num = i;
					array_searches[current_search_num]->set_Iscurrent_search(false);
					current_search_num = i;
					array_searches[current_search_num]->set_Iscurrent_search(true);


				}

				if (!array_searches[i]->getSearchClicked()) { //an den einai pathmeno emfanizei px "search title"
					array_searches[i]->draw("__"); //draws nothing but the search name

				}
				else if (array_searches[i]->getSearchClicked()) { //exw pathsei mesa sto search kai mporw na grapsw epitelus
					if (array_searches[i]->get_IScurrent_search()) {

						array_searches[i]->setInput(get_user_input(array_searches[i]->getInput()));

						//array_searches[i]->draw(array_searches[i]->getInput());

					}
					array_searches[i]->draw(array_searches[i]->getInput());
				}

			}


		}
	}

}

void Movie::update()
{

	if (m_state == STATE_INIT)
	{
		return;
	}

	if (m_state == STATE_LOADING)
	{
		init();
		m_state = STATE_RUNNING;
		return;
	}

	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {

			
			//graphics::drawText(15.f, 1.f, 1.0f, "NO MOVIE FOUND", br);
			//Sleep(3000)
		anazhtoumeno.clear();
		Sleep(200);
		if (anazhtoumeno.size()==0)
		{
			graphics::Brush br;
			SETCOLOR(br.fill_color, 1.f, 0.f, 0.f);
			graphics::drawText(15.f, 1.f, 1.0f, "NO MOVIE FOUND", br);
			Sleep(3000);
		}
		bool previous_was_indicator = false; //an exei perasei to <name>
		int n_inputs = 0; //posa einai ta inputs
		int matches = 0; //posa find exei brei px an psaksw tainia me title kai genre otan to match ginei 2 8a thn emfanisei prepei matches==n_inputs
		int twrinh_tainia = 0; //pointer poianhs tainias einai sto file px 0 h 2 h 4
		vector<int> indexes; //ta indexes twn searches px sto [title ,director,genre ] to genre einai 2


		fstream newfile;
		newfile.open(ASSET_PATH + string("cpp.txt"), ios::in);
		std::string grammh;

		for (int i = 0; i < array_searches.size(); i++) {
			if (array_searches[i]->getInput() != "") { //briskei posa searches exoun epilex8ei kai den einai kena
				n_inputs++;
				indexes.push_back(i);// pros8etei to index tous
			}
		}


		cout << "the n_inputs is " << n_inputs << endl;


		int twrino_index = 0; //8a deixnei ena pointer ka8e fora kai 8a metabaletai analogws
		int xx = 0;
		if (indexes.size() != 0) {
			twrino_index = indexes[0];
		}

		cout << " the size is " << indexes.size() << endl;
		cout << " twrino index " << twrino_index << endl;

		if (newfile.is_open() && indexes.size() != 0) {
			while (getline(newfile, grammh)) {
				if (grammh == "---") {
					twrinh_tainia++;
					matches = 0;
					xx = 0;
					twrino_index = indexes[0];
				}

				string str = "<" + (string)search_boxes_names[twrino_index] + ">"; //estw title



				if (grammh == str) {

					previous_was_indicator = true;
					continue;
				}
				if (previous_was_indicator) {
					transform(grammh.begin(), grammh.end(), grammh.begin(), ::toupper);

					if (grammh.find(array_searches[twrino_index]->getInput()) != std::string::npos) {
						cout << "here ---------------------" << grammh << endl;
						matches++;
						if (matches == n_inputs) {
							anazhtoumeno.push_back(twrinh_tainia);

						}
					}
					previous_was_indicator = false;
					if (xx != indexes.size() - 1)
						xx += 1;
					twrino_index = indexes[xx];
				}

			}
		}
		if (anazhtoumeno.size() == 0 || indexes.size() == 0) {
			cout << "no movies with those charasterics found";
		}
		else {

			for (auto ind : anazhtoumeno) {
				cout << "The movies indexes are : " << ind << endl;

			}
		}
	}



	//cout << " the state is " << m_state << endl;
	processEvents();

	for (auto poster : m_posters)
	{
		poster->update();
	}

	for (auto button : m_buttons)
	{
		button->update();
	}

	filter->update();


	graphics::MouseState ms; //pairnei to stigmiotypo toy pontikiou
	graphics::getMouseState(ms);

	float mx = graphics::windowToCanvasX(ms.cur_pos_x);
	float my = graphics::windowToCanvasY(ms.cur_pos_y);



	Poster* cur_poster = nullptr;

	int i = -1;

	for (auto poster : finalposters)
	{
		i++;
		if (poster->contains(mx, my))
		{

			finalposters[i]->setHighlight(true);
			cur_poster = poster; //krataei to torino poster poy kano hover
			if (left_key_pressed())
			{
				current = i;
				cout << "the poster i number is " << i << endl;
				finalposters[current]->setHighlight(true);
				continue;
			}
		}
		else
		{
			if (i != current)
				poster->setHighlight(false);
		}
	}

	finalposters[current]->drawDescription(current, page_number);


	Button* cur_button = nullptr;
	for (auto button : m_buttons)
	{
		if (button->containsB(mx, my))
		{
			//cout << "INSIDE BUTTON";
			button->setHighlight(true); //ginetai true otan einai mesa sto plaisio o cursor
			cur_button = button; //krataei to torino poster poy kano hover
		}
		else
		{
			button->setHighlight(false);
		}
	}


	if (left_key_pressed() and !filter->contains(mx, my, false) and !filter->contains(mx, my, true))
	{
		flag_in_filter = false;
	}

	if (filter->Filter::contains(mx, my, false) and left_key_pressed())
	{
		flag_in_filter = true;

	}



	//activate/press poster
	if (left_key_pressed() && cur_poster)
	{
		m_active_poster = cur_poster;
		m_active_poster->clickSound();
		cout << "INSIDE POSTER";
		m_active_poster->setActive(true);
		for (auto poster : m_posters) //kanei disable ta inactive posters 
		{
			if (poster != m_active_poster)
			{
				m_active_poster->setActive(false);
			}
		}
		//krataei thn sintetagmenh poy patithike to poster
		m_init_pos_x = m_active_poster->getPosX();
		m_init_pos_y = m_active_poster->getPosY();
	}

	//button pressed
	if (left_key_pressed() && cur_button)
	{
		current = -1;
		m_active_button = cur_button;

		m_active_button->clickSound();
		for (auto button : m_buttons) //kanei disable ta inactive posters 
		{
			if (button != m_active_button)
			{
				m_active_button->setActive(false);
			}
		}
		//krataei thn sintetagmenh poy patithike to poster
		m_init_pos_x = m_active_button->getPosX();
		m_init_pos_y = m_active_button->getPosY();

		//here goes the button click
		bpressed += 1;
		//init();
	}

	for (int i = 0; i < array_checboxes.size(); i++)
	{

		//ftiakse pio kalh domh 
		if (array_checboxes[i]->checkBox::contains(mx, my) && flag_in_filter && left_key_pressed())
		{
			graphics::Brush bx;
			if (array_checboxes[i]->getChecked()) {
				array_checboxes[i]->draw(false, flag_in_filter);
				array_checboxes[i]->setChecked(false);
				array_searches[i]->setInput("");
				array_searches[i]->setSearchClicked(false);

			}
			else {
				array_checboxes[i]->draw(true, flag_in_filter);
				array_checboxes[i]->setChecked(true);

			}

		}


	}


	if (ms.button_left_released && m_active_poster)
	{
		m_state = STATE_RUNNING;
		m_active_poster->setActive(false);
		m_active_poster = nullptr;
	}



}

void Movie::init()
{


	int j = -1;
	for (int i = 2; i < 6; i++) {
		//for (int j = 0; j < 2; j++) {
		j++;
		Poster* p = new Poster(); //dhmioyrgia instance poster
		m_posters.push_front(p);
		m_posters_reversed.push_back(p);
		finalposters[j] = p;

		p->setPosX(CANVAS_WIDTH * (i - 1.0f) / 6.0f);
		p->setPosY(CANVAS_HEIGHT * (0.5f) / 2.0f);
		//}
	}


	//arrows
	Button* p = new Button(); //dhmioyrgia instance poster
	m_buttons.push_front(p);

	//left button position
	p->setPosX(CANVAS_WIDTH * (0.5f) / 10.0f);
	p->setPosY(CANVAS_HEIGHT * (0.5f) / 2.0f);

	Button* p1 = new Button(); //dhmioyrgia instance poster
	m_buttons.push_front(p1);

	//right button position
	p1->setPosX(CANVAS_WIDTH * (1.55f) / 2.0f);
	p1->setPosY(CANVAS_HEIGHT * (0.5f) / 2.0f);

	//checkboxes + ok
	float add_box = 0.50508f;
	for (int i = 0; i < array_checboxes.size(); i++)
	{

		checkBox* c = new checkBox();
		array_checboxes[i] = c;
		c->checkBox::setPosX(26.5078f);
		c->checkBox::setPosY(2.40434f + (float)(i * add_box));
		if (i == 0)
		{
			c->setChecked(true);
			continue;
		}
		c->setChecked(false);
	}



	//searches
	//prepei na pairnei tis true checked metablhtes pio panw kai na emfanizei analaogws ta searches
	float add_search = 1.3f;
	for (int i = 0; i < array_searches.size(); i++) {
		Search* search = new Search();
		array_searches[i] = search;
		search->Search::setPosX(25.44f);
		search->Search::setPosX2(23.8);
		search->Search::setPosX3(24.2f);
		search->Search::setPosX4(25.f);
		search->Search::setPosX5(25.8f);
		search->Search::setPosX6(26.2f);
		search->Search::setPosX7(26.6f);
		search->Search::setPosX8(26.7f);
		search->Search::setPosX9(24.6f);
		search->Search::setPosY(2.4533f + (float)(i * add_search));
		search->Search::set_search_name(search_boxes_names[i]);
		search->Search::set_Iscurrent_search(false);

	}

	filter->setPosX(24.5f);
	filter->setPosX2(24.3f);
	filter->setPosX3(24.8f);
	filter->setPosX4(25.1f);
	filter->setPosX5(25.4f);
	filter->setPosX6(25.7f);
	filter->setPosY(1.0f);

	graphics::preloadBitmaps(ASSET_PATH); //preloads assets

}

Movie::~Movie()
{
	for (auto poster : m_posters)
	{
		delete poster;
	}
	m_posters.clear();

	for (auto button : m_buttons)
	{
		delete button;
	}
	m_buttons.clear();

	//filter->~Filter();
	//delete filter;
	//for (int i = 0; i < 5; i++) {
		/////array_searches[i]->~Search();
		//delete array_searches[i];
		/////array_checboxes[i]->~checkBox();
		//delete array_checboxes[i];
		//delete[] array_checboxes[i];
	//}
	//delete[] array_checboxes
	//delete[] array_checboxes;


	//finalposters->~Poster();


	//releaseInstance();
}


Movie* Movie::getInstance()
{
	if (!m_instance)
		m_instance = new Movie();
	return m_instance;
}

void Movie::processEvents()
{
	for (auto e : m_events)
	{
		e->update();
	}

	m_events.remove_if([](Event* ev) {return !ev->active(); }); //lamda expression
}

void Movie::addEvent(Event* evt)
{
	m_events.push_front(evt);
}

Movie* Movie::m_instance = nullptr; //arxikopoihsh

void end()
{

}