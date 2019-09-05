#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fIn;
	fIn = fopen("images/Broken_Tablet.bmp","rb");

	FILE *fOut;
	fOut = fopen("images/Broken_Tablet_cp.bmp","wb");

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

	unsigned char buf[height][width];
	unsigned char out_buf[width][height];

	fread (buf,sizeof (unsigned char),(height * width), fIn);
	fread (out_buf,sizeof (unsigned char),(height * width), fIn);

	if ( bitDepth<=8 )
	{
		fwrite(colorTable,sizeof(unsigned char),1024, fOut);
	}

// Brighten ur Image
int BRIGHTNESS_FACTOR,choice;

printf("Enter your Brightness factor\n");
scanf("%d",&BRIGHTNESS_FACTOR);

int i,j;
int temp;
int max_color = 255;

	for(i=0;i<width;i++)
	{
	for(j=0;j<height;j++)
    {
		temp = buf[i][j] + BRIGHTNESS_FACTOR;
		out_buf[i][j] = (temp > max_color) ? max_color : temp;
	}
    }

//write back to the output image

	fwrite(out_buf,sizeof(unsigned char),(width *height),fOut);

	fclose(fIn);
	fclose(fOut);

	return 0;
}
