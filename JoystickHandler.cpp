#include "include/JoystickHandler.h"

JoystickHandler::joystickevent_t::joystickevent_t(char k, char i, callback_function c)
{
	key = k;
	info = i;
	cback = c;
}

int JoystickHandler::registerCallback(char key, char info, callback_function callback)
{
	m_events.push_back( joystickevent_t( key, info, callback ) );
	return m_events.size();
}

void JoystickHandler::unRegisterCallback(int cbid)
{
	m_events.erase(m_events.begin() + cbid - 1);
}

void JoystickHandler::handleEvent(char key, char info)
{
	char _info = info;
	// For analog stick events, mask info and send the original information via _info
	if(key == LS || key == RS)
	{
		info = info & 4 ? YMOVE : XMOVE;
	}
	
	for(auto it = m_events.begin(); it != m_events.end(); ++it)
	{
		if(it->key == key && it->info == info)
			it->cback(key, _info);
	}
}