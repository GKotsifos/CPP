#pragma once

class Event
{
protected:

	float m_pos_x;
	float m_pos_y;

	float m_duration = 2.0f; //duration toy event
	float m_delay = 0.0f;
	float m_elapsed_time = 0.0f;
	float m_elapsed_delay = 0.0f;

	bool m_active = true;

public:
	virtual void draw() {}; //aparaithto gia polymorphismo
	virtual void update();
	Event(float x = 0.0f, float y = 0.0f, float dur = 2.0f, float del = 0.0f);

	virtual ~Event() {};
	bool active() { return m_active; }
	void disable() { m_active = false; }
	bool waiting();
};

class dummyEvent : public Event //klhronomei apo to event
{
public:
	void draw() override; //polymorphism
	dummyEvent(float x, float y); //constructor
};
