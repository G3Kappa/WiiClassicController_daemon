#ifndef JOYSTICKHANDLER_H
#define JOYSTICKHANDLER_H
#include <vector>
#include "include/JoystickHandler.h"

enum JoystickKeys
{
    X = 0,
    A,
    Y,
    B,
    Up,
    Left,
    Down,
    Right,
    L1,
    R1,
    L2,
    R2,
    Select,
    Start,
    Home,
    LS,
	RS,
    KEYS_N
};

enum JoystickKeyInfo
{
    DOWN = 0,
    UP = 1,
	XMOVE,
	YMOVE,
};

typedef void (*callback_function)(char, char);
class JoystickHandler
{
private:
    struct joystickevent_t
    {
		char key;
		char info;
		callback_function cback;
		
		joystickevent_t(char k, char i, callback_function c);
    };
    std::vector<joystickevent_t> m_events;
public:
    int registerCallback(char key, char info, callback_function callback);
    
    void unRegisterCallback(int cbid);
    
    void handleEvent(char key, char info);
};
#endif