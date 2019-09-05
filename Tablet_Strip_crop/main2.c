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
	fIn = fopen("images/tablet.bmp","rb");

	FILE *fOut;
	fOut = fopen("images/cameraman_histogram.bmp","wb");

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

int i,j,a,b,sum;

for (i= 0; i< height; i++ )
{
	for (j = 0; j< width; j++)
	{
		if (buf[i][j] == 255 )
		{
			printf ("%d \t %d \n" , i ,j);
			a = i;
			b = j;
			
		     goto end1;
		}
	}
}

end1:

for (i= a ; i < height; i++ )
{
	sum = 0;
	
	for (j = 0 ; j < width; j++)
	{
		sum = sum + buf[i][j];
	}
	
	if (sum == 0)
	{
		printf ("%d \t %d \n",i,b);
		goto end2;
	}
}

end2:

return 0;

}


