/* Any comment in which (?) appears indicates that I've reproduced whatever was done in the undocumented original source.
 * Unfortunately it does not explain why any of that must be done, but I have asserted that those instructions... work.
 * - Source: http://playground.arduino.cc/Main/WiiClassicController?action=sourceblock&num=2
*/

#define I2C_ADDR    0x52
#define PACKET_SIZE 6
//If defined, input is repeated
#define REPEAT_INPUT
//Millisecond delay before repeating
#define REPEAT_DELAY 250
//Repeats per second
#define REPEAT_RATE  35
//#define DEBUG

#ifdef DEBUG
#define SLEEP_FOR   500
#else
#define SLEEP_FOR   10
#endif

// BIT0, BIT1 check if a bit is set or unset in g_curData and the opposite in g_oldData
#define BIT0(n, b) (!_bit(g_curData[n], b) && _bit(g_oldData[n], b))
#define BIT1(n, b) (_bit(g_curData[n], b) && !_bit(g_oldData[n], b))

#include <Wire.h>

enum Keys
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

byte g_oldData[PACKET_SIZE];
byte g_curData[PACKET_SIZE];

#ifdef REPEAT_INPUT
byte g_evtToRepeat = 255;
bool g_isRepeating = false;
unsigned long g_oldRepeatMillis;
unsigned long g_millisAccumulator = 0;
#endif

void fireEvent(byte evtID, byte info, bool analogStick = false)
{
    #ifdef DEBUG
    Serial.print("Event fired; ID: ");
    Serial.print(evtID, DEC);
    Serial.print(", INFO: ");
    Serial.println(info, BIN);
    #else
    // Send the actual packet
    Serial.write(evtID | info << 5);
    #endif
    
    #ifdef REPEAT_INPUT
    // If a keypress event was fired, set g_evtToRepeat to 255 on keyup and evtID on keydown.
    if(!analogStick)
    {
        g_millisAccumulator = 0;
        g_oldRepeatMillis = millis();
        if(info)
        {
            g_evtToRepeat = 255;
            //Also, reset repeat status on keyup
            g_isRepeating = false;
        }
        else
        {
            g_evtToRepeat = evtID;
        }
    }
    #endif
}

bool _bit(int n, byte bit)
{
    return n & (1 << bit);
}

byte _getLSX(byte *data)
{
    int val = (data[0] & 0x3f);
    return (val < 24 ? 0 : val > 38 ? 2 : 1);
}

byte _getLSY(byte *data)
{
    int val = (data[1] & 0x3f);
    return (val < 24 ? 0 : val > 38 ? 2 : 1);
}

byte _getRSX(byte *data)
{
    int val = ((data[0] & 0xc0) >> 3) + ((data[1] & 0xc0) >> 5) + ((data[2] & 0x80) >> 7);
    return (val < 8 ? 0 : val > 22 ? 2 : 1);
}

byte _getRSY(byte *data)
{
    int val = (data[2] & 0x1f);
    return (val < 8 ? 0 : val > 22 ? 2 : 1);
}

