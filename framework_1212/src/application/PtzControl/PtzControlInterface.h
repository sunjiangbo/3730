#ifndef PTZCONTROLINTERFACE_H
#define PTZCONTROLINTERFACE_H

#define PTZ_PREPOINT_NUM_MAX 128

typedef enum _PTZ_TYPE
{
	PTZ_TYPE_START,
	PTZ_TYPE_PELCOD,
	PTZ_TYPE_PELCOP,
	PTZ_TYPE_END,
}PTZ_TYPE;

typedef enum _PTZ_SPEED
{
	PTZ_SPEED_START,
	PTZ_SPEED_1 = 0x00, 
	PTZ_SPEED_2 = 0x1f,
	PTZ_SPEED_3 = 0x2f,
	PTZ_SPEED_4 = 0x3f,
	PTZ_SPEED_5 = 0xff,
	PTZ_SPEED_END,
}PTZ_SPEED;

class  PtzControlInterface{	
public:
	virtual bool PtzInit(UINT portNo = 1, UINT baud = CBR_9600, char parity = 'N', UINT databits = 8, 
		UINT stopsbits = 1, DWORD dwCommEvents = EV_RXCHAR , PTZ_TYPE ptzType = PTZ_TYPE_PELCOD ,
		WORD speed = 0x3f, UINT logcialNum = 0x01) = 0;
	virtual bool PtzSetUp(WORD speed) = 0;
	virtual bool PtzSetDown(WORD speed) = 0;
	virtual bool PtzSetLeft(WORD speed) = 0;
	virtual bool PtzSetRight(WORD speed) = 0;
	virtual bool PtzSetZoomIn() = 0;
	virtual bool PtzSetZoomOut() = 0;
	virtual bool PtzSetAutoFocus() = 0;
	virtual bool PtzAutoIRIS() = 0;
	virtual bool PtzPreSet(BYTE pre) = 0;
	virtual bool PtzGoToPre(BYTE pre) = 0;
	virtual bool PtzDelPre(BYTE pre) = 0;
	virtual bool PtzClose() = 0;
};

extern bool CreatePtzControl(PtzControlInterface** ptzControl);
#endif
