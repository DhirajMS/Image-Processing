#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fIn1;
	fIn1 = fopen("images/cameraman1.bmp","rb");
	FILE *fIn2;
	fIn2 = fopen("images/cameraman2.bmp","rb");

	FILE *fOut;
	fOut = fopen("images/Added_Image.bmp","wb");

	if (fIn1 == (FILE*)0)
	{
	printf("Unable to open Image 1\n");
    exit(0);
	}
	if (fIn2 == (FILE*)0)
	{
	printf("Unable to open Image 2\n");
    exit(0);
	}

/*****************

  Image 1

*****************/ 

	unsigned char header1[54];
	unsigned char colorTable1[1024];

	for(int i=0; i<54; i++)
	{
		header1[i] =  getc(fIn1);
	}

	int width1 = *(int*)&header1[18];
	int height1 = *(int *)&header1[22];
	int bitDepth1 = *(int *)&header1[28];

	if ( bitDepth1<=8 )
	{
		fread(colorTable1,sizeof(unsigned char),1024, fIn1);
	}

/*****************

  Image 2

*****************/ 


	unsigned char header2[54];
	unsigned char colorTable2[1024];

	for(int i=0; i<54; i++)
	{
		header2[i] =  getc(fIn2);
	}

	int width2 = *(int*)&header2[18];
	int height2 = *(int *)&header2[22];
	int bitDepth2 = *(int *)&header2[28];

	if ( bitDepth2<=8 )
	{
		fread(colorTable1,sizeof(unsigned char),1024, fIn2);
	}

/*****/

	fwrite(header1, sizeof(unsigned char),54,fOut);

	unsigned char buf1[height1][width1];
	unsigned char buf2[height2][width2];
	unsigned char out_buf[width1][height2];

	fread (buf1,sizeof (unsigned char),(height1 * width1), fIn1);
	fread (buf2,sizeof (unsigned char),(height2 * width2), fIn2);
	fread (out_buf,sizeof (unsigned char),(height1 * width1), fIn1);

	if ( bitDepth1<=8 )
	{
		fwrite(colorTable1,sizeof(unsigned char),1024, fOut);
	}

int i,j;
for(i=0; i<255;i++)
{
for(j=0; j<255;j++)
{
	out_buf[j][i]=buf1[j][i]*0.5 - buf2[j][i]*0.5;
}
}

//write back to the output image

	fwrite(out_buf,sizeof(unsigned char),(width1 *height1),fOut);

	fclose(fIn1);
	fclose(fIn2);
	fclose(fOut);

	return 0;
}
