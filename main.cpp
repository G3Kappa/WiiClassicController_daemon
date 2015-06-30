// Port to which the arduino is connected
#define COM_PORT "COM3"
// vJoy device id
#define VJ_INTERFACE 1
// The sensitivity of the daemon, basically. 
// The Arduino has it set to 10ms, so by halving that I try to make sure every packet is handled right as it's available.
#define SLEEP_MS 5

#define PI 3.14159265358979323846

#include <cstdlib>
#include <cmath>
#ifdef DEBUG
#include <iostream>
#include <bitset>
#endif
#include "include/SerialClass.h"
#include "include/JoystickHandler.h"
#include "include/public.h"
#include "include/vjoyinterface.h"

void onKeyDown(char key, char info)
{
	SetBtn(1, VJ_INTERFACE, key + 1);
}

void onKeyUp(char key, char info)
{
	SetBtn(0, VJ_INTERFACE, key + 1);
}

// Info has to be interpreted correctly: it is a 3-bit wide number. The first bit is 0 for X-values and 1 for Y-values.
// The other two bits represent "negative", "neutral" and "positive" states, respectively 0, 1 and 2.
// ContPovs are neutral when -1 and any value between 0 and 35900 represents the degrees to which they're turned.

int g_lanalogx = 0;
int g_lanalogy = 0;
int g_ranalogx = 0;
int g_ranalogy = 0;

// Not strictly cartesianToPolar. It converts to degrees and does some transformations to appease SetContPov.
void cartesianToPolarSP(double x, double y, double* r, double* theta)
{
	*r = sqrt( pow(x, 2) + pow(y, 2) );
	*theta = atan2( y, x ) + PI / 2;
	*theta = fmod(*theta * 180 / PI + 180, 360);
	*theta = (360 - (int)*theta) % 360;
	// Due to some floating point error, I have to approximate to the nearest % 5 number
	*theta -= (int)*theta % 5;
}

void onAnalogMove(char analog, char info)
{
	double r, theta;
	
	if( analog == LS )
	{
		if( info & 4 )
			g_lanalogy = (info & 3) - 1;
		else
			g_lanalogx = (info & 3) - 1;
		
		cartesianToPolarSP(g_lanalogx, g_lanalogy, &r, &theta);
		SetContPov( r == 0 ? -1 : (int)theta * 100, VJ_INTERFACE, 1);
	}
	else
	{
		if( info & 4 )
			g_ranalogy = (info & 3) - 1;
		else
			g_ranalogx = (info & 3) - 1;
			
		cartesianToPolarSP(g_ranalogx, g_ranalogy, &r, &theta);
		SetContPov( r == 0 ? -1 : (int)theta * 100, VJ_INTERFACE, 2);
	}
	
	printf("Theta: %d\n", (int)theta);
}

int main()
{
    Serial serial((char*)COM_PORT);
    JoystickHandler handler;
	
	// Make sure that the vJoy driver is installed
	if (!vJoyEnabled())
	{
		printf("vJoy driver not enabled: Failed Getting vJoy attributes.\n");
		return -1;
	}
	// Make sure that we estabilished a connection to our Arduino
    if( !serial.IsConnected() ) 
	{
		printf("An Arduino is not connected to %s.\n", COM_PORT);
		return -2;
	}
	// Make sure that the device is free or otherwise available
	VjdStat status = GetVJDStatus(VJ_INTERFACE);
	if( status != VJD_STAT_FREE || !AcquireVJD(VJ_INTERFACE) )
	{
		printf("The device #%d isn't available!", VJ_INTERFACE);
		return -3;
	}
	// TODO: Make sure we're interfacing to an actual Wii Controller
	
    // Register all the clickable buttons
    for(int i = X; i <= Home; ++i)
    {
		handler.registerCallback(i, DOWN, onKeyDown);
		handler.registerCallback(i, UP, onKeyUp);
    }
    // Register the analog sticks
	handler.registerCallback(LS, XMOVE, onAnalogMove);
	handler.registerCallback(LS, YMOVE, onAnalogMove);
	handler.registerCallback(RS, XMOVE, onAnalogMove);
	handler.registerCallback(RS, YMOVE, onAnalogMove);
	
	// And at last, the main loop. It reads a packet from the Arduino and passes it to the handler,
	// which, in turn, fires the correct events in response to the right packets.
    char pckt;
	while( 1 )
    {
		//Read two bytes at a time
		if( serial.ReadData(&pckt, 1) == 1 )
		{
			// The first byte contains info regarding what key we're talking about.
			// The second byte contains info on the specified button.
			handler.handleEvent(pckt & 0b00011111, (char)((unsigned char)pckt >> 5) );
		}
		Sleep(SLEEP_MS);
    }
    
    return 0;
}