void updateStatus()
{
    // Key packets send 0 or 1 as info, 0 for keydown and 1 for keyup.
    
    if( BIT0(5, 3) )
        fireEvent(X, 0);
    else if( BIT1(5, 3) )
        fireEvent(X, 1);
        
    if( BIT0(5, 4) )
        fireEvent(A, 0);
    else if( BIT1(5, 4) )
        fireEvent(A, 1);
        
    if( BIT0(5, 5) )
        fireEvent(Y, 0);
    else if( BIT1(5, 5) )
        fireEvent(Y, 1);
        
    if( BIT0(5, 6) )
        fireEvent(B, 0);
    else if( BIT1(5, 6) )
        fireEvent(B, 1);
        
    if( BIT0(5, 0) )
        fireEvent(Up, 0);
    else if( BIT1(5, 0) )
        fireEvent(Up, 1);
        
    if( BIT0(4, 6) )
        fireEvent(Down, 0);
    else if( BIT1(4, 6) )
        fireEvent(Down, 1);
        
    if( BIT0(4, 7) )
        fireEvent(Right, 0);
    else if( BIT1(4, 7) )
        fireEvent(Right, 1);
        
    if( BIT0(5, 1) )
        fireEvent(Left, 0);
    else if( BIT1(5, 1) )
        fireEvent(Left, 1);
    
    if( BIT1(3, 7) && BIT1(3, 6) && BIT1(3, 5) )
        fireEvent(L1, 0);
    else if( BIT0(3, 7) && BIT0(3, 6) && BIT0(3, 5) )
        fireEvent(L1, 1);
    
    if( BIT1(3, 0) && BIT1(3, 1) && BIT1(3, 2) && BIT1(3, 3) && BIT1(3, 4) )
        fireEvent(R1, 0);
    else if( BIT0(3, 0) && BIT0(3, 1) && BIT0(3, 2) && BIT0(3, 3) && BIT0(3, 4) )
        fireEvent(R1, 1);
        
    if( BIT0(5, 7) )
        fireEvent(L2, 0);
    else if( BIT1(5, 7) )
        fireEvent(L2, 1);
        
    if( BIT0(5, 2) )
        fireEvent(R2, 0);
    else if( BIT1(5, 2) )
        fireEvent(R2, 1);
        
    if( BIT0(4, 4) )
        fireEvent(Select, 0);
    else if( BIT1(4, 4) )
        fireEvent(Select, 1);
        
    if( BIT0(4, 2) )
        fireEvent(Start, 0);
    else if( BIT1(4, 2) )
        fireEvent(Start, 1);
        
    if( BIT0(4, 3) )
        fireEvent(Home, 0);
    else if( BIT1(4, 3) )
        fireEvent(Home, 1);
    
    // Syntax: if(GETaSb != GETOaSb) means "if the current a analog stick changed in the b coordinate"
    // And basically all this does is send 1 if the stick is at rest, 0 if it's pushed in the negatives and 1 if in the opposites.
    // Also, the leftmost bit if 1 for Y-values and 0 for X-values.

    if(_getLSX(g_curData) != _getLSX(g_oldData) )
        fireEvent(LS, 0 | _getLSX(g_curData), true);
    if(_getLSY(g_curData) != _getLSY(g_oldData) )
        fireEvent(LS, 4 | _getLSY(g_curData), true);
    if(_getRSX(g_curData) != _getRSX(g_oldData) )
        fireEvent(RS, 0 | _getRSX(g_curData), true);
    if(_getRSY(g_curData) != _getRSY(g_oldData) )
        fireEvent(RS, 4 | _getRSY(g_curData), true);
    
    memcpy(g_oldData, g_curData, PACKET_SIZE);
}

void updateData()
{
    //Request 6 bytes from the controller
    Wire.requestFrom(I2C_ADDR, PACKET_SIZE);
    
    int i = 0;
    while(Wire.available())
    {
        byte packet = Wire.read();
        // (?) Decoding as seen in the original source. If anything it makes everything a bit nicer to decode.
        packet = (packet ^ 0x17) + 0x17;
        #ifdef DEBUG
        if(g_oldData[i] != packet)
        {
            Serial.print("PACKET #");
            Serial.print(i);
            Serial.print(": 0b");
            //Serial.print("", BIN) does not support leading zeroes.
            for (unsigned int mask = 128; mask; mask >>= 1) 
            {
               Serial.print(mask&packet?'1':'0');
            }
            Serial.print("\t0d");
            Serial.print(packet, DEC);
            Serial.println();
        }
        #endif
        g_curData[i++] = packet;
    }
    // (?) Send a zero to request new bytes. Undocumented, but verified to work.
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(0x00);
    Wire.endTransmission();
}

void setup() 
{
    //Join I2C bus as master
    Wire.begin();
    //Send address 
    Wire.beginTransmission(I2C_ADDR);
    Wire.write(0x40); 
    Wire.write(0x00);
    Wire.endTransmission();
    
    /* Wait for the controller to correctly initialize.
     * Apparently as soon as it 'turns on', it sends a bunch of 1s.
     * Then it sends a sequence which appears random for all bytes but the first.
     * The unchanging byte is 0b01011111, 95 in decimal.
    */
    do
    {
        updateData();
        delay(10);
    } while( g_curData[0] != 95 );
    
    //Now that g_curData contains the correct default values, we can initialize g_oldData as well.
    memcpy(g_oldData, g_curData, PACKET_SIZE);
    
    //And start sending data (or printing debug information for what matters).
    Serial.begin(9600);
}

void loop() 
{
    updateData();
    updateStatus();
    
    #ifdef REPEAT_INPUT
    if(g_evtToRepeat != 255)
    {
        unsigned long curMillis = millis();
        g_millisAccumulator += curMillis - g_oldRepeatMillis;
        
        #ifdef DEBUG
        Serial.print("g_millisAccumulator: ");
        Serial.println(g_millisAccumulator);
        #endif
        
        if(!g_isRepeating && g_millisAccumulator >= REPEAT_DELAY)
        {
            g_millisAccumulator = 0;
            g_isRepeating = true;
        }
        else if(g_isRepeating && g_millisAccumulator >= 1000.0 / REPEAT_RATE)
        {
            g_millisAccumulator = 0;
            fireEvent(g_evtToRepeat, 0);
        }
        
        g_oldRepeatMillis = curMillis;
    }
    #endif
    
    delay(SLEEP_FOR);
}
