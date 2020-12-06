void init_xms_handles();

void show_m_mouse(mouse &u);
void put_model_img(mouse &u);

void copy_xms_to_xms(unsigned int &dhandle,unsigned int &shandle);//2000kb
void copy_xms_to_xms(unsigned int &dhandle,unsigned int &shandle,long int size,long int doff,long int soff);
void direct_draw_rect(int x1,int y1,int x2,int y2);
void direct_draw_rect(int x1,int y1,int x2,int y2,colour c);
void direct_set_color(colour c);
void direct_copy_xms_to_vmem(unsigned int &handle,unsigned char *vmem,unsigned int size);
void direct_copy_xms_to_mem(unsigned int &handle,unsigned char *mem,int no);
void direct_copy_mem_to_mem(char *dmem,char *smem,long int index,long int size);
void direct_load_bmp(unsigned int &handle,char *file_name);
void direct_load_nbmp(unsigned int &handle,char *file_name,int i);
void direct_draw_bmp(unsigned int &handle,int no=30);
void direct_draw_nbmp(unsigned int &handle,int n);
void direct_draw_page(unsigned int &handle,int x1,int y1,int x2,int y2);
void direct_load_models(unsigned int &handle,int no,char *file_name);
void direct_draw_models(unsigned int &handle,int no,int x,int y);
void direct_draw_models_transparent(unsigned int &handle,int no,int x,int y);
void direct_copy_model_to_mem(char *mem,unsigned int &handle,int no);
void direct_put_image(char *bmp,int dx,int dy,long int x,long int y);
void direct_draw_rotate_models(char *b1,int no,float o);

void direct_draw_to_page(unsigned int &handle,int no,long int x,long int y);
void direct_draw_to_page(unsigned int &handle,int no,long int x,long int y,float o);
void direct_draw_to_page_trans(unsigned int &handle,int no,long int x,long int y);
void direct_draw_to_page_trans(unsigned int &handle,int no,long int x,long int y,float o);
int signum(float x);
float distance(float x,float y,float m,float c);

void add_to_string(char *string,int i);

void render_N();
void render_E(int no=30);
void render_G();

#define render_G() {if(skip==0){cam.show_cam();skip=1;}else{skip=0;}}
#define render_F() {if(skip==0){cam.show_cam(0);skip=1;}else{skip=0;}}

enum file_modes
{
	NEWLINE,SPACE,NOSPACE
};
enum log_code
{
	OBJECT_SIZE,INITIAL_MEM,FINAL_MEM,THETIME,START_TIMER,STOP_TIMER
};
long int itss,tits;
clock_t t1,t2;
int init_log()
{
	fstream myfile;
	myfile.open(".\\logs\\0.txt",ios::in);
	char data[20],data2[20];
	myfile>>data;
	myfile.close();
	myfile.open(".\\logs\\0.txt",ios::app|ios::trunc);
	myfile<<atoi(data)+1;
	myfile.close();
	runs=atoi(data)+1;
	itoa(atoi(data)+1,data2,10);
	strcpy(log_file,".\\logs\\");
	strcat(log_file,data2);
	strcat(log_file,".txt");
	myfile.close();
}
int logs(int code)
{
	if (code==INITIAL_MEM)
	{
        itss=farcoreleft();
        file_save(log_file,"initial main memory ",itss);
        return(1);
	}
	if (code==FINAL_MEM)
	{
		tits=farcoreleft();
        file_save(log_file,"main memory now ",tits);
        file_save(log_file,"memory used ",itss-tits);
        return(1);
	}
	if (code==THETIME)
	{
	struct date d;
	getdate(&d);
	file_save(log_file,"--------------------","-------------------",NOSPACE);
	file_save(log_file,"date ",d.da_day);
	file_save(log_file,":",d.da_mon,NOSPACE);
	file_save(log_file,":",d.da_year,NOSPACE);
	struct time t;
	gettime(&t);
	file_save(log_file,"and time ",t.ti_hour,SPACE);
	file_save(log_file,":",t.ti_min,NOSPACE);
	file_save(log_file,":",t.ti_sec,NOSPACE);
	return(1);
    }
    if (code==START_TIMER)
    {
    	t1=clock();
    	return(1);
    }
    if (code==STOP_TIMER)
    {
    	t2=clock();
    	file_save(log_file,"and the time taken is ",((t2-t1)/CLK_TCK),SPACE);
    	file_save(log_file," second","s",NOSPACE);
    	return(1);
    }
    return(1);
}

