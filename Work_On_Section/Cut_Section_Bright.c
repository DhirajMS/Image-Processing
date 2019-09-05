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
	fIn = fopen("images/cameraman.bmp","rb");

	FILE *fOut;
	fOut = fopen("images/cameraman_temp.bmp","wb");

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

//Fill Output Array with Input Array Values

int i,j;

for(i=0;i<width;i++)	
	{
	   for(j=0;j<height;j++)
	   {
            out_buf[i][j] = buf[i][j];
	   }
	}

printf("Enter the array Location you want to Proceed \n");

printf("\n");

int h1,w1,heigth1,width1;

printf("Enter distance from top \n" );
scanf("%d",&h1);
printf("Enter distance from Left side \n" );
scanf("%d",&w1);

printf("Enter Section Height \n" );
scanf("%d",&heigth1);
printf("Enter Section Width \n" );
scanf("%d",&width1);

//Proceed with Operation

//Brightning

int BRIGHTNESS_FACTOR,choice;

printf("Enter your Brightness factor\n");
scanf("%d",&BRIGHTNESS_FACTOR);

int temp;
int max_color = 255;

	for(i=h1; i<h1+heigth1; i++)
	{
	for(j=w1; j<w1+width1; j++)
    {	
		temp = buf[i][j] + BRIGHTNESS_FACTOR;
		out_buf[i][j] = (temp > max_color) ? max_color : temp;
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




 