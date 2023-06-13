#pragma once
#include <random>
#include <windows.h>
#include <stdlib.h>
#include <sgg/graphics.h>
#include <string>
#include <iostream>
using namespace std;
#define CANVAS_WIDTH 28.0f
#define CANVAS_HEIGHT 16.0f

#define ASSET_PATH ".\\assets\\"

#define POSTER_SIZE 3.5f
#define BUTTON_SIZE 1.0f
#define FILTER_SIZE 0.4f
#define CHECKBOX_SIZE 0.19754f
#define SEARCH_SIZE 0.3f

#define SETCOLOR(c, r, g, b) {c[0] = r; c[1] =g; c[2] =b;}
#define RAND0TO1() (rand()/(float)RAND_MAX)



inline graphics::MouseState getMS() {
	graphics::MouseState ms; //pairnei to stigmiotypo toy pontikiou
	graphics::getMouseState(ms);
	return ms;
}

inline bool left_key_pressed() {

	return getMS().button_left_pressed;
}

inline float getMX() {
	float mx = graphics::windowToCanvasX(getMS().cur_pos_x);
	return mx;
}

inline float getMY() {
	float my = graphics::windowToCanvasY(getMS().cur_pos_y);
	return my;
}


inline float distance(float x1, float y1, float x2, float y2)
{
	float dx = x1 - x2;
	float dy = y1 - y2;
	return sqrtf(dx * dx + dy * dy);
}

inline std::string get_user_input(std::string inp) { //pairnei to input tou xrhsth kai diagrafei me backspace

	static float delay = 0.0f;
	static int prev = 0;
	//std::string str;
	delay += graphics::getDeltaTime();

	for (int i = graphics::SCANCODE_A; i <= graphics::SCANCODE_Z; i++) {

		if (graphics::getKeyState((graphics::scancode_t)i))
		{

			if (prev == i && delay < 200.0f) {
				delay += 0.1f;
				continue;
			}
			else {
				prev = i;
				delay = 0.0f;
				Sleep(200);
				cout << "You pressed: " << (char)(i + 'A' - graphics::SCANCODE_A) << endl;
				inp += (char)(i + 'A' - graphics::SCANCODE_A);
				return inp;
			}
		}
	};
	for (int j = graphics::SCANCODE_1; j <= graphics::SCANCODE_0; j++) {
		if (graphics::getKeyState((graphics::scancode_t)j))
		{

			if (prev == j && delay < 200.0f) {
				delay += 0.1f;
				continue;
			}
			else {
				prev = j;
				delay = 0.0f;
				Sleep(200);
				cout << "You pressed: " << (char)(j + 18) << endl;
				if (j != 39) {
					inp += (char)(j + 19);
				}
				else
					inp += (char)(48);

				return inp;
			}
		}
	};
	if (graphics::getKeyState((graphics::scancode_t)graphics::SCANCODE_SPACE))
	{
		if (prev == graphics::SCANCODE_SPACE && delay < 200.0f) {
			delay += 0.1f;
		}
		else {
			prev = graphics::SCANCODE_SPACE;
			delay = 0.0f;
			Sleep(200);
			inp += (char)(32);
		}
		return inp;
	}
	if (graphics::getKeyState((graphics::scancode_t)graphics::SCANCODE_BACKSPACE))
	{
		if (prev == graphics::SCANCODE_BACKSPACE && delay < 200.0f) {
			delay += 0.1f;

		}
		else {
			prev = graphics::SCANCODE_BACKSPACE;
			delay = 0.0f;
			Sleep(200);
			if (inp.length() > 0) {
				inp.pop_back();
				cout << "You pressed backspace, the current input is : " << inp << endl;
			}
		}
	}

	return inp;
}