XMMS XMMS;
void init_xms_handles()
{
	XMS_Init();
	XMS_Allocate(3000,&model_handle);//for models
	XMS_Allocate(2000,&direct_page);//direct pages for menu
	XMS_Allocate(2000,&direct_page2);
	XMS_Allocate(2000,&direct_page5);//back buffer
	XMS_Allocate(26000,&map_page);
	XMS_Allocate(4000,&sound_handle);
	XMS_Allocate(4000,&music_handle);
}

int signum(float x)
{
	if (x>0)
	{
		return(1);
	}
	if (x==0)
	{
		return(0);
	}
	return(-1);
}

float distance(float x,float y,float m,float c)
{
	return(abs((y-m*x-c)/(sqrt(1+m*m))));
}

void add_to_string(char *string,int i)
{
	char stp[6];
	itoa(i,stp,10);
	strcat(string,stp);
}

void render_N()
{
	
      if(skip==0)
      {
        copy_xms_to_xms(direct_page5,visual_page);
        skip=1;
      }
      else
        skip=0;
}

void render_N(int nth)
{

      if(skip==0)
      {
      long int addr=1920000L;
	  addr*=nth;
        copy_xms_to_xms(direct_page5,visual_page,1920000L,0,addr);
        skip=1;
      }
      else
        skip=0;
}

void render_E(int no)
{
  if(skip==1)
  {
    direct_draw_bmp(direct_page5,no);
    skip=1;
  }
  else
    skip=0;
}





void direct_pixel_mem(unsigned int &handle,long int x,long int y,long int c)
{
	long int addr = ((y*(800)+x)*4);
	char ch[3];
	unsigned char r,g,b;
			b = c & 0x0000FF;
			g = c >> 8  & 0xFF;
			r = c >> 16 & 0xFF;
			ch[0]=r;
			ch[1]=g;
			ch[2]=b;
	  XMS_CopyToXMS(handle,addr,ch,4);

}

void line(int a, int b, int c, int d,long col)
{
	int i,u,s,v,d1x,d1y,d2x,d2y,m,n;
	u   = c-a;   
	v   = d-b;    
	d1x = signum(u); 
	d1y = signum(v); 
	d2x = signum(u);  
	d2y = 0;
	m   = abs(u);   
	n   = abs(v);  

	if (m<=n)
	{    
		d2x = 0;
		d2y = signum(v); 
		m   = abs(v);
		n   = abs(u);
	}

	s = m / 2;

	for (i=0;i<m+1;i++)
	{	
		putpixel(a,b,col);
		direct_pixel_mem(visual_page,a,b,col);
		s += n;        
		if (s >= m)
		{           
			s -= m;
			a += d1x;
			b += d1y;
		}
		else
		{
			a += d2x;
			b += d2y;
		}
	}
	_X = c;
	_Y = d;
}


void display_pixel_mem(long int x,long int y,long int c)
{
	long int addr = ((y*(800)+x)*4);
	char ch[3];
	long int offset_b;
	unsigned char r,g,b;
			b = c & 0x0000FF;
			g = c >> 8  & 0xFF;
			r = c >> 16 & 0xFF;
			ch[0]=r;
			ch[1]=g;
			ch[2]=b;
			setBank((int)(addr >> 16));
	       offset_b = addr & 0xFFFF;
	       vb[offset_b]=r;
	       vb[offset_b+1]=g;
	       vb[offset_b+2]=g;
}

void copy_xms_to_xms(unsigned int &dhandle,unsigned int &shandle)
{

XMMS.lLen = 2048000L;
XMMS.lDstOffset=0;
XMMS.lSrcOffset = 0;
XMMS.SrcHandle = shandle;
XMMS.DstHandle = dhandle;
XMS_Copy(&XMMS);
}


