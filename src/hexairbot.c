#include "board.h"
#include "mw.h"

// driver for SUMD receiver using UART2

#define HEXAIRBOT_MAX_CHANNEL 8

static bool hexairbotFrameDone = false;
static uint16_t hexairbotReadRawRC(uint8_t chan);

static uint32_t hexairbotChannelData[HEXAIRBOT_MAX_CHANNEL];


void hexairbotInit(rcReadRawDataPtr *callback)
{
    core.rcvrport = 0;
    if (callback) 
        *callback = hexairbotReadRawRC;
}


void hexairbotSetData(uint16_t index, uint16_t c)
{
    if( index == (HEXAIRBOT_MAX_CHANNEL-1) )
    {
        hexairbotFrameDone = true;    
    }
    
    hexairbotChannelData[index] = c;
}


bool hexairbotFrameComplete(void)
{
    uint8_t b;

    if (hexairbotFrameDone) 
    {
        hexairbotFrameDone = false;
        return true;
    }
    return false;
}

static uint16_t hexairbotReadRawRC(uint8_t chan)
{
    return hexairbotChannelData[chan];
}
