#include "board.h"
#include "mw.h"

extern core_t core;


void serialPrint(serialPort_t *instance, const char *str)
{
    uint8_t ch;
    while ((ch = *(str++)) != 0) {
        serialWrite(instance, ch);
    }
}

inline uint32_t serialGetBaudRate(serialPort_t *instance)
{
    return instance->baudRate;
}

inline void serialWrite(serialPort_t *instance, uint8_t ch)
{
	if( core.useVComMultiwii == true && instance->ByPassToVCom == true )
	{
		Hw_VCom_Putch(ch);
	}
	else
	{
		instance->vTable->serialWrite(instance, ch);
	}
}

inline uint8_t serialTotalBytesWaiting(serialPort_t *instance)
{
	if( core.useVComMultiwii == true && instance->ByPassToVCom == true )
	{
		return Hw_VCom_IsReceived();
	}
	else
	{
		return instance->vTable->serialTotalBytesWaiting(instance);
	}
}

inline uint8_t serialRead(serialPort_t *instance)
{
	if( core.useVComMultiwii == true && instance->ByPassToVCom == true )
	{
		return Hw_VCom_Getch();
	}
	else
	{
		return instance->vTable->serialRead(instance);
	}
}

inline void serialSetBaudRate(serialPort_t *instance, uint32_t baudRate)
{
    instance->vTable->serialSetBaudRate(instance, baudRate);
}

inline bool isSerialTransmitBufferEmpty(serialPort_t *instance)
{
    return instance->vTable->isSerialTransmitBufferEmpty(instance);
}