void copy_xms_to_xms(unsigned int &dhandle,unsigned int &shandle,long int size,long int doff,long int soff)
{
XMMS.lLen = size;
XMMS.lDstOffset=doff;
XMMS.lSrcOffset = soff;
XMMS.SrcHandle = shandle;
XMMS.DstHandle = dhandle;
XMS_Copy(&XMMS);
}


void direct_draw_to_page(unsigned int &handle,int no,long int x,long int y)
{
		long int mx=800,bpp=4,addr;
	    int size=models[no].width*4;
	    long saddr=models[no].index;
		//direct_copy_model_to_mem();
	for (long int i = y; i < y+models[no].height; i++)
	{
	  addr = ((i*(mx)+x)*bpp);//doff
	  copy_xms_to_xms(handle,model_handle,size,addr,saddr+(i-y)*size);
	}
}

void direct_draw_to_page(unsigned int &handle,int no,long int x,long int y,float o)
{
		long int mx=800,bpp=4,addr;
	    int size=models[no].width*4;
	    long saddr=models[no].index;
	    char byt[16000],bt[1000];
		direct_draw_rotate_models(byt,no,o);
	for (long int i = y; i < y+models[no].height; i++)
	{
	  addr = ((i*(mx)+x)*bpp);//doff
	  memcpy(bt,byt+size*(y-i),size);
	  XMS_CopyToXMS(handle,addr,bt,size);
	}
}


void direct_draw_to_page_trans(unsigned int &handle,int no,long int x,long int y)
{
			long int mx=800,bpp=4,addr;
	    int size=models[no].width*4;
	    long saddr=models[no].index;
	    long int index=0;
	    char byt[16000];
	    XMS_CopyFromXMS(byt,model_handle,models[no].index,models[no].size);
	    //direct_copy_model_to_mem(byt,model_handle,no);
	    int l=0;
	    char dat[3];
	    for (long int i = y; i < y+models[no].height; i++)
	    {
	    	addr = ((i*(mx)+x)*bpp);
	    	index=size*l;
	    	for (long int j = 0; j < size; )
	    	{
	    		dat[0]=byt[index+j];
	    		dat[1]=byt[index+j+1];
	    		dat[2]=byt[index+j+2];
	    		if ( dat[0]==char(-58) && dat[1]==char(53) && dat[2]==char(-67))
		        {
			      j+=4;
		        }
		        else
		        {
		        	XMS_CopyToXMS(handle,addr+j,dat,4);
			      j+=4;
		        }
	    		
	    	}
	    	l+=1;

	    }
	
}


void direct_draw_to_page_transparent(unsigned int &handle,int no,long int x,long int y,unsigned char a)
{
			long int mx=800,bpp=4,addr;
	    int size=models[no].width*4;
	    long saddr=models[no].index;
	    long int index=0;
	    unsigned char byt[4];
	    int l=0;
	    unsigned char dat[4];
	    unsigned char b=char(255);
	    for (long int i = y; i < y+models[no].height; i++)
	    {
	    	addr = ((i*(mx)+x)*bpp);
	    	index=size*l;
	    	for (long int j = 0; j < size; )
	    	{
	    		
	    		XMS_CopyFromXMS(dat,handle,addr+j,3);
	    		XMS_CopyFromXMS(byt,model_handle,models[no].index+j,3);
	    		dat[0]=(byt[0] * a + dat[0] * (b-a))/b;
	    		dat[1]=(byt[1] * a + dat[1] * (b-a))/b;
	    		dat[2]=(byt[2] * a + dat[2] * (b-a))/b;
		        XMS_CopyToXMS(handle,addr+j,dat,4);
			      j+=4;
	    	}
	    	l+=1;

	    }
	
}



