#include <stdio.h>
#include <stdlib.h>

int main()
{

	FILE *fIn;
	fIn = fopen("images/cameraman.bmp","rb");

	FILE *fOut;
	fOut = fopen("images/cameraman_zoom.bmp","wb");

	if (fIn == (FILE*)0)
	{
	printf("Unable to open Image");
    exit(0);
	}

	unsigned char header[54];
	unsigned char colorTable[1024];

	for(int i=0; i<54; i++)
	{
		header[i] =  getc(fIn);
	}

	int width = *(int*)&header[18];
	int height = *(int *)&header[22];
	int bitDepth = *(int *)&header[28];

	if ( bitDepth<=8 )
	{
		fread(colorTable,sizeof(unsigned char),1024, fIn);
	}

	fwrite(header, sizeof(unsigned char),54,fOut);

	unsigned char buf[width][height];
	unsigned char out_buf[width][height];

	fread (buf,sizeof (unsigned char),(height * width), fIn);
	fread (out_buf,sizeof (unsigned char),(height * width), fIn);

	if ( bitDepth<=8 )
	{
		fwrite(colorTable,sizeof(unsigned char),1024, fOut);
	}

/*
int width_mod = width/2;
int height_mod = height/2;
unsigned char buf_crop[height_mod][width_mod];

int i,j;
int k,l;

for(i=0; i<127; i++)
{
for(j=0; j<127; j++)
{
k=2*i;
l=2*j;
out_buf[i][j]=out_buf[k+1][l]=out_buf[k][l+1]=out_buf[k+1][l+1] = buf[k][l];



}
}
*/

int i,j,k,l;
for (i=0; i<width; i++)
{
for (j=0; j<height; j++)
{
for (k=0; k<width; k++)
{
for (l=0; l<height; l++)
{
out_buf[i][j]=buf[k][l];
}
}
}
}
//write back to the output image

	fwrite(out_buf,sizeof(unsigned char),(width *height),fOut);

	fclose(fIn);
	fclose(fOut);

	return 0;
}
