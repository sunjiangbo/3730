#ifndef _GLOBAL_H
#define _GLOBAL_H

#ifdef _cplusplus
extern "C" {
#endif
#include "ParamMgr.h"

extern bool g_VideoRequestFlag;
extern bool g_VideoResolutionChanged;

extern bool ResetALGParmbyCurrentTimeIf(bool bForce);
//extern bool Ident_WriteTextInPic(HWND hwnd,void *pDataBuf, int m_Height, int m_width , CString strText);
//extern bool Ident_MakeDirExist(CString pathname);
//extern CString Ident_GetModulePath();

#ifdef _cplusplus
}
#endif

#endif // _GLOBAL_H