void direct_draw_to_page_trans(unsigned int &handle,int no,long int x,long int y,float o)
{
	if (x<1 || x>799 || y<1 || y>415 || skip==0)
	{
		return;
	}
			long int mx=800,bpp=4,addr;
	    int size=models[no].width*4;
	    long saddr=models[no].index;
	    long int index=0;
	    char byt[16000];
	    XMS_CopyFromXMS(byt,model_handle,models[3].index,models[no].size);
	    direct_draw_rotate_models(byt,no,o);
	    //XMS_CopyFromXMS(byt,model_handle,models[no].index,models[no].size);
	    //direct_copy_model_to_mem(byt,model_handle,no);
	    int l=0;
	    char dat[3];
	    if (x+models[no].width>800)
	    {
	    	size=(models[no].width-x)*4;
	    }
	    for (long int i = y; i < y+models[no].height; i++)
	    {
	    	addr = ((i*(mx)+x)*bpp);
	    	index=size*l;
	    	for (long int j = 0; j < size; )
	    	{
	    		dat[0]=byt[index+j];
	    		dat[1]=byt[index+j+1];
	    		dat[2]=byt[index+j+2];
	    		if ( dat[0]==char(-58) && dat[1]==char(53) && dat[2]==char(-67))
		        {
			      j+=4;
		        }
		        else
		        {
		        	XMS_CopyToXMS(handle,addr+j,dat,4);
			      j+=4;
		        }
	    		
	    	}
	    	l+=1;

	    }
	
}

void direct_draw_rotate_models(char *b1,int no,float o)
{
	char b2[16000];
	direct_copy_xms_to_mem(model_handle,b2,no);
	float sn,cs,tn;
	cs=cos(o);
	sn=sin(o);
	tn=tan(o/2);
	int x2=models[no].width;
	int y2=models[no].height;
	long int ox=x2/2;
	long int oy=y2/2;
	long int xx,yy;
	int index;
	int count=0;
	if (o>2.4 && o<3.9)
	{
    for(int y = 0;y<y2;y++)
	{
	    for (int x = 0;x<x2;x++)
		{
			if (b2[count]==char(-58) && b2[count+1]==char(53) && b2[count+2]==char(-67))
			{
				count+=4;
			}
			else
			{
			xx=((x-ox)*cs)-(y-oy)*sn;
			yy=((y-oy)*cs)+(x-ox)*sn;
			xx+=ox;
			yy+=oy;
				if (xx>0 && xx<x2 && yy>0 && yy<y2)
				{
					index=(x2*yy+xx)*4;
					b1[index]=b2[(x2*y+x)*4];
					b1[index+1]=b2[(x2*y+x)*4 +1];
					b1[index+2]=b2[(x2*y+x)*4+2];
				}
			//xputpixel(xx+ox,yy+oy,bitmap[count],bitmap[count+1],bitmap[count+2]);
			count+=4;
		    }
		}
	}
	}
	else
	{

    for(int y = 0;y<y2;y++)
	{
	    for (int x = 0;x<x2;x++)
		{
			if (b2[count]==char(-58) && b2[count+1]==char(53) && b2[count+2]==char(-67))
			{
				count+=4;
			}
			else
			{
				xx=(x-ox);
				yy=(y-oy);

				xx=xx-yy*tn;

				
				yy=xx*sn+yy;
			

				xx=xx-yy*tn;

				xx+=ox;
				yy+=oy;

				if (xx>0 && xx<x2 && yy>0 && yy<y2)
				{
					index=(x2*yy+xx)*4;
					b1[index]=b2[(x2*y+x)*4];
					b1[index+1]=b2[(x2*y+x)*4 +1];
					b1[index+2]=b2[(x2*y+x)*4+2];
				}

			//xputpixel(xx+ox,yy+oy,bitmap[count],bitmap[count+1],bitmap[count+2]);
			count+=4;
		    }
		}
	}
	}
}

void direct_copy_xms_to_mem(unsigned int &handle,unsigned char *mem,int no)
{
	XMS_CopyFromXMS(mem,handle,models[no].index,models[no].size);
}

void direct_copy_mem_to_mem(char *dmem,char *smem,long int index,long int size)
{
	for (long int i = 0; i < size;)
	{
		if ( smem[index+i]==char(-58) && smem[index+i+1]==char(53) && smem[index+i+2]==char(-67))
		{
			i+=4;
		}
		else
		{
			dmem[i]=smem[i+index];
			dmem[i+1]=smem[i+index+1];
			dmem[i+2]=smem[i+index+2];
			i+=4;
		}
	}
}

