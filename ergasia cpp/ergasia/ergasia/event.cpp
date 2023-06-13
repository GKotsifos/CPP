#include "event.h"
#include "sgg/graphics.h"

void Event::update()
{
	if (!m_active)
		return;

	if (waiting())
	{
		m_elapsed_delay += graphics::getDeltaTime() / 1000.0f;
		return;
	}

	m_elapsed_delay += graphics::getDeltaTime() / 1000.0f;
	if (m_elapsed_time > m_duration)
	{
		m_active = false;
	}
}

Event::Event(float x, float y, float dur, float del)
	:m_pos_x(x), m_pos_y(y), m_duration(dur), m_delay(del)
{

}

bool Event::waiting()
{
	return m_elapsed_delay < m_delay;
}

void dummyEvent::draw()
{
	graphics::Brush br;
	//asset goes here
}

dummyEvent::dummyEvent(float x, float y)
	:Event(x, y, 2.0f, 0.0f)
{
}
