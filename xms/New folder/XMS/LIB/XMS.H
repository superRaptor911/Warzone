
#ifndef _XMS_H_
#define _XMS_H_

/*

DM&P XMS Library.
Copyright (C) 2002 by DM&P.

This library is for DM&P product user only.

*/

#ifdef __cplusplus
extern "C" {
#endif

#define XMS_VERSION "0.10"

/* eXtended Memory Move Structure */
struct XMMS
{
  unsigned long lLen;       /* length */
  unsigned int  SrcHandle;  /* source handle */
  unsigned long lSrcOffset; /* source offset */
  unsigned int  DstHandle;  /* destination handle */
  unsigned long lDstOffset; /* destination offset */
};

int          XMS_Init();
unsigned int XMS_GetVer();
void         XMS_GetFree(unsigned int *pnMax, unsigned int *pnTotal);
int          XMS_Allocate(unsigned int nSize, unsigned int *pHandle);
int          XMS_Free(unsigned int Handle);
int          XMS_GetInfo(unsigned int Handle, unsigned char *pcLockCounter,
                         unsigned char *pcAvailHandle, unsigned int *nSize);
int          XMS_Copy(struct XMMS *pXMMS);
int          XMS_CopyToXMS(unsigned int DstHandle, unsigned long lDstOffset,
                           const void far *pSrc, unsigned long lLen);
int          XMS_CopyFromXMS(void far *pDst, unsigned int SrcHandle,
                             unsigned long lSrcOffset, unsigned long lLen);

#ifdef __cplusplus
}
#endif

#endif /* _XMS_H_ */