void direct_copy_model_to_mem(char *mem,unsigned int &handle,int no)
{
	long int size=models[no].height*models[no].width*4;
	XMS_CopyFromXMS(mem,handle,models[no].index,size);
}

void direct_put_image(char *bmp,int dx,int dy,long int x,long int y)
{

	int size=dx*4;
	int bpp = 4;
	unsigned int offset_b;
	long int addr,r_addr=0;
	long int mx=800;
	for (long int i = y; i <y+dy ; i++)
	{
           addr = ((i*(mx)+x)*bpp);
	       setBank((int)(addr >> 16));
	       offset_b = addr & 0xFFFF;

	       if (offset_b+size>65535)
	       {
		memcpy(vb+offset_b,bmp+r_addr,65536-offset_b);
	       	r_addr+=65536-offset_b;
	       setBank(curBank+1);
	       	memcpy(vb,bmp+addr,size-(65536-offset_b));
	       }
	       else
	       {
	       	memcpy(vb+offset_b,bmp+r_addr,size);
	       } 
	       r_addr+=size; 
	}
}
void direct_copy_xms_to_vmem(unsigned int &handle,unsigned char *vmem,unsigned int size)
{
	XMS_CopyFromXMS(vmem,handle,0,size);
}

void direct_draw_models_transparent(unsigned int &handle,int no,int x,int y)
{
	long int width = models[no].width;
	long int height = models[no].height;
	int size=width*4;
	int bpp = 4;
	long int index=models[no].index;
	unsigned int offset_b;
	long int addr,r_addr=index;
	long int mx=800;

	for (long int i = y; i < y+height; i++)
	{
           addr = ((i*(mx)+x)*bpp);
	       setBank((int)(addr >> 16));
	       offset_b = addr & 0xFFFF;
	       if (offset_b+size>65335)
	       {
	       	//direct_copy_mem_to_mem(vb+offset_b,vb2,r_addr,65536-offset_b);
	       //	r_addr+=65536-offset_b;
	       //setBank(curBank+1);
	       //	direct_copy_mem_to_mem(vb,vb2,r_addr,size-(65536-offset_b));
	       }
	       //else
	       {
	       	direct_copy_mem_to_mem(vb+offset_b,vb2,r_addr,size);
	       }
	       r_addr+=size;
	}

}

void direct_draw_models(unsigned int &handle,int no,int x,int y)
{
	long int width = models[no].width;
	long int height = models[no].height;
	long int size=width*4;
	int bpp = 4;
	long int index=models[no].index;
	long int offset_b;
	long int addr,r_addr=index;
	long int mx=800;

	for (long int i = y; i < y+height; i++)
	{
           addr = ((i*(mx)+x)*bpp);
	       setBank((int)(addr >> 16));
	       offset_b = addr & 0xFFFF;
	       if (offset_b+size>65535)
	       {
	       	XMS_CopyFromXMS(vb+offset_b,handle,r_addr,65536-offset_b);
	       	r_addr+=65536-offset_b;
	       setBank(curBank+1);
	       	XMS_CopyFromXMS(vb,handle,r_addr,size-65536+offset_b);
	       	r_addr-=65536-offset_b;
	       }
	       else
	       {
	       	XMS_CopyFromXMS(vb+offset_b,handle,r_addr,size); 	
	       }
	       r_addr+=size;
	       
	}

}

