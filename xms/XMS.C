/*      SMIXC is Copyright 1995 by Ethan Brodsky.  All rights reserved      */

/* �� XMS.C ��������������������������������������������������������������� */

#ifdef __cplusplus
 extern "C" {
 #endif


  int xms_installed(void);
  void xms_init(void);

  unsigned int xms_getversion(void);
  unsigned int xms_getfreemem(void);

  int xms_allocate(int *handle,int size);
  int xms_reallocate(int handle, unsigned int newsize);
  int xms_free(int *handle);

  typedef struct
    {
      unsigned long length;         /* Length must be a multiple of two */
      unsigned int  sourcehandle;
      unsigned long sourceoffset;
      unsigned int  desthandle;
      unsigned long destoffset;
    } MOVEPARAMS;

  int xms_move(MOVEPARAMS far *params);

/* ������������������������������������������������������������������������ */

#include <mem.h>

#pragma option -w- // Prevent "Function should return a value" warning

/* Disable stack overflow checking.  The code for detecting stack overflows */
/* assumes that it is working with the program's stack.  SMIX has a number  */
/* of routines called from interrupts, when the system may be using another */
/* stack.  For this reason, the overflow checking will detect an overflow   */
/* when there is none. Disabling checking for SMIX modules eliminates this. */
#pragma option -N-

static void far *xms_driver = NULL;                /* Pointer to XMS driver */

int xms_installed(void)
  {
    asm {
      mov  ax, 0x4300
      int  0x2F
    }
    if (_AL == 0x80)
      return 1;
    else
      return 0;
  }

void xms_init()
  {
    asm {
      mov  ax, 0x4310
      int  0x2F
      mov  word ptr [xms_driver], bx
      mov  word ptr [xms_driver+2], es
    }
  }

/* ������������������������������������������������������������������������ */

unsigned int xms_getversion()
  {
    asm {
      mov  ah, 0x00
      call [xms_driver]
    }
  }

/* ������������������������������������������������������������������������ */

unsigned int xms_getfreemem()
  {
    asm {
      mov  ah, 0x08
      call [xms_driver]
      mov  ax, dx
    }
  }

/* ������������������������������������������������������������������������ */

int xms_allocate(int *handle,int size)
  {
    asm {
      mov  ah, 0x09
      mov  dx, size
      call [xms_driver]
      les  di, [handle]
      mov  es:[di], dx
    }
  }

/* ������������������������������������������������������������������������ */

int xms_reallocate(int handle, unsigned int newsize)
  {
    asm {
      mov  ah, 0x0F
      mov  bx, newsize
      mov  dx, handle
      call [xms_driver]
    }
  }

/* ������������������������������������������������������������������������ */

int xms_free(int *handle)
  {
    asm {
      mov  ah, 0x0A
      les  di, [handle]
      mov  dx, es:[di]
      call [xms_driver]
      mov  word ptr es:[di], 0
    }
  }

/* ������������������������������������������������������������������������ */

int xms_move(MOVEPARAMS far *params)
  {
    asm {
      push ds
      push es
      mov  ax, ds
      mov  es, ax
      mov  ah, 0x0B
      lds  si, [params]
      call es:[xms_driver]        // necessary to work in huge model
      pop  es
      pop  ds
    }
  }

/*��������������������������������������������������������������������������*/

#pragma option -w  // Re-enable "function should return a value" warning

 #ifdef __cplusplus
 }
 #endif