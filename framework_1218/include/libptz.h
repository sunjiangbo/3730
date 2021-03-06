#ifndef	_LIB_PTZ_H 
#define	_LIB_PTZ_H
#include "libgps.h"
#ifdef __cplusplus
extern "C"{
#endif

typedef enum _PTZ_SPEED
{
	PTZ_SPEED_START,
	PTZ_SPEED_1,
	PTZ_SPEED_2,
	PTZ_SPEED_3,
	PTZ_SPEED_4,
	PTZ_SPEED_5,
	PTZ_SPEED_END
}PTZ_SPEED;

typedef enum _PTZ_TYPE
{
	PTZ_TYPE_START,
	PTZ_TYPE_PELCOD,
	PTZ_TYPE_PELCOP,
	PTZ_TYPE_END
}PTZ_TYPE;

typedef struct _PTZ_HANDLE
{
	LIBGPS_OBJ *pgps;
	PTZ_TYPE ptztype;
}LIBPTZ_OBJ;


LIBPTZ_OBJ *PTZ_INIT();
succeed_type PTZ_SET_SPEED(LIBPTZ_OBJ *phandle, PTZ_SPEED speed);
succeed_type PTZ_SET_UP(LIBPTZ_OBJ *phandle);
succeed_type PTZ_SET_DOWN(LIBPTZ_OBJ *phandle);
succeed_type PTZ_SET_LEFT(LIBPTZ_OBJ *phandle);
succeed_type PTZ_SET_RIGHT(LIBPTZ_OBJ *phandle);
succeed_type PTZ_SET_ZOOMIN(LIBPTZ_OBJ *phandle);
succeed_type PTZ_SET_ZOOMOUT(LIBPTZ_OBJ *phandle);
succeed_type PTZ_SET_AUTOFOCUS(LIBPTZ_OBJ *phandle);
succeed_type PTZ_SET_AUTOIRIS(LIBPTZ_OBJ *phandle);
succeed_type PTZ_SET_PRESET(LIBPTZ_OBJ *phandle);
succeed_type PTZ_GOTO_PRESET(LIBPTZ_OBJ *phandle, unsigned int presetnum);

#ifdef __cplusplus
}
#endif
#endif  
