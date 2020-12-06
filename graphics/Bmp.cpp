#include <stdio.h>
#include <stdlib.h>
#include ".\graphics\gomphics.h"

#define byte char

struct bmpHeaderType
{
   char magic1, magic2;			// identity 'BM'
   long fileSize;				// size of file in bytes
   long reserved;				// always 0
   long pixelOffset;			// offset of data
   long bmiSize;				// remaining size of header in file, should be 40
   long cols, rows;				// width and height of image
   int  nPlanes;				// number of color planes, should be 1
   int  bitsPerPixel;			// number of bits used to represent a pixel
   long compression, cmpSize;	// compressed image?
   long xScale, yScale;
   long colors, impColors;
};

struct bmpColor
{
	unsigned char color_b;
	unsigned char color_g;
	unsigned char color_r;
};


void read_bmp_header (FILE *dataFile, bmpHeaderType &bmpHeader)
{
	fread (&bmpHeader, sizeof (bmpHeaderType), 1, dataFile);
}

int saveBMP24(long x1,long y1,long x2,long y2,char *filename)
{
	bmpHeaderType bmpHeader;			// to hold image information]
	bmpColor clr;
	FILE *saveFile; 					// file pointer

	saveFile = fopen (filename, "wb");	// open the file
	if(saveFile == NULL)
	{
		return 0;
	}

	int dx = x2 - x1;
	int dy = y2 - y1;

	long size = dx * dy * 3 + 54;

	bmpHeader.magic1		= 'B';
	bmpHeader.magic2		= 'M';
	bmpHeader.fileSize		= size;
	bmpHeader.reserved		= 0;
	bmpHeader.pixelOffset	= 54;
	bmpHeader.bmiSize		= 40;
	bmpHeader.cols			= dx;
	bmpHeader.rows			= dy;
	bmpHeader.nPlanes		= 1;
	bmpHeader.bitsPerPixel	= 24;
	bmpHeader.compression	= 0;
	bmpHeader.cmpSize		= 0;
	bmpHeader.xScale		= dx;
	bmpHeader.yScale		= dy;
	bmpHeader.colors		= 0;
	bmpHeader.impColors		= 0;

	if(fwrite(&bmpHeader, sizeof(bmpHeader), 1, saveFile) == NULL)
	{
		fclose(saveFile);
		return 0;
	}
	
	for(int y = dy-1;y>=0;y--)
	{
		for (int x = 0; x < dx; x++)
		{
			long color  = getpixel(x1+x,y1+y);
			clr.color_b = color & 0x0000FF;
			clr.color_g = color >> 8  & 0xFF;
			clr.color_r = color >> 16 & 0xFF;
			fwrite(&clr, sizeof(clr), 1, saveFile);
		}
	}
	fclose(saveFile);
	return 1;
}

void showBMP(int x1,int y1,const char *filename)
{
	bmpHeaderType bmpHeader;		// to hold image information
	FILE *dataFile; 				// file pointer

	dataFile = fopen (filename, "rb");	// open the file

	read_bmp_header (dataFile,bmpHeader);

	fseek (dataFile, 54, SEEK_SET);	// start reading the image

	int width = bmpHeader.cols;		// read width from the header
	int height = bmpHeader.rows;
	int bpp = bmpHeader.bitsPerPixel;

	long byte1;
	long byte2;
	long byte3;
	long color;
	int x,y;
	if(bpp == 24)
	{
		for (y = height-1; y >= 0; y--)
		{
			for(x=0; x<=width; x++)
			{
				byte1 = (long)fgetc(dataFile);
				byte2 = (long)fgetc(dataFile)<<8;
				byte3 = (long)fgetc(dataFile)<<16;
				color = (0x00ffffff & (byte1 + byte2 + byte3));
				putpixel(x+x1,y1+y,color);
			}
		}
	}

	fclose (dataFile);				// close the file
}

int showBMP24(int x1,int y1,const char *filename)
{
	bmpHeaderType bmpHeader;		// to hold image information
	FILE *dataFile; 				// file pointer

	if(!(dataFile = fopen (filename, "rb")))	// open the file
	{
		return 0;
	}

	read_bmp_header (dataFile,bmpHeader);

	fseek (dataFile, 54, SEEK_SET);	// start reading the image

	int width = bmpHeader.cols;		// read width from the header
	int height = bmpHeader.rows;
	int bpp = bmpHeader.bitsPerPixel;

	long byte1;
	long byte2;
	long byte3;
	long color;
	int x,y;
	if(bpp == 24)
	{
		for (y = height-1; y >= 0; y--)
		{
			for(x=0; x<width; x++)
			{
				byte1 = (long)fgetc(dataFile);
				byte2 = (long)fgetc(dataFile) <<8;
				byte3 = (long)fgetc(dataFile) <<16;
				color = (0x00ffffff & (byte1 + byte2 + byte3));
				putpixel(x+x1,y1+y,color);
			}
		}
	}
	fclose (dataFile);				// close the file
	return 1;
}