void direct_load_models(unsigned int &handle,int no,char *file_name)
{
	bmpHeaderType bmpHeader;		// to hold image information
	FILE *dataFile; 				// file pointer
    dataFile = fopen (file_name, "rb");
    if (dataFile==NULL)
    {
    	file_save(log_file,"\\\\error--\\\\ ",file_name);
    	file_save(log_file," does not ","exist",NOSPACE);
    	exit(-1);
    }
	read_bmp_header (dataFile,bmpHeader);
	file_save(log_file,"direct_load_models is loading model no. ",no);
	file_save(log_file,"which is ",file_name,SPACE);
	fseek (dataFile, 54, SEEK_SET);	// start reading the image

	long int width = bmpHeader.cols;		// read width from the header
	long int height = bmpHeader.rows;
	int bpp = 4;
	unsigned char byt[3];
	int bpl=width*bpp;
	long int x,y;
	long int index;
	if (no==0)
	{
		index=0;
		models[no].index=index;
		models[no].size=width*height*bpp;
		models[no].width=width;
		models[no].height=height;
	}
	else
	{
		index=models[no-1].index+models[no-1].size;
		models[no].index=index;
		models[no].size=width*height*bpp;
		models[no].width=width;
		models[no].height=height;	
	}
	index+=width*height*bpp - bpl;
	file_save(log_file,"size is ",models[no].size,SPACE);
		for (y = 0; y < height; y++)
		{
			for(x=0; x<width; x++)
			{
				byt[0] = fgetc(dataFile);
				byt[1] = fgetc(dataFile);
				byt[2] = fgetc(dataFile);
				XMS_CopyToXMS(handle,index,byt,4);
				index+=4;
				if (x==width-1)
				{
					index-=2*bpl;
				}
			}
		}
	fclose (dataFile);				// close the file
	if (models[no].index+models[no].size>2700000L)
	{
		file_save(log_file,"--------warning ","model_handle 90 percent full------");
	}
}



void direct_draw_page(unsigned int &handle,int x1,int y1,int x2,int y2)
{
	int dx=x2-x1;
	long int addr;
long int mx=800,bpp=4,size=4*dx;
unsigned int offset_b;
	for (long int i = y1; i < y2; i++)
	{
           addr = ((i*(mx)+x1)*bpp);
	       setBank((int)(addr >> 16));
	       offset_b = addr & 0xFFFF;
	       if (offset_b+size>65535)
	       {
	       	XMS_CopyFromXMS(vb+offset_b,handle,addr,65536-offset_b);
	       	addr+=65536-offset_b;
	       setBank(curBank+1);
		XMS_CopyFromXMS(vb,handle,addr,size-(65536-offset_b));
	       }
	       else
	       {
	       	XMS_CopyFromXMS(vb+offset_b,handle,addr,size);
	       }
	}
}

void direct_draw_bmp(unsigned int &handle,int no)
{
	long int index=0;
	for (int i = 0; i < no; i++)
	{
		setBank(i);
		XMS_CopyFromXMS(vb,handle,index,65536);
		index+=65536;
	}
}

void direct_draw_nbmp(unsigned int &handle,int n)
{
	long int ii=1920000L;
	ii=ii*n;
	long int index=ii;
	for (int i = 0; i < 30; i++)
	{
		setBank(i);
		XMS_CopyFromXMS(vb,handle,index,65536);
		index+=65536;
	}
}

void direct_load_bmp(unsigned int &handle,char *file_name)
{
	logs(START_TIMER);
	bmpHeaderType bmpHeader;		// to hold image information
	FILE *dataFile; 				// file pointer
    dataFile = fopen (file_name, "rb");
	read_bmp_header (dataFile,bmpHeader);
	file_save(log_file,"direct_load_bmp is loading ",file_name);
	fseek (dataFile, 54, SEEK_SET);	// start reading the image

	long int width = bmpHeader.cols;		// read width from the header
	long int height = bmpHeader.rows;
	long int bpp = bmpHeader.bitsPerPixel;
	file_save(log_file," its height is ",height,NOSPACE);
	file_save(log_file," and its size is ",width*height*4,NOSPACE);
	unsigned char byt[3];
	long int x,y;
	long int index=3200*(height-1);
		for (y = 0; y < height; y++)
		{
			for(x=0; x<width; x++)
			{
				byt[0] = fgetc(dataFile);
				byt[1] = fgetc(dataFile);
				byt[2] = fgetc(dataFile);
				XMS_CopyToXMS(handle,index,byt,4);
				index+=4;
				if (x==width-1)
				{
					index-=6400;
				}
			}
		}
	fclose (dataFile);				// close the file
	logs(STOP_TIMER);
}

