#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fIn;
	fIn = fopen("images/cameraman.bmp","rb");

	FILE *fOut;
	fOut = fopen("images/cameraman_rotate.bmp","wb");

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

//to rotate image in 3 direction
int i,j,choice;


	printf("Enter your choice :\n");
	printf("1. Rotate right\n");
	printf("2. Rotate left\n");
	printf("3. Rotate 180\n");

	scanf("%d",&choice);

	switch(choice)
	{
		case 1:
			for(i=0;i<width;i++)					//to rotate right
			{
				for(j=0;j<height;j++)
				{
					out_buf[j][height-1-i ] = buf[i][j];
				}
			}
			break;
		case 2:
			for(i=0;i<width;i++)					//to rotate left
			{
				for(j=0;j<height;j++)
				{
					out_buf[j][i]=buf[i][j];
				}
			}
			break;
		case 3:
			for(i=0;i<width;i++)					//to rotate 180 degree
			{
				for(j=0;j<height;j++)
				{
					out_buf[width-i][j]=buf[i][j];
				}
			}
			break;
		default:
			break;
	}

//write back to the output image

	fwrite(out_buf,sizeof(unsigned char),(width *height),fOut);

	fclose(fIn);
	fclose(fOut);

	return 0;
}
