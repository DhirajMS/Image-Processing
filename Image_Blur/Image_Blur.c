#include <stdio.h>
#include <stdlib.h>

int main()
{	
	 char input_image[0x100];
	 char output_image[0x100];
	 
     snprintf(input_image, sizeof(input_image), "%s.bmp", "images/cameraman");
     snprintf(output_image, sizeof(output_image), "%s.bmp", "images/cameraman_rotate");
	 
	 
    FILE *fIn = fopen(input_image, "r");
    FILE *fOut = fopen(output_image, "w");


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
	
	printf("Height is %d",height);

int i,j;
for(i=0; i<width;i++)
{
for(j=0; j<height;j++)
{
	out_buf[j][i]=buf[j][i]*0.25;
}
}

//write back to the output image

	fwrite(out_buf,sizeof(unsigned char),(width *height),fOut);

	fclose(fIn);
	fclose(fOut);

	return 0;
}