void direct_load_nbmp(unsigned int &handle,char *file_name,int i)
{
	logs(START_TIMER);
	bmpHeaderType bmpHeader;		// to hold image information
	FILE *dataFile; 				// file pointer
    dataFile = fopen (file_name, "rb");
	read_bmp_header (dataFile,bmpHeader);
	file_save(log_file,"direct_load_bmp is loading ",file_name);
	fseek (dataFile, 54, SEEK_SET);	// start reading the image

	long int width = bmpHeader.cols;		// read width from the header
	long int height = bmpHeader.rows;
	long int bpp = bmpHeader.bitsPerPixel;
	file_save(log_file," its height is ",height,NOSPACE);
	file_save(log_file," and its size is ",width*height*4,NOSPACE);
	unsigned char byt[3];
	long int x,y;
	long int ii=1920000L;
	ii=ii*i;
	long int index=3200*(height-1);
	index+=ii;
		for (y = 0; y < height; y++)
		{
			for(x=0; x<width; x++)
			{
				byt[0] = fgetc(dataFile);
				byt[1] = fgetc(dataFile);
				byt[2] = fgetc(dataFile);
				XMS_CopyToXMS(handle,index,byt,4);
				index+=4;
				if (x==width-1)
				{
					index-=6400;
				}
			}
		}
	fclose (dataFile);				// close the file
	logs(STOP_TIMER);
}


void direct_set_color(colour c)
{
for (long int i = 0; i < 3200;)
{
	vb3[i]=c.r;
	vb3[i+1]=c.g;
	vb3[i+2]=c.b;
	i+=4;
}
}

void direct_draw_rect(int x1,int y1,int x2,int y2,colour c)
{
unsigned offset_b;
long int addr,id;
long int mx=799,bpp=4,size=4*(x2-x1);
	for (int i = y1; i < y2; i++)
	{
		addr = ((i*(mx+1)+x1)*bpp);
	    setBank((int)(addr >> 16));
	    unsigned offset_b = addr & 0xFFFF;
		for (int j = 0; j < size;)
		{
			vb[offset_b+j]=c.r;
			vb[offset_b+j+1]=c.g;
			vb[offset_b+j+2]=c.b;
			j+=4;
		}
	}
}

void direct_draw_rect(int x1,int y1,int x2,int y2)
{
unsigned offset_b;
long int addr,id;
long int mx=799,bpp=4,size=4*(x2-x1);
		for (long int j = y1; j < y2; j++)
		{
           addr = ((j*(mx+1)+x1)*bpp);
	       setBank((int)(addr >> 16));
	       unsigned offset_b = addr & 0xFFFF;
	       if (offset_b+size>65535)
	       {
	       	memcpy(vb+offset_b,vb3,65536-offset_b);
	       setBank(curBank+1);
	       memcpy(vb,vb3,size-(65536-offset_b));
	       }
	       else
	       {
	       memcpy(vb+offset_b,vb3,size);
	       }
		}
}


void file_save(char *file,char *msg,double x,int mode)
{
	fstream myfile;
	myfile.open(file,ios::app);
	if(mode==NEWLINE)
		myfile<<"\n"<<msg<<x;
	if(mode==SPACE)
		myfile<<" "<<msg<<x;
	if(mode==NOSPACE)
		myfile<<msg<<x;
	myfile.close();
}

void file_save(char *file,char *msg,char *x,int mode)
{
	fstream myfile;
	myfile.open(file,ios::app);
	if(mode==NEWLINE)
		myfile<<"\n"<<msg<<x;
	if(mode==SPACE)
		myfile<<" "<<msg<<x;
	if(mode==NOSPACE)
		myfile<<msg<<x;
	myfile.close();
}

void put_from_page_mem(mouse &u)
{
		direct_draw_page(visual_page,u.x1,u.y1,u.x1+u.img_x,u.y1+u.img_y);
}

void show_m_mouse(mouse &u)///global
{
	direct_draw_to_page_trans(direct_page5,1,u.x1,u.y1);
	m[0].x1=m[0].x;
	m[0].y1=m[0].y;
}
