#include "sgg/graphics.h"
#include "defines.h"
#include <iostream>
#include <string>
#include "movie.h"

using namespace std;
//using namespace graphics;

void draw() //den pairnei orismata
{
	Movie* mymovie = Movie::getInstance();

	mymovie->draw(); //idio me . alla se pointer
}

void update(float ms)
{
	Movie* mymovie = Movie::getInstance();

	mymovie->update();
}

int main(int argc, char* argv)
{
	graphics::createWindow(1150, 600, "myApp"); //1150, 600

	Movie* movie = Movie::getInstance();

	graphics::setCanvasSize(CANVAS_WIDTH, CANVAS_HEIGHT);
	graphics::setCanvasScaleMode(graphics::CANVAS_SCALE_FIT);

	graphics::setDrawFunction(draw); //tha kalountai
	graphics::setUpdateFunction(update); //se kathe kare

	graphics::startMessageLoop();

	Movie::releaseInstance();

	return 0;
}