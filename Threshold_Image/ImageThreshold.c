#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main()
{

/**********************************************
Input and Output File name and location
rb = Read Byte : Open file for reading.
wb = Write Byte: Truncate to zero length or create file for writing.
***********************************************/

	FILE *fIn;
	fIn = fopen("images/Notes.bmp","rb");

	FILE *fOut;
	fOut = fopen("images/Notes_Thr.bmp","wb");

/**********************************************
If the Input File doesn't exist or curropted
or unable to read Image then Exit the Program.
***********************************************/
	if (fIn == (FILE*)0)
	{
	printf("Unable to open Image");
    exit(0);
	}

/**************************************************
Read the 54 byte header from fIn
header[18] contains width info.
header[22] contains height info.
header[28] contains bitDepth info.
***************************************************/

	unsigned char header[54];
	unsigned char colorTable[1024];

	for(int i=0; i<54; i++)
	{
		header[i] =  getc(fIn);
	}

	int width = *(int*)&header[18];   	// Extract image height, width and bitDepth from imageHeader
	int height = *(int *)&header[22];
	int bitDepth = *(int *)&header[28];

	if ( bitDepth<=8 )
	{
		fread(colorTable,sizeof(unsigned char),1024, fIn); //Read colortable if exist
	}

	fwrite(header, sizeof(unsigned char),54,fOut);  //write the header back

/*****************************************************
Store Input Image data in buf[width][height]
Store Output Image data in out_buf[width][height]
******************************************************/

	unsigned char buf[width][height];
	unsigned char out_buf[width][height];

	fread (buf,sizeof (unsigned char),(height * width), fIn);
	fread (out_buf,sizeof (unsigned char),(height * width), fIn);

	if ( bitDepth<=8 )
	{
		fwrite(colorTable,sizeof(unsigned char),1024, fOut);
	}


/*****************************************************
Do Image Operations on the array buf[width][height]
and store output in out_buf[width][height]
******************************************************/

	int i,j,n,choice;
	     	int h = 0;


     int hist[256] = { 0 };

     for (i = 0; i < width ; i++)
     {
        for (j =0; j< height; j++)
        {
        	n = buf[i][j];

			hist[n] = hist[n] + 1 ;
        }
     }

     int k1,k3;

     for (i=0; i<125; i++)
     {
         k1 = ( hist[i] > hist[i-1] ? hist[i] : hist[i-1] ) ;
     }

     for (i=125; i<256; i++)
     {
         k3 = ( hist[i] > hist[i-1] ? hist[i] : hist[i-1] ) ;
     }

int k2 = (k1+k3)/2;

//printf("max frequency is at gray level : %d\n",k);

for(i=0; i<256; i++)
    {
    for(j=0; j<256; j++)
      {
       if(buf[i][j] < k2)
        {
            out_buf[i][j] = 0;
        }
		else
			out_buf[i][j] = 255;

      }
    }
/********************************************************
Write back to the output image with new out_buf.
Close both input and output Image files
*********************************************************/

	fwrite(out_buf,sizeof(unsigned char),(width *height),fOut);

	fclose(fIn);
	fclose(fOut);

	return 0;

}


