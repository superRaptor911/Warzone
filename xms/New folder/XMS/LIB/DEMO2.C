/*

XMS test program for XMS library, copyright (C) 2002 by DM&P.
This example will test performance of XMS library.

*/


#include "xms.h"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <alloc.h>

#define BUF_SIZE  8192
#define TEST_CNT  10240

void main()
{
  unsigned int  Handle;
  char          *pcBuf;
  clock_t       c1, c2;
  int           i;

  printf("\nDM&P XMS Test Program, %s %s.\n\n", __DATE__, __TIME__);

  /* Initialize XMS driver */
  if(XMS_Init() == 0)
  {
    printf("Unable to find XMS driver.\n");
    return;
  }

  /* Allocate memory form heap */
  pcBuf = (char *)malloc(BUF_SIZE);

  /* Allocate XMS for test */
  if(XMS_Allocate(BUF_SIZE / 1024, &Handle) == 0)
  {
    printf("Unable to allocate XMS.\n");
    return;
  }

  /* Copy memory buffer to XMS by TEST_CNT times */
  printf("Copy memory buffer to XMS...\n");
  c1 = clock();
  for(i = 0; i < TEST_CNT; i++)
    XMS_CopyToXMS(Handle, 0, pcBuf, BUF_SIZE);
  c2 = clock();

  /* Calculate time and performance */
  printf("Buffer copied: %d MB\n", (BUF_SIZE / 1024) * (TEST_CNT / 1024));
  printf("Time: %5.2f ms\n", (c2 - c1) * (1000 / CLK_TCK));
  printf("Performance: %d MB/S\n",
           (long)((BUF_SIZE / 1024) * (TEST_CNT / 1024)) / (long)
             ((c2 - c1) / CLK_TCK));

  printf("\n");

  /* Reverse the test, copy XMS to memory buffer */
  printf("Copy XMS to memory buffer...\n");
  c1 = clock();
  for(i = 0; i < TEST_CNT; i++)
    XMS_CopyFromXMS(pcBuf, Handle, 0, BUF_SIZE);
  c2 = clock();

  /* Calculate time and performance */
  printf("Buffer copied: %d MB\n", (BUF_SIZE / 1024) * (TEST_CNT / 1024));
  printf("Time: %5.2f ms\n", (c2 - c1) * (1000 / CLK_TCK));
  printf("Performance: %d MB/S\n",
           (long)((BUF_SIZE / 1024) * (TEST_CNT / 1024)) / (long)
             ((c2 - c1) / CLK_TCK));

  /* Free memory allocated from heap */
  free(pcBuf);

  /* Free XMS we allocated */
  XMS_Free(Handle);
}
