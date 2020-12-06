/*

XMS example for XMS library, copyright (C) 2002 by DM&P.
This example will show you how to XMS library.

*/

#include "xms.h"
#include <stdio.h>
#include <string.h>

void main()
{
  unsigned int  Handle;
  unsigned char cLockCounter;
  unsigned char cAvailHandle;
  unsigned int  nSize;
  unsigned int  nMax, nTotal;
  char          szStr[] = "XMS test string";
  int           nStrLen = strlen(szStr) + 1;

  printf("\nDM&P XMS Demo Example, %s %s.\n\n", __DATE__, __TIME__);

  /* Initialize XMS driver */
  if(XMS_Init() == 0)
  {
    printf("Unable to find XMS driver.\n");
    return;
  }

  /* Show XMS version */
  printf("XMS Version: %x\n", XMS_GetVer());

  /* Get free memory and max available block size */
  XMS_GetFree(&nMax, &nTotal);
  printf("Free memory: max=%u KB, total=%u KB.\n", nMax, nTotal);

  printf("\n");

  /* Allocate 1 KB from XMS for test */
  printf("Allocate 1 KB memory: ");
  if(XMS_Allocate(1, &Handle) == 0)
  {
    printf("failed!\n");
    return;
  }

  printf("handle=%u.\n", Handle);

  /* Show handle information */
  XMS_GetInfo(Handle, &cLockCounter, &cAvailHandle, &nSize);
  printf("Block info: ");
  printf("lock counter=%u, ", cLockCounter);
  printf("available handle=%u, ", cAvailHandle);
  printf("size=%u KB.\n", nSize);


  /* Show free memory after allocating memory */
  XMS_GetFree(&nMax, &nTotal);
  printf("Free memory: max=%u KB, total=%u KB.\n", nMax, nTotal);

  printf("\n");

  /* Show original string */
  printf("szStr = \"%s\"\n", szStr);

  /* Copy string to XMS */
  printf("Copy string to XMS.\n");
  XMS_CopyToXMS(Handle, 0, szStr, nStrLen);

  /* Clear the string and show it */
  printf("Clear string: ");
  memset(szStr, 0, sizeof(nStrLen));
  printf("szStr=\"%s\"\n", szStr);

  /* Restore string content from XMS */
  printf("Restore string: ");
  XMS_CopyFromXMS(szStr, Handle, 0, nStrLen);
  printf("szStr=\"%s\"\n", szStr);

  /* Free XMS we allocated */
  XMS_Free(Handle);

  printf("\n");

  /* Show free memory again. It should be the same as the first free memory query. */
  XMS_GetFree(&nMax, &nTotal);
  printf("Free memory: max=%u KB, total=%u KB.\n", nMax, nTotal);
}
