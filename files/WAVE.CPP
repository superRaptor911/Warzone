
long int counter=0;
  long          LinearAddress;
  unsigned int  Page, OffSet;
  unsigned char TimeConstant;

struct HeaderType {
  long         RIFF;      //RIFF header
  char         NI1 [4];   //not important
  long         WAVE;      //WAVE identifier
  long         fmt;       //fmt  identifier
  char         NI2 [6];   //not important
  unsigned int Channels;  //channels 1 = mono; 2 = stereo
  long         Frequency; //sample frequency
  char         NI3 [6];   //not important
  unsigned int BitRes;    //bit resolution 8/16 bit
  long         data;      //data identifier
  long         datasize;  //size of data chunk
} Header;



unsigned int    Base;          //Sound Blaster base address

char            WaveFile [60]; //File name for the wave file to be played

/****************************************************************************
** Checks to see if a Sound Blaster exists at a given address, returns     **
** true if Sound Blaster found, false if not.                              **
****************************************************************************/
char ResetDSP(unsigned int Test)
{
  //Reset the DSP
  outportb (Test + 0x6, 1);
  delay(10);
  outportb (Test + 0x6, 0);
  delay(10);
  //Check if reset was succesfull
  if (((inportb(Test + 0xE) & 0x80) == 0x80) && (inportb (Test + 0xA) == 0xAA)) {
    //DSP was found
    Base = Test;
    return (1);
  } else
    //No DSP was found
    return (0);
}

/****************************************************************************
** Send a byte to the DSP (Digital Signal Processor) on the Sound Blaster  **
****************************************************************************/
void WriteDSP(unsigned char Value)
{
  //Wait for the DSP to be ready to accept data
  while ((inportb(Base + 0xC) & 0x80) == 0x80);
  //Send byte
  outportb (Base + 0xC, Value);
}




void LoadVoice(int i, char *FileName)
{
  FILE *WAVFile;
  WAVFile = fopen(FileName, "rb");
  if (WAVFile == NULL)
   {
    file_save(log_file,"\nLoadVoice unable to load ",FileName);
    return;
  }
  file_save(log_file,"\nLoadVoice loading ",FileName);
  fread(&Header, sizeof (Header), 1, WAVFile);

  //Check RIFF, WAVE, fmt and data headers
  if ((Header.RIFF != 0x46464952) ||
      (Header.WAVE != 0x45564157) ||
      (Header.fmt  != 0x20746D66) ||
      (Header.data != 0x61746164)) 
  {
    file_save(log_file,"file ",FileName);
    file_save(log_file," is not a ","wave file",SPACE);
    return;
  }
    file_save(log_file,"file ",FileName);
    file_save(log_file," is a ","wave file",SPACE);
  int num=0,rem=0;
  char data[23000];
      Voice[i].SoundLength=Header.datasize;
      Voice[i].size=Header.datasize;
    num=Header.datasize/M_CHUNK;
    rem=Header.datasize%M_CHUNK;
      if (i==0)
      {
        Voice[i].index=0;
      }
      else
      {
        Voice[i].index=Voice[i-1].index+Voice[i-1].size;
      }
      long index=Voice[i].index;
    for (int k = 0; k < num+1; k++)
    {
        if (k==num)
        {
            fread(data,rem, 1, WAVFile);
            XMS_CopyToXMS(sound_handle,index,data,rem);
        }
        else
        {
            fread(data,M_CHUNK, 1, WAVFile);
      XMS_CopyToXMS(sound_handle,index,data,M_CHUNK);
            index+=M_CHUNK;
        }
    }
    file_save(log_file,"and its index"," ",SPACE);
    file_save(log_file," in sound_handle is ",Voice[i].index,NOSPACE);
    file_save(log_file,"and size ","is",SPACE);
    file_save(log_file," ",Voice[i].size,NOSPACE);
  fclose (WAVFile); //Close the file
    if (Voice[i].index+Voice[i].size>3600000L)
  {
    file_save(log_file,"--------warning ","sound_handle 90 percent full------");
  }
}
//char xxx[CHUNK+2];

long int Loadmusic(char *FileName)
{
  FILE *WAVFile;
  WAVFile = fopen(FileName, "rb");
  if (WAVFile == NULL)
   {
    file_save(log_file,"Loadmusic unable to load ",FileName);
    return(0);
  }
  file_save(log_file,"Loadmusic loading ",FileName);
  fread(&Header, sizeof (Header), 1, WAVFile);

  //Check RIFF, WAVE, fmt and data headers
  if ((Header.RIFF != 0x46464952) ||
      (Header.WAVE != 0x45564157) ||
      (Header.fmt  != 0x20746D66) ||
      (Header.data != 0x61746164)) 
  {
    file_save(log_file,"file ",FileName);
    file_save(log_file," is not a ","wave file",SPACE);
    return (0);
  }
    file_save(log_file,"file ",FileName);
    file_save(log_file," is a ","wave file",SPACE);
  int num=0,rem=0;
  char data[23000];
    Header.datasize;
    num=Header.datasize/M_CHUNK;
    rem=Header.datasize%M_CHUNK;
    long index=0;
    for (int k = 0; k < num+1; k++)
    {
        if (k==num)
        {
            fread(data,rem, 1, WAVFile);
            XMS_CopyToXMS(music_handle,index,data,rem);
        }
        else
        {
            fread(data,M_CHUNK, 1, WAVFile);
      XMS_CopyToXMS(music_handle,index,data,M_CHUNK);
            index+=M_CHUNK;
        }
    }
    file_save(log_file,"size of ",FileName,SPACE);
    file_save(log_file," ",Header.datasize,NOSPACE);
  fclose (WAVFile); //Close the file
  return(Header.datasize);
  
}

