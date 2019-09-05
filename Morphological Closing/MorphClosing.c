#include <stdio.h>
#include <stdlib.h>

int main()
{

/**********************************************

Input and Output File name and location
rb = Open file for reading.
wb = Truncate to zero length or create file for writing.

***********************************************/

	FILE *fIn;
	fIn = fopen("images/tablet_binary.bmp","rb");

	FILE *fOut;
	fOut = fopen("images/tablet_binary_morph_c.bmp","wb");

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

short mask[3][3] = {
                           { 0,   0,   0 },

                           { 1,   1,   1 },

                           { 0,   0,   0 },
                     };

//Mask Erosion

int i,j,a,b,min;

   for(i=1; i<width-1; i++)
   {
      for(j=1; j<height-1; j++)
	  {
         min = value;
         for(a=-1; a<=1; a++)
		 {
             for(b=-1; b<=1; b++)
			 {
                if(mask[a+1][b+1] == 1)
				{
                   if(buf[i+a][j+b] < min)

                      min = buf[i+a][j+b];

                }
             }
         }
         out_buf[i][j] = max;
      }
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



